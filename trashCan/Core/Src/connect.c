#include "connect.h"
#include "gpio.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "cJSON.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "task.h"

//接收缓存区,一个字节
uint8_t ReceiveBuf;
//辅助拷贝接收缓存区数组的索引
uint8_t ReceiveIndex=0;
//拷贝接收缓存区数组
uint8_t ReceiveArray[ArraySize];
//接收到的数据缓存区
uint8_t DATA[ArraySize];
//标志位,是否进行拷贝(接收到开始标志后)
uint8_t copyFlag=0; 
//标志位,是否有数据可以被提取
uint8_t extractFlag=0;

extern osThreadId_t cloudPlatformHandle;


void connectInit(UART_HandleTypeDef* uartHandle )
{
    HAL_UART_Receive_IT(uartHandle,&ReceiveBuf,1);
}

flag_t send(UART_HandleTypeDef *uartHandle, char *info, size_t size)
{
    if(size!=strlen(info))
        return HAL_ERROR;
	  HAL_StatusTypeDef result = HAL_UART_Transmit(uartHandle,(uint8_t*)info,size,0xffff);
    return result;
}

flag_t receive(transportInfo *des) 
{
        cJSON* data = cJSON_Parse((char*)DATA);
				memset(DATA,0,ArraySize);
        if(data==NULL)
        {
            return HAL_ERROR;
        }
        cJSON* species = cJSON_GetObjectItem(data,"species");
        cJSON* coordX = cJSON_GetObjectItem(data,"coordX");
        cJSON* coordY = cJSON_GetObjectItem(data,"coordY");

        des->kind = species->valueint;
        des->coordX = coordX->valueint;
        des->coordY = coordY->valueint;
		if (data != NULL)
        {
            cJSON_Delete(data);
        }

        return HAL_OK;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(copyFlag==1)
    {
        if(ReceiveBuf==endFlag)
        {
						memcpy(DATA,ReceiveArray,ReceiveIndex);
            memset(ReceiveArray,0,ArraySize);
            copyFlag=0;
            ReceiveIndex=0; 
            //发送信号给分类任务
            // BaseType_t xHigherPriorityTaskWoken = pdFALSE;
            // vTaskNotifyGiveFromISR(cloudPlatformHandle,&xHigherPriorityTaskWoken);
            // portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
            osThreadFlagsSet (cloudPlatformHandle, 0x01); // 设置线程标志
        }
        else if(ReceiveIndex >=ArraySize-1)
        {
            memset(ReceiveArray,0,ArraySize);
            copyFlag=0;
            ReceiveIndex=0;  
        }
        else
        {
            ReceiveArray[ReceiveIndex++] = ReceiveBuf;
            //printf("%c",ReceiveBuf);
        }
    }
    if(ReceiveBuf==startFlag)
    {
        copyFlag=1;   
        ReceiveIndex=0; 
    }
    HAL_UART_Receive_IT(huart,&ReceiveBuf,1);
}
