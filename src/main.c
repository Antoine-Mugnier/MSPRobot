#include <msp430g2553.h>
#include <stdint.h>
#include "constants.h"
#include "motorFunctions.h"
#include "ADC.h"
//#include "Afficheur.h"
#include "utils.h"


void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;  // Stop the watchdog timer
    BCSCTL1 = CALBC1_1MHZ;     // Set clock frequency to 1MHz
    DCOCTL = CALDCO_1MHZ;      // Set clock frequency to 1MHz 

    __enable_interrupt();

    progTimeInit();
    motorInit();
    ADC_init();
    
    int g, d;
    uint16_t oldTime = 0;
    while (1)
    {
        if (time - oldTime >= 1) {
            oldTime = time;
            ADC_Demarrer_conversion(VOIE_CAPT_LIGNE_G);
            g = ADC_Lire_resultat();
            ADC_Demarrer_conversion(VOIE_CAPT_LIGNE_D);
            d = ADC_Lire_resultat();

            if (g < 0x3f0)
            {
                setMotorParams(100, 0b101);
            }
            else if (g > 0x260)
            {
                setMotorParams(100, 0b100);
            }
            if (d < 0x3f0)
            {
                setMotorParams(100, 0b011);
            }
            else if (d > 0x260)
            {
                setMotorParams(100, 0b010);
            }
        }
    }
}