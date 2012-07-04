/*
 * Interface to PIC32 JTAG port using FT2232-based USB adapter.
 * For example: Olimex ARM-USB-Tiny adapter.
 *
 * Copyright (C) 2011 Serge Vakulenko
 *
 * This file is part of PIC32PROXY project, which is distributed
 * under the terms of the GNU General Public License (GPL).
 * See the accompanying file "COPYING" for more details.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <usb.h>

#include "adapter.h"
#include "pic32.h"

typedef struct {
    /* Common part */
    adapter_t adapter;
    const char *name;

    /* Device handle for libusb. */
    usb_dev_handle *usbdev;

    /* Transmit buffer for MPSSE packet. */
    unsigned char output [256*16];
    int bytes_to_write;

    /* Receive buffer. */
    unsigned char input [64];
    int bytes_to_read;
    int bytes_per_word;
    unsigned long long fix_high_bit;
    unsigned long long high_byte_mask;
    unsigned long long high_bit_mask;
    unsigned high_byte_bits;

    unsigned serial_execution_mode;
} mpsse_adapter_t;

/*
 * Identifiers of USB adapter.
 */
#define OLIMEX_VID              0x15ba
#define OLIMEX_ARM_USB_TINY     0x0004  /* ARM-USB-Tiny */
#define OLIMEX_ARM_USB_TINY_H   0x002a	/* ARM-USB-Tiny-H */

/*
 * USB endpoints.
 */
#define IN_EP                   0x02
#define OUT_EP                  0x81

/* Requests */
#define SIO_RESET               0 /* Reset the port */
#define SIO_MODEM_CTRL          1 /* Set the modem control register */
#define SIO_SET_FLOW_CTRL       2 /* Set flow control register */
#define SIO_SET_BAUD_RATE       3 /* Set baud rate */
#define SIO_SET_DATA            4 /* Set the data characteristics of the port */
#define SIO_POLL_MODEM_STATUS   5
#define SIO_SET_EVENT_CHAR      6
#define SIO_SET_ERROR_CHAR      7
#define SIO_SET_LATENCY_TIMER   9
#define SIO_GET_LATENCY_TIMER   10
#define SIO_SET_BITMODE         11
#define SIO_READ_PINS           12
#define SIO_READ_EEPROM         0x90
#define SIO_WRITE_EEPROM        0x91
#define SIO_ERASE_EEPROM        0x92

/* MPSSE commands. */
#define CLKWNEG                 0x01
#define BITMODE                 0x02
#define CLKRNEG                 0x04
#define LSB                     0x08
#define WTDI                    0x10
#define RTDO                    0x20
#define WTMS                    0x40

/*
 * Send a packet to USB device.
 */
static void bulk_write (mpsse_adapter_t *a, unsigned char *output, int nbytes)
{
    int bytes_written;

    if (debug_level > 1) {
        int i;
        fprintf (stderr, "usb bulk write %d bytes:", nbytes);
        for (i=0; i<nbytes; i++)
            fprintf (stderr, "%c%02x", i ? '-' : ' ', output[i]);
        fprintf (stderr, "\n");
    }
    bytes_written = usb_bulk_write (a->usbdev, IN_EP, (char*) output,
        nbytes, 1000);
    if (bytes_written < 0) {
        fprintf (stderr, "usb bulk write failed\n");
        exit (-1);
    }
    if (bytes_written != nbytes)
        fprintf (stderr, "usb bulk written %d bytes of %d",
            bytes_written, nbytes);
}

/*
 * If there are any data in transmit buffer -
 * send them to device.
 */
