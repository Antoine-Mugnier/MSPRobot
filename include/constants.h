#define PWM_FREQ 20 // kHz will break the duty cycle scale if changed which will require adding an expensive runtime multiplication
#define DOUBLE_PWM_PERIOD 200 / PWM_FREQ // Twice the period of PWM signal
