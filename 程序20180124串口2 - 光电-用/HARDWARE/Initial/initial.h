#ifndef __INITIAL_H
#define __INITIAL_H
#include "sys.h"

/***************���ܺ������IO��*********************/

#define DIR1_Down PIout(3)  //֧�������ź���
#define DIR1_Up   PIout(7)  //֧�������ź���
#define DIR2_Down PIout(8)  //�������ź���
#define DIR2_Up   PGout(10) //�������ź���
#define DIR3 PDout(7)       //3�ŵ�������ź���     
#define DIR4 PDout(3)       //4�ŵ�������ź���
#define DIR5 PDout(2)       //5�ŵ�������ź��� 
#define DIR6 PCout(12)      //6�ŵ�������ź��� 
#define DIR6_1 PAout(5)     //6������ս���������ź��� 
#define DIR6_2 PHout(13)    //6������ս�����Ƹ������ź��� 
#define PWM6_2 PCout(4)     //6������ս�����Ƹ�����������  
#define RELAY6 PHout(12)    //����������ս����ͨ�ϵļ̵���
#define DIR7 PAout(6)       //7�ŵ�������ź��� 

/***************���ҵ�������/�����*********************/

#define DG_DIR1 PBout(9)   //1�ŵ��ҵ�������ź��� 
#define DG_DIR2 PBout(8)   //2�ŵ��ҵ�������ź��� 
#define DG_DIR3 PBout(7)   //3�ŵ��ҵ�������ź��� 
#define DG_DIR4 PBout(6)   //4�ŵ��ҵ�������ź���

#define DG_PWM1 PGout(6)   //1�ŵ��ҵ�������ź��� 
#define DG_PWM2 PDout(13)  //2�ŵ��ҵ�������ź���  
#define DG_PWM3 PGout(3)   //3�ŵ��ҵ�������ź��� 
#define DG_PWM4 PHout(11)  //4�ŵ��ҵ�������ź���

/***************���ҵ�������*********************/

#define DG_Relay	PAout(12)		//���Ҽ̵���

/****************ˮ��***********************/

#define DIR_SB      PBout(11)          //ˮ��PB12
#define DIR_QB      PHout(3)           //����
#define DIR_HG      PBout(10)          //���
#define DIR_XZFPQ   PEout(3)           //��ת������
#define DIR_JR      PHout(3)           //����-�̵���
#define DIR_WD      PHout(8)           //�¶ȴ�����
#define Liq_Sensor  PHin(7)            //Һλ������

/************��ϴ����Ƹ�********************/

#define DIR_CXHG      PCout(1)     //��ϴ����Ƹ˷����
#define PWM_CXHG      PBout(13)    //��ϴ������巽���

/***************��翪��********************/

#define GD3_CS     PEin(6)       //3�ŵ����翪��
#define GD3_ZFZZ   PBin(15)      //����ֹ
#define GD3_YFZZ   PBin(14)      //�ҷ���ֹ

#define GD4_CS     PEin(5)       //4�ŵ����翪��
#define GD4_ZFZZ   PEin(4)       //����ֹ
#define GD4_YFZZ   PHin(6)       //�ҷ���ֹ

#define GD5_CS     PEin(2)       //5�ŵ����翪��
#define GD5_ZFZZ   PCin(13)      //����ֹ
#define GD5_YFZZ   PHin(9)   	 //�ҷ���ֹ

#define GD6_CS     PCin(7)       //6�ŵ����翪��
#define GD6_ZZ     PCin(6) 
#define GD7_CS     PCin(8)       //7�ŵ����翪��
#define GD7_ZZ     PCin(9) 

#define GD3S  1
#define GD3LE 2
#define GD3RE 3

#define GD4S  4
#define GD4LE 5
#define GD4RE 6

#define GD5S 7
#define GD5LE 8
#define GD5RE	9

#define GD6S 10
#define GD6E 11

#define GD7S 12
#define GD7E 13

#define GD34S	14
#define GD34LE	15
#define GD34RE	16

//����
extern unsigned long u1,u2,u3;       //�����õ���ʵ������
extern unsigned int k,w,num;
extern u8 cz_time;

