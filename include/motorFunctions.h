#ifndef MOTORFUNCTIONS_H
#define MOTORFUNCTIONS_H

/*  Initialize motor pins, run before anything else requiring motor control.
    Uses timer A1 so it can't be used for anything else.
*/
void motorInit();

/*
    duty cycle in % assuming we don't change the pwm period
    0bABdir A and B to select which motor to affect and 0 backwards and 1 forwards for dir.
*/
void setMotorParams(uint8_t dutyMotor, char MotorAndDirection);

#endif
