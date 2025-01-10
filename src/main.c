#include <msp430g2553.h>
#include <stdint.h>
#include "motorFunctions.h"
#include "calcul_impuls.h"
#include "Afficheur.h"

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;  // Stop the watchdog timer
    BCSCTL1 = CALBC1_1MHZ;     // Set clock frequency to 1MHz
    DCOCTL = CALDCO_1MHZ;      // Set clock frequency to 1MHz 

    encoderInit();
    Aff_Init();
    Aff_Efface();
    __enable_interrupt();
    
    while (1){
        Aff_valeur(encoderA_pulse_count);
    }
    
}
