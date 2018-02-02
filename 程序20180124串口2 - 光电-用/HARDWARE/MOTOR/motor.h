#ifndef __MOTOR_H
#define __MOTOR_H
#include "sys.h"


/**************************************************************
                   ���ҵ����������
                   dir�����Ƶ��ҵ���ٶ�
				   pulse�����Ƶ��ҵ������ʱ��
				   ע�����ҵ��2/3ΪС�۵����
				       ���ҵ��1/4Ϊ��۵����
					   �����ʼ������Ϊ1010��
***************************************************************/
void Hang_Init(void);                          //���ҵ������ڡ�����ڳ�ʼ��
void Fun_Auto_DG2(u16 dir,u32 pulse);          //���ҵ��2�ŵ������2
void Fun_Auto_DG3(u16 dir,u32 pulse);          //���ҵ��3�ŵ������4
void Fun_Auto_DG12(u16 dir,u32 pulse);         //����1/2�ŵ��ͬʱ����
void Fun_Auto_DG23(u16 dir,u32 pulse);         //����1/3�ŵ��ͬʱ����
void Fun_Auto_DG34(u16 dir,u32 pulse);         //����3/4�ŵ��ͬʱ����
void Fun_Auto_DG1234(u16 dir,u32 pulse);       //����1/2/3/4�ŵ��ͬʱ����

void Fun_Hand_DG2(u16 dir,u32 pulse);          //���ҵ��2�ŵ������
void Fun_Hand_DG12(u16 dir,u32 pulse);         //����1/2�ŵ��ͬʱ����      
void Fun_Hand_DG3(u16 dir,u32 pulse);          //���ҵ��3�ŵ������
void Fun_Hand_DG34(u16 dir,u32 pulse);         //����3/4�ŵ��ͬʱ����
void Fun_Hand_DG23(u16 dir,u32 pulse);         //����2/3�ŵ��ͬʱ����
void Fun_Hand_DG1234(u16 dir,u32 pulse);       //����1/2/3/4�ŵ��ͬʱ����

/**************************************************************
                   ���ܺ��������������
                   arr���Զ���װֵ
				   psc��ʱ��Ԥ��Ƶ��
***************************************************************/
void Motor_Init(void);             //���IO�ڳ�ʼ������

void MotorStart(u8 Motori,u8 dir,u16 arr,u16 psc);  //�����������
void MotorStop(u8 Motori);                          //�������ֹͣ
void Motor_All_Stop(void);                          //���е��ֹͣ
void Motor4_BC(u8 dir,u16 time_arr,u16 arr,u16 psc);//���4��������

void Fun_ZBTG(u8 dir,u32 pulse);    //����������Ƹ���������
void ZBD_Start(u16 arr,u16 psc);   //�����������������
void ZBD_Stop(void);

#endif
