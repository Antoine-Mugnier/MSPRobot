#include <msp430g2553.h>
#include <stdint.h>
#include "motorFunctions.c"

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;  // Stop the watchdog timer
    BCSCTL1 = CALBC1_1MHZ;     // Set clock frequency to 1MHz
    DCOCTL = CALDCO_1MHZ;      // Set clock frequency to 1MHz

    motorInit();
    setMotorParams(50, 50, 0b11);

    while (1);                   // Enter infinite loop (timer is running autonomously)
}
