#ifndef CONSTANTS_H
#define CONSTANTS_H

#define FASTBOT // Quel robot est utilisé

/* =====================================================================================
    User defined constants
   ===================================================================================== */

#define PWM_FREQ 20 // in kHz, will break the duty cycle scale if changed from 20 which will require adding an expensive runtime multiplication

#define VOIE_CAPT_INFRA 0 // Voie du P1 sur laquelle le capteur infrarouge est branche
#define OBSTACLE_DISTANCE_THRESH 4 // distance to stop from obstacle in cm

#define VOIE_CAPT_LIGNE_G 1
#define VOIE_CAPT_LIGNE_D 2

#ifdef SLOWBOT
    #define MOTOR_SPEED 100
    #define MOTOR_SLOW_SPEED 0
    #define WHITE_THRESH 0x200
    #define L_BLACK_THRESH 0x300
    #define R_BLACK_THRESH 0x2A0
#endif
#ifdef FASTBOT
    #define MOTOR_SPEED 65
    #define MOTOR_SLOW_SPEED 20
    #define WHITE_THRESH 0x250
    #define L_BLACK_THRESH 0x1A0
    #define R_BLACK_THRESH 0x090
#endif
/* =====================================================================================
    Computed constants
   ===================================================================================== */

#define DOUBLE_PWM_PERIOD 2000 / PWM_FREQ // Twice the period of PWM signal
#define OBSTACLE_THRESH_RAW_ADC (int) ((2.5 / 1024)/(27.86/OBSTACLE_DISTANCE_THRESH + 0.42)) // Seuil en valeur ADC brute

#endif