static void mpsse_flush_output (mpsse_adapter_t *a)
{
    int bytes_read, n;
    unsigned char reply [64];

    if (a->bytes_to_write <= 0)
        return;

    bulk_write (a, a->output, a->bytes_to_write);
    a->bytes_to_write = 0;
    if (a->bytes_to_read <= 0)
        return;

    /* Get reply. */
    bytes_read = 0;
    while (bytes_read < a->bytes_to_read) {
        n = usb_bulk_read (a->usbdev, OUT_EP, (char*) reply,
            a->bytes_to_read - bytes_read + 2, 2000);
        if (n < 0) {
            fprintf (stderr, "usb bulk read failed\n");
            exit (-1);
        }
        if (debug_level > 1) {
            if (n != a->bytes_to_read + 2)
                fprintf (stderr, "usb bulk read %d bytes of %d\n",
                    n, a->bytes_to_read - bytes_read + 2);
            else {
                int i;
                fprintf (stderr, "usb bulk read %d bytes:", n);
                for (i=0; i<n; i++)
                    fprintf (stderr, "%c%02x", i ? '-' : ' ', reply[i]);
                fprintf (stderr, "\n");
            }
        }
        if (n > 2) {
            /* Copy data. */
            memcpy (a->input + bytes_read, reply + 2, n - 2);
            bytes_read += n - 2;
        }
    }
    if (debug_level > 1) {
        int i;
        fprintf (stderr, "mpsse_flush_output received %d bytes:", a->bytes_to_read);
        for (i=0; i<a->bytes_to_read; i++)
            fprintf (stderr, "%c%02x", i ? '-' : ' ', a->input[i]);
        fprintf (stderr, "\n");
    }
    a->bytes_to_read = 0;
}

static void mpsse_send (mpsse_adapter_t *a,
    unsigned tms_prolog_nbits, unsigned tms_prolog,
    unsigned tdi_nbits, unsigned long long tdi, int read_flag)
{
    unsigned tms_epilog_nbits = 0, tms_epilog = 0;

    if (tdi_nbits > 0) {
        /* We have some data; add generic prologue TMS 1-0-0
         * and epilogue TMS 1-0. */
        tms_prolog |= 1 << tms_prolog_nbits;
        tms_prolog_nbits += 3;
        tms_epilog = 1;
        tms_epilog_nbits = 2;
    }
    /* Check that we have enough space in output buffer.
     * Max size of one packet is 23 bytes (6+8+3+3+3). */
    if (a->bytes_to_write > sizeof (a->output) - 23)
        mpsse_flush_output (a);

    /* Prepare a packet of MPSSE commands. */
    if (tms_prolog_nbits > 0) {
        /* Prologue TMS, from 1 to 14 bits.
         * 4b - Clock Data to TMS Pin (no Read) */
        a->output [a->bytes_to_write++] = WTMS + BITMODE + CLKWNEG + LSB;
        if (tms_prolog_nbits < 8) {
            a->output [a->bytes_to_write++] = tms_prolog_nbits - 1;
            a->output [a->bytes_to_write++] = tms_prolog;
        } else {
            a->output [a->bytes_to_write++] = 7 - 1;
            a->output [a->bytes_to_write++] = tms_prolog & 0x7f;
            a->output [a->bytes_to_write++] = WTMS + BITMODE + CLKWNEG + LSB;
            a->output [a->bytes_to_write++] = tms_prolog_nbits - 7 - 1;
            a->output [a->bytes_to_write++] = tms_prolog >> 7;
        }
    }
    if (tdi_nbits > 0) {
        /* Data, from 1 to 64 bits. */
        if (tms_epilog_nbits > 0) {
            /* Last bit should be accompanied with signal TMS=1. */
            tdi_nbits--;
        }
        unsigned nbytes = tdi_nbits / 8;
        unsigned last_byte_bits = tdi_nbits & 7;
        if (read_flag) {
            a->high_byte_bits = last_byte_bits;
            a->fix_high_bit = 0;
            a->high_byte_mask = 0;
            a->bytes_per_word = nbytes;
            if (a->high_byte_bits > 0)
                a->bytes_per_word++;
            a->bytes_to_read += a->bytes_per_word;
        }
        if (nbytes > 0) {
            /* Whole bytes.
             * 39 - Clock Data Bytes In and Out LSB First
             * 19 - Clock Data Bytes Out LSB First (no Read) */
            a->output [a->bytes_to_write++] = read_flag ?
                (WTDI + RTDO + CLKWNEG + LSB) :
                (WTDI + CLKWNEG + LSB);
            a->output [a->bytes_to_write++] = nbytes - 1;
            a->output [a->bytes_to_write++] = (nbytes - 1) >> 8;
            while (nbytes-- > 0) {
                a->output [a->bytes_to_write++] = tdi;
                tdi >>= 8;
            }
        }
        if (last_byte_bits) {
            /* Last partial byte.
             * 3b - Clock Data Bits In and Out LSB First
             * 1b - Clock Data Bits Out LSB First (no Read) */
            a->output [a->bytes_to_write++] = read_flag ?
                (WTDI + RTDO + BITMODE + CLKWNEG + LSB) :
                (WTDI + BITMODE + CLKWNEG + LSB);
            a->output [a->bytes_to_write++] = last_byte_bits - 1;
            a->output [a->bytes_to_write++] = tdi;
            tdi >>= last_byte_bits;
            a->high_byte_mask = 0xffULL << (a->bytes_per_word - 1) * 8;
        }
        if (tms_epilog_nbits > 0) {
            /* Last bit (actually two bits).
             * 6b - Clock Data to TMS Pin with Read
             * 4b - Clock Data to TMS Pin (no Read) */
            tdi_nbits++;
            a->output [a->bytes_to_write++] = read_flag ?
                (WTMS + RTDO + BITMODE + CLKWNEG + LSB) :
                (WTMS + BITMODE + CLKWNEG + LSB);
            a->output [a->bytes_to_write++] = 1;
            a->output [a->bytes_to_write++] = tdi << 7 | 1 | tms_epilog << 1;
            tms_epilog_nbits--;
            tms_epilog >>= 1;
            if (read_flag) {
                /* Last bit wil come in next byte.
                 * Compute a mask for correction. */
                a->fix_high_bit = 0x40ULL << (a->bytes_per_word * 8);
                a->bytes_per_word++;
                a->bytes_to_read++;
            }
        }
        if (read_flag)
            a->high_bit_mask = 1ULL << (tdi_nbits - 1);
    }
    if (tms_epilog_nbits > 0) {
        /* Epiloque TMS, from 1 to 7 bits.
         * 4b - Clock Data to TMS Pin (no Read) */
        a->output [a->bytes_to_write++] = WTMS + BITMODE + CLKWNEG + LSB;
        a->output [a->bytes_to_write++] = tms_epilog_nbits - 1;
        a->output [a->bytes_to_write++] = tms_epilog;
    }
}

