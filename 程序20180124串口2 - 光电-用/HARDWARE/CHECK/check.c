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
 ������      ��Fun_GZCL(void)  
 ��������    ��������ϴ������������ڵ�����Ϻ󣬷�ָ�λ������
 ����        ����
 ���        ��1�������ų��󣬷���1
                           
************************************************************************/
u8 Fun_GZCL(void)
{
	u8 len;
	Motor_All_Stop();	            //���е��ֹͣ
	u2_printf("Fault_Warning");     //����λ���������ϱ����ź�	
	PCF8574_WriteBit(BEEP_IO,0);	//���Ʒ���������������
	delay_ms(2000);
	PCF8574_WriteBit(BEEP_IO,1);
	
/*************�жϵ�����ع���**********************************/	
		
	//����
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
	//�󱳲�����
	if(1==ZBH_GZ)      
	{	
		u2_printf("ZBHGZ");	
	}
	//����������
	if(1==ZYH_GZ)     
	{	
		u2_printf("ZYHGZ");		
	}	
	//�ҷ���
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
	//�ұ�������
	if(1==ZBH_GZ)      
	{	
		u2_printf("YBHGZ");		
	}
	//����������
	if(1==YYH_GZ)      
	{	
		u2_printf("YYHGZ");		
	}		
	 //�Զ�����
	if(1==ZBQ_GZ)   
	{	
		u2_printf("ZBQGZ");	
	}
	//С����
	if(1==YL_GZ)            
	{	
		u2_printf("YLGZ");	
	}
    
	memset(USART2_RX_BUF,0,len);   //�������
	USART2_RX_LEN=0;               //�����־λ
	memset(UART4_RX_BUF,0,len);    //�������
	UART4_RX_LEN=0;
	//��ͨ��ָ���ֶ���λ�����������������£������ų���ɷ��ص�ԭ������
	while(1)
	{
		if(USART2_RX_LEN&0x8000)
		{
			len=USART2_RX_LEN&0x3fff;				
			USART2_RX_BUF[len]=0;			
			if(strstr((const char *)USART2_RX_BUF,(const char *)"FWZBB"))
			{
				Fun_FW_ZB();     		    //֧����λ
			}

			if(strstr((const char *)USART2_RX_BUF,(const char *)"FWQT")) 
			{			
				Fun_FW_QT();   		    //���ȸ�λ
			}
			if(strstr((const char *)USART2_RX_BUF,(const char *)"FWZBQ"))
			{			
				Fun_ZBQ(1);	            //��������λ
			}	
			
			if(strstr((const char *)USART2_RX_BUF,(const char *)"FWZF")) 
			{			
				Fun_FW_ZF();              //����λ					
			}

			if(strstr((const char *)USART2_RX_BUF,(const char *)"FWYF"))
			{			
				Fun_FW_YF();              //�ҷ���λ	
			}						
			
			if(strstr((const char *)USART2_RX_BUF,(const char *)"FWYL")) 
			{			
				Fun_FW_YL();             //�Ͳ�����һ������λ
			}
			
			if(strstr((const char *)USART2_RX_BUF,(const char *)"FWALL")) 
			{			
				Fun_FW_ALL();            //���й���һ��λ
			}			
		
			if(strstr((const char *)USART2_RX_BUF,(const char *)"WC"))   //�������ų�������ԭ����
			{			
				u2_printf("FaultSolved");				
			
/*********************����־λ������Ϊ0***********************/
				
				//������ر�־λ			
				ZF3_GZ=0;          //����
				ZF4_GZ=0;          
				ZF5_GZ=0;          
				YF3_GZ=0;          //�ҷ���
				YF4_GZ=0;         
				YF5_GZ=0; 
				ZBQ_GZ=0;          //�Զ�����
				YL_GZ=0;           //�Ͳ�����һ����
				ZBH_GZ=0;          //�󱳲�����
				YBH_GZ=0;          //�ұ�������
				ZYH_GZ=0;          //����������
				YYH_GZ=0;          //����������
				
				//���ʧ����־λ	
				ZF_SB=0;          //���� 
				YF_SB=0;          //�ҷ���
				ZBQ_SB=0;         //�Զ�����
				YL_SB=0;          //�Ͳ�����һ����
				ZBH_SB=0;         //�󱳲�����
				YBH_SB=0;         //�ұ�������
				ZYH_SB=0;         //����������
				YYH_SB=0;         //����������
				break;
			}
			memset(USART2_RX_BUF,0,len);  //�������
			USART2_RX_LEN=0;              //�����־λ 
		}
		if(UART4_RX_LEN&0x8000)
		{
			len=UART4_RX_LEN&0x3fff;				
			UART4_RX_BUF[len]=0;
			if(strstr((const char *)UART4_RX_BUF,(const char *)"FWZBB"))
			{
				Fun_FW_ZB();     		  //֧����λ
			}
			if(strstr((const char *)UART4_RX_BUF,(const char *)"FWQT")) 
			{			
				Fun_FW_QT();   		      //���ȸ�λ
			}
			if(strstr((const char *)UART4_RX_BUF,(const char *)"FWZBQ"))
			{			
				Fun_ZBQ(1);	              //��������λ
			}				
			if(strstr((const char *)UART4_RX_BUF,(const char *)"FWZF")) 
			{			
				Fun_FW_ZF();              //����λ					
			}
			if(strstr((const char *)UART4_RX_BUF,(const char *)"FWYF"))
			{			
				Fun_FW_YF();              //�ҷ���λ	
			}									
			if(strstr((const char *)UART4_RX_BUF,(const char *)"FWYL")) 
			{			
				Fun_FW_YL();             //�Ͳ�����һ������λ
			}			
			if(strstr((const char *)UART4_RX_BUF,(const char *)"FWALL")) 
			{			
				Fun_FW_ALL();            //���й���һ��λ
			}					
			if(strstr((const char *)UART4_RX_BUF,(const char *)"WC"))   //�������ų�������ԭ����
			{			
				u2_printf("FaultSolved");				
			
/*********************����־λ������Ϊ0***********************/
				
				//������ر�־λ			
				ZF3_GZ=0;          //����
				ZF4_GZ=0;          
				ZF5_GZ=0;          
				YF3_GZ=0;          //�ҷ���
				YF4_GZ=0;         
				YF5_GZ=0; 
				ZBQ_GZ=0;          //�Զ�����
				YL_GZ=0;           //�Ͳ�����һ����
				ZBH_GZ=0;          //�󱳲�����
				YBH_GZ=0;          //�ұ�������
				ZYH_GZ=0;          //����������
				YYH_GZ=0;          //����������
				
				//���ʧ����־λ	
				ZF_SB=0;          //���� 
				YF_SB=0;          //�ҷ���
				ZBQ_SB=0;         //�Զ�����
				YL_SB=0;          //�Ͳ�����һ����
				ZBH_SB=0;         //�󱳲�����
				YBH_SB=0;         //�ұ�������
				ZYH_SB=0;         //����������
				YYH_SB=0;         //����������
				break;
			}
			memset(UART4_RX_BUF,0,len);  //�������
			UART4_RX_LEN=0;              //�����־λ 
		}
	}
	return 1;    
}


/***********************************************************************
 ������      ��GDCheck(u8 num)
 ��������    ������⺯��
 ����        ��������
 ���        ��1�������ˣ�0���󴥷�                      
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
 ������      ��GDCheckAll()
 ��������    ���������й���ź�
 ����        ����
 ���        ����                     
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

