#ifndef __SR04_H_
#define __SR04_H_

#include "main.h"

#define (void)(*userInit)(void) 

typedef struct SR{
    GPIO_TypeDef*           type;
    uint16_t                gpio;
    TIM_HandleTypeDef*      tim;
}SR04;

SR04* init(GPIO_TypeDef* typeHandle,uint16_t gpioHandle,TIM_HandleTypeDef* timHandle);
uint8_t isFull(void);

#endif
