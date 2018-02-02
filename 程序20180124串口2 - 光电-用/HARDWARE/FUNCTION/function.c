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
*������       ��All_Init()
*��������     ��ϵͳ���в�����ʼ��
*����         ����
*���         ����
***********************************************************************/
void All_Init(void)
{ 
	HAL_Init();                            //��ʼ��HAL��   
	Stm32_Clock_Init(360,25,2,8);          //����ʱ��,180Mhz
	delay_init(180);                       //��ʼ����ʱ����
	uart_init(115200);                     //��ʼ��USART
	usart2_init(115200);                   //��ʼ������2
	usart3_init(115200);                   //��ʼ������3
	uart4_init(115200);	                   //��ʼ������4
	LED_Init();                            //��ʼ��LED 	
	SPI5_Init();					       //��ʼ��SPI��
	Motor_Init();                          //��ʼ����������
	Hang_Init();                           //��ʼ�����ҵ������������
	CXHG_Init();                           //��ϴ��ɵ綯��
	Sensor_Init();                         //��ʼ����翪��
	KEY_Init();                            //��ʼ������
	Pump_Init();                           //��ʼ��ˮ��   
	PCF8574_Init();                        //��ʼ��PCF8574/������չоƬ
	NAND_Init();                           //��ʼ��NAND FLASH			
	W25QXX_Init();					       //��ʼ��w25q256/SPI FLASH
//	ESP8266_AP_Init(4);	
}


/*********************************************************************
*������       ��WIFI_JCGN()
*��������     ����������ģ��
*����         ����
*���         ����
***********************************************************************/
void WIFI_JCGN(void)
{
//	if(ESP8266_Get_ID())	//���յ���ǰ�豸���͵�ָ���������䷵��һ��Receivedָ��	
	//�������ܺ���
	if(strstr((const char *)UART4_RX_BUF,(const char *)"ZBS"))             
	{		Fun_ZB();		}	 //֧����	
	   		
	if(strstr((const char *)UART4_RX_BUF,(const char *)"ZBX"))           
	{		Fun_ZB();		}			//֧����		
		
	if(strstr((const char *)UART4_RX_BUF,(const char *)"SQTS"))            
	{
		Fun_SQT();			//��������		
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"SQTX"))          
	{
		Fun_SQT();			//��������		
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"XQTX"))        
	{
		Fun_XQT();			//��������		
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"XQTS"))          
	{
		Fun_XQT();			//��������		
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"ZFS"))         
	{
		Fun_ZF();			//������			
	}			
	if(strstr((const char *)UART4_RX_BUF,(const char *)"ZFX"))       
	{
		Fun_ZF();			//������		
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"YFS"))        
	{
		Fun_YF();			//�ҷ�����			
	}		
	if(strstr((const char *)UART4_RX_BUF,(const char *)"YFX"))      
	{
		Fun_YF();			//�ҷ�����			
	}							
	if(strstr((const char *)UART4_RX_BUF,(const char *)"YLS"))             
	{
		Fun_YL1();          //��������һ������ǰ
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"YLX"))           
	{
		Fun_YL1();          //��������һ��������
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"ZBH"))    
	{
		Fun_ZBH();			//�󱳲�����		
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"YBH"))   
	{
		Fun_YBH();			//�ұ�������		
	}					
	if(strstr((const char *)UART4_RX_BUF,(const char *)"ZYH"))   
	{
		Fun_ZYH();			//����������			
	}				
	if(strstr((const char *)UART4_RX_BUF,(const char *)"YYH"))  
	{
		Fun_YYH();         //����������
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"ZDZBQ"))        
	{
		Fun_ZDZBQ();		//�Զ�����				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"SDCX"))        
	{
		Fun_SDCX();		   //�ֶ���ϴ				
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"SDHG"))        
	{
		Fun_SDHG();		   //�ֶ����				
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"LD"))        
	{
		Fun_LD();		   //����				
	}	
	
	//�������ܸú���
	if(strstr((const char *)UART4_RX_BUF,(const char *)"HLZB"))           
	{
		Fun_HL_ZB();		//֧��			
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"HLZF"))      
	{
		Fun_HL_ZF();		//����				
	}					
	if(strstr((const char *)UART4_RX_BUF,(const char *)"HLYF"))     
	{
		Fun_HL_YF();		//�ҷ���			
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"HLBH"))   
	{
		Fun_HL_BH();		//��������			
	}							
	if(strstr((const char *)UART4_RX_BUF,(const char *)"HLYH"))  
	{
		Fun_HL_YH();		//��������				
	}					
	if(strstr((const char *)UART4_RX_BUF,(const char *)"HLZDZB"))   
	{
		Fun_ZDZBQ();		//�Զ�����			
	}							
	if(strstr((const char *)UART4_RX_BUF,(const char *)"HLSD"))           
	{
		Fun_HL_SD();       //����
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"HLFW"))          
	{
		Fun_FW_ALL();	    //���縴λ			
	}

//************************���Ժ���*********************************
		
	if(strstr((const char *)UART4_RX_BUF,(const char *)"Y2L2_1"))   
	{
		WriteInU2("YLS");		//����2��������д��"YLS"
		Fun_YL2();					//С������ǰ	
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"Y2L2_0"))   
	{
		WriteInU2("YLX");		//����2��������д��"YLX"
		Fun_YL2();		   		//С�������
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"U2_Z1D1C1X1"))   
	{
		ZBQ_Flag=1;					//��������־λ��1
		Fun_ZDCX();		      //�Զ���ϴ				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"U2_Z1D1H1G1"))   
	{
		ZBQ_Flag=1;					//��������־λ��1
		Fun_ZDHG();	        //�Զ����					
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"U2_ZBC1X1H1G1"))        
	{
		ZBQ_Flag=1;					//��������־λ��1
		RELAY6=1; 					//�Ƹ˼̵����õ�
		Fun_ZBCXHG(1,CXHG_Lim);   //��ϴ����Ƹ����
		RELAY6=0; 					//�Ƹ˼̵���ʧ��
	}		
	if(strstr((const char *)UART4_RX_BUF,(const char *)"U2_ZBC1X1H1G0"))                
	{
		ZBQ_Flag=1;					//��������־λ��1
		RELAY6=1; 					//�̵����õ�
		Fun_ZBCXHG(0,CXHG_Lim);  //��ϴ����Ƹ�����
		RELAY6=0;	      		//�̵���ʧ��			
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"U2_Z1B1D0"))              
	{
		ZBQ_Flag=1;					//��������־λ��1
		Fun_ZBD(0);	  	    //������ս� 		
	}			
	if(strstr((const char *)UART4_RX_BUF,(const char *)"U2_Z1B1D1"))            
	{
		ZBQ_Flag=1;					//��������־λ��1
		Fun_ZBD(1);	  		  //��������ߵ�������������		
	}
	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"U2_Z1B1T1G1"))          
	{
		ZBQ_Flag=1;					//��������־λ��1
		RELAY6=1;           //�̵����õ�
		Fun_ZBTG(1,ZBDTG_Lim); //�����Ƹ����	
		RELAY6=0;           //�̵���ʧ��  
	}		
	if(strstr((const char *)UART4_RX_BUF,(const char *)"U2_Z1B1T1G0"))               
	{
		ZBQ_Flag=1;					//��������־λ��1
		RELAY6=1;           //�̵����õ�
		Fun_ZBTG(0,ZBDTG_Lim); //�����Ƹ�����	
		RELAY6=0;           //�̵���ʧ��           
	}				
	if(strstr((const char *)UART4_RX_BUF,(const char *)"U2_Z1B1Q1"))           
	{
		u2_printf("��������");
		Fun_ZBQ(0);	  			//��������
	}		
	if(strstr((const char *)UART4_RX_BUF,(const char *)"U2_Z1B1Q0"))              
	{
		u2_printf("�������ر�");			
		Fun_ZBQ(1);	  	  	//�������ر�			
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"C2Z2"))              
	{
		u2_printf("����");			
		Fun_CZ1();	  			//���غ�������	
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"DIR_SB1")) 
	{
		RELAY6=1; 		 //�̵����õ�
		DIR_SB=1;      //ˮ�ô�		
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"DIR_SB0"))  
	{
		RELAY6=0;			 //�̵����õ�
		DIR_SB=0;      //ˮ�ùر�		
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"DIR_HG1"))       
	{
		RELAY6=1;     //�̵����õ�
		DIR_QB=1;     //���ô�	
		DIR_HG=1;     //��ɷ���	
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"DIR_HG0"))        
	{
		RELAY6=0;	 //�̵����õ�
		DIR_QB=0;	 //���ùر�	
		DIR_HG=0;  //��ɷ��ر�	
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"testhang1"))             
	{
		DG_Relay=1;	//���Ҽ̵����õ�
		TestAll(1);	//���Ҳ��Ժ�����
		DG_Relay=0;	//���Ҽ̵���ʧ��
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"testhang0"))             
	{
		DG_Relay=1;	//���Ҽ̵����õ�
		TestAll(0);	//���Ҳ��Ժ�����
		DG_Relay=0;	//���Ҽ̵���ʧ��
	}							
	if(strstr((const char *)UART4_RX_BUF,(const char *)"Hang1_1"))              
	{
		DG_Relay=1;	      //���Ҽ̵����õ�	       
		delay_ms(300);		//��ʱ300ms
		u2_printf("XINHAO");
		Hang1(0);	  			//1�ŵ��ҵ����
		DG_Relay=0;	      //���Ҽ̵���ʧ��
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"Hang1_0"))              
	{
		DG_Relay=1;	      //���Ҽ̵����õ�	
		Hang1(1);	        //����1
		DG_Relay=0;	     	//���Ҽ̵���ʧ��
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"Hang2_1"))           
	{
		DG_Relay=1;	      //���Ҽ̵����õ�
		Hang2(1);	        //����2
		DG_Relay=0;	      //���Ҽ̵���ʧ��
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"Hang2_0"))             
	{
		DG_Relay=1;	      //���Ҽ̵����õ�
		Hang2(0);	        //����2
		DG_Relay=0;	    	//���Ҽ̵���ʧ��
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"Hang3_1"))            
	{
		DG_Relay=1;	      //���Ҽ̵����õ�
		Hang3(0);	        //����3
		DG_Relay=0;	      //���Ҽ̵���ʧ��
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"Hang3_0"))             
	{
		DG_Relay=1;	      //���Ҽ̵����õ�
		Hang3(1);	        //����3
		DG_Relay=0;	      //���Ҽ̵���ʧ��
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"Hang4_1"))             
	{
		DG_Relay=1;	     //���Ҽ̵����õ�
		Hang4(1);	       //����4
		DG_Relay=0;	     //���Ҽ̵���ʧ��
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"Hang4_0"))             
	{
		DG_Relay=1;	      //���Ҽ̵����õ� 
		Hang4(0);         //����4
		DG_Relay=0;	    	//���Ҽ̵���ʧ��
	}	
	//���1  
	if(strstr((const char *)UART4_RX_BUF,(const char *)"MOTOR1111"))              
	{
		Motor1(1);	  		//1�ŵ��(�綯�Ƹ�)����		
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"MOTOR1110"))              
	{
		Motor1(0);	  		//1�ŵ��(�綯�Ƹ�)����		
	} 
	//���2  
	if(strstr((const char *)UART4_RX_BUF,(const char *)"MOTOR2221"))              
	{
		Motor2(1);	  		//2�ŵ��(�綯�Ƹ�)����		
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"MOTOR2220"))             
	{
		Motor2(0);	  		//2�ŵ��(�綯�Ƹ�)����		
	} 
	//���3  
	if(strstr((const char *)UART4_RX_BUF,(const char *)"MOTOR3331"))              
	{
		Motor3(1);	  		//3�ŵ������		
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"MOTOR3330"))              
	{
		Motor3(0);	  		//3�ŵ������		
	}
	//���4 
	if(strstr((const char *)UART4_RX_BUF,(const char *)"MOTOR4441"))            
	{
		Motor4(1);	  		//4�ŵ������		
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"MOTOR4440"))             
	{
		Motor4(0);	  		//4�ŵ������	
	}
	//���5 		
	if(strstr((const char *)UART4_RX_BUF,(const char *)"MOTOR5551"))             
	{
		Motor5(1);	  		//5�ŵ������		
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"MOTOR5550"))             
	{
		Motor5(0);	  		//5�ŵ������		
	}
	//���6 		
	if(strstr((const char *)UART4_RX_BUF,(const char *)"MOTOR6661"))              
	{
		Motor6(1);	  		//6�ŵ������		
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"MOTOR6660"))            
	{
		Motor6(0);	  		//6�ŵ������		
	}
	//���7		
	if(strstr((const char *)UART4_RX_BUF,(const char *)"MOTOR7771"))             
	{
		Motor7(1);	  		//7�ŵ������		
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"MOTOR7770"))              
	{
		Motor7(0);	  		//7�ŵ������		
	}	
}

/*********************************************************************
*������       ��WIFI_GJGN()
*��������     ���߼�����ģ��
*����         ����
*���         ����
***********************************************************************/
void WIFI_GJGN(void)
{
//	if(ESP8266_Get_ID())	//���յ���ǰ�豸���͵�ָ���������䷵��һ��Receivedָ��	
	//WiFi����ר��ϵͳ����ָ��					
	if(strstr((const char *)UART4_RX_BUF,(const char *)"ZJZB"))               
	{
		Fun_ZJ_ZB();		  //ר��ϵͳ֧�� 				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"ZJZYF"))                
	{
		Fun_ZJ_ZYF();		//ר��ϵͳ����				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"ZJSXQT"))                   
	{
		Fun_ZJ_SXQT();	    //ר��ϵͳ����					
	}	 
	if(strstr((const char *)UART4_RX_BUF,(const char *)"ZJZDZB"))         
	{
		Fun_ZJ_ZDZB();	    //ר��ϵͳ�Զ����� 					
	}	
			
	if(strstr((const char *)UART4_RX_BUF,(const char *)"JRAM"))   
	{
		Fun_JRAM();		    //���ⰴĦ				
	}			
	if(strstr((const char *)UART4_RX_BUF,(const char *)"JR"))                    
	{
		Fun_JR();			//����		
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"LD"))                         
	{
		Fun_LD();	  		//���ܺ������� 		
	}
	//WiFi���յ��ҿ���ѵ��ָ��
	if(strstr((const char *)UART4_RX_BUF,(const char *)"BZZ"))                 
	{
		Fun_ZD_ZZ(1); 	//��첲 				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"BYZ"))                
	{
		Fun_ZD_YZ(1);	//�Ҹ첲 				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"BLZ"))            
	{
		Fun_ZD_ZYZ(1);	//���Ҹ첲				
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"TZZ"))                  
	{
		Fun_ZD_ZZ(1); 	//����				
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"TYZ"))               
	{
		Fun_ZD_YZ(1);	//���� 					
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"TLZ"))            
	{
		Fun_ZD_ZYZ(1);	//������					
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"BZSXS"))                   
	{
		Fun_SD_ZXB();	//��첲С���� 				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"BZSXX"))                  
	{
		Fun_SD_ZXB();	//��첲С����				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"BZSDS"))                    
	{
		Fun_SD_ZDB();	//��첲�����				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"BZSDX"))                  
	{
		Fun_SD_ZDB();	//��첲�����					
	}			
	if(strstr((const char *)UART4_RX_BUF,(const char *)"BZSBS"))               
	{
		Fun_SD_ZB();	//��첲��С����				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"BZSBX"))             
	{
		Fun_SD_ZB();	//��첲��С����					
	}			
	//�Ҹ첲			
	if(strstr((const char *)UART4_RX_BUF,(const char *)"BYSXS"))                   
	{
		Fun_SD_YXB();	//�Ҹ첲С����				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"BYSXX"))                  
	{
		Fun_SD_YXB();	//�Ҹ첲С����				
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"BYSDS"))                    
	{
		Fun_SD_YDB();	//�Ҹ첲�����				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"BYSDX"))                  
	{
		Fun_SD_YDB();	//�Ҹ첲�����					
	}				
	if(strstr((const char *)UART4_RX_BUF,(const char *)"BYSBS"))              
	{
		Fun_SD_YB();	//�Ҹ첲��С���� 				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"BYSBX"))             
	{
		Fun_SD_YB();	//�Ҹ첲��С���� 					
	}		
	//���Ҹ첲			
	if(strstr((const char *)UART4_RX_BUF,(const char *)"BLSXS"))               
	{
		Fun_SD_ZYXB();	//���Ҹ첲С����				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"BLSXX"))             
	{
		Fun_SD_ZYXB();	//���Ҹ첲С����				
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"BLSDS"))              
	{
		Fun_SD_ZYDB();	//���Ҹ첲����� 				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"BLSDX"))             
	{
		Fun_SD_ZYDB();	//���Ҹ첲�����					
	}				
	if(strstr((const char *)UART4_RX_BUF,(const char *)"BLSBS"))          
	{
		Fun_SD_ZYB();	//���Ҹ첲��С����				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"BLSBX"))         
	{
		Fun_SD_ZYB();	//���Ҹ첲��С����					
	}				
	//����			
	if(strstr((const char *)UART4_RX_BUF,(const char *)"TZSXS"))                      
	{
		Fun_SD_ZXT();	//����С����				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"TZSXX"))                    
	{
		Fun_SD_ZXT();	//����С����				
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"TZSDS"))                     
	{
		Fun_SD_ZDT();	//���ȴ����� 				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"TZSDX"))                    
	{
		Fun_SD_ZDT();	//���ȴ�����					
	}			
	if(strstr((const char *)UART4_RX_BUF,(const char *)"TZSTS"))                 
	{
		Fun_SD_ZT();	//���ȴ�С����				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"TZSTX"))               
	{
		Fun_SD_ZT();	//���ȴ�С����					
	}			
	//����
	if(strstr((const char *)UART4_RX_BUF,(const char *)"TYSXS"))                     
	{
		Fun_SD_YXT();	//����С����				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"TYSXX"))                   
	{
		Fun_SD_YXT();	//����С����				
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"TYSDS"))                    
	{
		Fun_SD_YDT();	//���ȴ����� 				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"TYSDX"))                   
	{
		Fun_SD_YDT();	//���ȴ�����					
	}				
	if(strstr((const char *)UART4_RX_BUF,(const char *)"TYSTS"))                
	{
		Fun_SD_YT();	//���ȴ�С����				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"TYSTX"))              
	{
		Fun_SD_YT();	//���ȴ�С����					
	}		
	//������
	if(strstr((const char *)UART4_RX_BUF,(const char *)"TLSXS"))                
	{
		Fun_SD_ZYXT();	//������С����				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"TLSXX"))              
	{
		Fun_SD_ZYXT();	//������С����				
	}	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"TLSDS"))                
	{
		Fun_SD_ZYDT();	//�����ȴ�����				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"TLSDX"))              
	{
		Fun_SD_ZYDT();	//�����ȴ�����					
	}				
	if(strstr((const char *)UART4_RX_BUF,(const char *)"TLSTS"))           
	{
		Fun_SD_ZYT();	//�����ȴ�С����				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"TLSTX"))         
	{
		Fun_SD_ZYT();	//�����ȴ�С����					
	}                         		
}

/*********************************************************************
*������       ��WIFI_FW()
*��������     ����λ����ģ��
*����         ����
*���         ����
***********************************************************************/
void WIFI_FW(void)
{
//	if(ESP8266_Get_ID())	//���յ���ǰ�豸���͵�ָ���������䷵��һ��Receivedָ��	
	if(strstr((const char *)UART4_RX_BUF,(const char *)"FWALL"))	      
	{
		Fun_FW_ALL();       //���и�λ	    
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"FWZBB"))	            
	{
		Fun_FW_ZB();     	//֧����λ    
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"FWQT"))              
	{			
		Fun_FW_QT();   	   //���ȸ�λ       
	}				
	if(strstr((const char *)UART4_RX_BUF,(const char *)"FWZBQ"))            
	{			
		ZBQ_Pic=24;
		Fun_ZBQ(1);	       //��������λ        
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"FWYL"))               
	{			
		Fun_FW_YL();         //�Ͳ�����һ������λ     
	}				
	if(strstr((const char *)UART4_RX_BUF,(const char *)"FWZF"))          
	{			
		Fun_FW_ZF();        //����λ				
	}
	if(strstr((const char *)UART4_RX_BUF,(const char *)"FWYF"))         
	{			
		Fun_FW_YF();        //�ҷ���λ	
	}
	//�������ų������ϴ���������һ���ذ�ָ�� 
	if(strstr((const char *)UART4_RX_BUF,(const char *)"WC"))                  
	{
		Wifi_Send("Received");
		Wifi_Send("FaultSolved");
		ZF3_GZ=0;         //����
		ZF4_GZ=0;         //����
		ZF5_GZ=0;         //����
		YF3_GZ=0;         //�ҷ���
		YF4_GZ=0;         //�ҷ���
		YF5_GZ=0;         //�ҷ���
		ZBQ_GZ=0;         //�Զ�����
		YL_GZ=0;          //�Ͳ�����һ����
		ZBH_GZ=0;         //�󱳲�����
		YBH_GZ=0;         //�ұ�������
		ZYH_GZ=0;         //����������
		YYH_GZ=0;         //����������
		
		//���ʧ����־λ	
		ZF_SB=0;         //����
		YF_SB=0;         //�ҷ���
		ZBQ_SB=0;        //�Զ�����
		YL_SB=0;         //�Ͳ�����һ����
		ZBH_SB=0;        //�󱳲�����
		YBH_SB=0;        //�ұ�������
		ZYH_SB=0;        //����������
		YYH_SB=0;        //����������

	}					
}


/*********************************************************************
*������       ��U2_Wifi_SZ()
*��������     ��WiFi���ù���ģ��
*����         ����
*���         ����
***********************************************************************/
void U2_Wifi_SZ(void)
{	
	//��λ������WiFiģʽ
	if(strstr((const char *)USART2_RX_BUF,(const char *)"Mode"))          
	{			 
		//WiFi����ΪAPģʽ
		if(strstr((const char *)USART2_RX_BUF,(const char *)"AP"))        
		{			 
			W25QXX_Write((u8*)modeap_buf,10,2);		//��modeap_bufд��flash
			u2_printf("\r\n���ó�APģʽ\r\n");
		}
		//WiFi����ΪSTAģʽ
		if(strstr((const char *)USART2_RX_BUF,(const char *)"STA"))       
		{			 
			W25QXX_Write((u8*)modesta_buf,10,2);			//��modeap_bufд��flash
			u2_printf("\r\n���ó�STAģʽ\r\n");					
		}					
	}
	//wifi����-STAģʽ
	if(strstr((const char *)USART2_RX_BUF,(const char *)"staset"))        
	{ 
		get_wifiname_wifipassword(wifi_station,wifi_station_password);    //��ȡWiFi���ƺ�����	
	}		
	//wifi����-APģʽ
	if(strstr((const char *)USART2_RX_BUF,(const char *)"apset"))         
	{ 
		get_apname_wifipassword(wifi_ssid,wifi_ssid_password);            //��ȡWiFi�����ƺ�����
	}	
	//wifi����IP��PORT
	if(strstr((const char *)USART2_RX_BUF,(const char *)"ipportset"))     
	{ 
		get_ip_port(wifi_ap_ip,wifi_ap_port);                             //��ȡWiFi��ip��ַ�Ͷ˿ں�
	}	
	//wifi�������ƺ�����
	if(strstr((const char *)USART2_RX_BUF,(const char *)"wifireset"))     
	{ 
		delay_ms(100);
		get_wifiname_wifipassword(wifi_name,wifi_password);	              //��ȡWiFi�����ƺ�����
	}	
	//STAģʽ��ʼ��
	if(strstr((const char *)USART2_RX_BUF,(const char *)"stastart"))      
	{ 
		ESP8266_apsta_Init(4);		//STAģʽ��ʼ������
	}			
	//apģʽ��ʼ��
	if(strstr((const char *)USART2_RX_BUF,(const char *)"apstart"))       
	{ 
		ESP8266_AP_Init(4);			//APģʽ��ʼ������
	}				
	//��ȡ��λ�������趨ֵ
	if(strstr((const char *)USART2_RX_BUF,(const char *)"newangle"))      
	{ 
		Read_Ang();							//��ȡ��λ�������趨ֵ����
	}	
}

/*********************************************************************
*������       ��U2_CSSZ()
*��������     ����λ������������ù���ģ��
*����         ����
*���         ����
***********************************************************************/
void U2_CSSZ(void)
{	
	//��λ������Ƕ�
	if(strstr((const char *)USART2_RX_BUF,(const char *)"AngAll"))  
	{			 
		Fun_Get_Ang();  //����µĽǶ�ֵ
	}			
	//֧��		  		
	if(strstr((const char *)USART2_RX_BUF,(const char *)"AngZB"))   
	{
		p = strstr((const char *)USART2_RX_BUF,(const char *)"AngZB");
		if((usmart_strnum(p+1)!=0) &&(usmart_strnum(p+1)<=90))             //����λ�����͵��ַ����е�����ת��Ϊʮ����
		{
			ZB_Lim=usmart_strnum(p+1);                             //������λ���趨�ĽǶ�ֵ																			
//			W25QXX_Write((u8*)ZB_Lim,13,1);                        //����������λ���趨�Ƕ�ֵ
		}
	}
	//����	
	if(strstr((const char *)USART2_RX_BUF,(const char *)"AngZF"))
	{
		p = strstr((const char *)USART2_RX_BUF,(const char *)"AngZF");
		if((usmart_strnum(p+1)!=0)&&(usmart_strnum(p+1)<=60))                //����λ�����͵��ַ����е�����ת��Ϊʮ����
		{				
			ZF_Lim=usmart_strnum(p+1);                          //������λ���趨�ĽǶ�ֵ										 								
//			W25QXX_Write((u8*)ZF_Lim,14,1);                     //����������λ���趨����ֵ
		}
	}
	//�ҷ���	
	if(strstr((const char *)USART2_RX_BUF,(const char *)"AngYF"))
	{
		p = strstr((const char *)USART2_RX_BUF,(const char *)"AngYF");
		if((usmart_strnum(p+1)!=0)&&(usmart_strnum(p+1)<=60))                 //����λ�����͵��ַ����е�����ת��Ϊʮ����
		{
			YF_Lim=usmart_strnum(p+1);                          //������λ���趨�ĽǶ�ֵ															
//			W25QXX_Write((u8*)YF_Lim,15,1);                 //����������λ���趨����ֵ
		}
	}
	//������		
	if(strstr((const char *)USART2_RX_BUF,(const char *)"AngSQT"))     
	{
		p = strstr((const char *)USART2_RX_BUF,(const char *)"AngSQT");
		if((usmart_strnum(p+1)!=0)&&(usmart_strnum(p+1)<=40))                 //����λ�����͵��ַ����е�����ת��Ϊʮ����
		{
			SQT_Lim=usmart_strnum(p+1);                              //������λ���趨�ĽǶ�ֵ													
//			W25QXX_Write((u8*)SQT_Lim,16,1);                     //����������λ���趨����ֵ				
		}
	}
	//������	
	if(strstr((const char *)USART2_RX_BUF,(const char *)"AngXQT"))   
	{
		p = strstr((const char *)USART2_RX_BUF,(const char *)"AngXQT");
		if((usmart_strnum(p+1)!=0)&&(usmart_strnum(p+1)<=90))                 //����λ�����͵��ַ����е�����ת��Ϊʮ����
		{
			XQT_Lim=usmart_strnum(p+1);                            //������λ���趨�ĽǶ�ֵ													
//			W25QXX_Write((u8*)XQT_Lim,17,1);	                  //����������λ���趨����ֵ
		}
	}
	//��������һ����	
	if(strstr((const char *)USART2_RX_BUF,(const char *)"AngYL"))      
	{
		p = strstr((const char *)USART2_RX_BUF,(const char *)"AngYL");
		if((usmart_strnum(p+1)!=0) &&(usmart_strnum(p+1)<=100))   //����λ�����͵��ַ����е�����ת��Ϊʮ����
		{
			YL_Lim=usmart_strnum(p+1);                              //������λ���趨�ĽǶ�ֵ											
//			W25QXX_Write((u8*)YL_Lim,18,1);		              			//����������λ���趨����ֵ
		}
	}							
	//��ϴ���ʱ��		
	if(strstr((const char *)USART2_RX_BUF,(const char *)"TimeCXHG")) 
	{
		p = strstr((const char *)USART2_RX_BUF,(const char *)"TimeCXHG");
		if((usmart_strnum(p+1)!=0)&&(usmart_strnum(p+1)<=5))  //����λ�����͵��ַ����е�����ת��Ϊʮ����
		{
			CXHG_Time=usmart_strnum(p+1);                 		 //������λ���趨�ĳ�ϴ���ʱ��														
//			W25QXX_Write((u8*)CXHG_Time,19,1);	       			 //����������λ���趨����ֵ	
		}
	}
}

/*********************************************************************
*������       ��U2_JCGN()
*��������     ����������ģ��
*����         ����
*���         ����
***********************************************************************/
void U2_JCGN(void)
{
	if(strstr((const char *)USART2_RX_BUF,(const char *)"ZBS"))            
	{
		Fun_ZB();	    //֧����			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"ZBX"))           
	{
		Fun_ZB();        //֧����
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"SQTS"))            
	{
		Fun_SQT();       //��������
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"SQTX"))          
	{
		Fun_SQT();		//��������			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"XQTX"))        
	{
		Fun_XQT();		//��������			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"XQTS"))          
	{
		Fun_XQT();		//��������			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"ZFS"))         
	{
		Fun_ZF();		//������				
	}			
	if(strstr((const char *)USART2_RX_BUF,(const char *)"ZFX"))       
	{
		Fun_ZF();		//������			
	}	
	if(strstr((const char *)USART2_RX_BUF,(const char *)"YFS"))        
	{
		Fun_YF();		//�ҷ�����				
	}	
	if(strstr((const char *)USART2_RX_BUF,(const char *)"YFX"))     
	{
		Fun_YF();		//�ҷ�����				
	}						
	if(strstr((const char *)USART2_RX_BUF,(const char *)"YLS"))            
	{
		Fun_YL1();      //��������һ������ǰ
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"YLX"))          
	{
		Fun_YL1();      //��������һ��������
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"ZBH"))    
	{
		Fun_ZBH();	  //�󱳲�����			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"YBH"))   
	{
		Fun_YBH();	  //�ұ�������			
	}				
	if(strstr((const char *)USART2_RX_BUF,(const char *)"ZYH"))   
	{
		Fun_ZYH();	  //����������				
	}				
	if(strstr((const char *)USART2_RX_BUF,(const char *)"YYH"))  
	{
		Fun_YYH();     //����������
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"ZDZBQ"))        
	{
		Fun_ZDZBQ();  //�Զ�����				
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"SDCX"))        
	{
		Fun_SDCX();	  //�ֶ���ϴ				
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"SDHG"))        
	{
		Fun_SDHG();	  //�ֶ����				
	}	
	if(strstr((const char *)USART2_RX_BUF,(const char *)"JRE"))                   
	{
		Fun_JR();	  //����			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"LD"))                        
	{
		Fun_LD();	 //���ܺ������� 					
	}
	
	//�������ܺ���
	if(strstr((const char *)USART2_RX_BUF,(const char *)"HLZB"))           
	{
		Fun_HL_ZB();		//֧��			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"HLZF"))      
	{
		Fun_HL_ZF();		//����				
	}				
	if(strstr((const char *)USART2_RX_BUF,(const char *)"HLYF"))     
	{
		Fun_HL_YF();		//�ҷ���			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"HLBH"))   
	{
		Fun_HL_BH();		//��������			
	}							
	if(strstr((const char *)USART2_RX_BUF,(const char *)"HLYH"))  
	{
		Fun_HL_YH();		//��������				
	}				
	if(strstr((const char *)USART2_RX_BUF,(const char *)"HLZDZB"))   
	{
		Fun_ZDZBQ();		//�Զ�����			
	}						
	if(strstr((const char *)USART2_RX_BUF,(const char *)"HLSD"))          
	{
		Fun_HL_SD();       //����
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"HLFW"))        
	{
		Fun_FW_ALL();	  //���縴λ				
	}
	
	//************************���Ժ���*********************************
		
	if(strstr((const char *)USART2_RX_BUF,(const char *)"Y2L2_1"))   
	{
		WriteInU2("YLS");		//����2��������д��"YLS"
		Fun_YL2();					//С������ǰ	
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"Y2L2_0"))   
	{
		WriteInU2("YLX");		//����2��������д��"YLX"
		Fun_YL2();		   		//С�������
	}
	
	if(strstr((const char *)USART2_RX_BUF,(const char *)"U2_Z1D1C1X1"))   
	{
		ZBQ_Flag=1;					//��������־λ��1
		Fun_ZDCX();		      //�Զ���ϴ				
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"U2_Z1D1H1G1"))   
	{
		ZBQ_Flag=1;					//��������־λ��1
		Fun_ZDHG();	        //�Զ����					
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"U2_ZBC1X1H1G1"))        
	{
		ZBQ_Flag=1;					//��������־λ��1
		RELAY6=1; 					//�̵����õ�
		Fun_ZBCXHG(1,CXHG_Lim);   //��ϴ����Ƹ����
		RELAY6=0; 	      	//�̵���ʧ��	
	}		
	if(strstr((const char *)USART2_RX_BUF,(const char *)"U2_ZBC1X1H1G0"))                
	{
		ZBQ_Flag=1;					//��������־λ��1
		RELAY6=1; 					//�̵����õ� 		
		Fun_ZBCXHG(0,CXHG_Lim); //��ϴ����Ƹ�����
		RELAY6=0;	  	      		//�̵���ʧ��	    					
	}

	if(strstr((const char *)USART2_RX_BUF,(const char *)"U2_Z1B1D0"))              
	{
		ZBQ_Flag=1;					//��������־λ��1
		Fun_ZBD(0);	  	    //������ս� 		
	}		
	
	if(strstr((const char *)USART2_RX_BUF,(const char *)"U2_Z1B1D1"))            
	{
		ZBQ_Flag=1;					//��������־λ��1
		Fun_ZBD(1);	  		  //��������ߵ�������������		
	}
	
	if(strstr((const char *)USART2_RX_BUF,(const char *)"U2_Z1B1T1G1"))          
	{
		ZBQ_Flag=1;					//��������־λ��1
		RELAY6=1;           //�̵����õ�
		Fun_ZBTG(1,ZBDTG_Lim); //�����Ƹ����	
		RELAY6=0;           //�̵���ʧ��	  
	}		
	if(strstr((const char *)USART2_RX_BUF,(const char *)"U2_Z1B1T1G0"))               
	{
		ZBQ_Flag=1;					//��������־λ��1
		RELAY6=1;           //�̵����õ�
		Fun_ZBTG(0,ZBDTG_Lim);//�����Ƹ�����	
		RELAY6=0; 	      		//�̵���ʧ��          
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"U2CF1"))           
	{
		u2_printf("�෭��ʼ");
		Fun_FW_CF(1);					//�෭��λ
		u2_printf("�෭����");
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"U2CF0"))           
	{
		u2_printf("�෭��ʼ");
		Fun_FW_CF(0);					//�෭��ʼ
		u2_printf("�෭����");
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"U2_Z1B1Q1"))           
	{
		u2_printf("��������");
		Fun_ZBQ(0);	  				//��������
	}		
	if(strstr((const char *)USART2_RX_BUF,(const char *)"U2_Z1B1Q0"))              
	{
		u2_printf("�������ر�");			
		Fun_ZBQ(1);	  				//�������ر�
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"C2Z2"))              
	{
		u2_printf("����");			
		Fun_CZ1();	  				//���غ���
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"DIR_SB1")) 
	{
		RELAY6=1;			 //�̵�����
		DIR_SB=1;      //ˮ�ô�	
	}
	
	if(strstr((const char *)USART2_RX_BUF,(const char *)"DIR_SB0"))  
	{
		RELAY6=0;			 //�̵����ر�
		DIR_SB=0;      //ˮ�ùر�	
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"DIR_HG1"))       
	{
		RELAY6=1;			 //�̵�����
		DIR_QB=1;      //���ô�	
		DIR_HG=1;			 //��ɷ���
	}
	
	if(strstr((const char *)USART2_RX_BUF,(const char *)"DIR_HG0"))        
	{
		RELAY6=0;	 		 //�̵���ʧ��	
		DIR_QB=0;			 //���ùر�	
		DIR_HG=0;			 //��ɷ��ر�	
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"testhang1"))             
	{
		DG_Relay=1; 	//�̵����õ�
		TestAll(1);		//����
		DG_Relay=0;		//�̵���ʧ��
	}	

	if(strstr((const char *)USART2_RX_BUF,(const char *)"testhang0"))             
	{
		DG_Relay=1;		//�̵����õ�
		TestAll(0);
		DG_Relay=0;	  //�̵���ʧ��
	}	
						
	if(strstr((const char *)USART2_RX_BUF,(const char *)"Hang1_1"))              
	{
		DG_Relay=1;	  					//�̵����õ�    
		delay_ms(300);
		u2_printf("XINHAO");    //����1
		Hang1(0);	  	
		DG_Relay=0;						 //�̵���ʧ��     
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"Hang1_0"))              
	{
		DG_Relay=1;	  //�̵����õ�   
		Hang1(1);	    //����1
		DG_Relay=0;		//�̵���ʧ��	     
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"Hang2_1"))           
	{
		DG_Relay=1;	  //�̵����õ�   
		Hang2(1);	    //����2
		DG_Relay=0;		//�̵���ʧ��	      
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"Hang2_0"))             
	{
		DG_Relay=1;	  //�̵����õ�   
		Hang2(0);	    //����2
		DG_Relay=0;	  //�̵���ʧ��   
	}

	if(strstr((const char *)USART2_RX_BUF,(const char *)"Hang3_1"))            
	{
		DG_Relay=1;	  //�̵����õ�     
		Hang3(0);	    //����3
		DG_Relay=0;	  //�̵���ʧ��   
	}
	
	if(strstr((const char *)USART2_RX_BUF,(const char *)"Hang3_0"))             
	{
		DG_Relay=1;	   //�̵����õ�   
		Hang3(1);	     //����3
		DG_Relay=0;	   //�̵���ʧ��   
	}

	if(strstr((const char *)USART2_RX_BUF,(const char *)"Hang4_1"))             
	{
		DG_Relay=1;	   //�̵����õ�   
		Hang4(1);	     //����4
		DG_Relay=0;	   //�̵���ʧ��  
	}
	
	if(strstr((const char *)USART2_RX_BUF,(const char *)"Hang4_0"))             
	{
		DG_Relay=1;	  //�̵����õ�     
		Hang4(0);     //����4
		DG_Relay=0;	  //�̵���ʧ��  
	}	
	//���1  
	if(strstr((const char *)USART2_RX_BUF,(const char *)"MOTOR1111"))              
	{
		Motor1(1);	  //1�ŵ��		
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"MOTOR1110"))              
	{
		Motor1(0);	   //1�ŵ��				
	} 

	//���2  
	if(strstr((const char *)USART2_RX_BUF,(const char *)"MOTOR2221"))              
	{
		Motor2(1);	  //1�ŵ�� 				
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"MOTOR2220"))             
	{
		Motor2(0);	  //1�ŵ�� 				
	} 

	//���3  
	if(strstr((const char *)USART2_RX_BUF,(const char *)"MOTOR3331"))              
	{
		Motor3(1);	   //3�ŵ��				
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"MOTOR3330"))              
	{
		Motor3(0);	   //3�ŵ��				
	}
	//���4 
	if(strstr((const char *)USART2_RX_BUF,(const char *)"MOTOR4441"))            
	{
		Motor4(1);	   //4�ŵ��				
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"MOTOR4440"))             
	{
		Motor4(0);	   //4�ŵ��				
	}
	//���5 		
	if(strstr((const char *)USART2_RX_BUF,(const char *)"MOTOR5551"))             
	{
		Motor5(1);	   //5�ŵ��				
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"MOTOR5550"))             
	{
		Motor5(0);	   //5�ŵ��				
	}
	//���6 		
	if(strstr((const char *)USART2_RX_BUF,(const char *)"MOTOR6661"))              
	{
		Motor6(1);	   //6�ŵ��				
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"MOTOR6660"))            
	{
		Motor6(0);	   //6�ŵ��				
	}
	//���7		
	if(strstr((const char *)USART2_RX_BUF,(const char *)"MOTOR7771"))             
	{
		Motor7(1);	   //7�ŵ��				
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"MOTOR7770"))              
	{
		Motor7(0);	   //7�ŵ��				
	}	
}

/*********************************************************************
*������       ��U2_GJGN()
*��������     ���߼�����ģ��
*����         ����
*���         ����
***********************************************************************/
void U2_GJGN(void)
{
	if(strstr((const char *)USART2_RX_BUF,(const char *)"JRAM"))     
	{
		Fun_JRAM();		    //���ⰴĦ			
	}
	//ר��ϵͳ						
	if(strstr((const char *)USART2_RX_BUF,(const char *)"ZJZB"))              
	{
		Fun_ZJ_ZB();		//ר��ϵͳ֧��				
	}	
	if(strstr((const char *)USART2_RX_BUF,(const char *)"ZJZYF"))               
	{
		Fun_ZJ_ZYF();		//ר��ϵͳ����				
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"ZJSXQT"))                 
	{
		Fun_ZJ_SXQT();		//ר��ϵͳ���� 				
	}	
	if(strstr((const char *)USART2_RX_BUF,(const char *)"ZJZDZB"))          
	{
		Fun_ZJ_ZDZB();		//ר��ϵͳ�Զ�����				
	}	
	//���ҿ���ѵ��
	//�Զ�ģʽ										
	if(strstr((const char *)USART2_RX_BUF,(const char *)"BZZ"))                
	{
		Fun_ZD_ZZ(1); 		//��첲			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"BYZ"))               
	{
		Fun_ZD_YZ(1);		//�Ҹ첲			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"BLZ"))          
	{
		Fun_ZD_ZYZ(1);		//���Ҹ첲			
	}	
	if(strstr((const char *)USART2_RX_BUF,(const char *)"TZZ"))                
	{
		Fun_ZD_ZZ(1); 		//����			
	}	
	if(strstr((const char *)USART2_RX_BUF,(const char *)"TYZ"))              
	{
		Fun_ZD_YZ(1);		//����				
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"TLZ"))          
	{
		Fun_ZD_ZYZ(1);		//������				
	}
											
	//����ѵ���ֶ�ģʽ								
	if(strstr((const char *)USART2_RX_BUF,(const char *)"BZSXS"))              
	{
		Fun_SD_ZXB();	   //��첲С����			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"BZSXX"))            
	{
		Fun_SD_ZXB();	  //��첲С����			
	}	
	if(strstr((const char *)USART2_RX_BUF,(const char *)"BZSDS"))              
	{
		Fun_SD_ZDB();	  //��첲�����			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"BZSDX"))            
	{
		Fun_SD_ZDB();	  //��첲�����				
	}				
	if(strstr((const char *)USART2_RX_BUF,(const char *)"BZSBS"))          
	{
		Fun_SD_ZB();	  //��첲��С����			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"BZSBX"))        
	{
		Fun_SD_ZB();	  //��첲��С����				
	}					
	if(strstr((const char *)USART2_RX_BUF,(const char *)"BYSXS"))             
	{
		Fun_SD_YXB();	  //�Ҹ첲С����			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"BYSXX"))           
	{
		Fun_SD_YXB();	  //�Ҹ첲С����			
	}	
	if(strstr((const char *)USART2_RX_BUF,(const char *)"BYSDS"))             
	{
		Fun_SD_YDB();		//�Ҹ첲�����			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"BYSDX"))           
	{
		Fun_SD_YDB();		//�Ҹ첲�����				
	}				
	if(strstr((const char *)USART2_RX_BUF,(const char *)"BYSBS"))         
	{
		Fun_SD_YB();		//�Ҹ첲��С����			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"BYSBX"))        
	{
		Fun_SD_YB();		//�Ҹ첲��С����				
	}			
	if(strstr((const char *)USART2_RX_BUF,(const char *)"BLSXS"))          
	{
		Fun_SD_ZYXB();		//���Ҹ첲С����			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"BLSXX"))        
	{
		Fun_SD_ZYXB();		//���Ҹ첲С����			
	}	
	if(strstr((const char *)USART2_RX_BUF,(const char *)"BLSDS"))          
	{
		Fun_SD_ZYDB();		//���Ҹ첲�����			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"BLSDX"))        
	{
		Fun_SD_ZYDB();		//���Ҹ첲�����				
	}				
	if(strstr((const char *)USART2_RX_BUF,(const char *)"BLSBS"))        
	{
		Fun_SD_ZYB();	//���Ҹ첲��С����				
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"BLSBX"))        
	{
		Fun_SD_ZYB();	//���Ҹ첲��С����					
	}						
	if(strstr((const char *)USART2_RX_BUF,(const char *)"TZSXS"))                   
	{
		Fun_SD_ZXT();		//����С����			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"TZSXX"))                 
	{
		Fun_SD_ZXT();		//����С����			
	}	
	if(strstr((const char *)USART2_RX_BUF,(const char *)"TZSDS"))                   
	{
		Fun_SD_ZDT();		//���ȴ�����			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"TZSDX"))                 
	{
		Fun_SD_ZDT();		//���ȴ�����				
	}				
	if(strstr((const char *)USART2_RX_BUF,(const char *)"TZSTS"))               
	{
		Fun_SD_ZT();		//���ȴ�С����			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"TZSTX"))             
	{
		Fun_SD_ZT();		//���ȴ�С����				
	}			
	if(strstr((const char *)USART2_RX_BUF,(const char *)"TYSXS"))                  
	{
		Fun_SD_YXT();		//����С����			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"TYSXX"))                
	{
		Fun_SD_YXT();		//����С����			
	}	
	if(strstr((const char *)USART2_RX_BUF,(const char *)"TYSDS"))                  
	{
		Fun_SD_YDT();		//���ȴ�����			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"TYSDX"))                
	{
		Fun_SD_YDT();		//���ȴ�����				
	}				
	if(strstr((const char *)USART2_RX_BUF,(const char *)"TYSTS"))              
	{
		Fun_SD_YT();		//���ȴ�С����			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"TYSTX"))           
	{ 
		Fun_SD_YT();		//���ȴ�С����				
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"TLSXS"))            
	{
		Fun_SD_ZYXT();		//������С����			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"TLSXX"))          
	{
		Fun_SD_ZYXT();		//������С����			
	}	
	if(strstr((const char *)USART2_RX_BUF,(const char *)"TLSDS"))            
	{
		Fun_SD_ZYDT();		//�����ȴ�����			
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"TLSDX"))          
	{
		Fun_SD_ZYDT();		//�����ȴ�����				
	}				
	if(strstr((const char *)USART2_RX_BUF,(const char *)"TLSTS"))         
	{
		Fun_SD_ZYT();	//�����ȴ�С����				
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"TLSTX"))        
	{
		Fun_SD_ZYT();	//�����ȴ�С����					
	}	                         	
}
/*********************************************************************
*������       ��U2_FW()
*��������     ����λ����ģ��
*����         ����
*���         ����
***********************************************************************/
void U2_FW(void)
{						
	if(strstr((const char *)USART2_RX_BUF,(const char *)"FWALL"))	      
	{
		Fun_FW_ALL();     //���и�λ	    
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"FWZBB"))	      
	{
		Fun_FW_ZB();     //֧����λ	    
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"FWQT"))         
	{			
		Fun_FW_QT();   	//���ȸ�λ	       
	}					
	if(strstr((const char *)USART2_RX_BUF,(const char *)"FWZBQ"))     
	{
		ZBQ_Pic=24;
		Fun_ZBQ(1);	        //��������λ      
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"FWYL"))        
	{			
		Fun_FW_YL();        //�Ͳ�����һ������λ      
	}					
	if(strstr((const char *)USART2_RX_BUF,(const char *)"FWZF"))    
	{			
		Fun_FW_ZF();       	//����λ				
	}
	if(strstr((const char *)USART2_RX_BUF,(const char *)"FWYF"))   	
	{			
		Fun_FW_YF();        //�ҷ���λ
	}
	//�������ų������ϴ���������һ���ذ�ָ��
	if(strstr((const char *)USART2_RX_BUF,(const char *)"WC"))           
	{
		u2_printf("Received");
		u2_printf("WC");
		
/*********************����־λ������Ϊ0***********************/
		
		//������ر�־λ			
		ZF3_GZ=0;         //����
		ZF4_GZ=0;         //����
		ZF5_GZ=0;         //����
		YF3_GZ=0;         //�ҷ���
		YF4_GZ=0;         //�ҷ���
		YF5_GZ=0;         //�ҷ���
		ZBQ_GZ=0;         //�Զ�����
		YL_GZ=0;          //�Ͳ�����һ����
		ZBH_GZ=0;         //�󱳲�����
		YBH_GZ=0;         //�ұ�������
		ZYH_GZ=0;         //����������
		YYH_GZ=0;         //����������
		
		//���ʧ����־λ	
		ZF_SB=0;         //����
		YF_SB=0;         //�ҷ���
		ZBQ_SB=0;        //�Զ�����
		YL_SB=0;         //�Ͳ�����һ����
		ZBH_SB=0;        //�󱳲�����
		YBH_SB=0;        //�ұ�������
		ZYH_SB=0;        //����������
		YYH_SB=0;        //����������
	}					
}


/***********************************************************************
 ������      ��IO_TEST(void)   
 ��������    �����ư�IO�ڲ���
 ����        ����
 ���        ����  
                          
************************************************************************/
void IO_TEST(void)
{
	GPIO_InitTypeDef GPIO_Initure;          //����ṹ�����GPIO_Initure
    __HAL_RCC_GPIOA_CLK_ENABLE();           //ʹ��GPIOAʱ�� 
	__HAL_RCC_GPIOB_CLK_ENABLE();           //ʹ��GPIOAʱ�� 
    __HAL_RCC_GPIOC_CLK_ENABLE();           //����GPIOCʱ��
	__HAL_RCC_GPIOD_CLK_ENABLE();           //����GPIOCʱ��
    __HAL_RCC_GPIOE_CLK_ENABLE();           //����GPIOEʱ��
    __HAL_RCC_GPIOH_CLK_ENABLE();           //����GPIOHʱ��
    __HAL_RCC_GPIOG_CLK_ENABLE();           //����GPIOGʱ��
    __HAL_RCC_GPIOI_CLK_ENABLE();           //����GPIOIʱ��
		
    GPIO_Initure.Pin=GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_11|GPIO_PIN_12;            //PA0
    GPIO_Initure.Mode=GPIO_MODE_INPUT;      //����
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);	

    GPIO_Initure.Pin=GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;            //PA12
    GPIO_Initure.Mode=GPIO_MODE_INPUT;       //����
    GPIO_Initure.Pull=GPIO_PULLUP;           //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;      //����
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);		
	
    GPIO_Initure.Pin=GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_12|GPIO_PIN_13; 
	GPIO_Initure.Mode=GPIO_MODE_INPUT;      //����
    GPIO_Initure.Pull=GPIO_PULLUP; 
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(GPIOC,&GPIO_Initure);	

    GPIO_Initure.Pin=GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_7|GPIO_PIN_13; 
	GPIO_Initure.Mode=GPIO_MODE_INPUT;      //����
    GPIO_Initure.Pull=GPIO_PULLUP; 
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(GPIOD,&GPIO_Initure);	

    GPIO_Initure.Pin=GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6; 
	GPIO_Initure.Mode=GPIO_MODE_INPUT;      //����
    GPIO_Initure.Pull=GPIO_PULLUP; 
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(GPIOE,&GPIO_Initure);	

    GPIO_Initure.Pin=GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
	GPIO_Initure.Mode=GPIO_MODE_INPUT;      //����
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(GPIOH,&GPIO_Initure);	

    GPIO_Initure.Pin=GPIO_PIN_3|GPIO_PIN_6|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14;
	GPIO_Initure.Mode=GPIO_MODE_INPUT;      //����
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(GPIOG,&GPIO_Initure);	

    GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8; //PI4
	GPIO_Initure.Mode=GPIO_MODE_INPUT;      //����
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(GPIOI,&GPIO_Initure);		
}

/***********************************************************************
 ������      ��WriteInU4(void)  
 ��������    ������4д�뺯��
 ����        ��Ҫд��UART4_RX_BUF���ַ���""
 ���        ����                           
************************************************************************/
void WriteInU4(char *p)
{
	u8 len=strlen(p);			  //��ȡ�ַ�������
	u8 i;
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);	//�������4���պ���
	for(i=0;i<len;i++)
	{
	  UART4_RX_BUF[i]=p[i];	//�򴮿�4��������
	}	
}
/***********************************************************************
 ������      ��Ang_To_Arr_ZB  
 ��������    �����Ƕ�ֵת�����Զ���װ��ֵ
 ����        ���Ƕȣ�u8����
 ���        ��TIM3�Զ���װ��ֵ��u16����                           
************************************************************************/
u16 Ang_To_Arr_ZB(u8 angle)   //֧��
{
	u16 res;
	res=600*angle;//600
	return res;
}

u16 Ang_To_Arr_SXQT(u8 angle)   //����
{
	u16 res;
	res=380*angle;//400
	return res;
}

u16 Ang_To_Arr_ZYFS(u8 angle)  //����
{
	u16 res;
	res=300*angle;//280
	return res;
}

u16 Ang_To_Arr_YL(u8 distance)   //����
{
	u16 res;
	res=655*distance;//600
	return res;
}
u32 Ang_To_Arr_YL2(u8 distance)   //����
{
	u16 res;
	res=8000*distance;//600
	return res;
}
/***********************************************************************
 ������      ��Fun_Get_Ang
 ��������    ��ͨ������2����µĽǶ�ֵ
 ����        ����
 ���        ���� 
 ɨ������     ��USART2_RX_BUF��������2
 ����˵��        ������+���롰+���ַ�֮���������ȡ������������ȫ�ֵĽǶȱ���
 ����        ��AngAll+80+40+90+45+45+100+
               ֧���Ƕȣ�ZB_Lim��=80�������ȽǶȣ�SQT_Lim��=40�������ȽǶȣ�XQT_Lim��=90��
               �󷭽Ƕȣ�ZF_Lim��=45���ҷ��Ƕȣ�YF_Lim��=45��С�����ƶ����루YL_Lim��=100��
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
	
	presult1 = strstr( (const char *)USART2_RX_BUF ,(const char *)"+");	//��ȡ�ַ����е�1��"+"�ĵ�ַ
	presult2 = strstr( (const char *)presult1+1 , (const char *)"+");		//��ȡ�ַ����е�2��"+"�ĵ�ַ
	presult3 = strstr( (const char *)presult2+1 , (const char *)"+");		//��ȡ�ַ����е�3��"+"�ĵ�ַ		
	presult4 = strstr( (const char *)presult3+1 , (const char *)"+");		//��ȡ�ַ����е�4��"+"�ĵ�ַ			
	presult5 = strstr( (const char *)presult4+1 , (const char *)"+");		//��ȡ�ַ����е�5��"+"�ĵ�ַ		
 	presult6 = strstr( (const char *)presult5+1 , (const char *)"+");		//��ȡ�ַ����е�6��"+"�ĵ�ַ
	presult7 = strstr( (const char *)presult6+1 , (const char *)"+");		//��ȡ�ַ����е�7��"+"�ĵ�ַ
	presult8 = strstr( (const char *)presult7+1 , (const char *)"+");		//��ȡ�ַ����е�8��"+"�ĵ�ַ
	memcpy(ip1,presult1+1,presult2-presult1-1);   //��presult1+1��presult2-presult1-1֮������ݸ��Ƶ�ip1������
	memcpy(ip2,presult2+1,presult3-presult2-1);  	//��presult2+1��presult3-presult2-1֮������ݸ��Ƶ�ip1������
	memcpy(ip3,presult3+1,presult4-presult3-1);  	//��presult3+1��presult4-presult3-1֮������ݸ��Ƶ�ip1������	
	memcpy(ip4,presult4+1,presult5-presult4-1);  	//��presult4+1��presult5-presult4-1֮������ݸ��Ƶ�ip1������		
	memcpy(ip5,presult5+1,presult6-presult5-1);  	//��presult5+1��presult6-presult5-1֮������ݸ��Ƶ�ip1������	
	memcpy(ip6,presult6+1,presult7-presult6-1);  	//��presult6+1��presult7-presult6-1֮������ݸ��Ƶ�ip1������
	memcpy(ip7,presult7+1,presult8-presult7-1);  	//��presult7+1��presult8-presult7-1֮������ݸ��Ƶ�ip1������
	
	//��ip1�����е��������ַ���ת��������
	ZB_Buf[0]=usmart_strnum(ip1);       //֧��  
	SQT_Buf[0]=usmart_strnum(ip2);      //������
	XQT_Buf[0]=usmart_strnum(ip3);      //������
	ZF_Buf[0]=usmart_strnum(ip4);       //��
	YF_Buf[0]=usmart_strnum(ip5);       //�ҷ�
	YL_Buf[0]=usmart_strnum(ip6);       //�����ƶ�����
	CXHG_Buf[0]=usmart_strnum(ip7);     //��ϴ���ʱ��	

	if(ZB_Buf[0]<=90)             //֧��
	{	ZB_Lim=ZB_Buf[0];	}
	
	if(SQT_Buf[0]<=40)  	     //������
	{	SQT_Lim=SQT_Buf[0]; 	} 
	
	if(XQT_Buf[0]<=90)	      //������
	{	XQT_Lim=XQT_Buf[0]; 	}

	if(ZF_Buf[0]<=90)	       //��
	{	ZF_Lim=ZF_Buf[0];	}  
	
	if(ZF_Buf[0]<=90)	       //�ҷ�	
	{	YF_Lim=YF_Buf[0]; 	} 

	if(YL_Buf[0]<=100)          //�����ƶ�����   
	{	YL_Lim=YL_Buf[0];		}

	if(CXHG_Buf[0]<=5)             //��ϴ���ʱ��  
	{	CXHG_Time=CXHG_Buf[0];		}
 	

//	//����������λ���趨����ֵ
//	W25QXX_Write((u8*)ZB_Buf,13,1);         //�ӵ�13��ַ��ʼ��д��1���ֽ�
//	W25QXX_Write((u8*)SQT_Buf,14,1);		//�ӵ�14��ַ��ʼ��д��1���ֽ�
//	W25QXX_Write((u8*)XQT_Buf,15,1);		//�ӵ�15��ַ��ʼ��д��1���ֽ�
//	W25QXX_Write((u8*)ZF_Buf,16,1);	        //�ӵ�16��ַ��ʼ��д��1���ֽ�
//	W25QXX_Write((u8*)YF_Buf,17,1);	        //�ӵ�17��ַ��ʼ��д��1���ֽ�
//	W25QXX_Write((u8*)YL_Buf,18,1);		    //�ӵ�18��ַ��ʼ��д��1���ֽ�
//	W25QXX_Write((u8*)CXHG_Buf,19,1);		//�ӵ�19��ַ��ʼ��д��1���ֽ�	
}

/***********************************************************************
 ������      ��Read_Ang  
 ��������    ����ȡflash�������λ���趨�Ƕ�ֵ
 ����        ���Ƕȣ�u8����
 ���        ��TIM3�Զ���װ��ֵ��u16����                        
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
	
	//����������ݴ�flash�ж�����
	W25QXX_Read((u8*)ZB_Buf,13,1);    //�ӵ�13��ַ��ʼ����ȡ1���ֽ�
	W25QXX_Read((u8*)SQT_Buf,14,1);	  //�ӵ�14��ַ��ʼ����ȡ1���ֽ�
	W25QXX_Read((u8*)XQT_Buf,15,1);	  //�ӵ�15��ַ��ʼ����ȡ1���ֽ�
	W25QXX_Read((u8*)ZF_Buf,16,1);	  //�ӵ�16��ַ��ʼ����ȡ1���ֽ�
	W25QXX_Read((u8*)YF_Buf,17,1);    //�ӵ�17��ַ��ʼ����ȡ1���ֽ�
	W25QXX_Read((u8*)YL_Buf,18,1);	  //�ӵ�18��ַ��ʼ����ȡ1���ֽ�
	W25QXX_Read((u8*)CXHG_Buf,19,1);  //�ӵ�19��ַ��ʼ����ȡ1���ֽ�

	ZB_Lim=ZB_Buf[0];     //֧��  
	SQT_Lim=SQT_Buf[0];   //������
	XQT_Lim=XQT_Buf[0];   //������
	ZF_Lim=ZF_Buf[0];     //��
	YF_Lim=YF_Buf[0];     //�ҷ�
	YL_Lim=YL_Buf[0];     //�����ƶ�����
	CXHG_Time=CXHG_Buf[0];//�����ϴ���ʱ��	
}

/***********************************************************************
 ������      ��Wifi_Send  
 ��������    ��WiFi���ͺ���
 ����        ��Ҫ���͵����ݻ�ָ��
 ���        ����                       
************************************************************************/
void Wifi_Send(u8 *data)
{
	u16 i;
	u8 n;	
	i=strlen((const char*)data);                    //��ȡ���ݳ���	
	if(device_num>0)
	{
		u4_printf("AT+CIPSEND=%d,%d\r\n",0,i);      //����AT+CIPSENDָ��
		delay_ms(4);                         
		memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);	//�������4���ջ�����	
		UART4_RX_LEN=0; 			//�������4״̬��־λ                             
		u4_printf("%s",data);                       //���������ַ�����data
		delay_ms(200);								//��ʱ200ms��оƬ����Ҫ�����ʱ��
		memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);	//�������4���ջ�����	
		UART4_RX_LEN=0;  			//����4״̬����
	}
}

/***********************************************************************
 ������      ��Wifi_ToPC  
 ��������    ��WiFi��PC���ͺ���
 ����        ��Ҫ���͵����ݻ�ָ��
 ���        ����                      
************************************************************************/
void Wifi_ToPC(u8 *data)
{
	u16 i;
	u8 n;	
	if(PC_Ready==1)
	{
		i=strlen((const char*)data);                //��ȡ���ݳ���	
		u4_printf("AT+CIPSEND=%d,%d\r\n",PC,i);     //����AT+CIPSENDָ��
		delay_ms(4);
		memset(UART4_RX_BUF,0,20);	//�������4���ջ�����	
		UART4_RX_LEN=0;             //����4״̬����                
		u4_printf("%s",data);       //���������ַ�����data
		delay_ms(200);				//��ʱ200ms��оƬ����Ҫ�����ʱ��
		memset(UART4_RX_BUF,0,20);	//�������4���ջ�����	
		UART4_RX_LEN=0;				  		//����4״̬����  		
	}
}

/***********************************************************************
 ������      ��WiFi_ToSJ  
 ��������    ��WiFi���ֻ����ͺ���
 ����        ��Ҫ���͵����ݻ�ָ��
 ���        ����
************************************************************************/
void WiFi_ToSJ(u8 *data)
{
	u16 i;
	u8 n;	
	if(SJ_Ready==1)
	{
		i=strlen((const char*)data);             //��ȡ���ݳ���	
		u4_printf("AT+CIPSEND=%d,%d\r\n",SJ,i);  //����AT+CIPSENDָ��
		delay_ms(4);
		memset(UART4_RX_BUF,0,20);	//�������4���ջ�����	
		UART4_RX_LEN=0;           	//����4״̬����                    
		u4_printf("%s",data);       //���������ַ�����data
		delay_ms(200);				//��ʱ200ms��оƬ����Ҫ�����ʱ��
		memset(UART4_RX_BUF,0,20);	//�������4���ջ�����	
		UART4_RX_LEN=0;  						  //����4״̬����
	}
}


/***********************************************************************
 ������      ��WiFi_ToYKQ  
 ��������    ��WiFi��ң�������ͺ���
 ����        ��Ҫ���͵����ݻ�ָ��
 ���        ����
************************************************************************/
void WiFi_ToYKQ(u8 *data)
{
	u16 i;
	u8 n;	
	if(YKQ_Ready==1)
	{
		i=strlen((const char*)data);                 //��ȡ���ݳ���	
		u4_printf("AT+CIPSEND=%d,%d\r\n",YKQ,i);     //����AT+CIPSENDָ��
		delay_ms(4);
		memset(UART4_RX_BUF,0,20);	//�������4���ջ�����	
		UART4_RX_LEN=0;             //����4״̬����                  
		u4_printf("%s",data);       //���������ַ�����data
		delay_ms(200);				//��ʱ200ms��оƬ����Ҫ�����ʱ��
		memset(UART4_RX_BUF,0,20);	//�������4���ջ�����	
		UART4_RX_LEN=0;							//����4״̬���� 		
	}
}
/***********************************************************************
 ������      ��WiFi_ToHL  
 ��������    ��WiFi�������ͺ���
 ����        ��Ҫ���͵����ݻ�ָ��
 ���        ����
************************************************************************/
void WiFi_ToHL(u8 *data)
{
	u16 i;
	u8 n;	
	if(HL_Ready==1)
	{
		i=strlen((const char*)data);                //��ȡ���ݳ���	
		u4_printf("AT+CIPSEND=%d,%d\r\n",HL,i);     //����AT+CIPSENDָ��
		delay_ms(4);
		memset(UART4_RX_BUF,0,20);	 //�������4���ջ�����	
		UART4_RX_LEN=0;             //����4״̬����                  
		u4_printf("%s",data);        //���������ַ�����data
		delay_ms(200);				 //��ʱ200ms��оƬ����Ҫ�����ʱ��
		memset(UART4_RX_BUF,0,20);	 //�������4���ջ�����	
		UART4_RX_LEN=0; 		        //����4״̬����
	}
}

/***********************************************************************
 ������      ��WiFi_ToPC  
 ��������    ��������PC�����ͺ���
 ����        ��Ҫ���͵����ݻ�ָ��
 ���        ����
************************************************************************/
void WiFi_ToPC(u8 *data)
{
	if(PCB_Ready==1)
	{                             
		u2_printf("%s",data);	
		memset(USART2_RX_BUF,0,20);//�������2���ջ�����
		USART2_RX_LEN=0; 					//����2���ձ�־����
	}
}

/***********************************************************************
 ������      ��Fun_ZB(void)   
 ��������    ��ִ��֧������
 ����        ����
 ���        ����                           
************************************************************************/
void Fun_ZB(void)
{
	u8 direct,len;
	u16 arr_now;         //��ǰһ������������	
	//ʵ����λ��ʵʱ��ʾ������ǰ�˶�״̬
	static u8 k;         //����k�Ŷ���
	static u8 kj;
	u8 j=0;	
	u16 arr_send;        //��ǰһ����������ֵ
	static u8 zbjx_flag; //֧�����е�����λ����1�����ͼ���λ��ͼƬ	
	
	//�������ܣ�ֻ�������ҷ����ܸ�λ�󣬲��ܽ���֧��
	if((ZF_Flag==0)&&(YF_Flag==0))
	{	
		//�жϽ����ַ���
		if((strstr((const char *)USART2_RX_BUF,(const char *)"ZBS"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"ZBS")))
		{
			if(Ang_To_Arr_ZB(ZB_Lim)>ZB_Runed)  //����ʱ���Ƚ�ֵΪ���м���װ��ֵ��У׼��ĵ���װ��ֵ�Ĳ�ֵ��������ֵ����Ϊ0
			{				
				direct=1;					//�������з����־
				ZB_Dir_flag=1; 		//�������з����־     
				if(ZB_Flag==0)
				{
					ZB_Flag=1;			//����֧��״̬��־λ
					W25QXX_Write((u8*)&ZB_Flag,35,1);	//��״̬��־λд��flash
					delay_ms(200);
					u2_printf("ZB_flag==1");
					delay_ms(200);
					u2_printf("ZBKS");
					delay_ms(200);
					u2_printf("CT_ZB1");
				}
				MotorStart(1,1,0,0);                              //֧������
				u2_printf("*%s*M1*Z*/*/**",RX_BUF);								//����2����
				TIM10_Init(Ang_To_Arr_ZB(ZB_Lim)-ZB_Runed,65000);    //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
			}				
		}
		//�жϽ����ַ���
		if((strstr((const char *)USART2_RX_BUF,(const char *)"ZBX"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"ZBX")))
		{
			if(ZB_Runed>0)    //����ʱ���Ƚ�ֵΪУ׼��ĵ���װ��ֵ��0,�Ҳ���Ϊ0
			{
				direct=0;				//�������з����־
				ZB_Dir_flag=0;  //�������з����־
				if(1==zbjx_flag)
				{
					zbjx_flag=0;	//���ü���״̬��־λ
					delay_ms(200);
					u2_printf("CT_ZB20");
					delay_ms(200);
				}
				MotorStart(1,0,0,0);       //֧������
				u2_printf("*%s*M1*F*/*/**",RX_BUF);			//����2����
				TIM10_Init(ZB_Runed,65000);    //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
			}
		}
		
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//��մ���2��������
		memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//��մ���4��������
		USART2_RX_LEN=0;															//����2״̬����
		UART4_RX_LEN=0;																//����4״̬����
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ		
	 	if(((ZB_Runed<Ang_To_Arr_ZB(ZB_Lim))&&(1==direct))||((0<ZB_Runed)&&(0==direct)))
		{					
			while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))  //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��   
			{														
				//ָֹͣ��
				if(USART2_RX_LEN&0x8000)
				{
					len=USART2_RX_LEN&0x3fff;		//��ȡ����2���������ַ�����		
					USART2_RX_BUF[len]=0;			//����2����ĩβ��"0"
					if((strstr((const char *)USART2_RX_BUF,(const char *)"STOP"))||(strstr((const char *)USART2_RX_BUF,(const char *)"ZBS"))||(strstr((const char *)USART2_RX_BUF,(const char *)"ZBX")))    //�����յ�Stop,������ѭ��	
					{					
//						memcpy(RX_BUF,USART2_RX_BUF,15);
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//�������2��������
						USART2_RX_LEN=0;				//����2״̬����
						break;						
					}
					else 
					{
						u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���	
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//�������2��������		
						USART2_RX_LEN=0;				//����2״̬����
					}						
				}
				if(UART4_RX_LEN&0x8000)
				{
					len=UART4_RX_LEN&0x3fff;		//��ȡ����4���������ַ�����			
					UART4_RX_BUF[len]=0;			//����4����ĩβ��0��
					if((strstr((const char *)UART4_RX_BUF,(const char *)"STOP"))||(strstr((const char *)UART4_RX_BUF,(const char *)"ZBS"))||(strstr((const char *)UART4_RX_BUF,(const char *)"ZBX")))    //�����յ�Stop,������ѭ��	
					{					
//						memcpy(RX_BUF,UART4_RX_BUF,15);
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);	//�������4��������			
						UART4_RX_LEN=0;															//����4״̬����
						break;
					}
					if(strstr((const char *)UART4_RX_BUF,(const char *)"SEND OK"))
					{	}
					else 
					{
						u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���	
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);	//�������4��������			
						UART4_RX_LEN=0;				  //����4״̬����
					}						
				}		
				//����ͼƬָ��
				 arr_send=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//��ȡ��ǰ�Ĵ�������װ��ֵ
				if(direct==1)
				{
					j=(ZB_Runed+arr_send)/(Ang_To_Arr_ZB(ZB_Lim)/19);		//ͼƬ��ż���
				}
				else
				{
					j=abs(ZB_Runed,arr_send)/(Ang_To_Arr_ZB(ZB_Lim)/19);	//ͼƬ��ż���
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
							u2_printf("CT_ZB%d",ZB_Pic);		//����2���Ͷ���ͼƬָ��
						}							
					}				
				}
			}
			//���ֹͣ
			MotorStop(1);    u2_printf("*%s*M1*T*/*/**",RX_BUF);  //����2����			
			TIM10_Stop();      //�رն�ʱ��
			//�жϸ�λ
			if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))&&(direct==0))   //�ж��Ƿ��ڸ�λ״̬����λ״̬��ǰ�������еĶ�ʱ������
			{				
				arr_now=0;         //��ʱ���ڸ�λ״̬����״ֵ̬����Ϊ0��
				ZB_Flag=0;				 //���λ����
				W25QXX_Write((u8*)&ZB_Flag,35,1);		//����־λд��flash
				delay_ms(200);
				u2_printf("ZB_flag==0");
			}		
			else
			{
				arr_now=__HAL_TIM_GET_COUNTER(&TIM10_Handler);    //��ȡ��ǰ����ֵarr_now				
				ZB_Flag=1;
			}
		  //ͨ���������ж������ۼ�		
			if(	direct==1)        //�����֧�����У�����+
			{
				if(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))
				{  
					ZB_Runed=Ang_To_Arr_ZB(ZB_Lim);		//��������������ֵΪ����ֵ
					zbjx_flag=1; 				//���ü���״̬��־λ
					delay_ms(200);
					u2_printf("CT_ZB20");
					delay_ms(200);
					u2_printf("ZBJX");
				}
				else
				{  ZB_Runed+=arr_now;	}		//��������������ֵ=��һ����������ֵ+�˴���������ֵ
			}
			else                //�����֧�����У�����-
			{
				if(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))
				{	
					ZB_Runed=0;			//��������������ֵΪ0
					delay_ms(200);
					u2_printf("CT_ZB1");
					delay_ms(200);
					u2_printf("ZBFW");
					delay_ms(200);
				}
				else
				{
					ZB_Runed-=arr_now;	//��������������ֵ=��һ����������ֵ-�˴���������ֵ
				}						
			}		
			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ
		}
	}
	else
	{
		LedAlm(100,"ZBGS");
	}	
}
/***********************************************************************
 ������      ��Fun_SQT(void)   
 ��������    ��ִ�������Ȳ���
 ����        ����
 ���        ����                           
************************************************************************/
void Fun_SQT(void)
{
	u16 arr_now;              //��ǰһ������������
	u8 len;                   //WiFi���ڽ����ַ�������
	u8 direct;	              //���з����־λ
	//ʵ����λ��ʵʱ��ʾ������ǰ�˶�״̬
	static u8 k=0;            //�����k�Ŷ���ָ��
	static u8 kj;
	u8 j=0;	
	u16 arr_send;               //��ǰһ����������ֵ
	static u8 sqtjx_flag;//���������е�����λ����1�����ͼ���λ��ͼƬ	
	
	//�������ܣ�ֻ�������ҷ����ܸ�λ�������ȸ�λ����ܽ���������
	if((ZF_Flag==0)&&(YF_Flag==0)&&(XQT_Flag==0))
	{	//�жϽ����ַ���	
		if((strstr((const char *)USART2_RX_BUF,(const char *)"SQTS"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"SQTS")))//����������	
		{				   
			if(Ang_To_Arr_SXQT(SQT_Lim)>SQT_Runed)             //����ʱ���Ƚ�ֵΪ���м���װ��ֵ��У׼��ĵ���װ��ֵ�Ĳ�ֵ��������ֵ����Ϊ0
			{
				direct=1; 													//�������з����־
				if(SQT_Flag==0)
				{
					SQT_Flag=1;												//����״̬��־λ
					W25QXX_Write((u8*)&SQT_Flag,36,1);//��״̬��־λд��flash
					delay_ms(200);					
					u2_printf("SQT_flag==1");
					delay_ms(200);
					u2_printf("SQTKS");
					delay_ms(200);
					u2_printf("CT_SQT1");
				}											
				MotorStart(2,0,0,0);		//�����Ƹ�����
				u2_printf("*%s*M2*Z*/*/**",RX_BUF);	//����2����	
				TIM10_Init(Ang_To_Arr_SXQT(SQT_Lim)-SQT_Runed,65000);     //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz					
			} 
		}
		if((strstr((const char *)USART2_RX_BUF,(const char *)"SQTX"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"SQTX")))//����������
		{			
			if(SQT_Runed>0)                          //����ʱ���Ƚ�ֵΪУ׼��ĵ���װ��ֵ��0,�Ҳ���Ϊ0
			{
				direct=0;				//�������з����־
				if(sqtjx_flag==1)
				{
					sqtjx_flag=0;	//���ü��ޱ�־λ
					delay_ms(200);
					u2_printf("CT_SQT8");
				}
				MotorStart(2,1,0,0);				//�����Ƹ�����
				u2_printf("*%s*M2*F*/*/**",RX_BUF);//����2����	
				TIM10_Init(SQT_Runed,65000);     //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz				
			}
		}		
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//��մ���2��������
		memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//��մ���4��������
		USART2_RX_LEN=0;															//����2״̬����
		UART4_RX_LEN=0;															  //����4״̬����
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);  //����жϱ�־λ
	 	if(((SQT_Runed!=Ang_To_Arr_SXQT(SQT_Lim))&&(1==direct))||((0!=SQT_Runed)&&(0==direct)))
		{
			while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) )
			{	
				//ָֹͣ��
				if(USART2_RX_LEN&0x8000)
				{
					len=USART2_RX_LEN&0x3fff;	//��ȡ����2���������ַ�����		
					USART2_RX_BUF[len]=0;			//����2����ĩβ��"0"
					if((strstr((const char *)USART2_RX_BUF,(const char *)"STOP"))||(strstr((const char *)USART2_RX_BUF,(const char *)"SQTS"))||(strstr((const char *)USART2_RX_BUF,(const char *)"SQTX")))    //�����յ�Stop,������ѭ��	
					{
//						memcpy(RX_BUF,USART2_RX_BUF,15);
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//��մ���2��������
						USART2_RX_LEN=0;				//����2״̬����
						break;
					}						
					else
					{
						u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���							
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);		//��մ���2��������		
						USART2_RX_LEN=0;				//����2״̬����
					}						
				}
				if(UART4_RX_LEN&0x8000)
				{
					len=UART4_RX_LEN&0x3fff;		//��ȡ����4���������ַ�����			
					UART4_RX_BUF[len]=0;			//����4״̬����
					if((strstr((const char *)UART4_RX_BUF,(const char *)"STOP"))||(strstr((const char *)UART4_RX_BUF,(const char *)"SQTS"))||(strstr((const char *)UART4_RX_BUF,(const char *)"SQTX")))    //�����յ�Stop,������ѭ��	
					{
//						memcpy(RX_BUF,UART4_RX_BUF,15);
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);	//�������4��������		
						UART4_RX_LEN=0;				//����4״̬����
						break;
					}
					if(strstr((const char *)UART4_RX_BUF,(const char *)"SEND OK"))
					{	}
					else
					{
						u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���							
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);	//�������4��������		
						UART4_RX_LEN=0;					//����4״̬����
					}						
				}
				 arr_send=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//��ȡ��ǰ�Ĵ�������װ��ֵ
				//�жϴ��䶯��ָ��
				if(direct==1)
				{
					j=(SQT_Runed+arr_send)/(Ang_To_Arr_SXQT(SQT_Lim)/7);	//ͼƬ��ż���
				}
				else
				{
					j=abs(SQT_Runed,arr_send)/(Ang_To_Arr_SXQT(SQT_Lim)/7);//ͼƬ��ż���
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
							u2_printf("CT_SQT%d",SQT_Pic);	//����2���Ͷ���ͼƬָ��
						}
					}					
				}
			}				    //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��
			MotorStop(2);       //�Ƹ�ֹͣ
			u2_printf("*%s*M2*T*/*/**",RX_BUF);//����2����	
			TIM10_Stop();       //�رն�ʱ��
			//�жϸ�λ
			if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))&&(direct==0)) //�ж��Ƿ��ڸ�λ״̬����λ״̬��ǰ�������еĶ�ʱ������
			{
				arr_now=0;     		//��ʱ���ڸ�λ״̬����״ֵ̬����Ϊ0��
				SQT_Flag=0;					//����״̬��־λ
				W25QXX_Write((u8*)&SQT_Flag,36,1);//��״̬��־λд��flash
				delay_ms(200);
				u2_printf("SQT_flag==0");
			}
			else
			{
				arr_now=__HAL_TIM_GET_COUNTER(&TIM10_Handler); 		//��ȡ��ǰ�Ĵ�������װ��ֵ      
				SQT_Flag=1;			//����״̬��־λ
			}			
			 //ͨ���������ж������ۼ�	
			if(direct==1)    //��������������У�����+
			{
				if(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))
				{
					SQT_Runed=Ang_To_Arr_SXQT(SQT_Lim);		//��������������ֵΪ����ֵ
					sqtjx_flag=1;					//���ü��ޱ�־λ
					delay_ms(200);
					u2_printf("CT_SQT8");
					delay_ms(200);
					u2_printf("SQTJX");
				}
				 else
				{
					SQT_Runed=SQT_Runed+arr_now;			//��������������ֵ=��һ����������ֵ+�˴���������ֵ
				}	
			}
			else     //��������������У�����-
			{
				if(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))
				{
					SQT_Runed=0;		//��������������ֵ=0
					delay_ms(200);
					u2_printf("CT_SQT1");
					delay_ms(200);
					u2_printf("SQTFW");
				}
				 else
				{
					SQT_Runed=SQT_Runed-arr_now;	//��������������ֵ=��һ����������ֵ-�˴���������ֵ
				}			
			}	
			 __HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //����жϱ�־λ	 		
		 }
	}	
	else
	{
		LedAlm(100,"SQTGS");
	}
}

/***********************************************************************
 ������      ��Fun_XQT(void)   
 ��������    ��ִ�������Ȳ���
 ����        ����
 ���        ����                           
************************************************************************/
void Fun_XQT(void)
{
	u16 arr_now;         //��ǰһ������������   
	u8 len;              //���յ��ַ�������
	u8 direct;           //����ĳ���������еķ����־��1-�������У�0-��������	
	static u8 leg_down=0;
	//ʵ����λ��ʵʱ��ʾ������ǰ�˶�״̬
	static u8 k=0;       //���͵�K�Ŷ���ָ��
	static u8 kj=0;
	u8 j=0;	
	u16 arr_send;        //��ǰһ������������
	static u8 xqtjx_flag;//���������е�����λ����1�����ͼ���λ��ͼƬ	
	
	//�������ܣ�ֻ�������ҷ����ܸ�λ�������ȸ�λ����ܽ���������
	if((ZF_Flag==0)&&(YF_Flag==0)&&(SQT_Flag==0))
	{	//�жϽ����ַ���
		if((strstr((const char *)USART2_RX_BUF,(const char *)"XQTX"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"XQTX")))   //����������
		{				
			if(Ang_To_Arr_SXQT(XQT_Lim)>XQT_Runed)             //����ʱ���Ƚ�ֵΪ���м���װ��ֵ��У׼��ĵ���װ��ֵ�Ĳ�ֵ��������ֵ����Ϊ0
			{
				direct=1;		//�������з����־
				leg_down=1;	//����״̬��־λ
				if(XQT_Flag==0)	//����״̬��־λ
				{
					XQT_Flag=1;	//����״̬��־λ
					W25QXX_Write((u8*)&XQT_Flag,37,1);		//��״̬��־λд��flash
					u2_printf("XQT_flag==1");
					delay_ms(200);
					u2_printf("XQTKS");
					delay_ms(200);
					u2_printf("CT_XQT1");
					delay_ms(200);
				}							
				MotorStart(2,1,0,0);					//�����Ƹ�����
				u2_printf("*%s*M2*Z*/*/**",RX_BUF);//����2����
				TIM10_Init(Ang_To_Arr_SXQT(XQT_Lim)-XQT_Runed,65000);     //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz				
				XQT_Flag=1;		//����״̬��־λ
			}	
		}
		if((strstr((const char *)USART2_RX_BUF,(const char *)"XQTS"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"XQTS")))//����������
		{
			
			if(XQT_Runed>0)     //����ʱ���Ƚ�ֵΪ���м���װ��ֵ��У׼��ĵ���װ��ֵ�Ĳ�ֵ��������ֵ����Ϊ0
			{
				direct=0;			//�������з����־
				if(xqtjx_flag==1)
				{
					xqtjx_flag=0;	//���ü���״̬��־λ
					u2_printf("CT_XQT20");
					delay_ms(200);
				}
				MotorStart(2,0,0,0);		//�����Ƹ�����
				u2_printf("*%s*M2*F*/*/**",RX_BUF);//����2����
				TIM10_Init(XQT_Runed*1.1,65000);    //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz			
			}
		}
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);		//��մ���2��������			
		memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//��մ���4��������
		USART2_RX_LEN=0;			//����2״̬����
		UART4_RX_LEN=0;				  //����4״̬����
		
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);    //����жϱ�־λ	

	   if(((XQT_Runed!=Ang_To_Arr_SXQT(XQT_Lim))&&(1==direct))||((0!=XQT_Runed)&&(0==direct)))
	   {			
			while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) )
			{									
				//ָֹͣ��
				if(USART2_RX_LEN&0x8000)
				{
					len=USART2_RX_LEN&0x3fff;	//��ȡ����2���������ַ�����		
					USART2_RX_BUF[len]=0;	//����2����ĩβ��"0"
					if((strstr((const char *)USART2_RX_BUF,(const char *)"STOP"))||(strstr((const char *)USART2_RX_BUF,(const char *)"XQTX"))||(strstr((const char *)USART2_RX_BUF,(const char *)"XQTS")))    //�����յ�Stop,������ѭ��	
					{				
//						memcpy(RX_BUF,USART2_RX_BUF,15);
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			//��մ���2��������
						USART2_RX_LEN=0;			//����2״̬����
						break;
					}
					else
					{
						u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);		//��մ���2��������	
						USART2_RX_LEN=0;			//����2״̬����
					}					
				}
				if(UART4_RX_LEN&0x8000)
				{
					len=UART4_RX_LEN&0x3fff;			//��ȡ����4���������ַ�����		
					UART4_RX_BUF[len]=0;				//����4����ĩβ��"0"
					if((strstr((const char *)UART4_RX_BUF,(const char *)"STOP"))||(strstr((const char *)UART4_RX_BUF,(const char *)"XQTX"))||(strstr((const char *)UART4_RX_BUF,(const char *)"XQTS")))    //�����յ�Stop,������ѭ��	
					{				
//						memcpy(RX_BUF,UART4_RX_BUF,15);
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);					//��մ���4��������
						UART4_RX_LEN=0;				  //����4״̬����
						break;
					}
					if(strstr((const char *)UART4_RX_BUF,(const char *)"SEND OK"))
					{	}
					else
					{
						u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);				//��մ���4��������	
						UART4_RX_LEN=0;				  //����4״̬����
					}					
				}
				 arr_send=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//��ȡ��ǰ�Ĵ�������װ��ֵ
				//���Ͷ���ָ��
				if(direct==1)
				{
					j=(XQT_Runed+arr_send)/(Ang_To_Arr_SXQT(XQT_Lim)/19);		//ͼƬ��ż���
				}
				else
				{
					j=abs(XQT_Runed,arr_send)/(Ang_To_Arr_SXQT(XQT_Lim)/19);		//ͼƬ��ż���
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
							u2_printf("CT_XQT%d",XQT_Pic);		//����2���Ͷ���ͼƬָ��
						}
					}				
				}
			}				   //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��	
			MotorStop(2);      //�Ƹ�ֹͣ
			u2_printf("*%s*M2*T*/*/**",RX_BUF);//����2����
			TIM10_Stop();      //�رն�ʱ��
			//�жϸ�λ
			if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))&&(direct==0))
			{
				arr_now=0;    		//��ʱ���ڸ�λ״̬����״ֵ̬����Ϊ0��
				XQT_Flag=0;		//����״̬��־λ
				W25QXX_Write((u8*)&XQT_Flag,37,1);		//��״̬��־λд��flash
				delay_ms(200);			
				u2_printf("XQT_flag==0");
			}
			else
			{			
				arr_now=__HAL_TIM_GET_COUNTER(&TIM10_Handler);    		//��ȡ��ǰ�Ĵ�������װ��ֵ 
				XQT_Flag=1;		//����״̬��־λ
			}			
			//ͨ���������ж������ۼ�
			if(direct==1)    //��������������У�����+
			{
				if(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))
				{
					XQT_Runed=Ang_To_Arr_SXQT(XQT_Lim);				//��������������ֵΪ����ֵ
					xqtjx_flag=1;	   	//���ü���״̬��־λ
					delay_ms(200);
					u2_printf("CT_XQT20");
					delay_ms(200);
					u2_printf("XQTJX");
				}
				 else
				{
					XQT_Runed=XQT_Runed+arr_now;		//��������������ֵ=��һ����������ֵ+�˴���������ֵ
				}	
			}
			else		//��������������У�����-
			{
				if(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))
				{
					XQT_Runed=0;	//����������ֵ��Ϊ0
					delay_ms(200);
					u2_printf("CT_XQT1");
					delay_ms(200);
					u2_printf("XQTFW");
				}
				 else
				{
					XQT_Runed=XQT_Runed-arr_now;	//��������������ֵ=��һ����������ֵ-�˴���������ֵ
				}			
			}
			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ	 					
		}
//	    if((0==XQT_Runed)&&(1==leg_down))
//	   {
//			leg_down=0;
//		    MotorStart(2,0,0,0);          //�����ȼ���������
//			TIM10_Init(3000,65000);    //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
//			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ
//		    while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)));  //�ȴ���ʱʱ�䵽
//		    MotorStop(2); 
//			TIM10_Stop();      //�رն�ʱ��
//		    __HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ		   
//	   }
	}
	else
	{
		LedAlm(100,"XQTGS");
	}
}

/***********************************************************************
 ������      ��Fun_ZF(void)  
 ��������    ��ִ���������
 ����        ����
 ���        ����                           
************************************************************************/
void Fun_ZF(void)
{
	u8 direct,key;
	u16 arr_now;                 //��ǰһ������������,���������ۼ�
	u8 len;                      //���յ��ַ�������
	static u8 motor5_run_flag;   //�ж�С�෭�Ƿ��Ѿ���������������λ��1 
	
	//ʵ����λ��ʵʱ��ʾ������ǰ�˶�״̬
	static u8 k=0,m=0;
	u8 j=0,n=0;
	u16 arr_send,arr_send1;     //��ǰһ������������
	static u8 kj,mn;
	static u8 M345_Start;       //345�����һ������
	static u8 M345_End;         //345������е��ϼ���λ��
	
	//�������ܣ�ֻ����֧�����������ȡ����㡢���Ӹ�λ�󣬲���ִ��������
	if((ZB_Flag==0)&&(YF_Flag==0)&&(SQT_Flag==0)&&(XQT_Flag==0)&&(ZBQ_Flag==0)&&(YL_Flag==0)&&(ZBH_Flag==0)&&(ZYH_Flag==0))
	{			
		//С�෭����
		if(ZF_Flag==0)   //�����λ����ʼ״̬����ִ������
		{ //�жϽ����ַ���
			if((strstr((const char *)USART2_RX_BUF,(const char *)"ZFS"))||(strstr((const char *)UART4_RX_BUF,(const char *)"ZFS")))
			{
				memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);//��մ���2��������
				memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//��մ���4��������
				USART2_RX_LEN=0;			//����2״̬����
				UART4_RX_LEN=0;				  //����4״̬����
				//5�Ų෭��			
				ZF_Flag=1;		//����״̬��־λ
				motor5_run_flag=1;		//����״̬��־λ
				W25QXX_Write((u8*)&ZF_Flag,33,1); 		//��״̬��־λд��flash
				delay_ms(200);
				u2_printf("ZF_flag==1");
				delay_ms(200);
				u2_printf("ZFKS");
				delay_ms(200);
				u2_printf("CT_ZCF1");
				MotorStart(5,1,1400-1,25-1);	 			 //5�ŵ������
				u2_printf("*%s*M5*Z*0*/**",RX_BUF);//����2����
				memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);//��մ���2��������
				memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//��մ���4��������
				USART2_RX_LEN=0;			//����2״̬����
				UART4_RX_LEN=0;				  //����4״̬����
				TIM10_Init(Ang_To_Arr_ZYFS(ZF_Lim),65000);           //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz			
				__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);  //����жϱ�־λ
				while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)) )
				{						
					//�����λ						
					if((0==GD5_ZFZZ)&&(1==ZF_Flag))        //������翪������ѭ�������ͣת 
					{						
						delay_us(100);
						if(0==GD5_ZFZZ)
						{
							u2_printf("GD5ZFZZ");
							break;	
						}								
					}
					  //�ж���û���յ���λ��ָ��		
					if(USART2_RX_LEN&0x8000)
					{				
						u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���	
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			//��մ���2��������
						USART2_RX_LEN=0;				//����2״̬����										
					}
					if(UART4_RX_LEN&0x8000)
					{				
						u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���	
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//��մ���4��������			
						UART4_RX_LEN=0;				  //����4״̬����										
					}
					//������ϡ��������
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
					//���Ͷ���ָ��
				    arr_send1=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//��ȡ��ǰ�Ĵ�������װ��ֵ
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
								u2_printf("CT_ZCF%d",ZCF_Pic);		//����2���Ͷ���ͼƬָ��
							}
						}
					}
				}
				MotorStop(5);              //���5ֹͣ
				u2_printf("*%s*M5*T*0*/**",RX_BUF);//����2����
				TIM10_Stop();              //��ʱ���ر�
				__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ
				delay_ms(200);
				u2_printf("CT_ZCF10");
				Motor4_BC(0,1400,1400-1,25-1);	//���ò�������
			}
		}	
		//����345�ŵ������	
		if((strstr((const char *)USART2_RX_BUF,(const char *)"ZFS"))||(strstr((const char *)UART4_RX_BUF,(const char *)"ZFS"))||(1==motor5_run_flag))
		{				
			if(Ang_To_Arr_ZYFS(ZF_Lim)>ZF_Runed)
			{			     			 
				//345��������			
				 direct=1;			//�������з����־
				 ZF_Dir_flag=1;		//���÷���״̬��־λ
				 if(M345_Start==0)
				 {
					 M345_Start=1;
					 delay_ms(100);
					 u2_printf("CT_ZF1");
				 }
				 MotorStart(3,0,1400-1,25-1);     //3�ŵ������
				 MotorStart(4,0,(1400-1)*1.2,25-1);		 //4�ŵ������
				 MotorStart(5,0,1400-1,25-1);			 //5�ŵ������
				 if(1==motor5_run_flag)
				 {
					 motor5_run_flag=0;			//����״̬��־λ
					 u2_printf("*M5JS*M345*ZZZ*000*/**");
				 }
				 else
				 {
					u2_printf("*%s*M345*ZZZ*000*/**",RX_BUF);//����2����
				 }
				 TIM10_Init(Ang_To_Arr_ZYFS(ZF_Lim)-ZF_Runed,65000);	//�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
			}
		}		
		if((strstr((const char *)USART2_RX_BUF,(const char *)"ZFX"))||(strstr((const char *)UART4_RX_BUF,(const char *)"ZFX")))
		{					
			if(ZF_Runed>0)
			{			   
				//345��������	
			     direct=0;			//�������з����־
				 ZF_Dir_flag=0;		//���÷���״̬��־λ
				 if(M345_End==1)
				 {
					 M345_End=0;
					 delay_ms(200);
					 u2_printf("CT_ZF8");	
					 delay_ms(200);
				 }
				 MotorStart(3,1,1400-1,25-1);			     //3�ŵ������
				 MotorStart(4,1,(1400-1)*1.2,25-1);		 //4�ŵ������
				 MotorStart(5,1,1400-1,25-1);			 //5�ŵ������
				 u2_printf("*%s*M345*FFF*000*/**",RX_BUF);//����2����
			     TIM10_Init(ZF_Runed,65000);			          //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz
			}
		}
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//��մ���2��������		
		USART2_RX_LEN=0;			//����2״̬����
		memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//��մ���4��������			
		UART4_RX_LEN=0;				  //����4״̬����
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);             // ����жϱ�־λ
		if(((ZF_Runed!=Ang_To_Arr_ZYFS(ZF_Lim))&&(1==direct))||((0!=ZF_Runed)&&(0==direct)))
		{
			while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))  //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��
			{			
				//�����λ													
				if(((0==GD3_CS)||(0==GD4_CS))&&(0==direct))   //���������翪�أ�����ѭ����ֹͣ����
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
				if(((0==GD3_ZFZZ)||(0==GD4_ZFZZ))&&(1==direct))   //���������翪�أ�����ѭ����ֹͣ����
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
				//ָֹͣ��
				if(USART2_RX_LEN&0x8000)
				{
					len=USART2_RX_LEN&0x3fff;	//��ȡ����2���������ַ�����				
					USART2_RX_BUF[len]=0;			//����2����ĩβ��"0"
					if((strstr((const char *)USART2_RX_BUF,(const char *)"STOP"))||(strstr((const char *)USART2_RX_BUF,(const char *)"ZFS"))||(strstr((const char *)USART2_RX_BUF,(const char *)"ZFX")))    //�����յ�Stop,������ѭ��	
					{
//						memcpy(RX_BUF,USART2_RX_BUF,15);
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			//��մ���2��������
						USART2_RX_LEN=0;			//����2״̬����
						break;
					} 
					else 
					{
						u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���								
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);		//��մ���2��������	
						USART2_RX_LEN=0;			//����2״̬����
					}						
				}
				if(UART4_RX_LEN&0x8000)
				{
					len=UART4_RX_LEN&0x3fff;		//��ȡ����4���������ַ�����				
					UART4_RX_BUF[len]=0;				//����4����ĩβ��"0"
					if((strstr((const char *)UART4_RX_BUF,(const char *)"STOP"))||(strstr((const char *)UART4_RX_BUF,(const char *)"ZFS"))||(strstr((const char *)UART4_RX_BUF,(const char *)"ZFX")))    //�����յ�Stop,������ѭ��	
					{
//						memcpy(RX_BUF,UART4_RX_BUF,15);
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//��մ���4��������			
						UART4_RX_LEN=0;				  //����4״̬����
						break;
					} 
					if(strstr((const char *)UART4_RX_BUF,(const char *)"SEND OK"))
					{	}
					else 
					{
						u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���								
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//��մ���4��������			
						UART4_RX_LEN=0;				  //����4״̬����
					}						
				}
				//������ϡ��������
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
				//���Ͷ���ָ��
				 arr_send=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//��ȡ��ǰ�Ĵ�������װ��ֵ
				if(direct==1)
				{
					j=(ZF_Runed+arr_send)/(Ang_To_Arr_ZYFS(ZF_Lim)/7);		//ͼƬ��ż���
				}
				else
				{
					j=abs(ZF_Runed,arr_send)/(Ang_To_Arr_ZYFS(ZF_Lim)/7);		//ͼƬ��ż���
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
							u2_printf("CT_ZF%d",ZF_Pic);		//����2���Ͷ���ͼƬָ��
						}
					}				
				}
			}
			MotorStop(3);  		
			MotorStop(4);  		
			MotorStop(5);  
			u2_printf("*%s*M345*TTT*000*/**",RX_BUF);		//����2����	
			TIM10_Stop();          //�رն�ʱ��
			//�жϸ�λ
			if(((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))||(0==GD3_CS)||(0==GD4_CS))&&(direct==0))
			{
				arr_now=0;	 //��ʱ���ڸ�λ״̬����״ֵ̬����Ϊ0��
				ZF_Flag=0;		//����״̬��־λ
			}		
			else
			{					
				arr_now=__HAL_TIM_GET_COUNTER(&TIM10_Handler);    //��ȡ��ǰ����ֵarr_now														
			}
			//ͨ���������ж������ۼ�
			if(direct==1)           //���У�����+
			{
				if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))||(0==GD3_ZFZZ)||(0==GD4_ZFZZ))
				{
					ZF_Runed=Ang_To_Arr_ZYFS(ZF_Lim);				//��������������ֵΪ����ֵ
					M345_End=1;  					
					delay_ms(200);
					u2_printf("CT_ZF8");
					delay_ms(200);
					u2_printf("ZFJX");
				}
				else
				{
					ZF_Runed=ZF_Runed+arr_now;		//��������������ֵ=��һ����������ֵ+�˴���������ֵ
				}		
			}	
			else     //���У�����-
			{
				if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))||(0==GD3_CS)||(0==GD4_CS))
				{
					ZF_Runed=0;		//����������ֵ��Ϊ0
					M345_Start=0;  					
					delay_ms(200);
					u2_printf("CT_ZF1");
				}
				else
				{
					ZF_Runed=ZF_Runed-arr_now;			//��������������ֵ=��һ����������ֵ-�˴���������ֵ			
				}
			}					
			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);    //����жϱ�־λ
			
			//����ʱʱ�䵽���ǹ��û��������������һ�ξ��룬�����翪��λ�ã���翪�ذ�װ��򿪴˶Σ��������������ж�ɾ����
//			if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))&&((1==GD3_CS)||(1==GD4_CS))&&(direct==0))
//			{   			
//				if((1==GD3_CS)&&(0==GD4_CS))   //���3û��λ
//				{
//					u2_printf("\r\n3�ŵ���������е����λ��\r\n");
//					MotorStart(3,1,1400-1,25-1);			     //3�ŵ������
//					u2_printf("*%s*M3*F*0*/**",RX_BUF);	
//					TIM10_Init(add_arr,65000);     //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ	 	
//					while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))
//					{			
//						if(0==GD3_CS)  //����ʱ������翪�أ�����ѭ�� 
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
//					TIM10_Stop();         //�رն�ʱ��
//					if(0==GD3_CS)
//					{
//						u2_printf("*%s*GD3CS*/*0*/**",RX_BUF);
//					}
//					else
//					{
//						u2_printf("*%s*GD3CS*/*1*/**",RX_BUF);
//					}
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ
//				}
//				if((0==GD3_CS)&&(1==GD4_CS))         //���4û��λ
//				{
//					u2_printf("\r\n4�ŵ���������е����λ��\r\n");
//					MotorStart(4,1,1400-1,25-1);		 //4�ŵ������
//					u2_printf("*%s*M4*F*0*/**",RX_BUF);				
//					TIM10_Init(add_arr,65000);      //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ	 	
//					while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))
//					{			
//						if(0==GD4_CS)  //����ʱ������翪�أ�����ѭ�� 
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
//					MotorStop(4);         //���ֹͣ
//					u2_printf("*%s*M4*T*0*/**",RX_BUF);
//					TIM10_Stop();         //�رն�ʱ��
//					if(0==GD4_CS)
//					{
//						u2_printf("*%s*GD4CS*/*0*/**",RX_BUF);
//					}
//					else
//					{
//						u2_printf("*%s*GD4CS*/*1*/**",RX_BUF);
//					}
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ				
//				}
//				if((1==GD3_CS)&&(1==GD4_CS))   //���3/4��û��λ
//				{
//					u2_printf("\r\n3�ż�4�ŵ��ͬʱ�������е����λ��\r\n");
//					MotorStart(3,1,(1400-1),25-1);     //3�ŵ������
//					MotorStart(4,1,(1400-1)*1.2,25-1);		 //4�ŵ������
//					MotorStart(5,1,1400-1,25-1);			 //5�ŵ������
//					u2_printf("*%s*M345*FFF*000*/**",RX_BUF);	
//					TIM10_Init(add_arr,65000);   //�򿪶�ʱ��
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ	 	
//					while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))
//					{			
//						if((0==GD3_CS)||(0==GD4_CS))  //����ʱ������翪�أ�����ѭ�� 
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
//					MotorStop(3);         //���ֹͣ
//					MotorStop(4);
//					MotorStop(5);
//					u2_printf("*%s*M345*TTT*000*/**",RX_BUF);
//					TIM10_Stop();         //�رն�ʱ��
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
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ	
//				}
//			}
			
			//5�ŵ����λ
			if(ZF_Flag==0)     //345������λ����ʼ״̬���Ÿ�λ5�ŵ��
			{			
				memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			//��մ���2��������
				USART2_RX_LEN=0;			//����2״̬����
				memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);				//��մ���4��������	
				UART4_RX_LEN=0;				  //����4״̬����
				//5�Ų෭��λ
//				Motor4_BC(1,1400,1400-1,25-1);
				delay_ms(200);
				u2_printf("CT_ZCF10");
				MotorStart(5,0,1400-1,25-1); 			 //5�ŵ������
				u2_printf("*%s*M5*F*0*/**",RX_BUF);//����2����
				ZF_Runed=0;			//����������ֵ��Ϊ0		
				TIM10_Init(Ang_To_Arr_ZYFS(ZF_Lim),65000);              //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz
				__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ
				while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) )
				{								
					//�����λ
					if(((0==GD5_CS)&&(0==ZF_Flag)) )   //������翪������ѭ�������ͣת 
					{	
						delay_us(20);
						if(0==GD5_CS)
						{
							u2_printf("GD5CS");
							break;						
						}		             
					}
					  //�ж���û���յ���λ��ָ��		
					if(USART2_RX_LEN&0x8000)
					{
						u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���	
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);		//��մ���2��������	
						USART2_RX_LEN=0;				//����2״̬����											
					}
					if(UART4_RX_LEN&0x8000)
					{
						u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���	
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//��մ���4��������		
						UART4_RX_LEN=0;					  //����4״̬����											
					}
					//������ϡ��������
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
					//���Ͷ���ָ��
					arr_send1=__HAL_TIM_GET_COUNTER(&TIM10_Handler);			//��ȡ��ǰ�Ĵ�������װ��ֵ			
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
								u2_printf("CT_ZCF%d",ZCF_Pic);		//����2���Ͷ���ͼƬָ��
							}
						}
					}
				}      
				MotorStop(5);   
				u2_printf("*%s*M5*T*0*/**",RX_BUF);     //���ֹͣ������2����				
				TIM10_Stop();         //�رն�ʱ��
				__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ
				ZF_Flag=0;		//����״̬��־λ
				W25QXX_Write((u8*)&ZF_Flag,33,1);		//��״̬��־λд��flash
				delay_ms(200);
				u2_printf("CT_ZCF1");
				delay_ms(200);
				u2_printf("ZF_flag==0");
				delay_ms(200);
				u2_printf("ZFFW");
				//����ʱʱ�䵽���ǹ��û��������������һ�ξ��룬�����翪��λ�ã���翪�ذ�װ��򿪴˶Σ��������������ж�ɾ����
//				if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))&&(1==GD5_CS)&&(direct==0)&&(0==ZF_Flag))
//				{
//					MotorStart(5,0,1400-1,25-1);			 //5�ŵ������
//					u2_printf("*%s*M5*F*0*/**",RX_BUF); 
//					TIM10_Init(add_arr,65000);        //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ	 	
//					while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))
//					{			
//						if(0==GD5_CS)  //����ʱ������翪�أ�����ѭ�� 
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
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ	
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
 ������      ��Fun_YF(void)  
 ��������    ��ִ���ҷ������
 ����        ����
 ���        ����                           
************************************************************************/
void Fun_YF(void)
{
	u8 direct,key;
	u16 arr_now;        //��ǰһ�����������������������ۼ�
	u8 len;             //���յ��ַ�������	
	static u8 motor5_run_flag;  //С�෭�����б�־λ	
	
	//ʵ����λ��ʵʱ��ʾ������ǰ�˶�״̬ 
	static u16 k=0,m=0;
	static u8 M345R_Start=0;  //345����ӳ�ʼλ������
	static u8 M345R_End=0;    //345��������ϼ���λ��
	u8 mn,kj;
	u16 j=0,n=0;
	u16 arr_send,arr_send1;	  //��ǰһ������������
	
	//�������ܣ�ֻ����֧�����������ȡ����㡢���Ӹ�λ�󣬲���ִ����������
	if((ZB_Flag==0)&&(ZF_Flag==0)&&(SQT_Flag==0)&&(XQT_Flag==0)&&(ZBQ_Flag==0)&&(YL_Flag==0)&&(YBH_Flag==0)&&(YYH_Flag==0))
	{
		if(YF_Flag==0)   //�����λ����ʼ״̬����ִ���ҷ���
		{
			if((strstr((const char *)USART2_RX_BUF,(const char *)"YFS"))||(strstr((const char *)UART4_RX_BUF,(const char *)"YFS")))
			{
			 //5�Ų෭��
				memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			//��մ���2��������
				USART2_RX_LEN=0;			//����2״̬����
				memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//��մ���4��������			
				UART4_RX_LEN=0;				  //����4״̬����
				YF_Flag=1;		//����״̬��־λ
				motor5_run_flag=1;		//����״̬��־λ
				W25QXX_Write((u8*)&YF_Flag,34,1);		//��״̬��־λд��flash
				delay_ms(200);
				u2_printf("YF_flag==1");
				delay_ms(200);
				u2_printf("YFKS");
				delay_ms(200);
				u2_printf("CT_YCF1");
				MotorStart(5,0,1400-1,25-1);				 //5�ŵ������
				u2_printf("*%s*M5*Z*0*/**",RX_BUF);//����2����
				TIM10_Init(Ang_To_Arr_ZYFS(YF_Lim),65000);               //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz
				__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //����жϱ�־λ
				while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))
				{	
					//�����λ										
					if((0==GD5_YFZZ)&&(1==YF_Flag))                     //������翪������ѭ�������ͣת 
					{	
						delay_us(100);
						if(0==GD5_YFZZ)                    //������翪������ѭ�������ͣת 
						{
							u2_printf("GD5YFZZ");
							break;						
						}		             
					}
					  //�ж���û���յ���λ��ָ��		
					if(USART2_RX_LEN&0x8000)
					{
						u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���	
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//��մ���2��������		
						USART2_RX_LEN=0;				//����2״̬����											
					}	
					if(UART4_RX_LEN&0x8000)
					{
						u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���	
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//��մ���4��������			
						UART4_RX_LEN=0;					  //����4״̬����											
					}
					//������ϡ��������
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
					//����ͼƬָ��
					arr_send1=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//��ȡ��ǰ�Ĵ�������װ��ֵ
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
								u2_printf("CT_YCF%d",YCF_Pic);		//����2���Ͷ���ͼƬָ��
							}
						}
					}
				}					      
				MotorStop(5);  u2_printf("*%s*M5*T*0*/**",RX_BUF);       //���ֹͣ������2����			
				TIM10_Stop();         //�رն�ʱ��
				__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //����жϱ�־λ
				delay_ms(200);
				u2_printf("CT_YCF10");
				Motor4_BC(1,3200,1400-1,25-1);//���ò�������2200
			}			
		}	
		//����345�ŵ������	
		if((strstr((const char *)USART2_RX_BUF,(const char *)"YFS"))||(strstr((const char *)UART4_RX_BUF,(const char *)"YFS"))||(1==motor5_run_flag))  //�ҷ�����
		{		
			if(Ang_To_Arr_ZYFS(YF_Lim)>YF_Runed)
			{				
				//345��������
				direct=1;			//�������з����־
				YF_Dir_flag=1;		//���÷���״̬��־λ
				if(M345R_Start==0)
				{
					M345R_Start=1;
					delay_ms(200);
					u2_printf("CT_YF1");
					delay_ms(200);
				}
				MotorStart(3,1,(1400-1)*2,25-1);			     //3�ŵ������
				MotorStart(4,1,(1400-1)*0.8,25-1);				 //4�ŵ������
				MotorStart(5,1,1400-1,25-1);			 				 //5�ŵ������
				if(1==motor5_run_flag)
				{
					motor5_run_flag=0;		//����״̬��־λ
					u2_printf("*M5JS*M345*ZZZ*000*/**");
				}
				else
				{
					u2_printf("*%s*M345*ZZZ*000*/**",RX_BUF);	//����2����
				}
				TIM10_Init(Ang_To_Arr_ZYFS(YF_Lim)-YF_Runed,65000);	      //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz			
			}
		}
		if((strstr((const char *)USART2_RX_BUF,(const char *)"YFX"))||(strstr((const char *)UART4_RX_BUF,(const char *)"YFX")))  //�ҷ�����
		{			
			if(YF_Runed>0)
			{
				//345��������
			   direct=0;			//�������з����־
				 YF_Dir_flag=0;		//���÷���״̬��־λ
				if(M345R_End==1)
			   {
					M345R_End=0; 
					delay_ms(200);
					u2_printf("CT_YF8");	
			   }
				MotorStart(3,0,(1400-1)*2,25-1);			     //3�ŵ������
				MotorStart(4,0,(1400-1)*0.8,25-1);	 		 	 //4�ŵ������
				MotorStart(5,0,1400-1,25-1);			 //5�ŵ������
				u2_printf("*%s*M345*FFF*000*/**",RX_BUF);	//����2����
			  TIM10_Init(YF_Runed,65000);		     //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
			}	
		}				
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//��մ���2��������		
		USART2_RX_LEN=0;			//����2״̬����
		memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//��մ���4��������		
		UART4_RX_LEN=0;				  //����4״̬����
		  __HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);           //����жϱ�־λ	 	

		 if(((YF_Runed!=Ang_To_Arr_ZYFS(YF_Lim))&&(1==direct))||((0!=YF_Runed)&&(0==direct)))
		 {
			while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))    //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��
			{							
				//�����λ													
				if(((0==GD3_CS)||(0==GD4_CS))&&(0==direct))   //���������翪�أ�����ѭ����ֹͣ����
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
				if(((0==GD3_YFZZ)||(0==GD4_YFZZ))&&(1==direct))  //���������翪�أ�����ѭ����ֹͣ����
				{
					delay_us(100);
					if((0==GD3_YFZZ)||(0==GD4_YFZZ))          //���������翪�أ�����ѭ����ֹͣ����
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
				//ָֹͣ��
				if(USART2_RX_LEN&0x8000)
				{
					len=USART2_RX_LEN&0x3fff;	//��ȡ����2���������ַ�����		
					USART2_RX_BUF[len]=0;			//����2����ĩβ��"0"
					if((strstr((const char *)USART2_RX_BUF,(const char *)"STOP"))||(strstr((const char *)USART2_RX_BUF,(const char *)"YFS"))|| (strstr((const char *)USART2_RX_BUF,(const char *)"YFX"))) //�����յ�Stop,������ѭ��	
					{
//						memcpy(RX_BUF,USART2_RX_BUF,15);
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);//��մ���2��������			
						USART2_RX_LEN=0;				//����2״̬����
						break;
					}
					else 
					{
						u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���							
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//��մ���2��������		
						USART2_RX_LEN=0;
					}					
				}
				if(UART4_RX_LEN&0x8000)
				{
					len=UART4_RX_LEN&0x3fff;	//��ȡ����4���������ַ�����				
					UART4_RX_BUF[len]=0;				//����4����ĩβ��"0"
					if((strstr((const char *)UART4_RX_BUF,(const char *)"STOP"))||(strstr((const char *)UART4_RX_BUF,(const char *)"YFS"))|| (strstr((const char *)UART4_RX_BUF,(const char *)"YFX"))) //�����յ�Stop,������ѭ��	
					{
//						memcpy(RX_BUF,UART4_RX_BUF,15);
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);				//��մ���4��������	
						UART4_RX_LEN=0;				  //����4״̬����
						break;
					}
					if(strstr((const char *)UART4_RX_BUF,(const char *)"SEND OK"))
					{	}
					else 
					{
						u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���							
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//��մ���4��������		
						UART4_RX_LEN=0;				  //����4״̬����
					}					
				}
				//������ϡ��������
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
				//���Ͷ���ָ��
				 arr_send=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//��ȡ��ǰ�Ĵ�������װ��ֵ
				if(direct==1)
				{
					j=(YF_Runed+arr_send)/(Ang_To_Arr_ZYFS(YF_Lim)/7);		//ͼƬ��ż���
				}
				else
				{
					j=abs(YF_Runed,arr_send)/(Ang_To_Arr_ZYFS(YF_Lim)/7);		//ͼƬ��ż���
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
							u2_printf("CT_YF%d",YF_Pic);		//����2���Ͷ���ͼƬָ��
						}
					}				
				}
			}
			//���ֹͣ
			MotorStop(3); 				
			MotorStop(4); 	
			MotorStop(5);   
			u2_printf("*%s*M345*TTT*000*/**",RX_BUF);//����2����
			TIM10_Stop();          //��ʱ���ر�
			//�жϸ�λ	
			if(((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))||(0==GD3_CS)||(0==GD4_CS))&&(direct==0))
			{
				arr_now=0; 		//��ʱ���ڸ�λ״̬����״ֵ̬����Ϊ0��
				YF_Flag=0;		//����״̬��־λ
			}					
			else
			{							
				arr_now=__HAL_TIM_GET_COUNTER(&TIM10_Handler);			//��ȡ��ǰ�Ĵ�������װ��ֵ				
			}
			//ͨ���������ж������ۼ�
			if(direct==1)    //�������У�����+
			{
				if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))||(0==GD3_YFZZ)||(0==GD4_YFZZ))
				{
					YF_Runed=Ang_To_Arr_ZYFS(YF_Lim);				//��������������ֵΪ����ֵ
					M345R_End=1; 					
					delay_ms(200);
					u2_printf("CT_YF8");
				}
				else
				{				
					YF_Runed=YF_Runed+arr_now;		//��������������ֵ=��һ����������ֵ+�˴���������ֵ
				}
			}
			else		//�������У�����-
			{
				if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))||(0==GD3_CS)||(0==GD4_CS))
				{
					YF_Runed=0;	//����������ֵ��Ϊ0
					M345R_Start=0; 					
					delay_ms(200);
					u2_printf("CT_YF1");
				}
				else
				{
					YF_Runed=YF_Runed-arr_now;		//��������������ֵ=��һ����������ֵ-�˴���������ֵ
				}			
			}			
			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ
			//����ʱʱ�䵽���ǹ��û��������������һ�ξ��룬�����翪��λ�ã���翪�ذ�װ��򿪴˶Σ�
//			if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))&&((1==GD3_CS)||(1==GD4_CS))&&(direct==0)&&(YF_Flag==1))
//			{   			
//				if((1==GD3_CS)&&(0==GD4_CS))   //���3û��λ
//				{
//					MotorStart(3,0,1400-1,25-1);     //3�ŵ������
//					u2_printf("*%s*M3*F*0*/**",RX_BUF);
//					TIM10_Init(add_arr,65000);      //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ	 	
//					while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))
//					{			
//						if(0==GD3_CS)  //����ʱ������翪�أ�����ѭ�� 
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
//					MotorStop(3);  //���ֹͣ
//					u2_printf("*%s*M3*T*0*/**",RX_BUF);
//					TIM10_Stop();     //�رն�ʱ��
//					if(0==GD3_CS)
//					{
//						u2_printf("*%s*GD3CS*/*0*/**",RX_BUF);
//					}
//					else
//					{
//						u2_printf("*%s*GD3CS*/*1*/**",RX_BUF);
//					}
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ
//				}
//				if((0==GD3_CS)&&(1==GD4_CS))   //���4û��λ
//				{
//					MotorStart(4,0,1400-1,25-1);		 //4�ŵ������
//					u2_printf("*%s*M4*F*0*/**",RX_BUF);
//					TIM10_Init(add_arr,65000);      //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ	 	
//					while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))
//					{			
//						if(0==GD4_CS)  //����ʱ������翪�أ�����ѭ�� 
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
//					MotorStop(4);  //���ֹͣ
//					u2_printf("*%s*M4*T*0*/**",RX_BUF);
//					TIM10_Stop();      //�رն�ʱ��
//					if(0==GD4_CS)
//					{
//						u2_printf("*%s*GD4CS*/*0*/**",RX_BUF);
//					}
//					else
//					{
//						u2_printf("*%s*GD4CS*/*1*/**",RX_BUF);
//					}
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ				
//				}
//				if((1==GD3_CS)&&(1==GD4_CS))   //���3/4��û��λ
//				{
//					MotorStart(3,0,(1400-1)*2.0,25-1);     //3�ŵ������
//					MotorStart(4,0,(1400-1)*0.8,25-1);		 //4�ŵ������
//					MotorStart(5,0,1400-1,25-1);					 //5�ŵ������
//					u2_printf("*%s*M345*FFF*000*/**",RX_BUF);
//					TIM10_Init(add_arr,65000);      //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ	 	
//					while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))
//					{			
//						if((0==GD3_CS)||(0==GD4_CS))  //����ʱ������翪�أ�����ѭ�� 
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
//					MotorStop(3);   //���ֹͣ
//					MotorStop(4);
//					MotorStop(5);
//					u2_printf("*%s*M345*TTT*000*/**",RX_BUF);
//					TIM10_Stop();         //�رն�ʱ��
//					if((1==GD3_CS)||(1==GD4_CS))  //����ʱ������翪�أ�����ѭ�� 
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
//					if((0==GD3_CS)||(0==GD4_CS))  //����ʱ������翪�أ�����ѭ�� 
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
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ	
//				}
//			}
			//�෭��λ
			if(0==YF_Flag)      //ֻ�з���λ����ʼ״̬��С�෭�Ÿ�λ
			{			
				memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			//��մ���2��������
				USART2_RX_LEN=0;			//����2״̬����
				memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//��մ���4��������			
				UART4_RX_LEN=0;				  //����4״̬����
				//5�Ų෭��λ
//				Motor4_BC(0,2800,1400-1,25-1);//���ò�������
				memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//��մ���2��������		
				USART2_RX_LEN=0;				//����2״̬����
				memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//��մ���4��������		
				UART4_RX_LEN=0;				  //����4״̬����
				delay_ms(200);
				u2_printf("CT_ZCF10");
				MotorStart(5,1,1400-1,25-1);			 //5�ŵ������
				u2_printf("*%s*M5*F*0*/**",RX_BUF);		//����2����
				YF_Runed=0;			//����������ֵ��Ϊ0
				TIM10_Init(Ang_To_Arr_ZYFS(YF_Lim)*1,65000);           //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
				__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //����жϱ�־λ

				while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) )
				{				
					//�����λ
					if(((0==GD5_CS)&&(0==YF_Flag)))  //������翪������ѭ�������ͣת 
					{	
						delay_us(100);
						if(0==GD5_CS)
						{
							u2_printf("GD5CS");
							break;					
						}
					}
					  //�ж���û���յ���λ��ָ��		
					if(USART2_RX_LEN&0x8000)
					{
						u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���	
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);		//��մ���2��������	
						USART2_RX_LEN=0;							//����2״̬����								
					}
					if(UART4_RX_LEN&0x8000)
					{
						u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���	
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//��մ���4��������		
						UART4_RX_LEN=0;				  //����4״̬����												
					}
					//������ϡ��������
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
					//���Ͷ���ָ��
					arr_send1=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//��ȡ��ǰ�Ĵ�������װ��ֵ
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
								u2_printf("CT_YCF%d",YCF_Pic);		//����2���Ͷ���ͼƬָ��
							}
						}
					}
				}	     
				MotorStop(5);      //���ֹͣ
				u2_printf("*%s*M5*T*0*/**",RX_BUF);		//����2����
				TIM10_Stop();        //��ʱ���ر�
				__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //����жϱ�־λ
				YF_Flag=0;		//����״̬��־λ
				W25QXX_Write((u8*)&YF_Flag,34,1);		//��״̬��־λд��flash
				delay_ms(200);
				u2_printf("CT_YCF1");
				delay_ms(200);			
				u2_printf("YF_flag==0");
				delay_ms(200);
				u2_printf("YFFW");
				//����ʱʱ�䵽���ǹ��û��������������һ�ξ��룬�����翪��λ�ã���翪�ذ�װ��򿪴˶Σ��������������ж�ɾ����
//				if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))&&(1==GD5_CS)&&(direct==0)&&(0==YF_Flag))
//				{
//					MotorStart(5,1,1400-1,25-1);  			 //5�ŵ������
//					u2_printf("*%s*M5*F*0*/**",RX_BUF);
//					TIM10_Init(add_arr,65000);            //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //����жϱ�־λ	 	
//					while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))
//					{			
//						if(0==GD5_CS)  //����ʱ������翪�أ�����ѭ�� 
//						{
//							delay_us(100);
//							if(0==GD5_CS)
//							{
//								u2_printf("GD5CS");
//								break;	
//							}								
//						}
//					}			
//					MotorStop(5);      //���ֹͣ
//					u2_printf("*%s*M5*T*0*/**",RX_BUF);
//					TIM10_Stop();      //�رն�ʱ��
//					if(0==GD5_CS)
//					{
//						u2_printf("*%s*GD5CS*/*0*/**",RX_BUF);
//					}
//					else
//					{
//						u2_printf("*%s*GD5CS*/*1*/**",RX_BUF);
//					}
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ	
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
 ������      ��Fun_YL(void)  
 ��������    ��С����
 ����        ����
 ���        ����                           
************************************************************************/
void Fun_YL(void)
{
	u8 direct,key;    //��ʾ������з���1��С����ǰ����0��С���Ӻ���
	u16 arr_now;      //������������ֵ
	u8 len;           //��ʾ���յ��ַ����ĳ���
	u16 arr_feed;     //��������е�ǰһ������������,�����жϵ��ʧ������
	u16 pulse_num=0;  //�������е�ǰһ����������������ת�������������ĵ�ǰ������������Ƚ�
	u16 num=0;	
	u16 repeat_num;
	u8 break_flag=0;          //�жϳ����Ƿ��break���� 
//ʵ����λ��ʵʱ��ʾ������ǰ�˶�״̬ 
	static u8 k=0;            //���͵�k��ͼƬ
	static u8 kj=0;
	u8 i=0;
	u8 j=0;	
	u16 arr_send;                 //��ǰһ������������
	static u8 yljx_flag;    //�ж�С�����Ƿ����е�����λ�ã����Ƿ��ͼ���λ��ͼƬ	
	//�������ܣ�ֻ�������ҷ����ܸ�λ�󣬲��ܽ���С�����ƶ�
	if((ZF_Flag==0)&&(YF_Flag==0))
	{		
		if((strstr((const char *)USART2_RX_BUF,(const char *)"YLS"))||(strstr((const char *)UART4_RX_BUF,(const char *)"YLS")))
		{
			direct=1;			//�������з����־
			if(YL_Flag==0)
			{
				YL_Flag=1;		//����״̬��־λ
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
			direct=0;			//�������з����־
			if(1==yljx_flag)
			{
				yljx_flag=0;	//���ü���״̬��־λ
				delay_ms(200);
				u2_printf("CT_YL20");
			}
		}
		if(direct==1)   //�����С������ǰ
		{		
			if(Ang_To_Arr_YL(YL_Lim)>YL_Runed)  //����ʱ���Ƚ�ֵΪ���м���װ��ֵ��У׼��ĵ���װ��ֵ�Ĳ�ֵ��������ֵ����Ϊ0
			{
				MotorStart(7,0,700-1,25-1);
				TIM10_Init(Ang_To_Arr_YL(YL_Lim)-YL_Runed,65000);     //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz				
			}				
		}
		else       //�����С���Ӻ���
		{
			if(YL_Runed>0)    //����ʱ���Ƚ�ֵΪУ׼��ĵ���װ��ֵ��0,�Ҳ���Ϊ0
			{
				MotorStart(7,1,700-1,25-1);
				TIM10_Init(YL_Runed,65000);     //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz				
			}
		}
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);		//��մ���2��������	
		USART2_RX_LEN=0;				//����2״̬����
		memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//��մ���4��������	
		UART4_RX_LEN=0;				  //����4״̬����
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ
		 if(((YL_Runed!=Ang_To_Arr_YL(YL_Lim))&&(1==direct))||((0!=YL_Runed)&&(0==direct)))
		 {	 	
			while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))  //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��  
			{			
				for(repeat_num=0;repeat_num<600;repeat_num++)
				{			
					//�����λ											   						
//					if((0==GD7_ZZ)&&(1==direct))
//					{
//						delay_us(100);
//						if(0==GD7_ZZ)
//						{
//							u2_printf("GD7ZZ");					
//							break_flag=1;				//��ѭ��������־λ��1
//							break;					
//						}								
//					}
//					if((0==GD7_CS)&&(0==direct))
//					{
//						delay_us(100);
//						if(0==GD7_CS)
//						{
//							u2_printf("GD7CS");					
//							break_flag=1;			//��ѭ��������־λ��1
//							break;						
//						}					
//					}
					//ָֹͣ��
					if(USART2_RX_LEN&0x8000)
					{
						len=USART2_RX_LEN&0x3fff;			//��ȡ����2���������ַ�����		
						USART2_RX_BUF[len]=0;			//����2����ĩβ��"0"
						if((strstr((const char *)USART2_RX_BUF,(const char *)"STOP"))||(strstr((const char *)USART2_RX_BUF,(const char *)"YLS"))||(strstr((const char *)USART2_RX_BUF,(const char *)"YLX")))    //�����յ�Stop,������ѭ��	
						{
							break_flag=1;			//��ѭ��������־λ��1
							memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);		//��մ���2��������	
							USART2_RX_LEN=0;				//����2״̬����
							break;
						}
						else
						{
							u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���							
							memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);		//��մ���2��������	
							USART2_RX_LEN=0;				//����2״̬����
						}						
					}
					if(UART4_RX_LEN&0x8000)
					{
						len=UART4_RX_LEN&0x3fff;	//��ȡ����4���������ַ�����				
						UART4_RX_BUF[len]=0;				//����4����ĩβ��"0"
						if((strstr((const char *)UART4_RX_BUF,(const char *)"STOP"))||(strstr((const char *)UART4_RX_BUF,(const char *)"YLS"))||(strstr((const char *)UART4_RX_BUF,(const char *)"YLX")))    //�����յ�Stop,������ѭ��	
						{
							break_flag=1;			//��ѭ��������־λ��1
							memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//��մ���4��������			
							UART4_RX_LEN=0;				  //����4״̬����
							break;
						}
						if(strstr((const char *)UART4_RX_BUF,(const char *)"SEND OK"))
						{	}
						else
						{
							u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���							
							memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//��մ���4��������			
							UART4_RX_LEN=0;				  //����4״̬����
						}						
					}
					//������ϡ��������
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
//							break_flag=1;			//��ѭ��������־λ��1
//							break;						
//						}								             
//					}								
				}
				if(break_flag==1)
				{
					u2_printf("break_flag==1");
					break;
				}
				//���Ͷ���ָ��
				 arr_send=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//��ȡ��ǰ�Ĵ�������װ��ֵ
				if(direct==1)
				{
					j=(YL_Runed+arr_send)/(Ang_To_Arr_YL(YL_Lim)/19);		//ͼƬ��ż���
				}
				else
				{
					j=abs(YL_Runed,arr_send)/(Ang_To_Arr_YL(YL_Lim)/19);		//ͼƬ��ż���
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
							u2_printf("CT_YL%d",YL_Pic);		//����2���Ͷ���ͼƬָ��
						}
					}					
				}
			}				    
			MotorStop(7);       //���ֹͣ
			TIM10_Stop();       //��ʱ���ر�
			break_flag=0;		//���break��־λ
			//�жϸ�λ
			if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))&&(direct==0))   //�ж��Ƿ��ڸ�λ״̬����λ״̬��ǰ�������еĶ�ʱ������
			{
				arr_now=0;    		//��ʱ���ڸ�λ״̬����״ֵ̬����Ϊ0��
				YL_Flag=0;		//����״̬��־λ
				delay_ms(200);
				u2_printf("YL_flag==0");
			}
			else
			{
				arr_now=__HAL_TIM_GET_COUNTER(&TIM10_Handler);    //��ȡ��ǰ����ֵarr_now				
				YL_Flag=1;		//����״̬��־λ
			}	
			//ͨ���������ж������ۼ�
			if(direct==1)        //�����С����ǰ��������+
			{
				if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))||(0==GD7_ZZ))
				{ 					
					YL_Runed=Ang_To_Arr_YL(YL_Lim);				//��������������ֵΪ����ֵ
					yljx_flag=1;		//���ü���״̬��־λ
					delay_ms(200);
					u2_printf("CT_YL20");
					delay_ms(200);
					u2_printf("YLJX");
				}
				else
				{  YL_Runed=YL_Runed+arr_now;	}					//��������������ֵ=��һ����������ֵ+�˴���������ֵ	
			}
			else                //�����С���Ӻ��ˣ�����-
			{
				if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))||(0==GD7_CS))
				{						
					YL_Runed=0; 			//����������ֵ��Ϊ0
					delay_ms(200);
					u2_printf("CT_YL1");
					delay_ms(200);
					u2_printf("YLFW");
				}
				else
				{	 
					YL_Runed=YL_Runed-arr_now;		//��������������ֵ=��һ����������ֵ-�˴���������ֵ
				}						
			}				
			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ	   			
			//����ʱʱ�䵽���ǹ��û��������������һ�ξ��룬�����翪��λ�ã���翪�ذ�װ��򿪴˶�,��ɾ������ж���䣩
//			if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))&&(GD7_CS==1)&&(direct==0)&&(YL_Flag==1))
//			{   
//				MotorStart(7,1,700-1,25-1);
//			    TIM10_Init(add_arr,65000);   //�򿪶�ʱ��
//				__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ
//				
//				while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))
//				{							
//					if(0==GD7_CS)  //����ʱ������翪�أ�����ѭ�� 
//					{
//						delay_us(100);
//						if(0==GD7_CS)
//						{
//							u2_printf("GD7CS");
//							break;
//						}							
//					}
//				}			
//				MotorStop(7);   //���ֹͣ
//				TIM10_Stop();     //�رն�ʱ��
//				__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ	
//			}			
		}
	}
	else
	{
		LedAlm(100,"YLGS");
	}		
}



/***********************************************************************
 ������      ��Fun_YL1(void)  
 ��������    ��С����
 ����        ����
 ���        ����                           
************************************************************************/
void Fun_YL1(void)
{
	u8 direct,key;    //��ʾ������з���1��С����ǰ����0��С���Ӻ���
	u16 arr_now;      //������������ֵ
	u8 len;           //��ʾ���յ��ַ����ĳ���
	static u8 desk_front_flag=0;			//����״̬��־λ
	static u8 desk_behind_flag=0;	 		//����״̬��־λ
//ʵ����λ��ʵʱ��ʾ������ǰ�˶�״̬
	static u8 k=0;            //���͵�k��ͼƬ
	static u8 kj=0;
	u8 j=0;	
	u16 arr_send;                 //��ǰһ������������
	static u8 yljx_flag;    //�ж�С�����Ƿ����е�����λ�ã����Ƿ��ͼ���λ��ͼƬ	
	//�������ܣ�ֻ�������ҷ����ܸ�λ�󣬲��ܽ���С�����ƶ�
	if((ZF_Flag==0)&&(YF_Flag==0))
	{	
		//С���ӵ��������һ��ʱ��
		if(YL_Flag==0)
		{
			if((strstr((const char *)USART2_RX_BUF,(const char *)"YLS"))||(strstr((const char *)UART4_RX_BUF,(const char *)"YLS")))
			{
				direct=1;			//�������з����־
				YL_Flag=1;		//����״̬��־λ
				W25QXX_Write((u8*)&YL_Flag,39,1);		//��״̬��־λд��flash
				desk_front_flag=1;		//����״̬��־λ
				u2_printf("YL_flag==1");
				delay_ms(200);
				u2_printf("YLKS");
				delay_ms(200);
				u2_printf("CT_YLFront");
				MotorStart(7,0,700-1,25-1);
				u2_printf("*%s*M7*Z*0*/**",RX_BUF);		//����2����
				TIM10_Init((u16)(Ang_To_Arr_YL(YL_Lim)/1.5),65000);   //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
				__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);  //����жϱ�־λ
				while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))) 
				{
					//�����λ
					if((0==GD7_ZZ)&&(1==direct))
					{
						delay_us(100);
						if(0==GD7_ZZ)
						{
							u2_printf("GD7ZZ");					
							break;					
						}								
					}	
					//������ϡ��������
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
				MotorStop(7);    u2_printf("*%s*M7*T*0*/**",RX_BUF);   //���ֹͣ				������2����		
				TIM10_Stop();       //��ʱ���ر�
				__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);		// ����жϱ�־λ
				u2_printf("���7��һ�׶��������");
			}
		}

		if((strstr((const char *)USART2_RX_BUF,(const char *)"YLS"))||(strstr((const char *)UART4_RX_BUF,(const char *)"YLS"))||(desk_front_flag==1))
		{
			desk_front_flag=0;		//����״̬��־λ
			direct=1;			//�������з����־
			if(YL_Flag==0)
			{
				YL_Flag=1;		//����״̬��־λ
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
			direct=0;			//�������з����־
			if(1==yljx_flag)
			{
				yljx_flag=0;	//���ü���״̬��־λ
				delay_ms(200);
				u2_printf("CT_YL20");
			}
		}
		if(direct==1)   //�����С������ǰ
		{		
			if(Ang_To_Arr_YL(YL_Lim)>YL_Runed)  //����ʱ���Ƚ�ֵΪ���м���װ��ֵ��У׼��ĵ���װ��ֵ�Ĳ�ֵ��������ֵ����Ϊ0
			{
				MotorStart(7,0,700-1,25-1);
				u2_printf("*%s*M7*Z*0*/**",RX_BUF);		//����2����
				TIM10_Init(Ang_To_Arr_YL(YL_Lim)-YL_Runed,65000);    //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz		
			}				
		}
		else       //�����С���Ӻ���
		{
			if(YL_Runed>0)    //����ʱ���Ƚ�ֵΪУ׼��ĵ���װ��ֵ��0,�Ҳ���Ϊ0
			{
				desk_behind_flag=1;		//����״̬��־λ
				MotorStart(7,1,700-1,25-1);
				u2_printf("*%s*M7*F*0*/**",RX_BUF);		//����2����
				TIM10_Init(YL_Runed,65000);    //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz			
			}
		}
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);//��մ���2��������			
		USART2_RX_LEN=0;				//����2״̬����
		memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//��մ���4��������		
		UART4_RX_LEN=0;				  //����4״̬����
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ
		 if(((YL_Runed!=Ang_To_Arr_YL(YL_Lim))&&(1==direct))||((0!=YL_Runed)&&(0==direct)))
		 {	 	
			 while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))  //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��  
			{						
				//�����λ											   						
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
				//ָֹͣ��
				if(USART2_RX_LEN&0x8000)
				{
					len=USART2_RX_LEN&0x3fff;				//��ȡ����2���������ַ�����	
					USART2_RX_BUF[len]=0;			//����2����ĩβ��"0"
					if((strstr((const char *)USART2_RX_BUF,(const char *)"STOP"))||(strstr((const char *)USART2_RX_BUF,(const char *)"YLS"))||(strstr((const char *)USART2_RX_BUF,(const char *)"YLX")))    //�����յ�Stop,������ѭ��	
					{
//						memcpy(RX_BUF,USART2_RX_BUF,15);
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//��մ���2��������		
						USART2_RX_LEN=0;			//����2״̬����
						break;
					}
					else
					{
						u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���							
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//��մ���2��������		
						USART2_RX_LEN=0;			//����2״̬����
					}						
				}	
				if(UART4_RX_LEN&0x8000)
				{
					len=UART4_RX_LEN&0x3fff;	//��ȡ����4���������ַ�����				
					UART4_RX_BUF[len]=0;				//����4����ĩβ��"0"
					if((strstr((const char *)UART4_RX_BUF,(const char *)"STOP"))||(strstr((const char *)UART4_RX_BUF,(const char *)"YLS"))||(strstr((const char *)UART4_RX_BUF,(const char *)"YLX")))    //�����յ�Stop,������ѭ��	
					{
//						memcpy(RX_BUF,UART4_RX_BUF,15);
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//��մ���4��������		
						UART4_RX_LEN=0;				  //����4״̬����
						break;
					}
					if(strstr((const char *)UART4_RX_BUF,(const char *)"SEND OK"))
					{	}
					else
					{
						u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���							
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//��մ���4��������		
						UART4_RX_LEN=0;				  //����4״̬����
					}						
				}
				//������ϡ��������
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
				
				//���Ͷ���ָ��
				 arr_send=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//��ȡ��ǰ�Ĵ�������װ��ֵ
				if(direct==1)
				{
					j=(YL_Runed+arr_send)/(Ang_To_Arr_YL(YL_Lim)/19);		//ͼƬ��ż���
				}
				else
				{
					j=abs(YL_Runed,arr_send)/(Ang_To_Arr_YL(YL_Lim)/19);		//ͼƬ��ż���
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
							u2_printf("CT_YL%d",YL_Pic);		//����2���Ͷ���ͼƬָ��
						}							
					}					
				}
			}				    
			MotorStop(7);   u2_printf("*%s*M7*T*0*/**",RX_BUF);    //���ֹͣ������2����
			TIM10_Stop();       //��ʱ���ر�
			//�жϸ�λ
			if(((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))||(0==GD7_CS))&&(direct==0))   //�ж��Ƿ��ڸ�λ״̬����λ״̬��ǰ�������еĶ�ʱ������
			{
				arr_now=0;         //��ʱ���ڸ�λ״̬����״ֵ̬����Ϊ0��
				YL_Flag=0;				//����״̬��־λ
				W25QXX_Write((u8*)&YL_Flag,39,1);		//��״̬��־λд��flash
				u2_printf("YL_flag==0");
			}
			else
			{
				arr_now=__HAL_TIM_GET_COUNTER(&TIM10_Handler);    //��ȡ��ǰ����ֵarr_now				
				YL_Flag=1;		//����״̬��־λ
			}	
			//ͨ���������ж������ۼ�
			if(direct==1)        //�����С����ǰ��������+
			{
				if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))||(0==GD7_ZZ))
				{ 					
					YL_Runed=Ang_To_Arr_YL(YL_Lim);				//��������������ֵΪ����ֵ
					yljx_flag=1;		//���ü���״̬��־λ
					u2_printf("CT_YL20");
					delay_ms(200);
					u2_printf("YLJX");
				}
				else
				{  YL_Runed=YL_Runed+arr_now;	}				//��������������ֵ=��һ����������ֵ+�˴���������ֵ		
			}
			else                //�����С���Ӻ��ˣ�����-
			{
				if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))||(0==GD7_CS))
				{						
					YL_Runed=0; 			//����������ֵ��Ϊ0
					u2_printf("CT_YL1");
					delay_ms(200);
					u2_printf("YLFW");
				}
				else
				{	 
					YL_Runed=YL_Runed-arr_now;		//��������������ֵ=��һ����������ֵ-�˴���������ֵ
				}						
			}				
			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ	   			
			//����ʱʱ�䵽���ǹ��û��������������һ�ξ��룬�����翪��λ�ã���翪�ذ�װ��򿪴˶�,��ɾ������ж���䣩
//			if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))&&(GD7_CS==1)&&(direct==0)&&(YL_Flag==1))
//			{   
//				MotorStart(7,1,700-1,25-1);
//				u2_printf("*%s*M7*F*0*/**",RX_BUF);
//			    TIM10_Init(add_arr,65000);      //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
//				__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ
//				
//				while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))
//				{							
//					if(0==GD7_CS)  //����ʱ������翪�أ�����ѭ�� 
//					{
//						delay_us(100);
//						if(0==GD7_CS)
//						{
//							u2_printf("GD7CS");
//							break;
//						}							
//					}
//				}			
//				MotorStop(7);     //���ֹͣ
//				u2_printf("*%s*M7*T*0*/**",RX_BUF);
//				TIM10_Stop();     //�رն�ʱ��
//				if(0==GD7_CS)
//				{
//					u2_printf("*%s*GD7CS*/*0*/**",RX_BUF);
//				}
//				else
//				{
//					u2_printf("*%s*GD7CS*/*1*/**",RX_BUF);
//				}
//				__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ	
//			}			
		}
		if((YL_Flag==0)&&(1==desk_behind_flag))
		{
			memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//��մ���2��������		
			USART2_RX_LEN=0;			//����2״̬����
			memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//��մ���4��������		
			UART4_RX_LEN=0;				  //����4״̬����
			YL_Runed=0;						//��������������Ϊ0
			MotorStart(7,1,700-1,25-1);
			u2_printf("*%s*M7*F*0*/**",RX_BUF);		//����2����
			TIM10_Init(Ang_To_Arr_YL(YL_Lim)/1.5,65000);		   //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);  //����жϱ�־λ
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
					//������ϡ��������
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
			MotorStop(7);       //���ֹͣ
			u2_printf("*%s*M7*T*0*/**",RX_BUF);		//����2����
			TIM10_Stop();       //��ʱ���ر�
			desk_behind_flag=0;		//����״̬��־λ
			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);		// ����жϱ�־λ
			u2_printf("���7��һ�׶η������");
		}		
	}
	else
	{
		LedAlm(100,"YLGS");
	}		
}

/***********************************************************************
 ������      ��Fun_YF2(void)  
 ��������    ��ִ���ҷ������
 ����        ����
 ���        ����                           
************************************************************************/
void Fun_YL2(void)
{
	u8 direct,key;    //��ʾ������з���1��С����ǰ����0��С���Ӻ���
	u16 arr_now;      //������������ֵ
	u8 len;           //��ʾ���յ��ַ����ĳ���
	
//ʵ����λ��ʵʱ��ʾ������ǰ�˶�״̬ 
	static u8 k=0;            //���͵�k��ͼƬ
	static u8 kj=0;
	u8 j=0;	
	u16 arr_send;                 //��ǰһ������������
	static u8 yljx_flag;    //�ж�С�����Ƿ����е�����λ�ã����Ƿ��ͼ���λ��ͼƬ	
	//�������ܣ�ֻ�������ҷ����ܸ�λ�󣬲��ܽ���С�����ƶ�
	if((ZF_Flag==0)&&(YF_Flag==0))
	{		
		if((strstr((const char *)USART2_RX_BUF,(const char *)"YLS"))||(strstr((const char *)UART4_RX_BUF,(const char *)"YLS")))
		{
			direct=1;			//�������з����־
			if(YL_Flag==0)
			{
				YL_Flag=1;		//����״̬��־λ
				W25QXX_Write((u8*)&YL_Flag,39,1);		//��״̬��־λд��flash
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
			direct=0;			//�������з����־
			if(1==yljx_flag)
			{
				yljx_flag=0;	//���ü���״̬��־λ
				delay_ms(200);
				u2_printf("CT_YL20");
			}
		}
		if(direct==1)   //�����С������ǰ
		{		
			if(Ang_To_Arr_YL2(YL_Lim)>YL_Runed)  //����ʱ���Ƚ�ֵΪ���м���װ��ֵ��У׼��ĵ���װ��ֵ�Ĳ�ֵ��������ֵ����Ϊ0
			{
				MotorStart(7,0,700-1,25-1);
				u2_printf("*%s*M7*Z*0*/**",RX_BUF);		//����2����
				TIM2_Init(Ang_To_Arr_YL2(YL_Lim)-YL_Runed,65000);  //��ʱ������=(freq1*freq_time1_1)/90mhz			
			}				
		}
		else       //�����С���Ӻ���
		{
			if(YL_Runed>0)    //����ʱ���Ƚ�ֵΪУ׼��ĵ���װ��ֵ��0,�Ҳ���Ϊ0
			{
				MotorStart(7,1,700-1,25-1);
				u2_printf("*%s*M7*F*0*/**",RX_BUF);		//����2����
				TIM2_Init(YL_Runed,65000);  //��ʱ������=(freq1*freq_time1_1)/90mhz			
			}
		}
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//��մ���2��������		
		USART2_RX_LEN=0;				//����2״̬����
		memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//��մ���4��������			
		UART4_RX_LEN=0;				  //����4״̬����
		__HAL_TIM_CLEAR_FLAG(&TIM2_Handler, TIM_SR_CC1IF); // ����жϱ�־λ
		 if(((YL_Runed!=Ang_To_Arr_YL2(YL_Lim))&&(1==direct))||((0!=YL_Runed)&&(0==direct)))
		 {	 	
			while(!(__HAL_TIM_GET_FLAG(&TIM2_Handler, TIM_SR_CC1IF)))  //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��  
			{						
				//�����λ											   						
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
				//ָֹͣ��
				if(USART2_RX_LEN&0x8000)
				{
					len=USART2_RX_LEN&0x3fff;	//��ȡ����2���������ַ�����				
					USART2_RX_BUF[len]=0;			//����2����ĩβ��"0"
					if((strstr((const char *)USART2_RX_BUF,(const char *)"STOP"))||(strstr((const char *)USART2_RX_BUF,(const char *)"YLS"))||(strstr((const char *)USART2_RX_BUF,(const char *)"YLX")))    //�����յ�Stop,������ѭ��	
					{
//						memcpy(RX_BUF,USART2_RX_BUF,15);
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//��մ���2��������		
						USART2_RX_LEN=0;			//����2״̬����
						break;
					}
					else
					{
						u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���							
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);		//��մ���2��������	
						USART2_RX_LEN=0;			//����2״̬����
					}						
				}	
				if(UART4_RX_LEN&0x8000)
				{
					len=UART4_RX_LEN&0x3fff;		//��ȡ����4���������ַ�����			
					UART4_RX_BUF[len]=0;				//����4����ĩβ��"0"
					if((strstr((const char *)UART4_RX_BUF,(const char *)"STOP"))||(strstr((const char *)UART4_RX_BUF,(const char *)"YLS"))||(strstr((const char *)UART4_RX_BUF,(const char *)"YLX")))    //�����յ�Stop,������ѭ��	
					{
//						memcpy(RX_BUF,UART4_RX_BUF,15);
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//��մ���4��������		
						UART4_RX_LEN=0;				  //����4״̬����
						break;
					}
					if(strstr((const char *)UART4_RX_BUF,(const char *)"SEND OK"))
					{	}
					else
					{
						u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���							
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//��մ���4��������			
						UART4_RX_LEN=0;				  //����4״̬����
					}						
				}
				//������ϡ��������
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
				
				//���Ͷ���ָ��
				 arr_send=__HAL_TIM_GET_COUNTER(&TIM2_Handler);		//��ȡ��ǰ�Ĵ�������װ��ֵ
				if(direct==1)
				{
					j=(YL_Runed+arr_send)/(Ang_To_Arr_YL2(YL_Lim)/19);		//ͼƬ��ż���
				}
				else
				{
					j=abs(YL_Runed,arr_send)/(Ang_To_Arr_YL2(YL_Lim)/19);		//ͼƬ��ż���
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
							u2_printf("CT_YL%d",YL_Pic);		//����2���Ͷ���ͼƬָ��
						}
					}					
				}
			}				    
			MotorStop(7);       //���ֹͣ
			u2_printf("*%s*M7*T*0*/**",RX_BUF);		//����2����
			TIM2_Stop();        //��ʱ���ر�
			//�жϸ�λ
			if(((__HAL_TIM_GET_FLAG(&TIM2_Handler, TIM_SR_CC1IF))||(0==GD7_CS))&&(direct==0))   //�ж��Ƿ��ڸ�λ״̬����λ״̬��ǰ�������еĶ�ʱ������
			{
				arr_now=0;         //��ʱ���ڸ�λ״̬����״ֵ̬����Ϊ0��
				YL_Flag=0;		//����״̬��־λ
				W25QXX_Write((u8*)&YL_Flag,39,1);		//��״̬��־λд��flash
				delay_ms(200);
				u2_printf("YL_flag==0");
			}
			else
			{
				arr_now=__HAL_TIM_GET_COUNTER(&TIM2_Handler);    //��ȡ��ǰ����ֵarr_now				
				YL_Flag=1;		//����״̬��־λ
				W25QXX_Write((u8*)&YL_Flag,39,1);		//��״̬��־λд��flash
			}	
			//ͨ���������ж������ۼ�
			if(direct==1)        //�����С����ǰ��������+
			{
				if((__HAL_TIM_GET_FLAG(&TIM2_Handler, TIM_SR_CC1IF))||(0==GD7_ZZ))
				{ 					
					YL_Runed=Ang_To_Arr_YL2(YL_Lim);				//��������������ֵΪ����ֵ
					yljx_flag=1;		//���ü���״̬��־λ
					delay_ms(200);
					u2_printf("CT_YL20");
					delay_ms(200);
					u2_printf("YLJX");
				}
				else
				{  YL_Runed=YL_Runed+arr_now;	}					//��������������ֵ=��һ����������ֵ+�˴���������ֵ	
			}
			else                //�����С���Ӻ��ˣ�����-
			{
				if((__HAL_TIM_GET_FLAG(&TIM2_Handler, TIM_SR_CC1IF))||(0==GD7_CS))
				{						
					YL_Runed=0; 			//����������ֵ��Ϊ0
					delay_ms(200);
					u2_printf("CT_YL1");
					delay_ms(200);
					u2_printf("YLFW");
				}
				else
				{	 
					YL_Runed=YL_Runed-arr_now;		//��������������ֵ=��һ����������ֵ-�˴���������ֵ
				}						
			}				
			__HAL_TIM_CLEAR_FLAG(&TIM2_Handler, TIM_SR_CC1IF); // ����жϱ�־λ	   			
			//����ʱʱ�䵽���ǹ��û��������������һ�ξ��룬�����翪��λ�ã���翪�ذ�װ��򿪴˶�,��ɾ������ж���䣩
//			if((__HAL_TIM_GET_FLAG(&TIM2_Handler, TIM_SR_CC1IF))&&(GD7_CS==1)&&(direct==0)&&(YL_Flag==1))
//			{   
//				MotorStart(7,1,700-1,25-1);
//				u2_printf("*%s*M7*F*0*/**",RX_BUF);
//			    TIM2_Init(add_arr,65000);   //�򿪶�ʱ��
//				__HAL_TIM_CLEAR_FLAG(&TIM2_Handler, TIM_SR_CC1IF); // ����жϱ�־λ
//				
//				while(!(__HAL_TIM_GET_FLAG(&TIM2_Handler, TIM_SR_CC1IF)))
//				{							
//					if(0==GD7_CS)  //����ʱ������翪�أ�����ѭ�� 
//					{
//						delay_us(100);
//						if(0==GD7_CS)
//						{
//							u2_printf("GD7CS");
//							break;
//						}							
//					}
//				}			
//				MotorStop(7);    //���ֹͣ
//				u2_printf("*%s*M7*T*0*/**",RX_BUF);
//				TIM2_Stop();     //�رն�ʱ��
//				if(0==GD7_CS)
//				{
//					u2_printf("*%s*GD7CS*/*0*/**",RX_BUF);
//				}
//				else
//				{
//					u2_printf("*%s*GD7CS*/*1*/**",RX_BUF);
//				}
//				__HAL_TIM_CLEAR_FLAG(&TIM2_Handler, TIM_SR_CC1IF); // ����жϱ�־λ	
//			}			
		}
	}
	else
	{
		LedAlm(100,"YLGS");
	}		
}

/***********************************************************************
 ������      ��Fun_ZBH(void)  
 ��������    ���󱳲�����
 ����        ����
 ���        ���� 

************************************************************************/
void Fun_ZBH(void)
{
	u8 direct,key,len;
	//ʵ����λ��ʵʱ��ʾ������ǰ�˶�״̬
	static u8 k=0;      //���͵�k�Ŷ���ָ��
	u8 j=0;	
	u16 arr_send;	    //��ǰһ������������
	static u8 kj;
	
	//�������ܣ�ֻ������ִ��������������������λ�󣬲��ܽ����󱳲�����
	if((ZF_Flag==1)&&(ZYH_Flag==0))
	{
		ZBH_Flag=!ZBH_Flag;	         //�󱳲�����λ״̬��־λȡ��
		ZBH_Dir_flag=!ZBH_Dir_flag;	 //�󱳲��������־λ		
		if(ZBH_Dir_flag==1)
		{ 
			direct=1;			//�������з����־
			delay_ms(200);
			u2_printf("ZBHKS");
			delay_ms(200);
			u2_printf("CT_ZBH1");
		}
		else
		{ 
		    direct=0;			//�������з����־
			delay_ms(200);
			u2_printf("CT_ZBH20");
		}
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//��մ���2��������		
		USART2_RX_LEN=0;			//����2״̬����
		memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//��մ���4��������			
		UART4_RX_LEN=0;				  //����4״̬����
		if(1==direct)
		{
			MotorStart(3,1,1400-1,25-1);	           //3�ŵ������
			u2_printf("*%s*M3*Z*0*/**",RX_BUF);		//����2����
			TIM10_Init(ZF_Runed,65000);           //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
		}
		else
		{
			MotorStart(3,0,1400-1,25-1);            //3�ŵ������
			u2_printf("*%s*M3*F*0*/**",RX_BUF);		//����2����
			TIM10_Init(ZBH_Runed,65000);         //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz			
		}
		
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);        //����жϱ�־λ	 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))) //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��   
		{			
			//�����λ
			if((0==GD3_ZFZZ)&&(0==direct))  //����
			{
				delay_us(100);
				if(0==GD3_ZFZZ)
				{
					u2_printf("GD3ZFZZ");
					break;				
				}
			}
			if((0==GD3_CS)&&(1==direct))     //����
			{	
				delay_us(100);
				if(0==GD3_CS)
				{
					u2_printf("GD3_CS");
					break;					
				}					
			}
			  //�ж���û���յ���λ��ָ��		
			if(USART2_RX_LEN&0x8000)
			{
				u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���	
				memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			//��մ���2��������
				USART2_RX_LEN=0;								//����2״̬����										
			}
			if(UART4_RX_LEN&0x8000)
			{
				u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���	
				memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//��մ���4��������			
				UART4_RX_LEN=0;					  //����4״̬����														
			}
			//������ϡ��������
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
			//���Ͷ���ָ��
			arr_send=__HAL_TIM_GET_COUNTER(&TIM10_Handler);				//��ȡ��ǰ�Ĵ�������װ��ֵ		
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
						u2_printf("CT_ZBH%d",ZBH_Pic);			//����2���Ͷ���ͼƬָ��
					}						
				}
			}
		}				  
		MotorStop(3);       //���ֹͣ
		u2_printf("*%s*M3*T*0*/**",RX_BUF);		//����2����
		TIM10_Stop();       //�رն�ʱ��    
		//��ʱʱ��û������絽
		if((!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))&&(0==GD3_CS)&&(1==direct))
		{
			ZBH_Runed=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//��ȡ��ǰ�Ĵ�������װ��ֵ
		}
		else 
		{
			ZBH_Runed=ZF_Runed;
		}		
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //����жϱ�־λ	
		if(ZBH_Dir_flag==1)
		{			
			delay_ms(200);
			u2_printf("CT_ZBH20");
			delay_ms(200);
			u2_printf("ZBHJX");
		}
		else
		{			
			ZBH_Runed=0;			//����������ֵ��Ϊ0
			delay_ms(200);
			u2_printf("CT_ZBH1");
			delay_ms(200);
			u2_printf("ZBHFW");
		}
//		//ʹ����������ˮƽ״̬
//		if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))&&(1==GD4_CS)&&(direct==1))
//		{
//			MotorStart(3,1,1400-1,25-1);                 //3�ŵ������
//			u2_printf("*%s*M3*Z*0*/**",RX_BUF);
//			TIM10_Init(add_arr,65000);                //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
//			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);           //����жϱ�־λ	 	
//			while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))    //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��
//			{
//				if(0==GD3_CS)      //���������ػ�������翪�أ�������ѭ�������ֹͣת�� 
//				{ 
//					delay_us(100);
//					if(0==GD3_CS)
//					{
//						u2_printf("GD3CS");			
//						break; 
//					}						
//				}				
//			}				                                 			
//			MotorStop(3);        //���ֹͣ
//			u2_printf("*%s*M3*T*0*/**",RX_BUF);
//			TIM10_Stop();        //��ʱ���ر�
//			if(0==GD3_CS)
//			{
//				u2_printf("*%s*GD3CS*/*0*/**",RX_BUF);
//			}
//			else
//			{
//				u2_printf("*%s*GD3CS*/*1*/**",RX_BUF);
//			}
//			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ
//		}		
	}
	else
	{
		LedAlm(100,"ZBHGS");
	}	
}

/***********************************************************************
 ������      ��Fun_YBH(void)
 ��������    ���ұ�������
 ����        ����
 ���        ����                           
************************************************************************/
void Fun_YBH(void)
{
	u8 direct,key,len;
	//ʵ����λ��ʵʱ��ʾ������ǰ�˶�״̬
	static u8 k=0;       //���͵�k�Ŷ���ָ��
	u8 j=0;	
	u16 arr_send;	    //��ǰһ������������
	static u8 kj;	

	//�������ܣ�ֻ������ִ���ҷ�����������������λ�󣬲��ܽ����ұ�������
	if((1==YF_Flag)&&(YYH_Flag==0))
	{	
		YBH_Flag=!YBH_Flag;         //�ұ�������λ״̬��־λ
		YBH_Dir_flag=!YBH_Dir_flag; //�ұ����������־λ 	
		if(YBH_Dir_flag==1)
		{ 
			direct=1;			//�������з����־
			delay_ms(200);
			u2_printf("YBHKS");
			delay_ms(200);
			u2_printf("CT_YBH1");
		}
		else
		{ 
			direct=0;			//�������з����־
			delay_ms(200);
			u2_printf("CT_YBH20");
		}
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//��մ���2��������		
		USART2_RX_LEN=0;			//����2״̬����
		memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//��մ���4��������			
		UART4_RX_LEN=0;				  //����4״̬����
		if(1==direct)
		{
			MotorStart(3,0,(1400-1),25-1);              //3�ŵ������
			u2_printf("*%s*M3*Z*0*/**",RX_BUF);				//����2����
			TIM10_Init(YF_Runed,65000);                  //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
		}
		else
		{
			MotorStart(3,1,(1400-1),25-1);             //3�ŵ������
			u2_printf("*%s*M3*F*0*/**",RX_BUF);			//����2����
			TIM10_Init(YBH_Runed,65000);               //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
		}
		
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);           //����жϱ�־λ	 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))    //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ�� 
		{			
			//�����λ����
			if((0==GD3_YFZZ)&&(0==direct))  //����
			{
				delay_us(100);
				if(0==GD3_YFZZ)
				{
					u2_printf("GD3YFZZ");
					break;				
				}	
			}
			if((0==GD3_CS)&&(1==direct))     //����
			{
				delay_us(100);
				if(0==GD3_CS)
				{
					u2_printf("GD3CS");
					break;				
				}						
			}
			  //�ж���û���յ���λ��ָ��		
			if(USART2_RX_LEN&0x8000)
			{
				u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���	
				memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//��մ���2��������		
				USART2_RX_LEN=0;					//����2״̬����										
			}
			if(UART4_RX_LEN&0x8000)
			{
				u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���	
				memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//��մ���4��������			
				UART4_RX_LEN=0;						  //����4״̬����										
			}
			//������ϡ��������
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
			//���Ͷ���ָ��
			arr_send=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//��ȡ��ǰ�Ĵ�������װ��ֵ
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
						u2_printf("CT_YBH%d",YBH_Pic);			//����2���Ͷ���ͼƬָ��	
					}						
				}
			}
		}			
		MotorStop(3);        //���ֹͣ
		u2_printf("*%s*M3*T*0*/**",RX_BUF);		//����2����
		TIM10_Stop();        //�رն�ʱ��
		//��ʱʱ��û������絽
		if((!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))&&(0==GD3_CS)&&(1==direct))
		{
			YBH_Runed=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//��ȡ��ǰ�Ĵ�������װ��ֵ
		}
		else 
		{
			YBH_Runed=YF_Runed;
		}
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //����жϱ�־λ	
		
		if(YBH_Dir_flag==1)
		{ 		
			 delay_ms(200);
			 u2_printf("CT_YBH20");
			 delay_ms(200);
			 u2_printf("YBHJX");
		}
		else
		{ 			
			 YBH_Runed=0;			//����������ֵ��Ϊ0
			 delay_ms(200);
			 u2_printf("CT_YBH1");
			 delay_ms(200);
			 u2_printf("YBHFW");
		}	
//		//ʹ����������ˮƽ״̬
//		if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))&&(1==GD4_CS)&&(direct==1))
//		{
//			MotorStart(3,0,1400-1,25-1);             //3�ŵ������
//			u2_printf("*%s*M3*Z*0*/**",RX_BUF);
//			TIM10_Init(add_arr,65000);            //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
//			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);           //����жϱ�־λ	 	
//			while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))    //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��
//			{
//				if(0==GD3_CS)      //���������ػ�������翪�أ�������ѭ�������ֹͣת�� 
//				{ 
//					delay_us(100);
//					if(0==GD3_CS)
//					{
//						u2_printf("GD3CS");			
//						break; 
//					}						
//				}				
//			}				                                 			
//			MotorStop(3);        //���ֹͣ
//			u2_printf("*%s*M3*T*0*/**",RX_BUF);
//			TIM10_Stop();        //��ʱ���ر�
//			if(0==GD3_CS)
//			{
//				u2_printf("*%s*GD3CS*/*0*/**",RX_BUF);
//			}
//			else
//			{
//				u2_printf("*%s*GD3CS*/*1*/**",RX_BUF);
//			}
//			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ
//		}		
	}
	else
	{
		LedAlm(100,"YBHGS");	
	}
}

/***********************************************************************
 ������      ��Fun_ZYH(void)  
 ��������    ������������
 ����        ����
 ���        ����                           
************************************************************************/
void Fun_ZYH(void)
{
	u8 direct,key,len;	
	//ʵ����λ��ʵʱ��ʾ������ǰ�˶�״̬
	static u8 k=0;      //���͵�k�Ŷ���ָ��
	u8 j=0;	 
	u16 arr_send;	   //��ǰһ������������
	static u8 kj;	

	//�������ܣ�ֻ������ִ�����������󱳲�����λ�󣬲��ܽ�������������
	if((1==ZF_Flag)&&(ZBH_Flag==0))
	{
		ZYH_Flag=!ZYH_Flag;         //����������λ״̬��־λ
		ZYH_Dir_flag=!ZYH_Dir_flag; //�������������־λ		
		if(ZYH_Dir_flag==1)
		{ 
			direct=1;			//�������з����־
			delay_ms(200);
			u2_printf("ZYHKS");
			delay_ms(200);
			u2_printf("CT_ZYH1");
		}
		else
		{ 
			direct=0;			//�������з����־
			delay_ms(200);
			u2_printf("CT_ZYH20");
		}
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);//��մ���2��������			
		USART2_RX_LEN=0;			//����2״̬����
		memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//��մ���4��������			
		UART4_RX_LEN=0;				  //����4״̬����
		if(1==direct)
		{
			MotorStart(4,1,(1400-1)*1.2,25-1);   		 //4�ŵ������
			u2_printf("*%s*M4*Z*0*/**",RX_BUF);		//����2����
			TIM10_Init(ZF_Runed,65000);              //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
		}
		else  
		{
			MotorStart(4,0,(1400-1)*1.2,25-1);  		 //4�ŵ������
			u2_printf("*%s*M4*F*0*/**",RX_BUF);		//����2����
			TIM10_Init(ZYH_Runed,65000);            //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
		}
		
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);          //����жϱ�־λ	 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))   //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ�� 
		{			
			//�����λ
			if((0==GD4_ZFZZ)&&(0==direct))  //����
			{
				delay_us(100);
				if(0==GD4_ZFZZ)
				{
					u2_printf("GD4ZFZZ");
					break;					
				}
			}
			if((0==GD4_CS)&&(1==direct))     //����
			{
				delay_us(100);
				if(0==GD4_CS)
				{
					u2_printf("GD4CS");
					break;				
				}						
			}
			  //�ж���û���յ���λ��ָ��		
			if(USART2_RX_LEN&0x8000)
			{
				u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���	
				memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			//��մ���2��������
				USART2_RX_LEN=0;					//����2״̬����										
			}				
			if(UART4_RX_LEN&0x8000)
			{
				u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���	
				memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//��մ���4��������			
				UART4_RX_LEN=0;					  //����4״̬����											
			}
			//������ϡ��������
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
			 //���Ͷ���ָ��			
			arr_send=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//��ȡ��ǰ�Ĵ�������װ��ֵ
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
						u2_printf("CT_ZYH%d",ZYH_Pic);		//����2���Ͷ���ͼƬָ��	
					}						
				}
			}
		}				     
		MotorStop(4);       //���ֹͣ
		u2_printf("*%s*M4*T*0*/**",RX_BUF);		//����2����
		TIM10_Stop();       //��ʱ���ر�
		//��ʱʱ��û������絽
		if((!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))&&(0==GD4_CS)&&(1==direct))
		{
			ZYH_Runed=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//��ȡ��ǰ�Ĵ�������װ��ֵ
		}
		else 
		{
			ZYH_Runed=ZF_Runed;
		}
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //����жϱ�־λ	
		
		if(ZYH_Dir_flag==1)
		{ 
			delay_ms(200);
			u2_printf("CT_ZYH20");
			delay_ms(200);
			u2_printf("ZYHJX");
		}
		else
		{ 
			ZYH_Runed=0;			//����������ֵ��Ϊ0
			delay_ms(200);
			u2_printf("CT_ZYH1");
			delay_ms(200);
			u2_printf("ZYHFW");
		}		
		
//		//ʹ����������ˮƽ״̬
//		if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))&&(1==GD4_CS)&&(direct==1))
//		{
//			MotorStart(4,1,1400-1,25-1);       		 //4�ŵ������
//			u2_printf("*%s*M4*Z*0*/**",RX_BUF);
//			TIM10_Init(add_arr,65000);             //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
//			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);           //����жϱ�־λ	 	
//			while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))    //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��
//			{
//				if(0==GD4_CS)      //���������ػ�������翪�أ�������ѭ�������ֹͣת�� 
//				{ 
//					delay_us(100);
//					if(0==GD4_CS)
//					{
//						u2_printf("GD4CS");			
//						break; 
//					}						
//				}				
//			}				                                 			
//			MotorStop(4);        //���ֹͣ
//			u2_printf("*%s*M4*T*0*/**",RX_BUF);
//			TIM10_Stop();        //��ʱ���ر�
//			if(0==GD4_CS)
//			{
//				u2_printf("*%s*GD4CS*/*0*/**",RX_BUF);
//			}
//			else
//			{
//				u2_printf("*%s*GD4CS*/*1*/**",RX_BUF);
//			}
//			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ
//		}
	}
	else
	{
		LedAlm(100,"ZYHGS");
	}
}

/***********************************************************************
 ������      ��Fun_YYH(void)  
 ��������    ������������
 ����        ����
 ���        ����                           
************************************************************************/
void Fun_YYH(void)
{
	u8 direct,key,len;
	//ʵ����λ��ʵʱ��ʾ������ǰ�˶�״̬
	static u8 k=0;        //���͵�k�Ŷ���ָ��
	u8 j=0;	
	u16 arr_send;	      //��ǰһ������������
	static u8 kj;		

	//�������ܣ�ֻ������ִ���ҷ��������ұ�������λ�󣬲��ܽ�������������
	if((YF_Flag==1)&&(YBH_Flag==0))
	{
		YYH_Flag=!YYH_Flag;	        //����������λ״̬��־λ
		YYH_Dir_flag=!YYH_Dir_flag;	//�������������־λ	
		if(YYH_Dir_flag==1)
		{ 
			direct=1;			//�������з����־
			delay_ms(200);
			u2_printf("CT_YYH1");
			delay_ms(200);
			u2_printf("YYHKS");	
		}
		else
		{ 
			direct=0;			//�������з����־
			delay_ms(200);
			u2_printf("CT_YYH20");
		}
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//��մ���2��������		
		USART2_RX_LEN=0;			//����2״̬����
		memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//��մ���4��������		
		UART4_RX_LEN=0;				  //����4״̬����
		if(1==direct)
		{
			MotorStart(4,0,(1400-1)*0.8,25-1);   		 //4�ŵ������
			u2_printf("*%s*M4*Z*0*/**",RX_BUF);		//����2����
			TIM10_Init(YF_Runed,65000);            //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
		}
		else
		{
			MotorStart(4,1,(1400-1)*0.8,25-1);   		 //4�ŵ������
			u2_printf("*%s*M4*F*0*/**",RX_BUF);		//����2����
			TIM10_Init(YYH_Runed,65000);            //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
		}	
		
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);          //����жϱ�־λ	 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))   //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��
		{			
			//�����λ
			if((0==GD4_YFZZ)&&(0==direct))  //����
			{
				delay_us(100);
				if(0==GD4_YFZZ)
				{
					u2_printf("GD4YFZZ");
					break;				
				}	
			}
			if((0==GD4_CS)&&(1==direct))     //����
			{
				delay_us(100);
				if(0==GD4_CS)
				{	
					u2_printf("GD4CS");
					break;									
				}
			}
			  //�ж���û���յ���λ��ָ��		
			if(USART2_RX_LEN&0x8000)
			{
				u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���	
				memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//��մ���2��������		
				USART2_RX_LEN=0;						//����2״̬����									
			}
			if(UART4_RX_LEN&0x8000)
			{
				u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���	
				memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//��մ���4��������			
				UART4_RX_LEN=0;					  //����4״̬����											
			}
			//������ϡ��������
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
			//���Ͷ���ָ��
			arr_send=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//��ȡ��ǰ�Ĵ�������װ��ֵ
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
						u2_printf("CT_YYH%d",YYH_Pic);			//����2���Ͷ���ͼƬָ��
					}						
				}
			}
		}				      
		MotorStop(4);      //���ֹͣ
		u2_printf("*%s*M4*T*0*/**",RX_BUF);		//����2����
		TIM10_Stop();      //�رն�ʱ�� 
		//��ʱʱ��û������絽
		if((!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))&&(0==GD4_CS)&&(1==direct))
		{
			YYH_Runed=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//��ȡ��ǰ�Ĵ�������װ��ֵ
		}
		else 
		{
			YYH_Runed=YF_Runed;
		}
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //����жϱ�־λ	
		
		if(YYH_Dir_flag==1)
		{ 
			delay_ms(200);
			u2_printf("CT_YYH20"); 
			delay_ms(200);
			u2_printf("YYHJX");
		}
		else
		{ 
			YYH_Runed=0;			//����������ֵ��Ϊ0
			delay_ms(200);
			u2_printf("CT_YYH1");
			delay_ms(200);
			u2_printf("YYHFW");
		}
//		//ʹ����������ˮƽ״̬
//		if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))&&(1==GD4_CS)&&(direct==1))
//		{
//			MotorStart(4,0,1400-1,25-1);      		 //4�ŵ������
//			u2_printf("*%s*M4*Z*0*/**",RX_BUF);
//			TIM10_Init(add_arr,65000);                 //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
//			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);           //����жϱ�־λ	 	
//			while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))    //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��
//			{
//				if(0==GD4_CS)      //���������ػ�������翪�أ�������ѭ�������ֹͣת�� 
//				{ 
//					delay_us(100);
//					if(0==GD4_CS)
//					{
//						u2_printf("GD4CS");			
//						break; 
//					}						
//				}				
//			}				                                 			
//			MotorStop(4);        //���ֹͣ
//			u2_printf("*%s*M4*T*0*/**",RX_BUF);
//			TIM10_Stop();        //��ʱ���ر�
//			if(0==GD4_CS)
//			{
//				u2_printf("*%s*GD4CS*/*0*/**",RX_BUF);
//			}
//			else
//			{
//				u2_printf("*%s*GD4CS*/*1*/**",RX_BUF);
//			}
//			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ
//		}		
	}
	else
	{
		LedAlm(100,"YYHGS");
	}
}

/***********************************************************************
 ������      ��Fun_JRAM(void)   
 ��������    ��ִ�м��ⰴĦ����
 ����        ��t:���ⰴĦ����
 ���        ����  
                          
***********************************************************************/
void Fun_JRAM(void)
{
	u8 i=0;
	u8 len,break_flag=0;
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//��մ���2��������
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//��մ���4��������
	USART2_RX_LEN=0;		//����2״̬����
	UART4_RX_LEN=0;			//����4״̬����
	//�������ܣ�ֻ��������׹ر�ʱ�ſɽ��а�Ħ����
	if(0==ZBQ_Flag)
	{
		u2_printf("*%s*JRAM*Q*/*/**",RX_BUF);		//����2����
		DIR_XZFPQ=1;		//��ת���������Ŵ�
		delay_ms(500);      //�ȴ����Ŵ�		
		DIR_QB=1;           //��������
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
				len=USART2_RX_LEN&0x3fff;	//��ȡ����2���������ַ�����				
				USART2_RX_BUF[len]=0;			//����2����ĩβ��"0"
				if((strstr((const char *)USART2_RX_BUF,(const char *)"JRAM")))    //�����յ�Stop,������ѭ��	
				{											
//					memcpy(RX_BUF,USART2_RX_BUF,15);
					memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//��մ���2��������		
					USART2_RX_LEN=0;			//����2״̬����
					break_flag=1;			//��ѭ��������־λ��1
					break;						
				}
			}
			if(UART4_RX_LEN&0x8000)
			{
				len=UART4_RX_LEN&0x3fff;		//��ȡ����4���������ַ�����			
				UART4_RX_BUF[len]=0;				//����4����ĩβ��"0"
				if((strstr((const char *)UART4_RX_BUF,(const char *)"JRAM")))    //�����յ�Stop,������ѭ��	
				{											
//					memcpy(RX_BUF,UART4_RX_BUF,15);
					memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//��մ���4��������		
					UART4_RX_LEN=0;				  //����4״̬����
					break_flag=1;			//��ѭ��������־λ��1
					break;						
				}
			}				
		}
		if(1==break_flag)
		{			
			u2_printf("*%s*JRAM*T*/*/**",RX_BUF);		//����2����
			break_flag=0;			//���break��־λ
			DIR_QB=0;           //����ֹͣ
			DIR_XZFPQ=0;		//��ת������ֹͣ����
			delay_ms(1000);     //�ȴ����Źر�
			u2_printf("JRAMJS");
		}				
	}		
	else
	{
		LedAlm(100,"JRAMGS");
	} 
}


/***********************************************************************
 ������      ��Fun_JR(void)   
 ��������    ��ִ�м��ȹ���
 ����        ����
 ���        ����  
                          
***********************************************************************/
void Fun_JR(void)
{
	short temp;
	u8 i;
	if(1==ZBQ_Flag)   	//�������ܣ�ֻ��������򿪵�ʱ����ܽ��м���
	{
		LED1=0;
		//����
		DIR_JR=1;           //������������ʼ����PH3
		TIM10_Init(2000-1,45000-1);    //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
		for(i=0;i<20;i++)    //��ʱ20S
		{
			while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)));  //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��
			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);          //����жϱ�־λ   
		}
		TIM10_Stop();       //�رն�ʱ��	 
		DS18B20_Start();    //����һ���¶�ת��
		delay_ms(750);
			
		DS18B20_Rst();	 
		DS18B20_Write_Byte(0xCC);
		DS18B20_Write_Byte(0xBE);
			
		while(1)
		{
			if(1==WD1_flag)   //��ʼ��ʱ�ñ�־λΪ1
			{
				temp=DS18B20_Get_Temp();
				if(temp<=35)
				{
					u2_printf("*%s*WD*/*%d*/**",RX_BUF,temp);		//����2����
				}
				else
				{
					DIR_JR=0;        //�رռ�����
					u2_printf("*%s*WD*/*%d*/**",RX_BUF,temp);		//����2����
					WD1_flag=0;   //ʹ�������else��������һ��whileѭ��
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
			if(1==WD2_flag)              //��ʼ��ʱ�ñ�־λΪ1
			{
				temp=DS18B20_Get_Temp();    //��ds18b20�õ��¶�ֵ
				u2_printf("*%s*WD*/*%d*/**",RX_BUF,temp);		//����2����
				if(temp<=30)
				{
					DIR_JR=1;               //��������������				
				}
				else if(temp>=37)
				{
					DIR_JR=0;               //�رռ�����ֹͣ����
					WD2_flag=0;          //ʹ�������else��������һ��whileѭ��
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
 ������      ��Motor1(void)   
 ��������    ��
 ����        ����
 ���        ����                           
************************************************************************/
void Motor1(u8 dir)
{
	u8 direct,len;
	u16 arr_now;              //��ǰһ������������
	
//ʵ����λ��ʵʱ��ʾ������ǰ�˶�״̬
	u8 break_flag=0;          //�жϳ����Ƿ��Ǵ�break������ 
	u16 repeat_num;
	static u8 k;             //����k�Ŷ���
	static u8 kj;
	u8 i=0;
	u8 j=0;	
	u16 arr_send;              //��ǰһ����������ֵ
	static u8 zbjx_flag; //֧�����е�����λ����1�����ͼ���λ��ͼƬ
	
	//�������ܣ�ֻ�������ҷ����ܸ�λ�󣬲��ܽ���֧��	
		if(dir==1)
		{				
			MotorStart(1,1,0,0);      //֧������
			u2_printf("MotorStart(1,1,0,0)");
		}
		else
		{
			MotorStart(1,0,0,0);      ///֧������
			u2_printf("MotorStart(1,0,0,0)");
		}
		TIM10_Init(30000,65000);    //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	

		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//��մ���2��������			
		USART2_RX_LEN=0;				//����2״̬����				
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ
							
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))  //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��   
		{		}		
		MotorStop(1);    //���ֹͣ
		TIM10_Stop();      //�رն�ʱ��
		break_flag=0;      //��־λ����
		//�жϸ�λ
		u2_printf("Motor_1_STOP()");
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ	
}

/***********************************************************************
 ������      ��Motor2(void)   
 ��������    ��
 ����        ����
 ���        ����                           
************************************************************************/
void Motor2(u8 dir)
{
	u8 direct,len;
	u16 arr_now;              //��ǰһ������������
	
//ʵ����λ��ʵʱ��ʾ������ǰ�˶�״̬
	u8 break_flag=0;          //�жϳ����Ƿ��Ǵ�break������ 
	u16 repeat_num;
	static u8 k;             //����k�Ŷ���
	static u8 kj;
	u8 i=0;
	u8 j=0;	
	u16 arr_send;              //��ǰһ����������ֵ
	static u8 zbjx_flag; //֧�����е�����λ����1�����ͼ���λ��ͼƬ
	
	//�������ܣ�ֻ�������ҷ����ܸ�λ�󣬲��ܽ���֧��	
		if(dir==1)
		{				
			MotorStart(2,1,0,0);			//�����Ƹ�����
      u2_printf("otorStart(2,1,0,0)");           //֧������
		}
		else
		{
			MotorStart(2,0,0,0);     //�����Ƹ�����                                                     //֧������
			u2_printf("MotorStart(2,0,0,0)");
		}
		
		TIM10_Init(30000,65000);   //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz		
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//��մ���2��������		
		USART2_RX_LEN=0;				//����2״̬����								
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ
							
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))  //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��   
		{		}		
		MotorStop(2);   //���ֹͣ
		TIM10_Stop();      //�رն�ʱ��
		break_flag=0;      //��־λ����
		//�жϸ�λ
		u2_printf("Motor2Stop");
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ	
}


/***********************************************************************
 ������      ��Motor3(void)  
 ��������    ��
 ����        ����
 ���        ���� 

************************************************************************/
void Motor3(u8 dir)
{
	u8 direct,key,len;
	u16 arr_feed;       //��������е�ǰһ������������,�����жϵ��ʧ������
	u16 pulse_num=0;    //�������е�ǰһ����������������ת�������������ĵ�ǰ������������Ƚ�
	u16 num=0;	 
	u8 break_flag=0;    //�жϳ����Ƿ��break����
					
		if(dir==1)
		{ 
			u2_printf("\r\nDIR3=1\r\n");
			direct=1;			  //�������з����־
			MotorStart(3,0,1400-1,25-1);	         //3�ŵ������
		}
		else
		{ 
			u2_printf("\r\nDIR3=0\r\n");
			direct=0; 			//�������з����־
			MotorStart(3,1,1400-1,25-1);	          //3�ŵ������
		}
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);		//��մ���2��������	
		USART2_RX_LEN=0;			//����2״̬����
		TIM10_Init(8000,65000);                 //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);        //����жϱ�־λ	 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))) //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��   
		{		
				//�����λ
//				if((0==GD3_ZFZZ)&&(1==direct))  //����
//				{
//					delay_us(100);
//					if(0==GD3_ZFZZ)
//					{
//						u2_printf("\r\nGD3_Left_End\r\n");
//						break;
//					}
//				}
//				if((0==GD3_CS)&&(0==direct))     //����
//				{
//					delay_us(100);
//					if(0==GD3_CS)
//					{
//						u2_printf("\r\nGD3_Start\r\n");
//						break;
//					}
//				}
//				if((0==GD3_YFZZ)&&(1==direct))     //����
//				{
//					u2_printf("\r\nGD3_Right_End\r\n");
//					break;						
//				}
				//������ϡ��������
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
		MotorStop(3);    //���ֹͣ
		TIM10_Stop();       //�رն�ʱ��    
		break_flag=0;       //���break��־λ
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //����жϱ�־λ		
		u2_printf("\r\nMotor_3_STOP\r\n");
}

/***********************************************************************
 ������      ��Motor4(void)  
 ��������    ��
 ����        ����
 ���        ���� 

************************************************************************/
void Motor4(u8 dir)
{
	u8 direct,key,len;
	u16 arr_feed;       //��������е�ǰһ������������,�����жϵ��ʧ������
	u16 pulse_num=0;    //�������е�ǰһ����������������ת�������������ĵ�ǰ������������Ƚ�
	u16 num=0;
	u8 break_flag=0;    //�жϳ����Ƿ��break����
					
		if(dir==1)
		{ 
			u2_printf("\r\n0IR4=1\r\n");
			direct=1;			//�������з����־
			MotorStart(4,0,1400-1,25-1);	  		 //4�ŵ������
		}
		else
		{ 
			u2_printf("\r\nDIR4=0\r\n");
			direct=0;			//�������з����־
			MotorStart(4,1,1400-1,25-1);	     		 //4�ŵ������
		}
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);		//��մ���2��������	
		USART2_RX_LEN=0;		  	//����2״̬����
				
		TIM10_Init(8000,65000);            //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);        //����жϱ�־λ	 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))) //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��   
		{		
				//�����λ
//				if((0==GD4_ZFZZ)&&(1==direct))     //����
//				{
//					delay_us(100);
//					if(0==GD4_ZFZZ)
//					{
//						u2_printf("\r\nGD4_Left_End\r\n");
//						break;
//					}
//				}
//				if((0==GD4_CS)&&(0==direct))                     //����
//				{
//					delay_us(100);
//					if(0==GD4_CS)
//					{
//						u2_printf("\r\nGD4_Start\r\n");
//						break;
//					}
//											
//				}
//				if((0==GD4_YFZZ)&&(1==direct))     //����
//				{
//					u2_printf("\r\nGD4_Right_End\r\n");
//					break;						
//				}
				//������ϡ��������
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
		MotorStop(4);   //���ֹͣ
		TIM10_Stop();       //�رն�ʱ��    
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //����жϱ�־λ	
		u2_printf("\r\nMotor_4_STOP\r\n");
}


/************************************************************************
 ������      ��Motor5(void)  
 ��������    ��
 ����        ����
 ���        ���� 

************************************************************************/
void Motor5(u8 dir)
{
	u8 direct,key,len;
	u16 arr_feed;       //��������е�ǰһ������������,�����жϵ��ʧ������
	u16 pulse_num=0;    //�������е�ǰһ����������������ת�������������ĵ�ǰ������������Ƚ�
	u16 num=0;
	u8 break_flag=0;    //�жϳ����Ƿ��break����
					
		if(dir==1)
		{ 
			u2_printf("\r\nDIR5=1\r\n");
			direct=1;			//�������з����־
			MotorStart(5,1,1400-1,25-1);	    			 //5�ŵ������
		}
		else
		{ 
			u2_printf("\r\nDIR5=0\r\n");
			direct=0;			//�������з����־
			MotorStart(5,0,1400-1,25-1);	      			 //5�ŵ������
		}
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//��մ���2��������		
		USART2_RX_LEN=0;			 //����2״̬����
		
		
		TIM10_Init(8000,65000);            //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);        //����жϱ�־λ	 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))) //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��   
		{		
				//�����λ
//				if((0==GD5_ZFZZ))  //����
//				{
//					u2_printf("\r\n0==GD5_ZFZZ\r\n");
//					break;	
//				}
						
//				if((0==GD5_ZFZZ)&&(1==direct))  //����
//				{
//					delay_us(100);
//					if(0==GD5_ZFZZ)
//					{
//						u2_printf("\r\n0==GD5_ZFZZ\r\n");
//						break;	
//					}
//				}
//				if((0==GD5_CS)&&(0==direct))     //����
//				{
//					delay_us(100);
//					if(0==GD5_CS)
//					{
//						u2_printf("\r\n0==GD5_CS\r\n");
//						break;
//					}
//				}
//				if((0==GD5_YFZZ)&&(1==direct))     //����
//				{
//					u2_printf("\r\nGD5_Right_End\r\n");
//					break;						
//				}
				//������ϡ��������
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
		MotorStop(5);     //���ֹͣ
		TIM10_Stop();       //�رն�ʱ��    
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //����жϱ�־λ	
		u2_printf("\r\nMotor_5_STOP\r\n");
}

/************************************************************************
 ������      ��Motor6(void)  
 ��������    ��
 ����        ����
 ���        ���� 

************************************************************************/
void Motor6(u8 dir)
{
	u8 direct,key,len;
	u16 arr_feed;       //��������е�ǰһ������������,�����жϵ��ʧ������
	u16 pulse_num=0;    //�������е�ǰһ����������������ת�������������ĵ�ǰ������������Ƚ�
	u16 num=0;
	u8 break_flag=0;    //�жϳ����Ƿ��break����
					
		if(dir==1)
		{ 
			u2_printf("\r\nDIR6=0\r\n");
			direct=1;			//�������з����־
			MotorStart(6,0,1400-1,25-1);	       //�������
		}
		else
		{ 
			u2_printf("\r\nDIR6=1\r\n");
			direct=0;			//�������з����־
			MotorStart(6,1,1400-1,25-1);	       //�������
		}
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//��մ���2��������		
		USART2_RX_LEN=0;		  	//����2״̬����
		
		
		TIM10_Init(30000,65000);          //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);        //����жϱ�־λ	 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))) //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��   
		{		
				//�����λ
//				if((0==GD6_ZZ)&&(direct==1))  //����
//				{
//					delay_us(100);
//					if(0==GD6_ZZ)
//					{
//						u2_printf("\r\n0==GD6_ZZ\r\n");
//						break;
//					}					
//				}
//				if((0==GD6_CS)&&(direct==0))     //����
//				{
//					delay_us(100);
//					if(0==GD6_CS)
//					{
//						u2_printf("\r\n0==GD6_CS\r\n");
//						break;
//					}
//				}
//			
//				//������ϡ��������
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
		MotorStop(6);    //���ֹͣ
		TIM10_Stop();       //�رն�ʱ��    
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //����жϱ�־λ	
		u2_printf("\r\nMotorStop(6)\r\n");
}

/************************************************************************
 ������      ��Motor7(void)  
 ��������    ���󱳲�����
 ����        ����
 ���        ���� 
************************************************************************/
void Motor7(u8 dir)
{
	u8 direct,key,len;
	u16 arr_feed;       //��������е�ǰһ������������,�����жϵ��ʧ������
	u16 pulse_num=0;    //�������е�ǰһ����������������ת�������������ĵ�ǰ������������Ƚ�
	u16 num=0;
	u8 break_flag=0;    //�жϳ����Ƿ��break����
					
		if(dir==1)
		{ 
			u2_printf("\r\nDIR7=0\r\n");
			direct=1;			//�������з����־
			MotorStart(7,0,700-1,25-1);	       //�������
		}
		else
		{ 
			u2_printf("\r\nDIR7=1\r\n");
			direct=0;			//�������з����־
			MotorStart(7,1,700-1,25-1);	       //�������
		}
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//��մ���2��������		
		USART2_RX_LEN=0;  			//����2״̬����
		
		
		TIM10_Init(64000,65000);         //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);        //����жϱ�־λ	 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))) //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��   
		{		
				//�����λ
//				if((0==GD7_ZZ)&&(1==direct))  //����
//				{
//					u2_printf("\r\n0==GD7_ZZ\r\n");
//					break;	
//				}
//				if((0==GD7_CS)&&(0==direct))     //����
//				{
//					u2_printf("\r\n0==GD7_CS\r\n");
//					break;						
//				}
			
				//������ϡ��������
//				if(1==PCF8574_ReadBit(1))        
//				{						
//					u2_printf("\r\nMotor7_Alm\r\n");
//					break;		             
//				}															
		}				  
		MotorStop(7);     //���ֹͣ
		TIM10_Stop();       //�رն�ʱ��    
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //����жϱ�־λ	
		u2_printf("\r\nMotor_7_STOP\r\n");
}


/***********************************************************************
 ������      ��WriteInU2(void)  
 ��������    ��д�봮��2����
 ����        ����
 ���        ����                           
************************************************************************/
void WriteInU2(char *p)
{
	u8 len=strlen(p);
	u8 i;
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);//��մ���2��������
	for(i=0;i<len;i++)
	{
	  USART2_RX_BUF[i]=p[i];		//ѭ��������д�봮��2��������
	}	
}
/***********************************************************************
 ������      ��Fun_LD(void)  
 ��������    ���������Ժ���
 ����        ����
 ���        ����                           
************************************************************************/
void Fun_LD(void)
{
	//��
	WriteInU2("ZFS");		
	Fun_ZF();     //����	
	delay_ms(1000);
	Fun_ZBH();   //�󱳲�����	
	delay_ms(1000);
	Fun_ZBH();   //�󱳲�����λ	
	delay_ms(1000);
	Fun_ZYH();  //����������
	delay_ms(1000);
	Fun_ZYH();  //����������λ	
	delay_ms(1000);
	WriteInU2("ZFX");
	Fun_ZF();           //����λ
	delay_ms(1000);

	//�ҷ�
	WriteInU2("YFS");
	Fun_YF();          //�ҷ���
	delay_ms(1000);
	Fun_YBH();  //�ұ�������
	delay_ms(1000);
	Fun_YBH();  //�ұ�������λ
	delay_ms(1000);
	Fun_YYH(); //����������
	delay_ms(1000);
	Fun_YYH(); //����������λ
	delay_ms(1000);
	WriteInU2("YFX");
	Fun_YF();          //�ҷ���λ
	delay_ms(1000);
	
	//������
	WriteInU2("SQTS");
	Fun_SQT();              //������
	delay_ms(1000);
	WriteInU2("SQTX");
	Fun_SQT();              //�����ȸ�λ
	delay_ms(1000);
	
	//�γ�����-֧���������ȡ���������С����
	
	//֧��
	WriteInU2("ZBS");
	Fun_ZB();                //֧��
	delay_ms(1000);
	
	//������
	WriteInU2("XQTX");
	Fun_XQT();            //������	
	delay_ms(1000);
	
	//������
	Fun_ZBQ(0);            //��������
	delay_ms(1000);
	
	//���ش�����
	Fun_CZ1();	

	//�Զ���ϴ
	Fun_ZDCX();
	delay_ms(1000);
	
	//�Զ����	
	Fun_ZDHG();
	delay_ms(1000);

	Fun_ZBQ(1);            //�������ر�
	delay_ms(1000);
	
	//�����Ƹ����
	ZBQ_Flag=1;		//����״̬��־λ
	RELAY6=1;                   //�̵����õ�
	Fun_ZBTG(1,ZBDTG_Lim);           //�����Ƹ����	
	RELAY6=0;

	//����
	ZBQ_Flag=1;		//����״̬��־λ
	RELAY6=1;                  //�̵����õ�
	Fun_ZBD(1);
	RELAY6=0;   
	delay_ms(1000);

	//�����Ƹ�����
	ZBQ_Flag=1;		//����״̬��־λ
	RELAY6=1;                   //�̵����õ�
	Fun_ZBTG(0,ZBDTG_Lim);           //�����Ƹ����	
	RELAY6=0;
	delay_ms(1000);
	
	//С����
	WriteInU2("YLS");
	Fun_YL1();               //С���ӿ���
	delay_ms(1000);
	WriteInU2("YLX");
	Fun_YL1();               //С���Ӻ���
	delay_ms(1000);	
	
	
	WriteInU2("XQTS");
	Fun_XQT();            //�����ȸ�λ
	delay_ms(1000);
	
	WriteInU2("ZBX");
	Fun_ZB();                //֧����λ

	ZB_Flag=0;               //֧��
	SQT_Flag=0;              //������
	XQT_Flag=0;              //������
	ZF_Flag=0;               //��
	YF_Flag=0;               //�ҷ�
	ZBH_Flag=0;              //�󱳲�����
	YBH_Flag=0;              //�ұ�������
	ZYH_Flag=0;              //����������
	YYH_Flag=0;              //����������
	ZBQ_Flag=0;              //������
	ZDZBQ_Flag=0;            //�Զ�������
	YL_Flag=0;               //�Ͳ�����һ����
}


/***********************************************************************
 ������      ��Fun_HL_ZB(void)  
 ��������    ������֧����������
 ����        ����
 ���        ����
                           
************************************************************************/
void Fun_HL_ZB(void)
{
	static u8 zbjx_flag; //�ж�֧���Ƿ����е�����λ�ã����Ƿ��ͼ���λ��ͼƬ
	u8 direct,key;
	u16 arr_now;               //��ǰһ�����������������������ۼ� 
	u8 len;	                   //���ܵ��ַ�������
//ʵ����λ��ʵʱ��ʾ������ǰ�˶�״̬
	static u8 k=0;            //���͵�k��ͼƬָ��
	u8 j=0;	
	u16 arr_send;             //��ǰһ������������
	static u8 kj;
	strcpy((char *)RX_BUF,(const char *)"HLZB");
	//�������ܣ�ֻ�������ҷ����ܸ�λ�󣬲��ܽ���֧��
	if((ZF_Flag==0)&&(YF_Flag==0)&&(SD_Flag==1))
	{					
		ZB_Dir_flag=!ZB_Dir_flag;    //֧�������־λ
		if(ZB_Dir_flag==1)
		{
			if(Ang_To_Arr_ZB(ZB_Lim)>ZB_Runed)  //����ʱ���Ƚ�ֵΪ���м���װ��ֵ��У׼��ĵ���װ��ֵ�Ĳ�ֵ��������ֵ����Ϊ0
			{
				direct=1;			//�������з����־
				if(ZB_Flag==0)
				{
					ZB_Flag=1;		//����״̬��־λ
					W25QXX_Write((u8*)&ZB_Flag,35,1);		//��״̬��־λд��flash
					delay_ms(200);
					u2_printf("ZB_flag==1");
					delay_ms(200);
					u2_printf("HLZBKS");
					delay_ms(200);
					u2_printf("CT_ZB1");
					delay_ms(200);
				}
				MotorStart(1,1,0,0);      //֧������
				u2_printf("*%s*M1*Z*/*/**",RX_BUF);		//����2����
				TIM10_Init(Ang_To_Arr_ZB(ZB_Lim)-ZB_Runed,65000);	   //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
			}
		}
		if(ZB_Dir_flag==0)
		{
			if(ZB_Runed>0)    //����ʱ���Ƚ�ֵΪУ׼��ĵ���װ��ֵ��0,�Ҳ���Ϊ0
			{
				direct=0;			//�������з����־
				if(zbjx_flag==1)
				{
					zbjx_flag=0;			//���ü���״̬��־λ
					u2_printf("CT_ZB20");
					delay_ms(200);
				}
				MotorStart(1,0,0,0);								//֧������
				u2_printf("*%s*M1*F*/*/**",RX_BUF);		//����2����
				TIM10_Init(ZB_Runed,65000);		   //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
			}
		}				
		
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//��մ���2��������		
		USART2_RX_LEN=0; 			//����2״̬����
		memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//��մ���4��������		
		UART4_RX_LEN=0;				  //����4״̬����
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);             //����жϱ�־λ	 	
		
		if(((ZB_Runed!=Ang_To_Arr_ZB(ZB_Lim))&&(1==direct))||((0!=ZB_Runed)&&(0==direct)))
		{
			while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))  //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ�� 
			{			
				
				//ָֹͣ��
				if(USART2_RX_LEN&0x8000)
				{
					len=USART2_RX_LEN&0x3fff;	//��ȡ����2���������ַ�����				
					USART2_RX_BUF[len]=0;			//����2����ĩβ��"0"
					if((strstr((const char *)USART2_RX_BUF,(const char *)"STOP"))||
						(strstr((const char *)USART2_RX_BUF,(const char *)"HLZB"))||
						(strstr((const char *)USART2_RX_BUF,(const char *)"BackGB")))   //�����յ�Stop,������ѭ��	
					{
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);//��մ���2��������			
						USART2_RX_LEN=0;			//����2״̬����
						break;
					}
					else 
					{
						u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���								
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);		//��մ���2��������	
						USART2_RX_LEN=0;			//����2״̬����
					}						
				}
				if(UART4_RX_LEN&0x8000)
				{
					len=UART4_RX_LEN&0x3fff;		//��ȡ����4���������ַ�����			
					UART4_RX_BUF[len]=0;				//����4����ĩβ��"0"
					if((strstr((const char *)UART4_RX_BUF,(const char *)"STOP"))||
						(strstr((const char *)UART4_RX_BUF,(const char *)"HLZB"))||
						(strstr((const char *)UART4_RX_BUF,(const char *)"BackGB")))   //�����յ�Stop,������ѭ��	
					{
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//��մ���4��������		
						UART4_RX_LEN=0;				  //����4״̬����
						break;
					}
					if(strstr((const char *)UART4_RX_BUF,(const char *)"SEND OK"))
					{	}
					else 
					{
						u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���								
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//��մ���4��������		
						UART4_RX_LEN=0;				  //����4״̬����
					}						
				}
				//����ͼƬָ��
				 arr_send=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//��ȡ��ǰ�Ĵ�������װ��ֵ
				if(direct==1)
				{
					j=(ZB_Runed+arr_send)/(Ang_To_Arr_ZB(ZB_Lim)/19);		//ͼƬ��ż���
				}
				else
				{
					j=abs(ZB_Runed,arr_send)/(Ang_To_Arr_ZB(ZB_Lim)/19);		//ͼƬ��ż���
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
							u2_printf("CT_ZB%d",ZB_Pic);		//����2���Ͷ���ͼƬָ��	
						}							
					}				
				}							
			}
			MotorStop(1);          //���ֹͣ
			u2_printf("*%s*M1*T*/*/**",RX_BUF);		//����2����
			TIM10_Stop();          //�رն�ʱ��
			//�жϸ�λ
			if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))&&(direct==0))   //�ж��Ƿ��ڸ�λ״̬����λ״̬��ǰ�������еĶ�ʱ������
			{				
				arr_now=0;         //��ʱ���ڸ�λ״̬����״ֵ̬����Ϊ0��
				ZB_Flag=0;				//����״̬��־λ
				W25QXX_Write((u8*)&ZB_Flag,35,1);		//��״̬��־λд��flash
				delay_ms(200);
				u2_printf("ZB_flag==0");
			}		
			else
			{
				arr_now=__HAL_TIM_GET_COUNTER(&TIM10_Handler);    //��ȡ��ǰ����ֵarr_now				
				ZB_Flag=1;					//����״̬��־λ				 
			}	
			//ͨ���������ж������ۼ�
			if(	direct==1)        //�����֧�����У�����+
			{
				if(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))
				{  
					ZB_Runed=Ang_To_Arr_ZB(ZB_Lim); 				//��������������ֵΪ����ֵ
					zbjx_flag=1; 	//���ü���״̬��־λ
					delay_ms(200);
					u2_printf("CT_ZB20");		
					delay_ms(200);
					u2_printf("HLZBJX");
				}
				else
				{  ZB_Runed=ZB_Runed+arr_now;	}					//��������������ֵ=��һ����������ֵ+�˴���������ֵ	
			}
			else                //�����֧�����У�����-
			{
				if(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))
				{	
					ZB_Runed=0;				//����������ֵ��Ϊ0
					delay_ms(200);
					u2_printf("CT_ZB1"); 
					delay_ms(200);
					u2_printf("HLZBFW");					
				}
				else
				{
					ZB_Runed=ZB_Runed-arr_now;		//��������������ֵ=��һ����������ֵ-�˴���������ֵ
				}						
			}
			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ	 								
		}
	}
	else
	{
		LedAlm(100,"HLZBGS");
	}	
}

/***********************************************************************
 ������      ��Fun_HL_ZF(void)  
 ��������    ����������
 ����        ����
 ���        ����
                           
************************************************************************/
void Fun_HL_ZF(void)
{
	u8 direct,key;
	u16 arr_now;              //��ǰһ�����������������������ۼ�
	u8 len;                   //���ܵ��ַ�������
	static u8 motor5_run_flag;   //�ж�С�෭�Ƿ��Ѿ���������������λ��1 

	//ʵ����λ��ʵʱ��ʾ������ǰ�˶�״̬     
	static u8 M345_Start;     //345����ӳ�ʼλ���˶�
	static u8 M345_End;       //345������е��ϼ���λ�ñ�־λ  
	static u8 k=0,m=0;
	u8 mn;
	u8 kj;
	u8 j=0,n=0;
	u16 arr_send,arr_send1;	 //��ǰһ������������	
	strcpy((char *)RX_BUF,(const char *)"HLZF");
	//�������ܣ�ֻ����֧�����������ȡ����㡢���Ӹ�λ�󣬲���ִ��������
	if((SD_Flag==1)&&(ZB_Flag==0)&&(YF_Flag==0)&&(SQT_Flag==0)&&(XQT_Flag==0)&&(ZBQ_Flag==0)&&(YL_Flag==0)&&(ZBH_Flag==0)&&(ZYH_Flag==0))
	{					
		if(ZF_Flag==0)   //�����λ����ʼ״̬����ִ��С�෭����
		{
			if((strstr((const char *)USART2_RX_BUF,(const char *)"HLZF"))||(strstr((const char *)USART2_RX_BUF,(const char *)"BodyLeftGB"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"HLZF"))||(strstr((const char *)UART4_RX_BUF,(const char *)"BodyLeftGB")))
			{
				//5�Ų෭��	
				memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			//��մ���2��������
				USART2_RX_LEN=0;			//����2״̬����
				memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//��մ���4��������		
				UART4_RX_LEN=0;				  //����4״̬����
				delay_ms(200);
				u2_printf("HLZFKS");
				delay_ms(200);
				u2_printf("ZF_flag=1");				
				delay_ms(200);
				u2_printf("CT_ZCF1");
				delay_ms(200);
			  motor5_run_flag=1;		//����״̬��־λ		
				ZF_Flag=1;		//����״̬��־λ
				W25QXX_Write((u8*)&ZF_Flag,33,1);					//��״̬��־λд��flash	
				MotorStart(5,1,1400-1,25-1);	         			 //5�ŵ������
				u2_printf("*%s*M5*Z*0*/**",RX_BUF);		//����2����
				TIM10_Init(Ang_To_Arr_ZYFS(ZF_Lim),65000);     //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
				__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);               //����жϱ�־λ
				while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) )
				{					
					//�����λ
					if((0==GD5_ZFZZ)&&(1==ZF_Flag))  //����ʱ������翪�أ�����ѭ�� 
					{			   										
						delay_us(100);
						if(0==GD5_ZFZZ)
						{
							u2_printf("GD5ZFZZ");
							break;			
						}								
					}
					  //�ж���û���յ���λ��ָ��		
					if(USART2_RX_LEN&0x8000)
					{
						u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���	
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//��մ���2��������		
						USART2_RX_LEN=0;			 //����2״̬����												
					}
					if(UART4_RX_LEN&0x8000)
					{
						u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���	
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//��մ���4��������		
						UART4_RX_LEN=0;							  //����4״̬����									
					}
					//������ϡ��������
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
					//����ͼƬָ��
					arr_send1=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//��ȡ��ǰ�Ĵ�������װ��ֵ
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
								u2_printf("CT_ZCF%d",ZCF_Pic);			//����2���Ͷ���ͼƬָ��
							}								
						}
					}					
				}					      
				MotorStop(5);         //���ֹͣ
				u2_printf("*%s*M5*T*0*/**",RX_BUF);		//����2����
				TIM10_Stop();         //��ʱ���ر�
				__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //����жϱ�־λ
				delay_ms(200);
				u2_printf("CT_ZCF10");
				delay_ms(200);
				Motor4_BC(0,1400,1400-1,25-1);//���ò�������
			}	
		}
	
		//����345�������	
		if(1==ZF_Flag)
		{
			ZF_Dir_flag=!ZF_Dir_flag;		//����״̬��־λ
			if(ZF_Dir_flag==1)    //����
			{				
				if(Ang_To_Arr_ZYFS(ZF_Lim)>ZF_Runed)
				{
				   //345��������				
					 direct=1;			//�������з����־
					 if(M345_Start==0)
					 {
						 M345_Start=1;
						 u2_printf("CT_ZF1");
						 delay_ms(200);
					 }
					MotorStart(3,0,1400-1,25-1);	     //3�ŵ������			
					MotorStart(4,0,(1400-1)*1.2,25-1); //4�ŵ������
					MotorStart(5,0,1400-1,25-1);			 //5�ŵ������
					if(1==motor5_run_flag)
					{
						motor5_run_flag=0;		//����״̬��־λ
						u2_printf("*M5JS*M345*ZZZ*000*/**");		//����2����
					}
					else
					{
						u2_printf("*%s*M345*ZZZ*000*/**",RX_BUF);		//����2����
					}
					TIM10_Init(Ang_To_Arr_ZYFS(ZF_Lim)-ZF_Runed,65000);	   //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz							 
				}
			}
			else          //����
			{				
				if(ZF_Runed>0)
				{
				   //345��������
				   direct=0;			//�������з����־
					if(M345_End==1)
					 {
						 M345_End=0;
						 u2_printf("CT_ZF8");
						 delay_ms(200);
					 }
					MotorStart(3,1,1400-1,25-1);	     //3�ŵ������
					MotorStart(4,1,(1400-1)*1.2,25-1);		 //4�ŵ������	
					MotorStart(5,1,1400-1,25-1);			 //5�ŵ������	
					u2_printf("*%s*M345*FFF*000*/**",RX_BUF);		//����2����
				   TIM10_Init(ZF_Runed,65000);	             //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz		
				} 
			}
		}
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			//��մ���2��������
		USART2_RX_LEN=0;			 //����2״̬����
		memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);				//��մ���4��������	
		UART4_RX_LEN=0;				  //����4״̬����
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);              //����жϱ�־λ
		
		if(((ZF_Runed!=Ang_To_Arr_ZYFS(ZF_Lim))&&(1==direct))||((0!=ZF_Runed)&&(0==direct)))
		{			
			while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))   //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��
			{
				//�����λ
				if(((0==GD3_CS)||(0==GD4_CS))&&(0==direct))   //���������翪�أ�����ѭ����ֹͣ����
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
				if(((0==GD3_ZFZZ)||(0==GD4_ZFZZ))&&(1==direct))   //���������翪�أ�����ѭ����ֹͣ����
				{
					delay_us(100);
					if((0==GD3_ZFZZ)||(0==GD4_ZFZZ))          //���������翪�أ�����ѭ����ֹͣ����
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
				//ָֹͣ��
				if(USART2_RX_LEN&0x8000)
				{
					len=USART2_RX_LEN&0x3fff;		//��ȡ����2���������ַ�����			
					USART2_RX_BUF[len]=0;			//����2����ĩβ��"0"
					if((strstr((const char *)USART2_RX_BUF,(const char *)"BodyLeftGB"))||
						(strstr((const char *)USART2_RX_BUF,(const char *)"STOP"))||
							(strstr((const char *)USART2_RX_BUF,(const char *)"HLZF")))  //�����յ�Stop,������ѭ��	
					{
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//��մ���2��������		
						USART2_RX_LEN=0; 			//����2״̬����
						break;
					} 
					else 
					{
						u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���	
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//��մ���2��������		
						USART2_RX_LEN=0;			//����2״̬����
					}												
				}
				if(UART4_RX_LEN&0x8000)
				{
					len=UART4_RX_LEN&0x3fff;		//��ȡ����4���������ַ�����			
					UART4_RX_BUF[len]=0;				//����4����ĩβ��"0"
					if((strstr((const char *)UART4_RX_BUF,(const char *)"BodyLeftGB"))||
						(strstr((const char *)UART4_RX_BUF,(const char *)"STOP"))||
							(strstr((const char *)UART4_RX_BUF,(const char *)"HLZB")))  //�����յ�Stop,������ѭ��	
					{
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//��մ���4��������		
						UART4_RX_LEN=0;				  //����4״̬����
						break;
					} 
					if(strstr((const char *)UART4_RX_BUF,(const char *)"SEND OK"))
					{	}
					else 
					{
						u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���	
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);				//��մ���4��������	
						UART4_RX_LEN=0;				  //����4״̬����
					}												
				}
				//������ϡ��������
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
				//���Ͷ���ָ��
				arr_send=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//��ȡ��ǰ�Ĵ�������װ��ֵ
				if(direct==1)
				{
					j=(ZF_Runed+arr_send)/(Ang_To_Arr_ZYFS(ZF_Lim)/7);		//ͼƬ��ż���
				}
				else
				{
					j=abs(ZF_Runed,arr_send)/(Ang_To_Arr_ZYFS(ZF_Lim)/7);		//ͼƬ��ż���
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
							u2_printf("CT_ZF%d",ZF_Pic);		//����2���Ͷ���ͼƬָ��	
						}							
					}				
				}					
			}	
			//���ֹͣ
			MotorStop(3);   
			MotorStop(4);  
			MotorStop(5);   
			u2_printf("*%s*M345*TTT*000*/**",RX_BUF);		//����2����
			TIM10_Stop();         //��ʱ���ر�
			//�жϸ�λ
			if(((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))||(0==GD3_CS)||(0==GD4_CS))&&(direct==0))  //�ж��Ƿ񵽴︴λ״̬
			{
				arr_now=0; 		 //��ʱ���ڸ�λ״̬����״ֵ̬����Ϊ0��
				ZF_Flag=0;		//����״̬��־λ
			}					
			else
			{					
				arr_now=__HAL_TIM_GET_COUNTER(&TIM10_Handler);      //��ȡ��ǰ����ֵarr_now	
			}
			//ͨ���������ж������ۼ�
			if(direct==1)       //���У�����+
			{
				if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))||(0==GD3_ZFZZ)||(0==GD4_ZFZZ))  //�������е�����λ��
				{
					ZF_Runed=Ang_To_Arr_ZYFS(ZF_Lim);					//��������������ֵΪ����ֵ				
					M345_End=1;	 										
					delay_ms(200);
					u2_printf("CT_ZF8");
					delay_ms(200);
					u2_printf("HLZFJX");
				}
				else
				{
					ZF_Runed=ZF_Runed+arr_now;		//��������������ֵ=��һ����������ֵ+�˴���������ֵ
				}		
			}	
			else                //���У�����-
			{
				if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))||(0==GD3_CS)||(0==GD4_CS))      //�������е�����λ��
				{						
					ZF_Runed=0;			//����������ֵ��Ϊ0
					M345_Start=0;											
					delay_ms(200);
					u2_printf("CT_ZF1");
				}
				else
				{
					ZF_Runed=ZF_Runed-arr_now;			//��������������ֵ=��һ����������ֵ-�˴���������ֵ
				}
			}					
			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);        //����жϱ�־λ
			
			//����ʱʱ�䵽���ǹ��û��������������һ�ξ��룬�����翪��λ�ã���翪�ذ�װ��򿪴˶Σ��������������ж�ɾ����
//			if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))&&((1==GD3_CS)||(1==GD4_CS))&&(direct==0)&&(ZF_Flag==1))
//			{   			
//				if((1==GD3_CS)&&(0==GD4_CS))        //���3û��λ
//				{
//					MotorStart(3,1,1400-1,25-1);       //3�ŵ������
//					u2_printf("*%s*M3*F*0*/**",RX_BUF);
//					TIM10_Init(add_arr,65000);                    //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //����жϱ�־λ	 	
//					while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))
//					{			
//						if(0==GD3_CS)  //����ʱ������翪�أ�����ѭ�� 
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
//					MotorStop(3);         //���ֹͣ
//					u2_printf("*%s*M3*T*0*/**",RX_BUF);
//					TIM10_Stop();         //��ʱ���ر�
//					if(0==GD3_CS)
//					{
//						u2_printf("*%s*GD3CS*/*0*/**",RX_BUF);
//					}
//					else
//					{
//						u2_printf("*%s*GD3CS*/*1*/**",RX_BUF);
//					}
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //����жϱ�־λ
//				}
//				if((0==GD3_CS)&&(1==GD4_CS))   //���4û��λ
//				{
//					MotorStart(4,1,1400-1,25-1);  		 //4�ŵ������
//					u2_printf("*%s*M4*F*0*/**",RX_BUF);
//					TIM10_Init(add_arr,65000);              //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //����жϱ�־λ	 	
//					while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))
//					{			
//						if(0==GD4_CS)  //����ʱ������翪�أ�����ѭ�� 
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
//					MotorStop(4);     //���ֹͣ
//					u2_printf("*%s*M4*T*0*/**",RX_BUF);
//					TIM10_Stop();     //��ʱ���ر�
//					if(0==GD4_CS)
//					{
//						u2_printf("*%s*GD4CS*/*0*/**",RX_BUF);
//					}
//					else
//					{
//						u2_printf("*%s*GD4CS*/*1*/**",RX_BUF);
//					}
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //����жϱ�־λ				
//				}
//				if((1==GD3_CS)&&(1==GD4_CS))   //���3��4��û��λ
//				{
//					MotorStart(3,1,(1400-1),25-1);     //3�ŵ������
//					MotorStart(4,1,(1400-1)*1.2,25-1);		 //4�ŵ������
//					MotorStart(5,1,1400-1,25-1);			 //5�ŵ������
//					u2_printf("*%s*M345*FFF*000*/**",RX_BUF);
//					TIM10_Init(add_arr,65000);                //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //����жϱ�־λ	 	
//					while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))
//					{			
//						if((0==GD3_CS)||(0==GD4_CS))  //����ʱ������翪�أ�����ѭ�� 
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
//					MotorStop(3);    //���ֹͣ
//					MotorStop(4);
//					MotorStop(5);
//					u2_printf("*%s*M345*TTT*000*/**",RX_BUF);
//					TIM10_Stop();    //��ʱ���ر�
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
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ	
//				}
//			}
			//�෭��λ
			if((ZF_Flag==0)&&(0==direct))     //345������λ����ʼ״̬���Ÿ�λ5�ŵ��
			{			
				//5�Ų෭��λ
				memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//��մ���2��������		
				USART2_RX_LEN=0;			//����2״̬����
				memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//��մ���4��������		
				UART4_RX_LEN=0;				  //����4״̬����
//				Motor4_BC(1,1400,1400-1,25-1);//���ò�������	
				ZF_Runed=0;				//����������ֵ��Ϊ0
				delay_ms(200);
				u2_printf("CT_ZCF10");
				delay_ms(200);
				MotorStart(5,0,1400-1,25-1);         			 //5�ŵ������
				u2_printf("*%s*M5*F*0*/**",RX_BUF);					//����2����
				TIM10_Init(Ang_To_Arr_ZYFS(ZF_Lim),65000);    //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
				__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);              //����жϱ�־λ
				while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) )
				{				
					//�����λ
					if((0==GD5_CS)&&(0==ZF_Flag))    //������翪������ѭ�������ͣת 
					{								
						delay_us(100);
						if(0==GD5_CS)
						{
							u2_printf("GD5CS");
							break;			
						}								
					}
					  //�ж���û���յ���λ��ָ��		
					if(USART2_RX_LEN&0x8000)
					{
						u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���	
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//��մ���2��������		
						USART2_RX_LEN=0;					//����2״̬����										
					}	
					if(UART4_RX_LEN&0x8000)
					{
						u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���	
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//��մ���4��������			
						UART4_RX_LEN=0;							  //����4״̬����									
					}
					//������ϡ��������
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
					//���Ͷ���ָ��
					arr_send1=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//��ȡ��ǰ�Ĵ�������װ��ֵ
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
							u2_printf("CT_ZCF%d",ZCF_Pic);		//����2���Ͷ���ͼƬָ��
							}								
						}				
					}	
				}      
				MotorStop(5);       //���ֹͣ
				u2_printf("*%s*M5*T*0*/**",RX_BUF);		//����2����
				TIM10_Stop();       //��ʱ���ر�
				__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //����жϱ�־λ
				ZF_Flag=0;		//����״̬��־λ
				W25QXX_Write((u8*)&ZF_Flag,33,1);		//��״̬��־λд��flash
				delay_ms(200);
				u2_printf("CT_ZCF1");
				delay_ms(200);
				u2_printf("ZF_flag==0");				
				delay_ms(200);
				u2_printf("HLZFFW");
				//����ʱʱ�䵽���ǹ��û��������������һ�ξ��룬�����翪��λ�ã���翪�ذ�װ��򿪴˶Σ��������������ж�ɾ����
//				if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))&&(1==GD5_CS)&&(direct==0)&&(0==ZF_Flag))
//				{
//					MotorStart(5,0,1400-1,25-1);			 //5�ŵ������
//					u2_printf("*%s*M5*F*0*/**",RX_BUF);
//					TIM10_Init(add_arr,65000);   //�򿪶�ʱ��
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ	 	
//					while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))
//					{			
//						if(0==GD5_CS)  //����ʱ������翪�أ�����ѭ�� 
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
//					TIM10_Stop();       //��ʱ���ر�
//					if(0==GD5_CS)
//					{
//						u2_printf("*%s*GD5CS*/*0*/**",RX_BUF);
//					}
//					else
//					{
//						u2_printf("*%s*GD5CS*/*1*/**",RX_BUF);
//					}
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ	
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
 ������      ��Fun_HL_YF(void)  
 ��������    �������ҷ���
 ����        ����
 ���        ����
                           
************************************************************************/
void Fun_HL_YF(void)
{
	u8 direct,key;
	u16 arr_now;              //��ǰһ�����������������������ۼ�
	u8 len;                   //���յ��ַ�������
	static u8 motor5_run_flag;   //�ж�С�෭�Ƿ��Ѿ���������������λ��1 
	//ʵ����λ��ʵʱ��ʾ������ǰ�˶�״̬
	static u8 k=0,m=0;
	static u8 M345R_Start;    //345����ӳ�ʼλ������
	static u8 M345R_End;      //345������е��ϼ���λ��
	u8 mn;
	u8 kj;
	u8 j=0,n=0;
	u16 arr_send,arr_send1;	  //��ǰһ������������	
	strcpy((char *)RX_BUF,(const char *)"HLYF");
	//�������ܣ�ֻ����֧�����������ȡ����㡢���Ӹ�λ�󣬲���ִ���ҷ�����
	if((SD_Flag==1)&&(ZB_Flag==0)&&(ZF_Flag==0)&&(SQT_Flag==0)&&(XQT_Flag==0)&&(ZBQ_Flag==0)&&(YL_Flag==0)&&(YBH_Flag==0)&&(YYH_Flag==0))
	{			
		if(YF_Flag==0)   //�����λ����ʼ״̬����ִ������
		{
			if((strstr((const char *)USART2_RX_BUF,(const char *)"BodyRightGB"))||(strstr((const char *)USART2_RX_BUF,(const char *)"HLYF"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"BodyRightGB"))||(strstr((const char *)UART4_RX_BUF,(const char *)"HLYF")))
			{
			  //5�Ų෭��
				memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//��մ���2��������		
				USART2_RX_LEN=0;		 	//����2״̬����
				memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//��մ���4��������			
				UART4_RX_LEN=0;				  //����4״̬����
				delay_ms(200);
				u2_printf("HLYFKS");
				delay_ms(200);
				u2_printf("YF_flag==1");
				delay_ms(200);
				u2_printf("CT_YCF1");
				delay_ms(200);
				motor5_run_flag=1;		//����״̬��־λ
				YF_Flag=1;		//����״̬��־λ
				W25QXX_Write((u8*)&YF_Flag,34,1);					//��״̬��־λд��flash
				MotorStart(5,0,1400-1,25-1);	       			 //5�ŵ������
				u2_printf("*%s*M5*Z*0*/**",RX_BUF);		//����2����
				TIM10_Init(Ang_To_Arr_ZYFS(YF_Lim),65000);    //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	                   //�򿪶�ʱ��
				__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);               //����жϱ�־λ
				while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) )
				{					
					//�����λ
					if((0==GD5_YFZZ)&&(1==YF_Flag))                      //����ʱ������翪�أ�����ѭ�� 
					{			   										
						delay_us(100);
						if(0==GD5_YFZZ)
						{
							u2_printf("GD5YFZZ");
							break;		
						}								
					}
					  //�ж���û���յ���λ��ָ��		
					if(USART2_RX_LEN&0x8000)
					{
						u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���	
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);//��մ���2��������			
						USART2_RX_LEN=0;								//����2״̬����							
					}
					if(UART4_RX_LEN&0x8000)
					{
						u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���	
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//��մ���4��������		
						UART4_RX_LEN=0;						  //����4״̬����										
					}
					//������ϡ��������
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
					//����ͼƬָ��
					arr_send1=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//��ȡ��ǰ�Ĵ�������װ��ֵ
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
								u2_printf("CT_YCF%d",YCF_Pic);		//����2���Ͷ���ͼƬָ��
							}								
						}					
					}		
				}						      
				MotorStop(5);          //���ֹͣ
				u2_printf("*%s*M5*T*0*/**",RX_BUF);		//����2����
				TIM10_Stop();          //��ʱ���ر�
				__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //����жϱ�־λ
				delay_ms(200);
				u2_printf("CT_YCF10");
				delay_ms(200);
				Motor4_BC(1,3200,1400-1,25-1);//���ò�������
			}	
		}

		//����345�������	
		if(1==YF_Flag)
		{
			YF_Dir_flag=!YF_Dir_flag;		//����״̬��־λ
			if(YF_Dir_flag==1)
			{				
				if(Ang_To_Arr_ZYFS(YF_Lim)>YF_Runed)
				{
				   //345��������		
				   direct=1;			//�������з����־
				   if(M345R_Start==0)
				   {
					   M345R_Start=1;	
					   delay_ms(200);
					   u2_printf("CT_YF1");
					   delay_ms(200);
				   }
					MotorStart(3,1,(1400-1)*2,25-1);	     //3�ŵ������
					MotorStart(4,1,(1400-1)*0.8,25-1);		 //4�ŵ������	
					MotorStart(5,1,1400-1,25-1);			 		//5�ŵ������
					if(1==motor5_run_flag)
					{
						motor5_run_flag=0;		//����״̬��־λ
						u2_printf("*M5JS*M345*ZZZ*000*/**");		//����2����
					}
					else
					{
						u2_printf("*%s*M345*ZZZ*000*/**",RX_BUF);		//����2����
					}					
				   TIM10_Init(Ang_To_Arr_ZYFS(ZF_Lim)-ZF_Runed,65000);   //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
				}
			}
			else
			{				
				if(YF_Runed>0)
				{
				   //345��������
				   direct=0;			//�������з����־
				   if(M345R_End==1)
				   {
						M345R_End=0;
						delay_ms(200);
					    u2_printf("CT_YF8");	
					    delay_ms(200);
					}
					MotorStart(3,0,(1400-1)*2,25-1);	     //3�ŵ������
					MotorStart(4,0,(1400-1)*0.8,25-1);		 //4�ŵ������	
					MotorStart(5,0,1400-1,25-1);					 //5�ŵ������
					u2_printf("*%s*M345*FFF*000*/**",RX_BUF);		//����2����
				   TIM10_Init(YF_Runed,65000);	        //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz		
				}
			}
		}
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			//��մ���2��������
		USART2_RX_LEN=0;			//����2״̬����
		memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//��մ���4��������		
		UART4_RX_LEN=0;				  //����4״̬����
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);         //����жϱ�־λ		
		if(((YF_Runed!=Ang_To_Arr_ZYFS(YF_Lim))&&(1==direct))||((0!=YF_Runed)&&(0==direct)))
		{
			while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))  //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��
			{			
				//�����λ
				if(((0==GD3_CS)||(0==GD4_CS))&&(0==direct))   //���������翪�أ�����ѭ����ֹͣ����
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
				if(((0==GD3_YFZZ)||(0==GD4_YFZZ))&&(1==direct))           //���������翪�أ�����ѭ����ֹͣ����
				{
					delay_us(100);
					if((0==GD3_YFZZ)||(0==GD4_YFZZ))          //���������翪�أ�����ѭ����ֹͣ����
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
				//ָֹͣ��
				if(USART2_RX_LEN&0x8000)
				{
					len=USART2_RX_LEN&0x3fff;		//��ȡ����2���������ַ�����			
					USART2_RX_BUF[len]=0;			//����2����ĩβ��"0"
					if((strstr((const char *)USART2_RX_BUF,(const char *)"BodyRightGB"))||
						(strstr((const char *)USART2_RX_BUF,(const char *)"STOP"))||
							(strstr((const char *)USART2_RX_BUF,(const char *)"HLYF")))    //�����յ�Stop,������ѭ��	
					{
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//��մ���2��������		
						USART2_RX_LEN=0;			//����2״̬����
						break;
					} 
					else 
					{
						u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���	
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//��մ���2��������		
						USART2_RX_LEN=0;			//����2״̬����
					}
				}
				if(UART4_RX_LEN&0x8000)
				{
					len=UART4_RX_LEN&0x3fff;			//��ȡ����4���������ַ�����		
					UART4_RX_BUF[len]=0;				//����4����ĩβ��"0"
					if((strstr((const char *)UART4_RX_BUF,(const char *)"BodyRightGB"))||
						(strstr((const char *)UART4_RX_BUF,(const char *)"STOP"))||
							(strstr((const char *)UART4_RX_BUF,(const char *)"HLYF")))    //�����յ�Stop,������ѭ��	
					{
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//��մ���4��������		
						UART4_RX_LEN=0;				  //����4״̬����
						break;
					} 
					if(strstr((const char *)UART4_RX_BUF,(const char *)"SEND OK"))
					{	}
					else 
					{
						u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���	
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//��մ���4��������		
						UART4_RX_LEN=0;				  //����4״̬����
					}
				}
				//������ϡ��������
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
				//���Ͷ���ָ��
				 arr_send=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//��ȡ��ǰ�Ĵ�������װ��ֵ
				if(direct==1)
				{
					j=(YF_Runed+arr_send)/(Ang_To_Arr_ZYFS(YF_Lim)/7);		//ͼƬ��ż���
				}
				else
				{
					j=abs(YF_Runed,arr_send)/(Ang_To_Arr_ZYFS(YF_Lim)/7);		//ͼƬ��ż���
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
							u2_printf("CT_YF%d",YF_Pic);			//����2���Ͷ���ͼƬָ��
						}							
					}				
				}							
			}
			//���ֹͣ
			MotorStop(3);   
			MotorStop(4);   
			MotorStop(5);   
			u2_printf("*%s*M345*TTT*000*/**",RX_BUF);		//����2����
			TIM10_Stop();         //��ʱ���ر�
			//�жϸ�λ
			if(((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))||(0==GD3_CS)||(0==GD4_CS))&&(direct==0))  //�ж��Ƿ񵽴︴λ״̬
			{
				arr_now=0;     		//��ʱ���ڸ�λ״̬����״ֵ̬����Ϊ0��
				YF_Flag=0;		//����״̬��־λ
			}			
			else
			{					
				arr_now=__HAL_TIM_GET_COUNTER(&TIM10_Handler);         //��ȡ��ǰ����ֵarr_now	
			}
			//ͨ���������ж������ۼ�
			if(direct==1)      //���У�����+
			{ 
				if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))||(0==GD3_YFZZ)||(0==GD4_YFZZ)) //�������е�����λ��
				{
					YF_Runed=Ang_To_Arr_ZYFS(YF_Lim);				//��������������ֵΪ����ֵ
					M345R_End=1;    								
					delay_ms(200);
					u2_printf("CT_YF8");
					delay_ms(200);
					u2_printf("HLYFJX");
				}
				else
				{
					YF_Runed=YF_Runed+arr_now;		//��������������ֵ=��һ����������ֵ+�˴���������ֵ
				}		
			}	
			else              //���У�����-
			{
				if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))||(0==GD3_CS)||(0==GD4_CS))   //�������е�����λ��
				{
					YF_Runed=0;				//����������ֵ��Ϊ0
					M345R_Start=0;  								
					delay_ms(200);
					u2_printf("CT_YF1");
				}
				else
				{
					YF_Runed=YF_Runed-arr_now;		//��������������ֵ=��һ����������ֵ-�˴���������ֵ	
				}
			}					
			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);       //����жϱ�־λ
//		//����ʱʱ�䵽���ǹ��û��������������һ�ξ��룬�����翪��λ�ã���翪�ذ�װ��򿪴˶Σ�
//			if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))&&((1==GD3_CS)||(1==GD4_CS))&&(direct==0)&&(YF_Flag==1))
//			{   			
//				if((1==GD3_CS)&&(0==GD4_CS))   //���3û��λ
//				{
//					MotorStart(3,0,1400-1,25-1);        //3�ŵ������
//					u2_printf("*%s*M3*F*0*/**",RX_BUF);
//					TIM10_Init(add_arr,65000);               //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //����жϱ�־λ	 	
//					while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))
//					{			
//						if(0==GD3_CS)  //����ʱ������翪�أ�����ѭ�� 
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
//					MotorStop(3);    //���ֹͣ
//					u2_printf("*%s*M3*T*0*/**",RX_BUF);
//					TIM10_Stop();       //��ʱ���ر�
//					if(0==GD3_CS)
//					{
//						u2_printf("*%s*GD3CS*/*0*/**",RX_BUF);
//					}
//					else
//					{
//						u2_printf("*%s*GD3CS*/*1*/**",RX_BUF);
//					}
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ
//				}
//				if((0==GD3_CS)&&(1==GD4_CS))   //���4û��λ
//				{
//					MotorStart(4,0,1400-1,25-1); 		 //4�ŵ������
//					u2_printf("*%s*M4*F*0*/**",RX_BUF);
//					TIM10_Init(add_arr,65000);                //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //����жϱ�־λ	 	
//					while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))
//					{			
//						if(0==GD4_CS)  //����ʱ������翪�أ�����ѭ�� 
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
//					MotorStop(4);       //���ֹͣ
//					u2_printf("*%s*M4*T*0*/**",RX_BUF);
//					TIM10_Stop();       //��ʱ���ر�
//					if(0==GD4_CS)
//					{
//						u2_printf("*%s**GD4CS*/*0*/**",RX_BUF);
//					}
//					else
//					{
//						u2_printf("*%s*GD4CS*/*1*/**",RX_BUF);
//					}
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //����жϱ�־λ				
//				}
//				if((1==GD3_CS)&&(1==GD4_CS))   //���3/4��û��λ
//				{				
//					MotorStart(3,0,(1400-1)*2.0,25-1);     //3�ŵ������
//					MotorStart(4,0,(1400-1)*0.8,25-1);		 //4�ŵ������
//					MotorStart(5,0,1400-1,25-1);			 //5�ŵ������
//					u2_printf("*%s*M345*FFF*000*/**",RX_BUF);
//					TIM10_Init(add_arr,65000);                   //�򿪶�ʱ��
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //����жϱ�־λ	 	
//					while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))
//					{			
//						if((0==GD3_CS)||(0==GD4_CS))  //����ʱ������翪�أ�����ѭ�� 
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
//					MotorStop(3);      //���ֹͣ
//					MotorStop(4);
//					MotorStop(5);
//					u2_printf("*%s*M345*TTT*000*/**",RX_BUF);
//					TIM10_Stop();       //��ʱ���ر�
//					if((1==GD3_CS)||(1==GD4_CS))  //����ʱ������翪�أ�����ѭ�� 
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
//					if((0==GD3_CS)||(0==GD4_CS))  //����ʱ������翪�أ�����ѭ�� 
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
//					__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ	
//				}
//			}
		//�෭��λ
		if((YF_Flag==0)&&(0==direct))     //345������λ����ʼ״̬���Ÿ�λ5�ŵ��
		{			
			//5�Ų෭��λ
			memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//��մ���2��������		
			USART2_RX_LEN=0;					//����2״̬����
			memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//��մ���4��������		
			UART4_RX_LEN=0;				  //����4״̬����
//			Motor4_BC(0,2800,1400-1,25-1);//���ò�������
			delay_ms(200);
			u2_printf("CT_YCF10");
			delay_ms(200);
			MotorStart(5,1,1400-1,25-1);  			 //5�ŵ������
			u2_printf("*%s*M5*F*0*/**",RX_BUF);		//����2����
			YF_Runed=0;			//����������ֵ��Ϊ0		
			TIM10_Init(Ang_To_Arr_ZYFS(YF_Lim),65000);        //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	                         //�򿪶�ʱ��
			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);          //����жϱ�־λ
			while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))   //�ȴ���ʱʱ�䵽��
			{							
				//�����λ
				if((0==GD5_CS)&&(0==YF_Flag))       //����ʱ������翪�أ�����ѭ�� 
				{			   										
					delay_us(100);
					if(0==GD5_CS)
					{	
						u2_printf("GD5CS");	
						break;		
					}							
				}
				  //�ж���û���յ���λ��ָ��		
				if(USART2_RX_LEN&0x8000)
				{
					u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���	
					memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);		//��մ���2��������	
					USART2_RX_LEN=0;					//����2״̬����											
				}	
				if(UART4_RX_LEN&0x8000)
				{
					u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���	
					memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);				//��մ���4��������	
					UART4_RX_LEN=0;							  //����4״̬����									
				}
				//������ϡ��������
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
				//���Ͷ���ָ��
				 arr_send1=__HAL_TIM_GET_COUNTER(&TIM10_Handler);					//��ȡ��ǰ�Ĵ�������װ��ֵ
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
							u2_printf("CT_YCF%d",YCF_Pic);		//����2���Ͷ���ͼƬָ��
						}							
					}				
				}	
			}      
			MotorStop(5);          //���ֹͣ
			u2_printf("*%s*M5*T*0*/**",RX_BUF);		//����2����
			TIM10_Stop();		   //��ʱ���ر�
			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //����жϱ�־λ
			YF_Flag=0;			//����״̬��־λ
			W25QXX_Write((u8*)&YF_Flag,34,1);		//��״̬��־λд��flash
			delay_ms(200);
			u2_printf("CT_YCF1");
		    delay_ms(200);
			u2_printf("YF_flag==0");			
		    delay_ms(200);
		    u2_printf("HLYFFW");
			//����ʱʱ�䵽���ǹ��û��������������һ�ξ��룬�����翪��λ�ã���翪�ذ�װ��򿪴˶Σ��������������ж�ɾ����
//			if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))&&(1==GD5_CS)&&(direct==0)&&(0==ZF_Flag))
//			{
//				MotorStart(5,1,1400-1,25-1);    			 //5�ŵ������
//				u2_printf("*%s*M5*F*0*/**",RX_BUF);
//				TIM10_Init(add_arr,65000);                   //�򿪶�ʱ��
//				__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //����жϱ�־λ	 	
//				while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))
//				{			
//					if(0==GD5_CS)  //����ʱ������翪�أ�����ѭ�� 
//					{
//						delay_us(100);
//						if(0==GD5_CS) 
//						{
//							u2_printf("GD5CS");
//							break;		
//						}							
//					}
//				}			
//				MotorStop(5);        //���ֹͣ
//				u2_printf("*%s*M5*T*0*/**",RX_BUF);
//				TIM10_Stop();		   //��ʱ���ر�
//				if(0==GD5_CS)
//				{
//					u2_printf("*%s*GD5CS*/*0*/**",RX_BUF);
//				}
//				else
//				{
//					u2_printf("*%s*GD5CS*/*1*/**",RX_BUF);
//				}					
//				__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ	
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
 ������      ��Fun_HL_BH(void)  
 ��������    ��������������
 ����        ����
 ���        ����
                           
************************************************************************/
void Fun_HL_BH(void)
{		
	if((SD_Flag==1)&&(1==ZF_Flag))  //�����ʱ��������������󱳲�����
	{
		strcpy((char *)RX_BUF,(const char *)"HLZBH");
		Fun_ZBH(); 
	}
	if((SD_Flag==1)&&(1==YF_Flag))//�����ʱ�����ҷ���������ұ�������
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
 ������      ��Fun_HL_BH(void)  
 ��������    ��������������
 ����        ����
 ���        ����
                           
************************************************************************/
void Fun_HL_YH(void)
{
	if((SD_Flag==1)&&(1==ZF_Flag))  //�����ʱ�����������������������
	{
		strcpy((char *)RX_BUF,(const char *)"HLZYH");
		Fun_ZYH(); 
	}
	if((SD_Flag==1)&&(1==YF_Flag))//�����ʱ�����ҷ������������������
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
 ������      ��Fun_HL_SD(void)  
 ��������    ��һ����������
 ����        ����
 ���        ����
                           
************************************************************************/
u8 Fun_HL_SD(void)
{	
	strcpy((char *)RX_BUF,(const char *)"HLSD");
	SD_Dir_flag=!SD_Dir_flag;		//����״̬��־λ
	
	if(SD_Dir_flag==1)
	{		
		SD_Flag=0;	//��������	
		u2_printf("*%s*SD*/*/*/**",RX_BUF);		//����2����
		delay_ms(200);
		u2_printf("HLSD");
		
	}
	else
	{
		SD_Flag=1;   //��������
		u2_printf("*%s*JS*/*/*/**",RX_BUF);		//����2����
		delay_ms(200); 
		u2_printf("HLJS");
	}
    return 	SD_Flag;
}

/***********************************************************************
 ������      ��Fun_ZDZBQ(void)   
 ��������    ������ִ���Զ�����������
 ����        ����
 ���        ���� 
                          
************************************************************************/
void Fun_ZDZBQ(void) 
{			
	//�������ܣ�ֻ���������ȡ����ҷ���λ�󣬲���ִ������������	
	if((0==ZF_Flag)&&(0==YF_Flag)) 
	{
		if(0==ZDZBQ_Flag)
		{		
			delay_ms(200);		
			u2_printf("ZDZBKS");
			delay_ms(200);
		}                         
		ZDZBQ_Dir_flag=!ZDZBQ_Dir_flag; 
		
		if((ZDZBQ_Dir_flag==1)&&(0==ZDZBQ_Flag)) //�Զ��������г�
		{
			u2_printf("ZDZBQ_flag==1");			 
			ZDZBQ_Flag=1;
			delay_ms(200);
			if((1==ZB_Flag)&&(0==XQT_Flag))      //��ʱ�Ѵ���֧��֧��״̬
			{
				MotorStart(2,1,0,0);             			//�����Ƹ�����
				u2_printf("*%s*M2*Z*/*/**",RX_BUF);		//����2����
				XQT_State=1;                     //��������Ҫ������֧������Ҫ 
				ZB_State=0;
				u2_printf("CT_XQT1");
			}
			else if((0==ZB_Flag)&&(1==XQT_Flag))  //��ʱ�Ѵ���������״̬
			{
				MotorStart(1,1,0,0);              //֧������
				u2_printf("*%s*M1*Z*/*/**",RX_BUF);		//����2����
				ZB_Dir_flag=1;
				ZB_State=1;                       //֧����Ҫ�����������Ȳ���Ҫ 
				XQT_State=0;
				u2_printf("CT_ZB1");
			}
			else if((0==ZB_Flag)&&(0==XQT_Flag))            //��ʱ����֧���������ȸ�λ״̬
			{				 
				MotorStart(1,1,0,0); 	 				//֧������ 
				MotorStart(2,1,0,0);  				//�����Ƹ�����
				u2_printf("*%s*M12*ZZ*/*/**",RX_BUF); //��������,����2����		
				ZB_Dir_flag=1;
				XQT_State=1;                             //֧����Ҫ��������������Ҫ����       
				ZB_State=1;
				u2_printf("CT_ZBQ_ZBXQT1");
			}
			else if((1==ZB_Flag)&&(1==XQT_Flag))            //��ʱ�Ѵ���֧��֧��������״̬
			{
				XQT_State=0;            
				ZB_State=0; 
			}
		}		
		else if((ZDZBQ_Dir_flag==0)&&(1==ZDZBQ_Flag))         //�Զ����㸴λ-֧���������ȸ�λ
		{
			ZB_Dir_flag=0; 
			XQT_State=1;            
			ZB_State=1;			
			MotorStart(1,0,0,0); //֧������      
			MotorStart(2,0,0,0); //�����Ƹ�����
			u2_printf("*%s*M12*FF*/*/**",RX_BUF);  //��������,����2����
			delay_ms(200);
			u2_printf("CT_ZBQ_ZBXQT15");
		}
		if((1==XQT_State)||(1==ZB_State))
		{	
			if(1==XQT_State){ XQT_Flag=1; W25QXX_Write((u8*)&XQT_Flag,37,1); }		//��״̬��־λд��flash
			if(1==ZB_State) { ZB_Flag=1;  W25QXX_Write((u8*)&ZB_Flag,35,1); }		//��״̬��־λд��flash
			Fun_ZB_XQT();
		}
		if(ZDZBQ_Dir_flag==1)
		{
			Fun_ZBQ(0);	            //�����			
			delay_ms(1000);
			Fun_CZ1();              //������			
			delay_ms(1000);			
			Fun_CXHG();             //��ϴ���			
			Fun_ZBQ(1);	            //����ر�
			ZBQ_Flag=0;							//����״̬��־λ
			if(ZBQ_Flag==0)         //�ж������Ƿ��ڸ�λ״̬���ٽ���������ս�
			{									
				Fun_ZBTG(1,ZBDTG_Lim);   //�����Ƹ����
				Fun_ZBD(1);          //������ս�
				Fun_ZBTG(0,ZBDTG_Lim);   //�����Ƹ�����
				delay_ms(100);
				Fun_ZDZBQ();         //�ٴε��øú�����ʹ��־λȡ������λ
				XQT_Flag=0;          //�����־λ
				ZB_Flag=0;					//����״̬��־λ
				W25QXX_Write((u8*)&ZB_Flag,35,1);		//��״̬��־λд��flash
				W25QXX_Write((u8*)&XQT_Flag,37,1);		//��״̬��־λд��flash
				ZDZBQ_Flag=0;				//����״̬��־λ
				XQT_State=0;
				ZB_State=0;
				ZB_Dir_flag=0;		//���÷���״̬��־λ
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
 ������      ��Fun_ZBQ(void)  
 ��������    ������ִ������������
 ����        ��dir: 0(������)��1���ر����㣩
 ���        ����
                           
************************************************************************/
void Fun_ZBQ(u8 dir)
{
	u8 direct;       //����ĳ���������еķ����־��1-�������У�0-��������
	u8 key;          //����ɨ�躯������ֵ,�����жϵ��ʧ������
	u16 len;
	
//ʵ����λ��ʵʱ��ʾ������ǰ�˶�״̬
	static u16 k=0;           //���͵�k��ͼƬָ��
	u8 i=0;
	u16 j=0;	
	u16 arr_send;             //��ǰһ������������
	static u8 kj;
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);		//��մ���2��������	
	USART2_RX_LEN=0;					//����2״̬����
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//��մ���4��������			
	UART4_RX_LEN=0;				  //����4״̬����
	
	//�������ܣ�ֻ���������ȡ����ҷ���λ�󣬲���ִ������������
	if((SQT_Flag==0)&&(ZF_Flag==0)&&(YF_Flag==0))
	{
		ZBQ_Flag=1;							//����״̬��־λ
		W25QXX_Write((u8*)&ZBQ_Flag,38,1);		//��״̬��־λд��flash
		direct=!dir;					//�������з����־
		if(0==dir)
		{
			MotorStart(6,0,1400-1,25-1);           //�������
			u2_printf("*%s*M6*Z*0*/**",RX_BUF);		//����2����
			delay_ms(200);
			u2_printf("CT_ZBQ1");
		}
		else
		{
			MotorStart(6,1,1400-1,25-1);           //�������
			u2_printf("*%s*M6*F*0*/**",RX_BUF);		//����2����
			delay_ms(200);
			u2_printf("CT_ZBQ25");
		}
				
		TIM10_Init(ZBQ_Max,65000);              //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);           //����жϱ�־λ
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))    //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��
		{							
			//�����λ
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
			  //�ж���û���յ���λ��ָ��		
			if(USART2_RX_LEN&0x8000)
			{
				u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���	
				memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);//��մ���2��������			
				USART2_RX_LEN=0;				//����2״̬����
			}
			if(UART4_RX_LEN&0x8000)
			{
				u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���	
				memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//��մ���4��������			
				UART4_RX_LEN=0;				  //����4״̬����
			}
			//������ϡ��������
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
			//���Ͷ���ָ��
			arr_send=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//��ȡ��ǰ�Ĵ�������װ��ֵ
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
						u2_printf("CT_ZBQ%d",ZBQ_Pic);		//����2���Ͷ���ͼƬָ��
					}
				}
			}
		}			
		
		MotorStop(6);  u2_printf("*%s*M6*T*0*/**",RX_BUF); //6�ŵ��ֹͣ,����2����
		TIM10_Stop();      //�رն�ʱ��
		//�жϸ�λ
		if(((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))||(0==GD6_CS))&&(direct==0))//�ж��Ƿ��ڸ�λ״̬����λ״̬��ǰ�������еĶ�ʱ������
		{		
			ZBQ_Flag=0;	 		//����״̬��־λ
			W25QXX_Write((u8*)&ZBQ_Flag,38,1);		//��״̬��־λд��flash
		}
		 else if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))&&(1==direct))
		 {
			ZBQ_Flag=1; 		//����״̬��־λ
			W25QXX_Write((u8*)&ZBQ_Flag,38,1);		//��״̬��־λд��flash
		}
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ
		//ʹ�����λ����ʼ״̬����簲װ��ֱ�Ӵ򿪴˶Σ�
//		if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))&&(0==GD6_CS)&&(direct==0))  //��ʱʱ�䵽�����û��
//		{
//			MotorStart(6,1,1400-1,25-1);           //�������
//			u2_printf("*%s*M6*F*0*/**",RX_BUF);
//			TIM10_Init(add_arr,65000);                             //�򿪶�ʱ��35000
//			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);           //����жϱ�־λ	 	
//			while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) )  //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��
//			{
//				if(0==GD6_CS)  //���������ػ�������翪�أ�������ѭ�������ֹͣת�� 
//				{  
//					delay_us(100);
//					if(0==GD6_CS) 
//					{
//						u2_printf("GD6CS");
//						break; 
//					}						
//				}				
//			}				                                 			
//			MotorStop(6);     //���ֹͣ
//			u2_printf("*%s*M6*T*0*/**",RX_BUF);
//			TIM10_Stop();        //�رն�ʱ��
//			if(0==GD6_CS)
//			{
//				u2_printf("*%s*GD6CS*/*0*/**",RX_BUF);
//			}
//			else
//			{
//				u2_printf("*%s*GD6CS*/*1*/**",RX_BUF);
//			}
//			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);          //����жϱ�־λ
//		}
	}
	else
	 {
		 LedAlm(100,"ZBQGS");   	
	 }	
}

/***********************************************************************
 ������      ��Fun_CZ1()   
 ��������    �����غ���
 ����        ����
 ���        ��1�������ڱ仯��0������δ�����仯 
                          
************************************************************************/
u8 Fun_CZ(void)  
{
    //��ʼ�������				
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
	//������������Ƿ����仯
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
 ������      ��Fun_ZBD()   
 ��������    ��������ս�
 ����        ��dir:������з����־��1-��ת��0-��ת
 ���        ����
                          
************************************************************************/	
void Fun_ZBD(u8 dir)
{	
	//ʵ����λ��ʵʱ��ʾ������ǰ�˶�״̬
	u16 k=0;                  //����k�Ŷ���
	u8 kj;
	u16 j=0;	
	u16 arr_send;                   //��ǰһ����������ֵ	
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			//��մ���2��������
	USART2_RX_LEN=0;				//����2״̬����
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//��մ���4��������		
	UART4_RX_LEN=0;				  //����4״̬����
	u8 len;
	RELAY6=1;                       //�̵����õ磬��������պϣ��������������õ�
	delay_ms(1000);		
	u2_printf("CT_ZBD1");
	delay_ms(200);	
	//�����������
	if(1==dir)
	{
		DIR6_1=1;
		u2_printf("*%s*M10*Z*/*/**",RX_BUF);				//����2����
	}
	else
	{
		DIR6_1=0;
		u2_printf("*%s*M10*F*/*/**",RX_BUF);			//����2����
	}
	ZBD_Start(360-1,250-1); 
	TIM2_Init(ZBD_Lim,65000);                              //�򿪶�ʱ��10500
	__HAL_TIM_CLEAR_FLAG(&TIM2_Handler, TIM_SR_CC1IF);         //����жϱ�־λ
	while(!(__HAL_TIM_GET_FLAG(&TIM2_Handler, TIM_SR_CC1IF)))  //�ȴ���ʱʱ�䵽
	{			
		//�ж���û���յ���λ��ָ��		
		if(USART2_RX_LEN&0x8000)
		{
			len=USART2_RX_LEN&0x3fff;	//��ȡ����2���������ַ�����				
			USART2_RX_BUF[len]=0;			//����2����ĩβ��"0"
			if(strstr((const char *)USART2_RX_BUF,(const char *)"STOP")||
				strstr((const char *)USART2_RX_BUF,(const char *)"ZDZBQ"))
			{						
				memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//��մ���2��������		
				USART2_RX_LEN=0;					//����2״̬����
				break;
			}
			if(strstr((const char *)USART2_RX_BUF,(const char *)"SEND OK"))
			{	}
			else 
			{
				u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���	
				memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);		//��մ���2��������	
				USART2_RX_LEN=0;					//����2״̬����
			}				
		}
		if(UART4_RX_LEN&0x8000)
		{
			len=UART4_RX_LEN&0x3fff;		//��ȡ����4���������ַ�����			
			UART4_RX_BUF[len]=0;				//����4����ĩβ��"0"
			if(strstr((const char *)UART4_RX_BUF,(const char *)"STOP")||
				strstr((const char *)UART4_RX_BUF,(const char *)"ZDZBQ"))
			{	
				memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//��մ���4��������		
				UART4_RX_LEN=0;				  //����4״̬����
				break;
			}
			if(strstr((const char *)UART4_RX_BUF,(const char *)"SEND OK"))
			{	}
			else 
			{
				u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���	
				memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//��մ���4��������			
				UART4_RX_LEN=0;				  //����4״̬����
			}				
		}
		 arr_send=__HAL_TIM_GET_COUNTER(&TIM2_Handler);      //��ǰһ������ֵ
		//���䶯��ָ��
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
	__HAL_TIM_CLEAR_FLAG(&TIM2_Handler, TIM_SR_CC1IF);          //����жϱ�־λ
	ZBD_Stop();   u2_printf("*%s*M10*T*/*/**",RX_BUF);     //���ֹͣ,����2����
	TIM2_Stop();       //�رն�ʱ��
	delay_ms(100);
	u2_printf("CT_ZBD7");
	RELAY6=0;          //�̵�����λ���������������ϵ�
}	

/***********************************************************************
 ������      ��Fun_ZB_XQT()   
 ��������    ��֧����������ͬʱ���к���
 ����        ����
 ���        ���� 
                          
************************************************************************/
void Fun_ZB_XQT(void)
{
	u8 len;
	u16 arr_now;               //��ǰһ������������	
	//ʵ����λ��ʵʱ��ʾ������ǰ�˶�״̬
	static u8 k;               //����k�Ŷ���
	static u8 kj;
	u8 j=0;	
	u16 arr_send;              //��ǰһ����������ֵ
		
	//�������ܣ�ֻ�������ҷ����ܸ�λ�󣬲��ܽ���֧����������
	if((ZF_Flag==0)&&(YF_Flag==0))
	{	
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//��մ���2��������		
		USART2_RX_LEN=0;				//����2״̬����
		memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//��մ���4��������			
		UART4_RX_LEN=0;				  //����4״̬����
		//����֧���������Ȼ�֧����������ͬʱ����
		TIM10_Init(Ang_To_Arr_SXQT(XQT_Lim),65000);     //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);             //����жϱ�־λ	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) )    //��ʱʱ�䵽
		{
			 //�ж���û���յ����ָ��
			if(USART2_RX_LEN&0x8000)
			{
				len=USART2_RX_LEN&0x3fff;	//��ȡ����2���������ַ�����				
				USART2_RX_BUF[len]=0;			//����2����ĩβ��"0"
				if(strstr((const char *)USART2_RX_BUF,(const char *)"SEND OK"))
				{	}
				else 
				{
					u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���	
					memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			//��մ���2��������
					USART2_RX_LEN=0;				//����2״̬����
				}
			}
			if(UART4_RX_LEN&0x8000)
			{
				len=UART4_RX_LEN&0x3fff;		//��ȡ����4���������ַ�����			
				UART4_RX_BUF[len]=0;				//����4����ĩβ��"0"
				if(strstr((const char *)UART4_RX_BUF,(const char *)"SEND OK"))
				{	}
				else 
				{
					u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���	
					memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);				//��մ���4��������	
					UART4_RX_LEN=0;				  //����4״̬����
				}
			}
			 //����֧������ָ��
			if((1==ZB_State)&&(0==XQT_State))           //ִֻ��֧��
			{
				arr_send=__HAL_TIM_GET_COUNTER(&TIM10_Handler);						//��ȡ��ǰ�Ĵ�������װ��ֵ
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
							u2_printf("CT_ZB%d",ZB_Pic);		//����2���Ͷ���ͼƬָ��
						}							
					}
				}
			}
			//�������ȶ���ָ��
			else if((0==ZB_State)&&(1==XQT_State))      //ִֻ��������
			{
				arr_send=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//��ȡ��ǰ�Ĵ�������װ��ֵ
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
							u2_printf("CT_XQT%d",XQT_Pic);			//����2���Ͷ���ͼƬָ��
						}							
					}				
				}			
			}			
			
			//����֧����������ͬʱ���ж���ָ��
			else if((1==ZB_State)&&(1==XQT_State))      //֧����������ͬʱ����
			{				
				arr_send=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//��ȡ��ǰ�Ĵ�������װ��ֵ
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
		MotorStop(2); u2_printf("*%s*M2*T*/*/**",RX_BUF);  //������ֹͣ
		TIM10_Stop();		        //�رն�ʱ��	
		//�ж������ȸ�λ
		if((ZDZBQ_Dir_flag==0)&&(1==XQT_State)&&(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))
		{
			XQT_Flag=0; 		//����״̬��־λ
			XQT_Runed=0;			//����������ֵ��Ϊ0 
			if(0==ZB_State)                   //ֻ�����������У�֧��������
			{
				k=0;   XQT_Pic=0;
				delay_ms(200);
				u2_printf("CT_XQT1");
			}
		}
		if((ZDZBQ_Dir_flag==1)&&(1==XQT_State)&&(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))
		{
			XQT_Flag=1; 		//����״̬��־λ
			XQT_Runed=(Ang_To_Arr_SXQT(XQT_Lim)); 
			if(0==ZB_State)                   //ֻ�����������У�֧��������
			{
				k=19;   XQT_Pic=19;
				delay_ms(200);
				u2_printf("CT_XQT20");
			}
		}
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);         //����жϱ�־λ
		
		//��������֧����֧����������ͬʱ��������
		if(ZB_State==1)              //��������֧����֧����������ͬʱ��������
		{				
			TIM10_Init(Ang_To_Arr_ZB(ZB_Lim)-Ang_To_Arr_SXQT(XQT_Lim),65000);   //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);          //����жϱ�־λ
			while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) ) //֧����ʱʱ�䵽
			{	
				 //�ж���û���յ����ָ��
				if(USART2_RX_LEN&0x8000)
				{
					len=USART2_RX_LEN&0x3fff;		//��ȡ����2���������ַ�����			
					USART2_RX_BUF[len]=0;			//����2����ĩβ��"0"
					if(strstr((const char *)USART2_RX_BUF,(const char *)"SEND OK"))
					{	}
					else 
					{
						u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���	
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			//��մ���2��������
						USART2_RX_LEN=0;				//����2״̬����
					}
				}	
				if(UART4_RX_LEN&0x8000)
				{
					len=UART4_RX_LEN&0x3fff;		//��ȡ����4���������ַ�����		
					UART4_RX_BUF[len]=0;				//����4����ĩβ��"0"
					if(strstr((const char *)UART4_RX_BUF,(const char *)"SEND OK"))
					{	}
					else 
					{
						u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���	
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//��մ���4��������		
						UART4_RX_LEN=0;				  //����4״̬����
					}
				}
				 //��������֧�����ж���ָ��
				 if(0==XQT_State)        //ֻ��֧������
				 {
					 arr_send=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//��ȡ��ǰ�Ĵ�������װ��ֵ
					 if(ZDZBQ_Dir_flag==1)
					 {
						 j=(Ang_To_Arr_SXQT(XQT_Lim)+arr_send)/(Ang_To_Arr_ZB(ZB_Lim)/19);		//ͼƬ��ż���
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
								u2_printf("CT_ZB%d",ZB_Pic);		//����2���Ͷ���ͼƬָ��
							}								
						}				
					 }						
				 }
				 //�������������ȡ�֧��ͬʱ���еĶ���ָ��
				 if(1==XQT_State)       //֧�������ȶ�����
				 { 
					 arr_send=__HAL_TIM_GET_COUNTER(&TIM10_Handler);		//��ȡ��ǰ�Ĵ�������װ��ֵ
					 if(ZDZBQ_Dir_flag==1)
					 {
						 j=(Ang_To_Arr_SXQT(XQT_Lim)+arr_send)/(Ang_To_Arr_ZB(ZB_Lim)/14);		//ͼƬ��ż���
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
								u2_printf("CT_ZBQ_ZBXQT%d",XQT_Pic);			//����2���Ͷ���ͼƬָ��
							}								
						}				
					}	
				}						 
			}
			MotorStop(1); u2_printf("*%s*M1*T*/*/**",RX_BUF);  //֧��ֹͣ
			TIM10_Stop();                                   //�رն�ʱ��
			//�ж�֧����λ
			if((ZDZBQ_Dir_flag==0)&&(1==ZB_State)&&(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))
			{
				ZB_Flag=0; 		//����״̬��־λ
				ZB_Runed=0;			//����������ֵ��Ϊ0
				if(0==XQT_State)         //ֻ��֧������
				{
					k=0;   ZB_Pic=0;
					delay_ms(200);
					u2_printf("CT_ZB1");
				}
				if(1==XQT_State)         //֧��������ͬʱ����
				{
					k=0;
					delay_ms(200);
					u2_printf("CT_ZBQ_ZBXQT1");
				}
			}
			if((ZDZBQ_Dir_flag==1)&&(1==ZB_State)&&(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))
			{
				ZB_Flag=1; 		//����״̬��־λ
				ZB_Runed=Ang_To_Arr_ZB(ZB_Lim);				//��������������ֵΪ����ֵ
				if(0==XQT_State)         //ֻ��֧������
				{
					k=19;   ZB_Pic=19;
					delay_ms(200);
					u2_printf("CT_ZB20");
				}
				if(1==XQT_State)         //֧��������ͬʱ����
				{
					k=14;
					delay_ms(200);
					u2_printf("CT_ZBQ_ZBXQT15");
				}
			}
			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);         //����жϱ�־λ
		}				
	}
	else
	{
		LedAlm(100,"ZBQTGS");
	}	
}

/***********************************************************************
 ������      ��WIFI_CZ1(void)   
 ��������    ������ִ���Զ�����������
 ����        ����
 ���        ���� 
                          
************************************************************************/
u8  Fun_CZ1(void)
{
	u8 m=0,i=0;
//	TIM2_Init(45000,10000);    //�򿪶�ʱ������ʱʮ��
//	while(cz_time<2)
//	{
//		
		while(1)
		{
			TIM10_Init(45000-1,10000);       //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);         //����жϱ�־λ
			while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))  //�ȴ���ʱʱ�䵽
			{
				if(Fun_CZ())                //�������ڱ仯����ѭ�������¿�ʼ��ʱ
				{  
					m++;
					if((0<m)&&(m<16))
					{
						u2_printf("CT_CZ%d",m);	
					}
				}
			}
			//���30S��ʱ�䵽������û�з����仯
			if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))&&(0==Fun_CZ())) 
			{ 
				i++; 
			}
			else { i=0; }                    //�������¼�ʱ
			if(i==1)                         //����������û�з����仯����ʼ��ϴ���
			{
				u2_printf("CZJS");   //�ű���ؽ���
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
//	TIM2_Close();   //�رն�ʱ��	
	u2_printf("���ؽ���");
	
}

/***********************************************************************
 ������      ��Fun_CXHG(void)   
 ��������    ������ִ�г�ϴ��ɹ���
 ����        ����
 ���        ����  
                          
************************************************************************/
void Fun_CXHG()
{
	u8 num,len;    //�����ַ�������
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);//��մ���2��������
	USART2_RX_LEN=0;				//����2״̬����
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//��մ���4��������
	UART4_RX_LEN=0;				  //����4״̬����
    //�������ܣ�ֻ���������ʱ���ܽ����������
	if(1==ZBQ_Flag)		
	{
//		Fun_ZBCXHG(1,2000);      //��ϴ����Ƹ����                   
//		delay_ms(50);
		
/********************��ʼ��ϴ**********************/
		Fun_ZDCX();                               //�Զ���ϴ

		//�Զ���ϴ�������ȴ�30S���ٴΰ��³�ϴ�����������ֶ����ڳ�ϴ
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);     //��ս��ռĴ���
		USART2_RX_LEN=0;					//����2״̬����
		memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//��մ���4��������
		UART4_RX_LEN=0;				  //����4״̬����
		TIM9_Init(40000,65000);                   //�򿪶�ʱ������ʱ30S60000
		__HAL_TIM_CLEAR_FLAG(&TIM9_Handler, TIM_SR_CC1IF);         //����жϱ�־λ
		while(!(__HAL_TIM_GET_FLAG(&TIM9_Handler, TIM_SR_CC1IF)))  //�ȴ���ʱʱ�䵽
		{							
			if(USART2_RX_LEN&0x8000)
			{
				len=USART2_RX_LEN&0x3fff;		//��ȡ����2���������ַ�����			
				USART2_RX_BUF[len]=0;				//����2����ĩβ��"0"
				if(strstr((const char *)USART2_RX_BUF,(const char *)"SDCX"))   //�����յ�Stop,������ѭ��	
				{					
					if(1==Liq_Sensor)           //�㹻һ�γ�ϴ
					{	
						u2_printf("*%s*YW*/*0*/**",RX_BUF);		//����2����
//						memcpy(RX_BUF,USART2_RX_BUF,15);
						Fun_SDCX();
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);		//��մ���2��������	
					    USART2_RX_LEN=0;						//����2״̬����					
					}
					else                         //����һ�γ�ϴ
					{
						u2_printf("*%s*YW*/*1*/**",RX_BUF);		//����2����
						break;
					}
				}				
			}
			if(UART4_RX_LEN&0x8000)
			{
				len=UART4_RX_LEN&0x3fff;				//��ȡ����4���������ַ�����	
				UART4_RX_BUF[len]=0;					//����4����ĩβ��"0"
				if(strstr((const char *)UART4_RX_BUF,(const char *)"SDCX"))   //�����յ�Stop,������ѭ��	
				{					
					if(1==Liq_Sensor)           //�㹻һ�γ�ϴ
					{	
						u2_printf("*%s*YW*/*0*/**",RX_BUF);		//����2����
//						memcpy(RX_BUF,UART4_RX_BUF,15);
						Fun_SDCX();
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//��մ���4��������		
					    UART4_RX_LEN=0;				  //����4״̬����
					}
					else                         //����һ�γ�ϴ
					{
						u2_printf("*%s*YW*/*1*/**",RX_BUF);		//����2����
						break;
					}
				}				
			}
		}
		TIM9_Stop();                                         //�رն�ʱ��
		__HAL_TIM_CLEAR_FLAG(&TIM9_Handler, TIM_SR_CC1IF);   //����жϱ�־λ
	
		delay_ms(500);
		
/**********************************��ʼ���***********************************/
		
		Fun_ZDHG();       //�Զ����2����
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);//��մ���2��������
		USART2_RX_LEN=0;				//����2״̬����
		memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//��մ���4��������
		UART4_RX_LEN=0;				  //����4״̬����
		//�Զ���ɽ������ȴ�30S���ٴΰ��º�ɰ����������ֶ����ں��		
		TIM9_Init(40000,65000);                             //�򿪶�ʱ������ʱ30S
		__HAL_TIM_CLEAR_FLAG(&TIM9_Handler, TIM_SR_CC1IF);         //����жϱ�־λ
		while(!(__HAL_TIM_GET_FLAG(&TIM9_Handler, TIM_SR_CC1IF)))  //�ȴ���ʱʱ�䵽
		{
			if(USART2_RX_LEN&0x8000)
			{
				len=USART2_RX_LEN&0x3fff;		//��ȡ����2���������ַ�����			
				USART2_RX_BUF[len]=0;			//����2����ĩβ��"0"
				if(strstr((const char *)USART2_RX_BUF,(const char *)"SDHG"))    //�����յ�Stop,������ѭ��	
				{
					Fun_SDHG();
					memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);		//��մ���2��������	
					USART2_RX_LEN=0;						//����2״̬����
				}				
			}
			if(UART4_RX_LEN&0x8000)
			{
				len=UART4_RX_LEN&0x3fff;			//��ȡ����4���������ַ�����		
				UART4_RX_BUF[len]=0;				//����4����ĩβ��"0"
				if(strstr((const char *)UART4_RX_BUF,(const char *)"SDHG"))    //�����յ�Stop,������ѭ��	
				{
					Fun_SDHG();
					memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);				//��մ���4��������	
					UART4_RX_LEN=0;				  //����4״̬����
				}				
			}
		}
		
		TIM9_Stop();                                        //�رն�ʱ��
		__HAL_TIM_CLEAR_FLAG(&TIM9_Handler, TIM_SR_CC1IF);  //����жϱ�־λ		
//		delay_ms(500);
//		Fun_ZBCXHG(0,2000+CXHG_Runed);                    //��ϴ����Ƹ�����		
	}
	else
	{
		LedAlm(100,"ZBQGS");
	}		
}
			
/***********************************************************************
 ������      ��Fun_SDCX(void)   
 ��������    ������ִ�г�ϴ����
 ����        ����
 ���        ����  
                          
************************************************************************/
void Fun_SDCX(void)
{
	u8 len;              //WiFi�����ַ�������
	u8 direct;           //�����־λ
	u8 i;
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);//��մ���2��������
	USART2_RX_LEN=0;					//����2״̬����
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//��մ���4��������
	UART4_RX_LEN=0;				  //����4״̬����
	
    //�������ܣ�ֻ���������ʱ���ܽ�����ˮ��ϴ
	if(1==ZBQ_Flag)		
	{								
		//��ˮ��ϴ
		RELAY6=1;             //�̵����õ�
		DIR_SB=1;             //ˮ�ÿ���PB12	
		CX_Flag=1;						//����״̬��־λ
		if(0==CXHG_Runed)
		{
			u2_printf("CT_CX1");
		}
		Fun_ZBCX(1,CXHG_Lim/2); 
		for(i=0;i<2*CXHG_Time;i++)                                //��ϴ2*CXHG_Time����
		{
			TIM10_Init(60000-1,45000-1);            //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz					
			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);        //����жϱ�־λ 
			while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))) //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��
			{ 					
//				if(0==Liq_Sensor)	                       //ˮλ�ڵ�ˮλ�£�����һ�γ�ϴ����ֱ������
//				{ 
//					u2_printf("*%s*YW*/*1*/**",RX_BUF);
//					delay_ms(200);				
//					u2_printf("DYW");                      //���͸���λ��ָ���źţ���ʾ��ʱˮλƫ��
//					break;
//				}
//				else if(1==Liq_Sensor)
//				{
//					u2_printf("*%s*YW*/*0*/**",RX_BUF);
//				}					
				if(USART2_RX_LEN&0x8000)
				{
					len=USART2_RX_LEN&0x3fff;	//��ȡ����2���������ַ�����				
					USART2_RX_BUF[len]=0;			//����2����ĩβ��"0"
					if(strstr((const char *)USART2_RX_BUF,(const char *)"TGS"))    //�Ƹ����	
					{
						direct=1;			//�������з����־
						Fun_ZBCX(1,CXHG_Lim/2); 
					}
					if(strstr((const char *)USART2_RX_BUF,(const char *)"TGX"))  //�Ƹ�����	
					{ 
						direct=0;			//�������з����־
						Fun_ZBCX(0,CXHG_Lim/2); 					
					}
					memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);//��մ���2��������
					USART2_RX_LEN=0;				//����2״̬����
				}
				if(UART4_RX_LEN&0x8000)
				{
					len=UART4_RX_LEN&0x3fff;		//��ȡ����4���������ַ�����			
					UART4_RX_BUF[len]=0;			//����4����ĩβ��"0"
					if(strstr((const char *)UART4_RX_BUF,(const char *)"TGS"))    //�Ƹ����	
					{
						direct=1;			//�������з����־
						Fun_ZBCX(1,CXHG_Lim/2); 
					}
					if(strstr((const char *)UART4_RX_BUF,(const char *)"TGX"))  //�Ƹ�����	
					{ 
						direct=0;			//�������з����־
						Fun_ZBCX(0,CXHG_Lim/2); 					
					}
					memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//��մ���4��������
					UART4_RX_LEN=0;					  //����4״̬����
				}
			}			
			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //����жϱ�־λ   		
			TIM10_Stop();		                                //�رն�ʱ��				
		}
		Fun_ZBCX(0,CXHG_Lim/2);
		CX_Flag=0;						//����״̬��־λ
		DIR_SB=0;             //ˮ�ùر�PB12
		if(CXHG_Runed>0)
		{
			direct=0;			//�������з����־
			Fun_ZBCX(0,CXHG_Runed); 
		}
		if(0==CXHG_Runed)
		{
			u2_printf("CT_CX1");
		}		
		RELAY6=0;        //�̵����ϵ�
	}
	else
	{
		LedAlm(100,"SDCXGS");
	}	
}

/***********************************************************************
 ������      ��Fun_SDHG(void)   
 ��������    ������ִ�к�ɹ���
 ����        ����
 ���        ����  
                          
************************************************************************/
void Fun_SDHG(void)
{
	u8 len,i;
	u8 direct;     //����ûĳ���������еķ����־��1-�������У�0-��������         
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);//��մ���2��������
	USART2_RX_LEN=0;			//����2״̬����
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//��մ���4��������
	UART4_RX_LEN=0;				  //����4״̬����
    //�������ܣ�ֻ���������ʱ���ܽ����������
	if(1==ZBQ_Flag)		
	{	
		//�������
		DIR_HG=1;             //����������Ŵ�PB10
		delay_ms(500);       //�ȴ����Ŵ�1S
		RELAY6=1;             //�̵����õ�
		DIR_QB=1;             //��������PH2
		HG_Flag=1;						//����״̬��־λ
		if(0==CXHG_Runed)
		{
			u2_printf("CT_HG1");
		}
		Fun_ZBHG(1,CXHG_Lim/2); 
		for(i=0;i<2*CXHG_Time;i++)      //���CXHG_Time����
		{
			TIM10_Init(60000-1,45000-1);         //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz						
			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);        //����жϱ�־λ 
			while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))) //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��
			{ 					
				if(USART2_RX_LEN&0x8000)
				{
					len=USART2_RX_LEN&0x3fff;		//��ȡ����2���������ַ�����			
					USART2_RX_BUF[len]=0;			//����2����ĩβ��"0"
					//�ж�������
					if(strstr((const char *)USART2_RX_BUF,(const char *)"TGS"))    //�Ƹ����	
					{
						direct=1;			//�������з����־
						Fun_ZBHG(1,CXHG_Lim/2); 
					}
					if(strstr((const char *)USART2_RX_BUF,(const char *)"TGX"))  //�Ƹ�����	
					{ 
						direct=0;			//�������з����־
						Fun_ZBHG(0,CXHG_Lim/2); 					
					}
					memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);//��մ���2��������
					USART2_RX_LEN=0;				//����2״̬����
				}	
				if(UART4_RX_LEN&0x8000)
				{
					len=UART4_RX_LEN&0x3fff;		//��ȡ����4���������ַ�����			
					UART4_RX_BUF[len]=0;				//����4����ĩβ��"0"
					//�ж�������
					if(strstr((const char *)UART4_RX_BUF,(const char *)"TGS"))    //�Ƹ����	
					{
						direct=1;			//�������з����־
						Fun_ZBHG(1,CXHG_Lim/2); 
					}
					if(strstr((const char *)UART4_RX_BUF,(const char *)"TGX"))  //�Ƹ�����	
					{ 
						direct=0;			//�������з����־
						Fun_ZBHG(0,CXHG_Lim/2); 					
					}
					memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//��մ���4��������
					UART4_RX_LEN=0;				  //����4״̬����
				}
			}              		
			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //����жϱ�־λ   		
			TIM10_Stop();   //�رն�ʱ��		 	
		}
		Fun_ZBHG(0,CXHG_Lim/2); 
		HG_Flag=0;				//����״̬��־λ
		if(CXHG_Runed>0)
		{
			direct=0;			//�������з����־
			Fun_ZBHG(0,CXHG_Runed); 
		}		
		if(0==CXHG_Runed)
		{
			u2_printf("CT_HG1");
		}
		
		RELAY6=0;       //�̵����ϵ�
		DIR_QB=0;       //���ùر�PH2
		DIR_HG=0;       //����������ر�PB10		
	}
	else
	{
		LedAlm(100,"SDHGGS");
	}	
}

/***********************************************************************
 ������      ��Fun_ZDCX(void)   
 ��������    ������ִ�г�ϴ����
 ����        ����
 ���        ����  
                          
************************************************************************/
void Fun_ZDCX(void)
{
	u8 direct;   //����ûĳ���������еķ����־��1-�������У�0-��������
	u8 flag=0;   //�����Ƹ˷����л�
	u8 i;
	u8 num,len;
	
    //�������ܣ�ֻ���������ʱ���ܽ�����ˮ��ϴ
	if(1==ZBQ_Flag)		
	{						
//		//��ϴ֮ǰ���ˮλ��������ˮλ���£����������������ȴ�ˮ��עˮ
//		if(0==Liq_Sensor)  
//		{
//			delay_ms(100);
//			u2_printf("*%s*YW*/*1*/**",RX_BUF);
//			delay_ms(200);		
//			u2_printf("DYW");  //���͸���λ��ָ���źţ���ʾ��ʱˮλƫ��
//			PCF8574_WriteBit(BEEP_IO,0);	//���Ʒ���������	
//			delay_ms(500);	
//			PCF8574_WriteBit(BEEP_IO,1);	//���Ʒ���������			
//		}
//		while(0==Liq_Sensor);                  //�ȴ�ˮ��ע��
//		u2_printf("*%s*YW*/*0*/**",RX_BUF);  //Һλ�ָ��ɽ��г�ϴ���
//		PCF8574_WriteBit(BEEP_IO,1);
		RELAY6=1;                              //�̵����õ�
		//��ˮ��ϴ
		DIR_SB=1;                              //ˮ�ÿ���PB12	
		if(0==CXHG_Runed)
		{                   
			delay_ms(100);
			u2_printf("CT_CX1");
		}
		for(i=0;i<2*CXHG_Time;i++)     //��ϴ����Ƹ��Զ�ѭ����ϴCXHG_Time����
		{
			flag=!flag;
			if(1==flag)
			{
				Fun_ZBCX(1,CXHG_Lim);      //ÿ���������5S��
			}
			else
			{
				Fun_ZBCX(0,CXHG_Lim);      //ÿ���������5S��			
			}
			delay_ms(10);			
		}
		if(0==CXHG_Runed)
		{                   
			delay_ms(100);
			u2_printf("CT_CX1");
		}
		RELAY6=0;             //�̵����ϵ�
		DIR_SB=0;             //ˮ�ùر�PB12		
	}
	else
	{
		LedAlm(100,"ZDCXGS");
	}	
}

/***********************************************************************
 ������      ��Fun_ZDHG(void)   
 ��������    ������ִ�к�ɹ���
 ����        ����
 ���        ����  
                          
************************************************************************/
void Fun_ZDHG(void)
{
	u8 flag=0;        //�����Ƹ˷����л�
	u8 i;
	
    //�������ܣ�ֻ���������ʱ���ܽ����������
	if(1==ZBQ_Flag)		
	{
		//�������
		DIR_HG=1;             //����������Ŵ�PB10
		delay_ms(500);       //�ȴ����Ŵ�1S
		RELAY6=1;             //�̵����õ�
		DIR_QB=1;             //��������PH2
		if(0==CXHG_Runed)
		{
			u2_printf("CT_HG1");
		}		
		for(i=0;i<2*CXHG_Time;i++)     //��ϴ����Ƹ��Զ�ѭ�����CXHG_Time ����
		{
			flag=!flag;
			if(1==flag)
			{
				Fun_ZBHG(1,CXHG_Lim);      //ÿ���������5S��
			}
			else
			{
				Fun_ZBHG(0,CXHG_Lim);      //ÿ���������5S��			
			}
			delay_ms(50);
		}
		if(0==CXHG_Runed)
		{
			u2_printf("CT_HG1");
		}
		RELAY6=0;       //�̵����ϵ�
		DIR_QB=0;       //���ùر�PH2
		DIR_HG=0;       //����������ر�PB10
	}
	else
	{
		LedAlm(100,"ZDHGGS");
	}	
}

/***********************************************************************
 ������      ��Fun_ZJ_ZB(void)  
 ��������    ��ר��ϵͳ����-֧��
 ����        ����
 ���        ����
                           
************************************************************************/
void Fun_ZJ_ZB(void) 
{
	//֧����
	WriteInU2("ZBS");
	Fun_ZB();                //֧��
	delay_ms(1000);	
	//֧����λ	
	WriteInU2("ZBX");
	Fun_ZB();                //֧����λ		
}

/***********************************************************************
 ������      ��Fun_ZJ_ZYF(void)  
 ��������    ��ר��ϵͳ����-����
 ����        ����
 ���        ����
                           
************************************************************************/
void Fun_ZJ_ZYF(void) 
{
	//����
	WriteInU2("ZFS");		
	Fun_ZF();           //����	
	delay_ms(1000);
	WriteInU2("ZFX");		
	Fun_ZF();           //����λ
	delay_ms(1000);
			
	//�ҷ���
	WriteInU2("YFS");
	Fun_YF();          //�ҷ���
	delay_ms(1000);
	WriteInU2("YFX");
	Fun_YF();          //�ҷ���λ		
}

/***********************************************************************
 ������      ��Fun_ZJ_SXQT(void)  
 ��������    ��ר��ϵͳ����-����
 ����        ����
 ���        ����
                           
************************************************************************/
void Fun_ZJ_SXQT(void) 
{
	//������
	WriteInU2("SQTS");
	Fun_SQT();              //������
	delay_ms(1000);
	WriteInU2("SQTX");
	Fun_SQT();              //�����ȸ�λ
	delay_ms(1000);	
	
	//������
	WriteInU2("XQTX");
	Fun_XQT();            //������	
	delay_ms(1000);
	WriteInU2("XQTS");
	Fun_XQT();            //�����ȸ�λ	
}

/***********************************************************************
 ������      ��Fun_ZJ_ZDZB(void)  
 ��������    ��ר��ϵͳ����-�Զ�����
 ����        ����
 ���        ����
                           
************************************************************************/
void Fun_ZJ_ZDZB(void) 
{
	Fun_ZDZBQ();	  //�Զ�����
}

/***********************************************************************
 ������      ��Fun_ZD_ZZ(void)  
 ��������    ��ִ����֫��������
 ����        ��t-������������
 ���        ����
                           
************************************************************************/
void Fun_ZD_ZZ(int t)
{
   u32 pulse;          //��������������
   int j;	
	//����ֻ��ƽ���ڴ��ϲ��ܽ��е��ҿ���ѵ��
   if((0==ZB_Flag)&&(0==SQT_Flag)&&(0==XQT_Flag)&&(0==ZBQ_Flag)&&(0==ZF_Flag)&&(0==YF_Flag))
   { 
		
		DG_Relay=1;	       //�̵���
		if((strstr((const char *)USART2_RX_BUF,(const char *)"BZZ"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"BZZ")))//��첲
		{
			pulse=1000000;
			if(ZXT_Flag==0)       //��ֹ�����󴥷������±�־λ��λ
			{	
				ZXB_Flag=1;		//����״̬��־λ
				delay_ms(200);
				u2_printf("KS");
				delay_ms(200);
				u2_printf("DGZZKS");				
			}
		}
		if((strstr((const char *)USART2_RX_BUF,(const char *)"TZZ"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"TZZ")))//����
		{
			pulse=1500000;
			if(ZXB_Flag==0)      //��ֹ�����󴥷������±�־λ��λ
			{	
				ZXT_Flag=1;		//����״̬��־λ
				delay_ms(200);
				u2_printf("KS");
				delay_ms(200);
				u2_printf("DGZTKS");
				delay_ms(200);
			}			
		}
		Fun_Auto_DG12(1,pulse);        //����̧֫��		
		delay_ms(1000);	     
		   
		for(j=0;j<t;j++)              //����t����֫����ѵ��
		{
			Fun_Auto_DG2(1,500000);     //�����˶�			
			delay_ms(1000);			
			Fun_Auto_DG2(0,500000);     //�����˶�			
			delay_ms(1000);	
		}
		Fun_Auto_DG12(0,pulse);       //����֫��ƽ��ԭ����λ��
		//����־λ��λ
		if((0==ZGB_Runed)&&(1==ZXB_Flag))         //��첲����������Ϊ�㣬��λ����ʼ״̬
		{
			ZXB_Flag=0;		//����״̬��־λ
			delay_ms(200);
			u2_printf("FW");
			delay_ms(200);
			u2_printf("DGZZJX");
			delay_ms(200);
		}
		if((0==ZT_Runed)&&(1==ZXT_Flag))         //��������������Ϊ�㣬��λ����ʼ״̬
		{
			ZXT_Flag=0;		//����״̬��־λ
			delay_ms(200);
			u2_printf("FW");
			delay_ms(200);
			u2_printf("DGZTFW");
			delay_ms(200);
		}
		DG_Relay=0;	       //�̵���
	}
	else
	{
		LedAlm(100,"DGGS");
	}		
}

/***********************************************************************
 ������      ��Fun_ZD_YZ(void)   
 ��������    ��ִ����֫���ҿ���ѵ��
 ����        ��t���Ҵ���
 ���        ���� 
                          
************************************************************************/
void Fun_ZD_YZ(int t)
{
	u32 pulse;     //��������������
	//����ֻ��ƽ���ڴ��ϲ��ܽ��е��ҿ���ѵ��
	if((0==ZB_Flag)&&(0==SQT_Flag)&&(0==XQT_Flag)&&(0==ZBQ_Flag)&&(0==ZF_Flag)&&(0==YF_Flag))
	{
		DG_Relay=1;	       //�̵���
		if((strstr((const char *)USART2_RX_BUF,(const char *)"BYZ"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"BYZ")))//�Ҹ첲
		{
			pulse=1000000;
			if(YXT_Flag==0)          //��ֹ�����󴥷������±�־λ��λ
			{	
				YXB_Flag=1;		//����״̬��־λ
				delay_ms(200);
				u2_printf("KS");
				delay_ms(200);
				u2_printf("DGYZKS");
				delay_ms(200);
			}			
		}
		if((strstr((const char *)USART2_RX_BUF,(const char *)"TYZ"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"TYZ")))//����
		{
			pulse=1500000;
			if(YXB_Flag==0)          //��ֹ�����󴥷������±�־λ��λ
			{	
				YXT_Flag=1;		//����״̬��־λ
				delay_ms(200);				
				u2_printf("KS");
				delay_ms(200);
				u2_printf("DGYTKS");	
				delay_ms(200);
			}			
		}
	
		int j;
		Fun_Auto_DG34(1,pulse);       //����̧֫��
		delay_ms(1000);
		
		for(j=0;j<t;j++)                   //����t����֫����ѵ��
		{		
			Fun_Auto_DG3(1,500000);     //�����˶�		
			delay_ms(1000);		
			Fun_Auto_DG3(0,500000);     //�����˶�
			delay_ms(1000);		
		}	
		Fun_Auto_DG34(0,pulse);       //����֫��ƽ��ԭ����λ��
		//����־λ��λ
		if((0==YGB_Runed)&&(1==YXB_Flag))   //��첲����������Ϊ�㣬��λ����ʼ״̬
		{
			YXB_Flag=0;		//����״̬��־λ
			delay_ms(200);
			u2_printf("FW");
			delay_ms(200);			
			u2_printf("DGYZFW");
			delay_ms(200);
		}
		if((0==YT_Runed)&&(1==YXT_Flag))   //��������������Ϊ�㣬��λ����ʼ״̬
		{
			YXT_Flag=0;		//����״̬��־λ
			delay_ms(200);
			u2_printf("FW");
			delay_ms(200);
			u2_printf("DGYTFW");
			delay_ms(200);
		}	
		DG_Relay=0;	       //�̵���
	}
	else
	 {
		 LedAlm(100,"DGGS");
	 }	
}

/***********************************************************************
 ������      ��Fun_ZD_ZYZ(void)   
 ��������    ��ִ������֫���ҿ���ѵ��
 ����        ��t���Ҵ���
 ���        ����  
                          
***********************************************************************/
void Fun_ZD_ZYZ(int t)
{
	u32 pulse;	         //��������������
	int j;
	//����ֻ��ƽ���ڴ��ϲ��ܽ��е��ҿ���ѵ��
	if((0==ZB_Flag)&&(0==SQT_Flag)&&(0==XQT_Flag)&&(0==ZBQ_Flag)&&(0==ZF_Flag)&&(0==YF_Flag))
	{
		DG_Relay=1;	       //�̵���
		if((strstr((const char *)USART2_RX_BUF,(const char *)"BLZ"))|| 
			(strstr((const char *)UART4_RX_BUF,(const char *)"BLZ")))//���Ҹ첲
		{
			pulse=1000000;
			if(ZYXT_Flag==0)       //��ֹ�����󴥷������±�־λ��λ
			{	
				ZYXB_Flag=1;			//����״̬��־λ
				delay_ms(200);
				u2_printf("KS");
				delay_ms(200);
				u2_printf("DGZYZKS");	
				delay_ms(200);				
			}
			else
			{
				ZYXB_Flag=0;			//����״̬��־λ
			}
		}
		if((strstr((const char *)USART2_RX_BUF,(const char *)"TLZ"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"TLZ")))//������
		{
			pulse=1500000;
			if(ZYXB_Flag==0)      //��ֹ�����󴥷������±�־λ��λ
			{	
				ZYXT_Flag=1;		//����״̬��־λ
				delay_ms(200);
				u2_printf("KS");
				delay_ms(200);
				u2_printf("DGZYTKS");	
				delay_ms(200);				
			}
			else
			{
				ZYXT_Flag=0;			//����״̬��־λ
			}
		}	
		Fun_Auto_DG1234(1,pulse);     //������̧֫�ߣ�С��̧�ñȴ�۸�
		delay_ms(1000);	     
			   
		for(j=0;j<t;j++)                     //����t�ο���ѵ��
		{
			LED1=0;                          //�ڿ���ѵ��������LED0��˸
			Fun_Auto_DG23(1,500000);     //С������һ���߶�
			LED1=1;
			delay_ms(1000);
			LED1=0;
			Fun_Auto_DG23(0,500000);     //С���½�һ���߶�
			delay_ms(1000);
			LED1=1;	
		}
			Fun_Auto_DG1234(0,pulse); //������֫��ƽ��ԭ����λ��
		//����־λ��λ
		if((0==ZYGB_Runed)&&(1==ZYXB_Flag))    //��첲����������Ϊ�㣬��λ����ʼ״̬
		{
			ZYXB_Flag=0;		//����״̬��־λ
			delay_ms(200);
			u2_printf("FW");
			delay_ms(200);
			u2_printf("DGZYZFW");
			delay_ms(200);
		}
		if((0==ZYT_Runed)&&(1==ZYXT_Flag))    //��������������Ϊ�㣬��λ����ʼ״̬
		{
			ZYXT_Flag=0;		//����״̬��־λ
			delay_ms(200);
			u2_printf("FW");
			delay_ms(200);
			u2_printf("DGZYTFW");
			delay_ms(200);
		}	
		DG_Relay=0;	       //�̵���
	}
	else
	{
		LedAlm(100,"DGGS");
	}	
}

/***********************************************************************
 ������      ��Fun_SD_ZXB(void)  
 ��������    ���ֶ�ִ����С��
 ����        ����
 ���        ����                           
************************************************************************/
void Fun_SD_ZXB(void)
{
	 u8 direct;   //����ûĳ���������еķ����־��1-�������У�0-��������
	 static u8 runed_flag=0;
	//��������ֻ���ڼ����򿪡�֧�������㡢����λ������²��ܽ���С��/С�ȿ���ѵ��
   if((0==ZB_Flag)&&(0==SQT_Flag)&&(0==XQT_Flag)&&(0==ZBQ_Flag)&&(0==ZF_Flag)&&(0==YF_Flag))
   {
		DG_Relay=1;	       //�̵���
		 if(0==ZXB_Flag)                    //�Ƚ���̧֫�ߵ�һ���߶�
		{
			if((strstr((const char *)USART2_RX_BUF,(const char *)"BZSXS"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"BZSXS")))
			{
				delay_ms(200);
				u2_printf("KS");
				delay_ms(200);
				u2_printf("DGZXBKS");
				delay_ms(200);
				ZXB_Flag=1;		//����״̬��־λ
				Fun_Hand_DG12(1,ZGB_Lim);  //����̧֫�ߵ�һ���߶ȣ���ʼС�ۿ���ѵ��
				runed_flag=1;
			}
		}				
		//��С����������
		if((strstr((const char *)USART2_RX_BUF,(const char *)"BZSXS"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"BZSXS"))||(1==runed_flag))
		{	
			runed_flag=0;
			if(ZXB_Lim>ZXB_Runed)
			{
				Fun_Hand_DG2(1,ZXB_Lim-ZXB_Runed);
				if(ZXB_Runed==ZXB_Lim)
				{
					ZXB_Flag=1;		//����״̬��־λ
					delay_ms(200);
					u2_printf("JX");
					delay_ms(200);
					u2_printf("DGZXBJX");
					delay_ms(200);
				}
				else
				{
					ZXB_Flag=1;				//����״̬��־λ
				}								
			}	
		}
		//��С����������
		if((strstr((const char *)USART2_RX_BUF,(const char *)"BZSXX"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"BZSXX")))
		{	
			if(ZXB_Runed>0)
			{
				Fun_Hand_DG2(0,ZXB_Runed);					
			}
			if(0==ZXB_Runed)               //��С�۸�λ���򽫸첲��λ
			{
				Fun_Hand_DG12(0,ZGB_Runed);     //����֫��λ��ˮƽ״̬ 
			}
			if((0==ZXB_Runed)&&(0==ZGB_Runed))
			{
				ZXB_Flag=0;		//����״̬��־λ
				delay_ms(200);
				u2_printf("FW");
				delay_ms(200);
				u2_printf("DGZXBFW");
				delay_ms(200);
			}
		}	
		DG_Relay=0;	       //�̵���
	}
	else
	{
		LedAlm(100,"DGGS");
	}	
}

/***********************************************************************
 ������      ��Fun_SD_ZXT(void)  
 ��������    ���ֶ�ִ����С��
 ����        ����
 ���        ����                           
************************************************************************/
void Fun_SD_ZXT(void)
{
	 u8 direct;   //����ûĳ���������еķ����־��1-�������У�0-��������
	 static u8 runed_flag=0;
	//��������ֻ���ڼ����򿪡���֫������֫��ȥ��֧�������㡢����λ������²��ܽ���С��/С�ȿ���ѵ��
   if((0==ZB_Flag)&&(0==SQT_Flag)&&(0==XQT_Flag)&&(0==ZBQ_Flag)&&(0==ZF_Flag)&&(0==YF_Flag))
   {
		DG_Relay=1;	       //�̵���
		 if(0==ZXT_Flag)                    //�Ƚ���̧֫�ߵ�һ���߶�
		{
			if((strstr((const char *)USART2_RX_BUF,(const char *)"TZSXS"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"TZSXS")))
			{
				delay_ms(200);
				u2_printf("KS");
				delay_ms(200);
				u2_printf("DGZXTKS");
				delay_ms(200);
				ZXT_Flag=1;		//����״̬��־λ
				Fun_Hand_DG12(1,ZT_Lim);      //����̧֫�ߵ�һ���߶ȣ���ʼС�ۿ���ѵ��
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
					ZXT_Flag=1;		//����״̬��־λ
					delay_ms(200);
					u2_printf("JX");
					delay_ms(200);
					u2_printf("DGZXTJX");
					delay_ms(200);
				}
				else
				{
					ZXT_Flag=1;				//����״̬��־λ
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
			if(0==ZXT_Runed)             //��С������������Ϊ0���򽫸첲��λ
			{
				Fun_Hand_DG12(0,ZT_Runed);   //����֫��λ��ˮƽ״̬ 
			}
			if((0==ZXT_Runed)&&(0==ZT_Runed))
			{
				ZXT_Flag=0;		//����״̬��־λ
				delay_ms(200);
				u2_printf("FW");
				delay_ms(200);
				u2_printf("DGZXTFW");
				delay_ms(200);
			}			
		}	
		DG_Relay=0;	       //�̵���
	}
	else
	{
		LedAlm(100,"DGGS");
	}	
}

/***********************************************************************
 ������      ��Fun_SD_YXB(void)  
 ��������    ���ֶ�ִ����С��
 ����        ����
 ���        ����                           
************************************************************************/
void Fun_SD_YXB(void)
{
	 u8 direct;    //����ûĳ���������еķ����־��1-�������У�0-��������
	 static u8 runed_flag=0;
	//��������ֻ���ڼ����򿪡���֫������֫��ȥ��֧�������㡢����λ������²��ܽ���С��/С�ȿ���ѵ��
   if((0==ZB_Flag)&&(0==SQT_Flag)&&(0==XQT_Flag)&&(0==ZBQ_Flag)&&(0==ZF_Flag)&&(0==YF_Flag))
   {
		DG_Relay=1;	       //�̵���
		 if(0==YXB_Flag)                    //�Ƚ���̧֫�ߵ�һ���߶�
		{
			if((strstr((const char *)USART2_RX_BUF,(const char *)"BYSXS"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"BYSXS")))
			{
				delay_ms(200);
				u2_printf("KS");
				delay_ms(200);
				u2_printf("DGYXBKS");
				delay_ms(200);
				YXB_Flag=1;		//����״̬��־λ
				Fun_Hand_DG34(1,YGB_Lim);       //����̧֫�ߵ�һ���߶ȣ���ʼС�ۿ���ѵ��
				runed_flag=1;
			}
		}
		//��С����������
		if((strstr((const char *)USART2_RX_BUF,(const char *)"BYSXS"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"BYSXS"))||(1==runed_flag))		
		{
			runed_flag=0;
			if(YXB_Lim>YXB_Runed)
			{
				Fun_Hand_DG3(1,YXB_Lim-YXB_Runed);	
				if(YXB_Runed==YXB_Lim)
				{
					YXB_Flag=1;		//����״̬��־λ
					delay_ms(200);
					u2_printf("JX");
					delay_ms(200);
					u2_printf("DGYXBJX");
					delay_ms(200);
				}
				else
				{
					YXB_Flag=1;		//����״̬��־λ		
				}								
			}	
		}			
		//��С����������
		if((strstr((const char *)USART2_RX_BUF,(const char *)"BYSXX"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"BYSXX")))
		{
			if(YXB_Runed>0)    //��С�������˶�
			{
				Fun_Hand_DG3(0,YXB_Runed);					
			}
			if(YXB_Runed==0)    //����С�۸�λ�����Ҹ첲��λ��ˮƽλ��
			{
				Fun_Hand_DG34(0,YGB_Runed); 
			}
			if((YXB_Runed==0)&&(0==YGB_Runed))   //��־λ��λ
			{
				YXB_Flag=0;			//����״̬��־λ
				delay_ms(200);
				u2_printf("FW");
				delay_ms(200);
				u2_printf("DGYXBFW");
				delay_ms(200);
			}
		}
		DG_Relay=0;	       //�̵���
	}
	else
	{
		LedAlm(100,"DGGS");
	}	
}

/***********************************************************************
 ������      ��Fun_SD_YXT(void)  
 ��������    ���ֶ�ִ����С��
 ����        ����
 ���        ����                           
************************************************************************/
void Fun_SD_YXT(void)
{
	 u8 direct;    //����ûĳ���������еķ����־��1-�������У�0-��������
	 static u8 runed_flag;
	//��������ֻ���ڼ����򿪡���֫������֫��ȥ��֧�������㡢����λ������²��ܽ���С��/С�ȿ���ѵ��
   if((0==ZB_Flag)&&(0==SQT_Flag)&&(0==XQT_Flag)&&(0==ZBQ_Flag)&&(0==ZF_Flag)&&(0==YF_Flag))
   {
		DG_Relay=1;	       //�̵���
		 if(0==YXT_Flag)                    //�Ƚ���̧֫�ߵ�һ���߶�
		{
			if((strstr((const char *)USART2_RX_BUF,(const char *)"TYSXS"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"TYSXS")))
			{
				delay_ms(200);
				u2_printf("KS");
				delay_ms(200);
				u2_printf("DGYXTKS");
				delay_ms(200);
				YXT_Flag=1;		//����״̬��־λ
				Fun_Hand_DG34(1,YT_Lim);       //����̧֫�ߵ�һ���߶ȣ���ʼС�ۿ���ѵ��
				runed_flag=1;
			}
		}
		//��С������
	   if((strstr((const char *)USART2_RX_BUF,(const char *)"TYSXS"))||
		   (strstr((const char *)UART4_RX_BUF,(const char *)"TYSXS"))||(runed_flag==1))
		{
			runed_flag=0;		//����״̬��־λ
			if(YXT_Lim>YXT_Runed)
			{
				Fun_Hand_DG3(1,YXT_Lim-YXT_Runed);	
				if(YXT_Runed==YXT_Lim)
				{
					YXT_Flag=1;		//����״̬��־λ
					delay_ms(200);
					u2_printf("JX");
					delay_ms(200);
					u2_printf("DGYXTJX");
					delay_ms(200);
				}
				else
				{
					YXT_Flag=1;			//����״̬��־λ				
				}								
			}	
		}
		//��������
		if((strstr((const char *)USART2_RX_BUF,(const char *)"TYSXX"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"TYSXX")))
		{
			if(YXT_Runed>0)     //��С����������
			{
				Fun_Hand_DG3(0,YXT_Runed);					
			}
			if(0==YXT_Runed)    //����С�ȸ�λ������֫��ƽ��ˮƽλ��
			{
				Fun_Hand_DG34(0,YT_Runed);
			}
			if((0==YXT_Runed)&&(0==YT_Runed))  //��־λ��λ
			{
				YXT_Flag=0;		//����״̬��־λ
				delay_ms(200);
				u2_printf("FW");
				delay_ms(200);
				u2_printf("DGYXTFW");
				delay_ms(200);
			}
		}
		DG_Relay=0;	       //�̵���
	}
	else
	{
		LedAlm(100,"DGGS");
	}	
}

/***********************************************************************
 ������      ��Fun_SD_ZDB(void)  
 ��������    ���ֶ�ִ������
 ����        ����
 ���        ����                           
************************************************************************/
void Fun_SD_ZDB(void)
{
	//��������ֻ���ڼ����򿪡���֫������֫��ȥ��֧�������㡢����λ������²��ܽ��д��/���ȿ���ѵ��
   if((0==ZB_Flag)&&(0==SQT_Flag)&&(0==XQT_Flag)&&(0==ZBQ_Flag)&&(0==ZF_Flag)&&(0==YF_Flag))
   {
		DG_Relay=1;	       //�̵���
		 //��������		
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
				ZDB_Flag=1;		//����״̬��־λ
				Fun_Hand_DG12(1,ZDB_Lim-ZDB_Runed);	
				if(ZDB_Runed==ZDB_Lim)
				{
					ZDB_Flag=1;		//����״̬��־λ
					delay_ms(200);
					u2_printf("JX");
					delay_ms(200);
					u2_printf("DGZDBJX");
				}
				else
				{
					ZDB_Flag=1;		//����״̬��־λ
				}								
			}	
		}
         //��������		
		if((strstr((const char *)USART2_RX_BUF,(const char *)"BZSDX"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"BZSDX")))
		{
			if(ZDB_Runed>0)
			{
				Fun_Hand_DG12(0,ZDB_Runed);
				if(0==ZDB_Runed)
				{					
					ZDB_Flag=0;		//����״̬��־λ
					delay_ms(200);
					u2_printf("FW");
					delay_ms(200);
					u2_printf("DGZDBFW");
					delay_ms(200);
				}
				else
				{
					ZDB_Flag=1;			//����״̬��־λ		
				}					
			}				
		}
		DG_Relay=0;	       //�̵���
	}
	else
	{
		LedAlm(100,"DGGS");
	}	
}

/***********************************************************************
 ������      ��Uart_Hand_ArmLeg_Post_Left(void)  
 ��������    ���ֶ�ִ�������
 ����        ����
 ���        ����                           
************************************************************************/
void Fun_SD_ZDT(void)
{
	//��������ֻ���ڼ����򿪡���֫������֫��ȥ��֧�������㡢����λ������²��ܽ��д��/���ȿ���ѵ��
   if((0==ZB_Flag)&&(0==SQT_Flag)&&(0==XQT_Flag)&&(0==ZBQ_Flag)&&(0==ZF_Flag)&&(0==YF_Flag))
   {
		DG_Relay=1;	       //�̵���
		 //��������		
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
				ZDT_Flag=1;		//����״̬��־λ
				Fun_Hand_DG12(1,ZDT_Lim-ZDT_Runed);	
				if(ZDT_Runed==ZDT_Lim)
				{
					ZDT_Flag=1;		//����״̬��־λ
					delay_ms(200);
					u2_printf("JX");
					delay_ms(200);
					u2_printf("DGZDTJX");
					delay_ms(200);
				}
				else
				{
					ZDT_Flag=1;						//����״̬��־λ		
				}								
			}	
		}
		//��������
		if((strstr((const char *)USART2_RX_BUF,(const char *)"TZSDX"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"TZSDX")))
		{
			if(ZDT_Runed>0)
			{
				Fun_Hand_DG12(0,ZDT_Runed);
				if(0==ZDT_Runed)
				{					
					ZDT_Flag=0;		//����״̬��־λ
					delay_ms(200);
					u2_printf("FW");
					delay_ms(200);
					u2_printf("DGZDTFW");
					delay_ms(200);
				}
				else
				{
					ZDT_Flag=1;					//����״̬��־λ
				}					
			}				
		}
		DG_Relay=0;	       //�̵���
	}
	else
	{
		LedAlm(100,"DGGS");
	}	
}

/***********************************************************************
 ������      ��Fun_SD_YDB(void)  
 ��������    ���ֶ�ִ���Ҵ��
 ����        ����
 ���        ����                           
************************************************************************/
void Fun_SD_YDB(void)
{
	//��������ֻ���ڼ����򿪡���֫������֫��ȥ��֧�������㡢����λ������²��ܽ��д��/���ȿ���ѵ��
   if((0==ZB_Flag)&&(0==SQT_Flag)&&(0==XQT_Flag)&&(0==ZBQ_Flag)&&(0==ZF_Flag)&&(0==YF_Flag))
   {
		DG_Relay=1;	       //�̵���
		 //��������
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
				YDB_Flag=1;		//����״̬��־λ
				Fun_Hand_DG34(1,YDB_Lim-YDB_Runed);	
				if(YDB_Runed==YDB_Lim)
				{
					YDB_Flag=1;		//����״̬��־λ
					delay_ms(200);
					u2_printf("JX");
					delay_ms(200);
					u2_printf("DGYDBJX");
					delay_ms(200);
				}
				else
				{
					YDB_Flag=1;				//����״̬��־λ				
				}								
			}	
		}
		//��������
		if((strstr((const char *)USART2_RX_BUF,(const char *)"BYSDX"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"BYSDX")))
		{
			if(YDB_Runed>0)
			{
				Fun_Hand_DG34(0,YDB_Runed);
				if(0==YDB_Runed)
				{
					YDB_Flag=0;		//����״̬��־λ
					delay_ms(200);
					u2_printf("FW");
					delay_ms(200);
					u2_printf("DGYDBFW");
					delay_ms(200);
				}
				else
				{
					YDB_Flag=1;	//����״̬��־λ
				}					
			}				
		}
		DG_Relay=0;	       //�̵���
	}
	else
	{
		LedAlm(100,"DGGS");
	}	
}

/***********************************************************************
 ������      ��Fun_SD_YDT(void)  
 ��������    ���ֶ�ִ���Ҵ���
 ����        ����
 ���        ����                           
************************************************************************/
void Fun_SD_YDT(void)
{
	//��������ֻ���ڼ����򿪡���֫������֫��ȥ��֧�������㡢����λ������²��ܽ��д��/���ȿ���ѵ��
   if((0==ZB_Flag)&&(0==SQT_Flag)&&(0==XQT_Flag)&&(0==ZBQ_Flag)&&(0==ZF_Flag)&&(0==YF_Flag))
   {
		DG_Relay=1;	       //�̵���
		 //ͬ���������ж������ۼ�
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
				YDT_Flag=1;		//����״̬��־λ
				Fun_Hand_DG34(1,YDT_Lim-YDT_Runed);	
				if(YDT_Runed==YDT_Lim)
				{
					YDT_Flag=1;		//����״̬��־λ
					delay_ms(200);
					u2_printf("JX");
					delay_ms(200);
					u2_printf("LegPostRightHandLim");
					delay_ms(200);
				}
				else
				{
					YDT_Flag=1;	//����״̬��־λ
				}								
			}	
		}
		//��������
		if((strstr((const char *)USART2_RX_BUF,(const char *)"TYSDX"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"TYSDX")))
		{
			if(YDT_Runed>0)
			{
				Fun_Hand_DG34(0,YDT_Runed);
				if(0==YDT_Runed)
				{
					YDT_Flag=0;		//����״̬��־λ
					delay_ms(200);
					u2_printf("FW");
					delay_ms(200);
					u2_printf("DGYDTFW");
					delay_ms(200);
				}
				else
				{
					YDT_Flag=1;		//����״̬��־λ
				}					
			}			
		}
		DG_Relay=0;	       //�̵���
	}
	else
	{
		LedAlm(100,"DGGS");
	}	
}

/***********************************************************************
 ������      ��Fun_SD_ZB(void)  
 ��������    ���ֶ�ִ�����С��
 ����        ����
 ���        ����                           
************************************************************************/
void Fun_SD_ZB(void)
{
	 u8 direct;    //����ûĳ���������еķ����־��1-�������У�0-��������
	//��������ֻ���ڼ����򿪡���֫������֫��ȥ��֧�������㡢����λ������²��ܽ��д��/���ȿ���ѵ��
   if((0==ZB_Flag)&&(0==SQT_Flag)&&(0==XQT_Flag)&&(0==ZBQ_Flag)&&(0==ZF_Flag)&&(0==YF_Flag))
   {
      DG_Relay=1;	       //�̵���
		 //��������		
		if((strstr((const char *)USART2_RX_BUF,(const char *)"BZSBS"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"BZSBS")))
		{
			 //����������
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
				ZDXB_Flag=1;		//����״̬��־λ
				Fun_Hand_DG12(1,ZDB_Lim-ZDB_Runed);	
				if(ZDB_Runed==ZDB_Lim)
				{
					ZDXB_Flag=1;							//����״̬��־λ
				}
				else
				{
					ZDXB_Flag=1;					//����״̬��־λ			
				}								
			}
			//��������С��
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
		//��������
		if((strstr((const char *)USART2_RX_BUF,(const char *)"BZSBX"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"BZSBX")))
		{
			//��������С��
			if(ZXB_Runed>0)   
			{
				Fun_Hand_DG2(0,ZXB_Runed);					
			}
			//����������
			if((ZDB_Runed>0)&&(0==ZXB_Runed))
			{
				Fun_Hand_DG12(0,ZDB_Runed);	
			}
			if((0==ZDB_Runed)&&(0==ZXB_Runed))
			{
				ZDXB_Flag=0;		//����״̬��־λ
				delay_ms(200);
				u2_printf("FW");
				delay_ms(200);
				u2_printf("DGZZFW");
			}
		}
		DG_Relay=0;	       //�̵���
	}
	else
	{
		LedAlm(100,"DGGS");
	}	
}

/***********************************************************************
 ������      ��Uart_Hand_ArmLeg_Fore_Post_Left(void)  
 ��������    ���ֶ�ִ�����С��
 ����        ����
 ���        ����                           
************************************************************************/
void Fun_SD_ZT(void)
{
	 u8 direct;    //����ûĳ���������еķ����־��1-�������У�0-��������
	//��������ֻ���ڼ����򿪡���֫������֫��ȥ��֧�������㡢����λ������²��ܽ��д��/���ȿ���ѵ��
   if((0==ZB_Flag)&&(0==SQT_Flag)&&(0==XQT_Flag)&&(0==ZBQ_Flag)&&(0==ZF_Flag)&&(0==YF_Flag))
   {
     DG_Relay=1;	       //�̵���
		 //��������		
		if((strstr((const char *)USART2_RX_BUF,(const char *)"TZSTS"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"TZSTS")))
		{
			 //�����������
			if(ZDT_Lim>ZDT_Runed)
			{
				if(0==ZDXT_Flag)
				{
					delay_ms(200);
					u2_printf("KS");
					delay_ms(200);
					u2_printf("DGZTKS");
				}
				ZDXT_Flag=1;		//����״̬��־λ
				Fun_Hand_DG12(1,ZDT_Lim-ZDT_Runed);	
				if(ZDT_Runed==ZDT_Lim)
				{
					ZDXT_Flag=1;		//����״̬��־λ
				}
				else
				{
					ZDXT_Flag=1;		//����״̬��־λ
				}								
			}
			//��������С��
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
		//��������
		if((strstr((const char *)USART2_RX_BUF,(const char *)"TZSTX"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"TZSTX")))
		{
			//��������С��
			if(ZXT_Runed>0)   
			{
				Fun_Hand_DG2(0,ZXT_Runed);					
			}
			//�����������
			if((ZDT_Runed>0)&&(0==ZXT_Runed))
			{
				Fun_Hand_DG12(0,ZDT_Runed);	
			}			
			if((0==ZDT_Runed)&&(0==ZXT_Runed))
			{
				ZDXT_Flag=0;		//����״̬��־λ
				delay_ms(200);
				u2_printf("FW");
				delay_ms(200);
				u2_printf("DGZTFW");
			}				
		}
		DG_Relay=0;	       //�̵���
	}
	else
	{
		LedAlm(100,"DGGS");
	}	
}

/***********************************************************************
 ������      ��Fun_SD_YB(void)  
 ��������    ���ֶ�ִ���Ҵ�С��
 ����        ����
 ���        ����                           
************************************************************************/
void Fun_SD_YB(void)
{
	 u8 direct;     //����ûĳ���������еķ����־��1-�������У�0-��������
	//��������ֻ���ڼ����򿪡���֫������֫��ȥ��֧�������㡢����λ������²��ܽ��д��/���ȿ���ѵ��
   if((0==ZB_Flag)&&(0==SQT_Flag)&&(0==XQT_Flag)&&(0==ZBQ_Flag)&&(0==ZF_Flag)&&(0==YF_Flag))
   {
		DG_Relay=1;	       //�̵���
		 //ͬ���������ж������ۼ�
		if((strstr((const char *)USART2_RX_BUF,(const char *)"BYSBS"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"BYSBS")))
		{
			 //�������Ҵ��
			if(YDB_Lim>YDB_Runed)
			{
				if(0==YDXB_Flag)
				{
					delay_ms(200);
					u2_printf("KS");
					delay_ms(200);
					u2_printf("DGYZKS");
				}
				YDXB_Flag=1;		//����״̬��־λ
				Fun_Hand_DG34(1,YDB_Lim-YDB_Runed);	
				if(YDB_Runed==YDB_Lim)
				{
					YDXB_Flag=1;		//����״̬��־λ
				}
				else
				{
					YDXB_Flag=1;			//����״̬��־λ					
				}								
			}
			//��������С��
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
			//��������С��
			if(YXB_Runed>0)   
			{
				Fun_Hand_DG3(0,YXB_Runed);					
			}
			//�������Ҵ��
			if((YDB_Runed>0)&&(0==YXB_Runed))
			{
				Fun_Hand_DG34(0,YDB_Runed);	
			}
			if((0==YDB_Runed)&&(0==YXB_Runed))
			{
				YDXB_Flag=0;		//����״̬��־λ
				delay_ms(200);
				u2_printf("FW");
				delay_ms(200);
				u2_printf("DGYZFW");
			}			
		}
		DG_Relay=0;	       //�̵���
	}
	else
	{
		LedAlm(100,"DGGS");
	}	
}

/***********************************************************************
 ������      ��Fun_SD_YT(void)  
 ��������    ���ֶ�ִ���Ҵ�С��
 ����        ����
 ���        ����                           
************************************************************************/
void Fun_SD_YT(void)
{
	 u8 direct;     //����ûĳ���������еķ����־��1-�������У�0-��������
	//��������ֻ���ڼ����򿪡���֫������֫��ȥ��֧�������㡢����λ������²��ܽ��д��/���ȿ���ѵ��
   if((0==ZB_Flag)&&(0==SQT_Flag)&&(0==XQT_Flag)&&(0==ZBQ_Flag)&&(0==ZF_Flag)&&(0==YF_Flag))
   {
		DG_Relay=1;	       //�̵���
		 //ͬ���������ж������ۼ�
		if((strstr((const char *)USART2_RX_BUF,(const char *)"TYSTS"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"TYSTS")))
		{
			 //�������Ҵ���
			if(YDT_Lim>YDT_Runed)
			{
				if(0==YDXT_Flag)
				{
					delay_ms(200);
					u2_printf("KS");
					delay_ms(200);
					u2_printf("DGYTKS");
				}
				YDXT_Flag=1;		//����״̬��־λ
				Fun_Hand_DG34(1,YDT_Lim-YDT_Runed);	
				if(YDT_Runed==YDT_Lim)
				{
					YDXT_Flag=1;		//����״̬��־λ
				}
				else
				{
					YDXT_Flag=1;		//����״̬��־λ	
				}								
			}
			//��������С��
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
			//��������С��
			if(YXT_Runed>0)   
			{
				Fun_Hand_DG3(0,YXT_Runed);					
			}
			//�������Ҵ���
			if((YDT_Runed>0)&&(0==YXT_Runed))
			{
				Fun_Hand_DG34(0,YDT_Runed);	
			}
			if((0==YDT_Runed)&&(0==YXT_Runed))
			{
				YDXT_Flag=0;		//����״̬��־λ
				delay_ms(200);
				u2_printf("FW");
				delay_ms(200);
				u2_printf("DGYTFW");
			}				
		}
		DG_Relay=0;	       //�̵���
	}
	else
	{
		LedAlm(100,"DGGS");
	}	
}

/***********************************************************************
 ������      ��Fun_SD_ZYXB(void)  
 ��������    ���ֶ�ִ������С��
 ����        ����
 ���        ����                           
************************************************************************/
void Fun_SD_ZYXB(void)
{
	 u8 direct;     //����ûĳ���������еķ����־��1-�������У�0-��������
	 static u8 runed_flag;
	//��������ֻ���ڼ����򿪡�����֫��ȥ��֧�������㡢����λ������²��ܽ�������С��/С�ȿ���ѵ��
   if((0==ZB_Flag)&&(0==SQT_Flag)&&(0==XQT_Flag)&&(0==ZBQ_Flag)&&(0==ZF_Flag)&&(0==YF_Flag))
   {
		DG_Relay=1;	       //�̵���
		 if(0==ZYXB_Flag)    //�Ƚ�����̧֫��һ���߶�
		{
			if((strstr((const char *)USART2_RX_BUF,(const char *)"BLSXS"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"BLSXS")))
			{
				delay_ms(200);
				u2_printf("KS");
				delay_ms(200);
				u2_printf("DGZYXBKS");
				delay_ms(200);
				ZYXB_Flag=1;		//����״̬��־λ
				Fun_Hand_DG1234(1,ZYGB_Lim);
				runed_flag=1;		//����״̬��־λ
			}
		}
		//��������
		if((strstr((const char *)USART2_RX_BUF,(const char *)"BLSXS"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"BLSXS"))||(1==runed_flag))
		{	
			if(ZYXB_Lim>ZYXB_Runed)
			{
				runed_flag=0;		//����״̬��־λ
				Fun_Hand_DG23(1,ZYXB_Lim-ZYXB_Runed);	
				if(ZYXB_Runed==ZYXB_Lim)
				{
					ZYXB_Flag=1;		//����״̬��־λ
					delay_ms(200);
					u2_printf("JX");
					delay_ms(200);
					u2_printf("DGZYXBJX");
				}
				else
				{
					ZYXB_Flag=1;					//����״̬��־λ			
				}								
			}	
		}	
		//��������
		if((strstr((const char *)USART2_RX_BUF,(const char *)"BLSXX"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"BLSXX")))
		{
			if(ZYXB_Runed>0)      //����С����������
			{
				Fun_Hand_DG23(0,ZYXB_Runed);					
			}
			if(ZYXB_Runed==0)     //������С�۸�λ��������֫��λ��ˮƽλ��
			{
				Fun_Hand_DG1234(0,ZYGB_Runed);
			}
			if((ZYXB_Runed==0)&&(0==ZYGB_Runed))  //��־λ��λ
			{
				ZYXB_Flag=0;		//����״̬��־λ
				delay_ms(200);
				u2_printf("FW");
				delay_ms(200);
				u2_printf("DGZYXBFW");
			}
		}
		DG_Relay=0;	       //�̵���
	}
	else
	{
		LedAlm(100,"DGGS");
	}	
}

/***********************************************************************
 ������      ��Fun_SD_ZYXT(void)  
 ��������    ���ֶ�ִ������С��
 ����        ����
 ���        ����                           
************************************************************************/
void Fun_SD_ZYXT(void)
{
	 u8 direct;     //����ûĳ���������еķ����־��1-�������У�0-��������
	 static u8 runed_flag;
	//��������ֻ���ڼ����򿪡�����֫��ȥ��֧�������㡢����λ������²��ܽ�������С��/С�ȿ���ѵ��
   if((0==ZB_Flag)&&(0==SQT_Flag)&&(0==XQT_Flag)&&(0==ZBQ_Flag)&&(0==ZF_Flag)&&(0==YF_Flag))
   {
	    DG_Relay=1;	       //�̵���
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
				ZYXT_Flag=1;		//����״̬��־λ
				Fun_Hand_DG1234(1,ZYT_Lim);
				runed_flag=1;		//����״̬��־λ
			}				
		}
		//ͬ���������ж������ۼ�
		if((strstr((const char *)USART2_RX_BUF,(const char *)"TLSXS"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"TLSXS"))||(1==runed_flag))
		{
			if(ZYXT_Lim>ZYXT_Runed)
			{
				runed_flag=0;
				Fun_Hand_DG23(1,ZYXT_Lim-ZYXT_Runed);	
				if(ZYXT_Runed==ZYXT_Lim)
				{
					ZYXT_Flag=1;		//����״̬��־λ
					delay_ms(200);
					u2_printf("JX");
					delay_ms(200);
					u2_printf("DGZYXTJX");
				}
				else
				{
					ZYXT_Flag=1;				//����״̬��־λ				
				}								
			}	
		}
		//��������
		if((strstr((const char *)USART2_RX_BUF,(const char *)"TLSXX"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"TLSXX")))
		{
			if(ZYXT_Runed>0)    //����С����������
			{
				Fun_Hand_DG23(0,ZYXT_Runed);					
			}
			if(ZYXT_Runed==0)    //������С�ȸ�λ���������ȸ�λ��ˮƽλ��
			{
				Fun_Hand_DG1234(0,ZYT_Runed);
			}
			if((ZYXT_Runed==0)&&(0==ZYT_Runed))   //��־λ��λ
			{
				ZYXT_Flag=0;		//����״̬��־λ
				delay_ms(200);
				u2_printf("FW");
				delay_ms(200);
				u2_printf("DGZYXTFW");
			}
		}
		DG_Relay=0;	       //�̵���
	}
	else
	{
		LedAlm(100,"DGGS");	
	}	
}

/***********************************************************************
 ������      ��Fun_SD_ZYDB(void)  
 ��������    ���ֶ�ִ�����Ҵ��
 ����        ����
 ���        ����                           
************************************************************************/
void Fun_SD_ZYDB(void)
{
	 u8 direct;    //����ûĳ���������еķ����־��1-�������У�0-��������
//��������ֻ���ڼ����򿪡�����֫��ȥ��֧�������㡢����λ������²��ܽ������Ҵ��/���ȿ���ѵ��
   if((0==ZB_Flag)&&(0==SQT_Flag)&&(0==XQT_Flag)&&(0==ZBQ_Flag)&&(0==ZF_Flag)&&(0==YF_Flag))
   {
		DG_Relay=1;	       //�̵���
		 //ͬ���������ж������ۼ�		
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
				ZYDB_Flag=1;		//����״̬��־λ
				Fun_Hand_DG1234(1,ZYDB_Lim-ZYDB_Runed);	
				if(ZYDB_Runed==ZYDB_Lim)
				{
					ZYDB_Flag=1;		//����״̬��־λ
					delay_ms(200);
					u2_printf("JX");
					delay_ms(200);
					u2_printf("DGZYDBJX");
				}
				else
				{
					ZYDB_Flag=1;					//����״̬��־λ			
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
					ZYDB_Flag=0;		//����״̬��־λ
					delay_ms(200);
					u2_printf("FW");
					delay_ms(200);
					u2_printf("DGZYDBFW");
				}
				else
				{
					ZYDB_Flag=1;			//����״̬��־λ		
				}					
			}				
		}
		DG_Relay=0;	       //�̵���
	}
	else
	{
		LedAlm(100,"DGGS");
	}	
}

/***********************************************************************
 ������      ��Fun_SD_ZYDT(void)  
 ��������    ���ֶ�ִ�����Ҵ���
 ����        ����
 ���        ����                           
************************************************************************/
void Fun_SD_ZYDT(void)
{
	 u8 direct;    //����ûĳ���������еķ����־��1-�������У�0-��������
//��������ֻ���ڼ����򿪡�����֫��ȥ��֧�������㡢����λ������²��ܽ������Ҵ��/���ȿ���ѵ��
   if((0==ZB_Flag)&&(0==SQT_Flag)&&(0==XQT_Flag)&&(0==ZBQ_Flag)&&(0==ZF_Flag)&&(0==YF_Flag))
   {
		DG_Relay=1;	       //�̵���
		 //ͬ���������ж������ۼ�		
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
				ZYDT_Flag=1;			//����״̬��־λ
				Fun_Hand_DG1234(1,ZYDT_Lim-ZYDT_Runed);	
				if(ZYDT_Runed==ZYDT_Lim)
				{
					ZYDT_Flag=1;		//����״̬��־λ
					delay_ms(200);
					u2_printf("JX");
					delay_ms(200);
					u2_printf("DGZYDTJX");
				}
				else
				{
					ZYDT_Flag=1;					//����״̬��־λ				
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
					ZYDT_Flag=0;			//����״̬��־λ
					delay_ms(200);
					u2_printf("FW");
					delay_ms(200);
					u2_printf("DGZYDTFW");
				}
				else
				{
					ZYDT_Flag=1;			//����״̬��־λ		
				}					
			}			
		}
		DG_Relay=0;	       //�̵���
	}
	else
	{
		LedAlm(100,"DGGS");
	}	
}

/***********************************************************************
 ������      ��Fun_SD_ZYB(void)  
 ��������    ���ֶ�ִ�����Ҵ�С��
 ����        ����
 ���        ����                           
************************************************************************/
void Fun_SD_ZYB(void)
{
	 u8 direct;     //����ûĳ���������еķ����־��1-�������У�0-��������
//��������ֻ���ڼ����򿪡�����֫��ȥ��֧�������㡢����λ������²��ܽ��д��/���ȿ���ѵ��
   if((0==ZB_Flag)&&(0==SQT_Flag)&&(0==XQT_Flag)&&(0==ZBQ_Flag)&&(0==ZF_Flag)&&(0==YF_Flag))
   {
		DG_Relay=1;	       //�̵���
		 //�����˶�
		if((strstr((const char *)USART2_RX_BUF,(const char *)"BLSBS"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"BLSBS")))
		{
			 //���������Ҵ��
			if(ZYDB_Lim>ZYDB_Runed)
			{
				if(0==ZYDXB_Flag)
				{
					delay_ms(200);
					u2_printf("KS");
					delay_ms(200);
					u2_printf("DGZYZKS");
				}
				ZYDXB_Flag=1;		//����״̬��־λ
				Fun_Hand_DG1234(1,ZYDB_Lim-ZYDB_Runed);	
				if(ZYDB_Runed==ZYDB_Lim)
				{
					ZYDXB_Flag=1;		//����״̬��־λ
				}
				else
				{
					ZYDXB_Flag=1;		//����״̬��־λ			
				}								
			}
			//����������С��
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
			//����������С��
			if(ZYXB_Runed>0)   
			{
				Fun_Hand_DG23(0,ZYXB_Runed);					
			}
			//���������Ҵ��
			if((ZYDB_Runed>0)&&(0==ZYXB_Runed))
			{
				Fun_Hand_DG1234(0,ZYDB_Runed);	
			}
			if((0==ZYDB_Runed)&&(0==ZYXB_Runed))
			{
				ZYDXB_Flag=0;		//����״̬��־λ
				delay_ms(200);
				u2_printf("FW");
				delay_ms(200);
				u2_printf("DGZYZFW");
			}				
		}
		DG_Relay=0;	       //�̵���
	}
	else
	{
		LedAlm(100,"DGGS");
	}	
}

/***********************************************************************
 ������      ��Fun_SD_ZYT(void)  
 ��������    ���ֶ�ִ�����Ҵ�С��
 ����        ����
 ���        ����                           
************************************************************************/
void Fun_SD_ZYT(void)
{
	 u8 direct;     //����ûĳ���������еķ����־��1-�������У�0-��������
//��������ֻ���ڼ����򿪡�����֫��ȥ��֧�������㡢����λ������²��ܽ��д��/���ȿ���ѵ��
   if((0==ZB_Flag)&&(0==SQT_Flag)&&(0==XQT_Flag)&&(0==ZBQ_Flag)&&(0==ZF_Flag)&&(0==YF_Flag))
   {
		DG_Relay=1;	       //�̵���
		 //ͬ���������ж������ۼ�
		if((strstr((const char *)USART2_RX_BUF,(const char *)"TLSTS"))||
			(strstr((const char *)UART4_RX_BUF,(const char *)"TLSTS")))
		{
			 //���������Ҵ���
			if(ZYDT_Lim>ZYDT_Runed)
			{
				if(0==ZYDXT_Flag)
				{
					delay_ms(200);
					u2_printf("KS");
					delay_ms(200);
					u2_printf("DGZYTKS");
				}
				ZYDXT_Flag=1;		//����״̬��־λ
				Fun_Hand_DG1234(1,ZYDT_Lim-ZYDT_Runed);	
				if(ZYDT_Runed==ZYDT_Lim)
				{
					ZYDXT_Flag=1;		//����״̬��־λ
				}
				else
				{
					ZYDXT_Flag=1;				//����״̬��־λ				
				}								
			}
			//����������С��
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
			//����������С��
			if(ZYXT_Runed>0)   
			{
				Fun_Hand_DG23(0,ZYXT_Runed);					
			}
			//���������Ҵ���
			if((ZYDT_Runed>0)&&(0==ZYXT_Runed))
			{
				Fun_Hand_DG1234(0,ZYDT_Runed);	
			}
			if((0==ZYDT_Runed)&&(0==ZYXT_Runed))
			{
				ZYDXT_Flag=0;		//����״̬��־λ
				delay_ms(200);
				u2_printf("FW");
				delay_ms(200);
				u2_printf("DGZYTFW");
			}			
		}
		DG_Relay=0;	       //�̵���
	}
	else
	{
		LedAlm(100,"DGGS");
	}	
}

/***********************************************************************
 ������      ��Fun_FW_ALL(void)  
 ��������    �����縴λ,ÿ�����ܺ���ֹͣ��������翪��
 ����        ����
 ���        ����
                           
************************************************************************/
void Fun_FW_ALL(void)
{	
	u2_printf("��λ��ʼ");
	if(SD_Flag==1)
	{
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			//��մ���2��������
		USART2_RX_LEN=0;				//����2״̬����
		memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//��մ���4��������			
		UART4_RX_LEN=0;					  //����4״̬����
		
		//��ȡ��λ״̬��־λ
		u8 	ZF_Flag_Buf[1];
		u8 	YF_Flag_Buf[1];
		u8 	ZB_Flag_Buf[1];
		u8 	SQT_Flag_Buf[1];
		u8 	XQT_Flag_Buf[1];
		u8 	ZBQ_Flag_Buf[1];
		u8 	YL_Flag_Buf[1];	
		
	//֧����λ		
//		W25QXX_Read((u8*)ZB_Flag_Buf,35,1);       //�ӵ�33��ַ��ʼ����ȡ1���ֽ�
//		ZB_Flag=ZB_Flag_Buf[0];
//		if(1==ZB_Flag)
//		{
			u2_printf("/r/n֧����λ/r/n");
			Fun_FW_ZB(); 						
//		}
		delay_ms(1000);
		
	//���ҷ���λ	
		W25QXX_Read((u8*)ZF_Flag_Buf,33,1);       //�ӵ�33��ַ��ʼ����ȡ1���ֽ�
		W25QXX_Read((u8*)YF_Flag_Buf,34,1);       //�ӵ�34��ַ��ʼ����ȡ1���ֽ�
		ZF_Flag=ZF_Flag_Buf[0];
		YF_Flag=YF_Flag_Buf[0];		
		if((1==ZF_Flag)&&(0==YF_Flag))     //�󷭸�λ
		{			
			u2_printf("/r/n�󷭸�λ/r/n");
			Fun_FW_ZF();    		
		}		
		if((0==ZF_Flag)&&(1==YF_Flag))      //�ҷ���λ
		{
			u2_printf("/r/n�ҷ���λ/r/n");
			Fun_FW_YF();   			
		} 
		delay_ms(1000);	

	//������ģ�鸴λ
//		W25QXX_Read((u8*)ZBQ_Flag_Buf,38,1);       //�ӵ�33��ַ��ʼ����ȡ1���ֽ�
//		ZBQ_Flag=ZBQ_Flag_Buf[0];
		if(1==GD6_CS)
		{
			u2_printf("/r/n��ϴ����Ƹ˸�λ/r/n");
			ZBQ_Flag=1;		//����״̬��־λ
			RELAY6=1; 
			Fun_ZBCX(0,CXHG_Lim);  //��ϴ����Ƹ�����
			RELAY6=0;	      					
			delay_ms(1000);
			
			u2_printf("/r/n������Ƹ˸�λ/r/n");
			ZBQ_Flag=1;		//����״̬��־λ
			RELAY6=1;              //�̵����õ�
			Fun_ZBTG(0,ZBDTG_Lim);      //�����Ƹ�����	
			RELAY6=0;           
			delay_ms(1000);
			
			u2_printf("/r/n��������λ/r/n");
			SQT_Flag=0;		//����״̬��־λ
			ZF_Flag=0;		//����״̬��־λ
			YF_Flag=0;		//����״̬��־λ
			ZBQ_Pic=24;
			Fun_ZBQ(1);           //��������λ  
		}			
		delay_ms(1000);

	//С���Ӹ�λ	
		if(1==GD7_CS)
		{
			u2_printf("/r/nС���Ӹ�λ/r/n");
			Fun_FW_YL();         //�칫����һ������λ 					
			delay_ms(1000);
		}
		
	//�������ȸ�λ		
//		W25QXX_Read((u8*)SQT_Flag_Buf,36,1);      //�ӵ�34��ַ��ʼ����ȡ1���ֽ�
//		W25QXX_Read((u8*)XQT_Flag_Buf,37,1);      //�ӵ�33��ַ��ʼ����ȡ1���ֽ�		
//		SQT_Flag=SQT_Flag_Buf[0];
//		XQT_Flag=XQT_Flag_Buf[0];		
//		if((1==SQT_Flag)||(1==XQT_Flag))
//		{
			u2_printf("/r/n���ȸ�λ/r/n");
			Fun_FW_QT();         //���ȸ�λ
			u2_printf("��λ����");
//		}
		
		ZF_Flag=0;		//����״̬��־λ
		YF_Flag=0;		//����״̬��־λ
		ZB_Flag=0;		//����״̬��־λ
		SQT_Flag=0;		//����״̬��־λ
		XQT_Flag=0;		//����״̬��־λ
		ZBQ_Flag=0;		//����״̬��־λ
		YL_Flag=0;		//����״̬��־λ
		W25QXX_Write((u8*)&ZF_Flag,33,1);		//��״̬��־λд��flash
		W25QXX_Write((u8*)&YF_Flag,34,1);		//��״̬��־λд��flash
		W25QXX_Write((u8*)&ZB_Flag,35,1);		//��״̬��־λд��flash
		W25QXX_Write((u8*)&SQT_Flag,36,1);		//��״̬��־λд��flash
		W25QXX_Write((u8*)&XQT_Flag,37,1);		//��״̬��־λд��flash
		W25QXX_Write((u8*)&ZBQ_Flag,38,1);		//��״̬��־λд��flash
		W25QXX_Write((u8*)&YL_Flag,39,1);		//��״̬��־λд��flash
	}
}


/***********************************************************************
 ������      ��Fun_FW_ALL_GD(void)  
 ��������    �����縴λ,ÿ�����ܺ���ֹͣ��������翪��
 ����        ����
 ���        ����
                           
************************************************************************/
void Fun_FW_ALL_GD(void)
{	
	u2_printf("��λ��ʼ");
	if(SD_Flag==1)
	{
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			//��մ���2��������
		USART2_RX_LEN=0;				//����2״̬����
		memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//��մ���4��������			
		UART4_RX_LEN=0;					  //����4״̬����
		
		u2_printf("/r/n֧����λ/r/n");
		Fun_FW_ZB(); 			
		delay_ms(1000);
		
		//��ȡ��λ״̬��־λ
		u8 	ZF_Flag_Buf[1];
		u8 	YF_Flag_Buf[1];
		u8 	ZB_Flag_Buf[1];
		u8 	SQT_Flag_Buf[1];
		u8 	XQT_Flag_Buf[1];
		u8 	ZBQ_Flag_Buf[1];
		u8 	YL_Flag_Buf[1];
				
		W25QXX_Read((u8*)ZF_Flag_Buf,33,1);       //�ӵ�33��ַ��ʼ����ȡ1���ֽ�
		W25QXX_Read((u8*)YF_Flag_Buf,34,1);       //�ӵ�34��ַ��ʼ����ȡ1���ֽ�
		W25QXX_Read((u8*)ZB_Flag_Buf,35,1);       //�ӵ�33��ַ��ʼ����ȡ1���ֽ�
		W25QXX_Read((u8*)SQT_Flag_Buf,36,1);      //�ӵ�34��ַ��ʼ����ȡ1���ֽ�
		W25QXX_Read((u8*)XQT_Flag_Buf,37,1);      //�ӵ�33��ַ��ʼ����ȡ1���ֽ�
		W25QXX_Read((u8*)ZBQ_Flag_Buf,38,1);      //�ӵ�34��ַ��ʼ����ȡ1���ֽ�
		W25QXX_Read((u8*)YL_Flag_Buf,39,1);       //�ӵ�34��ַ��ʼ����ȡ1���ֽ�
		
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
						
				
		if((1==ZF_Flag)&&(0==YF_Flag))     //�󷭸�λ
		{			
			u2_printf("/r/n�󷭸�λ/r/n");
			Fun_FW_ZF();    		
		}		
		if((0==ZF_Flag)&&(1==YF_Flag))      //�ҷ���λ
		{
			u2_printf("/r/n�ҷ���λ/r/n");
			Fun_FW_YF();   			
		} 
		delay_ms(1000);				
		
		if(1==ZBQ_Flag)
		{
			u2_printf("/r/n��ϴ����Ƹ˸�λ/r/n");
			ZBQ_Flag=1;		//����״̬��־λ
			RELAY6=1; 
			Fun_ZBCX(0,CXHG_Lim);  //��ϴ����Ƹ�����
			RELAY6=0;	      					
			delay_ms(1000);
			
			u2_printf("/r/n������Ƹ˸�λ/r/n");
			ZBQ_Flag=1;		//����״̬��־λ
			RELAY6=1;              //�̵����õ�
			Fun_ZBTG(0,ZBDTG_Lim);      //�����Ƹ�����	
			RELAY6=0;           
			delay_ms(1000);
			
			u2_printf("/r/n��������λ/r/n");
			SQT_Flag=0;		//����״̬��־λ
			ZF_Flag=0;		//����״̬��־λ
			YF_Flag=0;		//����״̬��־λ
			ZBQ_Pic=24;
			Fun_ZBQ(1);           //��������λ  
		}			
		delay_ms(1000);
			
		u2_printf("/r/nС���Ӹ�λ/r/n");
		Fun_FW_YL();         //�칫����һ������λ 					
		delay_ms(1000);
			
		u2_printf("/r/n���ȸ�λ/r/n");
		Fun_FW_QT();         //���ȸ�λ
		u2_printf("��λ����");
		
		ZF_Flag=0;		//����״̬��־λ
		YF_Flag=0;		//����״̬��־λ
		ZB_Flag=0;		//����״̬��־λ
		SQT_Flag=0;		//����״̬��־λ
		XQT_Flag=0;		//����״̬��־λ
		ZBQ_Flag=0;		//����״̬��־λ
		YL_Flag=0;		//����״̬��־λ
		W25QXX_Write((u8*)&ZF_Flag,33,1);		//��״̬��־λд��flash
		W25QXX_Write((u8*)&YF_Flag,34,1);		//��״̬��־λд��flash
		W25QXX_Write((u8*)&ZB_Flag,35,1);		//��״̬��־λд��flash
		W25QXX_Write((u8*)&SQT_Flag,36,1);		//��״̬��־λд��flash
		W25QXX_Write((u8*)&XQT_Flag,37,1);		//��״̬��־λд��flash
		W25QXX_Write((u8*)&ZBQ_Flag,38,1);		//��״̬��־λд��flash
		W25QXX_Write((u8*)&YL_Flag,39,1);		//��״̬��־λд��flash
	}
}


/***********************************************************************
 ������      ��Fun_FW_ZB(void)  
 ��������    ��֧����λ�����ڵ��縴λ
 ����        ����
 ���        ����
                           
************************************************************************/
void Fun_FW_ZB(void)
{
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			//��մ���2��������
	USART2_RX_LEN=0;					//����2״̬����
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//��մ���4��������		
	UART4_RX_LEN=0;				  //����4״̬����
	ZF_Flag=0;		//����״̬��־λ
	YF_Flag=0;		//����״̬��־λ
	ZB_Runed=Ang_To_Arr_ZB(ZB_Lim);				//��������������ֵΪ����ֵ
	ZB_Pic=19;
	WriteInU2("ZBX");
	Fun_ZB();                //֧����λ	
	ZB_Flag=0;		//����״̬��־λ
}

/***********************************************************************
 ������      ��Fun_FW_QT(void)  
 ��������    �����ȸ�λ�����ڵ��縴λ
 ����        ����
 ���        ����
                           
************************************************************************/
void Fun_FW_QT(void)
{
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			//��մ���2��������
	USART2_RX_LEN=0;					//����2״̬����
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//��մ���4��������		
	UART4_RX_LEN=0;				  //����4״̬����
	SQT_Flag=0;		//����״̬��־λ
	ZF_Flag=0;		//����״̬��־λ
	YF_Flag=0;		//����״̬��־λ
	XQT_Runed=Ang_To_Arr_SXQT(XQT_Lim);  				//��������������ֵΪ����ֵ
	XQT_Pic=19;
	WriteInU2("XQTS");
	Fun_XQT();           
	delay_ms(1000);
	
	XQT_Flag=0;			//����״̬��־λ
	WriteInU2("SQTS");
	Fun_SQT();              //������
	delay_ms(1000);
	WriteInU2("SQTX");
	Fun_SQT();              //�����ȸ�λ
	SQT_Flag=0;		//����״̬��־λ
}

/***********************************************************************
 ������      ��Fun_FW_YL(void)  
 ��������    ���Ͳ�����һ������λ�����ڵ��縴λ
 ����        ����
 ���        ����
                           
************************************************************************/
void Fun_FW_YL(void)
{
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			//��մ���2��������
	USART2_RX_LEN=0;					//����2״̬����
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//��մ���4��������		
	UART4_RX_LEN=0;				  //����4״̬����
	ZF_Flag=0;		//����״̬��־λ
	YF_Flag=0;		//����״̬��־λ
	YL_Runed=Ang_To_Arr_YL(YL_Lim);				//��������������ֵΪ����ֵ
	YL_Pic=19;
	WriteInU2("YLX");
	Fun_YL1();             //С���Ӹ�λ
	YL_Flag=0;		//����״̬��־λ
}

	
/***********************************************************************
 ������      ��Uart_Reset_Motor5_0(void)  
 ��������    ��5�ŵ����λ:
 ����        ������λ0;����λ1
 ���        ����
                           
************************************************************************/
void Fun_FW_CF(u8 dir) 
{
	u8 key;
	u16 arr_feed;      //��������е�ǰһ������������,�����жϵ��ʧ������
	u16 pulse_num=0;   //�������е�ǰһ����������������ת�������������ĵ�ǰ������������Ƚ�
	u16 num=0;
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);		//��մ���2��������	
	USART2_RX_LEN=0;	  //����2״̬����
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);				//��մ���4��������	
	UART4_RX_LEN=0;				  //����4״̬����
	MotorStart(5,dir,1400-1,25-1);				 //5�ŵ������
	u2_printf("*%s*M5*F*0*/**",RX_BUF);		//����2����
	if(1==ZF_Flag)
	{
		TIM10_Init(Ang_To_Arr_ZYFS(ZF_Lim),65000);          //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
	}
	if(1==YF_Flag)
	{
		TIM10_Init(Ang_To_Arr_ZYFS(YF_Lim),65000);           //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
	}
	__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //����жϱ�־λ
	while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) )
	{				
		//�����λ
		if(0==GD5_CS)   //������翪������ѭ�������ͣת 
		{
			delay_us(100);
			if(0==GD5_CS)
			{
				u2_printf("GD5CS");
				break;	
			}				
		}
		//�������
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
		  //�ж���û���յ���λ��ָ��		
		if(USART2_RX_LEN&0x8000)
		{
			u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���	
			memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			//��մ���2��������
			USART2_RX_LEN=0;						//����2״̬����										
		}
		if(UART4_RX_LEN&0x8000)
		{
			u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���	
			memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//��մ���4��������		
			UART4_RX_LEN=0;				//����4״̬����								
		}		
	}		      
	MotorStop(5);   u2_printf("*%s*M5*T*0*/**",RX_BUF);    //���ֹͣ
	TIM10_Stop();       //�رն�ʱ��
	__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //����жϱ�־λ	
	//����ʱʱ�䵽���ǹ��û��������������һ�ξ��룬�����翪��λ�ã���翪�ذ�װ��򿪴˶Σ�
//	if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))&&(GD5_CS==1)&&(direct==0))
//	{  
//		MotorStart(5,dir,1400-1,25-1);   			 //5�ŵ������
//		u2_printf("*%s*M5*F*0*/**",RX_BUF);
//		TIM10_Init(add_arr,65000);                     //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
//		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //����жϱ�־λ	 	
//		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))
//		{			
//			if(0==GD5_CS)  //����ʱ������翪�أ�����ѭ�� 
//			{
//				delay_us(100);
//				if(0==GD5_CS) 
//				{
//					u2_printf("GD5CS");
//					break;	
//				}					
//			}
//		}			
//		MotorStop(5);       //���ֹͣ
//	    TIM10_Stop();       //�رն�ʱ��
//		if(0==GD5_CS)
//		{
//			u2_printf("*%s*M5*T*0*/**",RX_BUF);
//		}
//		else
//		{
//			u2_printf("*%s*M5*T*0*/**",RX_BUF);
//		}
//		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ	
//	}	
}


/***********************************************************************
 ������      ��Fun_FW_ZF(void)  
 ��������    ������λ�����ڵ��縴λ
 ����        ����
 ���        ����
                           
************************************************************************/
void Fun_FW_ZF(void)
{		
	//4�ŵ����λ
	if(1==GD4_CS)
	{
		SD_Flag=1;		//����״̬��־λ
		ZF_Flag=1;		//����״̬��־λ
		ZBH_Flag=0;		//����״̬��־λ
		ZYH_Dir_flag=0;		//���÷���״̬��־λ
		ZYH_Pic=0;			//ͼƬ��־��Ϊ0
		ZYH_Runed=Ang_To_Arr_ZYFS(ZF_Lim);	//��������������ֵΪ����ֵ
		Fun_ZYH();    //����������λ
		ZYH_Flag=0;		//����״̬��־λ
	}
	//3�ŵ����λ
	if(1==GD3_CS)
	{
		SD_Flag=1;		//����״̬��־λ
		ZF_Flag=1;		//����״̬��־λ
		ZYH_Flag=0;		//����״̬��־λ
		ZBH_Dir_flag=0;	//���÷���״̬��־λ
		ZBH_Pic=0;	//ͼƬ��־��Ϊ0
		ZBH_Runed=Ang_To_Arr_ZYFS(ZF_Lim);	//��������������ֵΪ����ֵ
		Fun_ZBH();     //�󱳲�����λ
		ZBH_Flag=0;	//���÷���״̬��־λ
	}
	
	//5�ŵ����λ
	if(1==GD5_CS)
	{
		Fun_FW_CF(0); 
	}
	ZF_Runed=0;				//����������ֵ��Ϊ0
	ZF_Flag=0;		//����״̬��־λ
	ZBH_Flag=0;		//����״̬��־λ
	ZYH_Flag=0;		//����״̬��־λ
	ZBH_Dir_flag=0;		//���÷���״̬��־λ
	ZYH_Dir_flag=0;		//���÷���״̬��־λ
	ZYH_Pic=0;			//ͼƬ��־��Ϊ0
	ZBH_Pic=0;			//ͼƬ��־��Ϊ0
}

/***********************************************************************
 ������      ��Fun_FW_YF(void)  
 ��������    ���ҷ���λ�����ڵ��縴λ
 ����        ����
 ���        ����
                           
************************************************************************/
void Fun_FW_YF(void)
{
	//4�ŵ����λ
	if(1==GD4_CS)
	{
		SD_Flag=1;		//����״̬��־λ
		YF_Flag=1;		//����״̬��־λ
		YBH_Flag=0;		//����״̬��־λ
		YYH_Dir_flag=0;		//���÷���״̬��־λ
		YYH_Pic=0;			//ͼƬ��־��Ϊ0
		YYH_Runed=Ang_To_Arr_ZYFS(YF_Lim);	//��������������ֵΪ����ֵ
		Fun_YYH();   //����������λ
		YYH_Flag=0;		//����״̬��־λ
	}
	
	//3�ŵ����λ
	if(1==GD3_CS)
	{
		SD_Flag=1;		//����״̬��־λ
		YF_Flag=1;		//����״̬��־λ
		YYH_Flag=0;		//����״̬��־λ
		YBH_Dir_flag=0;		//���÷���״̬��־λ
		YBH_Pic=0;			//ͼƬ��־��Ϊ0
		YBH_Runed=Ang_To_Arr_ZYFS(YF_Lim);	//��������������ֵΪ����ֵ
		Fun_YBH();    //�ұ�������λ
		YBH_Flag=0;		//����״̬��־λ
	}
	
	//5�ŵ����λ
	if(1==GD5_CS)
	{	
		Fun_FW_CF(1);
	}	
	YF_Runed=0;			//����������ֵ��Ϊ0
	YF_Flag=0;		//����״̬��־λ
	YBH_Flag=0;		//����״̬��־λ
	YYH_Flag=0;		//����״̬��־λ
	YBH_Dir_flag=0;		//���÷���״̬��־λ
	YYH_Dir_flag=0;		//���÷���״̬��־λ
	YYH_Pic=0;			//ͼƬ��־��Ϊ0
	YBH_Pic=0;			//ͼƬ��־��Ϊ0	
}


/***********************************************************************
 ������      �� 
 ��������    �����Ҳ��Ժ���
 ����        ����
 ���        ����
***********************************************************************/                           
void  TestAll(u8 dir)
{
	Hang_Init();         //�������ڳ�ʼ������
	int i,flag=1;        //flagΪ����ߵͱ�־λ
	int j=0,k=0;
	DG_DIR1=dir;       //3�ŵ��ҵ��ת��������ƣ��ߵ�ƽ��ת���͵�ƽ��ת 
	DG_DIR2=!dir;
	DG_DIR3=dir;
	DG_DIR4=!dir;
	
 	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//��մ���2��������		
	USART2_RX_LEN=0; 				//����2״̬����
	u2_printf("Hang_TestAll");
	TIM10_Init(DG_Freq,25-1);               //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
    for(i=0;i<1500000;i++)
    { 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) );   //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��
		flag = !flag ;
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);             //����жϱ�־λ
		DG_PWM1=flag;        //���ҵ����������ڸ�/�͵�ƽ				 
		DG_PWM2=flag;
		DG_PWM3=flag;
		DG_PWM4=flag;
	}
	DG_PWM1=0;              //3�ŵ��ҵ����Ӧ������������� 
	DG_PWM2=0;
	DG_PWM3=0;
	DG_PWM4=0;
	TIM10_Stop();             //�رն�ʱ��
	u2_printf("Hang_TestAll_Stop");
}	


/***********************************************************************
 ������      ��Hang1(u8 dir)
 ��������    �����Ҳ��Ժ���
 ����        ��dir��������
 ���        ����
***********************************************************************/   
void Hang1(u8 dir)
{
	Hang_Init();         //�������ڳ�ʼ������
	int i,flag=1;        //flagΪ����ߵͱ�־λ
	int j=0,k=0;
	DG_DIR1=dir;       //3�ŵ��ҵ��ת��������ƣ��ߵ�ƽ��ת���͵�ƽ��ת 
	u2_printf("Hang1");
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			//��մ���2��������
	USART2_RX_LEN=0; 				//����2״̬����
	TIM10_Init(DG_Freq,25-1);    //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
	
    for(i=0;i<1500000;i++)   //����ȷ��Ϊ3000000
    { 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) );   //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��
		flag = !flag ;
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);             //����жϱ�־λ
		DG_PWM1=flag;               //3�ŵ��ҵ����������ڸߵ�ƽ				 
	}
	DG_PWM1=0;              //3�ŵ��ҵ����Ӧ������������� 
	TIM10_Stop();             //�رն�ʱ��
	u2_printf("Hang1_Stop");
}
/***********************************************************************
 ������      ��Hang2(u8 dir)
 ��������    �����Ҳ��Ժ���
 ����        ��dir��������
 ���        ����
***********************************************************************/ 
void Hang2(u8 dir)
{
	Hang_Init();         //�������ڳ�ʼ������
	int i,flag=1;        //flagΪ����ߵͱ�־λ
	int j=0,k=0;
	DG_DIR2=dir;         //3�ŵ��ҵ��ת��������ƣ��ߵ�ƽ��ת���͵�ƽ��ת 
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			//��մ���2��������
	USART2_RX_LEN=0; 				//����2״̬����
	TIM10_Init(DG_Freq,25-1);          //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
	u2_printf("Hang2");
    for(i=0;i<1500000;i++)  //����ȷ��Ϊ3000000
    { 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) );   //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��
		flag = !flag ;
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);             //����жϱ�־λ
		DG_PWM2=flag;               //3�ŵ��ҵ����������ڸߵ�ƽ				 
	}
	DG_PWM2=0;               //3�ŵ��ҵ����Ӧ������������� 
	TIM10_Stop();             //�رն�ʱ��
	u2_printf("Hang2_Stop");
}
/***********************************************************************
 ������      ��Hang3(u8 dir)
 ��������    �����Ҳ��Ժ���
 ����        ��dir��������
 ���        ����
***********************************************************************/ 
void Hang3(u8 dir)
{
	Hang_Init();         //�������ڳ�ʼ������
	int i,flag=1;        //flagΪ����ߵͱ�־λ
	int j=0,k=0;
	DG_DIR3=dir;       //3�ŵ��ҵ��ת��������ƣ��ߵ�ƽ��ת���͵�ƽ��ת 
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//��մ���2��������		
	USART2_RX_LEN=0; 				//����2״̬����
	TIM10_Init(DG_Freq,25-1);        //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
	u2_printf("Hang3");
    for(i=0;i<1500000;i++)   //����ȷ��Ϊ3000000
    { 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) );   //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��
		flag = !flag ;
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);             //����жϱ�־λ
		DG_PWM3=flag;               //3�ŵ��ҵ����������ڸߵ�ƽ				 
	}
	DG_PWM3=0;              //3�ŵ��ҵ����Ӧ������������� 
	TIM10_Stop();             //�رն�ʱ��
	u2_printf("Hang3_Stop");
}
/***********************************************************************
 ������      ��Hang4(u8 dir)
 ��������    �����Ҳ��Ժ���
 ����        ��dir��������
 ���        ����
***********************************************************************/ 
void Hang4(u8 dir)
{
	Hang_Init();         //�������ڳ�ʼ������
	int i,flag=1;        //flagΪ����ߵͱ�־λ
	int j=0,k=0;
	DG_DIR4=dir;         //3�ŵ��ҵ��ת��������ƣ��ߵ�ƽ��ת���͵�ƽ��ת 
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);		//��մ���2��������	
	USART2_RX_LEN=0; 						//����2״̬����
	TIM10_Init(DG_Freq,25-1);     //�򿪶�ʱ������ʱ������=(freq1*freq_time1_1)/90mhz	
	u2_printf("Hang4");
    for(i=0;i<1500000;i++)    //����ȷ��Ϊ3000000
    { 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) );   //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��
		flag = !flag ;
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);             //����жϱ�־λ
		DG_PWM4=flag;         //4�ŵ��ҵ����������ڸߵ�ƽ		
	}
	DG_PWM4=0;                //4�ŵ��ҵ����Ӧ������������� 
	TIM10_Stop();             //�رն�ʱ��
	u2_printf("Hang4_Stop");
}
/***********************************************************************
 ������      ��DeskRunNew()
 ��������    ��С��������
 ����        ��
 ���        ��
***********************************************************************/ 
void DeskRunNew(void)
{
	u8 direct;    //��ʾ������з���1��С����ǰ����0��С���Ӻ���
	u16 arr_now;      //������������ֵ
	u8 len;           //��ʾ���յ��ַ����ĳ���
	u8 err=0;
//ʵ����λ��ʵʱ��ʾ������ǰ�˶�״̬ 
	static u8 k=0;            //���͵�k��ͼƬ
	static u8 kj=0;
	u8 j=0;	
	u16 arr_send;                 //��ǰһ������������
	static u8 yljx_flag;    //�ж�С�����Ƿ����е�����λ�ã����Ƿ��ͼ���λ��ͼƬ	
	//�������ܣ�ֻ�������ҷ����ܸ�λ�󣬲��ܽ���С�����ƶ�
	if((ZF_Flag==0)&&(YF_Flag==0))
	{		
		if(((strstr((const char *)USART2_RX_BUF,(const char *)"YLS"))||(strstr((const char *)UART4_RX_BUF,(const char *)"YLS"))))
		{
			direct=1;			//�������з����־
			if(yljx_flag==1)
			{err=1;u2_printf("err\r\n");}
			if((YL_Flag==0)&&(err==0))
			{
				YL_Flag=1;		//����״̬��־λ
			//	W25QXX_Write((u8*)&YL_Flag,39,1);		//��״̬��־λд��flash
				delay_ms(200);
				u2_printf("YL_flag==1");
				delay_ms(200);
				u2_printf("YLKS");
				delay_ms(200);
				u2_printf("CT_YL1");
			}
			
			if((20*(YL_Lim)>YL_Runed)&&(err==0))  //����ʱ���Ƚ�ֵΪ���м���װ��ֵ��У׼��ĵ���װ��ֵ�Ĳ�ֵ��������ֵ����Ϊ0
			{
				u2_printf("*%s*M7*Z*0*/**",RX_BUF);		//����2����
				MotorStart(7,0,700-1,25-1);
				TIM2_Init(2000,900);
				//TIM2_Init(Ang_To_Arr_YL2(YL_Lim)-YL_Runed,65000);  //��ʱ������=(freq1*freq_time1_1)/90mhz			
			}	
		}
		if(((strstr((const char *)USART2_RX_BUF,(const char *)"YLX"))||(strstr((const char *)UART4_RX_BUF,(const char *)"YLX"))))
		{
			direct=0;			//�������з����־
			if(YL_Runed==0)
			{err=1;u2_printf("err\r\n");}
			if((1==yljx_flag)&&(err==0))
			{
				yljx_flag=0;	//���ü���״̬��־λ
				delay_ms(200);
				u2_printf("CT_YL20");
			}
			if((YL_Runed>0)&&(err==0))    //����ʱ���Ƚ�ֵΪУ׼��ĵ���װ��ֵ��0,�Ҳ���Ϊ0
			{
				u2_printf("*%s*M7*F*0*/**",RX_BUF);		//����2����
				MotorStart(7,1,700-1,25-1);
				TIM2_Init(2000,900);	//��ʱ����ʱ20ms
			//	TIM2_Init(YL_Runed,65000);  //��ʱ������=(freq1*freq_time1_1)/90mhz			
			}
		}
		memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//��մ���2��������		
		USART2_RX_LEN=0;				//����2״̬����
		memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//��մ���4��������			
		UART4_RX_LEN=0;				  //����4״̬����
		 if((((YL_Runed!=20*(YL_Lim))&&(1==direct))||((0!=YL_Runed)&&(0==direct)))&&(err==0))
		 {	 	
			while((YL_Runed+(-1)*(1-direct*2)*T2RunTimes)<20*(YL_Lim))  //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��  
			{						
				//�����λ											   						
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
				//ָֹͣ��
				if(USART2_RX_LEN&0x8000)
				{
					len=USART2_RX_LEN&0x3fff;	//��ȡ����2���������ַ�����				
					USART2_RX_BUF[len]=0;			//����2����ĩβ��"0"
					if((strstr((const char *)USART2_RX_BUF,(const char *)"STOP"))||(strstr((const char *)USART2_RX_BUF,(const char *)"YLS"))||(strstr((const char *)USART2_RX_BUF,(const char *)"YLX")))    //�����յ�Stop,������ѭ��	
					{
//						memcpy(RX_BUF,USART2_RX_BUF,15);
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//��մ���2��������		
						USART2_RX_LEN=0;			//����2״̬����
						break;
					}
					else
					{
						u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���							
						memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);		//��մ���2��������	
						USART2_RX_LEN=0;			//����2״̬����
					}						
				}	
				if(UART4_RX_LEN&0x8000)
				{
					len=UART4_RX_LEN&0x3fff;		//��ȡ����4���������ַ�����			
					UART4_RX_BUF[len]=0;				//����4����ĩβ��"0"
					if((strstr((const char *)UART4_RX_BUF,(const char *)"STOP"))||(strstr((const char *)UART4_RX_BUF,(const char *)"YLS"))||(strstr((const char *)UART4_RX_BUF,(const char *)"YLX")))    //�����յ�Stop,������ѭ��	
					{
//						memcpy(RX_BUF,UART4_RX_BUF,15);
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			//��մ���4��������		
						UART4_RX_LEN=0;				  //����4״̬����
						break;
					}
					if(strstr((const char *)UART4_RX_BUF,(const char *)"SEND OK"))
					{	}
					else
					{
						u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���							
						memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//��մ���4��������			
						UART4_RX_LEN=0;				  //����4״̬����
					}						
				}
				//������ϡ��������
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
				
				//���Ͷ���ָ��
				// arr_send=__HAL_TIM_GET_COUNTER(&TIM2_Handler);		//��ȡ��ǰ�Ĵ�������װ��ֵ
				
				if(direct==1)
				{
					j=(YL_Runed+T2RunTimes)/(20*(YL_Lim)/19);		//ͼƬ��ż���
				}
				else
				{
					j=abs(YL_Runed,T2RunTimes)/(20*(YL_Lim)/19);		//ͼƬ��ż���
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
							u2_printf("CT_YL%d",YL_Pic);		//����2���Ͷ���ͼƬָ��
						}
					}					
				}
			}
			arr_now=T2RunTimes;
			MotorStop(7);       //���ֹͣ			
			TIM2_Close();        //��ʱ���ر�
			T2RunTimes=0;
			u2_printf("*%s*M7*T*0*/**",RX_BUF);		//����2����
			//�жϸ�λ

			if(direct==1)
			{
				YL_Runed+=arr_now;		//���ȼ��㵱ǰ�������е�20ms����
				if(YL_Runed<20*(YL_Lim))
				{
					YL_Flag=1;		//��־λ��1
				}
				else
				{
					YL_Runed=20*(YL_Lim);				//��������������ֵΪ����ֵ
					yljx_flag=1;		//���ü���״̬��־λ
					delay_ms(200);
					u2_printf("CT_YL20");
					delay_ms(200);
					u2_printf("YLJX");
				}	
			}
			else
			{				
				if(YL_Runed<arr_now)		//�ж��Ƿ����������
				{err=1;}			
				YL_Runed-=arr_now;	//���ȼ��㵱ǰ�������е�20ms����				
				if((YL_Runed>0)&&(err==0))
				{
					YL_Flag=1;		//��־λ��1
				}
				else
				{
					YL_Runed=0;
					arr_now=0;         //��ʱ���ڸ�λ״̬����״ֵ̬����Ϊ0��
					YL_Flag=0;		//����״̬��־λ
				//	W25QXX_Write((u8*)&YL_Flag,39,1);		//��״̬��־λд��flash
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
		LedAlm(100,"YLGS");//��������������LED0/LED1��һ��
	}	
}


