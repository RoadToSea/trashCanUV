#include "steer.h"
#include "trashCanConfig.h"
#include <stdio.h>
#include "log.h"

static uint32_t CCR_once_Degree = (2.5-0.5)/20*TIM4ARR/180; 


Steer* steerCreate(TIM_HandleTypeDef* tim,uint32_t chan,uint16_t degr)
{
    Steer* st = (Steer*)malloc(sizeof(Steer));
    LOG(st!=NULL);
    st->timHandle=tim;
    st->channel=chan;
    st->degree = degr;
    st->CCRVal = degr*CCR_once_Degree; 
    st->init= init;
    st->setDegree=setDegree;
    LOG(HAL_TIM_PWM_Start(st->timHandle,st->channel)==HAL_OK);
    __HAL_TIM_SET_COMPARE(st->timHandle,st->channel,st->CCRVal);
    return st;
}

void init(void)
{
    
}

void setDegree(Steer*st , uint16_t value)
{
    if(value>180)   value=180;
    st->CCRVal = value *CCR_once_Degree;
    __HAL_TIM_SET_COMPARE(st->timHandle,st->channel,st->CCRVal);
}
