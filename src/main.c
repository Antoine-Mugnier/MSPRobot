#include <msp430g2553.h>
#include <stdint.h>
#include "constants.h"
#include "motorFunctions.h"
#include "ADC.h"
#include "Afficheur.h"
#include "utils.h"


void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;  // Stop the watchdog timer
    BCSCTL1 = CALBC1_1MHZ;     // Set clock frequency to 1MHz
    DCOCTL = CALDCO_1MHZ;      // Set clock frequency to 1MHz 

    __enable_interrupt();

    progTimeInit();
    motorInit();
    setMotorParams(100, 0b111);
    ADC_init();
    Aff_Init();
    
    int g, d;
    uint16_t oldTime = 0;
    unsigned char msg [4] = "l r ";
    while (1)
    {
        ADC_Demarrer_conversion(VOIE_CAPT_LIGNE_G);
        g = ADC_Lire_resultat();
        ADC_Demarrer_conversion(VOIE_CAPT_LIGNE_D);
        d = ADC_Lire_resultat();

        
        if (g < 0x200) // Si gauche blanc
        {
            setMotorParams(0, 0b101);
            msg[1] = 'u';
        }
        else if (g > 0x300) // Si gauche noir
        {
            setMotorParams(100, 0b101);
            msg[1] = 'n';
        }
        if (d < 0x200) // Si droite blanc
        {
            setMotorParams(0, 0b011);
            msg[3] = 'u';
        }
        else if (d > 0x2A0) // Si droite noir
        {
            setMotorParams(100, 0b011);
            msg[3] = 'n';
        }
        Aff_Efface();
        Aff_4carac(msg);
        

    }
}