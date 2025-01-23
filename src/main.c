#include <msp430g2553.h>
#include <stdint.h>
#include "constants.h"
#include "motorFunctions.h"
#include "ADC.h"
#include "Afficheur.h"
#include "utils.h"

// One step of the line following routine. Intended to be put in main program loop.
void lineFollowRoutine(void) 
{
    int left, right;

    ADC_Demarrer_conversion(VOIE_CAPT_LIGNE_G);
    left = ADC_Lire_resultat();
    ADC_Demarrer_conversion(VOIE_CAPT_LIGNE_D);
    right = ADC_Lire_resultat();
    
    //Aff_valeur((left << 4 & 0xFF00) | right >> 4 & 0x00FF);

    if (left < WHITE_THRESH) setMotorParams(MOTOR_SLOW_SPEED, 0b101);

    else if (left > L_BLACK_THRESH) setMotorParams(MOTOR_SPEED, 0b101);

    if (right < WHITE_THRESH) setMotorParams(MOTOR_SLOW_SPEED, 0b011);

    else if (right > R_BLACK_THRESH) setMotorParams(MOTOR_SPEED, 0b011);
}


void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;  // Stop the watchdog timer
    BCSCTL1 = CALBC1_1MHZ;     // Set clock frequency to 1MHz
    DCOCTL = CALDCO_1MHZ;      // Set clock frequency to 1MHz 

    __enable_interrupt();

    progTimeInit();
    motorInit();
    ADC_init();
    Aff_Init();

    uint16_t oldTime = 0;

    setMotorParams(20, 0b111);

    while (1)
    {
        lineFollowRoutine();
    }

}