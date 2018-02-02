#include "sys.h"
#include "usart.h"
#include "washlet.h"
#include "led.h"
#include "key.h"
#include "motor.h"
#include "delay.h"


/***********************************************************************
 ������      ��U2_ZBQ(void)  
 ��������    ������ִ������������
 ����        ��dir: 1(������)��0���ر����㣩
 ���        ����
                           
************************************************************************/
void WashLet_V1(u8 dir,u16 arr)
{
	u16 arr_send;
	u16 j=0;	
	static u16 k=0; 
	static u8 kj;
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			
	USART2_RX_LEN=0;

	ZBQ_Flag=1;
	if((SQT_Flag==0)&&(ZF_Flag==0)&&(YF_Flag==0)&&(SD_Flag==1))
	{
		DIR6=!dir;		//DIR6=0ʱ�򿪣�DIR6=1ʱ�ر�
		u2_printf("��������ʼ����");
		MotorStart(6,1,1400-1,25-1);           //�������
		TIM10_Init(arr,65000-1);                     //�򿪶�ʱ��35000
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);           //����жϱ�־λ
		if(1==dir)
		{
			ZBQ_Flag=1;	
			u2_printf("Cartoon_Washlet_1");
			delay_ms(100);  
		}
		else
		{
			ZBQ_Pic=24;
			u2_printf("Cartoon_Washlet_25");	
			delay_ms(100);
		}
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)))    //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��
		{	
			//�����λ
//				if((0==GD6_End)&&(0==dir))
//				{
//					delay_us(100);
//					if(0==GD6_End)
//					{
//						break_flag=1;
//						u2_printf("GD6End"); 
//						break ;
//					}						
//				}
//				if((0==GD6_Start)&&(1==dir))
//				{
//					delay_us(100);
//					if(0==GD6_Start)
//					{
//						break_flag=1;
//						u2_printf("GD6Start"); 
//						break ; 
//					}
//				}
				if(USART2_RX_LEN&0x8000)
				{
					u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���	
					memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			
					USART2_RX_LEN=0;
				}
			
				//������ϡ��������
//				if(1==Motor6_Alm)     
//				{
//					delay_us(100);
//					if(1==Motor6_Alm)  
//					{
//						ZBQ_Overload=1;
//						u2_printf("WashletAutoOverload");
//						U2_GZCL();
//						break_flag=1;
//						break;		
//					}						
//				}	
				
			//���Ͷ���ָ��
			arr_send=__HAL_TIM_GET_COUNTER(&TIM10_Handler);
			j=arr_send/(arr/24);
			if(0==dir)
			{
				j=24-j;
			}
			k=ZBQ_Pic;
			if(k!=j)
			{
				kj=abs(k,j);				
				if(kj<2)
				{
					k=j;   ZBQ_Pic=k;
					switch (k)
					{						
						case 1:	u2_printf("Cartoon_Washlet_2");
								break;
						case 2:	u2_printf("Cartoon_Washlet_3");
								break;					
						case 3:	u2_printf("Cartoon_Washlet_4");
								break;					
						case 4:	u2_printf("Cartoon_Washlet_5");
								break;	
						case 5:	u2_printf("Cartoon_Washlet_6");
								break;	
						case 6:	u2_printf("Cartoon_Washlet_7");
								break;
						case 7:	u2_printf("Cartoon_Washlet_8");
								break;	
						case 8:	u2_printf("Cartoon_Washlet_9");
								break;	
						case 9:	u2_printf("Cartoon_Washlet_10");
								break;
						case 10:u2_printf("Cartoon_Washlet_11");
								break;	
						case 11:u2_printf("Cartoon_Washlet_12");
								break;	
						case 12:u2_printf("Cartoon_Washlet_13");
								break;		
						case 13:u2_printf("Cartoon_Washlet_14");
								break;	
						case 14:u2_printf("Cartoon_Washlet_15");
								break;	
						case 15:u2_printf("Cartoon_Washlet_16");
								break;	
						case 16:u2_printf("Cartoon_Washlet_17");
								break;		
						case 17:u2_printf("Cartoon_Washlet_18");
								break;	
						case 18:u2_printf("Cartoon_Washlet_19");
								break;
						case 19:u2_printf("Cartoon_Washlet_20");
								break;	
						case 20:u2_printf("Cartoon_Washlet_21");
								break;	
						case 21:u2_printf("Cartoon_Washlet_22");
								break;		
						case 22:u2_printf("Cartoon_Washlet_23");
								break;	
						case 23:u2_printf("Cartoon_Washlet_24");
								break;								
					}
				}
			}							
		}
       MotorStop(6);    //6�ŵ��ֹͣ
			TIM10_Stop();      //�رն�ʱ��	
		//�жϸ�λ
		if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))&&(dir==0))//�ж��Ƿ��ڸ�λ״̬����λ״̬��ǰ�������еĶ�ʱ������
		{		
			ZBQ_Flag=0;	 
			delay_ms(200);
			u2_printf("Cartoon_Washlet_1");		
		}
		 else if((__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF))&&(1==dir))
		 {
			ZBQ_Flag=1;    
			delay_ms(200);
			u2_printf("Cartoon_Washlet_25");
		}
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ
		u2_printf("��������������");
	}
	else
	 {
			LED0=0;          //��������������LED0/LED1��һ��
			LED1=0;
			delay_ms(100);
			LED0=1;
			LED1=1;    	
	 }	
}



