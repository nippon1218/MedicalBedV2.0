#ifndef __PUMP
#define __PUMP
#include "sys.h"

void Sensor_Init(void);            //��缰��������ʼ��
void Pump_Init(void);              //ˮ��IO�ڳ�ʼ��
void CXHG_Init(void);              //��ϴ��ɵ綯��
void Fun_ZBCXHG(u8 dir,u32 n);     //�����ϴ��ɵ綯�ˣ���ϴ���ǰ�Ƹ����ƶ�һ�ξ��������ú�����
void Fun_ZBCX(u8 dir,u32 n);       //�����ϴ�綯��
void Fun_ZBHG(u8 dir,u32 n);       //�����ɵ綯��

#endif