//wifi
extern u8 device_num;                //���ڼ��㵱ǰWiFi�����豸��

extern u8 *p;
extern u8 RX_BUF[]; 

//WiFi����-�ȵ�-Ĭ�����ƺ�����
extern u8 wifi_ssid[];	            //�ȵ�����
extern u8 wifi_ssid_password[];	    //�ȵ�����    

//WiFi����-·��-Ĭ��ֵ
extern u8 wifi_station[];			//·��������
extern u8 wifi_station_password[];	//·��������
extern u8 wifi_ap_ip[];             //IP��ַ
extern u16 wifi_ap_port;            //�˿ں�

//WiFi��������
extern u8 wifi_ip_address[];        //ip��ַ
extern u8 wifi_name[];              //WiFi����
extern u8 wifi_password[];          //����

extern const u8 modeap_buf[];       //apģʽд�����飬��ģʽд��AP
extern const u8 modesta_buf[];      //STAģʽд������,��ģʽд��ST


//��λ״̬��־λ1��δ��λ �� 0����λ����ʼ״̬
extern u8 ZB_Flag;         //֧��
extern u8 SQT_Flag;        //������
extern u8 XQT_Flag;        //������
extern u8 ZF_Flag;         //��
extern u8 YF_Flag;         //�ҷ�
extern u8 ZBH_Flag;        //�󱳲�����
extern u8 YBH_Flag;        //�ұ�������
extern u8 ZYH_Flag;        //����������
extern u8 YYH_Flag;        //����������
extern u8 ZBQ_Flag;        //������
extern u8 ZDZBQ_Flag;      //�Զ�������
extern u8 YL_Flag;         //�Ͳ�����һ����
extern u8 JRAM_Flag;       //���ⰴĦ
extern u8 CXHG_Flag;       //��ϴ���
extern u8 SD_Flag;         //һ����������
extern u8 GZ_Flag;         //������ϱ�־λ

//�����־λ
extern u8 ZB_Dir_flag;     //֧�������־λ
extern u8 ZF_Dir_flag;     //�󷭷����־λ
extern u8 YF_Dir_flag;     //�ҷ������־λ
extern u8 ZBH_Dir_flag;    //�󱳲��������־λ
extern u8 YBH_Dir_flag;    //�ұ����������־λ
extern u8 ZYH_Dir_flag;    //�������������־λ
extern u8 YYH_Dir_flag;    //�������������־λ
extern u8 ZDZBQ_Dir_flag;  //�Զ������������־λ
extern u8 JRAM_Dir_flag;   //���ⰴĦ�����־
extern u8 SD_Dir_flag;     //������־
extern u8 XQT_State;       //�Զ�����ʱ��¼�����Ƿ��Ѵ��ڶ���״̬
extern u8 ZB_State;        //�Զ�����ʱ��¼֧���Ƿ��Ѵ��ڶ���״̬
extern u32 WD1_flag;       //�¶ȱ�־
extern u32 WD2_flag;       //�¶ȱ�־

//����״̬��־λ
extern u8 ZBH_Dir_flag;   //�󱳲��������־λ
extern u8 YBH_Dir_flag;   //�ұ����������־λ
extern u8 ZYH_Dir_flag;   //�������������־λ
extern u8 YYH_Dir_flag;   //�������������־λ

extern u8 CX_Flag;        //�ֶ���ϴ��־λ
extern u8 HG_Flag;        //�ֶ���ɱ�־λ

