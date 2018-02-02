#ifndef __PWM_H
#define __PWM_H
#include "sys.h"

extern TIM_HandleTypeDef TIM_Handler;               //定时器3PWM句柄  
extern TIM_OC_InitTypeDef TIM_CHXHandler;           //定时器3通道4句柄

void TIM1_PWM4(u16 arr,u16 psc);     //TIM1通道 4 PWM输出函数
void TIM3_PWM2(u16 arr,u16 psc);     //TIM3通道 2 PWM输出函数
void TIM5_PWM4(u16 arr,u16 psc);     //TIM5通道 4 PWM输出函数
void TIM8_PWM1(u16 arr,u16 psc);     //TIM8通道 1 PWM输出函数
void TIM8_PWM2(u16 arr,u16 psc);     //TIM8通道 2 PWM输出函数
void TIM8_PWM3(u16 arr,u16 psc);     //TIM8通道 3 PWM输出函数
void TIM8_PWM4(u16 arr,u16 psc);     //TIM8通道 4 PWM输出函数

#endif

