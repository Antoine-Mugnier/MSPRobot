#ifndef CONSTANTS_H
#define CONSTANTS_H

#define FASTBOT // Quel robot est utilisé

/* =====================================================================================
    User defined constants
   ===================================================================================== */

#define PWM_FREQ 20 // in kHz, will break the duty cycle scale if changed from 20 which will require adding an expensive runtime multiplication

#define VOIE_CAPT_INFRA 0 // Voie du P1 sur laquelle le capteur infrarouge est branche

#define VOIE_CAPT_LIGNE_G 1
#define VOIE_CAPT_LIGNE_D 2

#ifdef SLOWBOT
    #define MOTOR_SPEED 100
    #define MOTOR_SLOW_SPEED 0
    #define WHITE_THRESH 0x200
    #define L_BLACK_THRESH 0x300
    #define R_BLACK_THRESH 0x2A0
    #define OBSTACLE_THRESH_RAW_ADC 0x200
    #define NB_IMPULS_DEMI_TOUR 23
    #define NB_IMPULS_CERCLE 20
#endif
#ifdef FASTBOT
    #define MOTOR_SPEED 60
    #define MOTOR_SLOW_SPEED 30
    #define WHITE_THRESH 0x250
    #define L_BLACK_THRESH 0x1A0
    #define R_BLACK_THRESH 0x090
    #define OBSTACLE_THRESH_RAW_ADC 0x260
    #define NB_IMPULS_DEMI_TOUR 20
    #define NB_IMPULS_CERCLE 10
#endif

/* =====================================================================================
    Computed constants
   ===================================================================================== */

#define DOUBLE_PWM_PERIOD 2000 / PWM_FREQ // Twice the period of PWM signal

#endif