extern u8 XQT_State;      //�Զ�����ʱ��¼�����Ƿ��Ѵ��ڶ���״̬
extern u8 ZB_State;       //�Զ�����ʱ��¼֧���Ƿ��Ѵ��ڶ���״̬
//���ҹ���
extern u8 ZXB_Flag;      //��С��
extern u8 ZXT_Flag;      //��С��
extern u8 YXB_Flag;      //��С��
extern u8 YXT_Flag;      //��С��
extern u8 ZDB_Flag;      //����
extern u8 ZDT_Flag;      //�����
extern u8 YDB_Flag;      //�Ҵ��
extern u8 YDT_Flag;      //�Ҵ���
extern u8 ZDXB_Flag;     //���С��
extern u8 ZDXT_Flag;     //���С��
extern u8 YDXB_Flag;     //�Ҵ�С��
extern u8 YDXT_Flag;     //�Ҵ�С��
extern u8 ZYXB_Flag;     //����С��
extern u8 ZYXT_Flag;     //����С��
extern u8 ZYDB_Flag;     //���Ҵ��
extern u8 ZYDT_Flag;     //���Ҵ���
extern u8 ZYDXB_Flag;    //���Ҵ�С��
extern u8 ZYDXT_Flag;    //���Ҵ�С��

//����ͼƬ
extern u8 ZB_Pic;    //֧��
extern u8 SQT_Pic;   //������
extern u8 XQT_Pic;   //������
extern u8 YL_Pic;    //С����
extern u8 ZBQ_Pic;   //������
extern u8 ZF_Pic;    //����
extern u8 ZCF_Pic;   //��С�෭
extern u8 YF_Pic;    //�ҷ���
extern u8 YCF_Pic;   //��С�෭
extern u8 ZBH_Pic;   //�󱳲�����
extern u8 ZYH_Pic;   //����������
extern u8 YBH_Pic;   //�ұ�������
extern u8 YYH_Pic;   //����������

//����״̬��־λ
//����������-�������
extern u8 ZF3_GZ;       //����
extern u8 ZF4_GZ;       //����
extern u8 ZF5_GZ;       //����
extern u8 YF3_GZ;       //�ҷ���
extern u8 YF4_GZ;       //�ҷ���
extern u8 YF5_GZ;       //�ҷ���
extern u8 ZBQ_GZ;       //�Զ�����
extern u8 YL_GZ;        //�Ͳ�����һ����
extern u8 ZBH_GZ;       //�󱳲�����
extern u8 YBH_GZ;       //�ұ�������
extern u8 ZYH_GZ;       //����������
extern u8 YYH_GZ;       //����������

//����������-���ʧ��
extern u8 ZF_SB;      //����
extern u8 YF_SB;      //�ҷ���
extern u8 ZBQ_SB;     //�Զ�����
extern u8 YL_SB;      //�Ͳ�����һ����
extern u8 ZBH_SB;     //�󱳲�����
extern u8 YBH_SB;     //�ұ�������
extern u8 ZYH_SB;     //����������
extern u8 YYH_SB;     //����������

//����ͼƬ
extern u8 ZB_Pic;        //֧��
extern u8 SQT_Pic;       //������
extern u8 XQT_Pic;       //������
extern u8 YL_Pic;        //С����
extern u8 ZBQ_Pic;       //������
extern u8 ZF_Pic;        //����
extern u8 ZCF_Pic;       //��С�෭
extern u8 YF_Pic;        //�ҷ���
extern u8 YCF_Pic;       //��С�෭


//�����趨�������ü������в���
extern u8  ZB_Lim;           //��λ���趨֧�����нǶ�
extern u8  SQT_Lim;          //��λ���趨���������нǶ�
extern u8  XQT_Lim;          //��λ���趨���������нǶ�
extern u8  ZF_Lim;           //��λ���趨�����нǶ�
extern u8  YF_Lim;           //��λ���趨�ҷ����нǶ�
extern u8  YL_Lim;           //��λ���趨����С�����˶�����
extern u8  CXHG_Time;        //��λ���趨���������ϴ���ʱ��
extern u32 ZBQ_Max;          //�����������£���ʱ����arr����װ��ֵ��-6�ŵ��

