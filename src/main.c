#include <msp430g2553.h>
#include <stdint.h>
#include "motorFunctions.c"
#include "ADC.h"

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;  // Stop the watchdog timer
    BCSCTL1 = CALBC1_1MHZ;     // Set clock frequency to 1MHz
    DCOCTL = CALDCO_1MHZ;      // Set clock frequency to 1MHz

    while (1) {
        motorInit();
        ADC_init();
        ADC_Demarrer_conversion(0);
        char res = (ADC_Lire_resultat() < 500);
        setMotorParams(50, 50, res);
    }
 
}
