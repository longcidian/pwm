/*******************************************************************************
Name	: pwm
Author	: longcd
*******************************************************************************/
#include "stm8l15x.h"
#include "pwm.h"

/*******************************************************************************
*
*/
#define MAX_CHANNEL_NUM		5

/*******************************************************************************
*
*/

typedef struct{
	u8	duty;
	u8	channelNum;
}pwm_t;

/*******************************************************************************
*
*/
pwm_t			pwm;
pwm_channel_t	*pwmChannel[MAX_CHANNEL_NUM];

/*******************************************************************************
*
*/

//called by a timer's overflow interrupt
void pwm_updateDuty(void)
{
	u8	i;

	for(i = 0; i < pwm.channelNum; i++) {
		if(pwm.duty == 0) {
			if(pwmChannel[i]->duty != 0) {
				pwmChannel[i]->outHigh();
			}
		} else if (pwm.duty == pwmChannel[i]->duty) {
			pwmChannel[i]->outLow();
		}
	}

	pwm.duty++;
}

/*******************************************************************************
*	public functions
*/

//use timer4 to generate pwm
void pwm_init(void)
{
	CLK_PeripheralClockConfig(CLK_Peripheral_TIM4,ENABLE);
	TIM4_TimeBaseInit(TIM4_Prescaler_128, 8);	//16M/128/8
	TIM4_ClearFlag(TIM4_FLAG_Update);
	TIM4_ITConfig(TIM4_IT_Update,ENABLE);
	TIM4_Cmd(ENABLE);

	pwm.duty = 0;
	pwm.channelNum = 0;
}

//add a channel to pwm channel array
void pwm_addChannel(pwm_channel_t *pChannel)
{
	if(pwm.channelNum < MAX_CHANNEL_NUM) {
		pwmChannel[pwm.channelNum] = pChannel;
	}

	pwm.channelNum++;
}

//change duty of a pwm channel
void pwm_changeDuty(pwm_channel_t *pChannel, u8 duty)
{
	pChannel->duty = duty;
	if(duty == 0) {
		pChannel->outLow();
	}
}

