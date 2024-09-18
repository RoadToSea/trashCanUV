#include "SR04.h"

SR04 *init(GPIO_TypeDef *typeHandle, uint16_t gpioHandle, TIM_HandleTypeDef *timHandle)
{
    SR04* instance = (SR04*)malloc(sizeof(SR04));
    LOG(instance!=NULL);
    instance->type = typeHandle;
    instance->gpio = gpioHandle;
    instance->tim = timHandle;
    return instance;
}