static unsigned long long mpsse_fix_data (mpsse_adapter_t *a, unsigned long long word)
{
    unsigned long long fix_high_bit = word & a->fix_high_bit;
    //if (debug) fprintf (stderr, "fix (%08llx) high_bit=%08llx\n", word, a->fix_high_bit);

    if (a->high_byte_bits) {
        /* Fix a high byte of received data. */
        unsigned long long high_byte = a->high_byte_mask &
            ((word & a->high_byte_mask) >> (8 - a->high_byte_bits));
        word = (word & ~a->high_byte_mask) | high_byte;
        //if (debug) fprintf (stderr, "Corrected byte %08llx -> %08llx\n", a->high_byte_mask, high_byte);
    }
    word &= a->high_bit_mask - 1;
    if (fix_high_bit) {
        /* Fix a high bit of received data. */
        word |= a->high_bit_mask;
        //if (debug) fprintf (stderr, "Corrected bit %08llx -> %08llx\n", a->high_bit_mask, word >> 9);
    }
    return word;
}

static unsigned long long mpsse_recv (mpsse_adapter_t *a)
{
    unsigned long long word;

    /* Send a packet. */
    mpsse_flush_output (a);

    /* Process a reply: one 64-bit word. */
    memcpy (&word, a->input, sizeof (word));
    return mpsse_fix_data (a, word);
}

static void mpsse_reset (mpsse_adapter_t *a, int trst, int sysrst, int led)
{
    unsigned char output [3];
    unsigned low_output = 0x08; /* TCK idle high */
    unsigned low_direction = 0x1b;
    unsigned high_direction = 0x0f;
    unsigned high_output = 0;

    /* command "set data bits low byte" */
    output [0] = 0x80;
    output [1] = low_output;
    output [2] = low_direction;
    bulk_write (a, output, 3);

    if (! trst)
        high_output |= 1;

    if (sysrst)
        high_output |= 2;

    if (led)
        high_output |= 8;

    /* command "set data bits high byte" */
    output [0] = 0x82;
    output [1] = high_output;
    output [2] = high_direction;

    bulk_write (a, output, 3);
    if (debug_level > 1)
        fprintf (stderr, "mpsse_reset (trst=%d, sysrst=%d) high_output=0x%2.2x, high_direction: 0x%2.2x\n",
            trst, sysrst, high_output, high_direction);
}

