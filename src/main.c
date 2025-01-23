#include <msp430g2553.h>
#include <stdint.h>
#include "constants.h"
#include "motorFunctions.h"
#include "ADC.h"
#include "Afficheur.h"
#include "utils.h"

// Variables globales

extern volatile uint16_t encoderA_pulse_count;
extern volatile uint16_t encoderB_pulse_count;
extern volatile uint16_t time;


void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;  // Stop the watchdog timer
    BCSCTL1 = CALBC1_1MHZ;     // Set clock frequency to 1MHz
    DCOCTL = CALDCO_1MHZ;      // Set clock frequency to 1MHz 

    __enable_interrupt();

    progTimeInit();
    motorInit();
    encoderInit();
    ADC_init();
    Aff_Init();

    char obstacle = 0;
    char cercle = 0;
    uint16_t oldCount = 0;
    int left, right;
    //setMotorParams(20, 0b011);

    while (1)
    {
        // Obstacle detection and go back
        if (!obstacle) {
            ADC_Demarrer_conversion(0);
            if ((ADC_Lire_resultat() > OBSTACLE_THRESH_RAW_ADC)) obstacle |= BIT0;
        }
        if (obstacle & BIT0) {
            if (!(obstacle & BIT1)) {
                oldCount = encoderB_pulse_count;
                setMotorParams(MOTOR_SLOW_SPEED, 0b101);
                setMotorParams(MOTOR_SLOW_SPEED, 0b010);
                obstacle |= BIT1;
            }
            if (encoderB_pulse_count - oldCount > NB_IMPULS_DEMI_TOUR) {
                setMotorParams(0,0b111);
                obstacle &= ~BIT0;
            }
        } else {
            if (!cercle) {
                ADC_Demarrer_conversion(VOIE_CAPT_LIGNE_G);
                left = ADC_Lire_resultat();
                ADC_Demarrer_conversion(VOIE_CAPT_LIGNE_D);
                right = ADC_Lire_resultat();

                //Aff_valeur((left << 4 & 0xFF00) | right >> 4 & 0x00FF);

                if (left < WHITE_THRESH) setMotorParams(0, 0b101);

                else if (left > L_BLACK_THRESH) setMotorParams(MOTOR_SPEED, 0b101);

                if (right < WHITE_THRESH) setMotorParams(0, 0b011);

                else if (right > R_BLACK_THRESH) setMotorParams(MOTOR_SPEED, 0b011);
            }


            if (left < WHITE_THRESH && right < WHITE_THRESH) cercle |= BIT0;
            if (cercle & BIT0) {
                if (!(cercle & BIT1)) {
                    oldCount = encoderB_pulse_count;
                    setMotorParams(MOTOR_SLOW_SPEED, 0b111);
                    cercle |= BIT1;
                }
                if (encoderB_pulse_count - oldCount > NB_IMPULS_CERCLE) {
                    setMotorParams(0,0b111);
                    break;
                }
            }
        }
    }
}