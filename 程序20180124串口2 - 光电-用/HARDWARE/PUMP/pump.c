#include "pump.h"
#include "delay.h"
#include "sys.h"
#include "timer.h"
#include "usart.h"
#include "function.h"
#include "led.h"
#include "motor.h"
#include "initial.h"
#include "string.h"

/*********************************************************************
*������       ��Pump_Init()
*��������     ��ˮ��IO�ڳ�ʼ��
*����         ����
*���         ����

***********************************************************************/
void Pump_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOB_CLK_ENABLE();                         //����GPIOBʱ��
	__HAL_RCC_GPIOC_CLK_ENABLE();                         //����GPIOCʱ��
	__HAL_RCC_GPIOE_CLK_ENABLE();                         //����GPIOEʱ��
	__HAL_RCC_GPIOH_CLK_ENABLE();                         //����GPIOHʱ��
		
    GPIO_Initure.Pin=GPIO_PIN_2|GPIO_PIN_3;               //PH2/3/7
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;                //�������
    GPIO_Initure.Pull=GPIO_PULLDOWN;                      //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;                   //����
    HAL_GPIO_Init(GPIOH,&GPIO_Initure);
	  
	GPIO_Initure.Pin=GPIO_PIN_10|GPIO_PIN_11;             //PB10/11
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;                //�������
    GPIO_Initure.Pull=GPIO_PULLDOWN;                      //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;                   //����
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);		
	
	GPIO_Initure.Pin=GPIO_PIN_3;                          //PE3
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;                //�������
    GPIO_Initure.Pull=GPIO_PULLDOWN;                      //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;                   //����
    HAL_GPIO_Init(GPIOE,&GPIO_Initure);	
	
	GPIO_Initure.Pin=GPIO_PIN_1;             
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;                //�������
    GPIO_Initure.Pull=GPIO_PULLDOWN;                      //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;                   //����
    HAL_GPIO_Init(GPIOC,&GPIO_Initure);		
}

/*********************************************************************
*������       ��Sensor_Init()
*��������     ��������IO�ڳ�ʼ��
*����         ����
*���         ����

***********************************************************************/
void Sensor_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOB_CLK_ENABLE();                       //����GPIOBʱ��
	__HAL_RCC_GPIOC_CLK_ENABLE();                       //����GPIOBʱ��
	__HAL_RCC_GPIOE_CLK_ENABLE();                       //����GPIOEʱ�� 
	__HAL_RCC_GPIOH_CLK_ENABLE();                       //����GPIOHʱ�� 

    GPIO_Initure.Pin=GPIO_PIN_14|GPIO_PIN_15;           //PB14/15
    GPIO_Initure.Mode=GPIO_MODE_INPUT;                  //���븡��
    GPIO_Initure.Pull=GPIO_PULLUP;                      //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;                 //����
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);

	GPIO_Initure.Pin=GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_13;  //PC6/7/8/9/13
    GPIO_Initure.Mode=GPIO_MODE_INPUT;                  //���븡��
    GPIO_Initure.Pull=GPIO_PULLUP;                      //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;                 //����
    HAL_GPIO_Init(GPIOC,&GPIO_Initure);	
	  
	GPIO_Initure.Pin=GPIO_PIN_2|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;  //PE2/4/5/6
    GPIO_Initure.Mode=GPIO_MODE_INPUT;                  //���븡��
    GPIO_Initure.Pull=GPIO_PULLUP;                      //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;                 //����
    HAL_GPIO_Init(GPIOE,&GPIO_Initure);
 	
	GPIO_Initure.Pin=GPIO_PIN_6|GPIO_PIN_9;             //PH679
    GPIO_Initure.Mode=GPIO_MODE_INPUT;                  //���븡��
    GPIO_Initure.Pull=GPIO_PULLUP;                      //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;                 //����
    HAL_GPIO_Init(GPIOH,&GPIO_Initure);
	
	GPIO_Initure.Pin=GPIO_PIN_7;  						//PH7
    GPIO_Initure.Mode=GPIO_MODE_INPUT;                  //���븡��
    GPIO_Initure.Pull=GPIO_PULLUP;                      //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;                 //����
    HAL_GPIO_Init(GPIOH,&GPIO_Initure);	
}

/*********************************************************************
*������       ��CXHG_Init()
*��������     ����ϴ����Ƹ˷���ں�����ڳ�ʼ��
*����         ����
*���         ����

***********************************************************************/
void CXHG_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOB_CLK_ENABLE();           //����GPIOBʱ��
	__HAL_RCC_GPIOC_CLK_ENABLE();           //����GPIOCʱ��

	GPIO_Initure.Pin=GPIO_PIN_13;           //PB13
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //���
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
	
	GPIO_Initure.Pin=GPIO_PIN_1;            //PC1
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //���
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(GPIOC,&GPIO_Initure);		
}

