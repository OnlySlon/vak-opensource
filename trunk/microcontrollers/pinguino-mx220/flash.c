/*
 * Include processor definitions.
 */
#include "pic32mx.h"

#define MHZ     40              /* CPU clock is 40 MHz. */

/*
 * Main entry point at bd003000.
 * Setup stack pointer and $gp registers, and jump to main().
 */
asm ("          .section .exception");
asm ("          .globl _start");
asm ("          .type _start, function");
asm ("_start:   la      $sp, _estack");
asm ("          la      $ra, main");
asm ("          la      $gp, _gp");
asm ("          jr      $ra");
asm ("          .text");

/*
 * Secondary entry point at bd004000.
 */
asm ("          .section .startup");
asm ("          .globl _init");
asm ("          .type _init, function");
asm ("_init:    la      $ra, _start");
asm ("          jr      $ra");
asm ("          .text");

/*
 * Delay for a given number of microseconds.
 * The processor has a 32-bit hardware Count register,
 * which increments at half CPU rate.
 * We use it to get a precise delay.
 */
void udelay (unsigned usec)
{
    unsigned now = mfc0 (C0_COUNT, 0);
    unsigned final = now + usec * MHZ / 2;

    for (;;) {
        now = mfc0 (C0_COUNT, 0);

        /* This comparison is valid only when using a signed type. */
        if ((int) (now - final) >= 0)
            break;
    }
}

int main()
{
    /* Initialize coprocessor 0. */
    mtc0 (C0_COUNT, 0, 0);
    mtc0 (C0_COMPARE, 0, -1);
    mtc0 (C0_EBASE, 1, 0x9fc00000);     /* Vector base */
    mtc0 (C0_INTCTL, 1, 1 << 5);        /* Vector spacing 32 bytes */
    mtc0 (C0_CAUSE, 0, 1 << 23);        /* Set IV */
    mtc0 (C0_STATUS, 0, 0);             /* Clear BEV */

    /* Disable JTAG and Trace ports, to make more pins available. */
    DDPCONCLR = 3 << 2;

    /* Use all ports as digital. */
    ANSELA = 0;
    ANSELB = 0;
    LATA = 0;
    LATB = 0;

    /* Use pin RB15 as output: LED1 control. */
    TRISBCLR = 1 << 15;

    /* Use pin RA10 as output: LED2 control. */
    TRISACLR = 1 << 10;
    LATASET = 1 << 10;

    for (;;) {
        /* Invert pin RB15. */
        LATBINV = 1 << 15;

        /* Invert pin RA10. */
        LATAINV = 1 << 10;

        /* Delay. */
        udelay (500000);
    }
}
