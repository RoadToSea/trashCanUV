#ifndef __STEER_H_
#define __STEER_H_

#include "main.h"




typedef struct steer{
	TIM_HandleTypeDef* 	timHandle;
	uint32_t 						channel;
	uint16_t						CCRVal;
	uint16_t                         degree;
    void(*init)(void);
    void(*setDegree)(struct steer*,uint16_t);
}Steer;


/// @brief 
/// 创建一个Steer对象用于控制舵机
/// @param tim : 控制舵机对应的定时器句柄
/// @param chan : 控制舵机对应的定时器通道
Steer* steerCreate(TIM_HandleTypeDef* tim,uint32_t chan,uint16_t degr);

/// @brief 
/// 初始化舵机的定时器和pwm通道
/// @param  
void init(void);

/// @brief 
/// 控制舵机偏转角度
/// @param value: 偏转角度 
void setDegree(Steer*st ,uint16_t value);



#endif
