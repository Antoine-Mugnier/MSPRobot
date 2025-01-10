#include <msp430g2553.h>
#include <stdint.h>
#include "constants.h"
#include "motorFunctions.h"
#include "ADC.h"
#include "Afficheur.h"


void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;  // Stop the watchdog timer
    BCSCTL1 = CALBC1_1MHZ;     // Set clock frequency to 1MHz
    DCOCTL = CALDCO_1MHZ;      // Set clock frequency to 1MHz 

    motorInit();
    ADC_init();
    Aff_Init();
    Aff_Luminosite(255);

    setMotorParams(50, 50, 0b01);
    
    //while (1);                   // Enter infinite loop (timer is running autonomously)
    int res;
    while (1)
    {
        ADC_Demarrer_conversion(VOIE_CAPT_INFRA);
        res = ADC_Lire_resultat();
        Aff_valeur(res);
        if (res > 0x200)
        {
            setMotorParams(0, 0, 0b00);      // Stop motors
        }
        else
        {
            setMotorParams(50, 50, 0b01);    // Resume motor operation
        }

    }
}

/*
// Function to convert ADC value to distance in cm
float convertToDistance(uint16_t adcValue)
{
    float voltage = (adcValue * VREF) / ADC_MAX;  // Convert ADC value to voltage
    // Approximate GP2D120 equation (voltage to distance), empirically derived
    float distance = 27.86 / (voltage - 0.42);    // Distance formula approximation
    if (distance > 30.0) distance = 30.0;         // Cap distance at 30cm
    if (distance < 4.0) distance = 4.0;           // Cap distance at 4cm
    return distance;
} 
*/