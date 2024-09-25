#ifndef __CONTROL_H_
#define __CONTROL_H_

#include "main.h"
#include "trashCanConfig.h"
#include "steer.h"

/*
    云台复位
*/
void dumpReset(Steer *top, Steer *bottom);

/*@倾倒垃圾
   根据垃圾种类选择特定位置倾倒
*/
void dumpTrash(transportInfo* info);

/*@是否满载
返回的低四位每一位代表一类垃圾
0000 0001   可回收垃圾
0000 0010   有害垃圾
0000 0100   厨余垃圾
0000 1000   其他垃圾
*/
uint8_t isFull(void);

#endif
