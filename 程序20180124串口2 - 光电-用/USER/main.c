#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "pwm.h"
#include "nand.h"
#include "key.h"
#include "function.h"
#include "common.h"
#include "pcf8574.h"
#include "ds18b20.h"
#include "check_cmd.h"
#include "motor.h"
#include "pump.h"
#include "hx711.h"
#include "modbus_master.h"
#include "bsp_user_lib.h"
#include "spi.h"
#include "w25qxx.h"
#include "check.h"
#include "initial.h"
#include "string.h"

int main(void)
{
	u8 num;        //��¼���ӵ��豸��
	u8 len;        //���ڽ��յ��ַ�������
	u8 key;        //����ɨ�践��ֵ
	All_Init();	   //ϵͳ��ʼ�� 
	
	//��մ���2������WiFi���ռĴ���
	UART4_RX_LEN=0;
	USART2_RX_LEN=0;
	
	PCF8574_WriteBit(BEEP_IO,0);	//���Ʒ�������
	delay_ms(300);								//��ʱ300ms
	PCF8574_WriteBit(BEEP_IO,1);	//���Ʒ�����ͣ
	while(1)
	{	
/*****************************************************************************			
		
			             ���ڲ���
			
******************************************************************************/	
		if(USART2_RX_LEN&0x8000)				//�жϴ���2���ճ������λ�Ƿ�Ϊ1����Ϊ1���ʾ�����������ַ���
		{
			len=USART2_RX_LEN&0x3fff;			//��ȡ����2���������ַ�����			
			USART2_RX_BUF[len]=0;					//����2��������ĩβ��0,��Ϊ�ַ����Ľ���

//			if(strstr((const char *)USART2_RX_BUF,(const char *)"YLS")) 
//			{	
//				DeskRunNew();								//С�������У�����
//			}	
//			if(strstr((const char *)USART2_RX_BUF,(const char *)"YLX")) 
//			{	
//				DeskRunNew();								//С�������У�����
//			}	
			//��������ģ��
			if(strstr((const char *)USART2_RX_BUF,(const char *)"SZ"))   //�ж�USART2_RX_BUF���Ƿ����"SZ"
			{			 				
				U2_Wifi_SZ();								//�������ù���ģ��
			}
			//��λ�������������ģ��
			if(strstr((const char *)USART2_RX_BUF,(const char *)"CS"))  
			{			 				
				U2_CSSZ();								 //������λ���������ù���ģ��
			}
			//��������ģ��
			if(strstr((const char *)USART2_RX_BUF,(const char *)"JC"))    
			{			 
				memcpy(RX_BUF,USART2_RX_BUF,15);				
				U2_JCGN();								//��������ģ��
			}	
			//�߼�����ģ��
			if(strstr((const char *)USART2_RX_BUF,(const char *)"GJ")) 
			{			 
				memcpy(RX_BUF,USART2_RX_BUF,15);
				U2_GJGN();								//�߼�����ģ��
			}
			//��λģ��
			if(strstr((const char *)USART2_RX_BUF,(const char *)"FW"))        
			{			 
				memcpy(RX_BUF,USART2_RX_BUF,15);
				U2_FW();								 //��λ����ģ��
			}				
			memset(USART2_RX_BUF,0,len);   //�������
			USART2_RX_LEN=0;               //�����־λ           	
		}	
/***********************************************************************
	         
	             WIFI����
	
*************************************************************************/					
		if(UART4_RX_LEN&0x8000)					//�жϴ���4(wifi)���ճ������λ�Ƿ�Ϊ1����Ϊ1���ʾ�����������ַ���
		{
			len=UART4_RX_LEN&0x3fff;   		//��ȡ����4���������ַ�����	
			UART4_RX_BUF[len]=0;					//����4��������ĩβ��0,��Ϊ�ַ����Ľ��� 						
			//��������ģ��

			if(strstr((const char *)UART4_RX_BUF,(const char *)"JC")) 
			{	
				memcpy(RX_BUF,UART4_RX_BUF,15);
				WIFI_JCGN();								//��������ģ��
			}
			//�߼�����ģ��
			if(strstr((const char *)UART4_RX_BUF,(const char *)"GJ")) 
			{	
				memcpy(RX_BUF,UART4_RX_BUF,15);
				WIFI_GJGN();								//�߼�����ģ��
			}
			//��λģ��
			if(strstr((const char *)UART4_RX_BUF,(const char *)"FW")) 
			{	
				memcpy(RX_BUF,UART4_RX_BUF,15);
				WIFI_FW();						  		//��λ����ģ��
			}
			//���㵱ǰ������WiFi���豸��
			if(strstr((const char *)UART4_RX_BUF,(const char *)"CONNECT")) 
			{	
				device_num++;									//wifi������Ŀ+1
				PCF8574_WriteBit(BEEP_IO,0);  //��������
				delay_ms(200);								//��ʱ200ms
				PCF8574_WriteBit(BEEP_IO,1);  //��������    		
			}
			//�豸�Ͽ����豸���Զ���1
			if(strstr((const char *)UART4_RX_BUF,(const char *)"CLOSED")) 
			{
				device_num--;									//wifi������Ŀ-1
				PCF8574_WriteBit(BEEP_IO,0);	//��������	     
				delay_ms(200);								//��ʱ200ms
				PCF8574_WriteBit(BEEP_IO,1);  //��������	
			}
			if(strstr((const char *)UART4_RX_BUF,(const char *)"FWGD"))           
			{				
				Fun_FW_ALL_GD();		//��λ����			
			}
			//����
			if(strstr((const char *)UART4_RX_BUF,(const char *)"BackGB"))           
			{				
				Fun_HL_ZB();		//֧��			
			}	
			if(strstr((const char *)UART4_RX_BUF,(const char *)"BodyLeftGB"))      
			{								
				Fun_HL_ZF();		//����				
			}					
			if(strstr((const char *)UART4_RX_BUF,(const char *)"BodyRightGB"))     
			{
				Fun_HL_YF();		//�ҷ���			
			}	
			if(strstr((const char *)UART4_RX_BUF,(const char *)"BackNursingGB"))   
			{				
				Fun_HL_BH();		//��������			
			}							
			if(strstr((const char *)UART4_RX_BUF,(const char *)"WaistNursingGB"))  
			{				
				Fun_HL_YH();		//��������				
			}					
			if(strstr((const char *)UART4_RX_BUF,(const char *)"WashletAutoGB"))   
			{								
				strcpy((char *)RX_BUF,(const char *)"HLZDZBQ");
				if(1==SD_Flag)
				{
					Fun_ZDZBQ();		//�Զ�����	
				}					
			}							
			if(strstr((const char *)UART4_RX_BUF,(const char *)"LockGB"))           
			{				
				Fun_HL_SD();       //����
			}	
			if(strstr((const char *)UART4_RX_BUF,(const char *)"ResetGB"))          
			{
				strcpy((char *)RX_BUF,(const char *)"HLFW");
				Fun_FW_ALL();	    //���縴λ			
			}			
			memset(UART4_RX_BUF,0,len);	 //�������
			UART4_RX_LEN=0;              //�����־λ				
		 }			 	
	}	
}

