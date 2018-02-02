#ifndef __CHECK_H
#define __CHECK_H
#include "sys.h"

u8 Fun_GZCL(void);   //电机故障（过流、过载）处理函数

u8 GDCheck(u8 num);  //校验光电信号
void GDCheckAll();   //校验光电信号

#endif


