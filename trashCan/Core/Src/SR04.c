#include "SR04.h"
#include <stdlib.h>
#include "log.h"
#include "tim.h"
#include "trashCanConfig.h"

uint32_t timeCount = 0;
uint8_t  flag =0 ;//上升沿下降沿标志  0:上升沿  1:下降沿
SR04* recycle;
SR04* harmful;
SR04* kitchen;
SR04* other;

void delay_us(__IO uint32_t delay);

void SR04_init(void)
{
    recycle = (SR04*)malloc(sizeof(SR04));
    harmful = (SR04*)malloc(sizeof(SR04));
    kitchen = (SR04*)malloc(sizeof(SR04));
    other = (SR04*)malloc(sizeof(SR04));
    
    recycle->gpiotype=GPIOF;
    harmful->gpiotype=GPIOE;
    kitchen->gpiotype=GPIOE;
    other->gpiotype=GPIOC;

    recycle->gpio=GPIO_PIN_1;
    harmful->gpio = GPIO_PIN_5;
    kitchen->gpio=GPIO_PIN_6;
    other->gpio=GPIO_PIN_2;

    recycle->tim =&htim8;
    harmful->tim =&htim8;
    kitchen->tim =&htim8;
    other->tim =&htim8;
}

//距离公式:
//距离 = 时间 * 声速(340m/s)/2 
//distance = ((timeStop-timeStart)/ 1000000.0) * 340.0 / 2.0 * 100.0  (m)
//         = (timeStop-timeStart) * 17/1000 (m)
//         = (timeStop-timeStart) * 1.7   (cm)
//没有加溢出判断,测量最大距离为10.2米
float getDistance(SR04* device)
{
    HAL_GPIO_WritePin(device->gpiotype,device->gpio,GPIO_PIN_SET);
	delay_us(20);
	HAL_GPIO_WritePin(device->gpiotype,device->gpio,GPIO_PIN_RESET);
    vTaskDelay(20);
    float distance = timeCount * 0.017;
    return distance;
}



void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(flag == 0)
    {
        __HAL_TIM_SET_COUNTER(&htim8,0);
        HAL_TIM_Base_Start(&htim8);
        flag=1;    
    }
    else if(flag ==1)
    {
        timeCount = __HAL_TIM_GET_COUNTER(&htim8);
        HAL_TIM_Base_Stop(&htim8);
        flag = 0;
    }
}



void delay_us(__IO uint32_t delay)
{
    int last, curr, val;
    int temp;

    while (delay != 0)
    {
        temp = delay > 900 ? 900 : delay;
        last = SysTick->VAL;
        curr = last - CPU_FREQUENCY_MHZ * temp;
        if (curr >= 0)
        {
            do
            {
                val = SysTick->VAL;
            }
            while ((val < last) && (val >= curr));
        }
        else
        {
            curr += CPU_FREQUENCY_MHZ * 1000;
            do
            {
                val = SysTick->VAL;
            }
            while ((val <= last) || (val > curr));
        }
        delay -= temp;
    }
}