static void mpsse_speed (mpsse_adapter_t *a, int divisor)
{
    unsigned char output [3];

    /* command "set TCK divisor" */
    output [0] = 0x86;
    output [1] = divisor;
    output [2] = divisor >> 8;
    bulk_write (a, output, 3);
}

static void mpsse_close (adapter_t *adapter, int power_on)
{
    mpsse_adapter_t *a = (mpsse_adapter_t*) adapter;

    /* Clear EJTAGBOOT mode. */
    mpsse_send (a, 1, 1, 5, TAP_SW_ETAP, 0);    /* Send command. */
    mpsse_send (a, 6, 31, 0, 0, 0);             /* TMS 1-1-1-1-1-0 */
    mpsse_flush_output (a);

    /* LED off. */
    mpsse_reset (a, 0, 0, 0);

    usb_release_interface (a->usbdev, 0);
    usb_close (a->usbdev);
    free (a);
}

/*
 * Read the Device Identification code
 */
static unsigned mpsse_get_idcode (adapter_t *adapter)
{
    mpsse_adapter_t *a = (mpsse_adapter_t*) adapter;
    unsigned idcode;

    /* Reset the JTAG TAP controller: TMS 1-1-1-1-1-0.
     * After reset, the IDCODE register is always selected.
     * Read out 32 bits of data. */
    mpsse_send (a, 6, 31, 32, 0, 1);
    idcode = mpsse_recv (a);

    if (debug_level > 0)
        fprintf (stderr, "%s: idcode %08x\n", a->name, idcode);
    return idcode;
}

/*
 * Put device to serial execution mode.
 */
static void serial_execution (mpsse_adapter_t *a)
{
    if (a->serial_execution_mode)
        return;
    a->serial_execution_mode = 1;

    /* Enter serial execution. */
    if (debug_level > 0)
        fprintf (stderr, "%s: enter serial execution\n", a->name);

    mpsse_send (a, 1, 1, 5, TAP_SW_ETAP, 0);    /* Send command. */
    mpsse_send (a, 1, 1, 5, ETAP_EJTAGBOOT, 0); /* Send command. */

    /* Check status. */
    mpsse_send (a, 1, 1, 5, TAP_SW_MTAP, 0);    /* Send command. */
    mpsse_send (a, 1, 1, 5, MTAP_COMMAND, 0);   /* Send command. */
    mpsse_send (a, 0, 0, 8, MCHP_DEASSERT_RST, 0);  /* Xfer data. */
    mpsse_send (a, 0, 0, 8, MCHP_FLASH_ENABLE, 0);  /* Xfer data. */
    mpsse_send (a, 0, 0, 8, MCHP_STATUS, 1);    /* Xfer data. */
    unsigned status = mpsse_recv (a);
    if (debug_level > 0)
        fprintf (stderr, "%s: status %04x\n", a->name, status);
    if (status != (MCHP_STATUS_CPS | MCHP_STATUS_CFGRDY |
                   MCHP_STATUS_FAEN | MCHP_STATUS_DEVRST)) {
        fprintf (stderr, "%s: invalid status = %04x (reset)\n", a->name, status);
        exit (-1);
    }

    /* Deactivate /SYSRST. */
    mpsse_reset (a, 0, 0, 1);
    mdelay (10);

    /* Check status. */
    mpsse_send (a, 1, 1, 5, TAP_SW_MTAP, 0);    /* Send command. */
    mpsse_send (a, 1, 1, 5, MTAP_COMMAND, 0);   /* Send command. */
    mpsse_send (a, 0, 0, 8, MCHP_STATUS, 1);    /* Xfer data. */
    status = mpsse_recv (a);
    if (debug_level > 0)
        fprintf (stderr, "%s: status %04x\n", a->name, status);
    if (status != (MCHP_STATUS_CPS | MCHP_STATUS_CFGRDY |
                   MCHP_STATUS_FAEN)) {
        fprintf (stderr, "%s: invalid status = %04x (no reset)\n", a->name, status);
        exit (-1);
    }

    /* Leave it in ETAP mode. */
    mpsse_send (a, 1, 1, 5, TAP_SW_ETAP, 0);    /* Send command. */
    mpsse_flush_output (a);
}

