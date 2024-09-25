#include "control.h"
#include "trashCanConfig.h"
#include "FreeRTOS.h"
#include "SR04.h"
#include "task.h"



//延时时间,(ms)
#define delay_time      500

void dumpReset(Steer *top, Steer *bottom)
{
    setDegree(top,cloudSteerZero);
    setDegree(bottom,cloudSteerZero);
    vTaskDelay(300);
    setDegree(around,aroundSteerZero);
}


void dumpTrash( transportInfo *info)
{
    setDegree(around,aroundSteerZero);
    switch (info->kind)
    {
    case Recycle:
        /* code */
        setDegree(bottom,cloudSteerZero-45);
        vTaskDelay(delay_time);
        setDegree(top,cloudSteerZero+30);
        vTaskDelay(delay_time);
        dumpReset(top,bottom);
        break;
    case Harmful:
        setDegree(bottom,cloudSteerZero+45);
        vTaskDelay(delay_time);
        setDegree(top,cloudSteerZero+30);
        vTaskDelay(delay_time);
        dumpReset(top,bottom);
        break;
    case Kitchen:
        setDegree(bottom,cloudSteerZero-45);
        vTaskDelay(delay_time);
        setDegree(top,cloudSteerZero-30);
        vTaskDelay(delay_time);
        dumpReset(top,bottom);
        break;
    case Other:
        setDegree(bottom,cloudSteerZero+45);
        vTaskDelay(delay_time);
        setDegree(top,cloudSteerZero-30);
        vTaskDelay(delay_time);
        dumpReset(top,bottom);
        break;
    default:
        break;
    }
}


uint8_t isFull(void)
{
    uint8_t ret=0;
    if(getDistance(recycle)<canLength) 
        ret |= 1<<0;
    if(getDistance(harmful)<canLength)
        ret |= 1<<1;
    if(getDistance(kitchen)<canLength)
        ret |= 1<<2;
    if(getDistance(other)<canLength)
        ret |= 1<<3;
    return ret;
}