/*********************************************************************
*������       ��Fun_ZBCXHG()
*��������     ����ϴ����Ƹ�������
*����         ��dir(�����źţ�1�������0������)
*���         ����

***********************************************************************/
void Fun_ZBCXHG(u8 dir,u32 n)
{
	CXHG_Init();      //�Ƹ˳�ʼ��	
	u8 len;
	int j,flag=1;                   //flagΪ����ߵͱ�־λ	
	RELAY6=1;                       //�̵����õ磬��������պϣ��������������õ�
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			
	USART2_RX_LEN=0;
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			
	UART4_RX_LEN=0;
	if(1==dir)
	{
		DIR_CXHG=1;                   //�жϳ�ϴ����Ƹ����������
		u2_printf("*%s*M8*Z*/*/**",RX_BUF);
	}
	else
	{
		DIR_CXHG=0;                   //�жϳ�ϴ����Ƹ����������
		u2_printf("*%s*M8*F*/*/**",RX_BUF);
	}
	TIM2_Init(3600-1,25-1);                                     //�򿪶�ʱ��
//	if(((1==dir)&&(CXHG1_Runed<CXHG1_Lim))||((0==dir)&&(CXHG1_Runed>0)))	
//	{	
		for(j=0;j<n;j++)
		{ 	
			while(!(__HAL_TIM_GET_FLAG(&TIM2_Handler,TIM_SR_CC3IF)));   //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��
			flag = !flag;
			__HAL_TIM_CLEAR_FLAG(&TIM2_Handler, TIM_SR_CC3IF);          //�����ʱ���жϱ�־λ					
			PWM_CXHG=flag;                                              //��ϴ��ɵ����������ڸ�/�͵�ƽ
			if(USART2_RX_LEN&0x8000)    //�жϴ���2�Ƿ��յ�ָ���ź�
			{			
				len=USART2_RX_LEN&0x3fff;				
				USART2_RX_BUF[len]=0;
				if(strstr((const char *)USART2_RX_BUF,(const char *)"STOP"))
				{
					break;
				}
				if(strstr((const char *)USART2_RX_BUF,(const char *)"SEND OK"))
				{	}
				else 
				{
					u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���	
					memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			
					USART2_RX_LEN=0;
				}				
			}
			if(UART4_RX_LEN&0x8000) //�жϴ���4�Ƿ��յ�ָ���ź�
			{			
				len=UART4_RX_LEN&0x3fff;				
				UART4_RX_BUF[len]=0;
				if(strstr((const char *)UART4_RX_BUF,(const char *)"STOP"))
				{
					break;
				}
				if(strstr((const char *)UART4_RX_BUF,(const char *)"SEND OK"))
				{	}
				else 
				{
					u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���	
					memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			
					UART4_RX_LEN=0;
				}				
			}
			if(1==dir)   //�����������ж������ۼ�
			{
				CXHG1_Runed++;    //���������
			}
			else
			{
				CXHG1_Runed--;	  //���������	 			
			}
			//���ͳ�ϴ����Ƹ˶���ָ��
			if(CXHG1_Runed==1)	
			{
				u2_printf("CT_CXHG1");				
			}
			else if(CXHG1_Runed==(u16)(CXHG1_Lim/3))	
			{
				u2_printf("CT_CXHG2");				
			}
			else if(CXHG1_Runed==(u16)(2*(CXHG1_Lim/3)))
			{
				u2_printf("CT_CXHG3");
			}			
			else if(((CXHG1_Runed==CXHG1_Lim)&&(1==dir))||((CXHG1_Runed==CXHG1_Lim-1)&&(0==dir)))	
			{
				u2_printf("CT_CXHG4");
			}
//		}
	}	
	PWM_CXHG=0;            //��ϴ��ɵ����Ӧ������������� 
	u2_printf("*%s*M8*T*/*/**",RX_BUF);                             
	TIM2_Stop();                                       //�رն�ʱ��
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);       //�������2������
	UART4_RX_LEN=0;
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);         //�������4������
	UART4_RX_LEN=0;
}	

