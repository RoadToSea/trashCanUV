#ifndef __SR04_H_
#define __SR04_H_

#include "main.h"


#define CPU_FREQUENCY_MHZ    168		// STM32时钟主频

typedef struct SR{
    GPIO_TypeDef*           gpiotype;
    uint16_t                gpio;
    TIM_HandleTypeDef*      tim;
}SR04;

void SR04_init(void);
float getDistance(SR04* device);
uint8_t isFull(void);

extern uint32_t timeCount;
extern SR04* recycle;
extern SR04* harmful;
extern SR04* kitchen;
extern SR04* other;

/*引脚
因为是单线程按顺序读取,所以只需要一个引脚接收
序号        trig        echo
 1           PF1        PF0
 2           PE5        PF0
 3           PE6        PF0
 4           PC2        PF0
*/




#endif
