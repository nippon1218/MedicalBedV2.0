#ifndef __PUMP
#define __PUMP
#include "sys.h"

void Sensor_Init(void);            //光电及传感器初始化
void Pump_Init(void);              //水箱IO口初始化
void CXHG_Init(void);              //冲洗烘干电动杆
void Fun_ZBCXHG(u8 dir,u32 n);     //坐便冲洗烘干电动杆（冲洗烘干前推杆先移动一段距离所调用函数）
void Fun_ZBCX(u8 dir,u32 n);       //坐便冲洗电动杆
void Fun_ZBHG(u8 dir,u32 n);       //坐便烘干电动杆

#endif


