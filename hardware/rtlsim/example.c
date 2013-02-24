/*
 * Example of simple simulation.
 */
#include <stdio.h>
#include "rtlsim.h"

#define STACK_NBYTES    2048    /* Stack size for processes */

/* Initialize signals */
signal_t clock  = signal_init ("clock",  0); /* Clock input of the design */
signal_t reset  = signal_init ("reset",  0); /* Active high, synchronous Reset input */
signal_t enable = signal_init ("enable", 0); /* Active high enable signal for counter */
signal_t count  = signal_init ("count",  0); /* 4-bit vector output of the counter */

/*
 * 4-bit up-counter with synchronous active high reset and
 * with active high enable signal.
 */
void proc_counter ()
{
    /* Create a sensitivity list. */
    process_sensitive (&clock, POSEDGE);
    process_sensitive (&reset, 0);

    for (;;) {
        /* Wait for event from the sensitivity list. */
        process_wait();

        /* At every rising edge of clock we check if reset is active.
         * If active, we load the counter output with 4'b0000. */
        if (reset.value != 0) {
            signal_set (&count, 0);

        /* If enable is active, then we increment the counter. */
        } else if (enable.value != 0) {
            int newval = (count.value + 1) & 15;
            signal_set (&count, newval);
            printf ("(%llu) Incremented Counter %u\n", time_ticks, newval);
        }
    }
}

int main (int argc, char **argv)
{
    /* Create processes. */
    process_init ("counter", proc_counter, STACK_NBYTES);

    int i;                      /* Issue some clock pulses */
    for (i=0; i<5; i++) {
        signal_set (&clock, 0);
        process_delay (10);
        signal_set (&clock, 1);
        process_delay (10);
    }
    signal_set (&reset, 1);     /* Assert the reset */
    printf ("(%llu) Asserting reset\n", time_ticks);
    for (i=0; i<10; i++) {
        signal_set (&clock, 0);
        process_delay (10);
        signal_set (&clock, 1);
        process_delay (10);
    }
    signal_set (&reset, 0);     /* De-assert the reset */
    printf ("(%llu) De-Asserting reset\n", time_ticks);
    for (i=0; i<5; i++) {
        signal_set (&clock, 0);
        process_delay (10);
        signal_set (&clock, 1);
        process_delay (10);
    }
    printf ("(%llu) Asserting Enable\n", time_ticks);
    signal_set (&enable, 1);    /* Assert enable */
    for (i=0; i<20; i++) {
        signal_set (&clock, 0);
        process_delay (10);
        signal_set (&clock, 1);
        process_delay (10);
    }
    printf ("(%llu) De-Asserting Enable\n", time_ticks);
    signal_set (&enable, 0);    /* De-assert enable */
    process_delay (10);

    /* Terminate simulation. */
    printf ("(%llu) Terminating simulation\n", time_ticks);
    return 0;
}
