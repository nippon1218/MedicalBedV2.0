#include "timer.h"
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

/*********************************************************************
*函数名       ：All_Init()
*函数功能     ：系统所有参数初始化
*输入         ：无
*输出         ：无
***********************************************************************/
void All_Init(void)
{ 
	HAL_Init();                            //初始化HAL库   
	Stm32_Clock_Init(360,25,2,8);          //设置时钟,180Mhz
	delay_init(180);                       //初始化延时函数
	uart_init(115200);                     //初始化USART
	usart2_init(115200);                   //初始化串口2
	usart3_init(115200);                   //初始化串口3
	uart4_init(115200);	                   //初始化串口4
	LED_Init();                            //初始化LED 	
	SPI5_Init();					       //初始化SPI口
	Motor_Init();                          //初始化电机方向口
	Hang_Init();                           //初始化吊挂电机方向口脉冲口
	CXHG_Init();                           //冲洗烘干电动杆
	Sensor_Init();                         //初始化光电开关
	KEY_Init();                            //初始化按键
	Pump_Init();                           //初始化水箱   
	PCF8574_Init();                        //初始化PCF8574/串口扩展芯片
	NAND_Init();                           //初始化NAND FLASH			
	W25QXX_Init();					       //初始化w25q256/SPI FLASH
//	ESP8266_AP_Init(4);	
}


/*********************************************************************
*函数名       ：WIFI_JCGN()
*函数功能     ：基础功能模块
*输入         ：无
*输出         ：无
***********************************************************************/
void WIFI_JCGN(void)
{
//	if(ESP8266_Get_ID())	//接收到当前设备发送的指令后，立马给其返回一个Received指令	
	//基础功能函数
	if(strstr((const char *)UART4_RX_BUF,(const char *)"ZBS"))             
	{		Fun_ZB();		}	 //支背上	
	   		
	if(strstr((const char *)UART4_RX_BUF,(const char *)"ZBX"))           
	{		Fun_ZB();		}			//支背下		
		
	if(strstr((const char *)UART4_RX_BUF,(const char *)"SQTS"))            
	{
		Fun_SQT();			//上曲腿上		
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"SQTX"))          
	{
		Fun_SQT();			//上曲腿下		
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"XQTX"))        
	{
		Fun_XQT();			//下曲腿下		
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"XQTS"))          
	{
		Fun_XQT();			//下曲腿上		
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"ZFS"))         
	{
		Fun_ZF();			//左翻身上			
	}			
	if(strstr((const char *)UART4_RX_BUF,(const char *)"ZFX"))       
	{
		Fun_ZF();			//左翻身下		
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"YFS"))        
	{
		Fun_YF();			//右翻身上			
	}		
	if(strstr((const char *)UART4_RX_BUF,(const char *)"YFX"))      
	{
		Fun_YF();			//右翻身下			
	}							
	if(strstr((const char *)UART4_RX_BUF,(const char *)"YLS"))             
	{
		Fun_YL1();          //餐饮娱乐一体桌向前
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"YLX"))           
	{
		Fun_YL1();          //餐饮娱乐一体桌后退
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"ZBH"))    
	{
		Fun_ZBH();			//左背部护理		
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"YBH"))   
	{
		Fun_YBH();			//右背部护理		
	}					
	if(strstr((const char *)UART4_RX_BUF,(const char *)"ZYH"))   
	{
		Fun_ZYH();			//左腰部护理			
	}				
	if(strstr((const char *)UART4_RX_BUF,(const char *)"YYH"))  
	{
		Fun_YYH();         //右腰部护理
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"ZDZBQ"))        
	{
		Fun_ZDZBQ();		//自动坐便				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"SDCX"))        
	{
		Fun_SDCX();		   //手动冲洗				
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"SDHG"))        
	{
		Fun_SDHG();		   //手动烘干				
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"LD"))        
	{
		Fun_LD();		   //联动				
	}	
	
	//护栏功能该函数
	if(strstr((const char *)UART4_RX_BUF,(const char *)"HLZB"))           
	{
		Fun_HL_ZB();		//支背			
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"HLZF"))      
	{
		Fun_HL_ZF();		//左翻身				
	}					
	if(strstr((const char *)UART4_RX_BUF,(const char *)"HLYF"))     
	{
		Fun_HL_YF();		//右翻身			
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"HLBH"))   
	{
		Fun_HL_BH();		//背部护理			
	}							
	if(strstr((const char *)UART4_RX_BUF,(const char *)"HLYH"))  
	{
		Fun_HL_YH();		//腰部护理				
	}					
	if(strstr((const char *)UART4_RX_BUF,(const char *)"HLZDZB"))   
	{
		Fun_ZDZBQ();		//自动坐便			
	}							
	if(strstr((const char *)UART4_RX_BUF,(const char *)"HLSD"))           
	{
		Fun_HL_SD();       //键锁
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"HLFW"))          
	{
		Fun_FW_ALL();	    //掉电复位			
	}

//************************调试函数*********************************
		
	if(strstr((const char *)UART4_RX_BUF,(const char *)"Y2L2_1"))   
	{
		WriteInU2("YLS");		//串口2接收数组写入"YLS"
		Fun_YL2();					//小桌子向前	
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"Y2L2_0"))   
	{
		WriteInU2("YLX");		//串口2接收数组写入"YLX"
		Fun_YL2();		   		//小桌子向后
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"U2_Z1D1C1X1"))   
	{
		ZBQ_Flag=1;					//坐便器标志位置1
		Fun_ZDCX();		      //自动冲洗				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"U2_Z1D1H1G1"))   
	{
		ZBQ_Flag=1;					//坐便器标志位置1
		Fun_ZDHG();	        //自动烘干					
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"U2_ZBC1X1H1G1"))        
	{
		ZBQ_Flag=1;					//坐便器标志位置1
		RELAY6=1; 					//推杆继电器得电
		Fun_ZBCXHG(1,CXHG_Lim);   //冲洗烘干推杆伸出
		RELAY6=0; 					//推杆继电器失电
	}		
	if(strstr((const char *)UART4_RX_BUF,(const char *)"U2_ZBC1X1H1G0"))                
	{
		ZBQ_Flag=1;					//坐便器标志位置1
		RELAY6=1; 					//继电器得电
		Fun_ZBCXHG(0,CXHG_Lim);  //冲洗烘干推杆缩回
		RELAY6=0;	      		//继电器失电			
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"U2_Z1B1D0"))              
	{
		ZBQ_Flag=1;					//坐便器标志位置1
		Fun_ZBD(0);	  	    //坐便袋收紧 		
	}			
	if(strstr((const char *)UART4_RX_BUF,(const char *)"U2_Z1B1D1"))            
	{
		ZBQ_Flag=1;					//坐便器标志位置1
		Fun_ZBD(1);	  		  //坐便袋收线电机，用这个收线		
	}
	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"U2_Z1B1T1G1"))          
	{
		ZBQ_Flag=1;					//坐便器标志位置1
		RELAY6=1;           //继电器得电
		Fun_ZBTG(1,ZBDTG_Lim); //收线推杆伸出	
		RELAY6=0;           //继电器失电  
	}		
	if(strstr((const char *)UART4_RX_BUF,(const char *)"U2_Z1B1T1G0"))               
	{
		ZBQ_Flag=1;					//坐便器标志位置1
		RELAY6=1;           //继电器得电
		Fun_ZBTG(0,ZBDTG_Lim); //收线推杆缩回	
		RELAY6=0;           //继电器失电           
	}				
	if(strstr((const char *)UART4_RX_BUF,(const char *)"U2_Z1B1Q1"))           
	{
		u2_printf("坐便器打开");
		Fun_ZBQ(0);	  			//坐便器打开
	}		
	if(strstr((const char *)UART4_RX_BUF,(const char *)"U2_Z1B1Q0"))              
	{
		u2_printf("坐便器关闭");			
		Fun_ZBQ(1);	  	  	//坐便器关闭			
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"C2Z2"))              
	{
		u2_printf("称重");			
		Fun_CZ1();	  			//称重函数运行	
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"DIR_SB1")) 
	{
		RELAY6=1; 		 //继电器得电
		DIR_SB=1;      //水泵打开		
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"DIR_SB0"))  
	{
		RELAY6=0;			 //继电器得电
		DIR_SB=0;      //水泵关闭		
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"DIR_HG1"))       
	{
		RELAY6=1;     //继电器得电
		DIR_QB=1;     //气泵打开	
		DIR_HG=1;     //烘干阀打开	
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"DIR_HG0"))        
	{
		RELAY6=0;	 //继电器得电
		DIR_QB=0;	 //气泵关闭	
		DIR_HG=0;  //烘干阀关闭	
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"testhang1"))             
	{
		DG_Relay=1;	//吊挂继电器得电
		TestAll(1);	//吊挂测试函数起
		DG_Relay=0;	//吊挂继电器失电
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"testhang0"))             
	{
		DG_Relay=1;	//吊挂继电器得电
		TestAll(0);	//吊挂测试函数落
		DG_Relay=0;	//吊挂继电器失电
	}							
	if(strstr((const char *)UART4_RX_BUF,(const char *)"Hang1_1"))              
	{
		DG_Relay=1;	      //吊挂继电器得电	       
		delay_ms(300);		//延时300ms
		u2_printf("XINHAO");
		Hang1(0);	  			//1号吊挂电机起
		DG_Relay=0;	      //吊挂继电器失电
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"Hang1_0"))              
	{
		DG_Relay=1;	      //吊挂继电器得电	
		Hang1(1);	        //吊挂1
		DG_Relay=0;	     	//吊挂继电器失电
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"Hang2_1"))           
	{
		DG_Relay=1;	      //吊挂继电器得电
		Hang2(1);	        //吊挂2
		DG_Relay=0;	      //吊挂继电器失电
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"Hang2_0"))             
	{
		DG_Relay=1;	      //吊挂继电器得电
		Hang2(0);	        //吊挂2
		DG_Relay=0;	    	//吊挂继电器失电
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"Hang3_1"))            
	{
		DG_Relay=1;	      //吊挂继电器得电
		Hang3(0);	        //吊挂3
		DG_Relay=0;	      //吊挂继电器失电
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"Hang3_0"))             
	{
		DG_Relay=1;	      //吊挂继电器得电
		Hang3(1);	        //吊挂3
		DG_Relay=0;	      //吊挂继电器失电
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"Hang4_1"))             
	{
		DG_Relay=1;	     //吊挂继电器得电
		Hang4(1);	       //吊挂4
		DG_Relay=0;	     //吊挂继电器失电
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"Hang4_0"))             
	{
		DG_Relay=1;	      //吊挂继电器得电 
		Hang4(0);         //吊挂4
		DG_Relay=0;	    	//吊挂继电器失电
	}	
	//电机1  
	if(strstr((const char *)UART4_RX_BUF,(const char *)"MOTOR1111"))              
	{
		Motor1(1);	  		//1号电机(电动推杆)运行		
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"MOTOR1110"))              
	{
		Motor1(0);	  		//1号电机(电动推杆)运行		
	} 
	//电机2  
	if(strstr((const char *)UART4_RX_BUF,(const char *)"MOTOR2221"))              
	{
		Motor2(1);	  		//2号电机(电动推杆)运行		
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"MOTOR2220"))             
	{
		Motor2(0);	  		//2号电机(电动推杆)运行		
	} 
	//电机3  
	if(strstr((const char *)UART4_RX_BUF,(const char *)"MOTOR3331"))              
	{
		Motor3(1);	  		//3号电机运行		
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"MOTOR3330"))              
	{
		Motor3(0);	  		//3号电机运行		
	}
	//电机4 
	if(strstr((const char *)UART4_RX_BUF,(const char *)"MOTOR4441"))            
	{
		Motor4(1);	  		//4号电机运行		
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"MOTOR4440"))             
	{
		Motor4(0);	  		//4号电机运行	
	}
	//电机5 		
	if(strstr((const char *)UART4_RX_BUF,(const char *)"MOTOR5551"))             
	{
		Motor5(1);	  		//5号电机运行		
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"MOTOR5550"))             
	{
		Motor5(0);	  		//5号电机运行		
	}
	//电机6 		
	if(strstr((const char *)UART4_RX_BUF,(const char *)"MOTOR6661"))              
	{
		Motor6(1);	  		//6号电机运行		
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"MOTOR6660"))            
	{
		Motor6(0);	  		//6号电机运行		
	}
	//电机7		
	if(strstr((const char *)UART4_RX_BUF,(const char *)"MOTOR7771"))             
	{
		Motor7(1);	  		//7号电机运行		
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"MOTOR7770"))              
	{
		Motor7(0);	  		//7号电机运行		
	}	
}

/*********************************************************************
*函数名       ：WIFI_GJGN()
*函数功能     ：高级功能模块
*输入         ：无
*输出         ：无
***********************************************************************/
void WIFI_GJGN(void)
{
//	if(ESP8266_Get_ID())	//接收到当前设备发送的指令后，立马给其返回一个Received指令	
	//WiFi接收专家系统推理指令					
	if(strstr((const char *)UART4_RX_BUF,(const char *)"ZJZB"))               
	{
		Fun_ZJ_ZB();		  //专家系统支背 				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"ZJZYF"))                
	{
		Fun_ZJ_ZYF();		//专家系统翻身				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"ZJSXQT"))                   
	{
		Fun_ZJ_SXQT();	    //专家系统曲腿					
	}	 
	if(strstr((const char *)UART4_RX_BUF,(const char *)"ZJZDZB"))         
	{
		Fun_ZJ_ZDZB();	    //专家系统自动坐便 					
	}	
			
	if(strstr((const char *)UART4_RX_BUF,(const char *)"JRAM"))   
	{
		Fun_JRAM();		    //肌肉按摩				
	}			
	if(strstr((const char *)UART4_RX_BUF,(const char *)"JR"))                    
	{
		Fun_JR();			//加热		
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"LD"))                         
	{
		Fun_LD();	  		//功能函数联动 		
	}
	//WiFi接收吊挂康复训练指令
	if(strstr((const char *)UART4_RX_BUF,(const char *)"BZZ"))                 
	{
		Fun_ZD_ZZ(1); 	//左胳膊 				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"BYZ"))                
	{
		Fun_ZD_YZ(1);	//右胳膊 				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"BLZ"))            
	{
		Fun_ZD_ZYZ(1);	//左右胳膊				
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"TZZ"))                  
	{
		Fun_ZD_ZZ(1); 	//左腿				
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"TYZ"))               
	{
		Fun_ZD_YZ(1);	//右腿 					
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"TLZ"))            
	{
		Fun_ZD_ZYZ(1);	//左右腿					
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"BZSXS"))                   
	{
		Fun_SD_ZXB();	//左胳膊小臂上 				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"BZSXX"))                  
	{
		Fun_SD_ZXB();	//左胳膊小臂下				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"BZSDS"))                    
	{
		Fun_SD_ZDB();	//左胳膊大臂上				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"BZSDX"))                  
	{
		Fun_SD_ZDB();	//左胳膊大臂下					
	}			
	if(strstr((const char *)UART4_RX_BUF,(const char *)"BZSBS"))               
	{
		Fun_SD_ZB();	//左胳膊大小臂上				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"BZSBX"))             
	{
		Fun_SD_ZB();	//左胳膊大小臂下					
	}			
	//右胳膊			
	if(strstr((const char *)UART4_RX_BUF,(const char *)"BYSXS"))                   
	{
		Fun_SD_YXB();	//右胳膊小臂上				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"BYSXX"))                  
	{
		Fun_SD_YXB();	//右胳膊小臂下				
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"BYSDS"))                    
	{
		Fun_SD_YDB();	//右胳膊大臂上				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"BYSDX"))                  
	{
		Fun_SD_YDB();	//右胳膊大臂下					
	}				
	if(strstr((const char *)UART4_RX_BUF,(const char *)"BYSBS"))              
	{
		Fun_SD_YB();	//右胳膊大小臂上 				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"BYSBX"))             
	{
		Fun_SD_YB();	//右胳膊大小臂下 					
	}		
	//左右胳膊			
	if(strstr((const char *)UART4_RX_BUF,(const char *)"BLSXS"))               
	{
		Fun_SD_ZYXB();	//左右胳膊小臂上				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"BLSXX"))             
	{
		Fun_SD_ZYXB();	//左右胳膊小臂下				
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"BLSDS"))              
	{
		Fun_SD_ZYDB();	//左右胳膊大臂上 				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"BLSDX"))             
	{
		Fun_SD_ZYDB();	//左右胳膊大臂下					
	}				
	if(strstr((const char *)UART4_RX_BUF,(const char *)"BLSBS"))          
	{
		Fun_SD_ZYB();	//左右胳膊大小臂上				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"BLSBX"))         
	{
		Fun_SD_ZYB();	//左右胳膊大小臂下					
	}				
	//左腿			
	if(strstr((const char *)UART4_RX_BUF,(const char *)"TZSXS"))                      
	{
		Fun_SD_ZXT();	//左腿小腿上				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"TZSXX"))                    
	{
		Fun_SD_ZXT();	//左腿小腿下				
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"TZSDS"))                     
	{
		Fun_SD_ZDT();	//左腿大腿上 				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"TZSDX"))                    
	{
		Fun_SD_ZDT();	//左腿大腿下					
	}			
	if(strstr((const char *)UART4_RX_BUF,(const char *)"TZSTS"))                 
	{
		Fun_SD_ZT();	//左腿大小腿上				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"TZSTX"))               
	{
		Fun_SD_ZT();	//左腿大小腿下					
	}			
	//右腿
	if(strstr((const char *)UART4_RX_BUF,(const char *)"TYSXS"))                     
	{
		Fun_SD_YXT();	//右腿小腿上				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"TYSXX"))                   
	{
		Fun_SD_YXT();	//右腿小腿下				
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"TYSDS"))                    
	{
		Fun_SD_YDT();	//右腿大腿上 				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"TYSDX"))                   
	{
		Fun_SD_YDT();	//右腿大腿下					
	}				
	if(strstr((const char *)UART4_RX_BUF,(const char *)"TYSTS"))                
	{
		Fun_SD_YT();	//右腿大小腿上				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"TYSTX"))              
	{
		Fun_SD_YT();	//右腿大小腿下					
	}		
	//左右腿
	if(strstr((const char *)UART4_RX_BUF,(const char *)"TLSXS"))                
	{
		Fun_SD_ZYXT();	//左右腿小腿上				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"TLSXX"))              
	{
		Fun_SD_ZYXT();	//左右腿小腿下				
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"TLSDS"))                
	{
		Fun_SD_ZYDT();	//左右腿大腿上				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"TLSDX"))              
	{
		Fun_SD_ZYDT();	//左右腿大腿下					
	}				
	if(strstr((const char *)UART4_RX_BUF,(const char *)"TLSTS"))           
	{
		Fun_SD_ZYT();	//左右腿大小腿上				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"TLSTX"))         
	{
		Fun_SD_ZYT();	//左右腿大小腿下					
	}                         		
}

/*********************************************************************
*函数名       ：WIFI_FW()
*函数功能     ：复位功能模块
*输入         ：无
*输出         ：无
***********************************************************************/
void WIFI_FW(void)
{
//	if(ESP8266_Get_ID())	//接收到当前设备发送的指令后，立马给其返回一个Received指令	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"FWALL"))	      
	{
		Fun_FW_ALL();       //所有复位	    
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"FWZBB"))	            
	{
		Fun_FW_ZB();     	//支背复位    
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"FWQT"))              
	{			
		Fun_FW_QT();   	   //曲腿复位       
	}				
	if(strstr((const char *)UART4_RX_BUF,(const char *)"FWZBQ"))            
	{			
		ZBQ_Pic=24;
		Fun_ZBQ(1);	       //坐便器复位        
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"FWYL"))               
	{			
		Fun_FW_YL();         //就餐娱乐一体桌复位     
	}				
	if(strstr((const char *)UART4_RX_BUF,(const char *)"FWZF"))          
	{			
		Fun_FW_ZF();        //左翻身复位				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"FWYF"))         
	{			
		Fun_FW_YF();        //右翻身复位	
	}
	//故障已排除，故障处理界面最后一条必按指令 
	if(strstr((const char *)UART4_RX_BUF,(const char *)"WC"))                  
	{
		Wifi_Send("Received");
		Wifi_Send("FaultSolved");
		ZF3_GZ=0;         //左翻身
		ZF4_GZ=0;         //左翻身
		ZF5_GZ=0;         //左翻身
		YF3_GZ=0;         //右翻身
		YF4_GZ=0;         //右翻身
		YF5_GZ=0;         //右翻身
		ZBQ_GZ=0;         //自动坐便
		YL_GZ=0;          //就餐娱乐一体桌
		ZBH_GZ=0;         //左背部护理
		YBH_GZ=0;         //右背部护理
		ZYH_GZ=0;         //左腰部护理
		YYH_GZ=0;         //右腰部护理
		
		//电机失步标志位	
		ZF_SB=0;         //左翻身
		YF_SB=0;         //右翻身
		ZBQ_SB=0;        //自动坐便
		YL_SB=0;         //就餐娱乐一体桌
		ZBH_SB=0;        //左背部护理
		YBH_SB=0;        //右背部护理
		ZYH_SB=0;        //左腰部护理
		YYH_SB=0;        //右腰部护理

	}					
}


/*********************************************************************
*函数名       ：U2_Wifi_SZ()
*函数功能     ：WiFi设置功能模块
*输入         ：无
*输出         ：无
***********************************************************************/
void U2_Wifi_SZ(void)
{	
	//上位机重设WiFi模式
	if(strstr((const char *)USART2_RX_BUF,(const char *)"Mode"))          
	{			 
		//WiFi设置为AP模式
		if(strstr((const char *)USART2_RX_BUF,(const char *)"AP"))        
		{			 
			W25QXX_Write((u8*)modeap_buf,10,2);		//将modeap_buf写入flash
			u2_printf("\r\n设置成AP模式\r\n");
		}
		//WiFi设置为STA模式
		if(strstr((const char *)USART2_RX_BUF,(const char *)"STA"))       
		{			 
			W25QXX_Write((u8*)modesta_buf,10,2);			//将modeap_buf写入flash
			u2_printf("\r\n设置成STA模式\r\n");					
		}					
	}
	//wifi重设-STA模式
	if(strstr((const char *)USART2_RX_BUF,(const char *)"staset"))        
	{ 
		get_wifiname_wifipassword(wifi_station,wifi_station_password);    //获取WiFi名称和密码	
	}		
	//wifi重设-AP模式
	if(strstr((const char *)USART2_RX_BUF,(const char *)"apset"))         
	{ 
		get_apname_wifipassword(wifi_ssid,wifi_ssid_password);            //获取WiFi的名称和密码
	}	
	//wifi重设IP和PORT
	if(strstr((const char *)USART2_RX_BUF,(const char *)"ipportset"))     
	{ 
		get_ip_port(wifi_ap_ip,wifi_ap_port);                             //获取WiFi的ip地址和端口号
	}	
	//wifi重设名称和密码
	if(strstr((const char *)USART2_RX_BUF,(const char *)"wifireset"))     
	{ 
		delay_ms(100);
		get_wifiname_wifipassword(wifi_name,wifi_password);	              //获取WiFi的名称和密码
	}	
	//STA模式初始化
	if(strstr((const char *)USART2_RX_BUF,(const char *)"stastart"))      
	{ 
		ESP8266_apsta_Init(4);		//STA模式初始化函数
	}			
	//ap模式初始化
	if(strstr((const char *)USART2_RX_BUF,(const char *)"apstart"))       
	{ 
		ESP8266_AP_Init(4);			//AP模式初始化函数
	}				
	//获取上位机参数设定值
	if(strstr((const char *)USART2_RX_BUF,(const char *)"newangle"))      
	{ 
		Read_Ang();							//获取上位机参数设定值函数
	}	
}

/*********************************************************************
*函数名       ：U2_CSSZ()
*函数功能     ：上位机界面参数设置功能模块
*输入         ：无
*输出         ：无
***********************************************************************/
void U2_CSSZ(void)
{	
	//上位机重设角度
	if(strstr((const char *)USART2_RX_BUF,(const char *)"AngAll"))  
	{			 
		Fun_Get_Ang();  //获得新的角度值
	}			
	//支背		  		
	if(strstr((const char *)USART2_RX_BUF,(const char *)"AngZB"))   
	{
		p = strstr((const char *)USART2_RX_BUF,(const char *)"AngZB");
		if((usmart_strnum(p+1)!=0) &&(usmart_strnum(p+1)<=90))             //将上位机发送的字符串中的数字转换为十进制
		{
			ZB_Lim=usmart_strnum(p+1);                             //接收上位机设定的角度值																			
//			W25QXX_Write((u8*)ZB_Lim,13,1);                        //保存最新上位机设定角度值
		}
	}
	//左翻身	
	if(strstr((const char *)USART2_RX_BUF,(const char *)"AngZF"))
	{
		p = strstr((const char *)USART2_RX_BUF,(const char *)"AngZF");
		if((usmart_strnum(p+1)!=0)&&(usmart_strnum(p+1)<=60))                //将上位机发送的字符串中的数字转换为十进制
		{				
			ZF_Lim=usmart_strnum(p+1);                          //接收上位机设定的角度值										 								
//			W25QXX_Write((u8*)ZF_Lim,14,1);                     //保存最新上位机设定脉冲值
		}
	}
	//右翻身	
	if(strstr((const char *)USART2_RX_BUF,(const char *)"AngYF"))
	{
		p = strstr((const char *)USART2_RX_BUF,(const char *)"AngYF");
		if((usmart_strnum(p+1)!=0)&&(usmart_strnum(p+1)<=60))                 //将上位机发送的字符串中的数字转换为十进制
		{
			YF_Lim=usmart_strnum(p+1);                          //接收上位机设定的角度值															
//			W25QXX_Write((u8*)YF_Lim,15,1);                 //保存最新上位机设定脉冲值
		}
	}
	//上曲腿		
	if(strstr((const char *)USART2_RX_BUF,(const char *)"AngSQT"))     
	{
		p = strstr((const char *)USART2_RX_BUF,(const char *)"AngSQT");
		if((usmart_strnum(p+1)!=0)&&(usmart_strnum(p+1)<=40))                 //将上位机发送的字符串中的数字转换为十进制
		{
			SQT_Lim=usmart_strnum(p+1);                              //接收上位机设定的角度值													
//			W25QXX_Write((u8*)SQT_Lim,16,1);                     //保存最新上位机设定脉冲值				
		}
	}
	//下曲腿	
	if(strstr((const char *)USART2_RX_BUF,(const char *)"AngXQT"))   
	{
		p = strstr((const char *)USART2_RX_BUF,(const char *)"AngXQT");
		if((usmart_strnum(p+1)!=0)&&(usmart_strnum(p+1)<=90))                 //将上位机发送的字符串中的数字转换为十进制
		{
			XQT_Lim=usmart_strnum(p+1);                            //接收上位机设定的角度值													
//			W25QXX_Write((u8*)XQT_Lim,17,1);	                  //保存最新上位机设定脉冲值
		}
	}
	//餐饮娱乐一体桌	
	if(strstr((const char *)USART2_RX_BUF,(const char *)"AngYL"))      
	{
		p = strstr((const char *)USART2_RX_BUF,(const char *)"AngYL");
		if((usmart_strnum(p+1)!=0) &&(usmart_strnum(p+1)<=100))   //将上位机发送的字符串中的数字转换为十进制
		{
			YL_Lim=usmart_strnum(p+1);                              //接收上位机设定的角度值											
//			W25QXX_Write((u8*)YL_Lim,18,1);		              			//保存最新上位机设定脉冲值
		}
	}							
	//冲洗烘干时间		
	if(strstr((const char *)USART2_RX_BUF,(const char *)"TimeCXHG")) 
	{
		p = strstr((const char *)USART2_RX_BUF,(const char *)"TimeCXHG");
		if((usmart_strnum(p+1)!=0)&&(usmart_strnum(p+1)<=5))  //将上位机发送的字符串中的数字转换为十进制
		{
			CXHG_Time=usmart_strnum(p+1);                 		 //接收上位机设定的冲洗烘干时间														
//			W25QXX_Write((u8*)CXHG_Time,19,1);	       			 //保存最新上位机设定脉冲值	
		}
	}
}

/*********************************************************************
*函数名       ：U2_JCGN()
*函数功能     ：基础功能模块
*输入         ：无
*输出         ：无
***********************************************************************/
void U2_JCGN(void)
{
	if(strstr((const char *)USART2_RX_BUF,(const char *)"ZBS"))            
	{
		Fun_ZB();	    //支背上			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"ZBX"))           
	{
		Fun_ZB();        //支背下
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"SQTS"))            
	{
		Fun_SQT();       //上曲腿上
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"SQTX"))          
	{
		Fun_SQT();		//上曲腿下			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"XQTX"))        
	{
		Fun_XQT();		//下曲腿下			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"XQTS"))          
	{
		Fun_XQT();		//下曲腿上			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"ZFS"))         
	{
		Fun_ZF();		//左翻身上				
	}			
	if(strstr((const char *)USART2_RX_BUF,(const char *)"ZFX"))       
	{
		Fun_ZF();		//左翻身下			
	}	
	if(strstr((const char *)USART2_RX_BUF,(const char *)"YFS"))        
	{
		Fun_YF();		//右翻身上				
	}	
	if(strstr((const char *)USART2_RX_BUF,(const char *)"YFX"))     
	{
		Fun_YF();		//右翻身下				
	}						
	if(strstr((const char *)USART2_RX_BUF,(const char *)"YLS"))            
	{
		Fun_YL1();      //餐饮娱乐一体桌向前
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"YLX"))          
	{
		Fun_YL1();      //餐饮娱乐一体桌后退
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"ZBH"))    
	{
		Fun_ZBH();	  //左背部护理			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"YBH"))   
	{
		Fun_YBH();	  //右背部护理			
	}				
	if(strstr((const char *)USART2_RX_BUF,(const char *)"ZYH"))   
	{
		Fun_ZYH();	  //左腰部护理				
	}				
	if(strstr((const char *)USART2_RX_BUF,(const char *)"YYH"))  
	{
		Fun_YYH();     //右腰部护理
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"ZDZBQ"))        
	{
		Fun_ZDZBQ();  //自动坐便				
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"SDCX"))        
	{
		Fun_SDCX();	  //手动冲洗				
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"SDHG"))        
	{
		Fun_SDHG();	  //手动烘干				
	}	
	if(strstr((const char *)USART2_RX_BUF,(const char *)"JRE"))                   
	{
		Fun_JR();	  //加热			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"LD"))                        
	{
		Fun_LD();	 //功能函数联动 					
	}
	
	//护栏功能函数
	if(strstr((const char *)USART2_RX_BUF,(const char *)"HLZB"))           
	{
		Fun_HL_ZB();		//支背			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"HLZF"))      
	{
		Fun_HL_ZF();		//左翻身				
	}				
	if(strstr((const char *)USART2_RX_BUF,(const char *)"HLYF"))     
	{
		Fun_HL_YF();		//右翻身			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"HLBH"))   
	{
		Fun_HL_BH();		//背部护理			
	}							
	if(strstr((const char *)USART2_RX_BUF,(const char *)"HLYH"))  
	{
		Fun_HL_YH();		//腰部护理				
	}				
	if(strstr((const char *)USART2_RX_BUF,(const char *)"HLZDZB"))   
	{
		Fun_ZDZBQ();		//自动坐便			
	}						
	if(strstr((const char *)USART2_RX_BUF,(const char *)"HLSD"))          
	{
		Fun_HL_SD();       //锁定
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"HLFW"))        
	{
		Fun_FW_ALL();	  //掉电复位				
	}
	
	//************************调试函数*********************************
		
	if(strstr((const char *)USART2_RX_BUF,(const char *)"Y2L2_1"))   
	{
		WriteInU2("YLS");		//串口2接收数组写入"YLS"
		Fun_YL2();					//小桌子向前	
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"Y2L2_0"))   
	{
		WriteInU2("YLX");		//串口2接收数组写入"YLX"
		Fun_YL2();		   		//小桌子向后
	}
	
	if(strstr((const char *)USART2_RX_BUF,(const char *)"U2_Z1D1C1X1"))   
	{
		ZBQ_Flag=1;					//坐便器标志位置1
		Fun_ZDCX();		      //自动冲洗				
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"U2_Z1D1H1G1"))   
	{
		ZBQ_Flag=1;					//坐便器标志位置1
		Fun_ZDHG();	        //自动烘干					
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"U2_ZBC1X1H1G1"))        
	{
		ZBQ_Flag=1;					//坐便器标志位置1
		RELAY6=1; 					//继电器得电
		Fun_ZBCXHG(1,CXHG_Lim);   //冲洗烘干推杆伸出
		RELAY6=0; 	      	//继电器失电	
	}		
	if(strstr((const char *)USART2_RX_BUF,(const char *)"U2_ZBC1X1H1G0"))                
	{
		ZBQ_Flag=1;					//坐便器标志位置1
		RELAY6=1; 					//继电器得电 		
		Fun_ZBCXHG(0,CXHG_Lim); //冲洗烘干推杆缩回
		RELAY6=0;	  	      		//继电器失电	    					
	}

	if(strstr((const char *)USART2_RX_BUF,(const char *)"U2_Z1B1D0"))              
	{
		ZBQ_Flag=1;					//坐便器标志位置1
		Fun_ZBD(0);	  	    //坐便袋收紧 		
	}		
	
	if(strstr((const char *)USART2_RX_BUF,(const char *)"U2_Z1B1D1"))            
	{
		ZBQ_Flag=1;					//坐便器标志位置1
		Fun_ZBD(1);	  		  //坐便袋收线电机，用这个收线		
	}
	
	if(strstr((const char *)USART2_RX_BUF,(const char *)"U2_Z1B1T1G1"))          
	{
		ZBQ_Flag=1;					//坐便器标志位置1
		RELAY6=1;           //继电器得电
		Fun_ZBTG(1,ZBDTG_Lim); //收线推杆伸出	
		RELAY6=0;           //继电器失电	  
	}		
	if(strstr((const char *)USART2_RX_BUF,(const char *)"U2_Z1B1T1G0"))               
	{
		ZBQ_Flag=1;					//坐便器标志位置1
		RELAY6=1;           //继电器得电
		Fun_ZBTG(0,ZBDTG_Lim);//收线推杆缩回	
		RELAY6=0; 	      		//继电器失电          
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"U2CF1"))           
	{
		u2_printf("侧翻开始");
		Fun_FW_CF(1);					//侧翻复位
		u2_printf("侧翻结束");
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"U2CF0"))           
	{
		u2_printf("侧翻开始");
		Fun_FW_CF(0);					//侧翻开始
		u2_printf("侧翻结束");
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"U2_Z1B1Q1"))           
	{
		u2_printf("坐便器打开");
		Fun_ZBQ(0);	  				//坐便器打开
	}		
	if(strstr((const char *)USART2_RX_BUF,(const char *)"U2_Z1B1Q0"))              
	{
		u2_printf("坐便器关闭");			
		Fun_ZBQ(1);	  				//坐便器关闭
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"C2Z2"))              
	{
		u2_printf("称重");			
		Fun_CZ1();	  				//称重函数
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"DIR_SB1")) 
	{
		RELAY6=1;			 //继电器打开
		DIR_SB=1;      //水泵打开	
	}
	
	if(strstr((const char *)USART2_RX_BUF,(const char *)"DIR_SB0"))  
	{
		RELAY6=0;			 //继电器关闭
		DIR_SB=0;      //水泵关闭	
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"DIR_HG1"))       
	{
		RELAY6=1;			 //继电器打开
		DIR_QB=1;      //气泵打开	
		DIR_HG=1;			 //烘干阀打开
	}
	
	if(strstr((const char *)USART2_RX_BUF,(const char *)"DIR_HG0"))        
	{
		RELAY6=0;	 		 //继电器失电	
		DIR_QB=0;			 //气泵关闭	
		DIR_HG=0;			 //烘干阀关闭	
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"testhang1"))             
	{
		DG_Relay=1; 	//继电器得电
		TestAll(1);		//吊挂
		DG_Relay=0;		//继电器失电
	}	

	if(strstr((const char *)USART2_RX_BUF,(const char *)"testhang0"))             
	{
		DG_Relay=1;		//继电器得电
		TestAll(0);
		DG_Relay=0;	  //继电器失电
	}	
						
	if(strstr((const char *)USART2_RX_BUF,(const char *)"Hang1_1"))              
	{
		DG_Relay=1;	  					//继电器得电    
		delay_ms(300);
		u2_printf("XINHAO");    //吊挂1
		Hang1(0);	  	
		DG_Relay=0;						 //继电器失电     
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"Hang1_0"))              
	{
		DG_Relay=1;	  //继电器得电   
		Hang1(1);	    //吊挂1
		DG_Relay=0;		//继电器失电	     
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"Hang2_1"))           
	{
		DG_Relay=1;	  //继电器得电   
		Hang2(1);	    //吊挂2
		DG_Relay=0;		//继电器失电	      
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"Hang2_0"))             
	{
		DG_Relay=1;	  //继电器得电   
		Hang2(0);	    //吊挂2
		DG_Relay=0;	  //继电器失电   
	}

	if(strstr((const char *)USART2_RX_BUF,(const char *)"Hang3_1"))            
	{
		DG_Relay=1;	  //继电器得电     
		Hang3(0);	    //吊挂3
		DG_Relay=0;	  //继电器失电   
	}
	
	if(strstr((const char *)USART2_RX_BUF,(const char *)"Hang3_0"))             
	{
		DG_Relay=1;	   //继电器得电   
		Hang3(1);	     //吊挂3
		DG_Relay=0;	   //继电器失电   
	}

	if(strstr((const char *)USART2_RX_BUF,(const char *)"Hang4_1"))             
	{
		DG_Relay=1;	   //继电器得电   
		Hang4(1);	     //吊挂4
		DG_Relay=0;	   //继电器失电  
	}
	
	if(strstr((const char *)USART2_RX_BUF,(const char *)"Hang4_0"))             
	{
		DG_Relay=1;	  //继电器得电     
		Hang4(0);     //吊挂4
		DG_Relay=0;	  //继电器失电  
	}	
	//电机1  
	if(strstr((const char *)USART2_RX_BUF,(const char *)"MOTOR1111"))              
	{
		Motor1(1);	  //1号电机		
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"MOTOR1110"))              
	{
		Motor1(0);	   //1号电机				
	} 

	//电机2  
	if(strstr((const char *)USART2_RX_BUF,(const char *)"MOTOR2221"))              
	{
		Motor2(1);	  //1号电机 				
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"MOTOR2220"))             
	{
		Motor2(0);	  //1号电机 				
	} 

	//电机3  
	if(strstr((const char *)USART2_RX_BUF,(const char *)"MOTOR3331"))              
	{
		Motor3(1);	   //3号电机				
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"MOTOR3330"))              
	{
		Motor3(0);	   //3号电机				
	}
	//电机4 
	if(strstr((const char *)USART2_RX_BUF,(const char *)"MOTOR4441"))            
	{
		Motor4(1);	   //4号电机				
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"MOTOR4440"))             
	{
		Motor4(0);	   //4号电机				
	}
	//电机5 		
	if(strstr((const char *)USART2_RX_BUF,(const char *)"MOTOR5551"))             
	{
		Motor5(1);	   //5号电机				
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"MOTOR5550"))             
	{
		Motor5(0);	   //5号电机				
	}
	//电机6 		
	if(strstr((const char *)USART2_RX_BUF,(const char *)"MOTOR6661"))              
	{
		Motor6(1);	   //6号电机				
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"MOTOR6660"))            
	{
		Motor6(0);	   //6号电机				
	}
	//电机7		
	if(strstr((const char *)USART2_RX_BUF,(const char *)"MOTOR7771"))             
	{
		Motor7(1);	   //7号电机				
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"MOTOR7770"))              
	{
		Motor7(0);	   //7号电机				
	}	
}

/*********************************************************************
*函数名       ：U2_GJGN()
*函数功能     ：高级功能模块
*输入         ：无
*输出         ：无
***********************************************************************/
void U2_GJGN(void)
{
	if(strstr((const char *)USART2_RX_BUF,(const char *)"JRAM"))     
	{
		Fun_JRAM();		    //肌肉按摩			
	}
	//专家系统						
	if(strstr((const char *)USART2_RX_BUF,(const char *)"ZJZB"))              
	{
		Fun_ZJ_ZB();		//专家系统支背				
	}	
	if(strstr((const char *)USART2_RX_BUF,(const char *)"ZJZYF"))               
	{
		Fun_ZJ_ZYF();		//专家系统翻身				
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"ZJSXQT"))                 
	{
		Fun_ZJ_SXQT();		//专家系统曲腿 				
	}	
	if(strstr((const char *)USART2_RX_BUF,(const char *)"ZJZDZB"))          
	{
		Fun_ZJ_ZDZB();		//专家系统自动坐便				
	}	
	//吊挂康复训练
	//自动模式										
	if(strstr((const char *)USART2_RX_BUF,(const char *)"BZZ"))                
	{
		Fun_ZD_ZZ(1); 		//左胳膊			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"BYZ"))               
	{
		Fun_ZD_YZ(1);		//右胳膊			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"BLZ"))          
	{
		Fun_ZD_ZYZ(1);		//左右胳膊			
	}	
	if(strstr((const char *)USART2_RX_BUF,(const char *)"TZZ"))                
	{
		Fun_ZD_ZZ(1); 		//左腿			
	}	
	if(strstr((const char *)USART2_RX_BUF,(const char *)"TYZ"))              
	{
		Fun_ZD_YZ(1);		//右腿				
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"TLZ"))          
	{
		Fun_ZD_ZYZ(1);		//左右腿				
	}
											
	//吊挂训练手动模式								
	if(strstr((const char *)USART2_RX_BUF,(const char *)"BZSXS"))              
	{
		Fun_SD_ZXB();	   //左胳膊小臂上			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"BZSXX"))            
	{
		Fun_SD_ZXB();	  //左胳膊小臂下			
	}	
	if(strstr((const char *)USART2_RX_BUF,(const char *)"BZSDS"))              
	{
		Fun_SD_ZDB();	  //左胳膊大臂上			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"BZSDX"))            
	{
		Fun_SD_ZDB();	  //左胳膊大臂下				
	}				
	if(strstr((const char *)USART2_RX_BUF,(const char *)"BZSBS"))          
	{
		Fun_SD_ZB();	  //左胳膊大小臂上			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"BZSBX"))        
	{
		Fun_SD_ZB();	  //左胳膊大小臂下				
	}					
	if(strstr((const char *)USART2_RX_BUF,(const char *)"BYSXS"))             
	{
		Fun_SD_YXB();	  //右胳膊小臂上			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"BYSXX"))           
	{
		Fun_SD_YXB();	  //右胳膊小臂下			
	}	
	if(strstr((const char *)USART2_RX_BUF,(const char *)"BYSDS"))             
	{
		Fun_SD_YDB();		//右胳膊大臂上			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"BYSDX"))           
	{
		Fun_SD_YDB();		//右胳膊大臂下				
	}				
	if(strstr((const char *)USART2_RX_BUF,(const char *)"BYSBS"))         
	{
		Fun_SD_YB();		//右胳膊大小臂上			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"BYSBX"))        
	{
		Fun_SD_YB();		//右胳膊大小臂下				
	}			
	if(strstr((const char *)USART2_RX_BUF,(const char *)"BLSXS"))          
	{
		Fun_SD_ZYXB();		//左右胳膊小臂上			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"BLSXX"))        
	{
		Fun_SD_ZYXB();		//左右胳膊小臂下			
	}	
	if(strstr((const char *)USART2_RX_BUF,(const char *)"BLSDS"))          
	{
		Fun_SD_ZYDB();		//左右胳膊大臂上			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"BLSDX"))        
	{
		Fun_SD_ZYDB();		//左右胳膊大臂下				
	}				
	if(strstr((const char *)USART2_RX_BUF,(const char *)"BLSBS"))        
	{
		Fun_SD_ZYB();	//左右胳膊大小臂上				
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"BLSBX"))        
	{
		Fun_SD_ZYB();	//左右胳膊大小臂下					
	}						
	if(strstr((const char *)USART2_RX_BUF,(const char *)"TZSXS"))                   
	{
		Fun_SD_ZXT();		//左腿小腿上			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"TZSXX"))                 
	{
		Fun_SD_ZXT();		//左腿小腿下			
	}	
	if(strstr((const char *)USART2_RX_BUF,(const char *)"TZSDS"))                   
	{
		Fun_SD_ZDT();		//左腿大腿上			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"TZSDX"))                 
	{
		Fun_SD_ZDT();		//左腿大腿下				
	}				
	if(strstr((const char *)USART2_RX_BUF,(const char *)"TZSTS"))               
	{
		Fun_SD_ZT();		//左腿大小腿上			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"TZSTX"))             
	{
		Fun_SD_ZT();		//左腿大小腿下				
	}			
	if(strstr((const char *)USART2_RX_BUF,(const char *)"TYSXS"))                  
	{
		Fun_SD_YXT();		//右腿小腿上			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"TYSXX"))                
	{
		Fun_SD_YXT();		//右腿小腿下			
	}	
	if(strstr((const char *)USART2_RX_BUF,(const char *)"TYSDS"))                  
	{
		Fun_SD_YDT();		//右腿大腿上			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"TYSDX"))                
	{
		Fun_SD_YDT();		//右腿大腿下				
	}				
	if(strstr((const char *)USART2_RX_BUF,(const char *)"TYSTS"))              
	{
		Fun_SD_YT();		//右腿大小腿上			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"TYSTX"))           
	{ 
		Fun_SD_YT();		//右腿大小腿下				
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"TLSXS"))            
	{
		Fun_SD_ZYXT();		//左右腿小腿上			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"TLSXX"))          
	{
		Fun_SD_ZYXT();		//左右腿小腿下			
	}	
	if(strstr((const char *)USART2_RX_BUF,(const char *)"TLSDS"))            
	{
		Fun_SD_ZYDT();		//左右腿大腿上			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"TLSDX"))          
	{
		Fun_SD_ZYDT();		//左右腿大腿下				
	}				
	if(strstr((const char *)USART2_RX_BUF,(const char *)"TLSTS"))         
	{
		Fun_SD_ZYT();	//左右腿大小腿上				
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"TLSTX"))        
	{
		Fun_SD_ZYT();	//左右腿大小腿下					
	}	                         	
}
/*********************************************************************
*函数名       ：U2_FW()
*函数功能     ：复位功能模块
*输入         ：无
*输出         ：无
***********************************************************************/
void U2_FW(void)
{						
	if(strstr((const char *)USART2_RX_BUF,(const char *)"FWALL"))	      
	{
		Fun_FW_ALL();     //所有复位	    
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"FWZBB"))	      
	{
		Fun_FW_ZB();     //支背复位	    
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"FWQT"))         
	{			
		Fun_FW_QT();   	//曲腿复位	       
	}					
	if(strstr((const char *)USART2_RX_BUF,(const char *)"FWZBQ"))     
	{
		ZBQ_Pic=24;
		Fun_ZBQ(1);	        //坐便器复位      
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"FWYL"))        
	{			
		Fun_FW_YL();        //就餐娱乐一体桌复位      
	}					
	if(strstr((const char *)USART2_RX_BUF,(const char *)"FWZF"))    
	{			
		Fun_FW_ZF();       	//左翻身复位				
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"FWYF"))   	
	{			
		Fun_FW_YF();        //右翻身复位
	}
	//故障已排除，故障处理界面最后一条必按指令
	if(strstr((const char *)USART2_RX_BUF,(const char *)"WC"))           
	{
		u2_printf("Received");
		u2_printf("WC");
		
/*********************将标志位重新置为0***********************/
		
		//电机过载标志位			
		ZF3_GZ=0;         //左翻身
		ZF4_GZ=0;         //左翻身
		ZF5_GZ=0;         //左翻身
		YF3_GZ=0;         //右翻身
		YF4_GZ=0;         //右翻身
		YF5_GZ=0;         //右翻身
		ZBQ_GZ=0;         //自动坐便
		YL_GZ=0;          //就餐娱乐一体桌
		ZBH_GZ=0;         //左背部护理
		YBH_GZ=0;         //右背部护理
		ZYH_GZ=0;         //左腰部护理
		YYH_GZ=0;         //右腰部护理
		
		//电机失步标志位	
		ZF_SB=0;         //左翻身
		YF_SB=0;         //右翻身
		ZBQ_SB=0;        //自动坐便
		YL_SB=0;         //就餐娱乐一体桌
		ZBH_SB=0;        //左背部护理
		YBH_SB=0;        //右背部护理
		ZYH_SB=0;        //左腰部护理
		YYH_SB=0;        //右腰部护理
	}					
}


/***********************************************************************
 函数名      ：IO_TEST(void)   
 函数功能    ：控制板IO口测试
 输入        ：无
 输出        ：无  
                          
************************************************************************/
void IO_TEST(void)
{
	GPIO_InitTypeDef GPIO_Initure;          //定义结构体变量GPIO_Initure
    __HAL_RCC_GPIOA_CLK_ENABLE();           //使能GPIOA时钟 
	__HAL_RCC_GPIOB_CLK_ENABLE();           //使能GPIOA时钟 
    __HAL_RCC_GPIOC_CLK_ENABLE();           //开启GPIOC时钟
	__HAL_RCC_GPIOD_CLK_ENABLE();           //开启GPIOC时钟
    __HAL_RCC_GPIOE_CLK_ENABLE();           //开启GPIOE时钟
    __HAL_RCC_GPIOH_CLK_ENABLE();           //开启GPIOH时钟
    __HAL_RCC_GPIOG_CLK_ENABLE();           //开启GPIOG时钟
    __HAL_RCC_GPIOI_CLK_ENABLE();           //开启GPIOI时钟
		
    GPIO_Initure.Pin=GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_11|GPIO_PIN_12;            //PA0
    GPIO_Initure.Mode=GPIO_MODE_INPUT;      //输入
    GPIO_Initure.Pull=GPIO_PULLUP;          //下拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);	

    GPIO_Initure.Pin=GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;            //PA12
    GPIO_Initure.Mode=GPIO_MODE_INPUT;       //输入
    GPIO_Initure.Pull=GPIO_PULLUP;           //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;      //高速
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);		
	
    GPIO_Initure.Pin=GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_12|GPIO_PIN_13; 
	GPIO_Initure.Mode=GPIO_MODE_INPUT;      //输入
    GPIO_Initure.Pull=GPIO_PULLUP; 
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
    HAL_GPIO_Init(GPIOC,&GPIO_Initure);	

    GPIO_Initure.Pin=GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_7|GPIO_PIN_13; 
	GPIO_Initure.Mode=GPIO_MODE_INPUT;      //输入
    GPIO_Initure.Pull=GPIO_PULLUP; 
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
    HAL_GPIO_Init(GPIOD,&GPIO_Initure);	

    GPIO_Initure.Pin=GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6; 
	GPIO_Initure.Mode=GPIO_MODE_INPUT;      //输入
    GPIO_Initure.Pull=GPIO_PULLUP; 
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
    HAL_GPIO_Init(GPIOE,&GPIO_Initure);	

    GPIO_Initure.Pin=GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
	GPIO_Initure.Mode=GPIO_MODE_INPUT;      //输入
    GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
    HAL_GPIO_Init(GPIOH,&GPIO_Initure);	

    GPIO_Initure.Pin=GPIO_PIN_3|GPIO_PIN_6|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14;
	GPIO_Initure.Mode=GPIO_MODE_INPUT;      //输入
    GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
    HAL_GPIO_Init(GPIOG,&GPIO_Initure);	

    GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8; //PI4
	GPIO_Initure.Mode=GPIO_MODE_INPUT;      //输入
    GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
    HAL_GPIO_Init(GPIOI,&GPIO_Initure);		
}

/***********************************************************************
 函数名      ：WriteInU4(void)  
 函数功能    ：串口4写入函数
 输入        ：要写入UART4_RX_BUF的字符串""
 输出        ：无                           
************************************************************************/
void WriteInU4(char *p)
{
	u8 len=strlen(p);			  //获取字符串长度
	u8 i;
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);	//清除串口4接收函数
	for(i=0;i<len;i++)
	{
	  UART4_RX_BUF[i]=p[i];	//向串口4复制数据
	}	
}
/***********************************************************************
 函数名      ：Ang_To_Arr_ZB  
 函数功能    ：将角度值转换成自动重装载值
 输入        ：角度，u8类型
 输出        ：TIM3自动重装载值，u16类型                           
************************************************************************/
u16 Ang_To_Arr_ZB(u8 angle)   //支背
{
	u16 res;
	res=600*angle;//600
	return res;
}

u16 Ang_To_Arr_SXQT(u8 angle)   //曲腿
{
	u16 res;
	res=380*angle;//400
	return res;
}

u16 Ang_To_Arr_ZYFS(u8 angle)  //翻身
{
	u16 res;
	res=300*angle;//280
	return res;
}

u16 Ang_To_Arr_YL(u8 distance)   //桌子
{
	u16 res;
	res=655*distance;//600
	return res;
}
u32 Ang_To_Arr_YL2(u8 distance)   //桌子
{
	u16 res;
	res=8000*distance;//600
	return res;
}
/***********************************************************************
 函数名      ：Fun_Get_Ang
 函数功能    ：通过串口2获得新的角度值
 输入        ：无
 输出        ：无 
 扫描数组     ：USART2_RX_BUF，即串口2
 其他说明        ：将“+”与“+”字符之间的数据提取出来，并存入全局的角度变量
 举例        ：AngAll+80+40+90+45+45+100+
               支背角度（ZB_Lim）=80，上曲腿角度（SQT_Lim）=40，下曲腿角度（XQT_Lim）=90；
               左翻角度（ZF_Lim）=45，右翻角度（YF_Lim）=45，小桌子移动距离（YL_Lim）=100；
************************************************************************/
void Fun_Get_Ang(void)
{
	u8 ip1[10],ip2[10],ip3[10],ip4[10],ip5[10],ip6[10],ip7[10];
	u8 	ZB_Buf[1];
	u8  SQT_Buf[1];
	u8  XQT_Buf[1];
	u8  ZF_Buf[1];
	u8  YF_Buf[1];
	u8  YL_Buf[1];
	u8  CXHG_Buf[1];
	
	char *presult1,*presult2,*presult3,*presult4,*presult5,*presult6,*presult7,*presult8;
	
	presult1 = strstr( (const char *)USART2_RX_BUF ,(const char *)"+");	//获取字符串中第1个"+"的地址
	presult2 = strstr( (const char *)presult1+1 , (const char *)"+");		//获取字符串中第2个"+"的地址
	presult3 = strstr( (const char *)presult2+1 , (const char *)"+");		//获取字符串中第3个"+"的地址		
	presult4 = strstr( (const char *)presult3+1 , (const char *)"+");		//获取字符串中第4个"+"的地址			
	presult5 = strstr( (const char *)presult4+1 , (const char *)"+");		//获取字符串中第5个"+"的地址		
 	presult6 = strstr( (const char *)presult5+1 , (const char *)"+");		//获取字符串中第6个"+"的地址
	presult7 = strstr( (const char *)presult6+1 , (const char *)"+");		//获取字符串中第7个"+"的地址
	presult8 = strstr( (const char *)presult7+1 , (const char *)"+");		//获取字符串中第8个"+"的地址
	memcpy(ip1,presult1+1,presult2-presult1-1);   //将presult1+1到presult2-presult1-1之间的数据复制到ip1数组中
	memcpy(ip2,presult2+1,presult3-presult2-1);  	//将presult2+1到presult3-presult2-1之间的数据复制到ip1数组中
	memcpy(ip3,presult3+1,presult4-presult3-1);  	//将presult3+1到presult4-presult3-1之间的数据复制到ip1数组中	
	memcpy(ip4,presult4+1,presult5-presult4-1);  	//将presult4+1到presult5-presult4-1之间的数据复制到ip1数组中		
	memcpy(ip5,presult5+1,presult6-presult5-1);  	//将presult5+1到presult6-presult5-1之间的数据复制到ip1数组中	
	memcpy(ip6,presult6+1,presult7-presult6-1);  	//将presult6+1到presult7-presult6-1之间的数据复制到ip1数组中
	memcpy(ip7,presult7+1,presult8-presult7-1);  	//将presult7+1到presult8-presult7-1之间的数据复制到ip1数组中
	
	//将ip1数组中的数字型字符串转换成数字
	ZB_Buf[0]=usmart_strnum(ip1);       //支背  
	SQT_Buf[0]=usmart_strnum(ip2);      //上曲腿
	XQT_Buf[0]=usmart_strnum(ip3);      //下曲腿
	ZF_Buf[0]=usmart_strnum(ip4);       //左翻
	YF_Buf[0]=usmart_strnum(ip5);       //右翻
	YL_Buf[0]=usmart_strnum(ip6);       //桌子移动距离
	CXHG_Buf[0]=usmart_strnum(ip7);     //冲洗烘干时间	

	if(ZB_Buf[0]<=90)             //支背
	{	ZB_Lim=ZB_Buf[0];	}
	
	if(SQT_Buf[0]<=40)  	     //上曲腿
	{	SQT_Lim=SQT_Buf[0]; 	} 
	
	if(XQT_Buf[0]<=90)	      //下曲腿
	{	XQT_Lim=XQT_Buf[0]; 	}

	if(ZF_Buf[0]<=90)	       //左翻
	{	ZF_Lim=ZF_Buf[0];	}  
	
	if(ZF_Buf[0]<=90)	       //右翻	
	{	YF_Lim=YF_Buf[0]; 	} 

	if(YL_Buf[0]<=100)          //桌子移动距离   
	{	YL_Lim=YL_Buf[0];		}

	if(CXHG_Buf[0]<=5)             //冲洗烘干时间  
	{	CXHG_Time=CXHG_Buf[0];		}
 	

//	//保存最新上位机设定脉冲值
//	W25QXX_Write((u8*)ZB_Buf,13,1);         //从第13地址开始，写入1个字节
//	W25QXX_Write((u8*)SQT_Buf,14,1);		//从第14地址开始，写入1个字节
//	W25QXX_Write((u8*)XQT_Buf,15,1);		//从第15地址开始，写入1个字节
//	W25QXX_Write((u8*)ZF_Buf,16,1);	        //从第16地址开始，写入1个字节
//	W25QXX_Write((u8*)YF_Buf,17,1);	        //从第17地址开始，写入1个字节
//	W25QXX_Write((u8*)YL_Buf,18,1);		    //从第18地址开始，写入1个字节
//	W25QXX_Write((u8*)CXHG_Buf,19,1);		//从第19地址开始，写入1个字节	
}

/***********************************************************************
 函数名      ：Read_Ang  
 函数功能    ：读取flash保存的上位机设定角度值
 输入        ：角度，u8类型
 输出        ：TIM3自动重装载值，u16类型                        
************************************************************************/
void Read_Ang(void)
{
	u8 	ZB_Buf[1];
	u8  SQT_Buf[1];
	u8  XQT_Buf[1];
	u8  ZF_Buf[1];
	u8  YF_Buf[1];
	u8  YL_Buf[1];
	u8  CXHG_Buf[1];
	
	//将保存的数据从flash中读出来
	W25QXX_Read((u8*)ZB_Buf,13,1);    //从第13地址开始，读取1个字节
	W25QXX_Read((u8*)SQT_Buf,14,1);	  //从第14地址开始，读取1个字节
	W25QXX_Read((u8*)XQT_Buf,15,1);	  //从第15地址开始，读取1个字节
	W25QXX_Read((u8*)ZF_Buf,16,1);	  //从第16地址开始，读取1个字节
	W25QXX_Read((u8*)YF_Buf,17,1);    //从第17地址开始，读取1个字节
	W25QXX_Read((u8*)YL_Buf,18,1);	  //从第18地址开始，读取1个字节
	W25QXX_Read((u8*)CXHG_Buf,19,1);  //从第19地址开始，读取1个字节

	ZB_Lim=ZB_Buf[0];     //支背  
	SQT_Lim=SQT_Buf[0];   //上曲腿
	XQT_Lim=XQT_Buf[0];   //下曲腿
	ZF_Lim=ZF_Buf[0];     //左翻
	YF_Lim=YF_Buf[0];     //右翻
	YL_Lim=YL_Buf[0];     //桌子移动距离
	CXHG_Time=CXHG_Buf[0];//坐便冲洗烘干时间	
}

/***********************************************************************
 函数名      ：Wifi_Send  
 函数功能    ：WiFi发送函数
 输入        ：要发送的数据或指令
 输出        ：无                       
************************************************************************/
void Wifi_Send(u8 *data)
{
	u16 i;
	u8 n;	
	i=strlen((const char*)data);                    //获取数据长度	
	if(device_num>0)
	{
		u4_printf("AT+CIPSEND=%d,%d\r\n",0,i);      //发送AT+CIPSEND指令
		delay_ms(4);                         
		memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);	//清除串口4接收缓存区	
		UART4_RX_LEN=0; 			//清除串口4状态标志位                             
		u4_printf("%s",data);                       //发送数据字符数据data
		delay_ms(200);								//延时200ms，芯片必须要求这个时间
		memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);	//清除串口4接收缓存区	
		UART4_RX_LEN=0;  			//串口4状态清零
	}
}

/***********************************************************************
 函数名      ：Wifi_ToPC  
 函数功能    ：WiFi向PC发送函数
 输入        ：要发送的数据或指令
 输出        ：无                      
************************************************************************/
void Wifi_ToPC(u8 *data)
{
	u16 i;
	u8 n;	
	if(PC_Ready==1)
	{
		i=strlen((const char*)data);                //获取数据长度	
		u4_printf("AT+CIPSEND=%d,%d\r\n",PC,i);     //发送AT+CIPSEND指令
		delay_ms(4);
		memset(UART4_RX_BUF,0,20);	//清除串口4接收缓存区	
		UART4_RX_LEN=0;             //串口4状态清零                
		u4_printf("%s",data);       //发送数据字符数据data
		delay_ms(200);				//延时200ms，芯片必须要求这个时间
		memset(UART4_RX_BUF,0,20);	//清除串口4接收缓存区	
		UART4_RX_LEN=0;				  		//串口4状态清零  		
	}
}

/***********************************************************************
 函数名      ：WiFi_ToSJ  
 函数功能    ：WiFi向手机发送函数
 输入        ：要发送的数据或指令
 输出        ：无
************************************************************************/
void WiFi_ToSJ(u8 *data)
{
	u16 i;
	u8 n;	
	if(SJ_Ready==1)
	{
		i=strlen((const char*)data);             //获取数据长度	
		u4_printf("AT+CIPSEND=%d,%d\r\n",SJ,i);  //发送AT+CIPSEND指令
		delay_ms(4);
		memset(UART4_RX_BUF,0,20);	//清除串口4接收缓存区	
		UART4_RX_LEN=0;           	//串口4状态清零                    
		u4_printf("%s",data);       //发送数据字符数据data
		delay_ms(200);				//延时200ms，芯片必须要求这个时间
		memset(UART4_RX_BUF,0,20);	//清除串口4接收缓存区	
		UART4_RX_LEN=0;  						  //串口4状态清零
	}
}


/***********************************************************************
 函数名      ：WiFi_ToYKQ  
 函数功能    ：WiFi向遥控器发送函数
 输入        ：要发送的数据或指令
 输出        ：无
************************************************************************/
void WiFi_ToYKQ(u8 *data)
{
	u16 i;
	u8 n;	
	if(YKQ_Ready==1)
	{
		i=strlen((const char*)data);                 //获取数据长度	
		u4_printf("AT+CIPSEND=%d,%d\r\n",YKQ,i);     //发送AT+CIPSEND指令
		delay_ms(4);
		memset(UART4_RX_BUF,0,20);	//清除串口4接收缓存区	
		UART4_RX_LEN=0;             //串口4状态清零                  
		u4_printf("%s",data);       //发送数据字符数据data
		delay_ms(200);				//延时200ms，芯片必须要求这个时间
		memset(UART4_RX_BUF,0,20);	//清除串口4接收缓存区	
		UART4_RX_LEN=0;							//串口4状态清零 		
	}
}
/***********************************************************************
 函数名      ：WiFi_ToHL  
 函数功能    ：WiFi向护栏发送函数
 输入        ：要发送的数据或指令
 输出        ：无
************************************************************************/
void WiFi_ToHL(u8 *data)
{
	u16 i;
	u8 n;	
	if(HL_Ready==1)
	{
		i=strlen((const char*)data);                //获取数据长度	
		u4_printf("AT+CIPSEND=%d,%d\r\n",HL,i);     //发送AT+CIPSEND指令
		delay_ms(4);
		memset(UART4_RX_BUF,0,20);	 //清除串口4接收缓存区	
		UART4_RX_LEN=0;             //串口4状态清零                  
		u4_printf("%s",data);        //发送数据字符数据data
		delay_ms(200);				 //延时200ms，芯片必须要求这个时间
		memset(UART4_RX_BUF,0,20);	 //清除串口4接收缓存区	
		UART4_RX_LEN=0; 		        //串口4状态清零
	}
}

/***********************************************************************
 函数名      ：WiFi_ToPC  
 函数功能    ：串口向PC棒发送函数
 输入        ：要发送的数据或指令
 输出        ：无
************************************************************************/
void WiFi_ToPC(u8 *data)
{
	if(PCB_Ready==1)
	{                             
		u2_printf("%s",data);	
		memset(USART2_RX_BUF,0,20);//清除串口2接收缓存区
		USART2_RX_LEN=0; 					//串口2接收标志清零
	}
}

/***********************************************************************
 函数名      ：Fun_ZB(void)   
 函数功能    ：执行支背操作
 输入        ：无
 输出        ：无                           
************************************************************************/
void Fun_ZB(void)
{
	u8 direct,len;
	u16 arr_now;         //当前一次运行脉冲数	
	//实现上位机实时显示护理床当前运动状态
	static u8 k;         //传第k张动画
	static u8 kj;
	u8 j=0;	
	u16 arr_send;        //当前一次运行脉冲值
	static u8 zbjx_flag; //支背运行到极限位置置1，发送极限位置图片	
	
	//联锁功能，只有在左右翻身功能复位后，才能进行支背
	if((ZF_Flag==0)&&(YF_Flag==0))
	{	
		//判断接收字符串
		if((strstr((const char *)USART2_RX_BUF,(const char *)"ZBS"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"ZBS")))
		{
			if(Ang_To_Arr_ZB(ZB_Lim)>ZB_Runed)  //上行时，比较值为上行极限装载值与校准后的当量装载值的差值，两个差值不能为0
			{				
				direct=1;					//设置运行方向标志
				ZB_Dir_flag=1; 		//设置运行方向标志     
				if(ZB_Flag==0)
				{
					ZB_Flag=1;			//设置支背状态标志位
					W25QXX_Write((u8*)&ZB_Flag,35,1);	//将状态标志位写入flash
					delay_ms(200);
					u2_printf("ZB_flag==1");
					delay_ms(200);
					u2_printf("ZBKS");
					delay_ms(200);
					u2_printf("CT_ZB1");
				}
				MotorStart(1,1,0,0);                              //支背上行
				u2_printf("*%s*M1*Z*/*/**",RX_BUF);								//串口2发送
				TIM10_Init(Ang_To_Arr_ZB(ZB_Lim)-ZB_Runed,65000);    //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
			}				
		}
		//判断接收字符串
		if((strstr((const char *)USART2_RX_BUF,(const char *)"ZBX"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"ZBX")))
		{
			if(ZB_Runed>0)    //下行时，比较值为校准后的当量装载值与0,且不能为0
			{
				direct=0;				//设置运行方向标志
				ZB_Dir_flag=0;  //设置运行方向标志
				if(1==zbjx_flag)
				{
					zbjx_flag=0;	//设置极限状态标志位
					delay_ms(200);
					u2_printf("CT_ZB20");
					delay_ms(200);
				}
				MotorStart(1,0,0,0);       //支背下行
				u2_printf("*%s*M1*F*/*/**",RX_BUF);			//串口2反馈
				TIM10_Init(ZB_Runed,65000);    //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
			}
		}
		
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//清空串口2接收数组
		memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//清空串口4接收数组
		USART2_RX_LEN=0;															//串口2状态清零
		UART4_RX_LEN=0;																//串口4状态清零
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位		
	 	if(((ZB_Runed<Ang_To_Arr_ZB(ZB_Lim))&&(1==direct))||((0<ZB_Runed)&&(0==direct)))
		{					
			while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))  //等待定时时间到，时间到跳出循环   
			{														
				//停止指令
				if(USART2_RX_LEN&0x8000)
				{
					len=USART2_RX_LEN&0x3fff;		//获取串口2接收数组字符长度		
					USART2_RX_BUF[len]=0;			//串口2数组末尾添"0"
					if((strstr((const char *)USART2_RX_BUF,(const char *)"STOP"))||(strstr((const char *)USART2_RX_BUF,(const char *)"ZBS"))||(strstr((const char *)USART2_RX_BUF,(const char *)"ZBX")))    //若接收到Stop,则跳出循环	
					{					
//						memcpy(RX_BUF,USART2_RX_BUF,15);
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//清除串口2接收数组
						USART2_RX_LEN=0;				//串口2状态清零
						break;						
					}
					else 
					{
						u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数	
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//清除串口2接收数组		
						USART2_RX_LEN=0;				//串口2状态清零
					}						
				}
				if(UART4_RX_LEN&0x8000)
				{
					len=UART4_RX_LEN&0x3fff;		//获取串口4接收数组字符长度			
					UART4_RX_BUF[len]=0;			//串口4数组末尾添“0”
					if((strstr((const char *)UART4_RX_BUF,(const char *)"STOP"))||(strstr((const char *)UART4_RX_BUF,(const char *)"ZBS"))||(strstr((const char *)UART4_RX_BUF,(const char *)"ZBX")))    //若接收到Stop,则跳出循环	
					{					
//						memcpy(RX_BUF,UART4_RX_BUF,15);
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);	//清除串口4接收数组			
						UART4_RX_LEN=0;															//串口4状态清零
						break;
					}
					if(strstr((const char *)UART4_RX_BUF,(const char *)"SEND OK"))
					{	}
					else 
					{
						u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数	
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);	//清除串口4接收数组			
						UART4_RX_LEN=0;				  //串口4状态清零
					}						
				}		
				//发送图片指令
				 arr_send=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//获取当前寄存器运行装载值
				if(direct==1)
				{
					j=(ZB_Runed+arr_send)/(Ang_To_Arr_ZB(ZB_Lim)/19);		//图片序号计算
				}
				else
				{
					j=abs(ZB_Runed,arr_send)/(Ang_To_Arr_ZB(ZB_Lim)/19);	//图片序号计算
				}			
				k=ZB_Pic;			
				if(	k!=j)
				{
					kj=abs(k,j);											
					if(kj<2)
					{
						k=j;	ZB_Pic=k;
						if((1<ZB_Pic)&&(ZB_Pic<20))
						{
							u2_printf("CT_ZB%d",ZB_Pic);		//串口2发送动画图片指令
						}							
					}				
				}
			}
			//电机停止
			MotorStop(1);    u2_printf("*%s*M1*T*/*/**",RX_BUF);  //串口2反馈			
			TIM10_Stop();      //关闭定时器
			//判断复位
			if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))&&(direct==0))   //判断是否处于复位状态，复位状态的前提是下行的定时器走完
			{				
				arr_now=0;         //此时处于复位状态，将状态值都设为0；
				ZB_Flag=0;				 //标记位清零
				W25QXX_Write((u8*)&ZB_Flag,35,1);		//将标志位写入flash
				delay_ms(200);
				u2_printf("ZB_flag==0");
			}		
			else
			{
				arr_now=__HAL_TIM_GET_COUNTER(&TIM10_Handler);    //获取当前计数值arr_now				
				ZB_Flag=1;
			}
		  //通过上下行判断脉冲累计		
			if(	direct==1)        //如果是支背上行，则用+
			{
				if(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))
				{  
					ZB_Runed=Ang_To_Arr_ZB(ZB_Lim);		//设置已运行脉冲值为极限值
					zbjx_flag=1; 				//设置极限状态标志位
					delay_ms(200);
					u2_printf("CT_ZB20");
					delay_ms(200);
					u2_printf("ZBJX");
				}
				else
				{  ZB_Runed+=arr_now;	}		//设置已运行脉冲值=上一次运行脉冲值+此次运行脉冲值
			}
			else                //如果是支背下行，则用-
			{
				if(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))
				{	
					ZB_Runed=0;			//设置已运行脉冲值为0
					delay_ms(200);
					u2_printf("CT_ZB1");
					delay_ms(200);
					u2_printf("ZBFW");
					delay_ms(200);
				}
				else
				{
					ZB_Runed-=arr_now;	//设置已运行脉冲值=上一次运行脉冲值-此次运行脉冲值
				}						
			}		
			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位
		}
	}
	else
	{
		LedAlm(100,"ZBGS");
	}	
}
/***********************************************************************
 函数名      ：Fun_SQT(void)   
 函数功能    ：执行上曲腿操作
 输入        ：无
 输出        ：无                           
************************************************************************/
void Fun_SQT(void)
{
	u16 arr_now;              //当前一次运行脉冲数
	u8 len;                   //WiFi串口接收字符串长度
	u8 direct;	              //运行方向标志位
	//实现上位机实时显示护理床当前运动状态
	static u8 k=0;            //传输第k张动画指令
	static u8 kj;
	u8 j=0;	
	u16 arr_send;               //当前一次运行脉冲值
	static u8 sqtjx_flag;//上曲腿运行到极限位置置1，发送极限位置图片	
	
	//联锁功能，只有在左右翻身功能复位及下曲腿复位后才能进行上曲腿
	if((ZF_Flag==0)&&(YF_Flag==0)&&(XQT_Flag==0))
	{	//判断接收字符串	
		if((strstr((const char *)USART2_RX_BUF,(const char *)"SQTS"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"SQTS")))//上曲腿上行	
		{				   
			if(Ang_To_Arr_SXQT(SQT_Lim)>SQT_Runed)             //上行时，比较值为上行极限装载值与校准后的当量装载值的差值，两个差值不能为0
			{
				direct=1; 													//设置运行方向标志
				if(SQT_Flag==0)
				{
					SQT_Flag=1;												//设置状态标志位
					W25QXX_Write((u8*)&SQT_Flag,36,1);//将状态标志位写入flash
					delay_ms(200);					
					u2_printf("SQT_flag==1");
					delay_ms(200);
					u2_printf("SQTKS");
					delay_ms(200);
					u2_printf("CT_SQT1");
				}											
				MotorStart(2,0,0,0);		//曲腿推杆上行
				u2_printf("*%s*M2*Z*/*/**",RX_BUF);	//串口2反馈	
				TIM10_Init(Ang_To_Arr_SXQT(SQT_Lim)-SQT_Runed,65000);     //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz					
			} 
		}
		if((strstr((const char *)USART2_RX_BUF,(const char *)"SQTX"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"SQTX")))//上曲腿下行
		{			
			if(SQT_Runed>0)                          //下行时，比较值为校准后的当量装载值与0,且不能为0
			{
				direct=0;				//设置运行方向标志
				if(sqtjx_flag==1)
				{
					sqtjx_flag=0;	//设置极限标志位
					delay_ms(200);
					u2_printf("CT_SQT8");
				}
				MotorStart(2,1,0,0);				//曲腿推杆下行
				u2_printf("*%s*M2*F*/*/**",RX_BUF);//串口2反馈	
				TIM10_Init(SQT_Runed,65000);     //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz				
			}
		}		
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//清空串口2接收数组
		memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//清空串口4接收数组
		USART2_RX_LEN=0;															//串口2状态清零
		UART4_RX_LEN=0;															  //串口4状态清零
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);  //清除中断标志位
	 	if(((SQT_Runed!=Ang_To_Arr_SXQT(SQT_Lim))&&(1==direct))||((0!=SQT_Runed)&&(0==direct)))
		{
			while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) )
			{	
				//停止指令
				if(USART2_RX_LEN&0x8000)
				{
					len=USART2_RX_LEN&0x3fff;	//获取串口2接收数组字符长度		
					USART2_RX_BUF[len]=0;			//串口2数组末尾添"0"
					if((strstr((const char *)USART2_RX_BUF,(const char *)"STOP"))||(strstr((const char *)USART2_RX_BUF,(const char *)"SQTS"))||(strstr((const char *)USART2_RX_BUF,(const char *)"SQTX")))    //若接收到Stop,则跳出循环	
					{
//						memcpy(RX_BUF,USART2_RX_BUF,15);
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//清空串口2接收数组
						USART2_RX_LEN=0;				//串口2状态清零
						break;
					}						
					else
					{
						u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数							
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);		//清空串口2接收数组		
						USART2_RX_LEN=0;				//串口2状态清零
					}						
				}
				if(UART4_RX_LEN&0x8000)
				{
					len=UART4_RX_LEN&0x3fff;		//获取串口4接收数组字符长度			
					UART4_RX_BUF[len]=0;			//串口4状态清零
					if((strstr((const char *)UART4_RX_BUF,(const char *)"STOP"))||(strstr((const char *)UART4_RX_BUF,(const char *)"SQTS"))||(strstr((const char *)UART4_RX_BUF,(const char *)"SQTX")))    //若接收到Stop,则跳出循环	
					{
//						memcpy(RX_BUF,UART4_RX_BUF,15);
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);	//清除串口4接收数组		
						UART4_RX_LEN=0;				//串口4状态清零
						break;
					}
					if(strstr((const char *)UART4_RX_BUF,(const char *)"SEND OK"))
					{	}
					else
					{
						u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数							
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);	//清除串口4接收数组		
						UART4_RX_LEN=0;					//串口4状态清零
					}						
				}
				 arr_send=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//获取当前寄存器运行装载值
				//判断传输动画指令
				if(direct==1)
				{
					j=(SQT_Runed+arr_send)/(Ang_To_Arr_SXQT(SQT_Lim)/7);	//图片序号计算
				}
				else
				{
					j=abs(SQT_Runed,arr_send)/(Ang_To_Arr_SXQT(SQT_Lim)/7);//图片序号计算
				}
				k=SQT_Pic;
				if(	k!=j)
				{				
					kj=abs(k,j);					
					if(kj<2)
					{
						k=j;    SQT_Pic=k;
						if((1<SQT_Pic)&&(SQT_Pic<8))
						{
							u2_printf("CT_SQT%d",SQT_Pic);	//串口2发送动画图片指令
						}
					}					
				}
			}				    //等待定时时间到，时间到跳出循环
			MotorStop(2);       //推杆停止
			u2_printf("*%s*M2*T*/*/**",RX_BUF);//串口2反馈	
			TIM10_Stop();       //关闭定时器
			//判断复位
			if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))&&(direct==0)) //判断是否处于复位状态，复位状态的前提是下行的定时器走完
			{
				arr_now=0;     		//此时处于复位状态，将状态值都设为0；
				SQT_Flag=0;					//设置状态标志位
				W25QXX_Write((u8*)&SQT_Flag,36,1);//将状态标志位写入flash
				delay_ms(200);
				u2_printf("SQT_flag==0");
			}
			else
			{
				arr_now=__HAL_TIM_GET_COUNTER(&TIM10_Handler); 		//获取当前寄存器运行装载值      
				SQT_Flag=1;			//设置状态标志位
			}			
			 //通过上下行判断脉冲累计	
			if(direct==1)    //如果是上曲腿上行，则用+
			{
				if(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))
				{
					SQT_Runed=Ang_To_Arr_SXQT(SQT_Lim);		//设置已运行脉冲值为极限值
					sqtjx_flag=1;					//设置极限标志位
					delay_ms(200);
					u2_printf("CT_SQT8");
					delay_ms(200);
					u2_printf("SQTJX");
				}
				 else
				{
					SQT_Runed=SQT_Runed+arr_now;			//设置已运行脉冲值=上一次运行脉冲值+此次运行脉冲值
				}	
			}
			else     //如果是上曲腿下行，则用-
			{
				if(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))
				{
					SQT_Runed=0;		//设置已运行脉冲值=0
					delay_ms(200);
					u2_printf("CT_SQT1");
					delay_ms(200);
					u2_printf("SQTFW");
				}
				 else
				{
					SQT_Runed=SQT_Runed-arr_now;	//设置已运行脉冲值=上一次运行脉冲值-此次运行脉冲值
				}			
			}	
			 __HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //清除中断标志位	 		
		 }
	}	
	else
	{
		LedAlm(100,"SQTGS");
	}
}

/***********************************************************************
 函数名      ：Fun_XQT(void)   
 函数功能    ：执行下曲腿操作
 输入        ：无
 输出        ：无                           
************************************************************************/
void Fun_XQT(void)
{
	u16 arr_now;         //当前一次运行脉冲数   
	u8 len;              //接收的字符串长度
	u8 direct;           //代表某个动作运行的方向标志：1-正向运行；0-反向运行	
	static u8 leg_down=0;
	//实现上位机实时显示护理床当前运动状态
	static u8 k=0;       //发送第K张动画指令
	static u8 kj=0;
	u8 j=0;	
	u16 arr_send;        //当前一次运行脉冲数
	static u8 xqtjx_flag;//下曲腿运行到极限位置置1，发送极限位置图片	
	
	//联锁功能，只有在左右翻身功能复位及下曲腿复位后才能进行上曲腿
	if((ZF_Flag==0)&&(YF_Flag==0)&&(SQT_Flag==0))
	{	//判断接收字符串
		if((strstr((const char *)USART2_RX_BUF,(const char *)"XQTX"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"XQTX")))   //下曲腿下行
		{				
			if(Ang_To_Arr_SXQT(XQT_Lim)>XQT_Runed)             //下行时，比较值为上行极限装载值与校准后的当量装载值的差值，两个差值不能为0
			{
				direct=1;		//设置运行方向标志
				leg_down=1;	//设置状态标志位
				if(XQT_Flag==0)	//设置状态标志位
				{
					XQT_Flag=1;	//设置状态标志位
					W25QXX_Write((u8*)&XQT_Flag,37,1);		//将状态标志位写入flash
					u2_printf("XQT_flag==1");
					delay_ms(200);
					u2_printf("XQTKS");
					delay_ms(200);
					u2_printf("CT_XQT1");
					delay_ms(200);
				}							
				MotorStart(2,1,0,0);					//曲腿推杆下行
				u2_printf("*%s*M2*Z*/*/**",RX_BUF);//串口2反馈
				TIM10_Init(Ang_To_Arr_SXQT(XQT_Lim)-XQT_Runed,65000);     //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz				
				XQT_Flag=1;		//设置状态标志位
			}	
		}
		if((strstr((const char *)USART2_RX_BUF,(const char *)"XQTS"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"XQTS")))//下曲腿上行
		{
			
			if(XQT_Runed>0)     //上行时，比较值为上行极限装载值与校准后的当量装载值的差值，两个差值不能为0
			{
				direct=0;			//设置运行方向标志
				if(xqtjx_flag==1)
				{
					xqtjx_flag=0;	//设置极限状态标志位
					u2_printf("CT_XQT20");
					delay_ms(200);
				}
				MotorStart(2,0,0,0);		//曲腿推杆上行
				u2_printf("*%s*M2*F*/*/**",RX_BUF);//串口2反馈
				TIM10_Init(XQT_Runed*1.1,65000);    //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz			
			}
		}
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);		//清空串口2接收数组			
		memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//清空串口4接收数组
		USART2_RX_LEN=0;			//串口2状态清零
		UART4_RX_LEN=0;				  //串口4状态清零
		
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);    //清除中断标志位	

	   if(((XQT_Runed!=Ang_To_Arr_SXQT(XQT_Lim))&&(1==direct))||((0!=XQT_Runed)&&(0==direct)))
	   {			
			while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) )
			{									
				//停止指令
				if(USART2_RX_LEN&0x8000)
				{
					len=USART2_RX_LEN&0x3fff;	//获取串口2接收数组字符长度		
					USART2_RX_BUF[len]=0;	//串口2数组末尾添"0"
					if((strstr((const char *)USART2_RX_BUF,(const char *)"STOP"))||(strstr((const char *)USART2_RX_BUF,(const char *)"XQTX"))||(strstr((const char *)USART2_RX_BUF,(const char *)"XQTS")))    //若接收到Stop,则跳出循环	
					{				
//						memcpy(RX_BUF,USART2_RX_BUF,15);
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			//清空串口2接收数组
						USART2_RX_LEN=0;			//串口2状态清零
						break;
					}
					else
					{
						u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);		//清空串口2接收数组	
						USART2_RX_LEN=0;			//串口2状态清零
					}					
				}
				if(UART4_RX_LEN&0x8000)
				{
					len=UART4_RX_LEN&0x3fff;			//获取串口4接收数组字符长度		
					UART4_RX_BUF[len]=0;				//串口4数组末尾添"0"
					if((strstr((const char *)UART4_RX_BUF,(const char *)"STOP"))||(strstr((const char *)UART4_RX_BUF,(const char *)"XQTX"))||(strstr((const char *)UART4_RX_BUF,(const char *)"XQTS")))    //若接收到Stop,则跳出循环	
					{				
//						memcpy(RX_BUF,UART4_RX_BUF,15);
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);					//清空串口4接收数组
						UART4_RX_LEN=0;				  //串口4状态清零
						break;
					}
					if(strstr((const char *)UART4_RX_BUF,(const char *)"SEND OK"))
					{	}
					else
					{
						u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);				//清空串口4接收数组	
						UART4_RX_LEN=0;				  //串口4状态清零
					}					
				}
				 arr_send=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//获取当前寄存器运行装载值
				//发送动画指令
				if(direct==1)
				{
					j=(XQT_Runed+arr_send)/(Ang_To_Arr_SXQT(XQT_Lim)/19);		//图片序号计算
				}
				else
				{
					j=abs(XQT_Runed,arr_send)/(Ang_To_Arr_SXQT(XQT_Lim)/19);		//图片序号计算
				}
				k=XQT_Pic;
				if(	k!=j)
				{				
					kj=abs(k,j);
					if(kj<2)
					{
						k=j;   XQT_Pic=k;
						if((1<XQT_Pic)&&(XQT_Pic<20))
						{
							u2_printf("CT_XQT%d",XQT_Pic);		//串口2发送动画图片指令
						}
					}				
				}
			}				   //等待定时时间到，时间到跳出循环	
			MotorStop(2);      //推杆停止
			u2_printf("*%s*M2*T*/*/**",RX_BUF);//串口2反馈
			TIM10_Stop();      //关闭定时器
			//判断复位
			if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))&&(direct==0))
			{
				arr_now=0;    		//此时处于复位状态，将状态值都设为0；
				XQT_Flag=0;		//设置状态标志位
				W25QXX_Write((u8*)&XQT_Flag,37,1);		//将状态标志位写入flash
				delay_ms(200);			
				u2_printf("XQT_flag==0");
			}
			else
			{			
				arr_now=__HAL_TIM_GET_COUNTER(&TIM10_Handler);    		//获取当前寄存器运行装载值 
				XQT_Flag=1;		//设置状态标志位
			}			
			//通过上下行判断脉冲累计
			if(direct==1)    //如果是下曲腿下行，则用+
			{
				if(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))
				{
					XQT_Runed=Ang_To_Arr_SXQT(XQT_Lim);				//设置已运行脉冲值为极限值
					xqtjx_flag=1;	   	//设置极限状态标志位
					delay_ms(200);
					u2_printf("CT_XQT20");
					delay_ms(200);
					u2_printf("XQTJX");
				}
				 else
				{
					XQT_Runed=XQT_Runed+arr_now;		//设置已运行脉冲值=上一次运行脉冲值+此次运行脉冲值
				}	
			}
			else		//如果是下曲腿上行，则用-
			{
				if(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))
				{
					XQT_Runed=0;	//已运行脉冲值设为0
					delay_ms(200);
					u2_printf("CT_XQT1");
					delay_ms(200);
					u2_printf("XQTFW");
				}
				 else
				{
					XQT_Runed=XQT_Runed-arr_now;	//设置已运行脉冲值=上一次运行脉冲值-此次运行脉冲值
				}			
			}
			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位	 					
		}
//	    if((0==XQT_Runed)&&(1==leg_down))
//	   {
//			leg_down=0;
//		    MotorStart(2,0,0,0);          //下曲腿继续往上走
//			TIM10_Init(3000,65000);    //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
//			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位
//		    while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)));  //等待定时时间到
//		    MotorStop(2); 
//			TIM10_Stop();      //关闭定时器
//		    __HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位		   
//	   }
	}
	else
	{
		LedAlm(100,"XQTGS");
	}
}

/***********************************************************************
 函数名      ：Fun_ZF(void)  
 函数功能    ：执行左翻身操作
 输入        ：无
 输出        ：无                           
************************************************************************/
void Fun_ZF(void)
{
	u8 direct,key;
	u16 arr_now;                 //当前一次运行脉冲数,用于脉冲累计
	u8 len;                      //接收的字符串长度
	static u8 motor5_run_flag;   //判断小侧翻是否已经动作，若动作该位置1 
	
	//实现上位机实时显示护理床当前运动状态
	static u8 k=0,m=0;
	u8 j=0,n=0;
	u16 arr_send,arr_send1;     //当前一次运行脉冲数
	static u8 kj,mn;
	static u8 M345_Start;       //345电机第一次运行
	static u8 M345_End;         //345电机运行到上极限位置
	
	//联锁功能，只有在支背、上下曲腿、座便、桌子复位后，才能执行左翻身功能
	if((ZB_Flag==0)&&(YF_Flag==0)&&(SQT_Flag==0)&&(XQT_Flag==0)&&(ZBQ_Flag==0)&&(YL_Flag==0)&&(ZBH_Flag==0)&&(ZYH_Flag==0))
	{			
		//小侧翻起来
		if(ZF_Flag==0)   //如果复位到初始状态，才执行左翻起
		{ //判断接收字符串
			if((strstr((const char *)USART2_RX_BUF,(const char *)"ZFS"))||(strstr((const char *)UART4_RX_BUF,(const char *)"ZFS")))
			{
				memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);//清空串口2接收数组
				memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//清空串口4接收数组
				USART2_RX_LEN=0;			//串口2状态清零
				UART4_RX_LEN=0;				  //串口4状态清零
				//5号侧翻起			
				ZF_Flag=1;		//设置状态标志位
				motor5_run_flag=1;		//设置状态标志位
				W25QXX_Write((u8*)&ZF_Flag,33,1); 		//将状态标志位写入flash
				delay_ms(200);
				u2_printf("ZF_flag==1");
				delay_ms(200);
				u2_printf("ZFKS");
				delay_ms(200);
				u2_printf("CT_ZCF1");
				MotorStart(5,1,1400-1,25-1);	 			 //5号电机启动
				u2_printf("*%s*M5*Z*0*/**",RX_BUF);//串口2反馈
				memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);//清空串口2接收数组
				memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//清空串口4接收数组
				USART2_RX_LEN=0;			//串口2状态清零
				UART4_RX_LEN=0;				  //串口4状态清零
				TIM10_Init(Ang_To_Arr_ZYFS(ZF_Lim),65000);           //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz			
				__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);  //清除中断标志位
				while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)) )
				{						
					//光电限位						
					if((0==GD5_ZFZZ)&&(1==ZF_Flag))        //碰到光电开关跳出循环，电机停转 
					{						
						delay_us(100);
						if(0==GD5_ZFZZ)
						{
							u2_printf("GD5ZFZZ");
							break;	
						}								
					}
					  //判断有没有收到上位机指令		
					if(USART2_RX_LEN&0x8000)
					{				
						u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数	
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			//清空串口2接收数组
						USART2_RX_LEN=0;				//串口2状态清零										
					}
					if(UART4_RX_LEN&0x8000)
					{				
						u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数	
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//清空串口4接收数组			
						UART4_RX_LEN=0;				  //串口4状态清零										
					}
					//电机故障、故障诊断
//					if(1==Motor5_Alm)       
//					{	
//						delay_us(100);
//						if(1==Motor5_Alm)
//						{
//							ZF5_GZ=1;
//							u2_printf("ZFGZ5");
//							delay_ms(200);
//							u2_printf("*%s*M5*Z*1*/**",RX_BUF);
//							Fun_GZCL();
//							break;							
//						}	             
//					}																										
					//发送动画指令
				    arr_send1=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//获取当前寄存器运行装载值
					n=arr_send1/(Ang_To_Arr_ZYFS(ZF_Lim)/9);
					m=ZCF_Pic;
					if(	m!=n)
					{	
						mn=abs(m,n);						
						if(mn<2)
						{
							m=n;   ZCF_Pic=m;
							if((1<ZCF_Pic)&&(ZCF_Pic<10))
							{
								u2_printf("CT_ZCF%d",ZCF_Pic);		//串口2发送动画图片指令
							}
						}
					}
				}
				MotorStop(5);              //电机5停止
				u2_printf("*%s*M5*T*0*/**",RX_BUF);//串口2反馈
				TIM10_Stop();              //定时器关闭
				__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位
				delay_ms(200);
				u2_printf("CT_ZCF10");
				Motor4_BC(0,1400,1400-1,25-1);	//调用补偿函数
			}
		}	
		//翻身345号电机动作	
		if((strstr((const char *)USART2_RX_BUF,(const char *)"ZFS"))||(strstr((const char *)UART4_RX_BUF,(const char *)"ZFS"))||(1==motor5_run_flag))
		{				
			if(Ang_To_Arr_ZYFS(ZF_Lim)>ZF_Runed)
			{			     			 
				//345联动左翻起			
				 direct=1;			//设置运行方向标志
				 ZF_Dir_flag=1;		//设置方向状态标志位
				 if(M345_Start==0)
				 {
					 M345_Start=1;
					 delay_ms(100);
					 u2_printf("CT_ZF1");
				 }
				 MotorStart(3,0,1400-1,25-1);     //3号电机启动
				 MotorStart(4,0,(1400-1)*1.2,25-1);		 //4号电机启动
				 MotorStart(5,0,1400-1,25-1);			 //5号电机启动
				 if(1==motor5_run_flag)
				 {
					 motor5_run_flag=0;			//设置状态标志位
					 u2_printf("*M5JS*M345*ZZZ*000*/**");
				 }
				 else
				 {
					u2_printf("*%s*M345*ZZZ*000*/**",RX_BUF);//串口2反馈
				 }
				 TIM10_Init(Ang_To_Arr_ZYFS(ZF_Lim)-ZF_Runed,65000);	//打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
			}
		}		
		if((strstr((const char *)USART2_RX_BUF,(const char *)"ZFX"))||(strstr((const char *)UART4_RX_BUF,(const char *)"ZFX")))
		{					
			if(ZF_Runed>0)
			{			   
				//345联动左翻起	
			     direct=0;			//设置运行方向标志
				 ZF_Dir_flag=0;		//设置方向状态标志位
				 if(M345_End==1)
				 {
					 M345_End=0;
					 delay_ms(200);
					 u2_printf("CT_ZF8");	
					 delay_ms(200);
				 }
				 MotorStart(3,1,1400-1,25-1);			     //3号电机启动
				 MotorStart(4,1,(1400-1)*1.2,25-1);		 //4号电机启动
				 MotorStart(5,1,1400-1,25-1);			 //5号电机启动
				 u2_printf("*%s*M345*FFF*000*/**",RX_BUF);//串口2反馈
			     TIM10_Init(ZF_Runed,65000);			          //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz
			}
		}
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//清空串口2接收数组		
		USART2_RX_LEN=0;			//串口2状态清零
		memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//清空串口4接收数组			
		UART4_RX_LEN=0;				  //串口4状态清零
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);             // 清除中断标志位
		if(((ZF_Runed!=Ang_To_Arr_ZYFS(ZF_Lim))&&(1==direct))||((0!=ZF_Runed)&&(0==direct)))
		{
			while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))  //等待定时时间到，时间到跳出循环
			{			
				//光电限位													
				if(((0==GD3_CS)||(0==GD4_CS))&&(0==direct))   //如果碰到光电开关，跳出循环，停止运行
				{
					delay_us(100);
					if((0==GD3_CS)&&(1==GD4_CS))
					{
						MotorStop(3);
					}
					if((1==GD3_CS)&&(0==GD4_CS))
					{
						MotorStop(4);
					}
					if((0==GD3_CS)&&(0==GD4_CS))
					{
						u2_printf("GD3CS");
						delay_ms(200);
						u2_printf("GD4CS");
						break;					
					}
				}
				if(((0==GD3_ZFZZ)||(0==GD4_ZFZZ))&&(1==direct))   //如果碰到光电开关，跳出循环，停止运行
				{ 	
					delay_us(100);
					if(((0==GD3_ZFZZ)||(0==GD4_ZFZZ)))
					{
						if(0==GD3_ZFZZ)
						{
							u2_printf("GD3ZFZZ");
						}
						if(0==GD4_ZFZZ)
						{
							u2_printf("GD4ZFZZ");
						}
					}						
					break;
				}
				//停止指令
				if(USART2_RX_LEN&0x8000)
				{
					len=USART2_RX_LEN&0x3fff;	//获取串口2接收数组字符长度				
					USART2_RX_BUF[len]=0;			//串口2数组末尾添"0"
					if((strstr((const char *)USART2_RX_BUF,(const char *)"STOP"))||(strstr((const char *)USART2_RX_BUF,(const char *)"ZFS"))||(strstr((const char *)USART2_RX_BUF,(const char *)"ZFX")))    //若接收到Stop,则跳出循环	
					{
//						memcpy(RX_BUF,USART2_RX_BUF,15);
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			//清空串口2接收数组
						USART2_RX_LEN=0;			//串口2状态清零
						break;
					} 
					else 
					{
						u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数								
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);		//清空串口2接收数组	
						USART2_RX_LEN=0;			//串口2状态清零
					}						
				}
				if(UART4_RX_LEN&0x8000)
				{
					len=UART4_RX_LEN&0x3fff;		//获取串口4接收数组字符长度				
					UART4_RX_BUF[len]=0;				//串口4数组末尾添"0"
					if((strstr((const char *)UART4_RX_BUF,(const char *)"STOP"))||(strstr((const char *)UART4_RX_BUF,(const char *)"ZFS"))||(strstr((const char *)UART4_RX_BUF,(const char *)"ZFX")))    //若接收到Stop,则跳出循环	
					{
//						memcpy(RX_BUF,UART4_RX_BUF,15);
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//清空串口4接收数组			
						UART4_RX_LEN=0;				  //串口4状态清零
						break;
					} 
					if(strstr((const char *)UART4_RX_BUF,(const char *)"SEND OK"))
					{	}
					else 
					{
						u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数								
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//清空串口4接收数组			
						UART4_RX_LEN=0;				  //串口4状态清零
					}						
				}
				//电机故障、故障诊断
//				if((1==Motor3_Alm)||(1==Motor4_Alm)||(1==Motor5_Alm))       
//				{	
//					delay_us(100);		
//					if((1==Motor3_Alm)||(1==Motor4_Alm)||(1==Motor5_Alm))       
//					{	
//						if(1==Motor3_Alm)
//						{
//							ZF3_GZ=1;
//							u2_printf("*%s*M3*/*1*/**",RX_BUF);
//							delay_ms(200);
//							u2_printf("ZFGZ3");
//							Fun_GZCL();
//							break;				
//						}
//						else if(1==Motor4_Alm)
//						{
//							ZF4_GZ=1;
//							u2_printf("*%s*M4*/*1*/**",RX_BUF);
//							delay_ms(200);
//							u2_printf("ZFGZ4");
//							Fun_GZCL();
//							break;				
//						}
//						else if(1==Motor5_Alm)
//						{
//							ZF5_GZ=1;
//							u2_printf("*%s*M5*/*1*/**",RX_BUF);
//							delay_ms(200);
//							u2_printf("ZFGZ5");
//							Fun_GZCL();
//							break;
//						}					
//					}						
//				}						
				//发送动画指令
				 arr_send=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//获取当前寄存器运行装载值
				if(direct==1)
				{
					j=(ZF_Runed+arr_send)/(Ang_To_Arr_ZYFS(ZF_Lim)/7);		//图片序号计算
				}
				else
				{
					j=abs(ZF_Runed,arr_send)/(Ang_To_Arr_ZYFS(ZF_Lim)/7);		//图片序号计算
				}
				k=ZF_Pic;
				if(k!=j)
				{	
					kj=abs(k,j);				
					if(kj<2)
					{	
						k=j;  ZF_Pic=k;
						if((1<ZF_Pic)&&(ZF_Pic<8))
						{
							u2_printf("CT_ZF%d",ZF_Pic);		//串口2发送动画图片指令
						}
					}				
				}
			}
			MotorStop(3);  		
			MotorStop(4);  		
			MotorStop(5);  
			u2_printf("*%s*M345*TTT*000*/**",RX_BUF);		//串口2反馈	
			TIM10_Stop();          //关闭定时器
			//判断复位
			if(((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))||(0==GD3_CS)||(0==GD4_CS))&&(direct==0))
			{
				arr_now=0;	 //此时处于复位状态，将状态值都设为0；
				ZF_Flag=0;		//设置状态标志位
			}		
			else
			{					
				arr_now=__HAL_TIM_GET_COUNTER(&TIM10_Handler);    //获取当前计数值arr_now														
			}
			//通过上下行判断脉冲累计
			if(direct==1)           //上行，脉冲+
			{
				if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))||(0==GD3_ZFZZ)||(0==GD4_ZFZZ))
				{
					ZF_Runed=Ang_To_Arr_ZYFS(ZF_Lim);				//设置已运行脉冲值为极限值
					M345_End=1;  					
					delay_ms(200);
					u2_printf("CT_ZF8");
					delay_ms(200);
					u2_printf("ZFJX");
				}
				else
				{
					ZF_Runed=ZF_Runed+arr_now;		//设置已运行脉冲值=上一次运行脉冲值+此次运行脉冲值
				}		
			}	
			else     //下行，脉冲-
			{
				if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))||(0==GD3_CS)||(0==GD4_CS))
				{
					ZF_Runed=0;		//已运行脉冲值设为0
					M345_Start=0;  					
					delay_ms(200);
					u2_printf("CT_ZF1");
				}
				else
				{
					ZF_Runed=ZF_Runed-arr_now;			//设置已运行脉冲值=上一次运行脉冲值-此次运行脉冲值			
				}
			}					
			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);    //清除中断标志位
			
			//若定时时间到但是光电没到，则电机再运行一段距离，到达光电开关位置（光电开关安装后打开此段，并将上面的清除中断删除）
//			if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))&&((1==GD3_CS)||(1==GD4_CS))&&(direct==0))
//			{   			
//				if((1==GD3_CS)&&(0==GD4_CS))   //光电3没到位
//				{
//					u2_printf("\r\n3号电机继续运行到光电位置\r\n");
//					MotorStart(3,1,1400-1,25-1);			     //3号电机启动
//					u2_printf("*%s*M3*F*0*/**",RX_BUF);	
//					TIM10_Init(add_arr,65000);     //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位	 	
//					while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))
//					{			
//						if(0==GD3_CS)  //运行时碰到光电开关，跳出循环 
//						{		
//							delay_us(100);
//							if(0==GD3_CS) 
//							{
//								ZF_Flag=0;				
//								u2_printf("GD3CS");
//								break;	
//							}								
//						}
//					}			
//					MotorStop(3);
//					u2_printf("*%s*M3*T*0*/**",RX_BUF);
//					TIM10_Stop();         //关闭定时器
//					if(0==GD3_CS)
//					{
//						u2_printf("*%s*GD3CS*/*0*/**",RX_BUF);
//					}
//					else
//					{
//						u2_printf("*%s*GD3CS*/*1*/**",RX_BUF);
//					}
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位
//				}
//				if((0==GD3_CS)&&(1==GD4_CS))         //光电4没到位
//				{
//					u2_printf("\r\n4号电机继续运行到光电位置\r\n");
//					MotorStart(4,1,1400-1,25-1);		 //4号电机启动
//					u2_printf("*%s*M4*F*0*/**",RX_BUF);				
//					TIM10_Init(add_arr,65000);      //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位	 	
//					while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))
//					{			
//						if(0==GD4_CS)  //运行时碰到光电开关，跳出循环 
//						{
//							delay_us(100);
//							if(0==GD4_CS) 
//							{
//								ZF_Flag=0;
//								u2_printf("GD4CS");
//								break;	
//							}								
//						}
//					}			
//					MotorStop(4);         //电机停止
//					u2_printf("*%s*M4*T*0*/**",RX_BUF);
//					TIM10_Stop();         //关闭定时器
//					if(0==GD4_CS)
//					{
//						u2_printf("*%s*GD4CS*/*0*/**",RX_BUF);
//					}
//					else
//					{
//						u2_printf("*%s*GD4CS*/*1*/**",RX_BUF);
//					}
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位				
//				}
//				if((1==GD3_CS)&&(1==GD4_CS))   //光电3/4都没到位
//				{
//					u2_printf("\r\n3号及4号电机同时继续运行到光电位置\r\n");
//					MotorStart(3,1,(1400-1),25-1);     //3号电机启动
//					MotorStart(4,1,(1400-1)*1.2,25-1);		 //4号电机启动
//					MotorStart(5,1,1400-1,25-1);			 //5号电机启动
//					u2_printf("*%s*M345*FFF*000*/**",RX_BUF);	
//					TIM10_Init(add_arr,65000);   //打开定时器
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位	 	
//					while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))
//					{			
//						if((0==GD3_CS)||(0==GD4_CS))  //运行时碰到光电开关，跳出循环 
//						{
//							delay_us(100);
//							if((0==GD3_CS)||(0==GD4_CS))
//							{
//								if((0==GD3_CS)&&(1==GD4_CS))
//								{
//									MotorStop(3);
//								}
//								if((1==GD3_CS)&&(0==GD4_CS))
//								{
//									MotorStop(4);
//								}
//								if((0==GD3_CS)&&(0==GD4_CS))
//								{
//									ZF_Flag=0;				
//									u2_printf("GD3CS");
//									delay_ms(200);
//									u2_printf("GD4CS");
//									break;
//								}
//							}								
//						}
//					}			
//					MotorStop(3);         //电机停止
//					MotorStop(4);
//					MotorStop(5);
//					u2_printf("*%s*M345*TTT*000*/**",RX_BUF);
//					TIM10_Stop();         //关闭定时器
//					if((1==GD3_CS)||(1==GD4_CS))
//					{
//						if(1==GD3_CS)
//						{
//							u2_printf("*%s*GD3CS*/*1*/**",RX_BUF);
//						}
//						if(1==GD4_CS)
//						{
//							u2_printf("*%s*GD4CS*/*1*/**",RX_BUF);
//						}						
//					}
//					if((0==GD3_CS)||(0==GD4_CS))
//					{
//						if(0==GD3_CS)
//						{
//							u2_printf("*%s*GD3CS*/*0*/**",RX_BUF);
//						}
//						if(0==GD4_CS)
//						{
//							u2_printf("*%s*GD4CS*/*0*/**",RX_BUF);
//						}						
//					}
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位	
//				}
//			}
			
			//5号电机复位
			if(ZF_Flag==0)     //345联动复位到初始状态，才复位5号电机
			{			
				memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			//清空串口2接收数组
				USART2_RX_LEN=0;			//串口2状态清零
				memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);				//清空串口4接收数组	
				UART4_RX_LEN=0;				  //串口4状态清零
				//5号侧翻复位
//				Motor4_BC(1,1400,1400-1,25-1);
				delay_ms(200);
				u2_printf("CT_ZCF10");
				MotorStart(5,0,1400-1,25-1); 			 //5号电机启动
				u2_printf("*%s*M5*F*0*/**",RX_BUF);//串口2反馈
				ZF_Runed=0;			//已运行脉冲值设为0		
				TIM10_Init(Ang_To_Arr_ZYFS(ZF_Lim),65000);              //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz
				__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位
				while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) )
				{								
					//光电限位
					if(((0==GD5_CS)&&(0==ZF_Flag)) )   //碰到光电开关跳出循环，电机停转 
					{	
						delay_us(20);
						if(0==GD5_CS)
						{
							u2_printf("GD5CS");
							break;						
						}		             
					}
					  //判断有没有收到上位机指令		
					if(USART2_RX_LEN&0x8000)
					{
						u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数	
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);		//清空串口2接收数组	
						USART2_RX_LEN=0;				//串口2状态清零											
					}
					if(UART4_RX_LEN&0x8000)
					{
						u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数	
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//清空串口4接收数组		
						UART4_RX_LEN=0;					  //串口4状态清零											
					}
					//电机故障、故障诊断
//					if(1==Motor5_Alm)         
//					{	
//						delay_us(100);
//						if(1==Motor5_Alm)
//						{
//							ZF5_GZ=1;
//							u2_printf("*%s*M5*F*1*/**",RX_BUF);
//							delay_ms(200);
//							u2_printf("ZFGZ5");
//							Fun_GZCL();
//							break;						
//						}		             
//					}										
					//发送动画指令
					arr_send1=__HAL_TIM_GET_COUNTER(&TIM10_Handler);			//获取当前寄存器运行装载值			
					n=arr_send1/(Ang_To_Arr_ZYFS(ZF_Lim)/9);
					n=9-n;
					m=ZCF_Pic;
					if(	m!=n)
					{	
						mn=abs(m,n);
						if(mn<2)
						{
							m=n;  ZCF_Pic=m;
							if((1<ZCF_Pic)&&(ZCF_Pic<10))
							{
								u2_printf("CT_ZCF%d",ZCF_Pic);		//串口2发送动画图片指令
							}
						}
					}
				}      
				MotorStop(5);   
				u2_printf("*%s*M5*T*0*/**",RX_BUF);     //电机停止，串口2反馈				
				TIM10_Stop();         //关闭定时器
				__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位
				ZF_Flag=0;		//设置状态标志位
				W25QXX_Write((u8*)&ZF_Flag,33,1);		//将状态标志位写入flash
				delay_ms(200);
				u2_printf("CT_ZCF1");
				delay_ms(200);
				u2_printf("ZF_flag==0");
				delay_ms(200);
				u2_printf("ZFFW");
				//若定时时间到但是光电没到，则电机再运行一段距离，到达光电开关位置（光电开关安装后打开此段，并将上面的清除中断删除）
//				if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))&&(1==GD5_CS)&&(direct==0)&&(0==ZF_Flag))
//				{
//					MotorStart(5,0,1400-1,25-1);			 //5号电机启动
//					u2_printf("*%s*M5*F*0*/**",RX_BUF); 
//					TIM10_Init(add_arr,65000);        //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位	 	
//					while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))
//					{			
//						if(0==GD5_CS)  //运行时碰到光电开关，跳出循环 
//						{
//							delay_us(100);
//							if(0==GD5_CS)
//							{
//								u2_printf("GD5CS");
//								break;	
//							}								
//						}
//					}			
//					MotorStop(5);
//					u2_printf("*%s*M5*T*0*/**",RX_BUF); 
//					TIM10_Stop();
//					if(0==GD5_CS)
//					{
//						u2_printf("*%s*GD5CS*/*0*/**",RX_BUF); 
//					}
//					else
//					{
//						u2_printf("*%s*GD5CS*/*1*/**",RX_BUF); 
//					}
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位	
//				}
			}				
		}
	}
	else
	{
		LedAlm(100,"ZFGS");
	}	
}

/***********************************************************************
 函数名      ：Fun_YF(void)  
 函数功能    ：执行右翻身操作
 输入        ：无
 输出        ：无                           
************************************************************************/
void Fun_YF(void)
{
	u8 direct,key;
	u16 arr_now;        //当前一次运行脉冲数，用于脉冲累计
	u8 len;             //接收的字符串长度	
	static u8 motor5_run_flag;  //小侧翻已运行标志位	
	
	//实现上位机实时显示护理床当前运动状态 
	static u16 k=0,m=0;
	static u8 M345R_Start=0;  //345电机从初始位置运行
	static u8 M345R_End=0;    //345电机到达上极限位置
	u8 mn,kj;
	u16 j=0,n=0;
	u16 arr_send,arr_send1;	  //当前一次运行脉冲数
	
	//联锁功能，只有在支背、上下曲腿、座便、桌子复位后，才能执行右左翻身功能
	if((ZB_Flag==0)&&(ZF_Flag==0)&&(SQT_Flag==0)&&(XQT_Flag==0)&&(ZBQ_Flag==0)&&(YL_Flag==0)&&(YBH_Flag==0)&&(YYH_Flag==0))
	{
		if(YF_Flag==0)   //如果复位到初始状态，才执行右翻起
		{
			if((strstr((const char *)USART2_RX_BUF,(const char *)"YFS"))||(strstr((const char *)UART4_RX_BUF,(const char *)"YFS")))
			{
			 //5号侧翻起
				memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			//清空串口2接收数组
				USART2_RX_LEN=0;			//串口2状态清零
				memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//清空串口4接收数组			
				UART4_RX_LEN=0;				  //串口4状态清零
				YF_Flag=1;		//设置状态标志位
				motor5_run_flag=1;		//设置状态标志位
				W25QXX_Write((u8*)&YF_Flag,34,1);		//将状态标志位写入flash
				delay_ms(200);
				u2_printf("YF_flag==1");
				delay_ms(200);
				u2_printf("YFKS");
				delay_ms(200);
				u2_printf("CT_YCF1");
				MotorStart(5,0,1400-1,25-1);				 //5号电机启动
				u2_printf("*%s*M5*Z*0*/**",RX_BUF);//串口2反馈
				TIM10_Init(Ang_To_Arr_ZYFS(YF_Lim),65000);               //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz
				__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //清除中断标志位
				while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))
				{	
					//光电限位										
					if((0==GD5_YFZZ)&&(1==YF_Flag))                     //碰到光电开关跳出循环，电机停转 
					{	
						delay_us(100);
						if(0==GD5_YFZZ)                    //碰到光电开关跳出循环，电机停转 
						{
							u2_printf("GD5YFZZ");
							break;						
						}		             
					}
					  //判断有没有收到上位机指令		
					if(USART2_RX_LEN&0x8000)
					{
						u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数	
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//清空串口2接收数组		
						USART2_RX_LEN=0;				//串口2状态清零											
					}	
					if(UART4_RX_LEN&0x8000)
					{
						u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数	
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//清空串口4接收数组			
						UART4_RX_LEN=0;					  //串口4状态清零											
					}
					//电机故障、故障诊断
//					if(1==Motor5_Alm)        
//					{	
//						delay_us(100);
//						if(1==Motor5_Alm)        
//						{	
//							YF5_GZ=1;
//							u2_printf("*%s*M5*Z*1*/**",RX_BUF);
//							u2_printf("YF5_GZ");
//							Fun_GZCL();
//							break;						
//						}		             
//					}											
					//发送图片指令
					arr_send1=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//获取当前寄存器运行装载值
					n=arr_send1/(Ang_To_Arr_ZYFS(YF_Lim)/9);
					m=YCF_Pic;
					if(	m!=n)
					{	
						mn=abs(m,n);
						if(mn<2)
						{
							m=n;   YCF_Pic=m;
							if((1<YCF_Pic)&&(YCF_Pic<10))
							{
								u2_printf("CT_YCF%d",YCF_Pic);		//串口2发送动画图片指令
							}
						}
					}
				}					      
				MotorStop(5);  u2_printf("*%s*M5*T*0*/**",RX_BUF);       //电机停止，串口2反馈			
				TIM10_Stop();         //关闭定时器
				__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //清除中断标志位
				delay_ms(200);
				u2_printf("CT_YCF10");
				Motor4_BC(1,3200,1400-1,25-1);//调用补偿函数2200
			}			
		}	
		//翻身345号电机动作	
		if((strstr((const char *)USART2_RX_BUF,(const char *)"YFS"))||(strstr((const char *)UART4_RX_BUF,(const char *)"YFS"))||(1==motor5_run_flag))  //右翻身上
		{		
			if(Ang_To_Arr_ZYFS(YF_Lim)>YF_Runed)
			{				
				//345联动左翻起
				direct=1;			//设置运行方向标志
				YF_Dir_flag=1;		//设置方向状态标志位
				if(M345R_Start==0)
				{
					M345R_Start=1;
					delay_ms(200);
					u2_printf("CT_YF1");
					delay_ms(200);
				}
				MotorStart(3,1,(1400-1)*2,25-1);			     //3号电机启动
				MotorStart(4,1,(1400-1)*0.8,25-1);				 //4号电机启动
				MotorStart(5,1,1400-1,25-1);			 				 //5号电机启动
				if(1==motor5_run_flag)
				{
					motor5_run_flag=0;		//设置状态标志位
					u2_printf("*M5JS*M345*ZZZ*000*/**");
				}
				else
				{
					u2_printf("*%s*M345*ZZZ*000*/**",RX_BUF);	//串口2反馈
				}
				TIM10_Init(Ang_To_Arr_ZYFS(YF_Lim)-YF_Runed,65000);	      //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz			
			}
		}
		if((strstr((const char *)USART2_RX_BUF,(const char *)"YFX"))||(strstr((const char *)UART4_RX_BUF,(const char *)"YFX")))  //右翻身下
		{			
			if(YF_Runed>0)
			{
				//345联动左翻起
			   direct=0;			//设置运行方向标志
				 YF_Dir_flag=0;		//设置方向状态标志位
				if(M345R_End==1)
			   {
					M345R_End=0; 
					delay_ms(200);
					u2_printf("CT_YF8");	
			   }
				MotorStart(3,0,(1400-1)*2,25-1);			     //3号电机启动
				MotorStart(4,0,(1400-1)*0.8,25-1);	 		 	 //4号电机启动
				MotorStart(5,0,1400-1,25-1);			 //5号电机启动
				u2_printf("*%s*M345*FFF*000*/**",RX_BUF);	//串口2反馈
			  TIM10_Init(YF_Runed,65000);		     //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
			}	
		}				
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//清空串口2接收数组		
		USART2_RX_LEN=0;			//串口2状态清零
		memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//清空串口4接收数组		
		UART4_RX_LEN=0;				  //串口4状态清零
		  __HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);           //清除中断标志位	 	

		 if(((YF_Runed!=Ang_To_Arr_ZYFS(YF_Lim))&&(1==direct))||((0!=YF_Runed)&&(0==direct)))
		 {
			while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))    //等待定时时间到，时间到跳出循环
			{							
				//光电限位													
				if(((0==GD3_CS)||(0==GD4_CS))&&(0==direct))   //如果碰到光电开关，跳出循环，停止运行
				{
					delay_us(100);
					if((0==GD3_CS)&&(1==GD4_CS))
					{
						MotorStop(3);  
					}
					if((1==GD3_CS)&&(0==GD4_CS))
					{
						MotorStop(4);
					}
					if((0==GD3_CS)&&(0==GD4_CS))
					{
						u2_printf("GD3CS");
						delay_ms(200);
						u2_printf("GD4CS");
						break;					
					}
				}
				if(((0==GD3_YFZZ)||(0==GD4_YFZZ))&&(1==direct))  //如果碰到光电开关，跳出循环，停止运行
				{
					delay_us(100);
					if((0==GD3_YFZZ)||(0==GD4_YFZZ))          //如果碰到光电开关，跳出循环，停止运行
					{
						if(0==GD3_YFZZ)
						{
							u2_printf("GD3YFZZ");
						}
						if(0==GD4_YFZZ)
						{
							u2_printf("GD4YFZZ");
						}
						break;
					}
				}
				//停止指令
				if(USART2_RX_LEN&0x8000)
				{
					len=USART2_RX_LEN&0x3fff;	//获取串口2接收数组字符长度		
					USART2_RX_BUF[len]=0;			//串口2数组末尾添"0"
					if((strstr((const char *)USART2_RX_BUF,(const char *)"STOP"))||(strstr((const char *)USART2_RX_BUF,(const char *)"YFS"))|| (strstr((const char *)USART2_RX_BUF,(const char *)"YFX"))) //若接收到Stop,则跳出循环	
					{
//						memcpy(RX_BUF,USART2_RX_BUF,15);
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);//清空串口2接收数组			
						USART2_RX_LEN=0;				//串口2状态清零
						break;
					}
					else 
					{
						u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数							
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//清空串口2接收数组		
						USART2_RX_LEN=0;
					}					
				}
				if(UART4_RX_LEN&0x8000)
				{
					len=UART4_RX_LEN&0x3fff;	//获取串口4接收数组字符长度				
					UART4_RX_BUF[len]=0;				//串口4数组末尾添"0"
					if((strstr((const char *)UART4_RX_BUF,(const char *)"STOP"))||(strstr((const char *)UART4_RX_BUF,(const char *)"YFS"))|| (strstr((const char *)UART4_RX_BUF,(const char *)"YFX"))) //若接收到Stop,则跳出循环	
					{
//						memcpy(RX_BUF,UART4_RX_BUF,15);
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);				//清空串口4接收数组	
						UART4_RX_LEN=0;				  //串口4状态清零
						break;
					}
					if(strstr((const char *)UART4_RX_BUF,(const char *)"SEND OK"))
					{	}
					else 
					{
						u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数							
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//清空串口4接收数组		
						UART4_RX_LEN=0;				  //串口4状态清零
					}					
				}
				//电机故障、故障诊断
//				if((1==Motor3_Alm)||(1==Motor4_Alm)||(1==Motor5_Alm))         
//				{	
//					delay_us(100);
//					if((1==Motor3_Alm)||(1==Motor4_Alm)||(1==Motor5_Alm))         
//					{
//						if(1==Motor3_Alm)
//						{
//							YF3_GZ=1;
//							u2_printf("*%s*M3*/*1*/**",RX_BUF);
//							delay_ms(200);
//							u2_printf("YFGZ3");
//							Fun_GZCL();	
//							break;				
//						}
//						if(1==Motor4_Alm)
//						{
//							YF4_GZ=1;
//							u2_printf("*%s*M4*/*1*/**",RX_BUF);
//							delay_ms(200);
//							u2_printf("YFGZ4");
//							Fun_GZCL();	
//							break;				
//						}
//						if(1==Motor5_Alm)
//						{
//							YF5_GZ=1;
//							u2_printf("*%s*M5*/*1*/**",RX_BUF);
//							delay_ms(200);
//							u2_printf("YFGZ5");
//							Fun_GZCL();	
//							break;
//						}
//					}						
//				}									
				//发送动画指令
				 arr_send=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//获取当前寄存器运行装载值
				if(direct==1)
				{
					j=(YF_Runed+arr_send)/(Ang_To_Arr_ZYFS(YF_Lim)/7);		//图片序号计算
				}
				else
				{
					j=abs(YF_Runed,arr_send)/(Ang_To_Arr_ZYFS(YF_Lim)/7);		//图片序号计算
				}
				k=YF_Pic;
				if(	k!=j)
				{	
					kj=abs(k,j);				
					if(kj<2)
					{
						k=j;  YF_Pic=k;
						if((1<YF_Pic)&&(YF_Pic<8))
						{	
							u2_printf("CT_YF%d",YF_Pic);		//串口2发送动画图片指令
						}
					}				
				}
			}
			//电机停止
			MotorStop(3); 				
			MotorStop(4); 	
			MotorStop(5);   
			u2_printf("*%s*M345*TTT*000*/**",RX_BUF);//串口2反馈
			TIM10_Stop();          //定时器关闭
			//判断复位	
			if(((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))||(0==GD3_CS)||(0==GD4_CS))&&(direct==0))
			{
				arr_now=0; 		//此时处于复位状态，将状态值都设为0；
				YF_Flag=0;		//设置状态标志位
			}					
			else
			{							
				arr_now=__HAL_TIM_GET_COUNTER(&TIM10_Handler);			//获取当前寄存器运行装载值				
			}
			//通过上下行判断脉冲累计
			if(direct==1)    //翻身上行，则用+
			{
				if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))||(0==GD3_YFZZ)||(0==GD4_YFZZ))
				{
					YF_Runed=Ang_To_Arr_ZYFS(YF_Lim);				//设置已运行脉冲值为极限值
					M345R_End=1; 					
					delay_ms(200);
					u2_printf("CT_YF8");
				}
				else
				{				
					YF_Runed=YF_Runed+arr_now;		//设置已运行脉冲值=上一次运行脉冲值+此次运行脉冲值
				}
			}
			else		//翻身下行，则用-
			{
				if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))||(0==GD3_CS)||(0==GD4_CS))
				{
					YF_Runed=0;	//已运行脉冲值设为0
					M345R_Start=0; 					
					delay_ms(200);
					u2_printf("CT_YF1");
				}
				else
				{
					YF_Runed=YF_Runed-arr_now;		//设置已运行脉冲值=上一次运行脉冲值-此次运行脉冲值
				}			
			}			
			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位
			//若定时时间到但是光电没到，则电机再运行一段距离，到达光电开关位置（光电开关安装后打开此段）
//			if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))&&((1==GD3_CS)||(1==GD4_CS))&&(direct==0)&&(YF_Flag==1))
//			{   			
//				if((1==GD3_CS)&&(0==GD4_CS))   //光电3没到位
//				{
//					MotorStart(3,0,1400-1,25-1);     //3号电机启动
//					u2_printf("*%s*M3*F*0*/**",RX_BUF);
//					TIM10_Init(add_arr,65000);      //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位	 	
//					while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))
//					{			
//						if(0==GD3_CS)  //运行时碰到光电开关，跳出循环 
//						{
//							delay_us(100);
//							if(0==GD3_CS) 
//							{
//								YF_Flag=0;	
//								u2_printf("GD3CS");
//								break;	
//							}								
//						}
//					}			
//					MotorStop(3);  //电机停止
//					u2_printf("*%s*M3*T*0*/**",RX_BUF);
//					TIM10_Stop();     //关闭定时器
//					if(0==GD3_CS)
//					{
//						u2_printf("*%s*GD3CS*/*0*/**",RX_BUF);
//					}
//					else
//					{
//						u2_printf("*%s*GD3CS*/*1*/**",RX_BUF);
//					}
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位
//				}
//				if((0==GD3_CS)&&(1==GD4_CS))   //光电4没到位
//				{
//					MotorStart(4,0,1400-1,25-1);		 //4号电机启动
//					u2_printf("*%s*M4*F*0*/**",RX_BUF);
//					TIM10_Init(add_arr,65000);      //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位	 	
//					while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))
//					{			
//						if(0==GD4_CS)  //运行时碰到光电开关，跳出循环 
//						{
//							delay_us(100);
//							if(0==GD4_CS) 
//							{
//								YF_Flag=0;	
//								u2_printf("GD4CS");
//								break;
//							}
//						}
//					}			
//					MotorStop(4);  //电机停止
//					u2_printf("*%s*M4*T*0*/**",RX_BUF);
//					TIM10_Stop();      //关闭定时器
//					if(0==GD4_CS)
//					{
//						u2_printf("*%s*GD4CS*/*0*/**",RX_BUF);
//					}
//					else
//					{
//						u2_printf("*%s*GD4CS*/*1*/**",RX_BUF);
//					}
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位				
//				}
//				if((1==GD3_CS)&&(1==GD4_CS))   //光电3/4都没到位
//				{
//					MotorStart(3,0,(1400-1)*2.0,25-1);     //3号电机启动
//					MotorStart(4,0,(1400-1)*0.8,25-1);		 //4号电机启动
//					MotorStart(5,0,1400-1,25-1);					 //5号电机启动
//					u2_printf("*%s*M345*FFF*000*/**",RX_BUF);
//					TIM10_Init(add_arr,65000);      //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位	 	
//					while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))
//					{			
//						if((0==GD3_CS)||(0==GD4_CS))  //运行时碰到光电开关，跳出循环 
//						{
//							delay_us(100);
//							if((0==GD3_CS)&&(1==GD4_CS))
//							{
//								MotorStop(3);
//							}
//							if((1==GD3_CS)&&(0==GD4_CS)) 
//							{
//								MotorStop(4);
//							}
//							if((0==GD3_CS)&&(0==GD4_CS)) 
//							{
//								YF_Flag=0;	
//								u2_printf("GD3CS");
//								delay_ms(200);
//								u2_printf("GD4CS");
//								break;
//							}
//						}
//					}			
//					MotorStop(3);   //电机停止
//					MotorStop(4);
//					MotorStop(5);
//					u2_printf("*%s*M345*TTT*000*/**",RX_BUF);
//					TIM10_Stop();         //关闭定时器
//					if((1==GD3_CS)||(1==GD4_CS))  //运行时碰到光电开关，跳出循环 
//					{
//						delay_us(100);
//						if(1==GD3_CS)
//						{
//							u2_printf("*%s*GD3CS*/*1*/**",RX_BUF);
//						}
//						if(1==GD4_CS) 
//						{
//							u2_printf("*%s*GD4CS*/*1*/**",RX_BUF);
//						}
//					}
//					if((0==GD3_CS)||(0==GD4_CS))  //运行时碰到光电开关，跳出循环 
//					{
//						delay_us(100);
//						if(0==GD3_CS)
//						{
//							u2_printf("*%s*GD3CS*/*0*/**",RX_BUF);
//						}
//						if(0==GD4_CS) 
//						{
//							u2_printf("*%s*GD4CS*/*0*/**",RX_BUF);
//						}
//					}
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位	
//				}
//			}
			//侧翻复位
			if(0==YF_Flag)      //只有翻身复位到初始状态，小侧翻才复位
			{			
				memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			//清空串口2接收数组
				USART2_RX_LEN=0;			//串口2状态清零
				memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//清空串口4接收数组			
				UART4_RX_LEN=0;				  //串口4状态清零
				//5号侧翻复位
//				Motor4_BC(0,2800,1400-1,25-1);//调用补偿函数
				memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//清空串口2接收数组		
				USART2_RX_LEN=0;				//串口2状态清零
				memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//清空串口4接收数组		
				UART4_RX_LEN=0;				  //串口4状态清零
				delay_ms(200);
				u2_printf("CT_ZCF10");
				MotorStart(5,1,1400-1,25-1);			 //5号电机启动
				u2_printf("*%s*M5*F*0*/**",RX_BUF);		//串口2反馈
				YF_Runed=0;			//已运行脉冲值设为0
				TIM10_Init(Ang_To_Arr_ZYFS(YF_Lim)*1,65000);           //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
				__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //清除中断标志位

				while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) )
				{				
					//光电限位
					if(((0==GD5_CS)&&(0==YF_Flag)))  //碰到光电开关跳出循环，电机停转 
					{	
						delay_us(100);
						if(0==GD5_CS)
						{
							u2_printf("GD5CS");
							break;					
						}
					}
					  //判断有没有收到上位机指令		
					if(USART2_RX_LEN&0x8000)
					{
						u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数	
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);		//清空串口2接收数组	
						USART2_RX_LEN=0;							//串口2状态清零								
					}
					if(UART4_RX_LEN&0x8000)
					{
						u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数	
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//清空串口4接收数组		
						UART4_RX_LEN=0;				  //串口4状态清零												
					}
					//电机故障、故障诊断
//					if(1==Motor5_Alm)       
//					{	
//						delay_us(100);
//						if(1==Motor5_Alm)
//						{
//							YF5_GZ=1;
//							u2_printf("*%s*M5*F*1*/**",RX_BUF);
//							u2_printf("YFGZ5");
//							Fun_GZCL();
//							break;						
//						}
//					}															
					//发送动画指令
					arr_send1=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//获取当前寄存器运行装载值
					n=arr_send1/(Ang_To_Arr_ZYFS(YF_Lim)/9);
					n=9-n;	
					m=YCF_Pic;
					if(	m!=n)
					{
						mn=abs(m,n);
						if(mn<2)
						{
							m=n;   YCF_Pic=m;
							if((1<YCF_Pic)&&(YCF_Pic<10))
							{
								u2_printf("CT_YCF%d",YCF_Pic);		//串口2发送动画图片指令
							}
						}
					}
				}	     
				MotorStop(5);      //电机停止
				u2_printf("*%s*M5*T*0*/**",RX_BUF);		//串口2反馈
				TIM10_Stop();        //定时器关闭
				__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //清除中断标志位
				YF_Flag=0;		//设置状态标志位
				W25QXX_Write((u8*)&YF_Flag,34,1);		//将状态标志位写入flash
				delay_ms(200);
				u2_printf("CT_YCF1");
				delay_ms(200);			
				u2_printf("YF_flag==0");
				delay_ms(200);
				u2_printf("YFFW");
				//若定时时间到但是光电没到，则电机再运行一段距离，到达光电开关位置（光电开关安装后打开此段，并将上面的清除中断删除）
//				if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))&&(1==GD5_CS)&&(direct==0)&&(0==YF_Flag))
//				{
//					MotorStart(5,1,1400-1,25-1);  			 //5号电机启动
//					u2_printf("*%s*M5*F*0*/**",RX_BUF);
//					TIM10_Init(add_arr,65000);            //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //清除中断标志位	 	
//					while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))
//					{			
//						if(0==GD5_CS)  //运行时碰到光电开关，跳出循环 
//						{
//							delay_us(100);
//							if(0==GD5_CS)
//							{
//								u2_printf("GD5CS");
//								break;	
//							}								
//						}
//					}			
//					MotorStop(5);      //电机停止
//					u2_printf("*%s*M5*T*0*/**",RX_BUF);
//					TIM10_Stop();      //关闭定时器
//					if(0==GD5_CS)
//					{
//						u2_printf("*%s*GD5CS*/*0*/**",RX_BUF);
//					}
//					else
//					{
//						u2_printf("*%s*GD5CS*/*1*/**",RX_BUF);
//					}
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位	
//				}			
			}	
		}
	}
	else
	{
		LedAlm(100,"YFGS");
	}	
}

/***********************************************************************
 函数名      ：Fun_YL(void)  
 函数功能    ：小桌子
 输入        ：无
 输出        ：无                           
************************************************************************/
void Fun_YL(void)
{
	u8 direct,key;    //表示电机运行方向，1：小桌子前进；0：小桌子后退
	u16 arr_now;      //本次运行脉冲值
	u8 len;           //表示接收的字符串的长度
	u16 arr_feed;     //计算程序中当前一次运行脉冲数,用于判断电机失步故障
	u16 pulse_num=0;  //将程序中当前一次运行脉冲数进行转化，与电机反馈的当前运行脉冲数相比较
	u16 num=0;	
	u16 repeat_num;
	u8 break_flag=0;          //判断程序是否从break跳出 
//实现上位机实时显示护理床当前运动状态 
	static u8 k=0;            //发送第k张图片
	static u8 kj=0;
	u8 i=0;
	u8 j=0;	
	u16 arr_send;                 //当前一次运行脉冲数
	static u8 yljx_flag;    //判断小桌子是否运行到极限位置，若是发送极限位置图片	
	//联锁功能，只有在左右翻身功能复位后，才能进行小桌子移动
	if((ZF_Flag==0)&&(YF_Flag==0))
	{		
		if((strstr((const char *)USART2_RX_BUF,(const char *)"YLS"))||(strstr((const char *)UART4_RX_BUF,(const char *)"YLS")))
		{
			direct=1;			//设置运行方向标志
			if(YL_Flag==0)
			{
				YL_Flag=1;		//设置状态标志位
				delay_ms(200);
				u2_printf("YL_flag==1");
				delay_ms(200);
				u2_printf("YLKS");
				delay_ms(200);
				u2_printf("CT_YL1");
			}
		}
		if((strstr((const char *)USART2_RX_BUF,(const char *)"YLX"))||(strstr((const char *)UART4_RX_BUF,(const char *)"YLX")))
		{
			direct=0;			//设置运行方向标志
			if(1==yljx_flag)
			{
				yljx_flag=0;	//设置极限状态标志位
				delay_ms(200);
				u2_printf("CT_YL20");
			}
		}
		if(direct==1)   //如果是小桌子向前
		{		
			if(Ang_To_Arr_YL(YL_Lim)>YL_Runed)  //上行时，比较值为上行极限装载值与校准后的当量装载值的差值，两个差值不能为0
			{
				MotorStart(7,0,700-1,25-1);
				TIM10_Init(Ang_To_Arr_YL(YL_Lim)-YL_Runed,65000);     //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz				
			}				
		}
		else       //如果是小桌子后退
		{
			if(YL_Runed>0)    //下行时，比较值为校准后的当量装载值与0,且不能为0
			{
				MotorStart(7,1,700-1,25-1);
				TIM10_Init(YL_Runed,65000);     //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz				
			}
		}
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);		//清空串口2接收数组	
		USART2_RX_LEN=0;				//串口2状态清零
		memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//清空串口4接收数组	
		UART4_RX_LEN=0;				  //串口4状态清零
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位
		 if(((YL_Runed!=Ang_To_Arr_YL(YL_Lim))&&(1==direct))||((0!=YL_Runed)&&(0==direct)))
		 {	 	
			while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))  //等待定时时间到，时间到跳出循环  
			{			
				for(repeat_num=0;repeat_num<600;repeat_num++)
				{			
					//光电限位											   						
//					if((0==GD7_ZZ)&&(1==direct))
//					{
//						delay_us(100);
//						if(0==GD7_ZZ)
//						{
//							u2_printf("GD7ZZ");					
//							break_flag=1;				//将循环跳出标志位置1
//							break;					
//						}								
//					}
//					if((0==GD7_CS)&&(0==direct))
//					{
//						delay_us(100);
//						if(0==GD7_CS)
//						{
//							u2_printf("GD7CS");					
//							break_flag=1;			//将循环跳出标志位置1
//							break;						
//						}					
//					}
					//停止指令
					if(USART2_RX_LEN&0x8000)
					{
						len=USART2_RX_LEN&0x3fff;			//获取串口2接收数组字符长度		
						USART2_RX_BUF[len]=0;			//串口2数组末尾添"0"
						if((strstr((const char *)USART2_RX_BUF,(const char *)"STOP"))||(strstr((const char *)USART2_RX_BUF,(const char *)"YLS"))||(strstr((const char *)USART2_RX_BUF,(const char *)"YLX")))    //若接收到Stop,则跳出循环	
						{
							break_flag=1;			//将循环跳出标志位置1
							memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);		//清空串口2接收数组	
							USART2_RX_LEN=0;				//串口2状态清零
							break;
						}
						else
						{
							u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数							
							memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);		//清空串口2接收数组	
							USART2_RX_LEN=0;				//串口2状态清零
						}						
					}
					if(UART4_RX_LEN&0x8000)
					{
						len=UART4_RX_LEN&0x3fff;	//获取串口4接收数组字符长度				
						UART4_RX_BUF[len]=0;				//串口4数组末尾添"0"
						if((strstr((const char *)UART4_RX_BUF,(const char *)"STOP"))||(strstr((const char *)UART4_RX_BUF,(const char *)"YLS"))||(strstr((const char *)UART4_RX_BUF,(const char *)"YLX")))    //若接收到Stop,则跳出循环	
						{
							break_flag=1;			//将循环跳出标志位置1
							memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//清空串口4接收数组			
							UART4_RX_LEN=0;				  //串口4状态清零
							break;
						}
						if(strstr((const char *)UART4_RX_BUF,(const char *)"SEND OK"))
						{	}
						else
						{
							u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数							
							memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//清空串口4接收数组			
							UART4_RX_LEN=0;				  //串口4状态清零
						}						
					}
					//电机故障、故障诊断
//					if(PCF8574_ReadBit(1)==1)        
//					{	
//						delay_us(100);
//						if(1==PCF8574_ReadBit(1))
//						{
//							YL_GZ=1;
//							u2_printf("*%s*M7*/*1*/**",RX_BUF);
//							delay_ms(200);
//							u2_printf("YLGZ");
//							Fun_GZCL();
//							break_flag=1;			//将循环跳出标志位置1
//							break;						
//						}								             
//					}								
				}
				if(break_flag==1)
				{
					u2_printf("break_flag==1");
					break;
				}
				//发送动画指令
				 arr_send=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//获取当前寄存器运行装载值
				if(direct==1)
				{
					j=(YL_Runed+arr_send)/(Ang_To_Arr_YL(YL_Lim)/19);		//图片序号计算
				}
				else
				{
					j=abs(YL_Runed,arr_send)/(Ang_To_Arr_YL(YL_Lim)/19);		//图片序号计算
				}
				k=YL_Pic;
				if(	k!=j)
				{				
					kj=abs(k,j);				
					if(kj<2)
					{
						k=j;  YL_Pic=k;
						if(1<YL_Pic<20)
						{
							u2_printf("CT_YL%d",YL_Pic);		//串口2发送动画图片指令
						}
					}					
				}
			}				    
			MotorStop(7);       //电机停止
			TIM10_Stop();       //定时器关闭
			break_flag=0;		//清除break标志位
			//判断复位
			if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))&&(direct==0))   //判断是否处于复位状态，复位状态的前提是下行的定时器走完
			{
				arr_now=0;    		//此时处于复位状态，将状态值都设为0；
				YL_Flag=0;		//设置状态标志位
				delay_ms(200);
				u2_printf("YL_flag==0");
			}
			else
			{
				arr_now=__HAL_TIM_GET_COUNTER(&TIM10_Handler);    //获取当前计数值arr_now				
				YL_Flag=1;		//设置状态标志位
			}	
			//通过上下行判断脉冲累计
			if(direct==1)        //如果是小桌子前进，则用+
			{
				if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))||(0==GD7_ZZ))
				{ 					
					YL_Runed=Ang_To_Arr_YL(YL_Lim);				//设置已运行脉冲值为极限值
					yljx_flag=1;		//设置极限状态标志位
					delay_ms(200);
					u2_printf("CT_YL20");
					delay_ms(200);
					u2_printf("YLJX");
				}
				else
				{  YL_Runed=YL_Runed+arr_now;	}					//设置已运行脉冲值=上一次运行脉冲值+此次运行脉冲值	
			}
			else                //如果是小桌子后退，则用-
			{
				if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))||(0==GD7_CS))
				{						
					YL_Runed=0; 			//已运行脉冲值设为0
					delay_ms(200);
					u2_printf("CT_YL1");
					delay_ms(200);
					u2_printf("YLFW");
				}
				else
				{	 
					YL_Runed=YL_Runed-arr_now;		//设置已运行脉冲值=上一次运行脉冲值-此次运行脉冲值
				}						
			}				
			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位	   			
			//若定时时间到但是光电没到，则电机再运行一段距离，到达光电开关位置（光电开关安装后打开此段,并删除清除中断语句）
//			if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))&&(GD7_CS==1)&&(direct==0)&&(YL_Flag==1))
//			{   
//				MotorStart(7,1,700-1,25-1);
//			    TIM10_Init(add_arr,65000);   //打开定时器
//				__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位
//				
//				while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))
//				{							
//					if(0==GD7_CS)  //运行时碰到光电开关，跳出循环 
//					{
//						delay_us(100);
//						if(0==GD7_CS)
//						{
//							u2_printf("GD7CS");
//							break;
//						}							
//					}
//				}			
//				MotorStop(7);   //电机停止
//				TIM10_Stop();     //关闭定时器
//				__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位	
//			}			
		}
	}
	else
	{
		LedAlm(100,"YLGS");
	}		
}



/***********************************************************************
 函数名      ：Fun_YL1(void)  
 函数功能    ：小桌子
 输入        ：无
 输出        ：无                           
************************************************************************/
void Fun_YL1(void)
{
	u8 direct,key;    //表示电机运行方向，1：小桌子前进；0：小桌子后退
	u16 arr_now;      //本次运行脉冲值
	u8 len;           //表示接收的字符串的长度
	static u8 desk_front_flag=0;			//设置状态标志位
	static u8 desk_behind_flag=0;	 		//设置状态标志位
//实现上位机实时显示护理床当前运动状态
	static u8 k=0;            //发送第k张图片
	static u8 kj=0;
	u8 j=0;	
	u16 arr_send;                 //当前一次运行脉冲数
	static u8 yljx_flag;    //判断小桌子是否运行到极限位置，若是发送极限位置图片	
	//联锁功能，只有在左右翻身功能复位后，才能进行小桌子移动
	if((ZF_Flag==0)&&(YF_Flag==0))
	{	
		//小桌子电机先运行一段时间
		if(YL_Flag==0)
		{
			if((strstr((const char *)USART2_RX_BUF,(const char *)"YLS"))||(strstr((const char *)UART4_RX_BUF,(const char *)"YLS")))
			{
				direct=1;			//设置运行方向标志
				YL_Flag=1;		//设置状态标志位
				W25QXX_Write((u8*)&YL_Flag,39,1);		//将状态标志位写入flash
				desk_front_flag=1;		//设置状态标志位
				u2_printf("YL_flag==1");
				delay_ms(200);
				u2_printf("YLKS");
				delay_ms(200);
				u2_printf("CT_YLFront");
				MotorStart(7,0,700-1,25-1);
				u2_printf("*%s*M7*Z*0*/**",RX_BUF);		//串口2反馈
				TIM10_Init((u16)(Ang_To_Arr_YL(YL_Lim)/1.5),65000);   //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
				__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);  //清除中断标志位
				while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))) 
				{
					//光电限位
					if((0==GD7_ZZ)&&(1==direct))
					{
						delay_us(100);
						if(0==GD7_ZZ)
						{
							u2_printf("GD7ZZ");					
							break;					
						}								
					}	
					//电机故障、故障诊断
//					if(PCF8574_ReadBit(1)==1)        
//					{	
//						delay_us(100);
//						if(1==PCF8574_ReadBit(1))
//						{
//							YL_GZ=1;
//							u2_printf("*%s*M7*Z*1*/**",RX_BUF);
//							delay_ms(200);
//							u2_printf("YLGZ");
//							Fun_GZCL();
//							break;						
//						}								             
//					}					
				}
				MotorStop(7);    u2_printf("*%s*M7*T*0*/**",RX_BUF);   //电机停止				，串口2反馈		
				TIM10_Stop();       //定时器关闭
				__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);		// 清除中断标志位
				u2_printf("电机7第一阶段运行完成");
			}
		}

		if((strstr((const char *)USART2_RX_BUF,(const char *)"YLS"))||(strstr((const char *)UART4_RX_BUF,(const char *)"YLS"))||(desk_front_flag==1))
		{
			desk_front_flag=0;		//设置状态标志位
			direct=1;			//设置运行方向标志
			if(YL_Flag==0)
			{
				YL_Flag=1;		//设置状态标志位
				delay_ms(200);
				u2_printf("YL_flag==1");
				delay_ms(200);
				u2_printf("YLKS");
				delay_ms(200);
				u2_printf("CT_YL1");
			}
		}
		if((strstr((const char *)USART2_RX_BUF,(const char *)"YLX"))||(strstr((const char *)UART4_RX_BUF,(const char *)"YLX")))
		{			
			direct=0;			//设置运行方向标志
			if(1==yljx_flag)
			{
				yljx_flag=0;	//设置极限状态标志位
				delay_ms(200);
				u2_printf("CT_YL20");
			}
		}
		if(direct==1)   //如果是小桌子向前
		{		
			if(Ang_To_Arr_YL(YL_Lim)>YL_Runed)  //上行时，比较值为上行极限装载值与校准后的当量装载值的差值，两个差值不能为0
			{
				MotorStart(7,0,700-1,25-1);
				u2_printf("*%s*M7*Z*0*/**",RX_BUF);		//串口2反馈
				TIM10_Init(Ang_To_Arr_YL(YL_Lim)-YL_Runed,65000);    //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz		
			}				
		}
		else       //如果是小桌子后退
		{
			if(YL_Runed>0)    //下行时，比较值为校准后的当量装载值与0,且不能为0
			{
				desk_behind_flag=1;		//设置状态标志位
				MotorStart(7,1,700-1,25-1);
				u2_printf("*%s*M7*F*0*/**",RX_BUF);		//串口2反馈
				TIM10_Init(YL_Runed,65000);    //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz			
			}
		}
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);//清空串口2接收数组			
		USART2_RX_LEN=0;				//串口2状态清零
		memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//清空串口4接收数组		
		UART4_RX_LEN=0;				  //串口4状态清零
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位
		 if(((YL_Runed!=Ang_To_Arr_YL(YL_Lim))&&(1==direct))||((0!=YL_Runed)&&(0==direct)))
		 {	 	
			 while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))  //等待定时时间到，时间到跳出循环  
			{						
				//光电限位											   						
				if((0==GD7_ZZ)&&(1==direct))
				{
					delay_us(100);
					if(0==GD7_ZZ)
					{
						u2_printf("GD7ZZ");					
						break;					
					}								
				}
				if((0==GD7_CS)&&(0==direct))
				{
					delay_us(100);
					if(0==GD7_CS)
					{
						u2_printf("GD7CS");					
						break;						
					}					
				}
				//停止指令
				if(USART2_RX_LEN&0x8000)
				{
					len=USART2_RX_LEN&0x3fff;				//获取串口2接收数组字符长度	
					USART2_RX_BUF[len]=0;			//串口2数组末尾添"0"
					if((strstr((const char *)USART2_RX_BUF,(const char *)"STOP"))||(strstr((const char *)USART2_RX_BUF,(const char *)"YLS"))||(strstr((const char *)USART2_RX_BUF,(const char *)"YLX")))    //若接收到Stop,则跳出循环	
					{
//						memcpy(RX_BUF,USART2_RX_BUF,15);
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//清空串口2接收数组		
						USART2_RX_LEN=0;			//串口2状态清零
						break;
					}
					else
					{
						u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数							
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//清空串口2接收数组		
						USART2_RX_LEN=0;			//串口2状态清零
					}						
				}	
				if(UART4_RX_LEN&0x8000)
				{
					len=UART4_RX_LEN&0x3fff;	//获取串口4接收数组字符长度				
					UART4_RX_BUF[len]=0;				//串口4数组末尾添"0"
					if((strstr((const char *)UART4_RX_BUF,(const char *)"STOP"))||(strstr((const char *)UART4_RX_BUF,(const char *)"YLS"))||(strstr((const char *)UART4_RX_BUF,(const char *)"YLX")))    //若接收到Stop,则跳出循环	
					{
//						memcpy(RX_BUF,UART4_RX_BUF,15);
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//清空串口4接收数组		
						UART4_RX_LEN=0;				  //串口4状态清零
						break;
					}
					if(strstr((const char *)UART4_RX_BUF,(const char *)"SEND OK"))
					{	}
					else
					{
						u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数							
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//清空串口4接收数组		
						UART4_RX_LEN=0;				  //串口4状态清零
					}						
				}
				//电机故障、故障诊断
//				if(1==PCF8574_ReadBit(1))        
//				{	
//					delay_us(100);
//					if(1==PCF8574_ReadBit(1))
//					{
//						YL_GZ=1;
//						u2_printf("*%s*M7*/*1*/**",RX_BUF);
//						delay_ms(200);
//						u2_printf("YLGZ");
//						Fun_GZCL();
//						break;						
//					}								             
//				}								
				
				//发送动画指令
				 arr_send=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//获取当前寄存器运行装载值
				if(direct==1)
				{
					j=(YL_Runed+arr_send)/(Ang_To_Arr_YL(YL_Lim)/19);		//图片序号计算
				}
				else
				{
					j=abs(YL_Runed,arr_send)/(Ang_To_Arr_YL(YL_Lim)/19);		//图片序号计算
				}
				k=YL_Pic;
				if(	k!=j)
				{				
					kj=abs(k,j);				
					if(kj<2)
					{
						k=j;  YL_Pic=k;
						if((1<YL_Pic)&&(YL_Pic<20))
						{
							u2_printf("CT_YL%d",YL_Pic);		//串口2发送动画图片指令
						}							
					}					
				}
			}				    
			MotorStop(7);   u2_printf("*%s*M7*T*0*/**",RX_BUF);    //电机停止，串口2反馈
			TIM10_Stop();       //定时器关闭
			//判断复位
			if(((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))||(0==GD7_CS))&&(direct==0))   //判断是否处于复位状态，复位状态的前提是下行的定时器走完
			{
				arr_now=0;         //此时处于复位状态，将状态值都设为0；
				YL_Flag=0;				//设置状态标志位
				W25QXX_Write((u8*)&YL_Flag,39,1);		//将状态标志位写入flash
				u2_printf("YL_flag==0");
			}
			else
			{
				arr_now=__HAL_TIM_GET_COUNTER(&TIM10_Handler);    //获取当前计数值arr_now				
				YL_Flag=1;		//设置状态标志位
			}	
			//通过上下行判断脉冲累计
			if(direct==1)        //如果是小桌子前进，则用+
			{
				if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))||(0==GD7_ZZ))
				{ 					
					YL_Runed=Ang_To_Arr_YL(YL_Lim);				//设置已运行脉冲值为极限值
					yljx_flag=1;		//设置极限状态标志位
					u2_printf("CT_YL20");
					delay_ms(200);
					u2_printf("YLJX");
				}
				else
				{  YL_Runed=YL_Runed+arr_now;	}				//设置已运行脉冲值=上一次运行脉冲值+此次运行脉冲值		
			}
			else                //如果是小桌子后退，则用-
			{
				if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))||(0==GD7_CS))
				{						
					YL_Runed=0; 			//已运行脉冲值设为0
					u2_printf("CT_YL1");
					delay_ms(200);
					u2_printf("YLFW");
				}
				else
				{	 
					YL_Runed=YL_Runed-arr_now;		//设置已运行脉冲值=上一次运行脉冲值-此次运行脉冲值
				}						
			}				
			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位	   			
			//若定时时间到但是光电没到，则电机再运行一段距离，到达光电开关位置（光电开关安装后打开此段,并删除清除中断语句）
//			if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))&&(GD7_CS==1)&&(direct==0)&&(YL_Flag==1))
//			{   
//				MotorStart(7,1,700-1,25-1);
//				u2_printf("*%s*M7*F*0*/**",RX_BUF);
//			    TIM10_Init(add_arr,65000);      //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
//				__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位
//				
//				while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))
//				{							
//					if(0==GD7_CS)  //运行时碰到光电开关，跳出循环 
//					{
//						delay_us(100);
//						if(0==GD7_CS)
//						{
//							u2_printf("GD7CS");
//							break;
//						}							
//					}
//				}			
//				MotorStop(7);     //电机停止
//				u2_printf("*%s*M7*T*0*/**",RX_BUF);
//				TIM10_Stop();     //关闭定时器
//				if(0==GD7_CS)
//				{
//					u2_printf("*%s*GD7CS*/*0*/**",RX_BUF);
//				}
//				else
//				{
//					u2_printf("*%s*GD7CS*/*1*/**",RX_BUF);
//				}
//				__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位	
//			}			
		}
		if((YL_Flag==0)&&(1==desk_behind_flag))
		{
			memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//清空串口2接收数组		
			USART2_RX_LEN=0;			//串口2状态清零
			memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//清空串口4接收数组		
			UART4_RX_LEN=0;				  //串口4状态清零
			YL_Runed=0;						//设置已运行脉冲为0
			MotorStart(7,1,700-1,25-1);
			u2_printf("*%s*M7*F*0*/**",RX_BUF);		//串口2反馈
			TIM10_Init(Ang_To_Arr_YL(YL_Lim)/1.5,65000);		   //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);  //清除中断标志位
			while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))) 
			{
				if(0==GD7_CS)
				{
					delay_us(100);
					if(0==GD7_CS)
					{
						u2_printf("GD7CS");					
						break;						
					}					
				}
					//电机故障、故障诊断
//				if(PCF8574_ReadBit(1)==1)        
//				{	
//					delay_us(100);
//					if(1==PCF8574_ReadBit(1))
//					{
//						YL_GZ=1;
//						u2_printf("*%s*M7*F*1*/**",RX_BUF);
//						delay_ms(200);
//						u2_printf("YLGZ");
//						Fun_GZCL();
//						break;						
//					}								             
//				}					
			}
			MotorStop(7);       //电机停止
			u2_printf("*%s*M7*T*0*/**",RX_BUF);		//串口2反馈
			TIM10_Stop();       //定时器关闭
			desk_behind_flag=0;		//设置状态标志位
			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);		// 清除中断标志位
			u2_printf("电机7第一阶段返回完成");
		}		
	}
	else
	{
		LedAlm(100,"YLGS");
	}		
}

/***********************************************************************
 函数名      ：Fun_YF2(void)  
 函数功能    ：执行右翻身操作
 输入        ：无
 输出        ：无                           
************************************************************************/
void Fun_YL2(void)
{
	u8 direct,key;    //表示电机运行方向，1：小桌子前进；0：小桌子后退
	u16 arr_now;      //本次运行脉冲值
	u8 len;           //表示接收的字符串的长度
	
//实现上位机实时显示护理床当前运动状态 
	static u8 k=0;            //发送第k张图片
	static u8 kj=0;
	u8 j=0;	
	u16 arr_send;                 //当前一次运行脉冲数
	static u8 yljx_flag;    //判断小桌子是否运行到极限位置，若是发送极限位置图片	
	//联锁功能，只有在左右翻身功能复位后，才能进行小桌子移动
	if((ZF_Flag==0)&&(YF_Flag==0))
	{		
		if((strstr((const char *)USART2_RX_BUF,(const char *)"YLS"))||(strstr((const char *)UART4_RX_BUF,(const char *)"YLS")))
		{
			direct=1;			//设置运行方向标志
			if(YL_Flag==0)
			{
				YL_Flag=1;		//设置状态标志位
				W25QXX_Write((u8*)&YL_Flag,39,1);		//将状态标志位写入flash
				delay_ms(200);
				u2_printf("YL_flag==1");
				delay_ms(200);
				u2_printf("YLKS");
				delay_ms(200);
				u2_printf("CT_YL1");
			}
		}
		if((strstr((const char *)USART2_RX_BUF,(const char *)"YLX"))||(strstr((const char *)UART4_RX_BUF,(const char *)"YLX")))
		{
			direct=0;			//设置运行方向标志
			if(1==yljx_flag)
			{
				yljx_flag=0;	//设置极限状态标志位
				delay_ms(200);
				u2_printf("CT_YL20");
			}
		}
		if(direct==1)   //如果是小桌子向前
		{		
			if(Ang_To_Arr_YL2(YL_Lim)>YL_Runed)  //上行时，比较值为上行极限装载值与校准后的当量装载值的差值，两个差值不能为0
			{
				MotorStart(7,0,700-1,25-1);
				u2_printf("*%s*M7*Z*0*/**",RX_BUF);		//串口2反馈
				TIM2_Init(Ang_To_Arr_YL2(YL_Lim)-YL_Runed,65000);  //定时器周期=(freq1*freq_time1_1)/90mhz			
			}				
		}
		else       //如果是小桌子后退
		{
			if(YL_Runed>0)    //下行时，比较值为校准后的当量装载值与0,且不能为0
			{
				MotorStart(7,1,700-1,25-1);
				u2_printf("*%s*M7*F*0*/**",RX_BUF);		//串口2反馈
				TIM2_Init(YL_Runed,65000);  //定时器周期=(freq1*freq_time1_1)/90mhz			
			}
		}
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//清空串口2接收数组		
		USART2_RX_LEN=0;				//串口2状态清零
		memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//清空串口4接收数组			
		UART4_RX_LEN=0;				  //串口4状态清零
		__HAL_TIM_CLEAR_FLAG(&TIM2_Handler, TIM_SR_CC1IF); // 清除中断标志位
		 if(((YL_Runed!=Ang_To_Arr_YL2(YL_Lim))&&(1==direct))||((0!=YL_Runed)&&(0==direct)))
		 {	 	
			while(!(__HAL_TIM_GET_FLAG(&TIM2_Handler, TIM_SR_CC1IF)))  //等待定时时间到，时间到跳出循环  
			{						
				//光电限位											   						
				if((0==GD7_ZZ)&&(1==direct))
				{
					delay_us(100);
					if(0==GD7_ZZ)
					{
						u2_printf("GD7ZZ");					
						break;					
					}								
				}
				if((0==GD7_CS)&&(0==direct))
				{
					delay_us(100);
					if(0==GD7_CS)
					{
						u2_printf("GD7CS");					
						break;						
					}					
				}
				//停止指令
				if(USART2_RX_LEN&0x8000)
				{
					len=USART2_RX_LEN&0x3fff;	//获取串口2接收数组字符长度				
					USART2_RX_BUF[len]=0;			//串口2数组末尾添"0"
					if((strstr((const char *)USART2_RX_BUF,(const char *)"STOP"))||(strstr((const char *)USART2_RX_BUF,(const char *)"YLS"))||(strstr((const char *)USART2_RX_BUF,(const char *)"YLX")))    //若接收到Stop,则跳出循环	
					{
//						memcpy(RX_BUF,USART2_RX_BUF,15);
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//清空串口2接收数组		
						USART2_RX_LEN=0;			//串口2状态清零
						break;
					}
					else
					{
						u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数							
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);		//清空串口2接收数组	
						USART2_RX_LEN=0;			//串口2状态清零
					}						
				}	
				if(UART4_RX_LEN&0x8000)
				{
					len=UART4_RX_LEN&0x3fff;		//获取串口4接收数组字符长度			
					UART4_RX_BUF[len]=0;				//串口4数组末尾添"0"
					if((strstr((const char *)UART4_RX_BUF,(const char *)"STOP"))||(strstr((const char *)UART4_RX_BUF,(const char *)"YLS"))||(strstr((const char *)UART4_RX_BUF,(const char *)"YLX")))    //若接收到Stop,则跳出循环	
					{
//						memcpy(RX_BUF,UART4_RX_BUF,15);
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//清空串口4接收数组		
						UART4_RX_LEN=0;				  //串口4状态清零
						break;
					}
					if(strstr((const char *)UART4_RX_BUF,(const char *)"SEND OK"))
					{	}
					else
					{
						u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数							
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//清空串口4接收数组			
						UART4_RX_LEN=0;				  //串口4状态清零
					}						
				}
				//电机故障、故障诊断
//				if(PCF8574_ReadBit(1)==1)        
//				{	
//					delay_us(100);
//					if(1==PCF8574_ReadBit(1))
//					{
//						YL_GZ=1;
//						u2_printf("*%s*M7*/*1*/**",RX_BUF);
//						delay_ms(200);
//						u2_printf("YLGZ");
//						Fun_GZCL();
//						break;						
//					}								             
//				}								
				
				//发送动画指令
				 arr_send=__HAL_TIM_GET_COUNTER(&TIM2_Handler);		//获取当前寄存器运行装载值
				if(direct==1)
				{
					j=(YL_Runed+arr_send)/(Ang_To_Arr_YL2(YL_Lim)/19);		//图片序号计算
				}
				else
				{
					j=abs(YL_Runed,arr_send)/(Ang_To_Arr_YL2(YL_Lim)/19);		//图片序号计算
				}
				k=YL_Pic;
				if(	k!=j)
				{				
					kj=abs(k,j);				
					if(kj<2)
					{
						k=j;  YL_Pic=k;
						if((1<YL_Pic)&&(YL_Pic<20))
						{
							u2_printf("CT_YL%d",YL_Pic);		//串口2发送动画图片指令
						}
					}					
				}
			}				    
			MotorStop(7);       //电机停止
			u2_printf("*%s*M7*T*0*/**",RX_BUF);		//串口2反馈
			TIM2_Stop();        //定时器关闭
			//判断复位
			if(((__HAL_TIM_GET_FLAG(&TIM2_Handler, TIM_SR_CC1IF))||(0==GD7_CS))&&(direct==0))   //判断是否处于复位状态，复位状态的前提是下行的定时器走完
			{
				arr_now=0;         //此时处于复位状态，将状态值都设为0；
				YL_Flag=0;		//设置状态标志位
				W25QXX_Write((u8*)&YL_Flag,39,1);		//将状态标志位写入flash
				delay_ms(200);
				u2_printf("YL_flag==0");
			}
			else
			{
				arr_now=__HAL_TIM_GET_COUNTER(&TIM2_Handler);    //获取当前计数值arr_now				
				YL_Flag=1;		//设置状态标志位
				W25QXX_Write((u8*)&YL_Flag,39,1);		//将状态标志位写入flash
			}	
			//通过上下行判断脉冲累计
			if(direct==1)        //如果是小桌子前进，则用+
			{
				if((__HAL_TIM_GET_FLAG(&TIM2_Handler, TIM_SR_CC1IF))||(0==GD7_ZZ))
				{ 					
					YL_Runed=Ang_To_Arr_YL2(YL_Lim);				//设置已运行脉冲值为极限值
					yljx_flag=1;		//设置极限状态标志位
					delay_ms(200);
					u2_printf("CT_YL20");
					delay_ms(200);
					u2_printf("YLJX");
				}
				else
				{  YL_Runed=YL_Runed+arr_now;	}					//设置已运行脉冲值=上一次运行脉冲值+此次运行脉冲值	
			}
			else                //如果是小桌子后退，则用-
			{
				if((__HAL_TIM_GET_FLAG(&TIM2_Handler, TIM_SR_CC1IF))||(0==GD7_CS))
				{						
					YL_Runed=0; 			//已运行脉冲值设为0
					delay_ms(200);
					u2_printf("CT_YL1");
					delay_ms(200);
					u2_printf("YLFW");
				}
				else
				{	 
					YL_Runed=YL_Runed-arr_now;		//设置已运行脉冲值=上一次运行脉冲值-此次运行脉冲值
				}						
			}				
			__HAL_TIM_CLEAR_FLAG(&TIM2_Handler, TIM_SR_CC1IF); // 清除中断标志位	   			
			//若定时时间到但是光电没到，则电机再运行一段距离，到达光电开关位置（光电开关安装后打开此段,并删除清除中断语句）
//			if((__HAL_TIM_GET_FLAG(&TIM2_Handler, TIM_SR_CC1IF))&&(GD7_CS==1)&&(direct==0)&&(YL_Flag==1))
//			{   
//				MotorStart(7,1,700-1,25-1);
//				u2_printf("*%s*M7*F*0*/**",RX_BUF);
//			    TIM2_Init(add_arr,65000);   //打开定时器
//				__HAL_TIM_CLEAR_FLAG(&TIM2_Handler, TIM_SR_CC1IF); // 清除中断标志位
//				
//				while(!(__HAL_TIM_GET_FLAG(&TIM2_Handler, TIM_SR_CC1IF)))
//				{							
//					if(0==GD7_CS)  //运行时碰到光电开关，跳出循环 
//					{
//						delay_us(100);
//						if(0==GD7_CS)
//						{
//							u2_printf("GD7CS");
//							break;
//						}							
//					}
//				}			
//				MotorStop(7);    //电机停止
//				u2_printf("*%s*M7*T*0*/**",RX_BUF);
//				TIM2_Stop();     //关闭定时器
//				if(0==GD7_CS)
//				{
//					u2_printf("*%s*GD7CS*/*0*/**",RX_BUF);
//				}
//				else
//				{
//					u2_printf("*%s*GD7CS*/*1*/**",RX_BUF);
//				}
//				__HAL_TIM_CLEAR_FLAG(&TIM2_Handler, TIM_SR_CC1IF); // 清除中断标志位	
//			}			
		}
	}
	else
	{
		LedAlm(100,"YLGS");
	}		
}

/***********************************************************************
 函数名      ：Fun_ZBH(void)  
 函数功能    ：左背部护理
 输入        ：无
 输出        ：无 

************************************************************************/
void Fun_ZBH(void)
{
	u8 direct,key,len;
	//实现上位机实时显示护理床当前运动状态
	static u8 k=0;      //发送第k张动画指令
	u8 j=0;	
	u16 arr_send;	    //当前一次运行脉冲数
	static u8 kj;
	
	//联锁功能，只有在已执行左翻身功能且左腰部护理复位后，才能进行左背部护理
	if((ZF_Flag==1)&&(ZYH_Flag==0))
	{
		ZBH_Flag=!ZBH_Flag;	         //左背部护理复位状态标志位取反
		ZBH_Dir_flag=!ZBH_Dir_flag;	 //左背部护理方向标志位		
		if(ZBH_Dir_flag==1)
		{ 
			direct=1;			//设置运行方向标志
			delay_ms(200);
			u2_printf("ZBHKS");
			delay_ms(200);
			u2_printf("CT_ZBH1");
		}
		else
		{ 
		    direct=0;			//设置运行方向标志
			delay_ms(200);
			u2_printf("CT_ZBH20");
		}
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//清空串口2接收数组		
		USART2_RX_LEN=0;			//串口2状态清零
		memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//清空串口4接收数组			
		UART4_RX_LEN=0;				  //串口4状态清零
		if(1==direct)
		{
			MotorStart(3,1,1400-1,25-1);	           //3号电机启动
			u2_printf("*%s*M3*Z*0*/**",RX_BUF);		//串口2反馈
			TIM10_Init(ZF_Runed,65000);           //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
		}
		else
		{
			MotorStart(3,0,1400-1,25-1);            //3号电机启动
			u2_printf("*%s*M3*F*0*/**",RX_BUF);		//串口2反馈
			TIM10_Init(ZBH_Runed,65000);         //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz			
		}
		
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);        //清除中断标志位	 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))) //等待定时时间到，时间到跳出循环   
		{			
			//光电限位
			if((0==GD3_ZFZZ)&&(0==direct))  //起来
			{
				delay_us(100);
				if(0==GD3_ZFZZ)
				{
					u2_printf("GD3ZFZZ");
					break;				
				}
			}
			if((0==GD3_CS)&&(1==direct))     //落下
			{	
				delay_us(100);
				if(0==GD3_CS)
				{
					u2_printf("GD3_CS");
					break;					
				}					
			}
			  //判断有没有收到上位机指令		
			if(USART2_RX_LEN&0x8000)
			{
				u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数	
				memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			//清空串口2接收数组
				USART2_RX_LEN=0;								//串口2状态清零										
			}
			if(UART4_RX_LEN&0x8000)
			{
				u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数	
				memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//清空串口4接收数组			
				UART4_RX_LEN=0;					  //串口4状态清零														
			}
			//电机故障、故障诊断
//			if(1==Motor3_Alm)        
//			{	
//				delay_us(100);
//				if(1==Motor3_Alm) 
//				{
//					ZBH_GZ=1;
//					u2_printf("*%s*M3*/*1*/**",RX_BUF);
//					delay_ms(200);
//					u2_printf("ZBHGZ");
//					Fun_GZCL();
//					break;				
//				}								             
//			}							
			//发送动画指令
			arr_send=__HAL_TIM_GET_COUNTER(&TIM10_Handler);				//获取当前寄存器运行装载值		
			j=arr_send/(Ang_To_Arr_ZYFS(ZF_Lim)/19);
			if(0==direct)
			{
				j=19-j;
			}
			k=ZBH_Pic;
			if(k!=j)
			{
				kj=abs(k,j);
				if(kj<2)
				{
					k=j;   ZBH_Pic=k;
					if((1<ZBH_Pic)&&(ZBH_Pic<20))
					{
						u2_printf("CT_ZBH%d",ZBH_Pic);			//串口2发送动画图片指令
					}						
				}
			}
		}				  
		MotorStop(3);       //电机停止
		u2_printf("*%s*M3*T*0*/**",RX_BUF);		//串口2反馈
		TIM10_Stop();       //关闭定时器    
		//定时时间没到，光电到
		if((!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))&&(0==GD3_CS)&&(1==direct))
		{
			ZBH_Runed=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//获取当前寄存器运行装载值
		}
		else 
		{
			ZBH_Runed=ZF_Runed;
		}		
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //清除中断标志位	
		if(ZBH_Dir_flag==1)
		{			
			delay_ms(200);
			u2_printf("CT_ZBH20");
			delay_ms(200);
			u2_printf("ZBHJX");
		}
		else
		{			
			ZBH_Runed=0;			//已运行脉冲值设为0
			delay_ms(200);
			u2_printf("CT_ZBH1");
			delay_ms(200);
			u2_printf("ZBHFW");
		}
//		//使背部护理到达水平状态
//		if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))&&(1==GD4_CS)&&(direct==1))
//		{
//			MotorStart(3,1,1400-1,25-1);                 //3号电机启动
//			u2_printf("*%s*M3*Z*0*/**",RX_BUF);
//			TIM10_Init(add_arr,65000);                //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
//			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);           //清除中断标志位	 	
//			while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))    //等待定时时间到，时间到跳出循环
//			{
//				if(0==GD3_CS)      //如果电机过载或碰到光电开关，则跳出循环，电机停止转动 
//				{ 
//					delay_us(100);
//					if(0==GD3_CS)
//					{
//						u2_printf("GD3CS");			
//						break; 
//					}						
//				}				
//			}				                                 			
//			MotorStop(3);        //电机停止
//			u2_printf("*%s*M3*T*0*/**",RX_BUF);
//			TIM10_Stop();        //定时器关闭
//			if(0==GD3_CS)
//			{
//				u2_printf("*%s*GD3CS*/*0*/**",RX_BUF);
//			}
//			else
//			{
//				u2_printf("*%s*GD3CS*/*1*/**",RX_BUF);
//			}
//			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位
//		}		
	}
	else
	{
		LedAlm(100,"ZBHGS");
	}	
}

/***********************************************************************
 函数名      ：Fun_YBH(void)
 函数功能    ：右背部护理
 输入        ：无
 输出        ：无                           
************************************************************************/
void Fun_YBH(void)
{
	u8 direct,key,len;
	//实现上位机实时显示护理床当前运动状态
	static u8 k=0;       //发送第k张动画指令
	u8 j=0;	
	u16 arr_send;	    //当前一次运行脉冲数
	static u8 kj;	

	//联锁功能，只有在已执行右翻身功能且右腰部护理复位后，才能进行右背部护理
	if((1==YF_Flag)&&(YYH_Flag==0))
	{	
		YBH_Flag=!YBH_Flag;         //右背部护理复位状态标志位
		YBH_Dir_flag=!YBH_Dir_flag; //右背部护理方向标志位 	
		if(YBH_Dir_flag==1)
		{ 
			direct=1;			//设置运行方向标志
			delay_ms(200);
			u2_printf("YBHKS");
			delay_ms(200);
			u2_printf("CT_YBH1");
		}
		else
		{ 
			direct=0;			//设置运行方向标志
			delay_ms(200);
			u2_printf("CT_YBH20");
		}
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//清空串口2接收数组		
		USART2_RX_LEN=0;			//串口2状态清零
		memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//清空串口4接收数组			
		UART4_RX_LEN=0;				  //串口4状态清零
		if(1==direct)
		{
			MotorStart(3,0,(1400-1),25-1);              //3号电机启动
			u2_printf("*%s*M3*Z*0*/**",RX_BUF);				//串口2反馈
			TIM10_Init(YF_Runed,65000);                  //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
		}
		else
		{
			MotorStart(3,1,(1400-1),25-1);             //3号电机启动
			u2_printf("*%s*M3*F*0*/**",RX_BUF);			//串口2反馈
			TIM10_Init(YBH_Runed,65000);               //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
		}
		
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);           //清除中断标志位	 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))    //等待定时时间到，时间到跳出循环 
		{			
			//光电限位控制
			if((0==GD3_YFZZ)&&(0==direct))  //起来
			{
				delay_us(100);
				if(0==GD3_YFZZ)
				{
					u2_printf("GD3YFZZ");
					break;				
				}	
			}
			if((0==GD3_CS)&&(1==direct))     //落下
			{
				delay_us(100);
				if(0==GD3_CS)
				{
					u2_printf("GD3CS");
					break;				
				}						
			}
			  //判断有没有收到上位机指令		
			if(USART2_RX_LEN&0x8000)
			{
				u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数	
				memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//清空串口2接收数组		
				USART2_RX_LEN=0;					//串口2状态清零										
			}
			if(UART4_RX_LEN&0x8000)
			{
				u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数	
				memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//清空串口4接收数组			
				UART4_RX_LEN=0;						  //串口4状态清零										
			}
			//电机故障、故障诊断
//			if(1==Motor3_Alm)        
//			{	
//				delay_us(100);
//				if(1==Motor3_Alm) 
//				{
//					YBH_GZ=1;
//					u2_printf("*%s*M3*/*1*/**",RX_BUF);
//					delay_ms(200);
//					u2_printf("YBHGZ");
//					Fun_GZCL();
//					break;				
//				}		             
//			}										
			//发送动画指令
			arr_send=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//获取当前寄存器运行装载值
			j=arr_send/(Ang_To_Arr_ZYFS(YF_Lim)/19);
			if(0==direct)
			{
				j=19-j;
			}
			k=YBH_Pic;
			if(	k!=j)
			{	
				kj=abs(k,j);				
				if(kj<2)
				{
					k=j;   YBH_Pic=k;
					if((1<YBH_Pic)&&(YBH_Pic<20))
					{
						u2_printf("CT_YBH%d",YBH_Pic);			//串口2发送动画图片指令	
					}						
				}
			}
		}			
		MotorStop(3);        //电机停止
		u2_printf("*%s*M3*T*0*/**",RX_BUF);		//串口2反馈
		TIM10_Stop();        //关闭定时器
		//定时时间没到，光电到
		if((!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))&&(0==GD3_CS)&&(1==direct))
		{
			YBH_Runed=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//获取当前寄存器运行装载值
		}
		else 
		{
			YBH_Runed=YF_Runed;
		}
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //清除中断标志位	
		
		if(YBH_Dir_flag==1)
		{ 		
			 delay_ms(200);
			 u2_printf("CT_YBH20");
			 delay_ms(200);
			 u2_printf("YBHJX");
		}
		else
		{ 			
			 YBH_Runed=0;			//已运行脉冲值设为0
			 delay_ms(200);
			 u2_printf("CT_YBH1");
			 delay_ms(200);
			 u2_printf("YBHFW");
		}	
//		//使背部护理到达水平状态
//		if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))&&(1==GD4_CS)&&(direct==1))
//		{
//			MotorStart(3,0,1400-1,25-1);             //3号电机启动
//			u2_printf("*%s*M3*Z*0*/**",RX_BUF);
//			TIM10_Init(add_arr,65000);            //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
//			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);           //清除中断标志位	 	
//			while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))    //等待定时时间到，时间到跳出循环
//			{
//				if(0==GD3_CS)      //如果电机过载或碰到光电开关，则跳出循环，电机停止转动 
//				{ 
//					delay_us(100);
//					if(0==GD3_CS)
//					{
//						u2_printf("GD3CS");			
//						break; 
//					}						
//				}				
//			}				                                 			
//			MotorStop(3);        //电机停止
//			u2_printf("*%s*M3*T*0*/**",RX_BUF);
//			TIM10_Stop();        //定时器关闭
//			if(0==GD3_CS)
//			{
//				u2_printf("*%s*GD3CS*/*0*/**",RX_BUF);
//			}
//			else
//			{
//				u2_printf("*%s*GD3CS*/*1*/**",RX_BUF);
//			}
//			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位
//		}		
	}
	else
	{
		LedAlm(100,"YBHGS");	
	}
}

/***********************************************************************
 函数名      ：Fun_ZYH(void)  
 函数功能    ：左腰部护理
 输入        ：无
 输出        ：无                           
************************************************************************/
void Fun_ZYH(void)
{
	u8 direct,key,len;	
	//实现上位机实时显示护理床当前运动状态
	static u8 k=0;      //发送第k张动画指令
	u8 j=0;	 
	u16 arr_send;	   //当前一次运行脉冲数
	static u8 kj;	

	//联锁功能，只有在已执行左翻身功能且左背部护理复位后，才能进行左腰部护理
	if((1==ZF_Flag)&&(ZBH_Flag==0))
	{
		ZYH_Flag=!ZYH_Flag;         //左腰部护理复位状态标志位
		ZYH_Dir_flag=!ZYH_Dir_flag; //左腰部护理方向标志位		
		if(ZYH_Dir_flag==1)
		{ 
			direct=1;			//设置运行方向标志
			delay_ms(200);
			u2_printf("ZYHKS");
			delay_ms(200);
			u2_printf("CT_ZYH1");
		}
		else
		{ 
			direct=0;			//设置运行方向标志
			delay_ms(200);
			u2_printf("CT_ZYH20");
		}
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);//清空串口2接收数组			
		USART2_RX_LEN=0;			//串口2状态清零
		memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//清空串口4接收数组			
		UART4_RX_LEN=0;				  //串口4状态清零
		if(1==direct)
		{
			MotorStart(4,1,(1400-1)*1.2,25-1);   		 //4号电机启动
			u2_printf("*%s*M4*Z*0*/**",RX_BUF);		//串口2反馈
			TIM10_Init(ZF_Runed,65000);              //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
		}
		else  
		{
			MotorStart(4,0,(1400-1)*1.2,25-1);  		 //4号电机启动
			u2_printf("*%s*M4*F*0*/**",RX_BUF);		//串口2反馈
			TIM10_Init(ZYH_Runed,65000);            //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
		}
		
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);          //清除中断标志位	 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))   //等待定时时间到，时间到跳出循环 
		{			
			//光电限位
			if((0==GD4_ZFZZ)&&(0==direct))  //起来
			{
				delay_us(100);
				if(0==GD4_ZFZZ)
				{
					u2_printf("GD4ZFZZ");
					break;					
				}
			}
			if((0==GD4_CS)&&(1==direct))     //落下
			{
				delay_us(100);
				if(0==GD4_CS)
				{
					u2_printf("GD4CS");
					break;				
				}						
			}
			  //判断有没有收到上位机指令		
			if(USART2_RX_LEN&0x8000)
			{
				u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数	
				memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			//清空串口2接收数组
				USART2_RX_LEN=0;					//串口2状态清零										
			}				
			if(UART4_RX_LEN&0x8000)
			{
				u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数	
				memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//清空串口4接收数组			
				UART4_RX_LEN=0;					  //串口4状态清零											
			}
			//电机故障、故障诊断
//			if(1==Motor4_Alm)        
//			{	
//				delay_us(100);
//				if(1==Motor4_Alm)
//				{
//					ZYH_GZ=1;
//					u2_printf("*%s*M4*/*1*/**",RX_BUF);
//					delay_ms(200);
//					u2_printf("ZYHGZ");
//					Fun_GZCL();
//					break;					
//				}	             
//			}						 
			 //发送动画指令			
			arr_send=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//获取当前寄存器运行装载值
			j=arr_send/(Ang_To_Arr_ZYFS(ZF_Lim)/19);
			if(0==direct)
			{
				j=19-j;
			}
			k=ZYH_Pic;
			if(	k!=j)
			{
				kj=abs(k,j);
				if(kj<2)
				{
					k=j;   ZYH_Pic=k;
					if((1<ZYH_Pic)&&(ZYH_Pic<20))
					{
						u2_printf("CT_ZYH%d",ZYH_Pic);		//串口2发送动画图片指令	
					}						
				}
			}
		}				     
		MotorStop(4);       //电机停止
		u2_printf("*%s*M4*T*0*/**",RX_BUF);		//串口2反馈
		TIM10_Stop();       //定时器关闭
		//定时时间没到，光电到
		if((!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))&&(0==GD4_CS)&&(1==direct))
		{
			ZYH_Runed=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//获取当前寄存器运行装载值
		}
		else 
		{
			ZYH_Runed=ZF_Runed;
		}
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //清除中断标志位	
		
		if(ZYH_Dir_flag==1)
		{ 
			delay_ms(200);
			u2_printf("CT_ZYH20");
			delay_ms(200);
			u2_printf("ZYHJX");
		}
		else
		{ 
			ZYH_Runed=0;			//已运行脉冲值设为0
			delay_ms(200);
			u2_printf("CT_ZYH1");
			delay_ms(200);
			u2_printf("ZYHFW");
		}		
		
//		//使腰部护理到达水平状态
//		if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))&&(1==GD4_CS)&&(direct==1))
//		{
//			MotorStart(4,1,1400-1,25-1);       		 //4号电机启动
//			u2_printf("*%s*M4*Z*0*/**",RX_BUF);
//			TIM10_Init(add_arr,65000);             //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
//			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);           //清除中断标志位	 	
//			while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))    //等待定时时间到，时间到跳出循环
//			{
//				if(0==GD4_CS)      //如果电机过载或碰到光电开关，则跳出循环，电机停止转动 
//				{ 
//					delay_us(100);
//					if(0==GD4_CS)
//					{
//						u2_printf("GD4CS");			
//						break; 
//					}						
//				}				
//			}				                                 			
//			MotorStop(4);        //电机停止
//			u2_printf("*%s*M4*T*0*/**",RX_BUF);
//			TIM10_Stop();        //定时器关闭
//			if(0==GD4_CS)
//			{
//				u2_printf("*%s*GD4CS*/*0*/**",RX_BUF);
//			}
//			else
//			{
//				u2_printf("*%s*GD4CS*/*1*/**",RX_BUF);
//			}
//			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位
//		}
	}
	else
	{
		LedAlm(100,"ZYHGS");
	}
}

/***********************************************************************
 函数名      ：Fun_YYH(void)  
 函数功能    ：右腰部护理
 输入        ：无
 输出        ：无                           
************************************************************************/
void Fun_YYH(void)
{
	u8 direct,key,len;
	//实现上位机实时显示护理床当前运动状态
	static u8 k=0;        //发送第k张动画指令
	u8 j=0;	
	u16 arr_send;	      //当前一次运行脉冲数
	static u8 kj;		

	//联锁功能，只有在已执行右翻身功能且右背部护理复位后，才能进行右腰部护理
	if((YF_Flag==1)&&(YBH_Flag==0))
	{
		YYH_Flag=!YYH_Flag;	        //右腰部护理复位状态标志位
		YYH_Dir_flag=!YYH_Dir_flag;	//右腰部护理方向标志位	
		if(YYH_Dir_flag==1)
		{ 
			direct=1;			//设置运行方向标志
			delay_ms(200);
			u2_printf("CT_YYH1");
			delay_ms(200);
			u2_printf("YYHKS");	
		}
		else
		{ 
			direct=0;			//设置运行方向标志
			delay_ms(200);
			u2_printf("CT_YYH20");
		}
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//清空串口2接收数组		
		USART2_RX_LEN=0;			//串口2状态清零
		memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//清空串口4接收数组		
		UART4_RX_LEN=0;				  //串口4状态清零
		if(1==direct)
		{
			MotorStart(4,0,(1400-1)*0.8,25-1);   		 //4号电机启动
			u2_printf("*%s*M4*Z*0*/**",RX_BUF);		//串口2反馈
			TIM10_Init(YF_Runed,65000);            //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
		}
		else
		{
			MotorStart(4,1,(1400-1)*0.8,25-1);   		 //4号电机启动
			u2_printf("*%s*M4*F*0*/**",RX_BUF);		//串口2反馈
			TIM10_Init(YYH_Runed,65000);            //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
		}	
		
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);          //清除中断标志位	 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))   //等待定时时间到，时间到跳出循环
		{			
			//光电限位
			if((0==GD4_YFZZ)&&(0==direct))  //起来
			{
				delay_us(100);
				if(0==GD4_YFZZ)
				{
					u2_printf("GD4YFZZ");
					break;				
				}	
			}
			if((0==GD4_CS)&&(1==direct))     //落下
			{
				delay_us(100);
				if(0==GD4_CS)
				{	
					u2_printf("GD4CS");
					break;									
				}
			}
			  //判断有没有收到上位机指令		
			if(USART2_RX_LEN&0x8000)
			{
				u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数	
				memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//清空串口2接收数组		
				USART2_RX_LEN=0;						//串口2状态清零									
			}
			if(UART4_RX_LEN&0x8000)
			{
				u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数	
				memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//清空串口4接收数组			
				UART4_RX_LEN=0;					  //串口4状态清零											
			}
			//电机故障、故障诊断
//			if(1==Motor4_Alm)        
//			{	
//				delay_us(100);
//				if(1==Motor4_Alm) 
//				{
//					YYH_GZ=1;
//					u2_printf("*%s*M4*/*1*/**",RX_BUF);
//					u2_printf("YYHGZ");
//					Fun_GZCL();
//					break;				
//				}		             
//			}							
			//发送动画指令
			arr_send=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//获取当前寄存器运行装载值
			j=arr_send/(Ang_To_Arr_ZYFS(YF_Lim)/19);
			if(0==direct)
			{
				j=19-j;
			}
			k=YYH_Pic;
			if(	k!=j)
			{
				kj=abs(k,j);							
				if(kj<2)	
				{
					k=j;   YYH_Pic=k;
					if((1<YYH_Pic)&&(YYH_Pic<20))
					{
						u2_printf("CT_YYH%d",YYH_Pic);			//串口2发送动画图片指令
					}						
				}
			}
		}				      
		MotorStop(4);      //电机停止
		u2_printf("*%s*M4*T*0*/**",RX_BUF);		//串口2反馈
		TIM10_Stop();      //关闭定时器 
		//定时时间没到，光电到
		if((!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))&&(0==GD4_CS)&&(1==direct))
		{
			YYH_Runed=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//获取当前寄存器运行装载值
		}
		else 
		{
			YYH_Runed=YF_Runed;
		}
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //清除中断标志位	
		
		if(YYH_Dir_flag==1)
		{ 
			delay_ms(200);
			u2_printf("CT_YYH20"); 
			delay_ms(200);
			u2_printf("YYHJX");
		}
		else
		{ 
			YYH_Runed=0;			//已运行脉冲值设为0
			delay_ms(200);
			u2_printf("CT_YYH1");
			delay_ms(200);
			u2_printf("YYHFW");
		}
//		//使腰部护理到达水平状态
//		if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))&&(1==GD4_CS)&&(direct==1))
//		{
//			MotorStart(4,0,1400-1,25-1);      		 //4号电机启动
//			u2_printf("*%s*M4*Z*0*/**",RX_BUF);
//			TIM10_Init(add_arr,65000);                 //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
//			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);           //清除中断标志位	 	
//			while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))    //等待定时时间到，时间到跳出循环
//			{
//				if(0==GD4_CS)      //如果电机过载或碰到光电开关，则跳出循环，电机停止转动 
//				{ 
//					delay_us(100);
//					if(0==GD4_CS)
//					{
//						u2_printf("GD4CS");			
//						break; 
//					}						
//				}				
//			}				                                 			
//			MotorStop(4);        //电机停止
//			u2_printf("*%s*M4*T*0*/**",RX_BUF);
//			TIM10_Stop();        //定时器关闭
//			if(0==GD4_CS)
//			{
//				u2_printf("*%s*GD4CS*/*0*/**",RX_BUF);
//			}
//			else
//			{
//				u2_printf("*%s*GD4CS*/*1*/**",RX_BUF);
//			}
//			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位
//		}		
	}
	else
	{
		LedAlm(100,"YYHGS");
	}
}

/***********************************************************************
 函数名      ：Fun_JRAM(void)   
 函数功能    ：执行肌肉按摩功能
 输入        ：t:肌肉按摩次数
 输出        ：无  
                          
***********************************************************************/
void Fun_JRAM(void)
{
	u8 i=0;
	u8 len,break_flag=0;
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//清空串口2接收数组
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//清空串口4接收数组
	USART2_RX_LEN=0;		//串口2状态清零
	UART4_RX_LEN=0;			//串口4状态清零
	//连锁功能，只有在坐便孔关闭时才可进行按摩功能
	if(0==ZBQ_Flag)
	{
		u2_printf("*%s*JRAM*Q*/*/**",RX_BUF);		//串口2反馈
		DIR_XZFPQ=1;		//旋转分配器阀门打开
		delay_ms(500);      //等待阀门打开		
		DIR_QB=1;           //气泵启动
		u2_printf("JRAMKS");
		while(1)
		{
			delay_ms(1000);
			i++;
			u2_printf("CT_JRAM%d",i);
			if(5==i)
			{
				i=0;
			}				
			if(USART2_RX_LEN&0x8000)
			{
				len=USART2_RX_LEN&0x3fff;	//获取串口2接收数组字符长度				
				USART2_RX_BUF[len]=0;			//串口2数组末尾添"0"
				if((strstr((const char *)USART2_RX_BUF,(const char *)"JRAM")))    //若接收到Stop,则跳出循环	
				{											
//					memcpy(RX_BUF,USART2_RX_BUF,15);
					memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//清空串口2接收数组		
					USART2_RX_LEN=0;			//串口2状态清零
					break_flag=1;			//将循环跳出标志位置1
					break;						
				}
			}
			if(UART4_RX_LEN&0x8000)
			{
				len=UART4_RX_LEN&0x3fff;		//获取串口4接收数组字符长度			
				UART4_RX_BUF[len]=0;				//串口4数组末尾添"0"
				if((strstr((const char *)UART4_RX_BUF,(const char *)"JRAM")))    //若接收到Stop,则跳出循环	
				{											
//					memcpy(RX_BUF,UART4_RX_BUF,15);
					memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//清空串口4接收数组		
					UART4_RX_LEN=0;				  //串口4状态清零
					break_flag=1;			//将循环跳出标志位置1
					break;						
				}
			}				
		}
		if(1==break_flag)
		{			
			u2_printf("*%s*JRAM*T*/*/**",RX_BUF);		//串口2反馈
			break_flag=0;			//清除break标志位
			DIR_QB=0;           //气泵停止
			DIR_XZFPQ=0;		//旋转分配器停止工作
			delay_ms(1000);     //等待阀门关闭
			u2_printf("JRAMJS");
		}				
	}		
	else
	{
		LedAlm(100,"JRAMGS");
	} 
}


/***********************************************************************
 函数名      ：Fun_JR(void)   
 函数功能    ：执行加热功能
 输入        ：无
 输出        ：无  
                          
***********************************************************************/
void Fun_JR(void)
{
	short temp;
	u8 i;
	if(1==ZBQ_Flag)   	//连锁功能，只有在坐便打开的时候才能进行加热
	{
		LED1=0;
		//加热
		DIR_JR=1;           //启动加热器开始加热PH3
		TIM10_Init(2000-1,45000-1);    //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
		for(i=0;i<20;i++)    //定时20S
		{
			while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)));  //等待定时时间到，时间到跳出循环
			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);          //清除中断标志位   
		}
		TIM10_Stop();       //关闭定时器	 
		DS18B20_Start();    //进行一次温度转换
		delay_ms(750);
			
		DS18B20_Rst();	 
		DS18B20_Write_Byte(0xCC);
		DS18B20_Write_Byte(0xBE);
			
		while(1)
		{
			if(1==WD1_flag)   //初始化时该标志位为1
			{
				temp=DS18B20_Get_Temp();
				if(temp<=35)
				{
					u2_printf("*%s*WD*/*%d*/**",RX_BUF,temp);		//串口2反馈
				}
				else
				{
					DIR_JR=0;        //关闭加热器
					u2_printf("*%s*WD*/*%d*/**",RX_BUF,temp);		//串口2反馈
					WD1_flag=0;   //使程序进入else，跳出第一个while循环
				}
			}
			else
			{
				WD1_flag=1;
				break;
			}
		}			
		while(1)
		{
			if(1==WD2_flag)              //初始化时该标志位为1
			{
				temp=DS18B20_Get_Temp();    //从ds18b20得到温度值
				u2_printf("*%s*WD*/*%d*/**",RX_BUF,temp);		//串口2反馈
				if(temp<=30)
				{
					DIR_JR=1;               //启动加热器加热				
				}
				else if(temp>=37)
				{
					DIR_JR=0;               //关闭加热器停止加热
					WD2_flag=0;          //使程序进入else，跳出第一个while循环
				}
			}
			else
			{
				WD1_flag=1;
				WD2_flag=1;
				break;
			}
		}		
		LED1=1;	
	}
	else
	{
		LedAlm(100,"JRGS");
	}	
}

/***********************************************************************
 函数名      ：Motor1(void)   
 函数功能    ：
 输入        ：无
 输出        ：无                           
************************************************************************/
void Motor1(u8 dir)
{
	u8 direct,len;
	u16 arr_now;              //当前一次运行脉冲数
	
//实现上位机实时显示护理床当前运动状态
	u8 break_flag=0;          //判断程序是否是从break跳出来 
	u16 repeat_num;
	static u8 k;             //传第k张动画
	static u8 kj;
	u8 i=0;
	u8 j=0;	
	u16 arr_send;              //当前一次运行脉冲值
	static u8 zbjx_flag; //支背运行到极限位置置1，发送极限位置图片
	
	//联锁功能，只有在左右翻身功能复位后，才能进行支背	
		if(dir==1)
		{				
			MotorStart(1,1,0,0);      //支背上行
			u2_printf("MotorStart(1,1,0,0)");
		}
		else
		{
			MotorStart(1,0,0,0);      ///支背下行
			u2_printf("MotorStart(1,0,0,0)");
		}
		TIM10_Init(30000,65000);    //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	

		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//清空串口2接收数组			
		USART2_RX_LEN=0;				//串口2状态清零				
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位
							
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))  //等待定时时间到，时间到跳出循环   
		{		}		
		MotorStop(1);    //电机停止
		TIM10_Stop();      //关闭定时器
		break_flag=0;      //标志位清零
		//判断复位
		u2_printf("Motor_1_STOP()");
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位	
}

/***********************************************************************
 函数名      ：Motor2(void)   
 函数功能    ：
 输入        ：无
 输出        ：无                           
************************************************************************/
void Motor2(u8 dir)
{
	u8 direct,len;
	u16 arr_now;              //当前一次运行脉冲数
	
//实现上位机实时显示护理床当前运动状态
	u8 break_flag=0;          //判断程序是否是从break跳出来 
	u16 repeat_num;
	static u8 k;             //传第k张动画
	static u8 kj;
	u8 i=0;
	u8 j=0;	
	u16 arr_send;              //当前一次运行脉冲值
	static u8 zbjx_flag; //支背运行到极限位置置1，发送极限位置图片
	
	//联锁功能，只有在左右翻身功能复位后，才能进行支背	
		if(dir==1)
		{				
			MotorStart(2,1,0,0);			//曲腿推杆下行
      u2_printf("otorStart(2,1,0,0)");           //支背上行
		}
		else
		{
			MotorStart(2,0,0,0);     //曲腿推杆上行                                                     //支背上行
			u2_printf("MotorStart(2,0,0,0)");
		}
		
		TIM10_Init(30000,65000);   //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz		
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//清空串口2接收数组		
		USART2_RX_LEN=0;				//串口2状态清零								
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位
							
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))  //等待定时时间到，时间到跳出循环   
		{		}		
		MotorStop(2);   //电机停止
		TIM10_Stop();      //关闭定时器
		break_flag=0;      //标志位清零
		//判断复位
		u2_printf("Motor2Stop");
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位	
}


/***********************************************************************
 函数名      ：Motor3(void)  
 函数功能    ：
 输入        ：无
 输出        ：无 

************************************************************************/
void Motor3(u8 dir)
{
	u8 direct,key,len;
	u16 arr_feed;       //计算程序中当前一次运行脉冲数,用于判断电机失步故障
	u16 pulse_num=0;    //将程序中当前一次运行脉冲数进行转化，与电机反馈的当前运行脉冲数相比较
	u16 num=0;	 
	u8 break_flag=0;    //判断程序是否从break跳出
					
		if(dir==1)
		{ 
			u2_printf("\r\nDIR3=1\r\n");
			direct=1;			  //设置运行方向标志
			MotorStart(3,0,1400-1,25-1);	         //3号电机启动
		}
		else
		{ 
			u2_printf("\r\nDIR3=0\r\n");
			direct=0; 			//设置运行方向标志
			MotorStart(3,1,1400-1,25-1);	          //3号电机启动
		}
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);		//清空串口2接收数组	
		USART2_RX_LEN=0;			//串口2状态清零
		TIM10_Init(8000,65000);                 //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);        //清除中断标志位	 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))) //等待定时时间到，时间到跳出循环   
		{		
				//光电限位
//				if((0==GD3_ZFZZ)&&(1==direct))  //起来
//				{
//					delay_us(100);
//					if(0==GD3_ZFZZ)
//					{
//						u2_printf("\r\nGD3_Left_End\r\n");
//						break;
//					}
//				}
//				if((0==GD3_CS)&&(0==direct))     //落下
//				{
//					delay_us(100);
//					if(0==GD3_CS)
//					{
//						u2_printf("\r\nGD3_Start\r\n");
//						break;
//					}
//				}
//				if((0==GD3_YFZZ)&&(1==direct))     //落下
//				{
//					u2_printf("\r\nGD3_Right_End\r\n");
//					break;						
//				}
				//电机故障、故障诊断
//				if(1==Motor3_Alm)        
//				{
//					delay_us(100);
//					if(1==Motor3_Alm) 
//					{
//						u2_printf("\r\nMotor3_Alm\r\n");
//						break;		       
//					}						
//				}															
		}				  
		MotorStop(3);    //电机停止
		TIM10_Stop();       //关闭定时器    
		break_flag=0;       //清除break标志位
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //清除中断标志位		
		u2_printf("\r\nMotor_3_STOP\r\n");
}

/***********************************************************************
 函数名      ：Motor4(void)  
 函数功能    ：
 输入        ：无
 输出        ：无 

************************************************************************/
void Motor4(u8 dir)
{
	u8 direct,key,len;
	u16 arr_feed;       //计算程序中当前一次运行脉冲数,用于判断电机失步故障
	u16 pulse_num=0;    //将程序中当前一次运行脉冲数进行转化，与电机反馈的当前运行脉冲数相比较
	u16 num=0;
	u8 break_flag=0;    //判断程序是否从break跳出
					
		if(dir==1)
		{ 
			u2_printf("\r\n0IR4=1\r\n");
			direct=1;			//设置运行方向标志
			MotorStart(4,0,1400-1,25-1);	  		 //4号电机启动
		}
		else
		{ 
			u2_printf("\r\nDIR4=0\r\n");
			direct=0;			//设置运行方向标志
			MotorStart(4,1,1400-1,25-1);	     		 //4号电机启动
		}
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);		//清空串口2接收数组	
		USART2_RX_LEN=0;		  	//串口2状态清零
				
		TIM10_Init(8000,65000);            //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);        //清除中断标志位	 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))) //等待定时时间到，时间到跳出循环   
		{		
				//光电限位
//				if((0==GD4_ZFZZ)&&(1==direct))     //起来
//				{
//					delay_us(100);
//					if(0==GD4_ZFZZ)
//					{
//						u2_printf("\r\nGD4_Left_End\r\n");
//						break;
//					}
//				}
//				if((0==GD4_CS)&&(0==direct))                     //落下
//				{
//					delay_us(100);
//					if(0==GD4_CS)
//					{
//						u2_printf("\r\nGD4_Start\r\n");
//						break;
//					}
//											
//				}
//				if((0==GD4_YFZZ)&&(1==direct))     //落下
//				{
//					u2_printf("\r\nGD4_Right_End\r\n");
//					break;						
//				}
				//电机故障、故障诊断
//				if(1==Motor4_Alm)        
//				{						
//					delay_us(100);
//					if(1==Motor4_Alm) 
//					{
//						u2_printf("\r\nMotor4_Alm\r\n");
//						break;
//					}
//				}													
		}				  
		MotorStop(4);   //电机停止
		TIM10_Stop();       //关闭定时器    
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //清除中断标志位	
		u2_printf("\r\nMotor_4_STOP\r\n");
}


/************************************************************************
 函数名      ：Motor5(void)  
 函数功能    ：
 输入        ：无
 输出        ：无 

************************************************************************/
void Motor5(u8 dir)
{
	u8 direct,key,len;
	u16 arr_feed;       //计算程序中当前一次运行脉冲数,用于判断电机失步故障
	u16 pulse_num=0;    //将程序中当前一次运行脉冲数进行转化，与电机反馈的当前运行脉冲数相比较
	u16 num=0;
	u8 break_flag=0;    //判断程序是否从break跳出
					
		if(dir==1)
		{ 
			u2_printf("\r\nDIR5=1\r\n");
			direct=1;			//设置运行方向标志
			MotorStart(5,1,1400-1,25-1);	    			 //5号电机启动
		}
		else
		{ 
			u2_printf("\r\nDIR5=0\r\n");
			direct=0;			//设置运行方向标志
			MotorStart(5,0,1400-1,25-1);	      			 //5号电机启动
		}
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//清空串口2接收数组		
		USART2_RX_LEN=0;			 //串口2状态清零
		
		
		TIM10_Init(8000,65000);            //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);        //清除中断标志位	 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))) //等待定时时间到，时间到跳出循环   
		{		
				//光电限位
//				if((0==GD5_ZFZZ))  //起来
//				{
//					u2_printf("\r\n0==GD5_ZFZZ\r\n");
//					break;	
//				}
						
//				if((0==GD5_ZFZZ)&&(1==direct))  //起来
//				{
//					delay_us(100);
//					if(0==GD5_ZFZZ)
//					{
//						u2_printf("\r\n0==GD5_ZFZZ\r\n");
//						break;	
//					}
//				}
//				if((0==GD5_CS)&&(0==direct))     //落下
//				{
//					delay_us(100);
//					if(0==GD5_CS)
//					{
//						u2_printf("\r\n0==GD5_CS\r\n");
//						break;
//					}
//				}
//				if((0==GD5_YFZZ)&&(1==direct))     //落下
//				{
//					u2_printf("\r\nGD5_Right_End\r\n");
//					break;						
//				}
				//电机故障、故障诊断
//				if(1==Motor5_Alm)        
//				{						
//					delay_us(100);
//					if(1==Motor5_Alm)
//					{
//						u2_printf("\r\n1==Motor5_Alm\r\n");
//						break;
//					}
//				}														
		}				  
		MotorStop(5);     //电机停止
		TIM10_Stop();       //关闭定时器    
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //清除中断标志位	
		u2_printf("\r\nMotor_5_STOP\r\n");
}

/************************************************************************
 函数名      ：Motor6(void)  
 函数功能    ：
 输入        ：无
 输出        ：无 

************************************************************************/
void Motor6(u8 dir)
{
	u8 direct,key,len;
	u16 arr_feed;       //计算程序中当前一次运行脉冲数,用于判断电机失步故障
	u16 pulse_num=0;    //将程序中当前一次运行脉冲数进行转化，与电机反馈的当前运行脉冲数相比较
	u16 num=0;
	u8 break_flag=0;    //判断程序是否从break跳出
					
		if(dir==1)
		{ 
			u2_printf("\r\nDIR6=0\r\n");
			direct=1;			//设置运行方向标志
			MotorStart(6,0,1400-1,25-1);	       //电机启动
		}
		else
		{ 
			u2_printf("\r\nDIR6=1\r\n");
			direct=0;			//设置运行方向标志
			MotorStart(6,1,1400-1,25-1);	       //电机启动
		}
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//清空串口2接收数组		
		USART2_RX_LEN=0;		  	//串口2状态清零
		
		
		TIM10_Init(30000,65000);          //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);        //清除中断标志位	 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))) //等待定时时间到，时间到跳出循环   
		{		
				//光电限位
//				if((0==GD6_ZZ)&&(direct==1))  //起来
//				{
//					delay_us(100);
//					if(0==GD6_ZZ)
//					{
//						u2_printf("\r\n0==GD6_ZZ\r\n");
//						break;
//					}					
//				}
//				if((0==GD6_CS)&&(direct==0))     //落下
//				{
//					delay_us(100);
//					if(0==GD6_CS)
//					{
//						u2_printf("\r\n0==GD6_CS\r\n");
//						break;
//					}
//				}
//			
//				//电机故障、故障诊断
//				if(1==Motor6_Alm)        
//				{						
//					delay_us(100);
//					if(1==Motor6_Alm)
//					{
//						u2_printf("\r\nMotor6_Alm\r\n");
//						break;
//					}
//				}															
		}				  
		MotorStop(6);    //电机停止
		TIM10_Stop();       //关闭定时器    
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //清除中断标志位	
		u2_printf("\r\nMotorStop(6)\r\n");
}

/************************************************************************
 函数名      ：Motor7(void)  
 函数功能    ：左背部护理
 输入        ：无
 输出        ：无 
************************************************************************/
void Motor7(u8 dir)
{
	u8 direct,key,len;
	u16 arr_feed;       //计算程序中当前一次运行脉冲数,用于判断电机失步故障
	u16 pulse_num=0;    //将程序中当前一次运行脉冲数进行转化，与电机反馈的当前运行脉冲数相比较
	u16 num=0;
	u8 break_flag=0;    //判断程序是否从break跳出
					
		if(dir==1)
		{ 
			u2_printf("\r\nDIR7=0\r\n");
			direct=1;			//设置运行方向标志
			MotorStart(7,0,700-1,25-1);	       //电机启动
		}
		else
		{ 
			u2_printf("\r\nDIR7=1\r\n");
			direct=0;			//设置运行方向标志
			MotorStart(7,1,700-1,25-1);	       //电机启动
		}
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//清空串口2接收数组		
		USART2_RX_LEN=0;  			//串口2状态清零
		
		
		TIM10_Init(64000,65000);         //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);        //清除中断标志位	 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))) //等待定时时间到，时间到跳出循环   
		{		
				//光电限位
//				if((0==GD7_ZZ)&&(1==direct))  //起来
//				{
//					u2_printf("\r\n0==GD7_ZZ\r\n");
//					break;	
//				}
//				if((0==GD7_CS)&&(0==direct))     //落下
//				{
//					u2_printf("\r\n0==GD7_CS\r\n");
//					break;						
//				}
			
				//电机故障、故障诊断
//				if(1==PCF8574_ReadBit(1))        
//				{						
//					u2_printf("\r\nMotor7_Alm\r\n");
//					break;		             
//				}															
		}				  
		MotorStop(7);     //电机停止
		TIM10_Stop();       //关闭定时器    
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //清除中断标志位	
		u2_printf("\r\nMotor_7_STOP\r\n");
}


/***********************************************************************
 函数名      ：WriteInU2(void)  
 函数功能    ：写入串口2函数
 输入        ：无
 输出        ：无                           
************************************************************************/
void WriteInU2(char *p)
{
	u8 len=strlen(p);
	u8 i;
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);//清空串口2接收数组
	for(i=0;i<len;i++)
	{
	  USART2_RX_BUF[i]=p[i];		//循环将数据写入串口2接收数组
	}	
}
/***********************************************************************
 函数名      ：Fun_LD(void)  
 函数功能    ：联动测试函数
 输入        ：无
 输出        ：无                           
************************************************************************/
void Fun_LD(void)
{
	//左翻
	WriteInU2("ZFS");		
	Fun_ZF();     //左翻身	
	delay_ms(1000);
	Fun_ZBH();   //左背部护理	
	delay_ms(1000);
	Fun_ZBH();   //左背部护理复位	
	delay_ms(1000);
	Fun_ZYH();  //左腰部护理
	delay_ms(1000);
	Fun_ZYH();  //左腰部护理复位	
	delay_ms(1000);
	WriteInU2("ZFX");
	Fun_ZF();           //左翻身复位
	delay_ms(1000);

	//右翻
	WriteInU2("YFS");
	Fun_YF();          //右翻身
	delay_ms(1000);
	Fun_YBH();  //右背部护理
	delay_ms(1000);
	Fun_YBH();  //右背部护理复位
	delay_ms(1000);
	Fun_YYH(); //右腰部护理
	delay_ms(1000);
	Fun_YYH(); //右腰部护理复位
	delay_ms(1000);
	WriteInU2("YFX");
	Fun_YF();          //右翻身复位
	delay_ms(1000);
	
	//上曲腿
	WriteInU2("SQTS");
	Fun_SQT();              //上曲腿
	delay_ms(1000);
	WriteInU2("SQTX");
	Fun_SQT();              //上曲腿复位
	delay_ms(1000);
	
	//形成坐姿-支背、下曲腿、坐便器、小桌子
	
	//支背
	WriteInU2("ZBS");
	Fun_ZB();                //支背
	delay_ms(1000);
	
	//下曲腿
	WriteInU2("XQTX");
	Fun_XQT();            //下曲腿	
	delay_ms(1000);
	
	//坐便器
	Fun_ZBQ(0);            //坐便器打开
	delay_ms(1000);
	
	//称重传感器
	Fun_CZ1();	

	//自动冲洗
	Fun_ZDCX();
	delay_ms(1000);
	
	//自动烘干	
	Fun_ZDHG();
	delay_ms(1000);

	Fun_ZBQ(1);            //坐便器关闭
	delay_ms(1000);
	
	//收线推杆伸出
	ZBQ_Flag=1;		//设置状态标志位
	RELAY6=1;                   //继电器得电
	Fun_ZBTG(1,ZBDTG_Lim);           //收线推杆伸出	
	RELAY6=0;

	//收线
	ZBQ_Flag=1;		//设置状态标志位
	RELAY6=1;                  //继电器得电
	Fun_ZBD(1);
	RELAY6=0;   
	delay_ms(1000);

	//收线推杆缩回
	ZBQ_Flag=1;		//设置状态标志位
	RELAY6=1;                   //继电器得电
	Fun_ZBTG(0,ZBDTG_Lim);           //收线推杆伸出	
	RELAY6=0;
	delay_ms(1000);
	
	//小桌子
	WriteInU2("YLS");
	Fun_YL1();               //小桌子靠近
	delay_ms(1000);
	WriteInU2("YLX");
	Fun_YL1();               //小桌子后退
	delay_ms(1000);	
	
	
	WriteInU2("XQTS");
	Fun_XQT();            //下曲腿复位
	delay_ms(1000);
	
	WriteInU2("ZBX");
	Fun_ZB();                //支背复位

	ZB_Flag=0;               //支背
	SQT_Flag=0;              //上曲腿
	XQT_Flag=0;              //下曲腿
	ZF_Flag=0;               //左翻
	YF_Flag=0;               //右翻
	ZBH_Flag=0;              //左背部护理
	YBH_Flag=0;              //右背部护理
	ZYH_Flag=0;              //左腰部护理
	YYH_Flag=0;              //右腰部护理
	ZBQ_Flag=0;              //坐便器
	ZDZBQ_Flag=0;            //自动坐便器
	YL_Flag=0;               //就餐娱乐一体桌
}


/***********************************************************************
 函数名      ：Fun_HL_ZB(void)  
 函数功能    ：护栏支背按键联动
 输入        ：无
 输出        ：无
                           
************************************************************************/
void Fun_HL_ZB(void)
{
	static u8 zbjx_flag; //判断支背是否运行到极限位置，若是发送极限位置图片
	u8 direct,key;
	u16 arr_now;               //当前一次运行脉冲数，用于脉冲累计 
	u8 len;	                   //接受的字符串长度
//实现上位机实时显示护理床当前运动状态
	static u8 k=0;            //发送第k张图片指令
	u8 j=0;	
	u16 arr_send;             //当前一次运行脉冲数
	static u8 kj;
	strcpy((char *)RX_BUF,(const char *)"HLZB");
	//联锁功能，只有在左右翻身功能复位后，才能进行支背
	if((ZF_Flag==0)&&(YF_Flag==0)&&(SD_Flag==1))
	{					
		ZB_Dir_flag=!ZB_Dir_flag;    //支背方向标志位
		if(ZB_Dir_flag==1)
		{
			if(Ang_To_Arr_ZB(ZB_Lim)>ZB_Runed)  //上行时，比较值为上行极限装载值与校准后的当量装载值的差值，两个差值不能为0
			{
				direct=1;			//设置运行方向标志
				if(ZB_Flag==0)
				{
					ZB_Flag=1;		//设置状态标志位
					W25QXX_Write((u8*)&ZB_Flag,35,1);		//将状态标志位写入flash
					delay_ms(200);
					u2_printf("ZB_flag==1");
					delay_ms(200);
					u2_printf("HLZBKS");
					delay_ms(200);
					u2_printf("CT_ZB1");
					delay_ms(200);
				}
				MotorStart(1,1,0,0);      //支背上行
				u2_printf("*%s*M1*Z*/*/**",RX_BUF);		//串口2反馈
				TIM10_Init(Ang_To_Arr_ZB(ZB_Lim)-ZB_Runed,65000);	   //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
			}
		}
		if(ZB_Dir_flag==0)
		{
			if(ZB_Runed>0)    //下行时，比较值为校准后的当量装载值与0,且不能为0
			{
				direct=0;			//设置运行方向标志
				if(zbjx_flag==1)
				{
					zbjx_flag=0;			//设置极限状态标志位
					u2_printf("CT_ZB20");
					delay_ms(200);
				}
				MotorStart(1,0,0,0);								//支背下行
				u2_printf("*%s*M1*F*/*/**",RX_BUF);		//串口2反馈
				TIM10_Init(ZB_Runed,65000);		   //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
			}
		}				
		
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//清空串口2接收数组		
		USART2_RX_LEN=0; 			//串口2状态清零
		memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//清空串口4接收数组		
		UART4_RX_LEN=0;				  //串口4状态清零
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);             //清除中断标志位	 	
		
		if(((ZB_Runed!=Ang_To_Arr_ZB(ZB_Lim))&&(1==direct))||((0!=ZB_Runed)&&(0==direct)))
		{
			while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))  //等待定时时间到，时间到跳出循环 
			{			
				
				//停止指令
				if(USART2_RX_LEN&0x8000)
				{
					len=USART2_RX_LEN&0x3fff;	//获取串口2接收数组字符长度				
					USART2_RX_BUF[len]=0;			//串口2数组末尾添"0"
					if((strstr((const char *)USART2_RX_BUF,(const char *)"STOP"))||
						(strstr((const char *)USART2_RX_BUF,(const char *)"HLZB"))||
						(strstr((const char *)USART2_RX_BUF,(const char *)"BackGB")))   //若接收到Stop,则跳出循环	
					{
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);//清空串口2接收数组			
						USART2_RX_LEN=0;			//串口2状态清零
						break;
					}
					else 
					{
						u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数								
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);		//清空串口2接收数组	
						USART2_RX_LEN=0;			//串口2状态清零
					}						
				}
				if(UART4_RX_LEN&0x8000)
				{
					len=UART4_RX_LEN&0x3fff;		//获取串口4接收数组字符长度			
					UART4_RX_BUF[len]=0;				//串口4数组末尾添"0"
					if((strstr((const char *)UART4_RX_BUF,(const char *)"STOP"))||
						(strstr((const char *)UART4_RX_BUF,(const char *)"HLZB"))||
						(strstr((const char *)UART4_RX_BUF,(const char *)"BackGB")))   //若接收到Stop,则跳出循环	
					{
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//清空串口4接收数组		
						UART4_RX_LEN=0;				  //串口4状态清零
						break;
					}
					if(strstr((const char *)UART4_RX_BUF,(const char *)"SEND OK"))
					{	}
					else 
					{
						u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数								
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//清空串口4接收数组		
						UART4_RX_LEN=0;				  //串口4状态清零
					}						
				}
				//发送图片指令
				 arr_send=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//获取当前寄存器运行装载值
				if(direct==1)
				{
					j=(ZB_Runed+arr_send)/(Ang_To_Arr_ZB(ZB_Lim)/19);		//图片序号计算
				}
				else
				{
					j=abs(ZB_Runed,arr_send)/(Ang_To_Arr_ZB(ZB_Lim)/19);		//图片序号计算
				}			
				k=ZB_Pic;			
				if(	k!=j)
				{
					kj=abs(k,j);												
					if(kj<2)
					{
						k=j;	ZB_Pic=k;
						if((1<ZB_Pic)&&(ZB_Pic<20))
						{
							u2_printf("CT_ZB%d",ZB_Pic);		//串口2发送动画图片指令	
						}							
					}				
				}							
			}
			MotorStop(1);          //电机停止
			u2_printf("*%s*M1*T*/*/**",RX_BUF);		//串口2反馈
			TIM10_Stop();          //关闭定时器
			//判断复位
			if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))&&(direct==0))   //判断是否处于复位状态，复位状态的前提是下行的定时器走完
			{				
				arr_now=0;         //此时处于复位状态，将状态值都设为0；
				ZB_Flag=0;				//设置状态标志位
				W25QXX_Write((u8*)&ZB_Flag,35,1);		//将状态标志位写入flash
				delay_ms(200);
				u2_printf("ZB_flag==0");
			}		
			else
			{
				arr_now=__HAL_TIM_GET_COUNTER(&TIM10_Handler);    //获取当前计数值arr_now				
				ZB_Flag=1;					//设置状态标志位				 
			}	
			//通过上下行判断脉冲累计
			if(	direct==1)        //如果是支背上行，则用+
			{
				if(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))
				{  
					ZB_Runed=Ang_To_Arr_ZB(ZB_Lim); 				//设置已运行脉冲值为极限值
					zbjx_flag=1; 	//设置极限状态标志位
					delay_ms(200);
					u2_printf("CT_ZB20");		
					delay_ms(200);
					u2_printf("HLZBJX");
				}
				else
				{  ZB_Runed=ZB_Runed+arr_now;	}					//设置已运行脉冲值=上一次运行脉冲值+此次运行脉冲值	
			}
			else                //如果是支背下行，则用-
			{
				if(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))
				{	
					ZB_Runed=0;				//已运行脉冲值设为0
					delay_ms(200);
					u2_printf("CT_ZB1"); 
					delay_ms(200);
					u2_printf("HLZBFW");					
				}
				else
				{
					ZB_Runed=ZB_Runed-arr_now;		//设置已运行脉冲值=上一次运行脉冲值-此次运行脉冲值
				}						
			}
			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位	 								
		}
	}
	else
	{
		LedAlm(100,"HLZBGS");
	}	
}

/***********************************************************************
 函数名      ：Fun_HL_ZF(void)  
 函数功能    ：护栏左翻身
 输入        ：无
 输出        ：无
                           
************************************************************************/
void Fun_HL_ZF(void)
{
	u8 direct,key;
	u16 arr_now;              //当前一次运行脉冲数，用于脉冲累计
	u8 len;                   //接受的字符串长度
	static u8 motor5_run_flag;   //判断小侧翻是否已经动作，若动作该位置1 

	//实现上位机实时显示护理床当前运动状态     
	static u8 M345_Start;     //345电机从初始位置运动
	static u8 M345_End;       //345电机运行到上极限位置标志位  
	static u8 k=0,m=0;
	u8 mn;
	u8 kj;
	u8 j=0,n=0;
	u16 arr_send,arr_send1;	 //当前一次运行脉冲数	
	strcpy((char *)RX_BUF,(const char *)"HLZF");
	//联锁功能，只有在支背、上下曲腿、座便、桌子复位后，才能执行左翻身功能
	if((SD_Flag==1)&&(ZB_Flag==0)&&(YF_Flag==0)&&(SQT_Flag==0)&&(XQT_Flag==0)&&(ZBQ_Flag==0)&&(YL_Flag==0)&&(ZBH_Flag==0)&&(ZYH_Flag==0))
	{					
		if(ZF_Flag==0)   //如果复位到初始状态，才执行小侧翻左翻起
		{
			if((strstr((const char *)USART2_RX_BUF,(const char *)"HLZF"))||(strstr((const char *)USART2_RX_BUF,(const char *)"BodyLeftGB"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"HLZF"))||(strstr((const char *)UART4_RX_BUF,(const char *)"BodyLeftGB")))
			{
				//5号侧翻起	
				memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			//清空串口2接收数组
				USART2_RX_LEN=0;			//串口2状态清零
				memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//清空串口4接收数组		
				UART4_RX_LEN=0;				  //串口4状态清零
				delay_ms(200);
				u2_printf("HLZFKS");
				delay_ms(200);
				u2_printf("ZF_flag=1");				
				delay_ms(200);
				u2_printf("CT_ZCF1");
				delay_ms(200);
			  motor5_run_flag=1;		//设置状态标志位		
				ZF_Flag=1;		//设置状态标志位
				W25QXX_Write((u8*)&ZF_Flag,33,1);					//将状态标志位写入flash	
				MotorStart(5,1,1400-1,25-1);	         			 //5号电机启动
				u2_printf("*%s*M5*Z*0*/**",RX_BUF);		//串口2反馈
				TIM10_Init(Ang_To_Arr_ZYFS(ZF_Lim),65000);     //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
				__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);               //清除中断标志位
				while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) )
				{					
					//光电限位
					if((0==GD5_ZFZZ)&&(1==ZF_Flag))  //运行时碰到光电开关，跳出循环 
					{			   										
						delay_us(100);
						if(0==GD5_ZFZZ)
						{
							u2_printf("GD5ZFZZ");
							break;			
						}								
					}
					  //判断有没有收到上位机指令		
					if(USART2_RX_LEN&0x8000)
					{
						u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数	
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//清空串口2接收数组		
						USART2_RX_LEN=0;			 //串口2状态清零												
					}
					if(UART4_RX_LEN&0x8000)
					{
						u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数	
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//清空串口4接收数组		
						UART4_RX_LEN=0;							  //串口4状态清零									
					}
					//电机故障、故障诊断
//					if(1==Motor5_Alm)       
//					{						
//						delay_us(100);
//						if(1==Motor5_Alm)
//						{
//							ZF5_GZ=1;
//							u2_printf("*%s*M5*Z*1*/**",RX_BUF);
//							u2_printf("ZFGZ5");
//							Fun_GZCL();
//							break;
//						}								
//					}						
					//发送图片指令
					arr_send1=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//获取当前寄存器运行装载值
					n=arr_send1/(Ang_To_Arr_ZYFS(ZF_Lim)/9);
					m=ZCF_Pic;
					if(m!=n)
					{
						mn=abs(m,n);					
						if(mn<2)
						{
							m=n;	ZCF_Pic=m;
							if((1<ZCF_Pic)&&(ZCF_Pic<10))
							{
								u2_printf("CT_ZCF%d",ZCF_Pic);			//串口2发送动画图片指令
							}								
						}
					}					
				}					      
				MotorStop(5);         //电机停止
				u2_printf("*%s*M5*T*0*/**",RX_BUF);		//串口2反馈
				TIM10_Stop();         //定时器关闭
				__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //清除中断标志位
				delay_ms(200);
				u2_printf("CT_ZCF10");
				delay_ms(200);
				Motor4_BC(0,1400,1400-1,25-1);//调用补偿函数
			}	
		}
	
		//翻身345电机动作	
		if(1==ZF_Flag)
		{
			ZF_Dir_flag=!ZF_Dir_flag;		//设置状态标志位
			if(ZF_Dir_flag==1)    //左翻起
			{				
				if(Ang_To_Arr_ZYFS(ZF_Lim)>ZF_Runed)
				{
				   //345联动左翻起				
					 direct=1;			//设置运行方向标志
					 if(M345_Start==0)
					 {
						 M345_Start=1;
						 u2_printf("CT_ZF1");
						 delay_ms(200);
					 }
					MotorStart(3,0,1400-1,25-1);	     //3号电机启动			
					MotorStart(4,0,(1400-1)*1.2,25-1); //4号电机启动
					MotorStart(5,0,1400-1,25-1);			 //5号电机启动
					if(1==motor5_run_flag)
					{
						motor5_run_flag=0;		//设置状态标志位
						u2_printf("*M5JS*M345*ZZZ*000*/**");		//串口2反馈
					}
					else
					{
						u2_printf("*%s*M345*ZZZ*000*/**",RX_BUF);		//串口2反馈
					}
					TIM10_Init(Ang_To_Arr_ZYFS(ZF_Lim)-ZF_Runed,65000);	   //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz							 
				}
			}
			else          //左翻落
			{				
				if(ZF_Runed>0)
				{
				   //345联动左翻落
				   direct=0;			//设置运行方向标志
					if(M345_End==1)
					 {
						 M345_End=0;
						 u2_printf("CT_ZF8");
						 delay_ms(200);
					 }
					MotorStart(3,1,1400-1,25-1);	     //3号电机启动
					MotorStart(4,1,(1400-1)*1.2,25-1);		 //4号电机启动	
					MotorStart(5,1,1400-1,25-1);			 //5号电机启动	
					u2_printf("*%s*M345*FFF*000*/**",RX_BUF);		//串口2反馈
				   TIM10_Init(ZF_Runed,65000);	             //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz		
				} 
			}
		}
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			//清空串口2接收数组
		USART2_RX_LEN=0;			 //串口2状态清零
		memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);				//清空串口4接收数组	
		UART4_RX_LEN=0;				  //串口4状态清零
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);              //清除中断标志位
		
		if(((ZF_Runed!=Ang_To_Arr_ZYFS(ZF_Lim))&&(1==direct))||((0!=ZF_Runed)&&(0==direct)))
		{			
			while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))   //等待定时时间到，时间到跳出循环
			{
				//光电限位
				if(((0==GD3_CS)||(0==GD4_CS))&&(0==direct))   //如果碰到光电开关，跳出循环，停止运行
				{
					delay_us(100);
					if((0==GD3_CS)&&(1==GD4_CS))
					{
						MotorStop(3);  
					}
					if((1==GD3_CS)&&(0==GD4_CS))
					{
						MotorStop(4);
					}
					if((0==GD3_CS)&&(0==GD4_CS))
					{
						u2_printf("GD3CS");
						delay_ms(200);
						u2_printf("GD4CS");
						break;					
					}
				}
				if(((0==GD3_ZFZZ)||(0==GD4_ZFZZ))&&(1==direct))   //如果碰到光电开关，跳出循环，停止运行
				{
					delay_us(100);
					if((0==GD3_ZFZZ)||(0==GD4_ZFZZ))          //如果碰到光电开关，跳出循环，停止运行
					{							
						if(0==GD3_ZFZZ)
						{
							u2_printf("GD3ZFZZ");
						}
						if(0==GD4_ZFZZ)
						{
							u2_printf("GD4ZFZZ");
						}
						break;
					}
				}
				//停止指令
				if(USART2_RX_LEN&0x8000)
				{
					len=USART2_RX_LEN&0x3fff;		//获取串口2接收数组字符长度			
					USART2_RX_BUF[len]=0;			//串口2数组末尾添"0"
					if((strstr((const char *)USART2_RX_BUF,(const char *)"BodyLeftGB"))||
						(strstr((const char *)USART2_RX_BUF,(const char *)"STOP"))||
							(strstr((const char *)USART2_RX_BUF,(const char *)"HLZF")))  //若接收到Stop,则跳出循环	
					{
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//清空串口2接收数组		
						USART2_RX_LEN=0; 			//串口2状态清零
						break;
					} 
					else 
					{
						u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数	
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//清空串口2接收数组		
						USART2_RX_LEN=0;			//串口2状态清零
					}												
				}
				if(UART4_RX_LEN&0x8000)
				{
					len=UART4_RX_LEN&0x3fff;		//获取串口4接收数组字符长度			
					UART4_RX_BUF[len]=0;				//串口4数组末尾添"0"
					if((strstr((const char *)UART4_RX_BUF,(const char *)"BodyLeftGB"))||
						(strstr((const char *)UART4_RX_BUF,(const char *)"STOP"))||
							(strstr((const char *)UART4_RX_BUF,(const char *)"HLZB")))  //若接收到Stop,则跳出循环	
					{
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//清空串口4接收数组		
						UART4_RX_LEN=0;				  //串口4状态清零
						break;
					} 
					if(strstr((const char *)UART4_RX_BUF,(const char *)"SEND OK"))
					{	}
					else 
					{
						u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数	
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);				//清空串口4接收数组	
						UART4_RX_LEN=0;				  //串口4状态清零
					}												
				}
				//电机故障、故障诊断
//				if((1==Motor3_Alm)||(1==Motor4_Alm)||(1==Motor5_Alm))         
//				{						
//					delay_us(100);
//					if(1==Motor3_Alm)
//					{
//						ZF3_GZ=1;
//						u2_printf("*%s*M3*/*1*/**",RX_BUF);
//						delay_ms(200);
//						u2_printf("ZFGZ3");
//						Fun_GZCL();
//						break;				
//					}
//					if(1==Motor4_Alm)
//					{
//						ZF4_GZ=1;
//						u2_printf("*%s*M4*/*1*/**",RX_BUF);
//						delay_ms(200);
//						u2_printf("ZFGZ4");
//						Fun_GZCL();
//						break;				
//					}
//					if(1==Motor5_Alm)
//					{
//						ZF5_GZ=1;
//						u2_printf("*%s*M5*/*1*/**",RX_BUF);
//						delay_ms(200);
//						u2_printf("ZFGZ5");
//						Fun_GZCL();
//						break;
//					}								             
//				}									
				//发送动画指令
				arr_send=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//获取当前寄存器运行装载值
				if(direct==1)
				{
					j=(ZF_Runed+arr_send)/(Ang_To_Arr_ZYFS(ZF_Lim)/7);		//图片序号计算
				}
				else
				{
					j=abs(ZF_Runed,arr_send)/(Ang_To_Arr_ZYFS(ZF_Lim)/7);		//图片序号计算
				}
				k=ZF_Pic;
				if(	k!=j)
				{	
					kj=abs(k,j);
					if(kj<2)
					{
						k=j;   ZF_Pic=k;
						if((1<ZF_Pic)&&(ZF_Pic<8))
						{
							u2_printf("CT_ZF%d",ZF_Pic);		//串口2发送动画图片指令	
						}							
					}				
				}					
			}	
			//电机停止
			MotorStop(3);   
			MotorStop(4);  
			MotorStop(5);   
			u2_printf("*%s*M345*TTT*000*/**",RX_BUF);		//串口2反馈
			TIM10_Stop();         //定时器关闭
			//判断复位
			if(((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))||(0==GD3_CS)||(0==GD4_CS))&&(direct==0))  //判断是否到达复位状态
			{
				arr_now=0; 		 //此时处于复位状态，将状态值都设为0；
				ZF_Flag=0;		//设置状态标志位
			}					
			else
			{					
				arr_now=__HAL_TIM_GET_COUNTER(&TIM10_Handler);      //获取当前计数值arr_now	
			}
			//通过上下行判断脉冲累计
			if(direct==1)       //上行，则用+
			{
				if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))||(0==GD3_ZFZZ)||(0==GD4_ZFZZ))  //向上运行到极限位置
				{
					ZF_Runed=Ang_To_Arr_ZYFS(ZF_Lim);					//设置已运行脉冲值为极限值				
					M345_End=1;	 										
					delay_ms(200);
					u2_printf("CT_ZF8");
					delay_ms(200);
					u2_printf("HLZFJX");
				}
				else
				{
					ZF_Runed=ZF_Runed+arr_now;		//设置已运行脉冲值=上一次运行脉冲值+此次运行脉冲值
				}		
			}	
			else                //下行，则用-
			{
				if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))||(0==GD3_CS)||(0==GD4_CS))      //向下运行到极限位置
				{						
					ZF_Runed=0;			//已运行脉冲值设为0
					M345_Start=0;											
					delay_ms(200);
					u2_printf("CT_ZF1");
				}
				else
				{
					ZF_Runed=ZF_Runed-arr_now;			//设置已运行脉冲值=上一次运行脉冲值-此次运行脉冲值
				}
			}					
			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);        //清除中断标志位
			
			//若定时时间到但是光电没到，则电机再运行一段距离，到达光电开关位置（光电开关安装后打开此段，并将上面的清除中断删除）
//			if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))&&((1==GD3_CS)||(1==GD4_CS))&&(direct==0)&&(ZF_Flag==1))
//			{   			
//				if((1==GD3_CS)&&(0==GD4_CS))        //光电3没到位
//				{
//					MotorStart(3,1,1400-1,25-1);       //3号电机启动
//					u2_printf("*%s*M3*F*0*/**",RX_BUF);
//					TIM10_Init(add_arr,65000);                    //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //清除中断标志位	 	
//					while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))
//					{			
//						if(0==GD3_CS)  //运行时碰到光电开关，跳出循环 
//						{
//							delay_us(100);
//							if(0==GD3_CS) 
//							{
//								ZF_Flag=0;							
//								u2_printf("GD3CS");			
//								break;	
//							}								
//						}
//					}			
//					MotorStop(3);         //电机停止
//					u2_printf("*%s*M3*T*0*/**",RX_BUF);
//					TIM10_Stop();         //定时器关闭
//					if(0==GD3_CS)
//					{
//						u2_printf("*%s*GD3CS*/*0*/**",RX_BUF);
//					}
//					else
//					{
//						u2_printf("*%s*GD3CS*/*1*/**",RX_BUF);
//					}
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //清除中断标志位
//				}
//				if((0==GD3_CS)&&(1==GD4_CS))   //光电4没到位
//				{
//					MotorStart(4,1,1400-1,25-1);  		 //4号电机启动
//					u2_printf("*%s*M4*F*0*/**",RX_BUF);
//					TIM10_Init(add_arr,65000);              //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //清除中断标志位	 	
//					while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))
//					{			
//						if(0==GD4_CS)  //运行时碰到光电开关，跳出循环 
//						{
//							delay_us(100);
//							if(0==GD4_CS) 
//							{
//								ZF_Flag=0;				
//								u2_printf("GD4CS");
//								break;
//							}
//						}
//					}			
//					MotorStop(4);     //电机停止
//					u2_printf("*%s*M4*T*0*/**",RX_BUF);
//					TIM10_Stop();     //定时器关闭
//					if(0==GD4_CS)
//					{
//						u2_printf("*%s*GD4CS*/*0*/**",RX_BUF);
//					}
//					else
//					{
//						u2_printf("*%s*GD4CS*/*1*/**",RX_BUF);
//					}
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //清除中断标志位				
//				}
//				if((1==GD3_CS)&&(1==GD4_CS))   //光电3和4都没到位
//				{
//					MotorStart(3,1,(1400-1),25-1);     //3号电机启动
//					MotorStart(4,1,(1400-1)*1.2,25-1);		 //4号电机启动
//					MotorStart(5,1,1400-1,25-1);			 //5号电机启动
//					u2_printf("*%s*M345*FFF*000*/**",RX_BUF);
//					TIM10_Init(add_arr,65000);                //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //清除中断标志位	 	
//					while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))
//					{			
//						if((0==GD3_CS)||(0==GD4_CS))  //运行时碰到光电开关，跳出循环 
//						{
//							delay_us(100);
//							if((0==GD3_CS)||(0==GD4_CS))
//							{
//								if((0==GD3_CS)&&(1==GD4_CS))
//								{
//									MotorStop(3);
//								}
//								if((1==GD3_CS)&&(0==GD4_CS))
//								{
//									MotorStop(4);
//								}
//								if((0==GD3_CS)&&(0==GD4_CS))
//								{
//									ZF_Flag=0;				
//									u2_printf("GD3CS");
//									delay_ms(200);
//									u2_printf("GD4CS");
//									break;
//								}
//							}								
//						}
//					}			
//					MotorStop(3);    //电机停止
//					MotorStop(4);
//					MotorStop(5);
//					u2_printf("*%s*M345*TTT*000*/**",RX_BUF);
//					TIM10_Stop();    //定时器关闭
//					if((1==GD3_CS)||(1==GD4_CS))
//					{
//						if(1==GD3_CS)
//						{
//							u2_printf("*%s*GD3CS*/*1*/**",RX_BUF);
//						}
//						if(1==GD4_CS)
//						{
//							u2_printf("*%s*GD4CS*/*1*/**",RX_BUF);
//						}						
//					}
//					if((0==GD3_CS)||(0==GD4_CS))
//					{
//						if(0==GD3_CS)
//						{
//							u2_printf("*%s*GD3CS*/*0*/**",RX_BUF);
//						}
//						if(0==GD4_CS)
//						{
//							u2_printf("*%s*GD4CS*/*0*/**",RX_BUF);
//						}						
//					}
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位	
//				}
//			}
			//侧翻复位
			if((ZF_Flag==0)&&(0==direct))     //345联动复位到初始状态，才复位5号电机
			{			
				//5号侧翻复位
				memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//清空串口2接收数组		
				USART2_RX_LEN=0;			//串口2状态清零
				memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//清空串口4接收数组		
				UART4_RX_LEN=0;				  //串口4状态清零
//				Motor4_BC(1,1400,1400-1,25-1);//调用补偿函数	
				ZF_Runed=0;				//已运行脉冲值设为0
				delay_ms(200);
				u2_printf("CT_ZCF10");
				delay_ms(200);
				MotorStart(5,0,1400-1,25-1);         			 //5号电机启动
				u2_printf("*%s*M5*F*0*/**",RX_BUF);					//串口2反馈
				TIM10_Init(Ang_To_Arr_ZYFS(ZF_Lim),65000);    //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
				__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);              //清除中断标志位
				while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) )
				{				
					//光电限位
					if((0==GD5_CS)&&(0==ZF_Flag))    //碰到光电开关跳出循环，电机停转 
					{								
						delay_us(100);
						if(0==GD5_CS)
						{
							u2_printf("GD5CS");
							break;			
						}								
					}
					  //判断有没有收到上位机指令		
					if(USART2_RX_LEN&0x8000)
					{
						u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数	
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//清空串口2接收数组		
						USART2_RX_LEN=0;					//串口2状态清零										
					}	
					if(UART4_RX_LEN&0x8000)
					{
						u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数	
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//清空串口4接收数组			
						UART4_RX_LEN=0;							  //串口4状态清零									
					}
					//电机故障、故障诊断
//					if(1==Motor5_Alm)         
//					{
//						delay_us(100);
//						if(1==Motor5_Alm)
//						{
//							ZF5_GZ=1;
//							u2_printf("*%s*M5*F*1*/**",RX_BUF);
//							u2_printf("ZFGZ5");
//							Fun_GZCL();
//							break;
//						}								
//					}						
					//发送动画指令
					arr_send1=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//获取当前寄存器运行装载值
					n=arr_send1/(Ang_To_Arr_ZYFS(ZF_Lim)/9);
					n=9-n;	
					m=ZCF_Pic;
					if(	m!=n)
					{			
						mn=abs(m,n);
						if(mn<2)
						{
							m=n;    ZCF_Pic=m;
							if((1<ZCF_Pic)&&(ZCF_Pic<10))
							{
							u2_printf("CT_ZCF%d",ZCF_Pic);		//串口2发送动画图片指令
							}								
						}				
					}	
				}      
				MotorStop(5);       //电机停止
				u2_printf("*%s*M5*T*0*/**",RX_BUF);		//串口2反馈
				TIM10_Stop();       //定时器关闭
				__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //清除中断标志位
				ZF_Flag=0;		//设置状态标志位
				W25QXX_Write((u8*)&ZF_Flag,33,1);		//将状态标志位写入flash
				delay_ms(200);
				u2_printf("CT_ZCF1");
				delay_ms(200);
				u2_printf("ZF_flag==0");				
				delay_ms(200);
				u2_printf("HLZFFW");
				//若定时时间到但是光电没到，则电机再运行一段距离，到达光电开关位置（光电开关安装后打开此段，并将上面的清除中断删除）
//				if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))&&(1==GD5_CS)&&(direct==0)&&(0==ZF_Flag))
//				{
//					MotorStart(5,0,1400-1,25-1);			 //5号电机启动
//					u2_printf("*%s*M5*F*0*/**",RX_BUF);
//					TIM10_Init(add_arr,65000);   //打开定时器
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位	 	
//					while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))
//					{			
//						if(0==GD5_CS)  //运行时碰到光电开关，跳出循环 
//						{
//							delay_us(100);
//							if(0==GD5_CS)
//							{
//								u2_printf("GD5CS");
//								break;		
//							}								
//						}
//					}			
//					MotorStop(5);
//					u2_printf("*%s*M5*T*0*/**",RX_BUF);
//					TIM10_Stop();       //定时器关闭
//					if(0==GD5_CS)
//					{
//						u2_printf("*%s*GD5CS*/*0*/**",RX_BUF);
//					}
//					else
//					{
//						u2_printf("*%s*GD5CS*/*1*/**",RX_BUF);
//					}
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位	
//				}			
			}				
		}
	}
	else
	{
		LedAlm(100,"HLZFGS");
	}	
}

/***********************************************************************
 函数名      ：Fun_HL_YF(void)  
 函数功能    ：护栏右翻身
 输入        ：无
 输出        ：无
                           
************************************************************************/
void Fun_HL_YF(void)
{
	u8 direct,key;
	u16 arr_now;              //当前一次运行脉冲数，用于脉冲累计
	u8 len;                   //接收的字符串长度
	static u8 motor5_run_flag;   //判断小侧翻是否已经动作，若动作该位置1 
	//实现上位机实时显示护理床当前运动状态
	static u8 k=0,m=0;
	static u8 M345R_Start;    //345电机从初始位置启动
	static u8 M345R_End;      //345电机运行到上极限位置
	u8 mn;
	u8 kj;
	u8 j=0,n=0;
	u16 arr_send,arr_send1;	  //当前一次运行脉冲数	
	strcpy((char *)RX_BUF,(const char *)"HLYF");
	//联锁功能，只有在支背、上下曲腿、座便、桌子复位后，才能执行右翻身功能
	if((SD_Flag==1)&&(ZB_Flag==0)&&(ZF_Flag==0)&&(SQT_Flag==0)&&(XQT_Flag==0)&&(ZBQ_Flag==0)&&(YL_Flag==0)&&(YBH_Flag==0)&&(YYH_Flag==0))
	{			
		if(YF_Flag==0)   //如果复位到初始状态，才执行左翻起
		{
			if((strstr((const char *)USART2_RX_BUF,(const char *)"BodyRightGB"))||(strstr((const char *)USART2_RX_BUF,(const char *)"HLYF"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"BodyRightGB"))||(strstr((const char *)UART4_RX_BUF,(const char *)"HLYF")))
			{
			  //5号侧翻起
				memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//清空串口2接收数组		
				USART2_RX_LEN=0;		 	//串口2状态清零
				memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//清空串口4接收数组			
				UART4_RX_LEN=0;				  //串口4状态清零
				delay_ms(200);
				u2_printf("HLYFKS");
				delay_ms(200);
				u2_printf("YF_flag==1");
				delay_ms(200);
				u2_printf("CT_YCF1");
				delay_ms(200);
				motor5_run_flag=1;		//设置状态标志位
				YF_Flag=1;		//设置状态标志位
				W25QXX_Write((u8*)&YF_Flag,34,1);					//将状态标志位写入flash
				MotorStart(5,0,1400-1,25-1);	       			 //5号电机启动
				u2_printf("*%s*M5*Z*0*/**",RX_BUF);		//串口2反馈
				TIM10_Init(Ang_To_Arr_ZYFS(YF_Lim),65000);    //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	                   //打开定时器
				__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);               //清除中断标志位
				while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) )
				{					
					//光电限位
					if((0==GD5_YFZZ)&&(1==YF_Flag))                      //运行时碰到光电开关，跳出循环 
					{			   										
						delay_us(100);
						if(0==GD5_YFZZ)
						{
							u2_printf("GD5YFZZ");
							break;		
						}								
					}
					  //判断有没有收到上位机指令		
					if(USART2_RX_LEN&0x8000)
					{
						u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数	
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);//清空串口2接收数组			
						USART2_RX_LEN=0;								//串口2状态清零							
					}
					if(UART4_RX_LEN&0x8000)
					{
						u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数	
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//清空串口4接收数组		
						UART4_RX_LEN=0;						  //串口4状态清零										
					}
					//电机故障、故障诊断
//					if(1==Motor5_Alm)         
//					{		
//						delay_us(100);
//						if(1==Motor5_Alm)  
//						{
//							YF5_GZ=1;
//							u2_printf("*%s*M5*Z*1*/**",RX_BUF);
//							u2_printf("YFGZ5");
//							Fun_GZCL();
//							break;	
//						}								
//					}											 
					//发送图片指令
					arr_send1=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//获取当前寄存器运行装载值
					n=arr_send1/(Ang_To_Arr_ZYFS(YF_Lim)/9);
					m=YCF_Pic;
					if(m!=n)
					{
						mn=abs(m,n);
						if(mn<2)
						{
							m=n;   YCF_Pic=m;
							if((1<YCF_Pic)&&(YCF_Pic<10))
							{
								u2_printf("CT_YCF%d",YCF_Pic);		//串口2发送动画图片指令
							}								
						}					
					}		
				}						      
				MotorStop(5);          //电机停止
				u2_printf("*%s*M5*T*0*/**",RX_BUF);		//串口2反馈
				TIM10_Stop();          //定时器关闭
				__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //清除中断标志位
				delay_ms(200);
				u2_printf("CT_YCF10");
				delay_ms(200);
				Motor4_BC(1,3200,1400-1,25-1);//调用补偿函数
			}	
		}

		//翻身345电机动作	
		if(1==YF_Flag)
		{
			YF_Dir_flag=!YF_Dir_flag;		//设置状态标志位
			if(YF_Dir_flag==1)
			{				
				if(Ang_To_Arr_ZYFS(YF_Lim)>YF_Runed)
				{
				   //345联动左翻起		
				   direct=1;			//设置运行方向标志
				   if(M345R_Start==0)
				   {
					   M345R_Start=1;	
					   delay_ms(200);
					   u2_printf("CT_YF1");
					   delay_ms(200);
				   }
					MotorStart(3,1,(1400-1)*2,25-1);	     //3号电机启动
					MotorStart(4,1,(1400-1)*0.8,25-1);		 //4号电机启动	
					MotorStart(5,1,1400-1,25-1);			 		//5号电机启动
					if(1==motor5_run_flag)
					{
						motor5_run_flag=0;		//设置状态标志位
						u2_printf("*M5JS*M345*ZZZ*000*/**");		//串口2反馈
					}
					else
					{
						u2_printf("*%s*M345*ZZZ*000*/**",RX_BUF);		//串口2反馈
					}					
				   TIM10_Init(Ang_To_Arr_ZYFS(ZF_Lim)-ZF_Runed,65000);   //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
				}
			}
			else
			{				
				if(YF_Runed>0)
				{
				   //345联动左翻起
				   direct=0;			//设置运行方向标志
				   if(M345R_End==1)
				   {
						M345R_End=0;
						delay_ms(200);
					    u2_printf("CT_YF8");	
					    delay_ms(200);
					}
					MotorStart(3,0,(1400-1)*2,25-1);	     //3号电机启动
					MotorStart(4,0,(1400-1)*0.8,25-1);		 //4号电机启动	
					MotorStart(5,0,1400-1,25-1);					 //5号电机启动
					u2_printf("*%s*M345*FFF*000*/**",RX_BUF);		//串口2反馈
				   TIM10_Init(YF_Runed,65000);	        //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz		
				}
			}
		}
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			//清空串口2接收数组
		USART2_RX_LEN=0;			//串口2状态清零
		memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//清空串口4接收数组		
		UART4_RX_LEN=0;				  //串口4状态清零
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);         //清除中断标志位		
		if(((YF_Runed!=Ang_To_Arr_ZYFS(YF_Lim))&&(1==direct))||((0!=YF_Runed)&&(0==direct)))
		{
			while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))  //等待定时时间到，时间到跳出循环
			{			
				//光电限位
				if(((0==GD3_CS)||(0==GD4_CS))&&(0==direct))   //如果碰到光电开关，跳出循环，停止运行
				{
					delay_us(100);
					if((0==GD3_CS)&&(1==GD4_CS))
					{
//						u2_printf("GD3CS");
						MotorStop(3);  
					}
					if((1==GD3_CS)&&(0==GD4_CS))
					{
						u2_printf("GD4CS");
						MotorStop(4);
					}
					if((0==GD3_CS)&&(0==GD4_CS))
					{
						u2_printf("GD3CS");
						delay_ms(200);
						u2_printf("GD4CS");
						break;					
					}
				}
				if(((0==GD3_YFZZ)||(0==GD4_YFZZ))&&(1==direct))           //如果碰到光电开关，跳出循环，停止运行
				{
					delay_us(100);
					if((0==GD3_YFZZ)||(0==GD4_YFZZ))          //如果碰到光电开关，跳出循环，停止运行
					{
						if(0==GD3_YFZZ)
						{
							u2_printf("GD3YFZZ");
						}
						if(0==GD4_YFZZ)
						{
							u2_printf("GD4YFZZ");
						}
						break;
					}
				}
				//停止指令
				if(USART2_RX_LEN&0x8000)
				{
					len=USART2_RX_LEN&0x3fff;		//获取串口2接收数组字符长度			
					USART2_RX_BUF[len]=0;			//串口2数组末尾添"0"
					if((strstr((const char *)USART2_RX_BUF,(const char *)"BodyRightGB"))||
						(strstr((const char *)USART2_RX_BUF,(const char *)"STOP"))||
							(strstr((const char *)USART2_RX_BUF,(const char *)"HLYF")))    //若接收到Stop,则跳出循环	
					{
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//清空串口2接收数组		
						USART2_RX_LEN=0;			//串口2状态清零
						break;
					} 
					else 
					{
						u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数	
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//清空串口2接收数组		
						USART2_RX_LEN=0;			//串口2状态清零
					}
				}
				if(UART4_RX_LEN&0x8000)
				{
					len=UART4_RX_LEN&0x3fff;			//获取串口4接收数组字符长度		
					UART4_RX_BUF[len]=0;				//串口4数组末尾添"0"
					if((strstr((const char *)UART4_RX_BUF,(const char *)"BodyRightGB"))||
						(strstr((const char *)UART4_RX_BUF,(const char *)"STOP"))||
							(strstr((const char *)UART4_RX_BUF,(const char *)"HLYF")))    //若接收到Stop,则跳出循环	
					{
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//清空串口4接收数组		
						UART4_RX_LEN=0;				  //串口4状态清零
						break;
					} 
					if(strstr((const char *)UART4_RX_BUF,(const char *)"SEND OK"))
					{	}
					else 
					{
						u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数	
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//清空串口4接收数组		
						UART4_RX_LEN=0;				  //串口4状态清零
					}
				}
				//电机故障、故障诊断
//				if((1==Motor3_Alm) || (1==Motor4_Alm) || (1==Motor5_Alm))       
//				{						
//					delay_us(100);
//					if(1==Motor3_Alm)
//					{
//						YF3_GZ=1;
//						u2_printf("*%s*M3*/*1*/**",RX_BUF);
//						delay_ms(200);
//						u2_printf("YFGZ3");
//						Fun_GZCL();
//						break;				
//					}
//					if(1==Motor4_Alm)
//					{
//						YF4_GZ=1;
//						u2_printf("*%s*M4*/*1*/**",RX_BUF);
//						delay_ms(200);
//						u2_printf("YFGZ4");
//						Fun_GZCL();
//						break;				
//					}
//					if(1==Motor5_Alm)
//					{
//						YF5_GZ=1;
//						u2_printf("*%s*M5*/*1*/**",RX_BUF);
//						delay_ms(200);
//						u2_printf("YFGZ5");
//						Fun_GZCL();
//						break;
//					}							             
//				}							
				//发送动画指令
				 arr_send=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//获取当前寄存器运行装载值
				if(direct==1)
				{
					j=(YF_Runed+arr_send)/(Ang_To_Arr_ZYFS(YF_Lim)/7);		//图片序号计算
				}
				else
				{
					j=abs(YF_Runed,arr_send)/(Ang_To_Arr_ZYFS(YF_Lim)/7);		//图片序号计算
				}
				k=YF_Pic;
				if(	k!=j)
				{	
					kj=abs(k,j);			
					if(kj<2)
					{
						k=j;   YF_Pic=k;
						if((1<YF_Pic)&&(YF_Pic<8))
						{
							u2_printf("CT_YF%d",YF_Pic);			//串口2发送动画图片指令
						}							
					}				
				}							
			}
			//电机停止
			MotorStop(3);   
			MotorStop(4);   
			MotorStop(5);   
			u2_printf("*%s*M345*TTT*000*/**",RX_BUF);		//串口2反馈
			TIM10_Stop();         //定时器关闭
			//判断复位
			if(((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))||(0==GD3_CS)||(0==GD4_CS))&&(direct==0))  //判断是否到达复位状态
			{
				arr_now=0;     		//此时处于复位状态，将状态值都设为0；
				YF_Flag=0;		//设置状态标志位
			}			
			else
			{					
				arr_now=__HAL_TIM_GET_COUNTER(&TIM10_Handler);         //获取当前计数值arr_now	
			}
			//通过上下行判断脉冲累计
			if(direct==1)      //上行，则用+
			{ 
				if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))||(0==GD3_YFZZ)||(0==GD4_YFZZ)) //向上运行到极限位置
				{
					YF_Runed=Ang_To_Arr_ZYFS(YF_Lim);				//设置已运行脉冲值为极限值
					M345R_End=1;    								
					delay_ms(200);
					u2_printf("CT_YF8");
					delay_ms(200);
					u2_printf("HLYFJX");
				}
				else
				{
					YF_Runed=YF_Runed+arr_now;		//设置已运行脉冲值=上一次运行脉冲值+此次运行脉冲值
				}		
			}	
			else              //下行，则用-
			{
				if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))||(0==GD3_CS)||(0==GD4_CS))   //向下运行到极限位置
				{
					YF_Runed=0;				//已运行脉冲值设为0
					M345R_Start=0;  								
					delay_ms(200);
					u2_printf("CT_YF1");
				}
				else
				{
					YF_Runed=YF_Runed-arr_now;		//设置已运行脉冲值=上一次运行脉冲值-此次运行脉冲值	
				}
			}					
			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);       //清除中断标志位
//		//若定时时间到但是光电没到，则电机再运行一段距离，到达光电开关位置（光电开关安装后打开此段）
//			if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))&&((1==GD3_CS)||(1==GD4_CS))&&(direct==0)&&(YF_Flag==1))
//			{   			
//				if((1==GD3_CS)&&(0==GD4_CS))   //光电3没到位
//				{
//					MotorStart(3,0,1400-1,25-1);        //3号电机启动
//					u2_printf("*%s*M3*F*0*/**",RX_BUF);
//					TIM10_Init(add_arr,65000);               //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //清除中断标志位	 	
//					while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))
//					{			
//						if(0==GD3_CS)  //运行时碰到光电开关，跳出循环 
//						{
//							delay_us(100);
//							if(0==GD3_CS) 
//							{
//								YF_Flag=0;				
//								u2_printf("GD3CS");
//								break;	
//							}							
//						}
//					}			
//					MotorStop(3);    //电机停止
//					u2_printf("*%s*M3*T*0*/**",RX_BUF);
//					TIM10_Stop();       //定时器关闭
//					if(0==GD3_CS)
//					{
//						u2_printf("*%s*GD3CS*/*0*/**",RX_BUF);
//					}
//					else
//					{
//						u2_printf("*%s*GD3CS*/*1*/**",RX_BUF);
//					}
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位
//				}
//				if((0==GD3_CS)&&(1==GD4_CS))   //光电4没到位
//				{
//					MotorStart(4,0,1400-1,25-1); 		 //4号电机启动
//					u2_printf("*%s*M4*F*0*/**",RX_BUF);
//					TIM10_Init(add_arr,65000);                //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //清除中断标志位	 	
//					while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))
//					{			
//						if(0==GD4_CS)  //运行时碰到光电开关，跳出循环 
//						{
//							delay_us(100);
//							if(0==GD4_CS)
//							{
//								YF_Flag=0;	
//								u2_printf("GD4CS");
//								break;	
//							}							
//						}
//					}			
//					MotorStop(4);       //电机停止
//					u2_printf("*%s*M4*T*0*/**",RX_BUF);
//					TIM10_Stop();       //定时器关闭
//					if(0==GD4_CS)
//					{
//						u2_printf("*%s**GD4CS*/*0*/**",RX_BUF);
//					}
//					else
//					{
//						u2_printf("*%s*GD4CS*/*1*/**",RX_BUF);
//					}
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //清除中断标志位				
//				}
//				if((1==GD3_CS)&&(1==GD4_CS))   //光电3/4都没到位
//				{				
//					MotorStart(3,0,(1400-1)*2.0,25-1);     //3号电机启动
//					MotorStart(4,0,(1400-1)*0.8,25-1);		 //4号电机启动
//					MotorStart(5,0,1400-1,25-1);			 //5号电机启动
//					u2_printf("*%s*M345*FFF*000*/**",RX_BUF);
//					TIM10_Init(add_arr,65000);                   //打开定时器
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //清除中断标志位	 	
//					while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))
//					{			
//						if((0==GD3_CS)||(0==GD4_CS))  //运行时碰到光电开关，跳出循环 
//						{
//							delay_us(100);
//							if((0==GD3_CS)||(0==GD4_CS))
//							{
//								if((0==GD3_CS)&&(1==GD4_CS))
//								{
//									u2_printf("GD3CS");
//									MotorStop(3);
//								}
//								if((1==GD3_CS)&&(0==GD4_CS))
//								{
//									u2_printf("GD4CS");
//									MotorStop(4);
//								}
//								if((0==GD3_CS)&&(0==GD4_CS))
//								{
//									YF_Flag=0;	
//									u2_printf("GD3CS");
//									delay_ms(200);
//									u2_printf("GD4CS");
//									break;
//								}
//							}								
//						}
//					}			
//					MotorStop(3);      //电机停止
//					MotorStop(4);
//					MotorStop(5);
//					u2_printf("*%s*M345*TTT*000*/**",RX_BUF);
//					TIM10_Stop();       //定时器关闭
//					if((1==GD3_CS)||(1==GD4_CS))  //运行时碰到光电开关，跳出循环 
//					{
//						delay_us(100);
//						if(1==GD3_CS)
//						{
//							u2_printf("*%s*GD3CS*/*1*/**",RX_BUF);
//						}
//						if(1==GD4_CS) 
//						{
//							u2_printf("*%s*GD4CS*/*1*/**",RX_BUF);
//						}
//					}
//					if((0==GD3_CS)||(0==GD4_CS))  //运行时碰到光电开关，跳出循环 
//					{
//						delay_us(100);
//						if(0==GD3_CS)
//						{
//							u2_printf("*%s*GD3CS*/*0*/**",RX_BUF);
//						}
//						if(0==GD4_CS) 
//						{
//							u2_printf("*%s*GD4CS*/*0*/**",RX_BUF);
//						}
//					}
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位	
//				}
//			}
		//侧翻复位
		if((YF_Flag==0)&&(0==direct))     //345联动复位到初始状态，才复位5号电机
		{			
			//5号侧翻复位
			memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//清空串口2接收数组		
			USART2_RX_LEN=0;					//串口2状态清零
			memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//清空串口4接收数组		
			UART4_RX_LEN=0;				  //串口4状态清零
//			Motor4_BC(0,2800,1400-1,25-1);//调用补偿函数
			delay_ms(200);
			u2_printf("CT_YCF10");
			delay_ms(200);
			MotorStart(5,1,1400-1,25-1);  			 //5号电机启动
			u2_printf("*%s*M5*F*0*/**",RX_BUF);		//串口2反馈
			YF_Runed=0;			//已运行脉冲值设为0		
			TIM10_Init(Ang_To_Arr_ZYFS(YF_Lim),65000);        //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	                         //打开定时器
			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);          //清除中断标志位
			while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))   //等待定时时间到，
			{							
				//光电限位
				if((0==GD5_CS)&&(0==YF_Flag))       //运行时碰到光电开关，跳出循环 
				{			   										
					delay_us(100);
					if(0==GD5_CS)
					{	
						u2_printf("GD5CS");	
						break;		
					}							
				}
				  //判断有没有收到上位机指令		
				if(USART2_RX_LEN&0x8000)
				{
					u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数	
					memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);		//清空串口2接收数组	
					USART2_RX_LEN=0;					//串口2状态清零											
				}	
				if(UART4_RX_LEN&0x8000)
				{
					u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数	
					memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);				//清空串口4接收数组	
					UART4_RX_LEN=0;							  //串口4状态清零									
				}
				//电机故障、故障诊断
//				if(1==Motor5_Alm)
//				{
//					delay_us(100);
//					if(1==Motor5_Alm)
//					{
//						YF5_GZ=1;
//						u2_printf("*%s*M5*F*1*/**",RX_BUF);
//						u2_printf("YFGZ5");
//						Fun_GZCL();
//						break;		
//					}							
//				}									
				//发送动画指令
				 arr_send1=__HAL_TIM_GET_COUNTER(&TIM10_Handler);					//获取当前寄存器运行装载值
				 n=arr_send1/(Ang_To_Arr_ZYFS(YF_Lim)/9);
				 n=9-n;
				 m=YCF_Pic;
				if(	m!=n)
				{	
					mn=abs(m,n);			
					if(mn<2)
					{
						m=n;   YCF_Pic=m;
						if((1<YCF_Pic)&&(YCF_Pic<10))
						{
							u2_printf("CT_YCF%d",YCF_Pic);		//串口2发送动画图片指令
						}							
					}				
				}	
			}      
			MotorStop(5);          //电机停止
			u2_printf("*%s*M5*T*0*/**",RX_BUF);		//串口2反馈
			TIM10_Stop();		   //定时器关闭
			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //清除中断标志位
			YF_Flag=0;			//设置状态标志位
			W25QXX_Write((u8*)&YF_Flag,34,1);		//将状态标志位写入flash
			delay_ms(200);
			u2_printf("CT_YCF1");
		    delay_ms(200);
			u2_printf("YF_flag==0");			
		    delay_ms(200);
		    u2_printf("HLYFFW");
			//若定时时间到但是光电没到，则电机再运行一段距离，到达光电开关位置（光电开关安装后打开此段，并将上面的清除中断删除）
//			if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))&&(1==GD5_CS)&&(direct==0)&&(0==ZF_Flag))
//			{
//				MotorStart(5,1,1400-1,25-1);    			 //5号电机启动
//				u2_printf("*%s*M5*F*0*/**",RX_BUF);
//				TIM10_Init(add_arr,65000);                   //打开定时器
//				__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //清除中断标志位	 	
//				while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))
//				{			
//					if(0==GD5_CS)  //运行时碰到光电开关，跳出循环 
//					{
//						delay_us(100);
//						if(0==GD5_CS) 
//						{
//							u2_printf("GD5CS");
//							break;		
//						}							
//					}
//				}			
//				MotorStop(5);        //电机停止
//				u2_printf("*%s*M5*T*0*/**",RX_BUF);
//				TIM10_Stop();		   //定时器关闭
//				if(0==GD5_CS)
//				{
//					u2_printf("*%s*GD5CS*/*0*/**",RX_BUF);
//				}
//				else
//				{
//					u2_printf("*%s*GD5CS*/*1*/**",RX_BUF);
//				}					
//				__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位	
//			}			
		}			
	 }
  }

	else
	{
		LedAlm(100,"HLYFGS");
	}	
}

/***********************************************************************
 函数名      ：Fun_HL_BH(void)  
 函数功能    ：护栏背部护理
 输入        ：无
 输出        ：无
                           
************************************************************************/
void Fun_HL_BH(void)
{		
	if((SD_Flag==1)&&(1==ZF_Flag))  //如果此时处于左翻身，则进行左背部护理
	{
		strcpy((char *)RX_BUF,(const char *)"HLZBH");
		Fun_ZBH(); 
	}
	if((SD_Flag==1)&&(1==YF_Flag))//如果此时处于右翻身，则进行右背部护理
	{
		strcpy((char *)RX_BUF,(const char *)"HLYBH");
		Fun_YBH();
	}
	else
	{
		LedAlm(100,"BHGS");
	}	
}

/***********************************************************************
 函数名      ：Fun_HL_BH(void)  
 函数功能    ：护栏腰部护理
 输入        ：无
 输出        ：无
                           
************************************************************************/
void Fun_HL_YH(void)
{
	if((SD_Flag==1)&&(1==ZF_Flag))  //如果此时处于左翻身，则进行左腰部护理
	{
		strcpy((char *)RX_BUF,(const char *)"HLZYH");
		Fun_ZYH(); 
	}
	if((SD_Flag==1)&&(1==YF_Flag))//如果此时处于右翻身，则进行右腰部护理
	{
		strcpy((char *)RX_BUF,(const char *)"HLYYH");
		Fun_YYH();
	}
	else
	{
		LedAlm(100,"YHGS");
	}	
}


/***********************************************************************
 函数名      ：Fun_HL_SD(void)  
 函数功能    ：一键锁定程序
 输入        ：无
 输出        ：无
                           
************************************************************************/
u8 Fun_HL_SD(void)
{	
	strcpy((char *)RX_BUF,(const char *)"HLSD");
	SD_Dir_flag=!SD_Dir_flag;		//设置状态标志位
	
	if(SD_Dir_flag==1)
	{		
		SD_Flag=0;	//护栏锁定	
		u2_printf("*%s*SD*/*/*/**",RX_BUF);		//串口2反馈
		delay_ms(200);
		u2_printf("HLSD");
		
	}
	else
	{
		SD_Flag=1;   //护栏解锁
		u2_printf("*%s*JS*/*/*/**",RX_BUF);		//串口2反馈
		delay_ms(200); 
		u2_printf("HLJS");
	}
    return 	SD_Flag;
}

/***********************************************************************
 函数名      ：Fun_ZDZBQ(void)   
 函数功能    ：按键执行自动坐便器功能
 输入        ：无
 输出        ：无 
                          
************************************************************************/
void Fun_ZDZBQ(void) 
{			
	//联锁功能，只有在上曲腿、左右翻身复位后，才能执行座便器功能	
	if((0==ZF_Flag)&&(0==YF_Flag)) 
	{
		if(0==ZDZBQ_Flag)
		{		
			delay_ms(200);		
			u2_printf("ZDZBKS");
			delay_ms(200);
		}                         
		ZDZBQ_Dir_flag=!ZDZBQ_Dir_flag; 
		
		if((ZDZBQ_Dir_flag==1)&&(0==ZDZBQ_Flag)) //自动坐便正行程
		{
			u2_printf("ZDZBQ_flag==1");			 
			ZDZBQ_Flag=1;
			delay_ms(200);
			if((1==ZB_Flag)&&(0==XQT_Flag))      //此时已处于支背支起状态
			{
				MotorStart(2,1,0,0);             			//曲腿推杆下行
				u2_printf("*%s*M2*Z*/*/**",RX_BUF);		//串口2反馈
				XQT_State=1;                     //下曲腿需要动作，支背不需要 
				ZB_State=0;
				u2_printf("CT_XQT1");
			}
			else if((0==ZB_Flag)&&(1==XQT_Flag))  //此时已处于下曲腿状态
			{
				MotorStart(1,1,0,0);              //支背上行
				u2_printf("*%s*M1*Z*/*/**",RX_BUF);		//串口2反馈
				ZB_Dir_flag=1;
				ZB_State=1;                       //支背需要动作，下曲腿不需要 
				XQT_State=0;
				u2_printf("CT_ZB1");
			}
			else if((0==ZB_Flag)&&(0==XQT_Flag))            //此时处于支背及下曲腿复位状态
			{				 
				MotorStart(1,1,0,0); 	 				//支背上行 
				MotorStart(2,1,0,0);  				//曲腿推杆下行
				u2_printf("*%s*M12*ZZ*/*/**",RX_BUF); //下曲腿下,串口2反馈		
				ZB_Dir_flag=1;
				XQT_State=1;                             //支背需要动作，下曲腿需要动作       
				ZB_State=1;
				u2_printf("CT_ZBQ_ZBXQT1");
			}
			else if((1==ZB_Flag)&&(1==XQT_Flag))            //此时已处于支背支起及下曲腿状态
			{
				XQT_State=0;            
				ZB_State=0; 
			}
		}		
		else if((ZDZBQ_Dir_flag==0)&&(1==ZDZBQ_Flag))         //自动坐便复位-支背、下曲腿复位
		{
			ZB_Dir_flag=0; 
			XQT_State=1;            
			ZB_State=1;			
			MotorStart(1,0,0,0); //支背下行      
			MotorStart(2,0,0,0); //曲腿推杆上行
			u2_printf("*%s*M12*FF*/*/**",RX_BUF);  //下曲腿上,串口2反馈
			delay_ms(200);
			u2_printf("CT_ZBQ_ZBXQT15");
		}
		if((1==XQT_State)||(1==ZB_State))
		{	
			if(1==XQT_State){ XQT_Flag=1; W25QXX_Write((u8*)&XQT_Flag,37,1); }		//将状态标志位写入flash
			if(1==ZB_State) { ZB_Flag=1;  W25QXX_Write((u8*)&ZB_Flag,35,1); }		//将状态标志位写入flash
			Fun_ZB_XQT();
		}
		if(ZDZBQ_Dir_flag==1)
		{
			Fun_ZBQ(0);	            //坐便打开			
			delay_ms(1000);
			Fun_CZ1();              //重物检测			
			delay_ms(1000);			
			Fun_CXHG();             //冲洗烘干			
			Fun_ZBQ(1);	            //坐便关闭
			ZBQ_Flag=0;							//设置状态标志位
			if(ZBQ_Flag==0)         //判断坐便是否处于复位状态，再进行坐便袋收紧
			{									
				Fun_ZBTG(1,ZBDTG_Lim);   //收线推杆伸出
				Fun_ZBD(1);          //坐便袋收紧
				Fun_ZBTG(0,ZBDTG_Lim);   //收线推杆缩回
				delay_ms(100);
				Fun_ZDZBQ();         //再次调用该函数，使标志位取反，复位
				XQT_Flag=0;          //清除标志位
				ZB_Flag=0;					//设置状态标志位
				W25QXX_Write((u8*)&ZB_Flag,35,1);		//将状态标志位写入flash
				W25QXX_Write((u8*)&XQT_Flag,37,1);		//将状态标志位写入flash
				ZDZBQ_Flag=0;				//设置状态标志位
				XQT_State=0;
				ZB_State=0;
				ZB_Dir_flag=0;		//设置方向状态标志位
				delay_ms(200);
				u2_printf("ZDZBQ_flag==0");
				delay_ms(200);
				u2_printf("ZDZBFW");
				
			}	
		}				
	}
	else
	{
		LedAlm(100,"ZDZBGS");
	}	
}


/***********************************************************************
 函数名      ：Fun_ZBQ(void)  
 函数功能    ：按键执行坐便器功能
 输入        ：dir: 0(打开坐便)；1（关闭坐便）
 输出        ：无
                           
************************************************************************/
void Fun_ZBQ(u8 dir)
{
	u8 direct;       //代表某个动作运行的方向标志：1-正向运行；0-反向运行
	u8 key;          //按键扫描函数返回值,用于判断电机失步故障
	u16 len;
	
//实现上位机实时显示护理床当前运动状态
	static u16 k=0;           //发送第k张图片指令
	u8 i=0;
	u16 j=0;	
	u16 arr_send;             //当前一次运行脉冲数
	static u8 kj;
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);		//清空串口2接收数组	
	USART2_RX_LEN=0;					//串口2状态清零
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//清空串口4接收数组			
	UART4_RX_LEN=0;				  //串口4状态清零
	
	//联锁功能，只有在上曲腿、左右翻身复位后，才能执行座便器功能
	if((SQT_Flag==0)&&(ZF_Flag==0)&&(YF_Flag==0))
	{
		ZBQ_Flag=1;							//设置状态标志位
		W25QXX_Write((u8*)&ZBQ_Flag,38,1);		//将状态标志位写入flash
		direct=!dir;					//设置运行方向标志
		if(0==dir)
		{
			MotorStart(6,0,1400-1,25-1);           //电机启动
			u2_printf("*%s*M6*Z*0*/**",RX_BUF);		//串口2反馈
			delay_ms(200);
			u2_printf("CT_ZBQ1");
		}
		else
		{
			MotorStart(6,1,1400-1,25-1);           //电机启动
			u2_printf("*%s*M6*F*0*/**",RX_BUF);		//串口2反馈
			delay_ms(200);
			u2_printf("CT_ZBQ25");
		}
				
		TIM10_Init(ZBQ_Max,65000);              //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);           //清除中断标志位
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))    //等待定时时间到，时间到跳出循环
		{							
			//光电限位
			if((0==GD6_ZZ)&&(1==direct))
			{
				delay_us(100);
				if(0==GD6_ZZ)
				{
					u2_printf("GD6ZZ"); 
					break ;
				}						
			}
			if((0==GD6_CS)&&(0==direct))
			{
				delay_us(100);
				if(0==GD6_CS)
				{
					u2_printf("GD6CS"); 
					break ; 
				}
			}
			  //判断有没有收到上位机指令		
			if(USART2_RX_LEN&0x8000)
			{
				u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数	
				memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);//清空串口2接收数组			
				USART2_RX_LEN=0;				//串口2状态清零
			}
			if(UART4_RX_LEN&0x8000)
			{
				u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数	
				memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//清空串口4接收数组			
				UART4_RX_LEN=0;				  //串口4状态清零
			}
			//电机故障、故障诊断
//			if(1==Motor6_Alm)     
//			{
//				delay_us(100);
//				if(1==Motor6_Alm)  
//				{
//					ZBQ_GZ=1;
//					u2_printf("*%s*M6*/*1*/**",RX_BUF);
//					u2_printf("ZBQGZ");
//					Fun_GZCL();
//					break;		
//				}						
//			}										
			//发送动画指令
			arr_send=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//获取当前寄存器运行装载值
			j=arr_send/(ZBQ_Max/24);	
			if(0==direct)
			{
				j=24-j;
			}
			k=ZBQ_Pic;
			if(k!=j)
			{
				kj=abs(k,j);
				if(kj<2)
				{
					k=j;  ZBQ_Pic=k;
					if((1<ZBQ_Pic)&&(ZBQ_Pic<25))
					{
						u2_printf("CT_ZBQ%d",ZBQ_Pic);		//串口2发送动画图片指令
					}
				}
			}
		}			
		
		MotorStop(6);  u2_printf("*%s*M6*T*0*/**",RX_BUF); //6号电机停止,串口2反馈
		TIM10_Stop();      //关闭定时器
		//判断复位
		if(((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))||(0==GD6_CS))&&(direct==0))//判断是否处于复位状态，复位状态的前提是下行的定时器走完
		{		
			ZBQ_Flag=0;	 		//设置状态标志位
			W25QXX_Write((u8*)&ZBQ_Flag,38,1);		//将状态标志位写入flash
		}
		 else if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))&&(1==direct))
		 {
			ZBQ_Flag=1; 		//设置状态标志位
			W25QXX_Write((u8*)&ZBQ_Flag,38,1);		//将状态标志位写入flash
		}
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位
		//使电机复位到初始状态（光电安装后直接打开此段）
//		if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))&&(0==GD6_CS)&&(direct==0))  //定时时间到，光电没到
//		{
//			MotorStart(6,1,1400-1,25-1);           //电机启动
//			u2_printf("*%s*M6*F*0*/**",RX_BUF);
//			TIM10_Init(add_arr,65000);                             //打开定时器35000
//			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);           //清除中断标志位	 	
//			while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) )  //等待定时时间到，时间到跳出循环
//			{
//				if(0==GD6_CS)  //如果电机过载或碰到光电开关，则跳出循环，电机停止转动 
//				{  
//					delay_us(100);
//					if(0==GD6_CS) 
//					{
//						u2_printf("GD6CS");
//						break; 
//					}						
//				}				
//			}				                                 			
//			MotorStop(6);     //电机停止
//			u2_printf("*%s*M6*T*0*/**",RX_BUF);
//			TIM10_Stop();        //关闭定时器
//			if(0==GD6_CS)
//			{
//				u2_printf("*%s*GD6CS*/*0*/**",RX_BUF);
//			}
//			else
//			{
//				u2_printf("*%s*GD6CS*/*1*/**",RX_BUF);
//			}
//			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);          //清除中断标志位
//		}
	}
	else
	 {
		 LedAlm(100,"ZBQGS");   	
	 }	
}

/***********************************************************************
 函数名      ：Fun_CZ1()   
 函数功能    ：称重函数
 输入        ：无
 输出        ：1：重物在变化；0：重物未发生变化 
                          
************************************************************************/
u8 Fun_CZ(void)  
{
    //开始检测重物				
	if(num==1)
	{				         			
		num=2;
		u1=filter();
		delay_ms(1000);
		if(num==2)
		{	
			num=3;
			u2=filter();
			delay_ms(1000);
			if(num==3)
			{	 
				num=1;
				u3=filter();
				delay_ms(1000);
			}
		}
	}
	//检测重物质量是否发生变化
	 if((abs(u1,u2)<3999)&&(abs(u1,u3)<3999)&&(abs(u2,u3)<3999))//0x300=768
	 {
		 return 0;
	 }
	 else
	 {
		 return 1;
	 }	 	
}		

/***********************************************************************
 函数名      ：Fun_ZBD()   
 函数功能    ：坐便袋收紧
 输入        ：dir:电机运行方向标志；1-正转；0-反转
 输出        ：无
                          
************************************************************************/	
void Fun_ZBD(u8 dir)
{	
	//实现上位机实时显示护理床当前运动状态
	u16 k=0;                  //传第k张动画
	u8 kj;
	u16 j=0;	
	u16 arr_send;                   //当前一次运行脉冲值	
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			//清空串口2接收数组
	USART2_RX_LEN=0;				//串口2状态清零
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//清空串口4接收数组		
	UART4_RX_LEN=0;				  //串口4状态清零
	u8 len;
	RELAY6=1;                       //继电器得电，常开触点闭合，坐便袋扎紧电机得电
	delay_ms(1000);		
	u2_printf("CT_ZBD1");
	delay_ms(200);	
	//将坐便袋扎紧
	if(1==dir)
	{
		DIR6_1=1;
		u2_printf("*%s*M10*Z*/*/**",RX_BUF);				//串口2反馈
	}
	else
	{
		DIR6_1=0;
		u2_printf("*%s*M10*F*/*/**",RX_BUF);			//串口2反馈
	}
	ZBD_Start(360-1,250-1); 
	TIM2_Init(ZBD_Lim,65000);                              //打开定时器10500
	__HAL_TIM_CLEAR_FLAG(&TIM2_Handler, TIM_SR_CC1IF);         //清除中断标志位
	while(!(__HAL_TIM_GET_FLAG(&TIM2_Handler, TIM_SR_CC1IF)))  //等待定时时间到
	{			
		//判断有没有收到上位机指令		
		if(USART2_RX_LEN&0x8000)
		{
			len=USART2_RX_LEN&0x3fff;	//获取串口2接收数组字符长度				
			USART2_RX_BUF[len]=0;			//串口2数组末尾添"0"
			if(strstr((const char *)USART2_RX_BUF,(const char *)"STOP")||
				strstr((const char *)USART2_RX_BUF,(const char *)"ZDZBQ"))
			{						
				memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//清空串口2接收数组		
				USART2_RX_LEN=0;					//串口2状态清零
				break;
			}
			if(strstr((const char *)USART2_RX_BUF,(const char *)"SEND OK"))
			{	}
			else 
			{
				u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数	
				memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);		//清空串口2接收数组	
				USART2_RX_LEN=0;					//串口2状态清零
			}				
		}
		if(UART4_RX_LEN&0x8000)
		{
			len=UART4_RX_LEN&0x3fff;		//获取串口4接收数组字符长度			
			UART4_RX_BUF[len]=0;				//串口4数组末尾添"0"
			if(strstr((const char *)UART4_RX_BUF,(const char *)"STOP")||
				strstr((const char *)UART4_RX_BUF,(const char *)"ZDZBQ"))
			{	
				memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//清空串口4接收数组		
				UART4_RX_LEN=0;				  //串口4状态清零
				break;
			}
			if(strstr((const char *)UART4_RX_BUF,(const char *)"SEND OK"))
			{	}
			else 
			{
				u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数	
				memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//清空串口4接收数组			
				UART4_RX_LEN=0;				  //串口4状态清零
			}				
		}
		 arr_send=__HAL_TIM_GET_COUNTER(&TIM2_Handler);      //当前一次脉冲值
		//传输动画指令
		if(dir==1)
		{
			j=arr_send/(ZBD_Lim/6);
		}
		else
		{
			j=arr_send/(ZBD_Lim/6);
			j=6-j;
		}
		if(	k!=j)
		{	
			kj=abs(k,j);
			if(kj<2)
			{
				k=j;
				u2_printf("CT_ZBD%d",k);				
			}
		}
	}
	__HAL_TIM_CLEAR_FLAG(&TIM2_Handler, TIM_SR_CC1IF);          //清除中断标志位
	ZBD_Stop();   u2_printf("*%s*M10*T*/*/**",RX_BUF);     //电机停止,串口2反馈
	TIM2_Stop();       //关闭定时器
	delay_ms(100);
	u2_printf("CT_ZBD7");
	RELAY6=0;          //继电器复位，坐便袋扎紧电机断电
}	

/***********************************************************************
 函数名      ：Fun_ZB_XQT()   
 函数功能    ：支背、下曲腿同时运行函数
 输入        ：无
 输出        ：无 
                          
************************************************************************/
void Fun_ZB_XQT(void)
{
	u8 len;
	u16 arr_now;               //当前一次运行脉冲数	
	//实现上位机实时显示护理床当前运动状态
	static u8 k;               //传第k张动画
	static u8 kj;
	u8 j=0;	
	u16 arr_send;              //当前一次运行脉冲值
		
	//联锁功能，只有在左右翻身功能复位后，才能进行支背、下曲腿
	if((ZF_Flag==0)&&(YF_Flag==0))
	{	
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//清空串口2接收数组		
		USART2_RX_LEN=0;				//串口2状态清零
		memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//清空串口4接收数组			
		UART4_RX_LEN=0;				  //串口4状态清零
		//运行支背或下曲腿或支背和下曲腿同时运行
		TIM10_Init(Ang_To_Arr_SXQT(XQT_Lim),65000);     //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);             //清除中断标志位	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) )    //定时时间到
		{
			 //判断有没有收到别的指令
			if(USART2_RX_LEN&0x8000)
			{
				len=USART2_RX_LEN&0x3fff;	//获取串口2接收数组字符长度				
				USART2_RX_BUF[len]=0;			//串口2数组末尾添"0"
				if(strstr((const char *)USART2_RX_BUF,(const char *)"SEND OK"))
				{	}
				else 
				{
					u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数	
					memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			//清空串口2接收数组
					USART2_RX_LEN=0;				//串口2状态清零
				}
			}
			if(UART4_RX_LEN&0x8000)
			{
				len=UART4_RX_LEN&0x3fff;		//获取串口4接收数组字符长度			
				UART4_RX_BUF[len]=0;				//串口4数组末尾添"0"
				if(strstr((const char *)UART4_RX_BUF,(const char *)"SEND OK"))
				{	}
				else 
				{
					u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数	
					memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);				//清空串口4接收数组	
					UART4_RX_LEN=0;				  //串口4状态清零
				}
			}
			 //发送支背动画指令
			if((1==ZB_State)&&(0==XQT_State))           //只执行支背
			{
				arr_send=__HAL_TIM_GET_COUNTER(&TIM10_Handler);						//获取当前寄存器运行装载值
				j=arr_send/(Ang_To_Arr_ZB(ZB_Lim)/19);
				if(0==ZDZBQ_Dir_flag)
				{
					j=19-j;
				}
				k=ZB_Pic;
				if(k!=j)
				{
					kj=abs(k,j);
					if(kj<2)
					{
						k=j;  ZB_Pic=k;
						if((1<ZB_Pic)&&(ZB_Pic<20))
						{
							u2_printf("CT_ZB%d",ZB_Pic);		//串口2发送动画图片指令
						}							
					}
				}
			}
			//发送曲腿动画指令
			else if((0==ZB_State)&&(1==XQT_State))      //只执行下曲腿
			{
				arr_send=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//获取当前寄存器运行装载值
				j=arr_send/(Ang_To_Arr_SXQT(XQT_Lim)/19);
				if(0==ZDZBQ_Dir_flag)
				{
					j=19-j;
				}
				k=XQT_Pic;
				if(	k!=j)
				{				
					kj=abs(k,j);
					if(kj<2)
					{
						k=j;  XQT_Pic=k;
						if((1<XQT_Pic)&&(XQT_Pic<20))
						{
							u2_printf("CT_XQT%d",XQT_Pic);			//串口2发送动画图片指令
						}							
					}				
				}			
			}			
			
			//发送支背和下曲腿同时运行动画指令
			else if((1==ZB_State)&&(1==XQT_State))      //支背和下曲腿同时运行
			{				
				arr_send=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//获取当前寄存器运行装载值
				j=arr_send/(Ang_To_Arr_ZB(ZB_Lim)/14);
				if(0==ZDZBQ_Dir_flag)
				{
					j=14-j;
				}
				if(	k!=j)
				{				
					kj=abs(k,j);
					if(kj<2)
					{
						k=j;
						if((1<k)&&(k<15))
						{
							u2_printf("CT_ZBQ_ZBXQT%d",k);	
						}							
					}				
				}								
			}										
		}
		MotorStop(2); u2_printf("*%s*M2*T*/*/**",RX_BUF);  //下曲腿停止
		TIM10_Stop();		        //关闭定时器	
		//判断下曲腿复位
		if((ZDZBQ_Dir_flag==0)&&(1==XQT_State)&&(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))
		{
			XQT_Flag=0; 		//设置状态标志位
			XQT_Runed=0;			//已运行脉冲值设为0 
			if(0==ZB_State)                   //只有下曲腿运行，支背不运行
			{
				k=0;   XQT_Pic=0;
				delay_ms(200);
				u2_printf("CT_XQT1");
			}
		}
		if((ZDZBQ_Dir_flag==1)&&(1==XQT_State)&&(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))
		{
			XQT_Flag=1; 		//设置状态标志位
			XQT_Runed=(Ang_To_Arr_SXQT(XQT_Lim)); 
			if(0==ZB_State)                   //只有下曲腿运行，支背不运行
			{
				k=19;   XQT_Pic=19;
				delay_ms(200);
				u2_printf("CT_XQT20");
			}
		}
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);         //清除中断标志位
		
		//继续运行支背或支背及下曲腿同时继续运行
		if(ZB_State==1)              //继续运行支背或支背及下曲腿同时继续运行
		{				
			TIM10_Init(Ang_To_Arr_ZB(ZB_Lim)-Ang_To_Arr_SXQT(XQT_Lim),65000);   //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);          //清除中断标志位
			while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) ) //支背定时时间到
			{	
				 //判断有没有收到别的指令
				if(USART2_RX_LEN&0x8000)
				{
					len=USART2_RX_LEN&0x3fff;		//获取串口2接收数组字符长度			
					USART2_RX_BUF[len]=0;			//串口2数组末尾添"0"
					if(strstr((const char *)USART2_RX_BUF,(const char *)"SEND OK"))
					{	}
					else 
					{
						u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数	
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			//清空串口2接收数组
						USART2_RX_LEN=0;				//串口2状态清零
					}
				}	
				if(UART4_RX_LEN&0x8000)
				{
					len=UART4_RX_LEN&0x3fff;		//获取串口4接收数组字符长度		
					UART4_RX_BUF[len]=0;				//串口4数组末尾添"0"
					if(strstr((const char *)UART4_RX_BUF,(const char *)"SEND OK"))
					{	}
					else 
					{
						u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数	
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//清空串口4接收数组		
						UART4_RX_LEN=0;				  //串口4状态清零
					}
				}
				 //继续发送支背运行动画指令
				 if(0==XQT_State)        //只有支背运行
				 {
					 arr_send=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//获取当前寄存器运行装载值
					 if(ZDZBQ_Dir_flag==1)
					 {
						 j=(Ang_To_Arr_SXQT(XQT_Lim)+arr_send)/(Ang_To_Arr_ZB(ZB_Lim)/19);		//图片序号计算
					 }
					 else
					 {
						 arr_send=Ang_To_Arr_ZB(ZB_Lim)-Ang_To_Arr_SXQT(XQT_Lim)-arr_send;
						 j=arr_send/(Ang_To_Arr_ZB(ZB_Lim)/19);
					 }
					 k=ZB_Pic;
					 if(k!=j)
					 {				
						kj=abs(k,j);
						if(kj<2)
						{
							k=j;   ZB_Pic=k;
							if((1<ZB_Pic)&&(ZB_Pic<20))
							{
								u2_printf("CT_ZB%d",ZB_Pic);		//串口2发送动画图片指令
							}								
						}				
					 }						
				 }
				 //继续发送下曲腿、支背同时运行的动画指令
				 if(1==XQT_State)       //支背、曲腿都运行
				 { 
					 arr_send=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//获取当前寄存器运行装载值
					 if(ZDZBQ_Dir_flag==1)
					 {
						 j=(Ang_To_Arr_SXQT(XQT_Lim)+arr_send)/(Ang_To_Arr_ZB(ZB_Lim)/14);		//图片序号计算
					 }
					 else
					 {
						 arr_send=Ang_To_Arr_ZB(ZB_Lim)-Ang_To_Arr_SXQT(XQT_Lim)-arr_send;
						 j=arr_send/(Ang_To_Arr_ZB(ZB_Lim)/14);
					 }
					 k=XQT_Pic;
					 if(k!=j)
					 {				
						kj=abs(k,j);
						if(kj<2)
						{
							k=j;  XQT_Pic=k;
							if((1<XQT_Pic)&&(XQT_Pic<15))
							{
								u2_printf("CT_ZBQ_ZBXQT%d",XQT_Pic);			//串口2发送动画图片指令
							}								
						}				
					}	
				}						 
			}
			MotorStop(1); u2_printf("*%s*M1*T*/*/**",RX_BUF);  //支背停止
			TIM10_Stop();                                   //关闭定时器
			//判断支背复位
			if((ZDZBQ_Dir_flag==0)&&(1==ZB_State)&&(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))
			{
				ZB_Flag=0; 		//设置状态标志位
				ZB_Runed=0;			//已运行脉冲值设为0
				if(0==XQT_State)         //只有支背运行
				{
					k=0;   ZB_Pic=0;
					delay_ms(200);
					u2_printf("CT_ZB1");
				}
				if(1==XQT_State)         //支背、曲腿同时运行
				{
					k=0;
					delay_ms(200);
					u2_printf("CT_ZBQ_ZBXQT1");
				}
			}
			if((ZDZBQ_Dir_flag==1)&&(1==ZB_State)&&(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))
			{
				ZB_Flag=1; 		//设置状态标志位
				ZB_Runed=Ang_To_Arr_ZB(ZB_Lim);				//设置已运行脉冲值为极限值
				if(0==XQT_State)         //只有支背运行
				{
					k=19;   ZB_Pic=19;
					delay_ms(200);
					u2_printf("CT_ZB20");
				}
				if(1==XQT_State)         //支背、曲腿同时运行
				{
					k=14;
					delay_ms(200);
					u2_printf("CT_ZBQ_ZBXQT15");
				}
			}
			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);         //清除中断标志位
		}				
	}
	else
	{
		LedAlm(100,"ZBQTGS");
	}	
}

/***********************************************************************
 函数名      ：WIFI_CZ1(void)   
 函数功能    ：按键执行自动坐便器功能
 输入        ：无
 输出        ：无 
                          
************************************************************************/
u8  Fun_CZ1(void)
{
	u8 m=0,i=0;
//	TIM2_Init(45000,10000);    //打开定时器，定时十秒
//	while(cz_time<2)
//	{
//		
		while(1)
		{
			TIM10_Init(45000-1,10000);       //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);         //清除中断标志位
			while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))  //等待定时时间到
			{
				if(Fun_CZ())                //若重物在变化跳出循环，重新开始计时
				{  
					m++;
					if((0<m)&&(m<16))
					{
						u2_printf("CT_CZ%d",m);	
					}
				}
			}
			//如果30S定时间到且重物没有发生变化
			if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))&&(0==Fun_CZ())) 
			{ 
				i++; 
			}
			else { i=0; }                    //否则重新计时
			if(i==1)                         //重物两分钟没有发生变化，开始冲洗烘干
			{
				u2_printf("CZJS");   //排便称重结束
				u1=0;
				u2=0;
				u3=0;
				break; 
			} 
			TIM10_Stop();
			u2_printf("CT_CZ%d",i);	
		}		
//	}
//	cz_time=0;
//	TIM2_Close();   //关闭定时器	
	u2_printf("称重结束");
	
}

/***********************************************************************
 函数名      ：Fun_CXHG(void)   
 函数功能    ：按键执行冲洗烘干功能
 输入        ：无
 输出        ：无  
                          
************************************************************************/
void Fun_CXHG()
{
	u8 num,len;    //接收字符串长度
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);//清空串口2接收数组
	USART2_RX_LEN=0;				//串口2状态清零
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//清空串口4接收数组
	UART4_RX_LEN=0;				  //串口4状态清零
    //连锁功能，只有在坐便打开时才能进行喷气烘干
	if(1==ZBQ_Flag)		
	{
//		Fun_ZBCXHG(1,2000);      //冲洗烘干推杆伸出                   
//		delay_ms(50);
		
/********************开始冲洗**********************/
		Fun_ZDCX();                               //自动冲洗

		//自动冲洗结束，等待30S若再次按下冲洗按键，进行手动调节冲洗
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);     //清空接收寄存器
		USART2_RX_LEN=0;					//串口2状态清零
		memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//清空串口4接收数组
		UART4_RX_LEN=0;				  //串口4状态清零
		TIM9_Init(40000,65000);                   //打开定时器，定时30S60000
		__HAL_TIM_CLEAR_FLAG(&TIM9_Handler, TIM_SR_CC1IF);         //清除中断标志位
		while(!(__HAL_TIM_GET_FLAG(&TIM9_Handler, TIM_SR_CC1IF)))  //等待定时时间到
		{							
			if(USART2_RX_LEN&0x8000)
			{
				len=USART2_RX_LEN&0x3fff;		//获取串口2接收数组字符长度			
				USART2_RX_BUF[len]=0;				//串口2数组末尾添"0"
				if(strstr((const char *)USART2_RX_BUF,(const char *)"SDCX"))   //若接收到Stop,则跳出循环	
				{					
					if(1==Liq_Sensor)           //足够一次冲洗
					{	
						u2_printf("*%s*YW*/*0*/**",RX_BUF);		//串口2反馈
//						memcpy(RX_BUF,USART2_RX_BUF,15);
						Fun_SDCX();
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);		//清空串口2接收数组	
					    USART2_RX_LEN=0;						//串口2状态清零					
					}
					else                         //不足一次冲洗
					{
						u2_printf("*%s*YW*/*1*/**",RX_BUF);		//串口2反馈
						break;
					}
				}				
			}
			if(UART4_RX_LEN&0x8000)
			{
				len=UART4_RX_LEN&0x3fff;				//获取串口4接收数组字符长度	
				UART4_RX_BUF[len]=0;					//串口4数组末尾添"0"
				if(strstr((const char *)UART4_RX_BUF,(const char *)"SDCX"))   //若接收到Stop,则跳出循环	
				{					
					if(1==Liq_Sensor)           //足够一次冲洗
					{	
						u2_printf("*%s*YW*/*0*/**",RX_BUF);		//串口2反馈
//						memcpy(RX_BUF,UART4_RX_BUF,15);
						Fun_SDCX();
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//清空串口4接收数组		
					    UART4_RX_LEN=0;				  //串口4状态清零
					}
					else                         //不足一次冲洗
					{
						u2_printf("*%s*YW*/*1*/**",RX_BUF);		//串口2反馈
						break;
					}
				}				
			}
		}
		TIM9_Stop();                                         //关闭定时器
		__HAL_TIM_CLEAR_FLAG(&TIM9_Handler, TIM_SR_CC1IF);   //清除中断标志位
	
		delay_ms(500);
		
/**********************************开始烘干***********************************/
		
		Fun_ZDHG();       //自动烘干2分钟
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);//清空串口2接收数组
		USART2_RX_LEN=0;				//串口2状态清零
		memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//清空串口4接收数组
		UART4_RX_LEN=0;				  //串口4状态清零
		//自动烘干结束，等待30S若再次按下烘干按键，进行手动调节烘干		
		TIM9_Init(40000,65000);                             //打开定时器，定时30S
		__HAL_TIM_CLEAR_FLAG(&TIM9_Handler, TIM_SR_CC1IF);         //清除中断标志位
		while(!(__HAL_TIM_GET_FLAG(&TIM9_Handler, TIM_SR_CC1IF)))  //等待定时时间到
		{
			if(USART2_RX_LEN&0x8000)
			{
				len=USART2_RX_LEN&0x3fff;		//获取串口2接收数组字符长度			
				USART2_RX_BUF[len]=0;			//串口2数组末尾添"0"
				if(strstr((const char *)USART2_RX_BUF,(const char *)"SDHG"))    //若接收到Stop,则跳出循环	
				{
					Fun_SDHG();
					memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);		//清空串口2接收数组	
					USART2_RX_LEN=0;						//串口2状态清零
				}				
			}
			if(UART4_RX_LEN&0x8000)
			{
				len=UART4_RX_LEN&0x3fff;			//获取串口4接收数组字符长度		
				UART4_RX_BUF[len]=0;				//串口4数组末尾添"0"
				if(strstr((const char *)UART4_RX_BUF,(const char *)"SDHG"))    //若接收到Stop,则跳出循环	
				{
					Fun_SDHG();
					memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);				//清空串口4接收数组	
					UART4_RX_LEN=0;				  //串口4状态清零
				}				
			}
		}
		
		TIM9_Stop();                                        //关闭定时器
		__HAL_TIM_CLEAR_FLAG(&TIM9_Handler, TIM_SR_CC1IF);  //清除中断标志位		
//		delay_ms(500);
//		Fun_ZBCXHG(0,2000+CXHG_Runed);                    //冲洗烘干推杆缩回		
	}
	else
	{
		LedAlm(100,"ZBQGS");
	}		
}
			
/***********************************************************************
 函数名      ：Fun_SDCX(void)   
 函数功能    ：按键执行冲洗功能
 输入        ：无
 输出        ：无  
                          
************************************************************************/
void Fun_SDCX(void)
{
	u8 len;              //WiFi接收字符串长度
	u8 direct;           //方向标志位
	u8 i;
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);//清空串口2接收数组
	USART2_RX_LEN=0;					//串口2状态清零
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//清空串口4接收数组
	UART4_RX_LEN=0;				  //串口4状态清零
	
    //连锁功能，只有在坐便打开时才能进行喷水冲洗
	if(1==ZBQ_Flag)		
	{								
		//喷水冲洗
		RELAY6=1;             //继电器得电
		DIR_SB=1;             //水泵开启PB12	
		CX_Flag=1;						//设置状态标志位
		if(0==CXHG_Runed)
		{
			u2_printf("CT_CX1");
		}
		Fun_ZBCX(1,CXHG_Lim/2); 
		for(i=0;i<2*CXHG_Time;i++)                                //冲洗2*CXHG_Time分钟
		{
			TIM10_Init(60000-1,45000-1);            //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz					
			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);        //清除中断标志位 
			while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))) //等待定时时间到，时间到跳出循环
			{ 					
//				if(0==Liq_Sensor)	                       //水位在低水位下，不足一次冲洗，则直接跳出
//				{ 
//					u2_printf("*%s*YW*/*1*/**",RX_BUF);
//					delay_ms(200);				
//					u2_printf("DYW");                      //发送给上位机指令信号，表示此时水位偏低
//					break;
//				}
//				else if(1==Liq_Sensor)
//				{
//					u2_printf("*%s*YW*/*0*/**",RX_BUF);
//				}					
				if(USART2_RX_LEN&0x8000)
				{
					len=USART2_RX_LEN&0x3fff;	//获取串口2接收数组字符长度				
					USART2_RX_BUF[len]=0;			//串口2数组末尾添"0"
					if(strstr((const char *)USART2_RX_BUF,(const char *)"TGS"))    //推杆伸出	
					{
						direct=1;			//设置运行方向标志
						Fun_ZBCX(1,CXHG_Lim/2); 
					}
					if(strstr((const char *)USART2_RX_BUF,(const char *)"TGX"))  //推杆缩回	
					{ 
						direct=0;			//设置运行方向标志
						Fun_ZBCX(0,CXHG_Lim/2); 					
					}
					memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);//清空串口2接收数组
					USART2_RX_LEN=0;				//串口2状态清零
				}
				if(UART4_RX_LEN&0x8000)
				{
					len=UART4_RX_LEN&0x3fff;		//获取串口4接收数组字符长度			
					UART4_RX_BUF[len]=0;			//串口4数组末尾添"0"
					if(strstr((const char *)UART4_RX_BUF,(const char *)"TGS"))    //推杆伸出	
					{
						direct=1;			//设置运行方向标志
						Fun_ZBCX(1,CXHG_Lim/2); 
					}
					if(strstr((const char *)UART4_RX_BUF,(const char *)"TGX"))  //推杆缩回	
					{ 
						direct=0;			//设置运行方向标志
						Fun_ZBCX(0,CXHG_Lim/2); 					
					}
					memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//清空串口4接收数组
					UART4_RX_LEN=0;					  //串口4状态清零
				}
			}			
			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //清除中断标志位   		
			TIM10_Stop();		                                //关闭定时器				
		}
		Fun_ZBCX(0,CXHG_Lim/2);
		CX_Flag=0;						//设置状态标志位
		DIR_SB=0;             //水泵关闭PB12
		if(CXHG_Runed>0)
		{
			direct=0;			//设置运行方向标志
			Fun_ZBCX(0,CXHG_Runed); 
		}
		if(0==CXHG_Runed)
		{
			u2_printf("CT_CX1");
		}		
		RELAY6=0;        //继电器断电
	}
	else
	{
		LedAlm(100,"SDCXGS");
	}	
}

/***********************************************************************
 函数名      ：Fun_SDHG(void)   
 函数功能    ：按键执行烘干功能
 输入        ：无
 输出        ：无  
                          
************************************************************************/
void Fun_SDHG(void)
{
	u8 len,i;
	u8 direct;     //代表没某个动作运行的方向标志：1-正向运行；0-反向运行         
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);//清空串口2接收数组
	USART2_RX_LEN=0;			//串口2状态清零
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//清空串口4接收数组
	UART4_RX_LEN=0;				  //串口4状态清零
    //连锁功能，只有在坐便打开时才能进行喷气烘干
	if(1==ZBQ_Flag)		
	{	
		//喷气烘干
		DIR_HG=1;             //烘干喷气阀门打开PB10
		delay_ms(500);       //等待阀门打开1S
		RELAY6=1;             //继电器得电
		DIR_QB=1;             //气泵启动PH2
		HG_Flag=1;						//设置状态标志位
		if(0==CXHG_Runed)
		{
			u2_printf("CT_HG1");
		}
		Fun_ZBHG(1,CXHG_Lim/2); 
		for(i=0;i<2*CXHG_Time;i++)      //烘干CXHG_Time分钟
		{
			TIM10_Init(60000-1,45000-1);         //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz						
			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);        //清除中断标志位 
			while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))) //等待定时时间到，时间到跳出循环
			{ 					
				if(USART2_RX_LEN&0x8000)
				{
					len=USART2_RX_LEN&0x3fff;		//获取串口2接收数组字符长度			
					USART2_RX_BUF[len]=0;			//串口2数组末尾添"0"
					//判断上下行
					if(strstr((const char *)USART2_RX_BUF,(const char *)"TGS"))    //推杆伸出	
					{
						direct=1;			//设置运行方向标志
						Fun_ZBHG(1,CXHG_Lim/2); 
					}
					if(strstr((const char *)USART2_RX_BUF,(const char *)"TGX"))  //推杆缩回	
					{ 
						direct=0;			//设置运行方向标志
						Fun_ZBHG(0,CXHG_Lim/2); 					
					}
					memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);//清空串口2接收数组
					USART2_RX_LEN=0;				//串口2状态清零
				}	
				if(UART4_RX_LEN&0x8000)
				{
					len=UART4_RX_LEN&0x3fff;		//获取串口4接收数组字符长度			
					UART4_RX_BUF[len]=0;				//串口4数组末尾添"0"
					//判断上下行
					if(strstr((const char *)UART4_RX_BUF,(const char *)"TGS"))    //推杆伸出	
					{
						direct=1;			//设置运行方向标志
						Fun_ZBHG(1,CXHG_Lim/2); 
					}
					if(strstr((const char *)UART4_RX_BUF,(const char *)"TGX"))  //推杆缩回	
					{ 
						direct=0;			//设置运行方向标志
						Fun_ZBHG(0,CXHG_Lim/2); 					
					}
					memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//清空串口4接收数组
					UART4_RX_LEN=0;				  //串口4状态清零
				}
			}              		
			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //清除中断标志位   		
			TIM10_Stop();   //关闭定时器		 	
		}
		Fun_ZBHG(0,CXHG_Lim/2); 
		HG_Flag=0;				//设置状态标志位
		if(CXHG_Runed>0)
		{
			direct=0;			//设置运行方向标志
			Fun_ZBHG(0,CXHG_Runed); 
		}		
		if(0==CXHG_Runed)
		{
			u2_printf("CT_HG1");
		}
		
		RELAY6=0;       //继电器断电
		DIR_QB=0;       //气泵关闭PH2
		DIR_HG=0;       //烘干喷气阀关闭PB10		
	}
	else
	{
		LedAlm(100,"SDHGGS");
	}	
}

/***********************************************************************
 函数名      ：Fun_ZDCX(void)   
 函数功能    ：按键执行冲洗功能
 输入        ：无
 输出        ：无  
                          
************************************************************************/
void Fun_ZDCX(void)
{
	u8 direct;   //代表没某个动作运行的方向标志：1-正向运行；0-反向运行
	u8 flag=0;   //控制推杆方向切换
	u8 i;
	u8 num,len;
	
    //连锁功能，只有在坐便打开时才能进行喷水冲洗
	if(1==ZBQ_Flag)		
	{						
//		//冲洗之前检测水位若在正常水位以下，发出报警声，并等待水箱注水
//		if(0==Liq_Sensor)  
//		{
//			delay_ms(100);
//			u2_printf("*%s*YW*/*1*/**",RX_BUF);
//			delay_ms(200);		
//			u2_printf("DYW");  //发送给上位机指令信号，表示此时水位偏低
//			PCF8574_WriteBit(BEEP_IO,0);	//控制蜂鸣器报警	
//			delay_ms(500);	
//			PCF8574_WriteBit(BEEP_IO,1);	//控制蜂鸣器报警			
//		}
//		while(0==Liq_Sensor);                  //等待水箱注满
//		u2_printf("*%s*YW*/*0*/**",RX_BUF);  //液位恢复可进行冲洗烘干
//		PCF8574_WriteBit(BEEP_IO,1);
		RELAY6=1;                              //继电器得电
		//喷水冲洗
		DIR_SB=1;                              //水泵开启PB12	
		if(0==CXHG_Runed)
		{                   
			delay_ms(100);
			u2_printf("CT_CX1");
		}
		for(i=0;i<2*CXHG_Time;i++)     //冲洗烘干推杆自动循环冲洗CXHG_Time分钟
		{
			flag=!flag;
			if(1==flag)
			{
				Fun_ZBCX(1,CXHG_Lim);      //每次伸出缩回5S钟
			}
			else
			{
				Fun_ZBCX(0,CXHG_Lim);      //每次伸出缩回5S钟			
			}
			delay_ms(10);			
		}
		if(0==CXHG_Runed)
		{                   
			delay_ms(100);
			u2_printf("CT_CX1");
		}
		RELAY6=0;             //继电器断电
		DIR_SB=0;             //水泵关闭PB12		
	}
	else
	{
		LedAlm(100,"ZDCXGS");
	}	
}

/***********************************************************************
 函数名      ：Fun_ZDHG(void)   
 函数功能    ：按键执行烘干功能
 输入        ：无
 输出        ：无  
                          
************************************************************************/
void Fun_ZDHG(void)
{
	u8 flag=0;        //控制推杆方向切换
	u8 i;
	
    //连锁功能，只有在坐便打开时才能进行喷气烘干
	if(1==ZBQ_Flag)		
	{
		//喷气烘干
		DIR_HG=1;             //烘干喷气阀门打开PB10
		delay_ms(500);       //等待阀门打开1S
		RELAY6=1;             //继电器得电
		DIR_QB=1;             //气泵启动PH2
		if(0==CXHG_Runed)
		{
			u2_printf("CT_HG1");
		}		
		for(i=0;i<2*CXHG_Time;i++)     //冲洗烘干推杆自动循环烘干CXHG_Time 分钟
		{
			flag=!flag;
			if(1==flag)
			{
				Fun_ZBHG(1,CXHG_Lim);      //每次伸出缩回5S钟
			}
			else
			{
				Fun_ZBHG(0,CXHG_Lim);      //每次伸出缩回5S钟			
			}
			delay_ms(50);
		}
		if(0==CXHG_Runed)
		{
			u2_printf("CT_HG1");
		}
		RELAY6=0;       //继电器断电
		DIR_QB=0;       //气泵关闭PH2
		DIR_HG=0;       //烘干喷气阀关闭PB10
	}
	else
	{
		LedAlm(100,"ZDHGGS");
	}	
}

/***********************************************************************
 函数名      ：Fun_ZJ_ZB(void)  
 函数功能    ：专家系统推理-支背
 输入        ：无
 输出        ：无
                           
************************************************************************/
void Fun_ZJ_ZB(void) 
{
	//支背起
	WriteInU2("ZBS");
	Fun_ZB();                //支背
	delay_ms(1000);	
	//支背复位	
	WriteInU2("ZBX");
	Fun_ZB();                //支背复位		
}

/***********************************************************************
 函数名      ：Fun_ZJ_ZYF(void)  
 函数功能    ：专家系统推理-翻身
 输入        ：无
 输出        ：无
                           
************************************************************************/
void Fun_ZJ_ZYF(void) 
{
	//左翻身
	WriteInU2("ZFS");		
	Fun_ZF();           //左翻身	
	delay_ms(1000);
	WriteInU2("ZFX");		
	Fun_ZF();           //左翻身复位
	delay_ms(1000);
			
	//右翻身
	WriteInU2("YFS");
	Fun_YF();          //右翻身
	delay_ms(1000);
	WriteInU2("YFX");
	Fun_YF();          //右翻身复位		
}

/***********************************************************************
 函数名      ：Fun_ZJ_SXQT(void)  
 函数功能    ：专家系统推理-曲腿
 输入        ：无
 输出        ：无
                           
************************************************************************/
void Fun_ZJ_SXQT(void) 
{
	//上曲腿
	WriteInU2("SQTS");
	Fun_SQT();              //上曲腿
	delay_ms(1000);
	WriteInU2("SQTX");
	Fun_SQT();              //上曲腿复位
	delay_ms(1000);	
	
	//下曲腿
	WriteInU2("XQTX");
	Fun_XQT();            //下曲腿	
	delay_ms(1000);
	WriteInU2("XQTS");
	Fun_XQT();            //下曲腿复位	
}

/***********************************************************************
 函数名      ：Fun_ZJ_ZDZB(void)  
 函数功能    ：专家系统推理-自动坐便
 输入        ：无
 输出        ：无
                           
************************************************************************/
void Fun_ZJ_ZDZB(void) 
{
	Fun_ZDZBQ();	  //自动坐便
}

/***********************************************************************
 函数名      ：Fun_ZD_ZZ(void)  
 函数功能    ：执行左肢康复锻炼
 输入        ：t-康复锻炼次数
 输出        ：无
                           
************************************************************************/
void Fun_ZD_ZZ(int t)
{
   u32 pulse;          //吊挂运行脉冲数
   int j;	
	//病人只有平躺在床上才能进行吊挂康复训练
   if((0==ZB_Flag)&&(0==SQT_Flag)&&(0==XQT_Flag)&&(0==ZBQ_Flag)&&(0==ZF_Flag)&&(0==YF_Flag))
   { 
		
		DG_Relay=1;	       //继电器
		if((strstr((const char *)USART2_RX_BUF,(const char *)"BZZ"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"BZZ")))//左胳膊
		{
			pulse=1000000;
			if(ZXT_Flag==0)       //防止按键误触发，导致标志位置位
			{	
				ZXB_Flag=1;		//设置状态标志位
				delay_ms(200);
				u2_printf("KS");
				delay_ms(200);
				u2_printf("DGZZKS");				
			}
		}
		if((strstr((const char *)USART2_RX_BUF,(const char *)"TZZ"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"TZZ")))//左腿
		{
			pulse=1500000;
			if(ZXB_Flag==0)      //防止按键误触发，导致标志位置位
			{	
				ZXT_Flag=1;		//设置状态标志位
				delay_ms(200);
				u2_printf("KS");
				delay_ms(200);
				u2_printf("DGZTKS");
				delay_ms(200);
			}			
		}
		Fun_Auto_DG12(1,pulse);        //将左肢抬高		
		delay_ms(1000);	     
		   
		for(j=0;j<t;j++)              //进行t此左肢康复训练
		{
			Fun_Auto_DG2(1,500000);     //向上运动			
			delay_ms(1000);			
			Fun_Auto_DG2(0,500000);     //向下运动			
			delay_ms(1000);	
		}
		Fun_Auto_DG12(0,pulse);       //将左肢放平到原来的位置
		//将标志位置位
		if((0==ZGB_Runed)&&(1==ZXB_Flag))         //左胳膊已运行脉冲为零，复位到初始状态
		{
			ZXB_Flag=0;		//设置状态标志位
			delay_ms(200);
			u2_printf("FW");
			delay_ms(200);
			u2_printf("DGZZJX");
			delay_ms(200);
		}
		if((0==ZT_Runed)&&(1==ZXT_Flag))         //左腿已运行脉冲为零，复位到初始状态
		{
			ZXT_Flag=0;		//设置状态标志位
			delay_ms(200);
			u2_printf("FW");
			delay_ms(200);
			u2_printf("DGZTFW");
			delay_ms(200);
		}
		DG_Relay=0;	       //继电器
	}
	else
	{
		LedAlm(100,"DGGS");
	}		
}

/***********************************************************************
 函数名      ：Fun_ZD_YZ(void)   
 函数功能    ：执行右肢吊挂康复训练
 输入        ：t吊挂次数
 输出        ：无 
                          
************************************************************************/
void Fun_ZD_YZ(int t)
{
	u32 pulse;     //吊挂运行脉冲数
	//病人只有平躺在床上才能进行吊挂康复训练
	if((0==ZB_Flag)&&(0==SQT_Flag)&&(0==XQT_Flag)&&(0==ZBQ_Flag)&&(0==ZF_Flag)&&(0==YF_Flag))
	{
		DG_Relay=1;	       //继电器
		if((strstr((const char *)USART2_RX_BUF,(const char *)"BYZ"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"BYZ")))//右胳膊
		{
			pulse=1000000;
			if(YXT_Flag==0)          //防止按键误触发，导致标志位置位
			{	
				YXB_Flag=1;		//设置状态标志位
				delay_ms(200);
				u2_printf("KS");
				delay_ms(200);
				u2_printf("DGYZKS");
				delay_ms(200);
			}			
		}
		if((strstr((const char *)USART2_RX_BUF,(const char *)"TYZ"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"TYZ")))//右腿
		{
			pulse=1500000;
			if(YXB_Flag==0)          //防止按键误触发，导致标志位置位
			{	
				YXT_Flag=1;		//设置状态标志位
				delay_ms(200);				
				u2_printf("KS");
				delay_ms(200);
				u2_printf("DGYTKS");	
				delay_ms(200);
			}			
		}
	
		int j;
		Fun_Auto_DG34(1,pulse);       //将右肢抬高
		delay_ms(1000);
		
		for(j=0;j<t;j++)                   //进行t次右肢康复训练
		{		
			Fun_Auto_DG3(1,500000);     //向上运动		
			delay_ms(1000);		
			Fun_Auto_DG3(0,500000);     //向下运动
			delay_ms(1000);		
		}	
		Fun_Auto_DG34(0,pulse);       //将右肢放平到原来的位置
		//将标志位置位
		if((0==YGB_Runed)&&(1==YXB_Flag))   //左胳膊已运行脉冲为零，复位到初始状态
		{
			YXB_Flag=0;		//设置状态标志位
			delay_ms(200);
			u2_printf("FW");
			delay_ms(200);			
			u2_printf("DGYZFW");
			delay_ms(200);
		}
		if((0==YT_Runed)&&(1==YXT_Flag))   //左腿已运行脉冲为零，复位到初始状态
		{
			YXT_Flag=0;		//设置状态标志位
			delay_ms(200);
			u2_printf("FW");
			delay_ms(200);
			u2_printf("DGYTFW");
			delay_ms(200);
		}	
		DG_Relay=0;	       //继电器
	}
	else
	 {
		 LedAlm(100,"DGGS");
	 }	
}

/***********************************************************************
 函数名      ：Fun_ZD_ZYZ(void)   
 函数功能    ：执行左右肢吊挂康复训练
 输入        ：t吊挂次数
 输出        ：无  
                          
***********************************************************************/
void Fun_ZD_ZYZ(int t)
{
	u32 pulse;	         //吊挂运行脉冲数
	int j;
	//病人只有平躺在床上才能进行吊挂康复训练
	if((0==ZB_Flag)&&(0==SQT_Flag)&&(0==XQT_Flag)&&(0==ZBQ_Flag)&&(0==ZF_Flag)&&(0==YF_Flag))
	{
		DG_Relay=1;	       //继电器
		if((strstr((const char *)USART2_RX_BUF,(const char *)"BLZ"))|| 
			(strstr((const char *)UART4_RX_BUF,(const char *)"BLZ")))//左右胳膊
		{
			pulse=1000000;
			if(ZYXT_Flag==0)       //防止按键误触发，导致标志位置位
			{	
				ZYXB_Flag=1;			//设置状态标志位
				delay_ms(200);
				u2_printf("KS");
				delay_ms(200);
				u2_printf("DGZYZKS");	
				delay_ms(200);				
			}
			else
			{
				ZYXB_Flag=0;			//设置状态标志位
			}
		}
		if((strstr((const char *)USART2_RX_BUF,(const char *)"TLZ"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"TLZ")))//左右腿
		{
			pulse=1500000;
			if(ZYXB_Flag==0)      //防止按键误触发，导致标志位置位
			{	
				ZYXT_Flag=1;		//设置状态标志位
				delay_ms(200);
				u2_printf("KS");
				delay_ms(200);
				u2_printf("DGZYTKS");	
				delay_ms(200);				
			}
			else
			{
				ZYXT_Flag=0;			//设置状态标志位
			}
		}	
		Fun_Auto_DG1234(1,pulse);     //将左右肢抬高，小臂抬得比大臂高
		delay_ms(1000);	     
			   
		for(j=0;j<t;j++)                     //进行t次康复训练
		{
			LED1=0;                          //在康复训练过程中LED0闪烁
			Fun_Auto_DG23(1,500000);     //小臂上升一定高度
			LED1=1;
			delay_ms(1000);
			LED1=0;
			Fun_Auto_DG23(0,500000);     //小臂下降一定高度
			delay_ms(1000);
			LED1=1;	
		}
			Fun_Auto_DG1234(0,pulse); //将左右肢放平到原来的位置
		//将标志位置位
		if((0==ZYGB_Runed)&&(1==ZYXB_Flag))    //左胳膊已运行脉冲为零，复位到初始状态
		{
			ZYXB_Flag=0;		//设置状态标志位
			delay_ms(200);
			u2_printf("FW");
			delay_ms(200);
			u2_printf("DGZYZFW");
			delay_ms(200);
		}
		if((0==ZYT_Runed)&&(1==ZYXT_Flag))    //左腿已运行脉冲为零，复位到初始状态
		{
			ZYXT_Flag=0;		//设置状态标志位
			delay_ms(200);
			u2_printf("FW");
			delay_ms(200);
			u2_printf("DGZYTFW");
			delay_ms(200);
		}	
		DG_Relay=0;	       //继电器
	}
	else
	{
		LedAlm(100,"DGGS");
	}	
}

/***********************************************************************
 函数名      ：Fun_SD_ZXB(void)  
 函数功能    ：手动执行左小臂
 输入        ：无
 输出        ：无                           
************************************************************************/
void Fun_SD_ZXB(void)
{
	 u8 direct;   //代表没某个动作运行的方向标志：1-正向运行；0-反向运行
	 static u8 runed_flag=0;
	//连锁功能只有在键锁打开、支背、坐便、翻身复位的情况下才能进行小臂/小腿康复训练
   if((0==ZB_Flag)&&(0==SQT_Flag)&&(0==XQT_Flag)&&(0==ZBQ_Flag)&&(0==ZF_Flag)&&(0==YF_Flag))
   {
		DG_Relay=1;	       //继电器
		 if(0==ZXB_Flag)                    //先将左肢抬高到一定高度
		{
			if((strstr((const char *)USART2_RX_BUF,(const char *)"BZSXS"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"BZSXS")))
			{
				delay_ms(200);
				u2_printf("KS");
				delay_ms(200);
				u2_printf("DGZXBKS");
				delay_ms(200);
				ZXB_Flag=1;		//设置状态标志位
				Fun_Hand_DG12(1,ZGB_Lim);  //将左肢抬高到一定高度，开始小臂康复训练
				runed_flag=1;
			}
		}				
		//左小臂向上运行
		if((strstr((const char *)USART2_RX_BUF,(const char *)"BZSXS"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"BZSXS"))||(1==runed_flag))
		{	
			runed_flag=0;
			if(ZXB_Lim>ZXB_Runed)
			{
				Fun_Hand_DG2(1,ZXB_Lim-ZXB_Runed);
				if(ZXB_Runed==ZXB_Lim)
				{
					ZXB_Flag=1;		//设置状态标志位
					delay_ms(200);
					u2_printf("JX");
					delay_ms(200);
					u2_printf("DGZXBJX");
					delay_ms(200);
				}
				else
				{
					ZXB_Flag=1;				//设置状态标志位
				}								
			}	
		}
		//左小臂向下运行
		if((strstr((const char *)USART2_RX_BUF,(const char *)"BZSXX"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"BZSXX")))
		{	
			if(ZXB_Runed>0)
			{
				Fun_Hand_DG2(0,ZXB_Runed);					
			}
			if(0==ZXB_Runed)               //若小臂复位，则将胳膊复位
			{
				Fun_Hand_DG12(0,ZGB_Runed);     //将左肢复位到水平状态 
			}
			if((0==ZXB_Runed)&&(0==ZGB_Runed))
			{
				ZXB_Flag=0;		//设置状态标志位
				delay_ms(200);
				u2_printf("FW");
				delay_ms(200);
				u2_printf("DGZXBFW");
				delay_ms(200);
			}
		}	
		DG_Relay=0;	       //继电器
	}
	else
	{
		LedAlm(100,"DGGS");
	}	
}

/***********************************************************************
 函数名      ：Fun_SD_ZXT(void)  
 函数功能    ：手动执行左小腿
 输入        ：无
 输出        ：无                           
************************************************************************/
void Fun_SD_ZXT(void)
{
	 u8 direct;   //代表没某个动作运行的方向标志：1-正向运行；0-反向运行
	 static u8 runed_flag=0;
	//连锁功能只有在键锁打开、左肢或左右肢上去、支背、坐便、翻身复位的情况下才能进行小臂/小腿康复训练
   if((0==ZB_Flag)&&(0==SQT_Flag)&&(0==XQT_Flag)&&(0==ZBQ_Flag)&&(0==ZF_Flag)&&(0==YF_Flag))
   {
		DG_Relay=1;	       //继电器
		 if(0==ZXT_Flag)                    //先将左肢抬高到一定高度
		{
			if((strstr((const char *)USART2_RX_BUF,(const char *)"TZSXS"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"TZSXS")))
			{
				delay_ms(200);
				u2_printf("KS");
				delay_ms(200);
				u2_printf("DGZXTKS");
				delay_ms(200);
				ZXT_Flag=1;		//设置状态标志位
				Fun_Hand_DG12(1,ZT_Lim);      //将左肢抬高到一定高度，开始小臂康复训练
				runed_flag=1;
			}
		}
		if((strstr((const char *)USART2_RX_BUF,(const char *)"TZSXS"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"TZSXS"))||(1==runed_flag))
		{	
			runed_flag=0;
			if(ZXT_Lim>ZXT_Runed)
			{
				Fun_Hand_DG2(1,ZXT_Lim-ZXT_Runed);	
				if(ZXT_Runed==ZXT_Lim)
				{
					ZXT_Flag=1;		//设置状态标志位
					delay_ms(200);
					u2_printf("JX");
					delay_ms(200);
					u2_printf("DGZXTJX");
					delay_ms(200);
				}
				else
				{
					ZXT_Flag=1;				//设置状态标志位
				}								
			}	
		}
		if((strstr((const char *)USART2_RX_BUF,(const char *)"TZSXX"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"TZSXX")))
		{	
			if(ZXT_Runed>0)
			{
				Fun_Hand_DG2(0,ZXT_Runed);					
			}
			if(0==ZXT_Runed)             //若小臂已运行脉冲为0，则将胳膊复位
			{
				Fun_Hand_DG12(0,ZT_Runed);   //将左肢复位到水平状态 
			}
			if((0==ZXT_Runed)&&(0==ZT_Runed))
			{
				ZXT_Flag=0;		//设置状态标志位
				delay_ms(200);
				u2_printf("FW");
				delay_ms(200);
				u2_printf("DGZXTFW");
				delay_ms(200);
			}			
		}	
		DG_Relay=0;	       //继电器
	}
	else
	{
		LedAlm(100,"DGGS");
	}	
}

/***********************************************************************
 函数名      ：Fun_SD_YXB(void)  
 函数功能    ：手动执行右小臂
 输入        ：无
 输出        ：无                           
************************************************************************/
void Fun_SD_YXB(void)
{
	 u8 direct;    //代表没某个动作运行的方向标志：1-正向运行；0-反向运行
	 static u8 runed_flag=0;
	//连锁功能只有在键锁打开、右肢或左右肢上去、支背、坐便、翻身复位的情况下才能进行小臂/小腿康复训练
   if((0==ZB_Flag)&&(0==SQT_Flag)&&(0==XQT_Flag)&&(0==ZBQ_Flag)&&(0==ZF_Flag)&&(0==YF_Flag))
   {
		DG_Relay=1;	       //继电器
		 if(0==YXB_Flag)                    //先将右肢抬高到一定高度
		{
			if((strstr((const char *)USART2_RX_BUF,(const char *)"BYSXS"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"BYSXS")))
			{
				delay_ms(200);
				u2_printf("KS");
				delay_ms(200);
				u2_printf("DGYXBKS");
				delay_ms(200);
				YXB_Flag=1;		//设置状态标志位
				Fun_Hand_DG34(1,YGB_Lim);       //将右肢抬高到一定高度，开始小臂康复训练
				runed_flag=1;
			}
		}
		//右小臂向上运行
		if((strstr((const char *)USART2_RX_BUF,(const char *)"BYSXS"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"BYSXS"))||(1==runed_flag))		
		{
			runed_flag=0;
			if(YXB_Lim>YXB_Runed)
			{
				Fun_Hand_DG3(1,YXB_Lim-YXB_Runed);	
				if(YXB_Runed==YXB_Lim)
				{
					YXB_Flag=1;		//设置状态标志位
					delay_ms(200);
					u2_printf("JX");
					delay_ms(200);
					u2_printf("DGYXBJX");
					delay_ms(200);
				}
				else
				{
					YXB_Flag=1;		//设置状态标志位		
				}								
			}	
		}			
		//右小臂向下运行
		if((strstr((const char *)USART2_RX_BUF,(const char *)"BYSXX"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"BYSXX")))
		{
			if(YXB_Runed>0)    //右小臂向下运动
			{
				Fun_Hand_DG3(0,YXB_Runed);					
			}
			if(YXB_Runed==0)    //若右小臂复位，则将右胳膊复位到水平位置
			{
				Fun_Hand_DG34(0,YGB_Runed); 
			}
			if((YXB_Runed==0)&&(0==YGB_Runed))   //标志位置位
			{
				YXB_Flag=0;			//设置状态标志位
				delay_ms(200);
				u2_printf("FW");
				delay_ms(200);
				u2_printf("DGYXBFW");
				delay_ms(200);
			}
		}
		DG_Relay=0;	       //继电器
	}
	else
	{
		LedAlm(100,"DGGS");
	}	
}

/***********************************************************************
 函数名      ：Fun_SD_YXT(void)  
 函数功能    ：手动执行右小腿
 输入        ：无
 输出        ：无                           
************************************************************************/
void Fun_SD_YXT(void)
{
	 u8 direct;    //代表没某个动作运行的方向标志：1-正向运行；0-反向运行
	 static u8 runed_flag;
	//连锁功能只有在键锁打开、右肢或左右肢上去、支背、坐便、翻身复位的情况下才能进行小臂/小腿康复训练
   if((0==ZB_Flag)&&(0==SQT_Flag)&&(0==XQT_Flag)&&(0==ZBQ_Flag)&&(0==ZF_Flag)&&(0==YF_Flag))
   {
		DG_Relay=1;	       //继电器
		 if(0==YXT_Flag)                    //先将左肢抬高到一定高度
		{
			if((strstr((const char *)USART2_RX_BUF,(const char *)"TYSXS"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"TYSXS")))
			{
				delay_ms(200);
				u2_printf("KS");
				delay_ms(200);
				u2_printf("DGYXTKS");
				delay_ms(200);
				YXT_Flag=1;		//设置状态标志位
				Fun_Hand_DG34(1,YT_Lim);       //将左肢抬高到一定高度，开始小臂康复训练
				runed_flag=1;
			}
		}
		//右小腿上行
	   if((strstr((const char *)USART2_RX_BUF,(const char *)"TYSXS"))||
		   (strstr((const char *)UART4_RX_BUF,(const char *)"TYSXS"))||(runed_flag==1))
		{
			runed_flag=0;		//设置状态标志位
			if(YXT_Lim>YXT_Runed)
			{
				Fun_Hand_DG3(1,YXT_Lim-YXT_Runed);	
				if(YXT_Runed==YXT_Lim)
				{
					YXT_Flag=1;		//设置状态标志位
					delay_ms(200);
					u2_printf("JX");
					delay_ms(200);
					u2_printf("DGYXTJX");
					delay_ms(200);
				}
				else
				{
					YXT_Flag=1;			//设置状态标志位				
				}								
			}	
		}
		//向下运行
		if((strstr((const char *)USART2_RX_BUF,(const char *)"TYSXX"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"TYSXX")))
		{
			if(YXT_Runed>0)     //右小腿向下运行
			{
				Fun_Hand_DG3(0,YXT_Runed);					
			}
			if(0==YXT_Runed)    //若右小腿复位，则将左肢放平到水平位置
			{
				Fun_Hand_DG34(0,YT_Runed);
			}
			if((0==YXT_Runed)&&(0==YT_Runed))  //标志位复位
			{
				YXT_Flag=0;		//设置状态标志位
				delay_ms(200);
				u2_printf("FW");
				delay_ms(200);
				u2_printf("DGYXTFW");
				delay_ms(200);
			}
		}
		DG_Relay=0;	       //继电器
	}
	else
	{
		LedAlm(100,"DGGS");
	}	
}

/***********************************************************************
 函数名      ：Fun_SD_ZDB(void)  
 函数功能    ：手动执行左大臂
 输入        ：无
 输出        ：无                           
************************************************************************/
void Fun_SD_ZDB(void)
{
	//连锁功能只有在键锁打开、左肢或左右肢上去、支背、坐便、翻身复位的情况下才能进行大臂/大腿康复训练
   if((0==ZB_Flag)&&(0==SQT_Flag)&&(0==XQT_Flag)&&(0==ZBQ_Flag)&&(0==ZF_Flag)&&(0==YF_Flag))
   {
		DG_Relay=1;	       //继电器
		 //向上运行		
		if((strstr((const char *)USART2_RX_BUF,(const char *)"BZSDS"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"BZSDS")))
		{
			if(ZDB_Lim>ZDB_Runed)
			{
			    if(0==ZDB_Flag)
				{
					delay_ms(200);
					u2_printf("KS");
					delay_ms(200);
					u2_printf("DGZDBKS");
					delay_ms(200);
				}
				ZDB_Flag=1;		//设置状态标志位
				Fun_Hand_DG12(1,ZDB_Lim-ZDB_Runed);	
				if(ZDB_Runed==ZDB_Lim)
				{
					ZDB_Flag=1;		//设置状态标志位
					delay_ms(200);
					u2_printf("JX");
					delay_ms(200);
					u2_printf("DGZDBJX");
				}
				else
				{
					ZDB_Flag=1;		//设置状态标志位
				}								
			}	
		}
         //向下运行		
		if((strstr((const char *)USART2_RX_BUF,(const char *)"BZSDX"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"BZSDX")))
		{
			if(ZDB_Runed>0)
			{
				Fun_Hand_DG12(0,ZDB_Runed);
				if(0==ZDB_Runed)
				{					
					ZDB_Flag=0;		//设置状态标志位
					delay_ms(200);
					u2_printf("FW");
					delay_ms(200);
					u2_printf("DGZDBFW");
					delay_ms(200);
				}
				else
				{
					ZDB_Flag=1;			//设置状态标志位		
				}					
			}				
		}
		DG_Relay=0;	       //继电器
	}
	else
	{
		LedAlm(100,"DGGS");
	}	
}

/***********************************************************************
 函数名      ：Uart_Hand_ArmLeg_Post_Left(void)  
 函数功能    ：手动执行左大腿
 输入        ：无
 输出        ：无                           
************************************************************************/
void Fun_SD_ZDT(void)
{
	//连锁功能只有在键锁打开、左肢或左右肢上去、支背、坐便、翻身复位的情况下才能进行大臂/大腿康复训练
   if((0==ZB_Flag)&&(0==SQT_Flag)&&(0==XQT_Flag)&&(0==ZBQ_Flag)&&(0==ZF_Flag)&&(0==YF_Flag))
   {
		DG_Relay=1;	       //继电器
		 //向上运行		
		if((strstr((const char *)USART2_RX_BUF,(const char *)"TZSDS"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"TZSDS")))
		{
			if(ZDT_Lim>ZDT_Runed)
			{
				if(0==ZDT_Flag)
				{
					delay_ms(200);
					u2_printf("KS");
					delay_ms(200);
					u2_printf("DGZDTKS");
					delay_ms(200);
				}
				ZDT_Flag=1;		//设置状态标志位
				Fun_Hand_DG12(1,ZDT_Lim-ZDT_Runed);	
				if(ZDT_Runed==ZDT_Lim)
				{
					ZDT_Flag=1;		//设置状态标志位
					delay_ms(200);
					u2_printf("JX");
					delay_ms(200);
					u2_printf("DGZDTJX");
					delay_ms(200);
				}
				else
				{
					ZDT_Flag=1;						//设置状态标志位		
				}								
			}	
		}
		//向下运行
		if((strstr((const char *)USART2_RX_BUF,(const char *)"TZSDX"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"TZSDX")))
		{
			if(ZDT_Runed>0)
			{
				Fun_Hand_DG12(0,ZDT_Runed);
				if(0==ZDT_Runed)
				{					
					ZDT_Flag=0;		//设置状态标志位
					delay_ms(200);
					u2_printf("FW");
					delay_ms(200);
					u2_printf("DGZDTFW");
					delay_ms(200);
				}
				else
				{
					ZDT_Flag=1;					//设置状态标志位
				}					
			}				
		}
		DG_Relay=0;	       //继电器
	}
	else
	{
		LedAlm(100,"DGGS");
	}	
}

/***********************************************************************
 函数名      ：Fun_SD_YDB(void)  
 函数功能    ：手动执行右大臂
 输入        ：无
 输出        ：无                           
************************************************************************/
void Fun_SD_YDB(void)
{
	//连锁功能只有在键锁打开、右肢或左右肢上去、支背、坐便、翻身复位的情况下才能进行大臂/大腿康复训练
   if((0==ZB_Flag)&&(0==SQT_Flag)&&(0==XQT_Flag)&&(0==ZBQ_Flag)&&(0==ZF_Flag)&&(0==YF_Flag))
   {
		DG_Relay=1;	       //继电器
		 //向上运行
		if((strstr((const char *)USART2_RX_BUF,(const char *)"BYSDS"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"BYSDS")))
		{
			if(YDB_Lim>YDB_Runed)
			{
				if(0==YDB_Flag)
				{
					delay_ms(200);
					u2_printf("KS");
					delay_ms(200);
					u2_printf("DGYDBKS");
					delay_ms(200);
				}
				YDB_Flag=1;		//设置状态标志位
				Fun_Hand_DG34(1,YDB_Lim-YDB_Runed);	
				if(YDB_Runed==YDB_Lim)
				{
					YDB_Flag=1;		//设置状态标志位
					delay_ms(200);
					u2_printf("JX");
					delay_ms(200);
					u2_printf("DGYDBJX");
					delay_ms(200);
				}
				else
				{
					YDB_Flag=1;				//设置状态标志位				
				}								
			}	
		}
		//向下运行
		if((strstr((const char *)USART2_RX_BUF,(const char *)"BYSDX"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"BYSDX")))
		{
			if(YDB_Runed>0)
			{
				Fun_Hand_DG34(0,YDB_Runed);
				if(0==YDB_Runed)
				{
					YDB_Flag=0;		//设置状态标志位
					delay_ms(200);
					u2_printf("FW");
					delay_ms(200);
					u2_printf("DGYDBFW");
					delay_ms(200);
				}
				else
				{
					YDB_Flag=1;	//设置状态标志位
				}					
			}				
		}
		DG_Relay=0;	       //继电器
	}
	else
	{
		LedAlm(100,"DGGS");
	}	
}

/***********************************************************************
 函数名      ：Fun_SD_YDT(void)  
 函数功能    ：手动执行右大腿
 输入        ：无
 输出        ：无                           
************************************************************************/
void Fun_SD_YDT(void)
{
	//连锁功能只有在键锁打开、右肢或左右肢上去、支背、坐便、翻身复位的情况下才能进行大臂/大腿康复训练
   if((0==ZB_Flag)&&(0==SQT_Flag)&&(0==XQT_Flag)&&(0==ZBQ_Flag)&&(0==ZF_Flag)&&(0==YF_Flag))
   {
		DG_Relay=1;	       //继电器
		 //同过上下行判断脉冲累计
		if((strstr((const char *)USART2_RX_BUF,(const char *)"TYSDS"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"TYSDS")))
		{
			if(YDT_Lim>YDT_Runed)
			{
				if(0==YDT_Flag)
				{
					delay_ms(200);
					u2_printf("FW");
					delay_ms(200);
					u2_printf("LegPostRightHandStart");
					delay_ms(200);
				}
				YDT_Flag=1;		//设置状态标志位
				Fun_Hand_DG34(1,YDT_Lim-YDT_Runed);	
				if(YDT_Runed==YDT_Lim)
				{
					YDT_Flag=1;		//设置状态标志位
					delay_ms(200);
					u2_printf("JX");
					delay_ms(200);
					u2_printf("LegPostRightHandLim");
					delay_ms(200);
				}
				else
				{
					YDT_Flag=1;	//设置状态标志位
				}								
			}	
		}
		//向下运行
		if((strstr((const char *)USART2_RX_BUF,(const char *)"TYSDX"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"TYSDX")))
		{
			if(YDT_Runed>0)
			{
				Fun_Hand_DG34(0,YDT_Runed);
				if(0==YDT_Runed)
				{
					YDT_Flag=0;		//设置状态标志位
					delay_ms(200);
					u2_printf("FW");
					delay_ms(200);
					u2_printf("DGYDTFW");
					delay_ms(200);
				}
				else
				{
					YDT_Flag=1;		//设置状态标志位
				}					
			}			
		}
		DG_Relay=0;	       //继电器
	}
	else
	{
		LedAlm(100,"DGGS");
	}	
}

/***********************************************************************
 函数名      ：Fun_SD_ZB(void)  
 函数功能    ：手动执行左大小臂
 输入        ：无
 输出        ：无                           
************************************************************************/
void Fun_SD_ZB(void)
{
	 u8 direct;    //代表没某个动作运行的方向标志：1-正向运行；0-反向运行
	//连锁功能只有在键锁打开、左肢或左右肢上去、支背、坐便、翻身复位的情况下才能进行大臂/大腿康复训练
   if((0==ZB_Flag)&&(0==SQT_Flag)&&(0==XQT_Flag)&&(0==ZBQ_Flag)&&(0==ZF_Flag)&&(0==YF_Flag))
   {
      DG_Relay=1;	       //继电器
		 //向上运行		
		if((strstr((const char *)USART2_RX_BUF,(const char *)"BZSBS"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"BZSBS")))
		{
			 //先运行左大臂
			if(ZDB_Lim>ZDB_Runed)
			{
				if(0==ZDXB_Flag)
				{
					delay_ms(200);
					u2_printf("KS");
					delay_ms(200);
					u2_printf("DGZZKS");
					delay_ms(200);
				}
				ZDXB_Flag=1;		//设置状态标志位
				Fun_Hand_DG12(1,ZDB_Lim-ZDB_Runed);	
				if(ZDB_Runed==ZDB_Lim)
				{
					ZDXB_Flag=1;							//设置状态标志位
				}
				else
				{
					ZDXB_Flag=1;					//设置状态标志位			
				}								
			}
			//再运行左小臂
			if((ZXB_Lim>ZXB_Runed)&&(ZDB_Runed==ZDB_Lim))  
			{
				Fun_Hand_DG2(1,ZXB_Lim-ZXB_Runed);	
				if(ZXB_Runed==ZXB_Lim)
				{
					delay_ms(200);
					u2_printf("JX");
					delay_ms(200);
					u2_printf("DGZZJX");
					delay_ms(200);
				}
			}			
		}	
		//向下运行
		if((strstr((const char *)USART2_RX_BUF,(const char *)"BZSBX"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"BZSBX")))
		{
			//先运行左小臂
			if(ZXB_Runed>0)   
			{
				Fun_Hand_DG2(0,ZXB_Runed);					
			}
			//再运行左大臂
			if((ZDB_Runed>0)&&(0==ZXB_Runed))
			{
				Fun_Hand_DG12(0,ZDB_Runed);	
			}
			if((0==ZDB_Runed)&&(0==ZXB_Runed))
			{
				ZDXB_Flag=0;		//设置状态标志位
				delay_ms(200);
				u2_printf("FW");
				delay_ms(200);
				u2_printf("DGZZFW");
			}
		}
		DG_Relay=0;	       //继电器
	}
	else
	{
		LedAlm(100,"DGGS");
	}	
}

/***********************************************************************
 函数名      ：Uart_Hand_ArmLeg_Fore_Post_Left(void)  
 函数功能    ：手动执行左大小腿
 输入        ：无
 输出        ：无                           
************************************************************************/
void Fun_SD_ZT(void)
{
	 u8 direct;    //代表没某个动作运行的方向标志：1-正向运行；0-反向运行
	//连锁功能只有在键锁打开、左肢或左右肢上去、支背、坐便、翻身复位的情况下才能进行大臂/大腿康复训练
   if((0==ZB_Flag)&&(0==SQT_Flag)&&(0==XQT_Flag)&&(0==ZBQ_Flag)&&(0==ZF_Flag)&&(0==YF_Flag))
   {
     DG_Relay=1;	       //继电器
		 //向上运行		
		if((strstr((const char *)USART2_RX_BUF,(const char *)"TZSTS"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"TZSTS")))
		{
			 //先运行左大腿
			if(ZDT_Lim>ZDT_Runed)
			{
				if(0==ZDXT_Flag)
				{
					delay_ms(200);
					u2_printf("KS");
					delay_ms(200);
					u2_printf("DGZTKS");
				}
				ZDXT_Flag=1;		//设置状态标志位
				Fun_Hand_DG12(1,ZDT_Lim-ZDT_Runed);	
				if(ZDT_Runed==ZDT_Lim)
				{
					ZDXT_Flag=1;		//设置状态标志位
				}
				else
				{
					ZDXT_Flag=1;		//设置状态标志位
				}								
			}
			//再运行左小腿
			if((ZXT_Lim>ZXT_Runed)&&(ZDT_Runed==ZDT_Lim))  
			{
				Fun_Hand_DG2(1,ZXT_Lim-ZXB_Runed);
				if(ZXB_Runed==ZXT_Lim)
				{
					delay_ms(200);
					u2_printf("JX");
					delay_ms(200);
					u2_printf("DGZTJX");
				}
			}							
		}
		//向下运行
		if((strstr((const char *)USART2_RX_BUF,(const char *)"TZSTX"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"TZSTX")))
		{
			//先运行左小腿
			if(ZXT_Runed>0)   
			{
				Fun_Hand_DG2(0,ZXT_Runed);					
			}
			//再运行左大腿
			if((ZDT_Runed>0)&&(0==ZXT_Runed))
			{
				Fun_Hand_DG12(0,ZDT_Runed);	
			}			
			if((0==ZDT_Runed)&&(0==ZXT_Runed))
			{
				ZDXT_Flag=0;		//设置状态标志位
				delay_ms(200);
				u2_printf("FW");
				delay_ms(200);
				u2_printf("DGZTFW");
			}				
		}
		DG_Relay=0;	       //继电器
	}
	else
	{
		LedAlm(100,"DGGS");
	}	
}

/***********************************************************************
 函数名      ：Fun_SD_YB(void)  
 函数功能    ：手动执行右大小臂
 输入        ：无
 输出        ：无                           
************************************************************************/
void Fun_SD_YB(void)
{
	 u8 direct;     //代表没某个动作运行的方向标志：1-正向运行；0-反向运行
	//连锁功能只有在键锁打开、右肢或左右肢上去、支背、坐便、翻身复位的情况下才能进行大臂/大腿康复训练
   if((0==ZB_Flag)&&(0==SQT_Flag)&&(0==XQT_Flag)&&(0==ZBQ_Flag)&&(0==ZF_Flag)&&(0==YF_Flag))
   {
		DG_Relay=1;	       //继电器
		 //同过上下行判断脉冲累计
		if((strstr((const char *)USART2_RX_BUF,(const char *)"BYSBS"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"BYSBS")))
		{
			 //先运行右大臂
			if(YDB_Lim>YDB_Runed)
			{
				if(0==YDXB_Flag)
				{
					delay_ms(200);
					u2_printf("KS");
					delay_ms(200);
					u2_printf("DGYZKS");
				}
				YDXB_Flag=1;		//设置状态标志位
				Fun_Hand_DG34(1,YDB_Lim-YDB_Runed);	
				if(YDB_Runed==YDB_Lim)
				{
					YDXB_Flag=1;		//设置状态标志位
				}
				else
				{
					YDXB_Flag=1;			//设置状态标志位					
				}								
			}
			//再运行右小臂
			if((YXB_Lim>YXB_Runed)&&(YDB_Runed==YDB_Lim))  
			{
				Fun_Hand_DG3(1,YXB_Lim-YXB_Runed);
				if(YXB_Runed==YXB_Lim)
				{
					delay_ms(200);
					u2_printf("JX");
					delay_ms(200);
					u2_printf("DGYZJX");
				}
			}	
		}			
		if((strstr((const char *)USART2_RX_BUF,(const char *)"BYSBX"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"BYSBX")))
		{
			//先运行右小臂
			if(YXB_Runed>0)   
			{
				Fun_Hand_DG3(0,YXB_Runed);					
			}
			//再运行右大臂
			if((YDB_Runed>0)&&(0==YXB_Runed))
			{
				Fun_Hand_DG34(0,YDB_Runed);	
			}
			if((0==YDB_Runed)&&(0==YXB_Runed))
			{
				YDXB_Flag=0;		//设置状态标志位
				delay_ms(200);
				u2_printf("FW");
				delay_ms(200);
				u2_printf("DGYZFW");
			}			
		}
		DG_Relay=0;	       //继电器
	}
	else
	{
		LedAlm(100,"DGGS");
	}	
}

/***********************************************************************
 函数名      ：Fun_SD_YT(void)  
 函数功能    ：手动执行右大小腿
 输入        ：无
 输出        ：无                           
************************************************************************/
void Fun_SD_YT(void)
{
	 u8 direct;     //代表没某个动作运行的方向标志：1-正向运行；0-反向运行
	//连锁功能只有在键锁打开、右肢或左右肢上去、支背、坐便、翻身复位的情况下才能进行大臂/大腿康复训练
   if((0==ZB_Flag)&&(0==SQT_Flag)&&(0==XQT_Flag)&&(0==ZBQ_Flag)&&(0==ZF_Flag)&&(0==YF_Flag))
   {
		DG_Relay=1;	       //继电器
		 //同过上下行判断脉冲累计
		if((strstr((const char *)USART2_RX_BUF,(const char *)"TYSTS"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"TYSTS")))
		{
			 //先运行右大腿
			if(YDT_Lim>YDT_Runed)
			{
				if(0==YDXT_Flag)
				{
					delay_ms(200);
					u2_printf("KS");
					delay_ms(200);
					u2_printf("DGYTKS");
				}
				YDXT_Flag=1;		//设置状态标志位
				Fun_Hand_DG34(1,YDT_Lim-YDT_Runed);	
				if(YDT_Runed==YDT_Lim)
				{
					YDXT_Flag=1;		//设置状态标志位
				}
				else
				{
					YDXT_Flag=1;		//设置状态标志位	
				}								
			}
			//再运行右小腿
			if((YXT_Lim>YXT_Runed)&&(YDT_Runed==YDT_Lim))  
			{
				Fun_Hand_DG3(1,YXT_Lim-YXT_Runed);
				if(YXT_Runed==YXT_Lim)
				{
					delay_ms(200);
					u2_printf("JX");
					delay_ms(200);
					u2_printf("DGYTJX");
				}
			}	
		}			
		if((strstr((const char *)USART2_RX_BUF,(const char *)"TYSTX"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"TYSTX")))
		{
			//先运行右小腿
			if(YXT_Runed>0)   
			{
				Fun_Hand_DG3(0,YXT_Runed);					
			}
			//再运行右大腿
			if((YDT_Runed>0)&&(0==YXT_Runed))
			{
				Fun_Hand_DG34(0,YDT_Runed);	
			}
			if((0==YDT_Runed)&&(0==YXT_Runed))
			{
				YDXT_Flag=0;		//设置状态标志位
				delay_ms(200);
				u2_printf("FW");
				delay_ms(200);
				u2_printf("DGYTFW");
			}				
		}
		DG_Relay=0;	       //继电器
	}
	else
	{
		LedAlm(100,"DGGS");
	}	
}

/***********************************************************************
 函数名      ：Fun_SD_ZYXB(void)  
 函数功能    ：手动执行左右小臂
 输入        ：无
 输出        ：无                           
************************************************************************/
void Fun_SD_ZYXB(void)
{
	 u8 direct;     //代表没某个动作运行的方向标志：1-正向运行；0-反向运行
	 static u8 runed_flag;
	//连锁功能只有在键锁打开、左右肢上去、支背、坐便、翻身复位的情况下才能进行左右小臂/小腿康复训练
   if((0==ZB_Flag)&&(0==SQT_Flag)&&(0==XQT_Flag)&&(0==ZBQ_Flag)&&(0==ZF_Flag)&&(0==YF_Flag))
   {
		DG_Relay=1;	       //继电器
		 if(0==ZYXB_Flag)    //先将左右肢抬到一定高度
		{
			if((strstr((const char *)USART2_RX_BUF,(const char *)"BLSXS"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"BLSXS")))
			{
				delay_ms(200);
				u2_printf("KS");
				delay_ms(200);
				u2_printf("DGZYXBKS");
				delay_ms(200);
				ZYXB_Flag=1;		//设置状态标志位
				Fun_Hand_DG1234(1,ZYGB_Lim);
				runed_flag=1;		//设置状态标志位
			}
		}
		//向上运行
		if((strstr((const char *)USART2_RX_BUF,(const char *)"BLSXS"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"BLSXS"))||(1==runed_flag))
		{	
			if(ZYXB_Lim>ZYXB_Runed)
			{
				runed_flag=0;		//设置状态标志位
				Fun_Hand_DG23(1,ZYXB_Lim-ZYXB_Runed);	
				if(ZYXB_Runed==ZYXB_Lim)
				{
					ZYXB_Flag=1;		//设置状态标志位
					delay_ms(200);
					u2_printf("JX");
					delay_ms(200);
					u2_printf("DGZYXBJX");
				}
				else
				{
					ZYXB_Flag=1;					//设置状态标志位			
				}								
			}	
		}	
		//向下运行
		if((strstr((const char *)USART2_RX_BUF,(const char *)"BLSXX"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"BLSXX")))
		{
			if(ZYXB_Runed>0)      //左右小臂向下运行
			{
				Fun_Hand_DG23(0,ZYXB_Runed);					
			}
			if(ZYXB_Runed==0)     //若左右小臂复位，则将左右肢复位到水平位置
			{
				Fun_Hand_DG1234(0,ZYGB_Runed);
			}
			if((ZYXB_Runed==0)&&(0==ZYGB_Runed))  //标志位置位
			{
				ZYXB_Flag=0;		//设置状态标志位
				delay_ms(200);
				u2_printf("FW");
				delay_ms(200);
				u2_printf("DGZYXBFW");
			}
		}
		DG_Relay=0;	       //继电器
	}
	else
	{
		LedAlm(100,"DGGS");
	}	
}

/***********************************************************************
 函数名      ：Fun_SD_ZYXT(void)  
 函数功能    ：手动执行左右小腿
 输入        ：无
 输出        ：无                           
************************************************************************/
void Fun_SD_ZYXT(void)
{
	 u8 direct;     //代表没某个动作运行的方向标志：1-正向运行；0-反向运行
	 static u8 runed_flag;
	//连锁功能只有在键锁打开、左右肢上去、支背、坐便、翻身复位的情况下才能进行左右小臂/小腿康复训练
   if((0==ZB_Flag)&&(0==SQT_Flag)&&(0==XQT_Flag)&&(0==ZBQ_Flag)&&(0==ZF_Flag)&&(0==YF_Flag))
   {
	    DG_Relay=1;	       //继电器
		 if(0==ZYXT_Flag)
		{
			if((strstr((const char *)USART2_RX_BUF,(const char *)"TLSXS"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"TLSXS")))
			{
				delay_ms(200);
				u2_printf("KS");
				delay_ms(200);
				u2_printf("DGZYXTKS");
				delay_ms(200);
				ZYXT_Flag=1;		//设置状态标志位
				Fun_Hand_DG1234(1,ZYT_Lim);
				runed_flag=1;		//设置状态标志位
			}				
		}
		//同过上下行判断脉冲累计
		if((strstr((const char *)USART2_RX_BUF,(const char *)"TLSXS"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"TLSXS"))||(1==runed_flag))
		{
			if(ZYXT_Lim>ZYXT_Runed)
			{
				runed_flag=0;
				Fun_Hand_DG23(1,ZYXT_Lim-ZYXT_Runed);	
				if(ZYXT_Runed==ZYXT_Lim)
				{
					ZYXT_Flag=1;		//设置状态标志位
					delay_ms(200);
					u2_printf("JX");
					delay_ms(200);
					u2_printf("DGZYXTJX");
				}
				else
				{
					ZYXT_Flag=1;				//设置状态标志位				
				}								
			}	
		}
		//向下运行
		if((strstr((const char *)USART2_RX_BUF,(const char *)"TLSXX"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"TLSXX")))
		{
			if(ZYXT_Runed>0)    //左右小腿向下运行
			{
				Fun_Hand_DG23(0,ZYXT_Runed);					
			}
			if(ZYXT_Runed==0)    //若左右小腿复位，则将左右腿复位到水平位置
			{
				Fun_Hand_DG1234(0,ZYT_Runed);
			}
			if((ZYXT_Runed==0)&&(0==ZYT_Runed))   //标志位置位
			{
				ZYXT_Flag=0;		//设置状态标志位
				delay_ms(200);
				u2_printf("FW");
				delay_ms(200);
				u2_printf("DGZYXTFW");
			}
		}
		DG_Relay=0;	       //继电器
	}
	else
	{
		LedAlm(100,"DGGS");	
	}	
}

/***********************************************************************
 函数名      ：Fun_SD_ZYDB(void)  
 函数功能    ：手动执行左右大臂
 输入        ：无
 输出        ：无                           
************************************************************************/
void Fun_SD_ZYDB(void)
{
	 u8 direct;    //代表没某个动作运行的方向标志：1-正向运行；0-反向运行
//连锁功能只有在键锁打开、左右肢上去、支背、坐便、翻身复位的情况下才能进行左右大臂/大腿康复训练
   if((0==ZB_Flag)&&(0==SQT_Flag)&&(0==XQT_Flag)&&(0==ZBQ_Flag)&&(0==ZF_Flag)&&(0==YF_Flag))
   {
		DG_Relay=1;	       //继电器
		 //同过上下行判断脉冲累计		
		if((strstr((const char *)USART2_RX_BUF,(const char *)"BLSDS"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"BLSDS")))
		{
			if(ZYDB_Lim>ZYDB_Runed)
			{
				if(0==ZYDB_Flag)
				{
					delay_ms(200);
					u2_printf("KS");
					delay_ms(200);
					u2_printf("DGZYDBKS");
				}
				ZYDB_Flag=1;		//设置状态标志位
				Fun_Hand_DG1234(1,ZYDB_Lim-ZYDB_Runed);	
				if(ZYDB_Runed==ZYDB_Lim)
				{
					ZYDB_Flag=1;		//设置状态标志位
					delay_ms(200);
					u2_printf("JX");
					delay_ms(200);
					u2_printf("DGZYDBJX");
				}
				else
				{
					ZYDB_Flag=1;					//设置状态标志位			
				}								
			}	
		}			
		if((strstr((const char *)USART2_RX_BUF,(const char *)"BLSDX"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"BLSDX")))
		{
			if(ZYDB_Runed>0)
			{
				Fun_Hand_DG1234(0,ZYDB_Runed);
				if(0==ZYDB_Runed)
				{
					ZYDB_Flag=0;		//设置状态标志位
					delay_ms(200);
					u2_printf("FW");
					delay_ms(200);
					u2_printf("DGZYDBFW");
				}
				else
				{
					ZYDB_Flag=1;			//设置状态标志位		
				}					
			}				
		}
		DG_Relay=0;	       //继电器
	}
	else
	{
		LedAlm(100,"DGGS");
	}	
}

/***********************************************************************
 函数名      ：Fun_SD_ZYDT(void)  
 函数功能    ：手动执行左右大腿
 输入        ：无
 输出        ：无                           
************************************************************************/
void Fun_SD_ZYDT(void)
{
	 u8 direct;    //代表没某个动作运行的方向标志：1-正向运行；0-反向运行
//连锁功能只有在键锁打开、左右肢上去、支背、坐便、翻身复位的情况下才能进行左右大臂/大腿康复训练
   if((0==ZB_Flag)&&(0==SQT_Flag)&&(0==XQT_Flag)&&(0==ZBQ_Flag)&&(0==ZF_Flag)&&(0==YF_Flag))
   {
		DG_Relay=1;	       //继电器
		 //同过上下行判断脉冲累计		
		if((strstr((const char *)USART2_RX_BUF,(const char *)"TLSDS"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"TLSDS")))
		{
			if(ZYDT_Lim>ZYDT_Runed)
			{
				if(0==ZYDT_Flag)
				{
					delay_ms(200);
					u2_printf("KS");
					delay_ms(200);
					u2_printf("DGZYDTKS");
				}
				ZYDT_Flag=1;			//设置状态标志位
				Fun_Hand_DG1234(1,ZYDT_Lim-ZYDT_Runed);	
				if(ZYDT_Runed==ZYDT_Lim)
				{
					ZYDT_Flag=1;		//设置状态标志位
					delay_ms(200);
					u2_printf("JX");
					delay_ms(200);
					u2_printf("DGZYDTJX");
				}
				else
				{
					ZYDT_Flag=1;					//设置状态标志位				
				}								
			}	
		}			
		if((strstr((const char *)USART2_RX_BUF,(const char *)"TLSDX"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"TLSDX")))
		{
			if(ZYDT_Runed>0)
			{
				Fun_Hand_DG1234(0,ZYDT_Runed);
				if(0==ZYDT_Runed)
				{
					ZYDT_Flag=0;			//设置状态标志位
					delay_ms(200);
					u2_printf("FW");
					delay_ms(200);
					u2_printf("DGZYDTFW");
				}
				else
				{
					ZYDT_Flag=1;			//设置状态标志位		
				}					
			}			
		}
		DG_Relay=0;	       //继电器
	}
	else
	{
		LedAlm(100,"DGGS");
	}	
}

/***********************************************************************
 函数名      ：Fun_SD_ZYB(void)  
 函数功能    ：手动执行左右大小臂
 输入        ：无
 输出        ：无                           
************************************************************************/
void Fun_SD_ZYB(void)
{
	 u8 direct;     //代表没某个动作运行的方向标志：1-正向运行；0-反向运行
//连锁功能只有在键锁打开、左右肢上去、支背、坐便、翻身复位的情况下才能进行大臂/大腿康复训练
   if((0==ZB_Flag)&&(0==SQT_Flag)&&(0==XQT_Flag)&&(0==ZBQ_Flag)&&(0==ZF_Flag)&&(0==YF_Flag))
   {
		DG_Relay=1;	       //继电器
		 //向上运动
		if((strstr((const char *)USART2_RX_BUF,(const char *)"BLSBS"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"BLSBS")))
		{
			 //先运行左右大臂
			if(ZYDB_Lim>ZYDB_Runed)
			{
				if(0==ZYDXB_Flag)
				{
					delay_ms(200);
					u2_printf("KS");
					delay_ms(200);
					u2_printf("DGZYZKS");
				}
				ZYDXB_Flag=1;		//设置状态标志位
				Fun_Hand_DG1234(1,ZYDB_Lim-ZYDB_Runed);	
				if(ZYDB_Runed==ZYDB_Lim)
				{
					ZYDXB_Flag=1;		//设置状态标志位
				}
				else
				{
					ZYDXB_Flag=1;		//设置状态标志位			
				}								
			}
			//再运行左右小臂
			if((ZYXB_Lim>ZYXB_Runed)&&(ZYDB_Runed==ZYDB_Lim))  
			{
				Fun_Hand_DG23(1,ZYXB_Lim-ZYXB_Runed);
				if(ZYXB_Runed==ZYXB_Lim)
				{
					
					delay_ms(200);
					u2_printf("JX");
					delay_ms(200);
					u2_printf("DGZYZJX");
				}
			}	
		}			
		if((strstr((const char *)USART2_RX_BUF,(const char *)"BLSBX"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"BLSBX")))
		{
			//先运行左右小臂
			if(ZYXB_Runed>0)   
			{
				Fun_Hand_DG23(0,ZYXB_Runed);					
			}
			//再运行左右大臂
			if((ZYDB_Runed>0)&&(0==ZYXB_Runed))
			{
				Fun_Hand_DG1234(0,ZYDB_Runed);	
			}
			if((0==ZYDB_Runed)&&(0==ZYXB_Runed))
			{
				ZYDXB_Flag=0;		//设置状态标志位
				delay_ms(200);
				u2_printf("FW");
				delay_ms(200);
				u2_printf("DGZYZFW");
			}				
		}
		DG_Relay=0;	       //继电器
	}
	else
	{
		LedAlm(100,"DGGS");
	}	
}

/***********************************************************************
 函数名      ：Fun_SD_ZYT(void)  
 函数功能    ：手动执行左右大小腿
 输入        ：无
 输出        ：无                           
************************************************************************/
void Fun_SD_ZYT(void)
{
	 u8 direct;     //代表没某个动作运行的方向标志：1-正向运行；0-反向运行
//连锁功能只有在键锁打开、左右肢上去、支背、坐便、翻身复位的情况下才能进行大臂/大腿康复训练
   if((0==ZB_Flag)&&(0==SQT_Flag)&&(0==XQT_Flag)&&(0==ZBQ_Flag)&&(0==ZF_Flag)&&(0==YF_Flag))
   {
		DG_Relay=1;	       //继电器
		 //同过上下行判断脉冲累计
		if((strstr((const char *)USART2_RX_BUF,(const char *)"TLSTS"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"TLSTS")))
		{
			 //先运行左右大腿
			if(ZYDT_Lim>ZYDT_Runed)
			{
				if(0==ZYDXT_Flag)
				{
					delay_ms(200);
					u2_printf("KS");
					delay_ms(200);
					u2_printf("DGZYTKS");
				}
				ZYDXT_Flag=1;		//设置状态标志位
				Fun_Hand_DG1234(1,ZYDT_Lim-ZYDT_Runed);	
				if(ZYDT_Runed==ZYDT_Lim)
				{
					ZYDXT_Flag=1;		//设置状态标志位
				}
				else
				{
					ZYDXT_Flag=1;				//设置状态标志位				
				}								
			}
			//再运行左右小腿
			if((ZYXT_Lim>ZYXT_Runed)&&(ZYDT_Runed==ZYDT_Lim))  
			{
				Fun_Hand_DG23(1,ZYXT_Lim-ZYXT_Runed);
				if(ZYXT_Runed==ZYXT_Lim)
				{
					delay_ms(200);
					u2_printf("JX");
					delay_ms(200);
					u2_printf("DGZYTJX");
				}
			}
		}			
		if((strstr((const char *)USART2_RX_BUF,(const char *)"TLSTX"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"TLSTX")))
		{
			//先运行左右小腿
			if(ZYXT_Runed>0)   
			{
				Fun_Hand_DG23(0,ZYXT_Runed);					
			}
			//再运行左右大腿
			if((ZYDT_Runed>0)&&(0==ZYXT_Runed))
			{
				Fun_Hand_DG1234(0,ZYDT_Runed);	
			}
			if((0==ZYDT_Runed)&&(0==ZYXT_Runed))
			{
				ZYDXT_Flag=0;		//设置状态标志位
				delay_ms(200);
				u2_printf("FW");
				delay_ms(200);
				u2_printf("DGZYTFW");
			}			
		}
		DG_Relay=0;	       //继电器
	}
	else
	{
		LedAlm(100,"DGGS");
	}	
}

/***********************************************************************
 函数名      ：Fun_FW_ALL(void)  
 函数功能    ：掉电复位,每个功能函数停止条件靠光电开关
 输入        ：无
 输出        ：无
                           
************************************************************************/
void Fun_FW_ALL(void)
{	
	u2_printf("复位开始");
	if(SD_Flag==1)
	{
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			//清空串口2接收数组
		USART2_RX_LEN=0;				//串口2状态清零
		memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//清空串口4接收数组			
		UART4_RX_LEN=0;					  //串口4状态清零
		
		//读取复位状态标志位
		u8 	ZF_Flag_Buf[1];
		u8 	YF_Flag_Buf[1];
		u8 	ZB_Flag_Buf[1];
		u8 	SQT_Flag_Buf[1];
		u8 	XQT_Flag_Buf[1];
		u8 	ZBQ_Flag_Buf[1];
		u8 	YL_Flag_Buf[1];	
		
	//支背复位		
//		W25QXX_Read((u8*)ZB_Flag_Buf,35,1);       //从第33地址开始，读取1个字节
//		ZB_Flag=ZB_Flag_Buf[0];
//		if(1==ZB_Flag)
//		{
			u2_printf("/r/n支背复位/r/n");
			Fun_FW_ZB(); 						
//		}
		delay_ms(1000);
		
	//左右翻身复位	
		W25QXX_Read((u8*)ZF_Flag_Buf,33,1);       //从第33地址开始，读取1个字节
		W25QXX_Read((u8*)YF_Flag_Buf,34,1);       //从第34地址开始，读取1个字节
		ZF_Flag=ZF_Flag_Buf[0];
		YF_Flag=YF_Flag_Buf[0];		
		if((1==ZF_Flag)&&(0==YF_Flag))     //左翻复位
		{			
			u2_printf("/r/n左翻复位/r/n");
			Fun_FW_ZF();    		
		}		
		if((0==ZF_Flag)&&(1==YF_Flag))      //右翻复位
		{
			u2_printf("/r/n右翻复位/r/n");
			Fun_FW_YF();   			
		} 
		delay_ms(1000);	

	//坐便器模块复位
//		W25QXX_Read((u8*)ZBQ_Flag_Buf,38,1);       //从第33地址开始，读取1个字节
//		ZBQ_Flag=ZBQ_Flag_Buf[0];
		if(1==GD6_CS)
		{
			u2_printf("/r/n冲洗烘干推杆复位/r/n");
			ZBQ_Flag=1;		//设置状态标志位
			RELAY6=1; 
			Fun_ZBCX(0,CXHG_Lim);  //冲洗烘干推杆缩回
			RELAY6=0;	      					
			delay_ms(1000);
			
			u2_printf("/r/n坐便袋推杆复位/r/n");
			ZBQ_Flag=1;		//设置状态标志位
			RELAY6=1;              //继电器得电
			Fun_ZBTG(0,ZBDTG_Lim);      //收线推杆缩回	
			RELAY6=0;           
			delay_ms(1000);
			
			u2_printf("/r/n坐便器复位/r/n");
			SQT_Flag=0;		//设置状态标志位
			ZF_Flag=0;		//设置状态标志位
			YF_Flag=0;		//设置状态标志位
			ZBQ_Pic=24;
			Fun_ZBQ(1);           //坐便器复位  
		}			
		delay_ms(1000);

	//小桌子复位	
		if(1==GD7_CS)
		{
			u2_printf("/r/n小桌子复位/r/n");
			Fun_FW_YL();         //办公娱乐一体桌复位 					
			delay_ms(1000);
		}
		
	//上下曲腿复位		
//		W25QXX_Read((u8*)SQT_Flag_Buf,36,1);      //从第34地址开始，读取1个字节
//		W25QXX_Read((u8*)XQT_Flag_Buf,37,1);      //从第33地址开始，读取1个字节		
//		SQT_Flag=SQT_Flag_Buf[0];
//		XQT_Flag=XQT_Flag_Buf[0];		
//		if((1==SQT_Flag)||(1==XQT_Flag))
//		{
			u2_printf("/r/n曲腿复位/r/n");
			Fun_FW_QT();         //曲腿复位
			u2_printf("复位结束");
//		}
		
		ZF_Flag=0;		//设置状态标志位
		YF_Flag=0;		//设置状态标志位
		ZB_Flag=0;		//设置状态标志位
		SQT_Flag=0;		//设置状态标志位
		XQT_Flag=0;		//设置状态标志位
		ZBQ_Flag=0;		//设置状态标志位
		YL_Flag=0;		//设置状态标志位
		W25QXX_Write((u8*)&ZF_Flag,33,1);		//将状态标志位写入flash
		W25QXX_Write((u8*)&YF_Flag,34,1);		//将状态标志位写入flash
		W25QXX_Write((u8*)&ZB_Flag,35,1);		//将状态标志位写入flash
		W25QXX_Write((u8*)&SQT_Flag,36,1);		//将状态标志位写入flash
		W25QXX_Write((u8*)&XQT_Flag,37,1);		//将状态标志位写入flash
		W25QXX_Write((u8*)&ZBQ_Flag,38,1);		//将状态标志位写入flash
		W25QXX_Write((u8*)&YL_Flag,39,1);		//将状态标志位写入flash
	}
}


/***********************************************************************
 函数名      ：Fun_FW_ALL_GD(void)  
 函数功能    ：掉电复位,每个功能函数停止条件靠光电开关
 输入        ：无
 输出        ：无
                           
************************************************************************/
void Fun_FW_ALL_GD(void)
{	
	u2_printf("复位开始");
	if(SD_Flag==1)
	{
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			//清空串口2接收数组
		USART2_RX_LEN=0;				//串口2状态清零
		memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//清空串口4接收数组			
		UART4_RX_LEN=0;					  //串口4状态清零
		
		u2_printf("/r/n支背复位/r/n");
		Fun_FW_ZB(); 			
		delay_ms(1000);
		
		//读取复位状态标志位
		u8 	ZF_Flag_Buf[1];
		u8 	YF_Flag_Buf[1];
		u8 	ZB_Flag_Buf[1];
		u8 	SQT_Flag_Buf[1];
		u8 	XQT_Flag_Buf[1];
		u8 	ZBQ_Flag_Buf[1];
		u8 	YL_Flag_Buf[1];
				
		W25QXX_Read((u8*)ZF_Flag_Buf,33,1);       //从第33地址开始，读取1个字节
		W25QXX_Read((u8*)YF_Flag_Buf,34,1);       //从第34地址开始，读取1个字节
		W25QXX_Read((u8*)ZB_Flag_Buf,35,1);       //从第33地址开始，读取1个字节
		W25QXX_Read((u8*)SQT_Flag_Buf,36,1);      //从第34地址开始，读取1个字节
		W25QXX_Read((u8*)XQT_Flag_Buf,37,1);      //从第33地址开始，读取1个字节
		W25QXX_Read((u8*)ZBQ_Flag_Buf,38,1);      //从第34地址开始，读取1个字节
		W25QXX_Read((u8*)YL_Flag_Buf,39,1);       //从第34地址开始，读取1个字节
		
		ZF_Flag=ZF_Flag_Buf[0];
		YF_Flag=YF_Flag_Buf[0];
		ZB_Flag=ZB_Flag_Buf[0];
		SQT_Flag=SQT_Flag_Buf[0];
		XQT_Flag=XQT_Flag_Buf[0];
		ZBQ_Flag=ZBQ_Flag_Buf[0];
		YL_Flag=YL_Flag_Buf[0];
		
		u2_printf("%d",ZF_Flag);
		u2_printf("%d",YF_Flag);
		u2_printf("%d",ZB_Flag);
		u2_printf("%d",SQT_Flag);
		u2_printf("%d",XQT_Flag);
		u2_printf("%d",ZBQ_Flag);
		u2_printf("%d",YL_Flag);
						
				
		if((1==ZF_Flag)&&(0==YF_Flag))     //左翻复位
		{			
			u2_printf("/r/n左翻复位/r/n");
			Fun_FW_ZF();    		
		}		
		if((0==ZF_Flag)&&(1==YF_Flag))      //右翻复位
		{
			u2_printf("/r/n右翻复位/r/n");
			Fun_FW_YF();   			
		} 
		delay_ms(1000);				
		
		if(1==ZBQ_Flag)
		{
			u2_printf("/r/n冲洗烘干推杆复位/r/n");
			ZBQ_Flag=1;		//设置状态标志位
			RELAY6=1; 
			Fun_ZBCX(0,CXHG_Lim);  //冲洗烘干推杆缩回
			RELAY6=0;	      					
			delay_ms(1000);
			
			u2_printf("/r/n坐便袋推杆复位/r/n");
			ZBQ_Flag=1;		//设置状态标志位
			RELAY6=1;              //继电器得电
			Fun_ZBTG(0,ZBDTG_Lim);      //收线推杆缩回	
			RELAY6=0;           
			delay_ms(1000);
			
			u2_printf("/r/n坐便器复位/r/n");
			SQT_Flag=0;		//设置状态标志位
			ZF_Flag=0;		//设置状态标志位
			YF_Flag=0;		//设置状态标志位
			ZBQ_Pic=24;
			Fun_ZBQ(1);           //坐便器复位  
		}			
		delay_ms(1000);
			
		u2_printf("/r/n小桌子复位/r/n");
		Fun_FW_YL();         //办公娱乐一体桌复位 					
		delay_ms(1000);
			
		u2_printf("/r/n曲腿复位/r/n");
		Fun_FW_QT();         //曲腿复位
		u2_printf("复位结束");
		
		ZF_Flag=0;		//设置状态标志位
		YF_Flag=0;		//设置状态标志位
		ZB_Flag=0;		//设置状态标志位
		SQT_Flag=0;		//设置状态标志位
		XQT_Flag=0;		//设置状态标志位
		ZBQ_Flag=0;		//设置状态标志位
		YL_Flag=0;		//设置状态标志位
		W25QXX_Write((u8*)&ZF_Flag,33,1);		//将状态标志位写入flash
		W25QXX_Write((u8*)&YF_Flag,34,1);		//将状态标志位写入flash
		W25QXX_Write((u8*)&ZB_Flag,35,1);		//将状态标志位写入flash
		W25QXX_Write((u8*)&SQT_Flag,36,1);		//将状态标志位写入flash
		W25QXX_Write((u8*)&XQT_Flag,37,1);		//将状态标志位写入flash
		W25QXX_Write((u8*)&ZBQ_Flag,38,1);		//将状态标志位写入flash
		W25QXX_Write((u8*)&YL_Flag,39,1);		//将状态标志位写入flash
	}
}


/***********************************************************************
 函数名      ：Fun_FW_ZB(void)  
 函数功能    ：支背复位，用于掉电复位
 输入        ：无
 输出        ：无
                           
************************************************************************/
void Fun_FW_ZB(void)
{
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			//清空串口2接收数组
	USART2_RX_LEN=0;					//串口2状态清零
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//清空串口4接收数组		
	UART4_RX_LEN=0;				  //串口4状态清零
	ZF_Flag=0;		//设置状态标志位
	YF_Flag=0;		//设置状态标志位
	ZB_Runed=Ang_To_Arr_ZB(ZB_Lim);				//设置已运行脉冲值为极限值
	ZB_Pic=19;
	WriteInU2("ZBX");
	Fun_ZB();                //支背复位	
	ZB_Flag=0;		//设置状态标志位
}

/***********************************************************************
 函数名      ：Fun_FW_QT(void)  
 函数功能    ：曲腿复位，用于掉电复位
 输入        ：无
 输出        ：无
                           
************************************************************************/
void Fun_FW_QT(void)
{
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			//清空串口2接收数组
	USART2_RX_LEN=0;					//串口2状态清零
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//清空串口4接收数组		
	UART4_RX_LEN=0;				  //串口4状态清零
	SQT_Flag=0;		//设置状态标志位
	ZF_Flag=0;		//设置状态标志位
	YF_Flag=0;		//设置状态标志位
	XQT_Runed=Ang_To_Arr_SXQT(XQT_Lim);  				//设置已运行脉冲值为极限值
	XQT_Pic=19;
	WriteInU2("XQTS");
	Fun_XQT();           
	delay_ms(1000);
	
	XQT_Flag=0;			//设置状态标志位
	WriteInU2("SQTS");
	Fun_SQT();              //上曲腿
	delay_ms(1000);
	WriteInU2("SQTX");
	Fun_SQT();              //上曲腿复位
	SQT_Flag=0;		//设置状态标志位
}

/***********************************************************************
 函数名      ：Fun_FW_YL(void)  
 函数功能    ：就餐娱乐一体桌复位，用于掉电复位
 输入        ：无
 输出        ：无
                           
************************************************************************/
void Fun_FW_YL(void)
{
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			//清空串口2接收数组
	USART2_RX_LEN=0;					//串口2状态清零
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//清空串口4接收数组		
	UART4_RX_LEN=0;				  //串口4状态清零
	ZF_Flag=0;		//设置状态标志位
	YF_Flag=0;		//设置状态标志位
	YL_Runed=Ang_To_Arr_YL(YL_Lim);				//设置已运行脉冲值为极限值
	YL_Pic=19;
	WriteInU2("YLX");
	Fun_YL1();             //小桌子复位
	YL_Flag=0;		//设置状态标志位
}

	
/***********************************************************************
 函数名      ：Uart_Reset_Motor5_0(void)  
 函数功能    ：5号电机复位:
 输入        ：反向复位0;正向复位1
 输出        ：无
                           
************************************************************************/
void Fun_FW_CF(u8 dir) 
{
	u8 key;
	u16 arr_feed;      //计算程序中当前一次运行脉冲数,用于判断电机失步故障
	u16 pulse_num=0;   //将程序中当前一次运行脉冲数进行转化，与电机反馈的当前运行脉冲数相比较
	u16 num=0;
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);		//清空串口2接收数组	
	USART2_RX_LEN=0;	  //串口2状态清零
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);				//清空串口4接收数组	
	UART4_RX_LEN=0;				  //串口4状态清零
	MotorStart(5,dir,1400-1,25-1);				 //5号电机启动
	u2_printf("*%s*M5*F*0*/**",RX_BUF);		//串口2反馈
	if(1==ZF_Flag)
	{
		TIM10_Init(Ang_To_Arr_ZYFS(ZF_Lim),65000);          //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
	}
	if(1==YF_Flag)
	{
		TIM10_Init(Ang_To_Arr_ZYFS(YF_Lim),65000);           //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
	}
	__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //清除中断标志位
	while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) )
	{				
		//光电限位
		if(0==GD5_CS)   //碰到光电开关跳出循环，电机停转 
		{
			delay_us(100);
			if(0==GD5_CS)
			{
				u2_printf("GD5CS");
				break;	
			}				
		}
		//电机过载
//		if(1==Motor5_Alm)      
//		{						
//			delay_us(100);
//			if(1==Motor5_Alm)
//			{
//				if(ZF_Flag==1)
//				{
//					ZF5_GZ=1;
//					u2_printf("*%s*M5*F*1*/**",RX_BUF);
//					delay_ms(200);
//					u2_printf("ZFGZ5");
//				}
//				if(YF_Flag==1)
//				{
//					YF5_GZ=1;
//					u2_printf("*%s*M5*F*1/*",RX_BUF);
//					delay_ms(200);
//					u2_printf("YFGZ5");
//				}
//				Fun_GZCL();
//				break;
//			}			
//		}
		  //判断有没有收到上位机指令		
		if(USART2_RX_LEN&0x8000)
		{
			u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数	
			memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			//清空串口2接收数组
			USART2_RX_LEN=0;						//串口2状态清零										
		}
		if(UART4_RX_LEN&0x8000)
		{
			u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数	
			memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//清空串口4接收数组		
			UART4_RX_LEN=0;				//串口4状态清零								
		}		
	}		      
	MotorStop(5);   u2_printf("*%s*M5*T*0*/**",RX_BUF);    //电机停止
	TIM10_Stop();       //关闭定时器
	__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //清除中断标志位	
	//若定时时间到但是光电没到，则电机再运行一段距离，到达光电开关位置（光电开关安装后打开此段）
//	if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))&&(GD5_CS==1)&&(direct==0))
//	{  
//		MotorStart(5,dir,1400-1,25-1);   			 //5号电机启动
//		u2_printf("*%s*M5*F*0*/**",RX_BUF);
//		TIM10_Init(add_arr,65000);                     //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
//		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //清除中断标志位	 	
//		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))
//		{			
//			if(0==GD5_CS)  //运行时碰到光电开关，跳出循环 
//			{
//				delay_us(100);
//				if(0==GD5_CS) 
//				{
//					u2_printf("GD5CS");
//					break;	
//				}					
//			}
//		}			
//		MotorStop(5);       //电机停止
//	    TIM10_Stop();       //关闭定时器
//		if(0==GD5_CS)
//		{
//			u2_printf("*%s*M5*T*0*/**",RX_BUF);
//		}
//		else
//		{
//			u2_printf("*%s*M5*T*0*/**",RX_BUF);
//		}
//		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位	
//	}	
}


/***********************************************************************
 函数名      ：Fun_FW_ZF(void)  
 函数功能    ：左翻身复位，用于掉电复位
 输入        ：无
 输出        ：无
                           
************************************************************************/
void Fun_FW_ZF(void)
{		
	//4号电机复位
	if(1==GD4_CS)
	{
		SD_Flag=1;		//设置状态标志位
		ZF_Flag=1;		//设置状态标志位
		ZBH_Flag=0;		//设置状态标志位
		ZYH_Dir_flag=0;		//设置方向状态标志位
		ZYH_Pic=0;			//图片标志设为0
		ZYH_Runed=Ang_To_Arr_ZYFS(ZF_Lim);	//设置已运行脉冲值为极限值
		Fun_ZYH();    //左腰部护理复位
		ZYH_Flag=0;		//设置状态标志位
	}
	//3号电机复位
	if(1==GD3_CS)
	{
		SD_Flag=1;		//设置状态标志位
		ZF_Flag=1;		//设置状态标志位
		ZYH_Flag=0;		//设置状态标志位
		ZBH_Dir_flag=0;	//设置方向状态标志位
		ZBH_Pic=0;	//图片标志设为0
		ZBH_Runed=Ang_To_Arr_ZYFS(ZF_Lim);	//设置已运行脉冲值为极限值
		Fun_ZBH();     //左背部护理复位
		ZBH_Flag=0;	//设置方向状态标志位
	}
	
	//5号电机复位
	if(1==GD5_CS)
	{
		Fun_FW_CF(0); 
	}
	ZF_Runed=0;				//已运行脉冲值设为0
	ZF_Flag=0;		//设置状态标志位
	ZBH_Flag=0;		//设置状态标志位
	ZYH_Flag=0;		//设置状态标志位
	ZBH_Dir_flag=0;		//设置方向状态标志位
	ZYH_Dir_flag=0;		//设置方向状态标志位
	ZYH_Pic=0;			//图片标志设为0
	ZBH_Pic=0;			//图片标志设为0
}

/***********************************************************************
 函数名      ：Fun_FW_YF(void)  
 函数功能    ：右翻身复位，用于掉电复位
 输入        ：无
 输出        ：无
                           
************************************************************************/
void Fun_FW_YF(void)
{
	//4号电机复位
	if(1==GD4_CS)
	{
		SD_Flag=1;		//设置状态标志位
		YF_Flag=1;		//设置状态标志位
		YBH_Flag=0;		//设置状态标志位
		YYH_Dir_flag=0;		//设置方向状态标志位
		YYH_Pic=0;			//图片标志设为0
		YYH_Runed=Ang_To_Arr_ZYFS(YF_Lim);	//设置已运行脉冲值为极限值
		Fun_YYH();   //右腰部护理复位
		YYH_Flag=0;		//设置状态标志位
	}
	
	//3号电机复位
	if(1==GD3_CS)
	{
		SD_Flag=1;		//设置状态标志位
		YF_Flag=1;		//设置状态标志位
		YYH_Flag=0;		//设置状态标志位
		YBH_Dir_flag=0;		//设置方向状态标志位
		YBH_Pic=0;			//图片标志设为0
		YBH_Runed=Ang_To_Arr_ZYFS(YF_Lim);	//设置已运行脉冲值为极限值
		Fun_YBH();    //右背部护理复位
		YBH_Flag=0;		//设置状态标志位
	}
	
	//5号电机复位
	if(1==GD5_CS)
	{	
		Fun_FW_CF(1);
	}	
	YF_Runed=0;			//已运行脉冲值设为0
	YF_Flag=0;		//设置状态标志位
	YBH_Flag=0;		//设置状态标志位
	YYH_Flag=0;		//设置状态标志位
	YBH_Dir_flag=0;		//设置方向状态标志位
	YYH_Dir_flag=0;		//设置方向状态标志位
	YYH_Pic=0;			//图片标志设为0
	YBH_Pic=0;			//图片标志设为0	
}


/***********************************************************************
 函数名      ： 
 函数功能    ：吊挂测试函数
 输入        ：无
 输出        ：无
***********************************************************************/                           
void  TestAll(u8 dir)
{
	Hang_Init();         //电机方向口初始化函数
	int i,flag=1;        //flag为脉冲高低标志位
	int j=0,k=0;
	DG_DIR1=dir;       //3号吊挂电机转动方向控制，高电平正转，低电平反转 
	DG_DIR2=!dir;
	DG_DIR3=dir;
	DG_DIR4=!dir;
	
 	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//清空串口2接收数组		
	USART2_RX_LEN=0; 				//串口2状态清零
	u2_printf("Hang_TestAll");
	TIM10_Init(DG_Freq,25-1);               //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
    for(i=0;i<1500000;i++)
    { 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) );   //等待定时时间到，时间到跳出循环
		flag = !flag ;
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);             //清除中断标志位
		DG_PWM1=flag;        //吊挂电机脉冲输出口高/低电平				 
		DG_PWM2=flag;
		DG_PWM3=flag;
		DG_PWM4=flag;
	}
	DG_PWM1=0;              //3号吊挂电机对应脉冲输出口拉低 
	DG_PWM2=0;
	DG_PWM3=0;
	DG_PWM4=0;
	TIM10_Stop();             //关闭定时器
	u2_printf("Hang_TestAll_Stop");
}	


/***********************************************************************
 函数名      ：Hang1(u8 dir)
 函数功能    ：吊挂测试函数
 输入        ：dir，代表方向
 输出        ：无
***********************************************************************/   
void Hang1(u8 dir)
{
	Hang_Init();         //电机方向口初始化函数
	int i,flag=1;        //flag为脉冲高低标志位
	int j=0,k=0;
	DG_DIR1=dir;       //3号吊挂电机转动方向控制，高电平正转，低电平反转 
	u2_printf("Hang1");
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			//清空串口2接收数组
	USART2_RX_LEN=0; 				//串口2状态清零
	TIM10_Init(DG_Freq,25-1);    //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
	
    for(i=0;i<1500000;i++)   //最终确定为3000000
    { 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) );   //等待定时时间到，时间到跳出循环
		flag = !flag ;
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);             //清除中断标志位
		DG_PWM1=flag;               //3号吊挂电机脉冲输出口高电平				 
	}
	DG_PWM1=0;              //3号吊挂电机对应脉冲输出口拉低 
	TIM10_Stop();             //关闭定时器
	u2_printf("Hang1_Stop");
}
/***********************************************************************
 函数名      ：Hang2(u8 dir)
 函数功能    ：吊挂测试函数
 输入        ：dir，代表方向
 输出        ：无
***********************************************************************/ 
void Hang2(u8 dir)
{
	Hang_Init();         //电机方向口初始化函数
	int i,flag=1;        //flag为脉冲高低标志位
	int j=0,k=0;
	DG_DIR2=dir;         //3号吊挂电机转动方向控制，高电平正转，低电平反转 
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			//清空串口2接收数组
	USART2_RX_LEN=0; 				//串口2状态清零
	TIM10_Init(DG_Freq,25-1);          //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
	u2_printf("Hang2");
    for(i=0;i<1500000;i++)  //最终确定为3000000
    { 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) );   //等待定时时间到，时间到跳出循环
		flag = !flag ;
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);             //清除中断标志位
		DG_PWM2=flag;               //3号吊挂电机脉冲输出口高电平				 
	}
	DG_PWM2=0;               //3号吊挂电机对应脉冲输出口拉低 
	TIM10_Stop();             //关闭定时器
	u2_printf("Hang2_Stop");
}
/***********************************************************************
 函数名      ：Hang3(u8 dir)
 函数功能    ：吊挂测试函数
 输入        ：dir，代表方向
 输出        ：无
***********************************************************************/ 
void Hang3(u8 dir)
{
	Hang_Init();         //电机方向口初始化函数
	int i,flag=1;        //flag为脉冲高低标志位
	int j=0,k=0;
	DG_DIR3=dir;       //3号吊挂电机转动方向控制，高电平正转，低电平反转 
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//清空串口2接收数组		
	USART2_RX_LEN=0; 				//串口2状态清零
	TIM10_Init(DG_Freq,25-1);        //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
	u2_printf("Hang3");
    for(i=0;i<1500000;i++)   //最终确定为3000000
    { 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) );   //等待定时时间到，时间到跳出循环
		flag = !flag ;
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);             //清除中断标志位
		DG_PWM3=flag;               //3号吊挂电机脉冲输出口高电平				 
	}
	DG_PWM3=0;              //3号吊挂电机对应脉冲输出口拉低 
	TIM10_Stop();             //关闭定时器
	u2_printf("Hang3_Stop");
}
/***********************************************************************
 函数名      ：Hang4(u8 dir)
 函数功能    ：吊挂测试函数
 输入        ：dir，代表方向
 输出        ：无
***********************************************************************/ 
void Hang4(u8 dir)
{
	Hang_Init();         //电机方向口初始化函数
	int i,flag=1;        //flag为脉冲高低标志位
	int j=0,k=0;
	DG_DIR4=dir;         //3号吊挂电机转动方向控制，高电平正转，低电平反转 
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);		//清空串口2接收数组	
	USART2_RX_LEN=0; 						//串口2状态清零
	TIM10_Init(DG_Freq,25-1);     //打开定时器，定时器周期=(freq1*freq_time1_1)/90mhz	
	u2_printf("Hang4");
    for(i=0;i<1500000;i++)    //最终确定为3000000
    { 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) );   //等待定时时间到，时间到跳出循环
		flag = !flag ;
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);             //清除中断标志位
		DG_PWM4=flag;         //4号吊挂电机脉冲输出口高电平		
	}
	DG_PWM4=0;                //4号吊挂电机对应脉冲输出口拉低 
	TIM10_Stop();             //关闭定时器
	u2_printf("Hang4_Stop");
}
/***********************************************************************
 函数名      ：DeskRunNew()
 函数功能    ：小桌子运行
 输入        ：
 输出        ：
***********************************************************************/ 
void DeskRunNew(void)
{
	u8 direct;    //表示电机运行方向，1：小桌子前进；0：小桌子后退
	u16 arr_now;      //本次运行脉冲值
	u8 len;           //表示接收的字符串的长度
	u8 err=0;
//实现上位机实时显示护理床当前运动状态 
	static u8 k=0;            //发送第k张图片
	static u8 kj=0;
	u8 j=0;	
	u16 arr_send;                 //当前一次运行脉冲数
	static u8 yljx_flag;    //判断小桌子是否运行到极限位置，若是发送极限位置图片	
	//联锁功能，只有在左右翻身功能复位后，才能进行小桌子移动
	if((ZF_Flag==0)&&(YF_Flag==0))
	{		
		if(((strstr((const char *)USART2_RX_BUF,(const char *)"YLS"))||(strstr((const char *)UART4_RX_BUF,(const char *)"YLS"))))
		{
			direct=1;			//设置运行方向标志
			if(yljx_flag==1)
			{err=1;u2_printf("err\r\n");}
			if((YL_Flag==0)&&(err==0))
			{
				YL_Flag=1;		//设置状态标志位
			//	W25QXX_Write((u8*)&YL_Flag,39,1);		//将状态标志位写入flash
				delay_ms(200);
				u2_printf("YL_flag==1");
				delay_ms(200);
				u2_printf("YLKS");
				delay_ms(200);
				u2_printf("CT_YL1");
			}
			
			if((20*(YL_Lim)>YL_Runed)&&(err==0))  //上行时，比较值为上行极限装载值与校准后的当量装载值的差值，两个差值不能为0
			{
				u2_printf("*%s*M7*Z*0*/**",RX_BUF);		//串口2反馈
				MotorStart(7,0,700-1,25-1);
				TIM2_Init(2000,900);
				//TIM2_Init(Ang_To_Arr_YL2(YL_Lim)-YL_Runed,65000);  //定时器周期=(freq1*freq_time1_1)/90mhz			
			}	
		}
		if(((strstr((const char *)USART2_RX_BUF,(const char *)"YLX"))||(strstr((const char *)UART4_RX_BUF,(const char *)"YLX"))))
		{
			direct=0;			//设置运行方向标志
			if(YL_Runed==0)
			{err=1;u2_printf("err\r\n");}
			if((1==yljx_flag)&&(err==0))
			{
				yljx_flag=0;	//设置极限状态标志位
				delay_ms(200);
				u2_printf("CT_YL20");
			}
			if((YL_Runed>0)&&(err==0))    //下行时，比较值为校准后的当量装载值与0,且不能为0
			{
				u2_printf("*%s*M7*F*0*/**",RX_BUF);		//串口2反馈
				MotorStart(7,1,700-1,25-1);
				TIM2_Init(2000,900);	//定时器定时20ms
			//	TIM2_Init(YL_Runed,65000);  //定时器周期=(freq1*freq_time1_1)/90mhz			
			}
		}
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//清空串口2接收数组		
		USART2_RX_LEN=0;				//串口2状态清零
		memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//清空串口4接收数组			
		UART4_RX_LEN=0;				  //串口4状态清零
		 if((((YL_Runed!=20*(YL_Lim))&&(1==direct))||((0!=YL_Runed)&&(0==direct)))&&(err==0))
		 {	 	
			while((YL_Runed+(-1)*(1-direct*2)*T2RunTimes)<20*(YL_Lim))  //等待定时时间到，时间到跳出循环  
			{						
				//光电限位											   						
//				if((0==GD7_ZZ)&&(1==direct))
//				{
//					delay_us(100);
//					if(0==GD7_ZZ)
//					{
//						u2_printf("GD7ZZ");					
//						break;					
//					}								
//				}
//				if((0==GD7_CS)&&(0==direct))
//				{
//					delay_us(100);
//					if(0==GD7_CS)
//					{
//						u2_printf("GD7CS");					
//						break;						
//					}					
//				}
				//停止指令
				if(USART2_RX_LEN&0x8000)
				{
					len=USART2_RX_LEN&0x3fff;	//获取串口2接收数组字符长度				
					USART2_RX_BUF[len]=0;			//串口2数组末尾添"0"
					if((strstr((const char *)USART2_RX_BUF,(const char *)"STOP"))||(strstr((const char *)USART2_RX_BUF,(const char *)"YLS"))||(strstr((const char *)USART2_RX_BUF,(const char *)"YLX")))    //若接收到Stop,则跳出循环	
					{
//						memcpy(RX_BUF,USART2_RX_BUF,15);
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//清空串口2接收数组		
						USART2_RX_LEN=0;			//串口2状态清零
						break;
					}
					else
					{
						u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数							
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);		//清空串口2接收数组	
						USART2_RX_LEN=0;			//串口2状态清零
					}						
				}	
				if(UART4_RX_LEN&0x8000)
				{
					len=UART4_RX_LEN&0x3fff;		//获取串口4接收数组字符长度			
					UART4_RX_BUF[len]=0;				//串口4数组末尾添"0"
					if((strstr((const char *)UART4_RX_BUF,(const char *)"STOP"))||(strstr((const char *)UART4_RX_BUF,(const char *)"YLS"))||(strstr((const char *)UART4_RX_BUF,(const char *)"YLX")))    //若接收到Stop,则跳出循环	
					{
//						memcpy(RX_BUF,UART4_RX_BUF,15);
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//清空串口4接收数组		
						UART4_RX_LEN=0;				  //串口4状态清零
						break;
					}
					if(strstr((const char *)UART4_RX_BUF,(const char *)"SEND OK"))
					{	}
					else
					{
						u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数							
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//清空串口4接收数组			
						UART4_RX_LEN=0;				  //串口4状态清零
					}						
				}
				//电机故障、故障诊断
//				if(PCF8574_ReadBit(1)==1)        
//				{	
//					delay_us(100);
//					if(1==PCF8574_ReadBit(1))
//					{
//						YL_GZ=1;
//						u2_printf("*%s*M7*/*1*/**",RX_BUF);
//						delay_ms(200);
//						u2_printf("YLGZ");
//						Fun_GZCL();
//						break;						
//					}								             
//				}								
				
				//发送动画指令
				// arr_send=__HAL_TIM_GET_COUNTER(&TIM2_Handler);		//获取当前寄存器运行装载值
				
				if(direct==1)
				{
					j=(YL_Runed+T2RunTimes)/(20*(YL_Lim)/19);		//图片序号计算
				}
				else
				{
					j=abs(YL_Runed,T2RunTimes)/(20*(YL_Lim)/19);		//图片序号计算
				}
				k=YL_Pic;
				if(	k!=j)
				{				
					kj=abs(k,j);				
					if(kj<2)
					{
						k=j;  YL_Pic=k;
						if((1<YL_Pic)&&(YL_Pic<20))
						{
							u2_printf("CT_YL%d",YL_Pic);		//串口2发送动画图片指令
						}
					}					
				}
			}
			arr_now=T2RunTimes;
			MotorStop(7);       //电机停止			
			TIM2_Close();        //定时器关闭
			T2RunTimes=0;
			u2_printf("*%s*M7*T*0*/**",RX_BUF);		//串口2反馈
			//判断复位

			if(direct==1)
			{
				YL_Runed+=arr_now;		//首先计算当前所有运行的20ms次数
				if(YL_Runed<20*(YL_Lim))
				{
					YL_Flag=1;		//标志位置1
				}
				else
				{
					YL_Runed=20*(YL_Lim);				//设置已运行脉冲值为极限值
					yljx_flag=1;		//设置极限状态标志位
					delay_ms(200);
					u2_printf("CT_YL20");
					delay_ms(200);
					u2_printf("YLJX");
				}	
			}
			else
			{				
				if(YL_Runed<arr_now)		//判断是否发生计算错误
				{err=1;}			
				YL_Runed-=arr_now;	//首先计算当前所有运行的20ms次数				
				if((YL_Runed>0)&&(err==0))
				{
					YL_Flag=1;		//标志位置1
				}
				else
				{
					YL_Runed=0;
					arr_now=0;         //此时处于复位状态，将状态值都设为0；
					YL_Flag=0;		//设置状态标志位
				//	W25QXX_Write((u8*)&YL_Flag,39,1);		//将状态标志位写入flash
					u2_printf("CT_YL%d",1);
					delay_ms(200);
					u2_printf("YL_flag==0");
				}					
			}
  		T2RunTimes=0;				
		}
	}
	else
	{
		LedAlm(100,"YLGS");//若不满足条件，LED0/LED1闪一下
	}	
}


