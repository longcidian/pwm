/*******************************************************************************
Name	: pwm
Author	: longcd
*******************************************************************************/
#ifndef _PWM_H
#define _PWM_H


typedef struct{
	u8		duty;
	void	(*outHigh)(void);
	void	(*outLow)(void);
}pwm_channel_t;


void pwm_init(void);
void pwm_changeDuty(pwm_channel_t *pChannel, u8 duty);


#endif

