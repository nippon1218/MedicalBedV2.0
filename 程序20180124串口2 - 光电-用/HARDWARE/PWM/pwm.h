#ifndef __PWM_H
#define __PWM_H
#include "sys.h"

extern TIM_HandleTypeDef TIM_Handler;               //��ʱ��3PWM���  
extern TIM_OC_InitTypeDef TIM_CHXHandler;           //��ʱ��3ͨ��4���

void TIM1_PWM4(u16 arr,u16 psc);     //TIM1ͨ�� 4 PWM�������
void TIM3_PWM2(u16 arr,u16 psc);     //TIM3ͨ�� 2 PWM�������
void TIM5_PWM4(u16 arr,u16 psc);     //TIM5ͨ�� 4 PWM�������
void TIM8_PWM1(u16 arr,u16 psc);     //TIM8ͨ�� 1 PWM�������
void TIM8_PWM2(u16 arr,u16 psc);     //TIM8ͨ�� 2 PWM�������
void TIM8_PWM3(u16 arr,u16 psc);     //TIM8ͨ�� 3 PWM�������
void TIM8_PWM4(u16 arr,u16 psc);     //TIM8ͨ�� 4 PWM�������

#endif