//����������ֵ
//�������ܵ��
extern u16 ZB_Runed;             //֧������������Զ���װ��ֵ
extern u16 SQT_Runed;            //�����ȣ���������Զ���װ��ֵ
extern u16 XQT_Runed;            //�����ȣ���������Զ���װ��ֵ
extern u16 ZF_Runed;             //�󷭣���������Զ���װ��ֵ
extern u16 ZBH_Runed;            //�󱳻�����������Զ���װ��ֵ
extern u16 ZYH_Runed;            //����������������Զ���װ��ֵ
extern u16 YF_Runed;             //�ҷ�����������Զ���װ��ֵ
extern u16 YBH_Runed;            //�ұ�������������Զ���װ��ֵ
extern u16 YYH_Runed;            //����������������Զ���װ��ֵ
extern u32 YL_Runed;             //���ӣ���������Զ���װ��ֵ
extern u16 add_arr;              //Ϊ��֤��λ����ʼλ�ã���Ӷ�������ֵ

//���ҿ���ѵ������ֵ����
//��֫
extern u32 ZGB_Runed;        //�����ʼλ��������������   
extern u32 ZGB_Lim;          //��������
extern u32 ZT_Runed;         //�����ʼλ��������������   
extern u32 ZT_Lim;           //��������
//��֫
extern u32 YGB_Runed;        //�����ʼλ��������������  
extern u32 YGB_Lim;          //��������
extern u32 YT_Runed;         //�����ʼλ��������������  
extern u32 YT_Lim;           //��������
//����֫
extern u32 ZYGB_Runed;       //�����ʼλ��������������  
extern u32 ZYGB_Lim;         //��������
extern u32 ZYT_Runed;        //�����ʼλ��������������  
extern u32 ZYT_Lim;          //��������
//��С��/С��
extern u32 ZXB_Runed;        //�����ʼλ��������������  
extern u32 ZXB_Lim;          //��������
extern u32 ZXT_Runed;        //�����ʼλ��������������  
extern u32 ZXT_Lim;          //��������
//����/����
extern u32 ZDB_Lim;          //��������    
extern u32 ZDB_Runed;        //�����ʼλ��������������
extern u32 ZDT_Lim;          //��������    
extern u32 ZDT_Runed;        //�����ʼλ��������������
//��С��/С��
extern u32 YXB_Lim;          //��������     
extern u32 YXB_Runed;        //�����ʼλ��������������
extern u32 YXT_Lim;          //��������     
extern u32 YXT_Runed;        //�����ʼλ��������������
//�Ҵ��/����
extern u32 YDB_Lim;          //��������   
extern u32 YDB_Runed;        //�����ʼλ��������������
extern u32 YDT_Lim;          //��������   
extern u32 YDT_Runed;        //�����ʼλ��������������
//����С��/С��
extern u32 ZYXB_Lim;         //��������     
extern u32 ZYXB_Runed;       //�����ʼλ��������������
extern u32 ZYXT_Lim;         //��������     
extern u32 ZYXT_Runed;       //�����ʼλ��������������
//���Ҵ��/����
extern u32 ZYDB_Lim;         //��������     
extern u32 ZYDB_Runed;       //�����ʼλ��������������
extern u32 ZYDT_Lim;         //��������     
extern u32 ZYDT_Runed;       //�����ʼλ��������������

//��ϴ����Ƹ�
extern u32 CXHG1_Runed;      //�����ʼλ��������������
extern u32 CXHG1_Lim;        //��������
extern u32 CXHG_Runed;       //��ϴ���ǰ�Ƹ������ʼλ��������������  
extern u32 CXHG_Lim;         //��ϴ���ǰ�Ƹ˼�������

//������ս�ǰ�ƶ����Ƹ�
extern u32 ZBDTG_Runed;       //�����ʼλ��������������  
extern u32 ZBDTG_Lim;         //��������
extern u32 ZBD_Lim;           //��������

extern u32 DG_Freq;           //���Ƶ��ҵ�������ٶ�

//��粹��
extern u16 M3GDL_BC;				  //3�ŵ���󷭸�λ����
extern u16 M3GDR_BC;			  	//3�ŵ���ҷ���λ����
extern u16 M4GDL_BC;				  //4�ŵ���󷭸�λ����
extern u16 M4GDR_BC;				  //4�ŵ���ҷ���λ����
extern u16 M5GDL_BC;				  //5�ŵ���󷭸�λ����
extern u16 M5GDR_BC;				  //5�ŵ���ҷ���λ����

#endif