static void xfer_instruction (mpsse_adapter_t *a, unsigned instruction)
{
    unsigned ctl;

    if (debug_level > 1)
        fprintf (stderr, "%s: xfer instruction %08x\n", a->name, instruction);

    // Select Control Register
    mpsse_send (a, 1, 1, 5, ETAP_CONTROL, 0);       /* Send command. */

    // Wait until CPU is ready
    // Check if Processor Access bit (bit 18) is set
    do {
        mpsse_send (a, 0, 0, 32, CONTROL_PRACC |    /* Xfer data. */
                                 CONTROL_PROBEN |
                                 CONTROL_PROBTRAP |
                                 CONTROL_EJTAGBRK, 1);
        ctl = mpsse_recv (a);
    } while (! (ctl & CONTROL_PRACC));

    // Select Data Register
    // Send the instruction
    mpsse_send (a, 1, 1, 5, ETAP_DATA, 0);          /* Send command. */
    mpsse_send (a, 0, 0, 32, instruction, 0);       /* Send data. */

    // Tell CPU to execute instruction
    mpsse_send (a, 1, 1, 5, ETAP_CONTROL, 0);       /* Send command. */
    mpsse_send (a, 0, 0, 32, CONTROL_PROBEN |       /* Send data. */
                             CONTROL_PROBTRAP, 0);
}

/*
 * Read a word from memory (without PE).
 */
static unsigned mpsse_read_word (adapter_t *adapter, unsigned addr)
{
    mpsse_adapter_t *a = (mpsse_adapter_t*) adapter;
    unsigned addr_lo = addr & 0xFFFF;
    unsigned addr_hi = (addr >> 16) & 0xFFFF;

    serial_execution (a);

    //fprintf (stderr, "%s: read word from %08x\n", a->name, addr);
    xfer_instruction (a, 0x3c04bf80);           // lui s3, 0xFF20
    xfer_instruction (a, 0x3c080000 | addr_hi); // lui t0, addr_hi
    xfer_instruction (a, 0x35080000 | addr_lo); // ori t0, addr_lo
    xfer_instruction (a, 0x8d090000);           // lw t1, 0(t0)
    xfer_instruction (a, 0xae690000);           // sw t1, 0(s3)

    mpsse_send (a, 1, 1, 5, ETAP_FASTDATA, 0);  /* Send command. */
    mpsse_send (a, 0, 0, 33, 0, 1);             /* Get fastdata. */
    unsigned word = mpsse_recv (a) >> 1;

    if (debug_level > 0)
        fprintf (stderr, "%s: read word at %08x -> %08x\n", a->name, addr, word);
    return word;
}

/*
 * Read a memory block.
 */
static void mpsse_read_data (adapter_t *adapter,
    unsigned addr, unsigned nwords, unsigned *data)
{
    //mpsse_adapter_t *a = (mpsse_adapter_t*) adapter;

    //fprintf (stderr, "%s: read %d bytes from %08x\n", a->name, nwords*4, addr);
    for (; nwords > 0; nwords--) {
        *data++ = mpsse_read_word (adapter, addr);
        addr += 4;
    }
}

/*
 * Initialize adapter F2232.
 * Return a pointer to a data structure, allocated dynamically.
 * When adapter not found, return 0.
 */
