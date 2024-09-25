#ifndef __CONNECT_H_
#define __CONNECT_H_

#include "trashCanConfig.h"
#include "main.h"

void connectInit(UART_HandleTypeDef* uartHandle);
flag_t send(UART_HandleTypeDef* uartHandle,char* info,size_t size);
flag_t receive(transportInfo* des);

#endif