/*********************************************************************
*������       ��Fun_ZBCX()
*��������     ����ϴ�Ƹ�������
*����         ��dir(�����źţ�1�������0������)
*���         ����

***********************************************************************/
void Fun_ZBCX(u8 dir,u32 n)
{
	CXHG_Init();                    //�Ƹ˳�ʼ��
	static u16 k;                   //����k�Ŷ���
	static u8 kj;
	u8 break_flag;
	u8 len;                         //���յ��ַ�������	
	int j,flag=0;                   //flagΪ����ߵͱ�־λ	
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);    //�������2������			
	USART2_RX_LEN=0;
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);	    //�������4������		
	UART4_RX_LEN=0;	
	
	if(1==dir)
	{
		DIR_CXHG=1;                   //�жϳ�ϴ����Ƹ����������
		u2_printf("*%s*M8*Z*/*/**",RX_BUF);
	}
	else
	{
		DIR_CXHG=0;                   //�жϳ�ϴ����Ƹ����������
		u2_printf("*%s*M8*F*/*/**",RX_BUF);
	}
	TIM2_Init(3600-1,25-1);                                     //�򿪶�ʱ��
//	if(((1==dir)&&(CXHG_Runed<CXHG_Lim))||((0==dir)&&(CXHG_Runed>0)))	
//	{	
		for(j=0;j<n;j++)
		{ 	
			while(!(__HAL_TIM_GET_FLAG(&TIM2_Handler,TIM_SR_CC3IF)));   //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��
			flag = !flag;
			__HAL_TIM_CLEAR_FLAG(&TIM2_Handler, TIM_SR_CC3IF);          //�����ʱ���жϱ�־λ					
			PWM_CXHG=flag;                                              //��ϴ��ɵ����������ڸ�/�͵�ƽ
			if(USART2_RX_LEN&0x8000)   //�жϴ���2�Ƿ��յ�ָ���ź�
			{			
				len=USART2_RX_LEN&0x3fff;				
				USART2_RX_BUF[len]=0;
				 //�����յ�STOP,������ѭ��	
				if(((strstr((const char *)USART2_RX_BUF,(const char *)"STOP"))|| 
					(strstr((const char *)USART2_RX_BUF,(const char *)"TGS"))||
						(strstr((const char *)USART2_RX_BUF,(const char *)"TGX")))&&(1==CX_Flag))
				{
//					memcpy(RX_BUF,USART2_RX_BUF,15);
					memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			
					USART2_RX_LEN=0;
					break;
				}
				if(strstr((const char *)USART2_RX_BUF,(const char *)"SEND OK"))
				{	}
				else 
				{
					u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���	
					memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);         //�������4������
					USART2_RX_LEN=0;
				}				
			}
			if(UART4_RX_LEN&0x8000)    //�жϴ���4�Ƿ��յ�ָ���ź�
			{			
				len=UART4_RX_LEN&0x3fff;				
				UART4_RX_BUF[len]=0;
				 //�����յ�STOP,������ѭ��	
				if(((strstr((const char *)UART4_RX_BUF,(const char *)"STOP"))|| 
					(strstr((const char *)UART4_RX_BUF,(const char *)"TGS"))||
						(strstr((const char *)UART4_RX_BUF,(const char *)"TGX")))&&(1==CX_Flag))
				{
//					memcpy(RX_BUF,UART4_RX_BUF,15);
					memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			
					UART4_RX_LEN=0;
					break;
				}
				if(strstr((const char *)UART4_RX_BUF,(const char *)"SEND OK"))
				{	}
				else 
				{
					u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���	
					memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);         //�������4������
					UART4_RX_LEN=0;
				}				
			}
			//�����������ж������ۼ�
			if(1==dir)    
			{
				CXHG_Runed++;   //���������
			}
			else
			{
				CXHG_Runed--;	//���������				
			}
			//���ͳ�ϴ�Ƹ˶���ָ��						
			if(CXHG_Runed==(u16)(CXHG_Lim/4))	
			{
				u2_printf("CT_CX2");
			}
			else if(CXHG_Runed==(u16)(2*(CXHG_Lim/4)))
			{
				u2_printf("CT_CX3");
			}
			else if(CXHG_Runed==(u16)(3*(CXHG_Lim/4)))
			{
				u2_printf("CT_CX4");
			}			
			else if(((CXHG_Runed==CXHG_Lim)&&(1==dir))||((CXHG_Runed==CXHG_Lim-1)&&(0==dir)))
			{
				u2_printf("CT_CX5");
			}
		}
//	}	
	PWM_CXHG=0;  u2_printf("*%s*M8*T*/*/**",RX_BUF);   //��ϴ��ɵ����Ӧ�������������  
	TIM2_Stop();                                       //�رն�ʱ��	
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);       //�������2������
	USART2_RX_LEN=0;
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);         //�������4������
	UART4_RX_LEN=0;	
}	


