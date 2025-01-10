#ifndef ENCODER_H
#define ENCODER_H

// Variables globales

extern volatile uint16_t encoderA_pulse_count;
extern volatile uint16_t encoderB_pulse_count;

// Prototypes des fonctions
void encoderInit(void);

#endif // ENCODER_H
