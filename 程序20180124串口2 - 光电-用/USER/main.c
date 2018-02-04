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
	u8 num;        //记录连接的设备数
	u8 len;        //串口接收的字符串长度
	u8 key;        //按键扫描返回值
	All_Init();	   //系统初始化 
	
	//清空串口2、串口WiFi接收寄存器
	UART4_RX_LEN=0;
	USART2_RX_LEN=0;
	
	PCF8574_WriteBit(BEEP_IO,0);	//控制蜂鸣器响
	delay_ms(300);								//延时300ms
	PCF8574_WriteBit(BEEP_IO,1);	//控制蜂鸣器停
	while(1)
	{	
/*****************************************************************************			
		
			             串口部分
			
******************************************************************************/	
		if(USART2_RX_LEN&0x8000)				//判断串口2接收长度最高位是否为1，若为1则表示接收完整的字符串
		{
			len=USART2_RX_LEN&0x3fff;			//获取串口2接收数组字符长度			
			USART2_RX_BUF[len]=0;					//串口2接收数组末尾添0,作为字符串的结束

//			if(strstr((const char *)USART2_RX_BUF,(const char *)"YLS")) 
//			{	
//				DeskRunNew();								//小桌子运行，上行
//			}	
//			if(strstr((const char *)USART2_RX_BUF,(const char *)"YLX")) 
//			{	
//				DeskRunNew();								//小桌子运行，下行
//			}	
			//串口设置模块
			if(strstr((const char *)USART2_RX_BUF,(const char *)"SZ"))   //判断USART2_RX_BUF中是否存在"SZ"
			{			 				
				U2_Wifi_SZ();								//串口设置功能模块
			}
			//上位机界面参数设置模块
			if(strstr((const char *)USART2_RX_BUF,(const char *)"CS"))  
			{			 				
				U2_CSSZ();								 //串口上位机参数设置功能模块
			}
			//基础功能模块
			if(strstr((const char *)USART2_RX_BUF,(const char *)"JC"))    
			{			 
				memcpy(RX_BUF,USART2_RX_BUF,15);				
				U2_JCGN();								//基础功能模块
			}	
			//高级功能模块
			if(strstr((const char *)USART2_RX_BUF,(const char *)"GJ")) 
			{			 
				memcpy(RX_BUF,USART2_RX_BUF,15);
				U2_GJGN();								//高级功能模块
			}
			//复位模块
			if(strstr((const char *)USART2_RX_BUF,(const char *)"FW"))        
			{			 
				memcpy(RX_BUF,USART2_RX_BUF,15);
				U2_FW();								 //复位功能模块
			}				
			memset(USART2_RX_BUF,0,len);   //清除接收
			USART2_RX_LEN=0;               //清除标志位           	
		}	
/***********************************************************************
	         
	             WIFI部分
	
*************************************************************************/					
		if(UART4_RX_LEN&0x8000)					//判断串口4(wifi)接收长度最高位是否为1，若为1则表示接收完整的字符串
		{
			len=UART4_RX_LEN&0x3fff;   		//获取串口4接收数组字符长度	
			UART4_RX_BUF[len]=0;					//串口4接收数组末尾添0,作为字符串的结束 						
			//基础功能模块

			if(strstr((const char *)UART4_RX_BUF,(const char *)"JC")) 
			{	
				memcpy(RX_BUF,UART4_RX_BUF,15);
				WIFI_JCGN();								//基础功能模块
			}
			//高级功能模块
			if(strstr((const char *)UART4_RX_BUF,(const char *)"GJ")) 
			{	
				memcpy(RX_BUF,UART4_RX_BUF,15);
				WIFI_GJGN();								//高级功能模块
			}
			//复位模块
			if(strstr((const char *)UART4_RX_BUF,(const char *)"FW")) 
			{	
				memcpy(RX_BUF,UART4_RX_BUF,15);
				WIFI_FW();						  		//复位功能模块
			}
			//计算当前连接上WiFi的设备数
			if(strstr((const char *)UART4_RX_BUF,(const char *)"CONNECT")) 
			{	
				device_num++;									//wifi连接数目+1
				PCF8574_WriteBit(BEEP_IO,0);  //蜂鸣器开
				delay_ms(200);								//延时200ms
				PCF8574_WriteBit(BEEP_IO,1);  //蜂鸣器关    		
			}
			//设备断开，设备数自动减1
			if(strstr((const char *)UART4_RX_BUF,(const char *)"CLOSED")) 
			{
				device_num--;									//wifi连接数目-1
				PCF8574_WriteBit(BEEP_IO,0);	//蜂鸣器开	     
				delay_ms(200);								//延时200ms
				PCF8574_WriteBit(BEEP_IO,1);  //蜂鸣器关	
			}
			if(strstr((const char *)UART4_RX_BUF,(const char *)"FWGD"))           
			{				
				Fun_FW_ALL_GD();		//复位所有			
			}
			//护栏
			if(strstr((const char *)UART4_RX_BUF,(const char *)"BackGB"))           
			{				
				Fun_HL_ZB();		//支背			
			}	
			if(strstr((const char *)UART4_RX_BUF,(const char *)"BodyLeftGB"))      
			{								
				Fun_HL_ZF();		//左翻身				
			}					
			if(strstr((const char *)UART4_RX_BUF,(const char *)"BodyRightGB"))     
			{
				Fun_HL_YF();		//右翻身			
			}	
			if(strstr((const char *)UART4_RX_BUF,(const char *)"BackNursingGB"))   
			{				
				Fun_HL_BH();		//背部护理			
			}							
			if(strstr((const char *)UART4_RX_BUF,(const char *)"WaistNursingGB"))  
			{				
				Fun_HL_YH();		//腰部护理				
			}					
			if(strstr((const char *)UART4_RX_BUF,(const char *)"WashletAutoGB"))   
			{								
				strcpy((char *)RX_BUF,(const char *)"HLZDZBQ");
				if(1==SD_Flag)
				{
					Fun_ZDZBQ();		//自动坐便	
				}					
			}							
			if(strstr((const char *)UART4_RX_BUF,(const char *)"LockGB"))           
			{				
				Fun_HL_SD();       //键锁
			}	
			if(strstr((const char *)UART4_RX_BUF,(const char *)"ResetGB"))          
			{
				strcpy((char *)RX_BUF,(const char *)"HLFW");
				Fun_FW_ALL();	    //掉电复位			
			}			
			memset(UART4_RX_BUF,0,len);	 //清除接收
			UART4_RX_LEN=0;              //清除标志位				
		 }			 	
	}	
}

