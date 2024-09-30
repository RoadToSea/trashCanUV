#include "control.h"
#include "trashCanConfig.h"
#include "FreeRTOS.h"
#include "SR04.h"
#include "task.h"
#include "tim.h"




void dumpTrash( transportInfo *info)
{
    setDegree(around,aroundSteerZero);
    switch (info->kind)
    {
    case Recycle:
        /* code */
        setDegree(bottom,cloudSteerZero-bottomIncline);
        setDegree(top,cloudSteerZero+topIncline);

        break;
    case Harmful:
        setDegree(bottom,cloudSteerZero+bottomIncline);
        setDegree(top,cloudSteerZero-topIncline);

        break;
    case Kitchen:
        setDegree(bottom,cloudSteerZero-bottomIncline);
        setDegree(top,cloudSteerZero-topIncline);

        break;
    case Other:
        setDegree(bottom,cloudSteerZero+bottomIncline);
        setDegree(top,cloudSteerZero+topIncline);

        break;
    default:
        break;
    }
}

void dumpReset(Steer *top, Steer *bottom)
{
    setDegree(top,cloudSteerZero);
    setDegree(bottom,cloudSteerZero);
    setDegree(around,aroundSteerZero);
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

