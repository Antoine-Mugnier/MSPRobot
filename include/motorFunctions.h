#ifndef MOTORFUNCTIONS_H
#define MOTORFUNCTIONS_H

/*  Initialize motor pins, run before anything else requiring motor control.
    Uses timer A1 so it can't be used for anything else.
*/
void motorInit();

/*  0xAB with 1 forward and 0 backwards
    duty cycle in % assuming we don't change the pwm period
*/
void setMotorParams(uint8_t dutyMotor1, uint8_t dutyMotor2, char direction);

#endif
