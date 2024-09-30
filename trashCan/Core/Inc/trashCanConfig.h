#ifndef __TRANSHCANCONFIG_H_
#define __TRANSHCANCONFIG_H_

#include "main.h"

//主频:HZ
#define CLK         180000000 
#define APB1CLK     90000000
#define TIM4PSC     90
#define TIM4ARR     20000
#define TIM2ARR     10000
#define TIM8ARR     10000

//@connect.c
#define flag_t      uint8_t
//数据起始终止符号
#define startFlag   '+'
#define endFlag     '-'
//接收缓存区大小
#define ArraySize   50

//@steer.c
//舵机零点角度
#define cloudSteerZero   90 
#define topIncline       30
#define bottomIncline    30
#define aroundSteerZero  30
//延时时间,(ms)
#define delay_time      0
#define reset_time      800

//@motor.c
//使用输出比较模式还是pwm模式配合脉冲完成中断
#define USE_PWM   1
#define USE_OC    0

//@SR04.c
//垃圾框长度
#define canLength   10


typedef enum trashSpecies{
    Recycle,
    Harmful,
    Kitchen,
    Other
}trashSpecies;

typedef struct transport_info{
    trashSpecies kind;
    uint32_t coordX;
    uint32_t coordY;
}transportInfo;





#endif
