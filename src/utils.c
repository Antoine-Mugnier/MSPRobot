#include <msp430g2553.h>
#include <stdint.h>

volatile uint16_t time = 0;

void progTimeInit(void) {
    TA0CTL = TASSEL_2 | MC_1 | ID_0;   // SMCLK, up mode, no division
    TA0CCR0 = 10000 - 1;                // Set Timer A0 period to 10ms
    TA0CCTL0 = CCIE;                   // Enable interrupt on CCR0
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A0_ISR(void)
{
    time++; // Increment the millisecond counter
}