adapter_t *adapter_open_mpsse (void)
{
    mpsse_adapter_t *a;
    struct usb_bus *bus;
    struct usb_device *dev;
    char *name;

    usb_init();
    usb_find_busses();
    usb_find_devices();
    for (bus = usb_get_busses(); bus; bus = bus->next) {
        for (dev = bus->devices; dev; dev = dev->next) {
            if (dev->descriptor.idVendor == OLIMEX_VID &&
                (dev->descriptor.idProduct == OLIMEX_ARM_USB_TINY ||
                 dev->descriptor.idProduct == OLIMEX_ARM_USB_TINY_H))
                name = "Olimex ARM-USB-Tiny";
                goto found;
        }
    }
    /*fprintf (stderr, "USB adapter not found: vid=%04x, pid=%04x\n",
        OLIMEX_VID, OLIMEX_PID);*/
    return 0;
found:
    a = calloc (1, sizeof (*a));
    if (! a) {
        fprintf (stderr, "%s: out of memory\n", name);
        return 0;
    }
    a->name = name;
    a->usbdev = usb_open (dev);
    if (! a->usbdev) {
        fprintf (stderr, "%s: usb_open() failed\n", a->name);
        free (a);
        return 0;
    }
    usb_claim_interface (a->usbdev, 0);
    printf ("Adapter: %s, id %04x:%04x\n", a->name,
        dev->descriptor.idVendor, dev->descriptor.idProduct);

    /* Reset the ftdi device. */
    if (usb_control_msg (a->usbdev,
        USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT,
        SIO_RESET, 0, 1, 0, 0, 1000) != 0) {
        if (errno == EPERM)
            fprintf (stderr, "%s: superuser privileges needed.\n", a->name);
        else
            fprintf (stderr, "%s: FTDI reset failed\n", a->name);
failed: usb_release_interface (a->usbdev, 0);
        usb_close (a->usbdev);
        free (a);
        return 0;
    }

    /* MPSSE mode. */
    if (usb_control_msg (a->usbdev,
        USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT,
        SIO_SET_BITMODE, 0x20b, 1, 0, 0, 1000) != 0) {
        fprintf (stderr, "%s: can't set sync mpsse mode\n", a->name);
        goto failed;
    }

    /* Optimal rate is 0.5 MHz.
     * Divide base oscillator 6 MHz by 12. */
    unsigned divisor = 12 - 1;
    unsigned char latency_timer = 2;

    if (usb_control_msg (a->usbdev,
        USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT,
        SIO_SET_LATENCY_TIMER, latency_timer, 1, 0, 0, 1000) != 0) {
        fprintf (stderr, "%s: unable to set latency timer\n", a->name);
        goto failed;
    }
    if (usb_control_msg (a->usbdev,
        USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_IN,
        SIO_GET_LATENCY_TIMER, 0, 1, (char*) &latency_timer, 1, 1000) != 1) {
        fprintf (stderr, "%s: unable to get latency timer\n", a->name);
        goto failed;
    }
    if (debug_level) {
    	fprintf (stderr, "%s: divisor: %u\n", a->name, divisor);
    	fprintf (stderr, "%s: latency timer: %u usec\n", a->name, latency_timer);
    }

    /* Light a LED. */
    mpsse_reset (a, 0, 0, 1);

    if (debug_level) {
     int baud = 6000000 / (divisor + 1);
        fprintf (stderr, "%s: speed %d samples/sec\n", a->name, baud);
    }
    mpsse_speed (a, divisor);

    /* Disable TDI to TDO loopback. */
    unsigned char enable_loopback[] = "\x85";
    bulk_write (a, enable_loopback, 1);

    /* Reset the JTAG TAP controller. */
    mpsse_send (a, 6, 31, 0, 0, 0);             /* TMS 1-1-1-1-1-0 */

    /* Check status. */
    mpsse_send (a, 1, 1, 5, TAP_SW_MTAP, 0);    /* Send command. */
    mpsse_send (a, 1, 1, 5, MTAP_COMMAND, 0);   /* Send command. */
    mpsse_send (a, 0, 0, 8, MCHP_STATUS, 1);    /* Xfer data. */
    unsigned status = mpsse_recv (a);
    if (debug_level > 0)
        fprintf (stderr, "%s: status %04x\n", a->name, status);
    if (status & MCHP_STATUS_DEVRST)
        fprintf (stderr, "%s: processor is in reset mode\n", a->name);
    if ((status & ~MCHP_STATUS_DEVRST) !=
        (MCHP_STATUS_CPS | MCHP_STATUS_CFGRDY | MCHP_STATUS_FAEN))
    {
        fprintf (stderr, "%s: invalid status = %04x\n", a->name, status);
        free (a);
        return 0;
    }

    /* User functions. */
    a->adapter.close = mpsse_close;
    a->adapter.get_idcode = mpsse_get_idcode;
    a->adapter.read_word = mpsse_read_word;
    a->adapter.read_data = mpsse_read_data;
    return &a->adapter;
}
