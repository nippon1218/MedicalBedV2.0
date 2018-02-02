#include "check.h"
#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "pump.h"
#include "function.h"
#include "common.h"
#include "motor.h"
#include "w25qxx.h"
#include "key.h"
#include "pcf8574.h"
#include "initial.h"


/***********************************************************************
 函数名      ：Fun_GZCL(void)  
 函数功能    ：电机故障处理函数，可用于电机故障后，发指令复位各动作
 输入        ：无
 输出        ：1：故障排除后，返回1
                           
************************************************************************/
u8 Fun_GZCL(void)
{
	u8 len;
	Motor_All_Stop();	            //所有电机停止
	u2_printf("Fault_Warning");     //向上位机发出故障报警信号	
	PCF8574_WriteBit(BEEP_IO,0);	//控制蜂鸣器发出报警声
	delay_ms(2000);
	PCF8574_WriteBit(BEEP_IO,1);
	
/*************判断电机过载故障**********************************/	
		
	//左翻身
	if(1==ZF3_GZ)     
	{	
		u2_printf("ZFGZ3");	
	}
	if(1==ZF4_GZ)     
	{	
		u2_printf("ZFGZ4");		
	}
	if(1==ZF5_GZ)     
	{	
		u2_printf("ZFGZ5");		
	}	
	//左背部护理
	if(1==ZBH_GZ)      
	{	
		u2_printf("ZBHGZ");	
	}
	//左腰部护理
	if(1==ZYH_GZ)     
	{	
		u2_printf("ZYHGZ");		
	}	
	//右翻身
	if(1==YF3_GZ)     
	{	
		u2_printf("YFGZ3");		
	}
	if(1==YF4_GZ)     
	{	
		u2_printf("YFGZ4");		
	}
	if(1==YF5_GZ)     
	{	
		u2_printf("YFGZ5");		
	}	
	//右背部护理
	if(1==ZBH_GZ)      
	{	
		u2_printf("YBHGZ");		
	}
	//右腰部护理
	if(1==YYH_GZ)      
	{	
		u2_printf("YYHGZ");		
	}		
	 //自动坐便
	if(1==ZBQ_GZ)   
	{	
		u2_printf("ZBQGZ");	
	}
	//小桌子
	if(1==YL_GZ)            
	{	
		u2_printf("YLGZ");	
	}
    
	memset(USART2_RX_BUF,0,len);   //清除接收
	USART2_RX_LEN=0;               //清除标志位
	memset(UART4_RX_BUF,0,len);    //清除接收
	UART4_RX_LEN=0;
	//可通过指令手动复位动作（不掉电的情况下，故障排除后可返回到原函数）
	while(1)
	{
		if(USART2_RX_LEN&0x8000)
		{
			len=USART2_RX_LEN&0x3fff;				
			USART2_RX_BUF[len]=0;			
			if(strstr((const char *)USART2_RX_BUF,(const char *)"FWZBB"))
			{
				Fun_FW_ZB();     		    //支背复位
			}

			if(strstr((const char *)USART2_RX_BUF,(const char *)"FWQT")) 
			{			
				Fun_FW_QT();   		    //曲腿复位
			}
			if(strstr((const char *)USART2_RX_BUF,(const char *)"FWZBQ"))
			{			
				Fun_ZBQ(1);	            //坐便器复位
			}	
			
			if(strstr((const char *)USART2_RX_BUF,(const char *)"FWZF")) 
			{			
				Fun_FW_ZF();              //左翻身复位					
			}

			if(strstr((const char *)USART2_RX_BUF,(const char *)"FWYF"))
			{			
				Fun_FW_YF();              //右翻身复位	
			}						
			
			if(strstr((const char *)USART2_RX_BUF,(const char *)"FWYL")) 
			{			
				Fun_FW_YL();             //就餐娱乐一体桌复位
			}
			
			if(strstr((const char *)USART2_RX_BUF,(const char *)"FWALL")) 
			{			
				Fun_FW_ALL();            //所有功能一起复位
			}			
		
			if(strstr((const char *)USART2_RX_BUF,(const char *)"WC"))   //故障已排除，返回原函数
			{			
				u2_printf("FaultSolved");				
			
/*********************将标志位重新置为0***********************/
				
				//电机过载标志位			
				ZF3_GZ=0;          //左翻身
				ZF4_GZ=0;          
				ZF5_GZ=0;          
				YF3_GZ=0;          //右翻身
				YF4_GZ=0;         
				YF5_GZ=0; 
				ZBQ_GZ=0;          //自动坐便
				YL_GZ=0;           //就餐娱乐一体桌
				ZBH_GZ=0;          //左背部护理
				YBH_GZ=0;          //右背部护理
				ZYH_GZ=0;          //左腰部护理
				YYH_GZ=0;          //右腰部护理
				
				//电机失步标志位	
				ZF_SB=0;          //左翻身 
				YF_SB=0;          //右翻身
				ZBQ_SB=0;         //自动坐便
				YL_SB=0;          //就餐娱乐一体桌
				ZBH_SB=0;         //左背部护理
				YBH_SB=0;         //右背部护理
				ZYH_SB=0;         //左腰部护理
				YYH_SB=0;         //右腰部护理
				break;
			}
			memset(USART2_RX_BUF,0,len);  //清除接收
			USART2_RX_LEN=0;              //清除标志位 
		}
		if(UART4_RX_LEN&0x8000)
		{
			len=UART4_RX_LEN&0x3fff;				
			UART4_RX_BUF[len]=0;
			if(strstr((const char *)UART4_RX_BUF,(const char *)"FWZBB"))
			{
				Fun_FW_ZB();     		  //支背复位
			}
			if(strstr((const char *)UART4_RX_BUF,(const char *)"FWQT")) 
			{			
				Fun_FW_QT();   		      //曲腿复位
			}
			if(strstr((const char *)UART4_RX_BUF,(const char *)"FWZBQ"))
			{			
				Fun_ZBQ(1);	              //坐便器复位
			}				
			if(strstr((const char *)UART4_RX_BUF,(const char *)"FWZF")) 
			{			
				Fun_FW_ZF();              //左翻身复位					
			}
			if(strstr((const char *)UART4_RX_BUF,(const char *)"FWYF"))
			{			
				Fun_FW_YF();              //右翻身复位	
			}									
			if(strstr((const char *)UART4_RX_BUF,(const char *)"FWYL")) 
			{			
				Fun_FW_YL();             //就餐娱乐一体桌复位
			}			
			if(strstr((const char *)UART4_RX_BUF,(const char *)"FWALL")) 
			{			
				Fun_FW_ALL();            //所有功能一起复位
			}					
			if(strstr((const char *)UART4_RX_BUF,(const char *)"WC"))   //故障已排除，返回原函数
			{			
				u2_printf("FaultSolved");				
			
/*********************将标志位重新置为0***********************/
				
				//电机过载标志位			
				ZF3_GZ=0;          //左翻身
				ZF4_GZ=0;          
				ZF5_GZ=0;          
				YF3_GZ=0;          //右翻身
				YF4_GZ=0;         
				YF5_GZ=0; 
				ZBQ_GZ=0;          //自动坐便
				YL_GZ=0;           //就餐娱乐一体桌
				ZBH_GZ=0;          //左背部护理
				YBH_GZ=0;          //右背部护理
				ZYH_GZ=0;          //左腰部护理
				YYH_GZ=0;          //右腰部护理
				
				//电机失步标志位	
				ZF_SB=0;          //左翻身 
				YF_SB=0;          //右翻身
				ZBQ_SB=0;         //自动坐便
				YL_SB=0;          //就餐娱乐一体桌
				ZBH_SB=0;         //左背部护理
				YBH_SB=0;         //右背部护理
				ZYH_SB=0;         //左腰部护理
				YYH_SB=0;         //右腰部护理
				break;
			}
			memset(UART4_RX_BUF,0,len);  //清除接收
			UART4_RX_LEN=0;              //清除标志位 
		}
	}
	return 1;    
}


