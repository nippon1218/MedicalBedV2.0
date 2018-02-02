#ifndef __FUN_H
#define __FUN_H
#include "sys.h"
#include "usart.h"
#include "common.h"

//���ɺ��� 
void All_Init(void);   //ϵͳ��ʼ��              					
void U2_Wifi_SZ(void); //WIFI����         
void U2_CSSZ(void);    //��λ������������ú���
void U2_JCGN(void);    //�������ܺ���
void U2_GJGN(void);    //�߼����ܺ���
void U2_FW(void);      //��λ����

//�������ܺ���
void Fun_ZB(void);      //֧��
void Fun_SQT(void);     //������
void Fun_XQT(void);     //������
void Fun_ZF(void);      //��
void Fun_YF(void);      //�ҷ�
void Fun_YL(void);      //�칫����һ����
void Fun_YL1(void);			 //�칫����һ����1
void Fun_YL2(void); 			//�칫����һ����2
void Fun_ZBH(void);     //�󱳲�����
void Fun_YBH(void);     //�ұ������� 
void Fun_ZYH(void);     //����������
void Fun_YYH(void);     //����������
void Fun_JRAM(void);    //���ⰴĦ
void Fun_JR(void);      //����
void Fun_Get_Ang(void); //ͨ������2��ȡ��λ���µ�����ֵ

void DeskRunNew(void);

//�������ܺ���
void Fun_HL_ZB(void);    //֧��
void Fun_HL_ZF(void);    //����
void Fun_HL_YF(void);    //�ҷ���
void Fun_HL_BH(void);    //��������
void Fun_HL_YH(void);    //��������
u8   Fun_HL_SD(void);    //һ������

//�Զ�����
void Fun_ZDZBQ(void);      //�Զ�����
void Fun_ZB_XQT(void);     //֧��������ͬʱ����
void Fun_ZBQ(u8 dir);      //��������/�ر�
void Fun_ZBD(u8 dir);      //������ս�
void Fun_CXHG(void);       //��ϴ���
void Fun_SDCX(void);       //�ֶ���ϴ
void Fun_SDHG(void);       //�ֶ����
void Fun_ZDCX(void);       //�Զ���ϴ
void Fun_ZDHG(void);       //�Զ����
u8   Fun_CZ(void);         //����
u8   Fun_CZ1(void);        //����


//ר��ϵͳ
void Fun_ZJ_ZB(void);     //ר��ϵͳ֧��
void Fun_ZJ_ZYF(void);    //ר��ϵͳ����
void Fun_ZJ_SXQT(void);   //ר��ϵͳ����
void Fun_ZJ_ZDZB(void);   //ר��ϵͳ�Զ�����

//���ҿ���ѵ��
//�Զ�
void Fun_ZD_ZZ(int t);    //��֫����ѵ��
void Fun_ZD_YZ(int t);    //��֫����ѵ��
void Fun_ZD_ZYZ(int t);   //����֫����ѵ�� 

//�ֶ�
void Fun_SD_ZXB(void);    //��С��
void Fun_SD_ZDB(void);    //����
void Fun_SD_ZB(void);     //���С��

void Fun_SD_ZXT(void);    //��С��
void Fun_SD_ZDT(void);    //�����
void Fun_SD_ZT(void);     //���С��

void Fun_SD_YXB(void);    //��С��
void Fun_SD_YDB(void);    //�Ҵ��
void Fun_SD_YB(void);     //�Ҵ�С��

void Fun_SD_YXT(void);    //��С��
void Fun_SD_YDT(void);    //�Ҵ���
void Fun_SD_YT(void);     //�Ҵ�С��

void Fun_SD_ZYXB(void);   //����С��
void Fun_SD_ZYDB(void);   //���Ҵ��
void Fun_SD_ZYB(void);    //���Ҵ�С��

void Fun_SD_ZYXT(void);   //����С��
void Fun_SD_ZYDT(void);   //���Ҵ���
void Fun_SD_ZYT(void);    //���Ҵ�С��

//��λ���ܺ���
void Fun_FW_ALL(void);    //���縴λ����
void Fun_FW_ALL_GD(void);    //���縴λ����
void Fun_FW_ZB(void);     //֧����λ
void Fun_FW_QT(void);     //���ȸ�λ
void Fun_FW_YL(void);     //�Ͳ�����һ������λ
void Fun_FW_CF(u8 dir);   //5�ŵ������λ0;����λ1
void Fun_FW_ZF(void);     //����λ
void Fun_FW_YF(void);     //�ҷ���λ

//��������
void Fun_LD(void);        //���ܺ�������
void WriteInU2(char *p);  //���ַ���д�뵽����2��USART2_RX_BUF��
void WriteInU4(char *p);  //���ַ���д������4��

//WIFI���ɹ��ܺ���
void WIFI_JCGN(void);    //�������ܺ���
void WIFI_GJGN(void);    //�߼����ܺ���
void WIFI_FW(void);      //��λ����

void Wifi_Send(u8 *data);              //WiFi���ͺ���
void Wifi_ToPC(u8 *data);              //WiFi���͸�PC����
void WiFi_ToSJ(u8 *data);              //WiFi���͸��ֻ�APP����
void WiFi_ToYKQ(u8 *data);             //WiFi���͸�ң��������
void WiFi_ToHL(u8 *data);              //WiFi���͸���������
void WiFi_ToPC(u8 *data);              //WiFi���͸�PC������

//�����нǶ�ת��Ϊ������
u16 Ang_To_Arr_ZB(u8 angle);           //��֧�����нǶ�ת��Ϊ������
u16 Ang_To_Arr_SXQT(u8 angle);         //���������нǶ�ת��Ϊ������
u16 Ang_To_Arr_ZYFS(u8 angle);         //���������нǶ�ת��Ϊ������
u16 Ang_To_Arr_YL(u8 distance);        //���������нǶ�ת��Ϊ������
u32 Ang_To_Arr_YL2(u8 distance);       //���������нǶ�ת��Ϊ������
void Read_Ang(void);                   //��ȡ��λ�����õĽǶ�ֵ�;���ֵ

//���Ե������
void IO_TEST(void);        //IO�ڲ��Ժ��� 
//�������ܵ��
void Motor1(u8 dir);			//1�ŵ������
void Motor2(u8 dir);			//2�ŵ������
void Motor3(u8 dir);			//3�ŵ������
void Motor4(u8 dir);			//4�ŵ������
void Motor5(u8 dir);			//5�ŵ������
void Motor6(u8 dir);			//6�ŵ������
void Motor7(u8 dir);			//7�ŵ������
//���ҵ��
void TestAll(u8 dir);			//���ҵ�����Ժ�����4������һ������
void Hang1(u8 dir);				//1�ŵ��ҵ�����Ժ���
void Hang2(u8 dir);				//2�ŵ��ҵ�����Ժ���
void Hang3(u8 dir);				//3�ŵ��ҵ�����Ժ���
void Hang4(u8 dir);				//4�ŵ��ҵ�����Ժ���

#endif

