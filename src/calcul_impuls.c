#include <msp430g2553.h>
#include <stdio.h>  


//compteurs d'impulsions
volatile uint16_t encoderA_pulse_count = 0;
volatile uint16_t encoderB_pulse_count = 0;


// Initialisation des broches et interruptions pour les codeurs incrémentaux
void encoderInit(void) {
    // Configuration pour P2.3 (codeur A)
    P2DIR &= ~BIT3;        // Entrée pour P2.3
    P2IE  |= BIT3;         // Activation des interruptions sur P2.3
    P2IES &= ~BIT3;        // Front montant
    P2IFG &= ~BIT3;        // Réinitialisation du drapeau d'interruption
    
    // Configuration pour P1.6 (codeur B)
    P1DIR &= ~BIT6;        // Entrée pour P1.6
    P1IE  |= BIT6;         // Activation des interruptions sur P1.6
    P1IES &= ~BIT6;        // Front montant
    P1IFG &= ~BIT6;        // Réinitialisation du drapeau d'interruption
}

// Gestionnaire d'interruption pour P2 (codeur A)
#pragma vector=PORT2_VECTOR
__interrupt void Port_2_ISR(void) {
    if (P2IFG & BIT3) {      // Si interruption sur P2.3
        encoderB_pulse_count++;  // Incrémenter le compteur du codeur B
        P2IFG &= ~BIT3;      // Effacer le drapeau d'interruption
    }
}

// Gestionnaire d'interruption pour P1 (codeur B)
#pragma vector=PORT1_VECTOR
__interrupt void Port_1_ISR(void) {
    if (P1IFG & BIT6) {      // Si interruption sur P1.6
        encoderA_pulse_count++;  // Incrémenter le compteur du codeur A
        P1IFG &= ~BIT6;      // Effacer le drapeau d'interruption
    }
}