/***********************************************************************
 函数名      ：GDCheck(u8 num)
 函数功能    ：光电检测函数
 输入        ：光电序号
 输出        ：1：触发了，0：误触发                      
************************************************************************/
u8 GDCheck(u8 num)
{
	u32 i=0,j=0,n;
	n=285000;
	switch(num)
	{
		case GD3S:
		for(i=0;i<n;i++)
		{
			if(GD3_CS==0)
			{
				j++;
			}
		}
		break;
		case GD3LE:
		for(i=0;i<n;i++)
		{
			if(GD3_ZFZZ==0)
			{
				j++;
			}
		}
		break;
		case GD3RE:
		for(i=0;i<n;i++)
		{
			if(GD3_YFZZ==0)
			{
				j++;
			}
		}
		break;	
		case GD4S:
		for(i=0;i<n;i++)
		{
			if(GD4_CS==0)
			{
				j++;
			}
		}			
		break;
		case GD4LE:
		for(i=0;i<n;i++)
		{
			if(GD4_ZFZZ==0)
			{
				j++;
			}
		}				
		break;
		case GD4RE:
		for(i=0;i<n;i++)
		{
			if(GD4_YFZZ==0)
			{
				j++;
			}
		}	
		break;		
		case GD5S:
		for(i=0;i<n;i++)
		{
			if(GD5_CS==0)
			{
				j++;
			}
		}	
		break;
		case GD5LE:
		for(i=0;i<n;i++)
		{
			if(GD5_ZFZZ==0)
			{
				j++;
			}
		}				
		break;
		case GD5RE:
		for(i=0;i<n;i++)
		{
			if(GD5_YFZZ==0)
			{
				j++;
			}
		}	
		break;	
		case GD6S:
		for(i=0;i<n;i++)
		{
			if(GD6_CS==0)
			{
				j++;
			}
		}
		break;
		case GD6E:
			for(i=0;i<n;i++)
			{
				if(GD6_ZZ==0)
				{
					j++;
				}
			}
			break;
		case GD7S:
			for(i=0;i<n;i++)
			{
				if(GD7_CS==0)
				{
					j++;
				}
			}
			break;
		case GD7E:
			for(i=0;i<n;i++)
			{
				if(GD7_ZZ==0)
				{
					j++;
				}
			}		
			break;
		case GD34S:
			for(i=0;i<n;i++)
			{
				if((GD3_CS==0)||((GD4_CS==0)))
				{
					j++;
				}
			}		
			break;	
		case GD34LE:
			for(i=0;i<n;i++)
			{
				if((GD3_ZFZZ==0)||((GD4_ZFZZ==0)))
				{
					j++;
				}
			}		
			break;
		case GD34RE:
		for(i=0;i<n;i++)
		{
			if((GD3_YFZZ==0)||((GD4_YFZZ==0)))
			{
				j++;
			}
		}		
		break;
		default:
			break;
	}
	if(j<284000)
	{
		j=0;
		return 0;
	}
	else
	{
		j=0;
		return 1;
	}
}
/***********************************************************************
 函数名      ：GDCheckAll()
 函数功能    ：检验所有光电信号
 输入        ：无
 输出        ：无                     
************************************************************************/
void GDCheckAll()
{
	if(GDCheck(GD3S))
	{u2_printf("GD3S\r\n");}
	if(GDCheck(GD3LE))
	{u2_printf("GD3LE\r\n");}
	if(GDCheck(GD3RE))
	{u2_printf("GD3RE\r\n");}
	if(GDCheck(GD4S))
	{u2_printf("GD4S\r\n");}
	if(GDCheck(GD4LE))
	{u2_printf("GD4LE\r\n");}
	if(GDCheck(GD4RE))
	{u2_printf("GD4RE\r\n");}
	if(GDCheck(GD5S))
	{u2_printf("GD5S\r\n");}	
	if(GDCheck(GD5RE))
	{u2_printf("GD5RE\r\n");}	
	if(GDCheck(GD5RE))
	{u2_printf("GD5RE\r\n");}
	if(GDCheck(GD6S))
	{u2_printf("GD6S\r\n");}
	if(GDCheck(GD6E))
	{u2_printf("GD6E\r\n");}	
	if(GDCheck(GD7S))
	{u2_printf("GD7S\r\n");}	
	if(GDCheck(GD7E))
	{u2_printf("GD7E\r\n");}
}