/*********************************************************************
*������       ��Fun_ZBHG()
*��������     ������Ƹ�������
*����         ��dir(�����źţ�1�������0������)
*���         ����

***********************************************************************/
void Fun_ZBHG(u8 dir,u32 n)
{
	CXHG_Init();      //�Ƹ˳�ʼ��	
	u8 len;
	int j,flag=1;     //flagΪ����ߵͱ�־λ	
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);  //�������2������			
	USART2_RX_LEN=0;
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);	//�������4������	
	UART4_RX_LEN=0;
	if(1==dir)
	{
		DIR_CXHG=1; //�жϳ�ϴ����Ƹ����������
		u2_printf("*%s*M8*Z*/*/**",RX_BUF);
	}
	else
	{
		DIR_CXHG=0; //�жϳ�ϴ����Ƹ����������
		u2_printf("*%s*M8*F*/*/**",RX_BUF);
	}
	TIM2_Init(3600-1,25-1);           //�򿪶�ʱ��
//	if(((1==dir)&&(CXHG_Runed<CXHG_Lim))||((0==dir)&&(CXHG_Runed>0)))	
//	{	
		for(j=0;j<n;j++)
		{ 	
			while(!(__HAL_TIM_GET_FLAG(&TIM2_Handler,TIM_SR_CC3IF)));   //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��
			flag = !flag;
			__HAL_TIM_CLEAR_FLAG(&TIM2_Handler, TIM_SR_CC3IF);          //�����ʱ���жϱ�־λ					
			PWM_CXHG=flag;                                              //��ϴ��ɵ����������ڸ�/�͵�ƽ
			if(USART2_RX_LEN&0x8000)   //�жϴ���2�Ƿ��յ�ָ���ź�
			{			
				len=USART2_RX_LEN&0x3fff;				
				USART2_RX_BUF[len]=0;			
				//�����յ�STOP,������ѭ��	
				if(((strstr((const char *)USART2_RX_BUF,(const char *)"STOP"))|| 
					(strstr((const char *)USART2_RX_BUF,(const char *)"TGS"))||
							(strstr((const char *)USART2_RX_BUF,(const char *)"TGX")))&&(1==HG_Flag))
				{
//					memcpy(RX_BUF,USART2_RX_BUF,15);
					memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			
					USART2_RX_LEN=0;
					break;
				}
				if(strstr((const char *)USART2_RX_BUF,(const char *)"SEND OK"))
				{	}
				else 
				{
					u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���	
					memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);         //�������2������
					USART2_RX_LEN=0;
				}				
			}
			if(UART4_RX_LEN&0x8000)	 //�жϴ���4�Ƿ��յ�ָ���ź�
			{			
				len=UART4_RX_LEN&0x3fff;				
				UART4_RX_BUF[len]=0;			
				//�����յ�STOP,������ѭ��	
				if(((strstr((const char *)UART4_RX_BUF,(const char *)"STOP"))|| 
					(strstr((const char *)UART4_RX_BUF,(const char *)"TGS"))||
							(strstr((const char *)UART4_RX_BUF,(const char *)"TGX")))&&(1==HG_Flag))
				{
//					memcpy(RX_BUF,UART4_RX_BUF,15);
					memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			
					UART4_RX_LEN=0;
					break;
				}
				if(strstr((const char *)UART4_RX_BUF,(const char *)"SEND OK"))
				{	}
				else 
				{
					u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���	
					memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);         //�������4������
					UART4_RX_LEN=0;
				}				
			}
			//ͨ���������ж������ۼ�
			if(1==dir)
			{
				CXHG_Runed++;   //���������
			}
			else
			{
				CXHG_Runed--;	//���������				
			}
			//���ͺ���Ƹ˶���ָ��
			if(CXHG_Runed==(u16)(CXHG_Lim/4))	
			{
				u2_printf("CT_HG2");				
			}
			else if(CXHG_Runed==(u16)(2*(CXHG_Lim/4)))
			{
				u2_printf("CT_HG3");
			}
			else if(CXHG_Runed==(u16)(3*(CXHG_Lim/4)))
			{
				u2_printf("CT_HG4");
			}			
			else if(((CXHG_Runed==CXHG_Lim)&&(1==dir))||((CXHG_Runed==CXHG_Lim-1)&&(0==dir)))				
			{
				u2_printf("CT_HG5");
			}
		}
//	}	
	PWM_CXHG=0;   u2_printf("*%s*M8*T*/*/**",RX_BUF);     	 //��ϴ��ɵ����Ӧ�������������  
	TIM2_Stop();                                             //�رն�ʱ��
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);             //�������2������
	USART2_RX_LEN=0;
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);               //�������4������
	UART4_RX_LEN=0;
}	




