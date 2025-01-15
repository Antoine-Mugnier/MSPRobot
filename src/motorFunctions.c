#include <msp430g2553.h>
#include <stdint.h>
#include "constants.h"


void motorInit() {
    // Set P2.1, P2.2, P2.4, P2.5 as outputs
    P2DIR |= BIT1 | BIT2 | BIT4 | BIT5; 

    // Set P2.2 and P2.4 for Timer A output (PWM)
    P2SEL |= BIT2 | BIT4; 
    P2SEL2 &= ~(BIT2 | BIT4); 

    // Timer A configuration for PWM
    TA1CTL = TASSEL_2 | MC_1;    // SMCLK source, Up mode
    TA1CCTL1 |= OUTMOD_7;        // PWM output on TA1.1
    TA1CCTL2 |= OUTMOD_7;        // PWM output on TA1.2
    TA1CCR0 = DOUBLE_PWM_PERIOD;

    // Initialize direction for both motors (Forward)
    P2OUT |= BIT1;
    P2OUT &= ~BIT5;
}

void setMotorParams(uint8_t dutyMotor, char MotorAndDirection){
    
    if (MotorAndDirection & BIT2) {
        TA1CCR1 = dutyMotor;        // Duty cycle for motor 1
        if (MotorAndDirection & BIT0) P2OUT &= ~BIT1;
        else P2OUT |= BIT1;

    }
    if (MotorAndDirection & BIT1) {
        TA1CCR2 = dutyMotor;        // Duty cycle for motor 2
        if (MotorAndDirection & BIT0) P2OUT |= BIT5;
        else P2OUT &= ~BIT5;

    }
}
