#include "steer.h"
#include "trashCanConfig.h"
#include <stdio.h>
#include <stdlib.h>
#include "log.h"
#include "tim.h"
#include "control.h"

static float CCR_once_Degree = 0; 
static float CCR_zero = 0;

extern transportInfo info;

Steer* top;
Steer* bottom;
Steer* around;

Steer* steerCreate(TIM_HandleTypeDef* tim,uint32_t chan,uint16_t degr)
{
    Steer* st = (Steer*)malloc(sizeof(Steer));
    LOG(st==NULL,"steer is null");
    st->timHandle=tim;
    st->channel=chan;
    st->degree = degr;
    st->CCRVal = degr*CCR_once_Degree+CCR_zero; 
    st->setDegree=setDegree;
    LOG(HAL_TIM_PWM_Start(st->timHandle,st->channel)!=HAL_OK,"pwm start error");
    __HAL_TIM_SET_COMPARE(st->timHandle,st->channel,st->CCRVal);
    return st;
}

void steerInit(void)
{
    //(2.5-0.5)/20*TIM4ARR/180 -> TIM4ARR/1800
    CCR_once_Degree = TIM4ARR/1800;
    //0.5/20*TIM4ARR -> 0.025* TIM4ARR
    CCR_zero =  0.025* TIM4ARR;

    top = steerCreate(&htim4,TIM_CHANNEL_1,0);
    bottom = steerCreate(&htim4,TIM_CHANNEL_2,0);
    around = steerCreate(&htim4,TIM_CHANNEL_3,0);
	  dumpReset(top,bottom);
}

void setDegree(Steer*st , uint16_t value)
{
    if(value>180)   value=180;
    st->CCRVal = value *CCR_once_Degree+CCR_zero;
    __HAL_TIM_SET_COMPARE(st->timHandle,st->channel,st->CCRVal);
}
