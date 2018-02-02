#include "motor.h"
#include "sys.h"
#include "pwm.h"
#include "delay.h"
#include "usart.h"
#include "function.h"
#include "pump.h"
#include "usart.h"
#include "LED.h"
#include "initial.h"
#include "string.h"

/*********************************************************************
*������       ��Motor_Init()
*��������     ��6̨�������ڳ�ʼ��
*����         ����
*���         ����
***********************************************************************/
void Motor_Init(void)
{
	GPIO_InitTypeDef GPIO_Initure;
	__HAL_RCC_GPIOA_CLK_ENABLE();           //����GPIOAʱ��
	__HAL_RCC_GPIOC_CLK_ENABLE();           //����GPIOCʱ��
	__HAL_RCC_GPIOD_CLK_ENABLE();           //����GPIODʱ��
	__HAL_RCC_GPIOG_CLK_ENABLE();           //����GPIOGʱ�� 
	__HAL_RCC_GPIOH_CLK_ENABLE();           //����GPIOHʱ��	
	__HAL_RCC_GPIOI_CLK_ENABLE();           //����GPIOIʱ��
	
    GPIO_Initure.Pin=GPIO_PIN_5|GPIO_PIN_6;            //PA5/6  
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;             //�������
    GPIO_Initure.Pull=GPIO_PULLUP;                     //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;                //����
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
	
	GPIO_Initure.Pin= GPIO_PIN_4|GPIO_PIN_12;           //PC4/12
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;              //�������
    GPIO_Initure.Pull=GPIO_PULLUP;                      //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;                 //����
    HAL_GPIO_Init(GPIOC,&GPIO_Initure);	
	
	GPIO_Initure.Pin=GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_7;  //PD2/3/7
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;              //�������
    GPIO_Initure.Pull=GPIO_PULLUP;                      //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;                 //����
    HAL_GPIO_Init(GPIOD,&GPIO_Initure);		
			
	GPIO_Initure.Pin=GPIO_PIN_13;                       //PH13
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;              //�������
    GPIO_Initure.Pull=GPIO_PULLUP;                      //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;                 //����
    HAL_GPIO_Init(GPIOH,&GPIO_Initure);	
	
//�������������̵��������Ƶ����ͨ�ϣ��������㣬�ߵ�ƽ��Ч
	
	GPIO_Initure.Pin=GPIO_PIN_12;                       //PH12
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;              //�������
    GPIO_Initure.Pull=GPIO_PULLDOWN;                    //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;                 //����
    HAL_GPIO_Init(GPIOH,&GPIO_Initure);
	
//�綯�Ƹ�		
	GPIO_Initure.Pin=GPIO_PIN_8|GPIO_PIN_3|GPIO_PIN_7;
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //�������
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(GPIOI,&GPIO_Initure);

	GPIO_Initure.Pin=GPIO_PIN_10;           //PG10
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //�������
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(GPIOG,&GPIO_Initure);		
	
}

/*********************************************************************
*������       ��Hang_Init()
*��������     �����ҵ������ڡ�����ڳ�ʼ��
*����         ����
*���         ����
***********************************************************************/
void Hang_Init(void)
{
	GPIO_InitTypeDef GPIO_Initure;
	__HAL_RCC_GPIOA_CLK_ENABLE();           //����GPIOAʱ��
    __HAL_RCC_GPIOB_CLK_ENABLE();           //����GPIOBʱ��
	__HAL_RCC_GPIOD_CLK_ENABLE();           //����GPIODʱ��  
    __HAL_RCC_GPIOG_CLK_ENABLE();           //����GPIOGʱ��
	__HAL_RCC_GPIOH_CLK_ENABLE();           //����GPIOHʱ�� 

   GPIO_Initure.Pin=GPIO_PIN_12;               //PD13
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;      //�������
    GPIO_Initure.Pull=GPIO_PULLUP;              //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;         //����	
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);

	GPIO_Initure.Pin=GPIO_PIN_6 | GPIO_PIN_7|  GPIO_PIN_8|GPIO_PIN_9;  //PB6/7/8//9
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;      //�������
    GPIO_Initure.Pull=GPIO_PULLUP;              //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;         //����	
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
	
	
  	
	GPIO_Initure.Pin=GPIO_PIN_13;               //PD13
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;      //�������
    GPIO_Initure.Pull=GPIO_PULLUP;              //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;         //����	
    HAL_GPIO_Init(GPIOD,&GPIO_Initure);

	GPIO_Initure.Pin=GPIO_PIN_11;              //PH11
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;     //�������
    GPIO_Initure.Pull=GPIO_PULLUP;             //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;        //����	
    HAL_GPIO_Init(GPIOH,&GPIO_Initure);
	
	GPIO_Initure.Pin=GPIO_PIN_3|GPIO_PIN_6;    //PG3/6
	GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;     //�������
    GPIO_Initure.Pull=GPIO_PULLUP;             //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;        //����
    HAL_GPIO_Init(GPIOG,&GPIO_Initure);
}

/*********************************************************************
*������       ��MotorStart()
*��������     ���������
*����         ��MotorID-���ID��dir-���򣬶�ʱ����װ��ֵarr(�Զ���װ��ֵ)��psc(��Ƶֵ)
*���         ����
***********************************************************************/
void MotorStart(u8 i,u8 dir,u16 arr,u16 psc)
{ 
	if(i==1||i==2)
	{
		Motor_Init();
		switch(i)
		{
			case 1:
			if(dir==1)
		    {
			    DIR1_Down=0 ;   //֧������
			    DIR1_Up=1 ;  		
		    }
			else
			{
				DIR1_Down=1 ;   //֧������
				DIR1_Up=0 ; 	
			}
		    break;
		    case 2:
		    if(dir==1)
	        {
			   DIR2_Down=0 ;   //������
			   DIR2_Up=1 ;  		
		    }
		    else
		   {
			  DIR2_Down=1 ;   //������
			  DIR2_Up=0 ; 	
		   }
		   break;
		}
	}
    else
	{  
		
	switch(i)
	{
		case 3:
			DIR3=dir;                  
	        TIM8_PWM2(arr,psc);  //3�ŵ��
			break;
		case 4:
			DIR4=dir;
	        TIM5_PWM4(arr,psc);  //4�ŵ��
			break;
		case 5:
			DIR5=dir;
	        TIM8_PWM1(arr,psc);  //5�ŵ��
			break;
		case 6:
			DIR6=dir;			
	        TIM3_PWM2(arr,psc);  //6�ŵ��		
			break;
		case 7:
			DIR7=dir;
	        TIM1_PWM4(arr,psc);  //7�ŵ��		
			break;
		case 8:                  //345�ŵ��
			DIR3=dir;
			DIR4=dir;
			DIR5=dir;
			TIM8_PWM2(arr,psc);     //TIM8ͨ�� 2 PWM������� ��3�ŵ��
			TIM5_PWM4(arr,psc);		//TIM5ͨ�� 4 PWM������� ��4�ŵ��
			TIM8_PWM1(arr,psc);     //TIM8ͨ�� 1 PWM������� ,5�ŵ��
	    }
	}
}

/*********************************************************************
*������       ��MotorStop()
*��������     �����ֹͣ
*����         ��MotorID-���ID
*���         ����
***********************************************************************/ 
void MotorStop(u8 i)
{
	switch(i)
	{
		case 1:
			DIR1_Down=0 ;     //��Ӧ���������
			DIR1_Up=0 ; 
		  break;
		case 2:
			DIR2_Down=0 ;     //��Ӧ���������
			DIR2_Up=0 ; 
		  break;
		case 3:
			Motor_Init();                      //���3����ڳ�ʼ������
			TIM8->CCER&=~(1<<4); 
			break;
		case 4:
			Motor_Init();                      //���4����ڳ�ʼ������
			TIM5->CCER&=~(1<<12); 
			break;
		case 5:
			Motor_Init();                      //���5����ڳ�ʼ������
			TIM8->CCER&=~(1<<0);     
			break;
		case 6:
			Motor_Init();                      //���6����ڳ�ʼ������
			TIM3->CCER&=~(1<<4); 
			break;
		case 7:
			Motor_Init();                      //���7����ڳ�ʼ������
			TIM1->CCER&=~(1<<12); 	
			break;
		case 8:
			Motor_Init();                      //���345����ڳ�ʼ������
			TIM8->CCER&=~(1<<4); 
			TIM5->CCER&=~(1<<12); 
			TIM8->CCER&=~(1<<0);
			break;
	}
}

/*********************************************************************
*������       ��M345DelayStop()
*��������     ��3��4��5���ֹͣ
*����         ��MotorID-���ID
*���         ����
***********************************************************************/ 
void M345DelayStop(u16 M3delay,u16 M4delay,u16 M5delay)
{
	if((M3delay<=M4delay)&&(M4delay<=M5delay))
	{
		delay_ms(M3delay);MotorStop(3);
		delay_ms(M4delay-M3delay);MotorStop(4);	
		delay_ms(M5delay-M4delay);MotorStop(5);	
	}
	else if((M3delay<=M5delay)&&(M5delay<=M4delay))
	{
		delay_ms(M3delay);MotorStop(3);
		delay_ms(M5delay-M3delay);MotorStop(5);	
		delay_ms(M4delay-M5delay);MotorStop(4);
	}		
	else if((M4delay<=M3delay)&&(M3delay<=M5delay))
	{
		delay_ms(M4delay);MotorStop(4);
		delay_ms(M3delay-M4delay);MotorStop(3);	
		delay_ms(M5delay-M3delay);MotorStop(5);		
	}
	else if((M4delay<=M5delay)&&(M5delay<=M3delay))
	{
		delay_ms(M4delay);MotorStop(4);
		delay_ms(M5delay-M4delay);MotorStop(5);	
		delay_ms(M3delay-M5delay);MotorStop(3);		
	}
	else if((M5delay<=M3delay)&&(M3delay<=M4delay))
	{
		delay_ms(M5delay);MotorStop(5);
		delay_ms(M3delay-M5delay);MotorStop(3);	
		delay_ms(M4delay-M3delay);MotorStop(4);		
	}
	else if((M5delay<=M4delay)&&(M4delay<=M3delay))
	{
		delay_ms(M5delay);MotorStop(5);
		delay_ms(M4delay-M5delay);MotorStop(4);	
		delay_ms(M3delay-M4delay);MotorStop(3);		
	}
}

/*********************************************************************
*������       ��Motor4_BC()
*��������     ��4�ŵ������
*����         ��arr(�Զ���װ��ֵ)��psc(��Ƶֵ)
*���         ����
***********************************************************************/
void Motor4_BC(u8 dir,u16 time_arr,u16 arr,u16 psc)
{
	if(1==dir)
	{
		MotorStart(4,1,1400-1,25-1);//�������
	}
	else
	{
		MotorStart(4,0,1400-1,25-1);//�������
	}
	TIM10_Init(time_arr,65000);    //�򿪶�ʱ��
	__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //�����ʱ���жϱ�־λ
	while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)) )//�ȴ���ʱʱ�䵽
	{

	}
	MotorStop(4);//���ֹͣ
	TIM10_Stop();//�رն�ʱ��
	__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //�����ʱ���жϱ�־λ
}

/*********************************************************************
*������       ��Motor_BC()
*��������     ���������
*����         ��MotorNum:����ţ�3,4,5 dir:����  arr(�Զ���װ��ֵ)��psc(��Ƶֵ)
*���         ����
***********************************************************************/
void Motor_BC(u8 MotorNum,u8 dir,u16 time_arr,u16 arr,u16 psc)
{
	u8 err=0;
	if((MotorNum==3)||(MotorNum==4)||(MotorNum)==5)
	{err=0;}
	else{err=1;}
	if(err==0)
	{
		MotorStart(MotorNum,dir,1400-1,25-1);//�������
		TIM10_Init(time_arr,65000);    //�򿪶�ʱ��
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //�����ʱ���жϱ�־λ
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)) )//�ȴ���ʱʱ�䵽
		{			}
		MotorStop(MotorNum);//���ֹͣ
		TIM10_Stop();//�رն�ʱ��
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //�����ʱ���жϱ�־λ
	}
}

/*********************************************************************
*������       ��ZBD_Start()
*��������     �������������ս��������
*����         ��arr(�Զ���װ��ֵ)��psc(��Ƶֵ)
*���         ����
***********************************************************************/
void ZBD_Start(u16 arr,u16 psc)
{
	Motor_Init();           //�������ڳ�ʼ������
	TIM8_PWM4(arr,psc);     //TIM8ͨ�� 4 PWM������� 
}
/*********************************************************************
*������       ��ZBD_Stop()
*��������     �������������ս����ֹͣ
*����         ����
*���         ����
***********************************************************************/
void ZBD_Stop(void)
{
	Motor_Init();              //�������ڳ�ʼ������
	TIM8->CCER&=~(1<<12);      //��ʱ��8ͨ��4
}
/*********************************************************************
*������       ��Motor_All_Stop()
*��������     �����е��ֹͣ
*����         ����
*���         ����
***********************************************************************/
void Motor_All_Stop(void)
{      
	MotorStop(1);               //֧�����ֹͣ����
	MotorStop(2);               //���ȵ��ֹͣ����
	MotorStop(3);               //�������ֹͣ����
	MotorStop(4);               //����֧�����ֹͣ����
	MotorStop(5);               //�෭���ֹͣ����
	MotorStop(6);               //���������ֹͣ����
	MotorStop(7);               //С���ӵ��ֹͣ����
	MotorStop(8);               //��/�ҷ�����ֹͣ����	
	ZBD_Stop();                 //������������ֹͣ����		
}

/*********************************************************************
*������       ��Fun_Auto_DG2()
*��������     ��2�ŵ��ҵ������
*����         ��dir(����:1��0��)��pulse(������)
*���         ����
***********************************************************************/
void Fun_Auto_DG2(u16 dir,u32 pulse)
{
    Hang_Init();                      //�������ڳ�ʼ������
	int i,flag=1;                     //flagΪ����ߵͱ�־λ
	int j=0,k=0;
	if(1==dir)
	{
		DG_DIR2=1;                    //1�ŵ��ҵ��ת��������ƣ��ߵ�ƽ��ת���͵�ƽ��ת		
		u2_printf("*%s*DG2*Z*/*/**",RX_BUF);
	}
	else
	{
		DG_DIR2=0;                    //1�ŵ��ҵ��ת��������ƣ��ߵ�ƽ��ת���͵�ƽ��ת		
		u2_printf("*%s*DG2*F*/*/**",RX_BUF);
	}	
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);//�������2���ջ���			
	USART2_RX_LEN=0;
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);	//�������4���ջ���		
	UART4_RX_LEN=0;
	
    TIM10_Init(DG_Freq,25-1);                   //�򿪶�ʱ��3
    for(i=0;i<pulse;i++)
     { 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) );   //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��
		flag = !flag ;
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);             // ����жϱ�־λ			
		DG_PWM2=flag;              //1�ŵ��ҵ����������ڸߵ�ƽ 
		if(ZXB_Flag==1)    //��첲
		{
			//ͨ���������ж������ۼ�
			if(1==dir)     //���У�����+
			{
				ZXB_Runed++;
			}
			else           //���У�����-
			{
				ZXB_Runed--;
			}
			//������첲���Ҷ���ָ��
			j=ZGB_Runed/(ZGB_Lim/9);
			j=j+1;			
			if(k!=j)
			{
				k=j;
				u2_printf("CT_ZZ%d",(k+5));				
			}				
		}
		else if( ZXT_Flag==1)    //����
		{
			//ͨ���������ж������ۼ�
			if(1==dir)     //���У�����+
			{				
				ZXT_Runed++; 
			}
			else           //���У�����-
			{
				ZXT_Runed--;
			}
			//�������ȵ��Ҷ���ָ��						
			j=ZT_Runed/(ZT_Lim/9);
			j=j+1;						
			if(k!=j)
			{
				k=j;
				u2_printf("CT_ZT%d",(k+5));						
			}
		}
	}
	DG_PWM2=0;                      //1�ŵ��ҵ����Ӧ�������������
	u2_printf("*%s*DG2*T*/*/**",RX_BUF);
	TIM10_Stop();                     //�رն�ʱ��
}
/*********************************************************************
*������       ��Fun_Auto_DG3()
*��������     ��3�ŵ��ҵ������
*����         ��dir(����:1��0��)��n(������)
*���         ����
***********************************************************************/
void Fun_Auto_DG3(u16 dir,u32 pulse)
{
	Hang_Init();         //�������ڳ�ʼ������
	int i,flag=1;        //flagΪ����ߵͱ�־λ
	int j=0,k=0;
	if(1==dir)
	{
		DG_DIR3=0;       //3�ŵ��ҵ��ת��������ƣ��ߵ�ƽ��ת���͵�ƽ��ת   		
		u2_printf("*%s*DG3*Z*/*/**",RX_BUF);
	}
 	else
	{
		DG_DIR3=1;       //3�ŵ��ҵ��ת��������ƣ��ߵ�ƽ��ת���͵�ƽ��ת   		
		u2_printf("*%s*DG3*F*/*/**",RX_BUF);
	}	
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);//�������2���ջ���				
	USART2_RX_LEN=0; 
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);	//�������4���ջ���			
	UART4_RX_LEN=0; 
	TIM10_Init(DG_Freq,25-1);                       //�򿪶�ʱ��3
    for(i=0;i<pulse;i++)
     { 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) );   //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��
		flag = !flag ;
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);             //����жϱ�־λ
		DG_PWM3=flag;          //3�ŵ��ҵ����������ڸߵ�ƽ
		if(YXB_Flag==1)    //�Ҹ첲
		{
			//ͨ���������ж������ۼ�
			if(1==dir)     //���У�����+
			{
				YXB_Runed++;
			}
			else           //���У�����-
			{
				YXB_Runed--;
			}			
			//������첲���Ҷ���ָ��
			j=YGB_Runed/(YGB_Lim/9);
			j=j+1;
			
			if(k!=j)
			{
				k=j;
				u2_printf("CT_YZ%d",(k+5));								
			}					
		}
		if( YXT_Flag==1)    //����
		{
			//ͨ���������ж������ۼ�
			if(1==dir)     //���У�����+
			{				
				YXT_Runed++; 
			}
			else           //���У�����-
			{
				YXT_Runed--;
			}
			//�������ȵ��Ҷ���ָ��						
			j=YT_Runed/(YT_Lim/9);
			j=j+1;
						
			if(k!=j)
			{
				k=j;
				u2_printf("CT_YTd%",(k+5));						
			}
		}		 
	}
	DG_PWM3=0;              //3�ŵ��ҵ����Ӧ������������� 
	u2_printf("*%s*DG3*T*/*/**",RX_BUF);
	TIM10_Stop();             //�رն�ʱ��
}
/*********************************************************************
*������       ��Fun_Auto_DG12()
*��������     ��1/2�ŵ��ҵ������
*����         ��dir(����:1��0��)��pulse(������)
*���         ����
***********************************************************************/
void Fun_Auto_DG12(u16 dir,u32 pulse)
{
	Hang_Init();        //�������ڳ�ʼ������
	int i,flag=1;       //flagΪ����ߵͱ�־λ
	u8 j=0,k=0;
    if(dir==1)
     {
		DG_DIR1=0;    //1�ŵ��ҵ��ת��������ƣ��ߵ�ƽ��ת
		DG_DIR2=1;    //2�ŵ��ҵ��ת��������ƣ��ߵ�ƽ��ת
		u2_printf("*%s*DG12*ZZ*/*/**",RX_BUF);
	 }
    else
     {
		DG_DIR1=1;   //1�ŵ��ҵ��ת��������ƣ��͵�ƽ��ת
		DG_DIR2=0;   //2�ŵ��ҵ��ת��������ƣ��ߵ�ƽ��ת
		u2_printf("*%s*DG12*FF*/*/**",RX_BUF);
	 }
    memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);//�������2���ջ���		
	USART2_RX_LEN=0; 
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);	//�������4���ջ���			
	UART4_RX_LEN=0; 
    TIM10_Init(DG_Freq,25-1);    //�򿪶�ʱ��3
    for(i=0;i<pulse;i++)
     { 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)));    //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��
		flag = !flag ;
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);             // ����жϱ�־λ
		
		DG_PWM1=flag; 
		DG_PWM2=flag;
		if(ZXB_Flag==1)    //��첲
		{
			//ͨ���������ж������ۼ�
			if(1==dir)     //���У�����+
			{
				ZGB_Runed++;
			}
			else           //���У�����-
			{
				ZGB_Runed--;
			}
			//������첲���Ҷ���ָ��	
			j=ZGB_Runed/(ZGB_Lim/4);
			j=j+1;
			
			if(k!=j)
			{
				k=j;
				u2_printf("CT_ZZ%d",k);							
			}
		}
		if( ZXT_Flag==1)    //����
		{
			//ͨ���������ж������ۼ�
			if(1==dir)     //���У�����+
			{				
				ZT_Runed++; 
			}
			else           //���У�����-
			{
				ZT_Runed--;
			}
			//�������ȵ��Ҷ���ָ��						
			j=ZT_Runed/(ZT_Lim/4);
			j=j+1;
			
			if(k!=j)
			{
				k=j;
				u2_printf("CT_ZT%d",(k+5));							
			}
		}		
	}
	DG_PWM1=0;           //1�ŵ��ҵ����������ڵ͵�ƽ
	DG_PWM2=0;           //2�ŵ��ҵ����������ڸߵ�ƽ 
	u2_printf("*%s*DG12*TT*/*/**",RX_BUF);
	TIM10_Stop();          //�رն�ʱ��
}

/*********************************************************************
*������       ��Fun_Auto_DG23()
*��������     ��2/3�ŵ��ҵ������
*����         ��dir(����:1��0��)��pulse(������)
*���         ����
***********************************************************************/
void Fun_Auto_DG23(u16 dir,u32 pulse)
{
	Hang_Init();        //�������ڳ�ʼ������
	int i,flag=1;       //flagΪ����ߵͱ�־λ
	int j=0,k=0;
	if(dir==1)
     {
		DG_DIR2=1;    //1�ŵ��ҵ��ת��������ƣ��ߵ�ƽ��ת
		DG_DIR3=0;    //2�ŵ��ҵ��ת��������ƣ��ߵ�ƽ��ת
		u2_printf("*%s*DG23*ZZ*/*/**",RX_BUF);
	 }
    else
     {
		DG_DIR2=0;   //1�ŵ��ҵ��ת��������ƣ��͵�ƽ��ת
		DG_DIR3=1;   //2�ŵ��ҵ��ת��������ƣ��ߵ�ƽ��ת
		u2_printf("*%s*DG23*FF*/*/**",RX_BUF);
	 }
    
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);//�������2���ջ���			
	USART2_RX_LEN=0;
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);	//�������4���ջ���			
	UART4_RX_LEN=0; 	 
	TIM10_Init(DG_Freq,25-1);//�򿪶�ʱ��3
	for(i=0;i<pulse;i++)
     { 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) );   //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��
		flag = !flag ;
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);             //����жϱ�־λ
		DG_PWM2=flag;   //1�ŵ��ҵ����������ڸ�/�͵�ƽ
		DG_PWM3=flag;   //2�ŵ��ҵ����������ڸ�/�͵�ƽ	
 		if(ZYXB_Flag==1)    //���Ҹ첲
		{
			//ͨ���������ж������ۼ�
			if(1==dir)     //���У�����+
			{
				ZYXB_Runed++;
			}
			else           //���У�����-
			{
				ZYXB_Runed--;
			}
			//������YOU�첲���Ҷ���ָ��
			j=ZYGB_Runed/(ZYGB_Lim/9);
			j=j+1;
			
			if(k!=j)
			{
				k=j;
				u2_printf("CT_ZYZ%d",(k+5));								
			}
		}
		if( ZYXT_Flag==1)    //������
		{
			//ͨ���������ж������ۼ�
			if(1==dir)     //���У�����+
			{				
				ZYXT_Runed++; 
			}
			else           //���У�����-
			{
				ZYXT_Runed--;
			}
			//������YOU�ȵ��Ҷ���ָ��						
			j=ZYT_Runed/(ZYT_Lim/9);
			j=j+1;						
			if(k!=j)
			{
				k=j;
				u2_printf("CT_ZYT%d",(k+5));						
			}
		}  
	}
	DG_PWM2=0;          //1�ŵ��ҵ����������ڵ͵�ƽ
	DG_PWM3=0;          //3�ŵ��ҵ����������ڸߵ�ƽ
	u2_printf("*%s*DG23*TT*/*/**",RX_BUF);
	TIM10_Stop();         //�رն�ʱ��
}


/*********************************************************************
*������       ��Fun_Auto_DG34()
*��������     ��3/4�ŵ��ҵ������
*����         ��dir(����:1��0��)��pulse(������)
*���         ����
***********************************************************************/
void Fun_Auto_DG34(u16 dir,u32 pulse)
{
	Hang_Init();         //�������ڳ�ʼ������
	int i,flag=1;        //flagΪ����ߵͱ�־λ
	u8 j=0,k=0;	
	if(dir==1)
     {
		DG_DIR3=0;    //3�ŵ��ҵ��ת��������ƣ��ߵ�ƽ��ת
		DG_DIR4=1;    //4�ŵ��ҵ��ת��������ƣ��ߵ�ƽ��ת
		u2_printf("*%s*DG34*ZZ*/*/**",RX_BUF);
	 }
    else
     {
		DG_DIR3=1;   //3�ŵ��ҵ��ת��������ƣ��͵�ƽ��ת
		DG_DIR4=0;   //4�ŵ��ҵ��ת��������ƣ��ߵ�ƽ��ת
		u2_printf("*%s*DG34*FF*/*/**",RX_BUF);
	 }
   
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);//�������2���ջ���		
	USART2_RX_LEN=0;
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);	//�������4���ջ���			
	UART4_RX_LEN=0; 
	TIM10_Init(DG_Freq,25-1);//�򿪶�ʱ��3
	for(i=0;i<pulse;i++)
     { 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) );   //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��
		flag = !flag ;
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // ����жϱ�־λ
			
		DG_PWM3=flag;          //3�ŵ��ҵ����������ڸߵ�ƽ
		DG_PWM4=flag;          //4�ŵ��ҵ����������ڸߵ�ƽ
		if(YXB_Flag==1)        //�Ҹ첲
		{
			//ͨ���������ж������ۼ�
			if(1==dir)     //���У�����+
			{
				YGB_Runed++;
			}
			else           //���У�����-
			{
				YGB_Runed--;
			}
			//�����Ҹ첲���Ҷ���ָ��	
			j=YGB_Runed/(YGB_Lim/4);
			j=j+1;
			
			if(k!=j)
			{
				k=j;
				u2_printf("CT_YZ%d",k);							
			}
		}
		if( YXT_Flag==1)    //����
		{
			//ͨ���������ж������ۼ�
			if(1==dir)     //���У�����+
			{				
				YT_Runed++; 
			}
			else           //���У�����-
			{
				YT_Runed--;
			}
			//�������ȵ��Ҷ���ָ��						
			j=YT_Runed/(YT_Lim/4);
			j=j+1;
			
			if(k!=j)
			{
				k=j;
				u2_printf("CT_YT%d",k);							
			}
		}		
	}
	DG_PWM3=0;           //3�ŵ��ҵ����������ڵ͵�ƽ
	DG_PWM4=0;           //4�ŵ��ҵ����������ڸߵ�ƽ 
	u2_printf("*%s*DG34*TT*/*/**",RX_BUF);
	TIM10_Stop();          //�رն�ʱ��
}

/*********************************************************************
*������       ��Fun_Auto_DG1234()
*��������     ��1/2/3/4�ŵ��ҵ������
*����         ��dir(����:1��0��)��pulse(������)
*���         ����
***********************************************************************/
void Fun_Auto_DG1234(u16 dir,u32 pulse)
{
	Hang_Init();         //�������ڳ�ʼ������
	int i,flag=1;        //flagΪ����ߵͱ�־λ
	u8 j=0,k=0;
	if(dir==1)
    {
		DG_DIR1=0;    //1�ŵ��ҵ��ת��������ƣ��ߵ�ƽ��ת
		DG_DIR2=1;    //2�ŵ��ҵ��ת��������ƣ��ߵ�ƽ��ת
		DG_DIR3=0;    //3�ŵ��ҵ��ת��������ƣ��ߵ�ƽ��ת
		DG_DIR4=1;    //4�ŵ��ҵ��ת��������ƣ��ߵ�ƽ��ת
		u2_printf("*%s*DG1234*ZZZZ*/*/**",RX_BUF);
	}
    else
    {
		DG_DIR1=1;   //1�ŵ��ҵ��ת��������ƣ��͵�ƽ��ת
		DG_DIR2=0;   //2�ŵ��ҵ��ת��������ƣ��ߵ�ƽ��ת
		DG_DIR3=1;   //3�ŵ��ҵ��ת��������ƣ��ߵ�ƽ��ת
		DG_DIR4=0;   //4�ŵ��ҵ��ת��������ƣ��ߵ�ƽ��ת
		u2_printf("*%s*DG1234*FFFF*/*/**",RX_BUF);
	}
  
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//�������2���ջ���		
	USART2_RX_LEN=0;
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);	//�������4���ջ���			
	UART4_RX_LEN=0; 
	TIM10_Init(DG_Freq,25-1);                       //�򿪶�ʱ��3
	for(i=0;i<pulse;i++)
     { 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) );   //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��
		flag = !flag ;
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);             //����жϱ�־λ
		DG_PWM1=flag;   //1�ŵ��ҵ����������ڸ�/�͵�ƽ
		DG_PWM2=flag;   //2�ŵ��ҵ����������ڸ�/�͵�ƽ
		DG_PWM3=flag;   //3�ŵ��ҵ����������ڸ�/�͵�ƽ
		DG_PWM4=flag;   //4�ŵ��ҵ����������ڸ�/�͵�ƽ	
		if(ZYXB_Flag==1)    //���Ҹ첲
		{
			//ͨ���������ж������ۼ�
			if(1==dir)     //���У�����+
			{
				ZYGB_Runed++;
			}
			else           //���У�����-
			{
				ZYGB_Runed--;
			}
			//������첲���Ҷ���ָ��	
			j=ZYGB_Runed/(ZYGB_Lim/4);
			j=j+1;
			
			if(k!=j)
			{
				k=j;
				u2_printf("CT_ZYZ%d",k);							
			}	
			
		}
		if( ZYXT_Flag==1)    //������
		{
			//ͨ���������ж������ۼ�
			if(1==dir)     //���У�����+
			{				
				ZYT_Runed++; 
			}
			else           //���У�����-
			{
				ZYT_Runed--;
			}
			//�������ȵ��Ҷ���ָ��						
			j=ZYT_Runed/(ZYT_Lim/4);
			j=j+1;
			
			if(k!=j)
			{
				k=j;
				u2_printf("CT_ZYT%d",k);							
			}
		}	  		 
	}
	DG_PWM1=0;           //1�ŵ��ҵ����������ڵ͵�ƽ
	DG_PWM2=0;           //2�ŵ��ҵ����������ڸߵ�ƽ 
	DG_PWM3=0;           //3�ŵ��ҵ����������ڵ͵�ƽ
	DG_PWM4=0;           //4�ŵ��ҵ����������ڸߵ�ƽ
	u2_printf("*%s*DG1234*TTTT*/*/**",RX_BUF);
	TIM10_Stop();          //�رն�ʱ��
}

/*********************************************************************
*������       ��Fun_Hand_DG2()
*��������     ��2�ŵ��ҵ������֫С��
*����         ��dir:����ڣ�n�������
*���         ����
***********************************************************************/
void Fun_Hand_DG2(u16 dir,u32 pulse)
{
	u8 len;
	int i,j,flag=1;            //flagΪ����ߵͱ�־λ	
	static int k=0;	
    Hang_Init();               //�������ڳ�ʼ������
	if(1==dir)
	{
		DG_DIR2=1;  		   //1��ת��0��ת 
		u2_printf("*%s*DG2*Z*/*/**",RX_BUF);
	}
	else
	{
		DG_DIR2=0;  		   //1��ת��0��ת 
		u2_printf("*%s*DG2*F*/*/**",RX_BUF);
	}
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);//�������2���ջ���			
	USART2_RX_LEN=0;
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);	//�������4���ջ���			
	UART4_RX_LEN=0; 
	
	TIM10_Init(DG_Freq,25-1);    //�򿪶�ʱ��10
	for(i=0;i<pulse;i++)
    { 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) );   //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��
		flag = !flag ;
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);             // ����жϱ�־λ		
		DG_PWM2=flag; 	  
		if(USART2_RX_LEN&0x8000)
		{
			len=USART2_RX_LEN&0x3fff;				
			USART2_RX_BUF[len]=0;
			
			if((strstr((const char *)USART2_RX_BUF,(const char *)"BZSXS"))||    
			   (strstr((const char *)USART2_RX_BUF,(const char *)"BZSXX"))||
			   (strstr((const char *)USART2_RX_BUF,(const char *)"BZSBS"))||
			   (strstr((const char *)USART2_RX_BUF,(const char *)"BZSBX"))||
			   (strstr((const char *)USART2_RX_BUF,(const char *)"TZSXS"))||
			   (strstr((const char *)USART2_RX_BUF,(const char *)"TZSXX"))||
			   (strstr((const char *)USART2_RX_BUF,(const char *)"TZSTS"))||
			   (strstr((const char *)USART2_RX_BUF,(const char *)"TZSTX")))	
			{							
//				memcpy(RX_BUF,USART2_RX_BUF,15);
				u2_printf("break_flag==1");
				break;
			}
			if(strstr((const char *)USART2_RX_BUF,(const char *)"SEND OK"))    //�����յ�Stop,������ѭ��	
			{	}
			else
			{
				u2_printf("USART2_RX_BUF=%s",USART2_RX_BUF);
				u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���
				memset(USART2_RX_BUF,0,len);   //�������
				USART2_RX_LEN=0; 
			}			
		}
		if(UART4_RX_LEN&0x8000)
		{
			len=UART4_RX_LEN&0x3fff;				
			UART4_RX_BUF[len]=0;
			
			if((strstr((const char *)UART4_RX_BUF,(const char *)"BZSXS"))||    
			   (strstr((const char *)UART4_RX_BUF,(const char *)"BZSXX"))||
			   (strstr((const char *)UART4_RX_BUF,(const char *)"BZSBS"))||
			   (strstr((const char *)UART4_RX_BUF,(const char *)"BZSBX"))||
			   (strstr((const char *)UART4_RX_BUF,(const char *)"TZSXS"))||
			   (strstr((const char *)UART4_RX_BUF,(const char *)"TZSXX"))||
			   (strstr((const char *)UART4_RX_BUF,(const char *)"TZSTS"))||
			   (strstr((const char *)UART4_RX_BUF,(const char *)"TZSTX")))	
			{							
//				memcpy(RX_BUF,UART4_RX_BUF,15);
				u2_printf("break_flag==1");
				break;
			}
			if(strstr((const char *)UART4_RX_BUF,(const char *)"SEND OK"))    //�����յ�Stop,������ѭ��	
			{	}
			else
			{
				u2_printf("UART4_RX_BUF=%s",UART4_RX_BUF);
				u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���
				memset(UART4_RX_BUF,0,len);   //�������
				UART4_RX_LEN=0; 
			}			
		}
		//������С�۶���ָ��
		if((1==ZXB_Flag)||(1==ZDXB_Flag))        //��С�ۡ����С��
		{
			//ͨ���������ж������ۼ�
			if(1==dir)      //���У�����+
			{
				ZXB_Runed++;
			}
			else           //���У�����-
			{
				ZXB_Runed--;
			}
			j=ZXB_Runed/(ZXB_Lim/9);
			j=j+1;
			if(k!=j)
			{
				k=j;
				u2_printf("CT_ZZ%d",(k+5));								
			}
		}
		else if((1==ZXT_Flag)||(1==ZDXT_Flag))   //��С�ȡ����С��
		{
			//ͨ���������ж������ۼ�
			if(1==dir)      //���У�����+
			{
				ZXT_Runed++;
			}
			else           //���У�����-
			{
				ZXT_Runed--;
			}
			j=ZXT_Runed/(ZXT_Lim/9);
			j=j+1;
			if(k!=j)
			{
				k=j;
				u2_printf("CT_ZT%d",(k+5));								
			}
		}
		if(((ZXB_Runed==0)&&((1==ZXB_Flag)||(1==ZDXB_Flag)) )||
			((ZXT_Runed==0)&&((1==ZXT_Flag)||(1==ZDXT_Flag))))
		{
			k=0;     
		}
	}
	DG_PWM2=0;           //1�ŵ��ҵ����������ڵ͵�ƽ
	u2_printf("*%s*DG2*T*/*/**",RX_BUF);
	TIM10_Stop();          //�رն�ʱ��
}

/*********************************************************************
*������       ��Fun_Hand_DG12()
*��������     ��1/2�ŵ��ҵ����������֫
*����         ��m:����ڣ�pulse�������
*���         ����
***********************************************************************/
void Fun_Hand_DG12(u16 dir,u32 pulse)
{
	u8 len;
	int i,j,flag=1;     //flagΪ����ߵͱ�־λ
	static int k=0;
    Hang_Init();        //�������ڳ�ʼ������
	if(1==dir)
	{
		DG_DIR1=0;  	//1��ת��2��ת
		DG_DIR2=1;
		u2_printf("*%s*DG12*ZZ*/*/**",RX_BUF);
	}
	else
	{
		DG_DIR1=1;  	//1��ת��2��ת
		DG_DIR2=0;
		u2_printf("*%s*DG12*FF*/*/**",RX_BUF);
	}	   
	
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//�������4���ջ���		
	USART2_RX_LEN=0;
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);	//�������4���ջ���		
	UART4_RX_LEN=0;
	TIM10_Init(DG_Freq,25-1);    //�򿪶�ʱ��3
	for(i=0;i<pulse;i++)
	{ 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) );   //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��
		flag = !flag ;
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);             // ����жϱ�־λ
		
		DG_PWM1=flag; 
		DG_PWM2=flag; 
	  
		if(USART2_RX_LEN&0x8000)
		{
			len=USART2_RX_LEN&0x3fff;				
			USART2_RX_BUF[len]=0;
			
			if((strstr((const char *)USART2_RX_BUF,(const char *)"BZSXS"))||
				(strstr((const char *)USART2_RX_BUF,(const char *)"BZSXX"))||
				(strstr((const char *)USART2_RX_BUF,(const char *)"BZSDS"))||
				(strstr((const char *)USART2_RX_BUF,(const char *)"BZSDX"))||
				(strstr((const char *)USART2_RX_BUF,(const char *)"BZSBS"))||
				(strstr((const char *)USART2_RX_BUF,(const char *)"TZSXS"))||
				(strstr((const char *)USART2_RX_BUF,(const char *)"TZSXX"))||	
				(strstr((const char *)USART2_RX_BUF,(const char *)"BZSBX"))||
				(strstr((const char *)USART2_RX_BUF,(const char *)"TZSDS"))||
				(strstr((const char *)USART2_RX_BUF,(const char *)"TZSDX"))||
				(strstr((const char *)USART2_RX_BUF,(const char *)"TZSTS"))||
				(strstr((const char *)USART2_RX_BUF,(const char *)"TZSTX"))) 	
			{			
//				memcpy(RX_BUF,USART2_RX_BUF,15);
				u2_printf("break_flag==1");
				break;
			}
			if(strstr((const char *)USART2_RX_BUF,(const char *)"SEND OK"))    //�����յ�Stop,������ѭ��	
			{	}
			else
			{
				u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���
				memset(USART2_RX_BUF,0,len);   //�������
				USART2_RX_LEN=0; 
			}
		}
		if(UART4_RX_LEN&0x8000)
		{
			len=UART4_RX_LEN&0x3fff;				
			UART4_RX_BUF[len]=0;	
			
			if((strstr((const char *)UART4_RX_BUF,(const char *)"BZSXS"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"BZSXX"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"BZSDS"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"BZSDX"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"BZSBS"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"TZSXS"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"TZSXX"))||	
				(strstr((const char *)UART4_RX_BUF,(const char *)"BZSBX"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"TZSDS"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"TZSDX"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"TZSTS"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"TZSTX"))) 	
			{			
//				memcpy(RX_BUF,UART4_RX_BUF,15);
				u2_printf("break_flag==1");
				break;
			}
			if(strstr((const char *)UART4_RX_BUF,(const char *)"SEND OK"))    //�����յ�Stop,������ѭ��	
			{	}
			else
			{
				u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���
				memset(UART4_RX_BUF,0,len);   //�������
				UART4_RX_LEN=0; 
			}
		}
		//������첲����ָ��
		if(1==ZXB_Flag)        //��С��
		{
			//ͨ���������ж������ۼ�
			if(1==dir)      //���У�����+
			{
				ZGB_Runed++;
			}
			else           //���У�����-
			{
				ZGB_Runed--;
			}
			j=ZGB_Runed/(ZGB_Lim/4);
			j=j+1;
			if(k!=j)
			{
				k=j;
				u2_printf("CT_ZZ%d",k);				
			}
		}
		else if((1==ZDB_Flag)||(1==ZDXB_Flag))   //���ۡ����С��
		{
			//ͨ���������ж������ۼ�
			if(1==dir)      //���У�����+
			{
				ZDB_Runed++;
			}
			else           //���У�����-
			{
				ZDB_Runed--;
			}
			j=ZDB_Runed/(ZDB_Lim/4);
			j=j+1;
			if(k!=j)
			{
				k=j;  
				u2_printf("CT_ZZ%d",k);				
			}
		}		
		//�������ȶ���ָ��
		else if(1==ZXT_Flag)   //��С��
		{
			//ͨ���������ж������ۼ�
			if(1==dir)      //���У�����+
			{
				ZT_Runed++;
			}
			else           //���У�����-
			{
				ZT_Runed--;
			}
			j=ZT_Runed/(ZT_Lim/4);
			j=j+1;
			if(k!=j)
			{
				k=j;
				u2_printf("CT_ZT%d",k);				
			}
		}
		else if((1==ZDT_Flag)||(1==ZDXT_Flag))   //����ȡ����С��
		{
			//ͨ���������ж������ۼ�
			if(1==dir)      //���У�����+
			{
				ZDT_Runed++;
			}
			else           //���У�����-
			{
				ZDT_Runed--;
			}
			j=ZDT_Runed/(ZDT_Lim/4);
			j=j+1;
			if(k!=j)
			{
				k=j;
				u2_printf("CT_ZT%d",k);					
			}
		}
		if(((ZGB_Runed==0)&&(1==ZXB_Flag))||
			((ZDB_Runed==0)&&((1==ZDB_Flag)||(1==ZDXB_Flag)))||
			((ZT_Runed==0)&&(1==ZXT_Flag))||
			((0==ZDT_Runed)&&((1==ZDT_Flag)||(1==ZDXT_Flag))))
		{
			k=0;     
		}
	}
	DG_PWM1=0;           //1�ŵ��ҵ����������ڵ͵�ƽ
	DG_PWM2=0;           //2�ŵ��ҵ����������ڸߵ�ƽ
	u2_printf("*%s*DG12*TT*/*/**",RX_BUF);
	TIM10_Stop();          //�رն�ʱ��
}

/*********************************************************************
*������       ��Fun_Hand_DG3()
*��������     ��3�ŵ��ҵ������֫С��
*����         ��m:����ڣ�n�������
*���         ����
***********************************************************************/
void Fun_Hand_DG3(u16 dir,u32 pulse)
{
	u8 len;
	int i,j,flag=1;          //flagΪ����ߵͱ�־λ	
	static int k=0;		
    Hang_Init();             //�������ڳ�ʼ������
	if(1==dir)
	{
		DG_DIR3=0;  		 //1��ת��2��ת 
		u2_printf("*%s*DG3*Z*/*/**",RX_BUF);
	}
	else
	{
		DG_DIR3=1;  		 //1��ת��2��ת 
		u2_printf("*%s*DG3*F*/*/**",RX_BUF);
	}
	
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);//�������2���ջ���		
	USART2_RX_LEN=0;
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);	//�������4���ջ���		
	UART4_RX_LEN=0;
	TIM10_Init(DG_Freq,25-1);    //�򿪶�ʱ��10
	for(i=0;i<pulse;i++)
	{ 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) );   //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��
		flag = !flag ;
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);             // ����жϱ�־λ		
		DG_PWM3=flag; 	  
		if(USART2_RX_LEN&0x8000)
		{
			len=USART2_RX_LEN&0x3fff;				
			USART2_RX_BUF[len]=0;			
			if((strstr((const char *)USART2_RX_BUF,(const char *)"BYSXS"))||
				(strstr((const char *)USART2_RX_BUF,(const char *)"BYSXX"))||
				(strstr((const char *)USART2_RX_BUF,(const char *)"BYSBS"))||
				(strstr((const char *)USART2_RX_BUF,(const char *)"BYSBX"))||
				(strstr((const char *)USART2_RX_BUF,(const char *)"TYSXS"))||
				(strstr((const char *)USART2_RX_BUF,(const char *)"TYSXX"))||
				(strstr((const char *)USART2_RX_BUF,(const char *)"TYSTS"))||
				(strstr((const char *)USART2_RX_BUF,(const char *)"TYSTX")))	
			{			
//				memcpy(RX_BUF,USART2_RX_BUF,15);
				u2_printf("break_flag==1");
				break;
			}
			if(strstr((const char *)USART2_RX_BUF,(const char *)"SEND OK"))    //�����յ�Stop,������ѭ��	
			{	}
			else
			{
				u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���
				memset(USART2_RX_BUF,0,len);
				USART2_RX_LEN=0; 
			}
		}
		if(UART4_RX_LEN&0x8000)
		{
			len=UART4_RX_LEN&0x3fff;				
			UART4_RX_BUF[len]=0;			
			if((strstr((const char *)UART4_RX_BUF,(const char *)"BYSXS"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"BYSXX"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"BYSBS"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"BYSBX"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"TYSXS"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"TYSXX"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"TYSTS"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"TYSTX")))	
			{			
//				memcpy(RX_BUF,UART4_RX_BUF,15);
				u2_printf("break_flag==1");
				break;
			}
			if(strstr((const char *)UART4_RX_BUF,(const char *)"SEND OK"))    //�����յ�Stop,������ѭ��	
			{	}
			else
			{
				u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���
				memset(UART4_RX_BUF,0,len);
				UART4_RX_LEN=0; 
			}
		}
		//������С�۶���ָ��
		if((1==YXB_Flag)||(1==YDXB_Flag))         //��С�ۡ��Ҵ�С��
		{
			//ͨ���������ж������ۼ�
			if(1==dir)      //���У�����+
			{
				YXB_Runed++;
			}
			else           //���У�����-
			{
				YXB_Runed--;
			}
			j=YXB_Runed/(YXB_Lim/9);
			j=j+1;
			if(k!=j)
			{
				k=j;  
				u2_printf("CT_YZ%d",(k+5));								
			}
		}
		else if((1==YXT_Flag)||(1==YDXT_Flag))    //��С�ȡ��Ҵ�С��
		{
			//ͨ���������ж������ۼ�
			if(1==dir)      //���У�����+
			{
				YXT_Runed++;
			}
			else           //���У�����-
			{
				YXT_Runed--;
			}
			j=YXT_Runed/(YXT_Lim/9);
			j=j+1;
			if(k!=j)
			{
				k=j;
				u2_printf("CT_YT%d",(k+5));								
			}
		}
		if(((YXB_Runed==0)&&((1==YXB_Flag)||(1==YDXB_Flag)))||
			((YXT_Runed==0)&&((1==YXT_Flag)||(1==YDXT_Flag))))
		{
			k=0;     
		}			
  }
	DG_PWM3=0;           //3�ŵ��ҵ����������ڵ͵�ƽ
	u2_printf("*%s*DG3*T*/*/**",RX_BUF);
	TIM10_Stop();          //�رն�ʱ��
}


/*********************************************************************
*������       ��Fun_Hand_DG34()
*��������     ��3/4�ŵ��ҵ����������֫
*����         ��dir:����ڣ�pulse��������
*���         ����
***********************************************************************/
void Fun_Hand_DG34(u16 dir,u32 pulse)
{
	u8 len;
	int i,j,flag=1;       //flagΪ����ߵͱ�־λ
	static int k=0;	
    Hang_Init();          //�������ڳ�ʼ������
	if(1==dir)
	{
		DG_DIR3=0;  	  //1��ת��2��ת
		DG_DIR4=1;
		u2_printf("*%s*DG34*ZZ*/*/**",RX_BUF);
	}
	else
	{
		DG_DIR3=1;  	  //1��ת��2��ת
		DG_DIR4=0;
		u2_printf("*%s*DG34*FF*/*/**",RX_BUF);
	}	 
	
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//�������2���ջ���		
	USART2_RX_LEN=0;	
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//�������4���ջ���	
	UART4_RX_LEN=0;
	TIM10_Init(DG_Freq,25-1);    //�򿪶�ʱ��10
	for(i=0;i<pulse;i++)
	{ 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) );   //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��
		flag = !flag ;
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);             // ����жϱ�־λ		
		DG_PWM3=flag; 
		DG_PWM4=flag; 	  
		if(USART2_RX_LEN&0x8000)
		{
			len=USART2_RX_LEN&0x3fff;				
			USART2_RX_BUF[len]=0;			
			if((strstr((const char *)USART2_RX_BUF,(const char *)"BYSXS"))||
				(strstr((const char *)USART2_RX_BUF,(const char *)"BYSXX"))||
				(strstr((const char *)USART2_RX_BUF,(const char *)"BYSDS"))||
				(strstr((const char *)USART2_RX_BUF,(const char *)"BYSDX"))||
				(strstr((const char *)USART2_RX_BUF,(const char *)"BYSBS"))||
				(strstr((const char *)USART2_RX_BUF,(const char *)"BYSBX"))||
				(strstr((const char *)USART2_RX_BUF,(const char *)"TYSXS"))||	
				(strstr((const char *)USART2_RX_BUF,(const char *)"TYSXX"))||	
				(strstr((const char *)USART2_RX_BUF,(const char *)"TYSDS"))||
				(strstr((const char *)USART2_RX_BUF,(const char *)"TYSDX"))||
				(strstr((const char *)USART2_RX_BUF,(const char *)"TYSTS"))||
				(strstr((const char *)USART2_RX_BUF,(const char *)"TYSTX")))	
			{			
//				memcpy(RX_BUF,USART2_RX_BUF,15);
				u2_printf("break_flag==1");
				break;
			}
			if(strstr((const char *)USART2_RX_BUF,(const char *)"SEND OK"))    //�����յ�Stop,������ѭ��	
			{	}
			else
			{
				u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���
				memset(USART2_RX_BUF,0,len);
				USART2_RX_LEN=0; 
			}			
		}
		if(UART4_RX_LEN&0x8000)
		{
			len=UART4_RX_LEN&0x3fff;				
			UART4_RX_BUF[len]=0;			
			if((strstr((const char *)UART4_RX_BUF,(const char *)"BYSXS"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"BYSXX"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"BYSDS"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"BYSDX"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"BYSBS"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"BYSBX"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"TYSXS"))||	
				(strstr((const char *)UART4_RX_BUF,(const char *)"TYSXX"))||	
				(strstr((const char *)UART4_RX_BUF,(const char *)"TYSDS"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"TYSDX"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"TYSTS"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"TYSTX")))	
			{			
//				memcpy(RX_BUF,UART4_RX_BUF,15);
				u2_printf("break_flag==1");
				break;
			}
			if(strstr((const char *)UART4_RX_BUF,(const char *)"SEND OK"))    //�����յ�Stop,������ѭ��	
			{	}
			else
			{
				u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���
				memset(UART4_RX_BUF,0,len);
				UART4_RX_LEN=0; 
			}			
		}
		//�����Ҹ첲����ָ��
		if(1==YXB_Flag)            //��С��
		{
			//ͨ���������ж������ۼ�
			if(1==dir)      //���У�����+
			{
				YGB_Runed++;
			}
			else           //���У�����-
			{
				YGB_Runed--;
			}
			j=YGB_Runed/(YGB_Lim/4);
			j=j+1;
			if(k!=j)
			{
				k=j; 
				u2_printf("CT_YZ%d",k);				
			}
		}
		else if(1==YXT_Flag)       //��С��
		{
			//ͨ���������ж������ۼ�
			if(1==dir)      //���У�����+
			{
				YT_Runed++;
			}
			else           //���У�����-
			{
				YT_Runed--;
			}
			j=YT_Runed/(YT_Lim/4);
			j=j+1;
			if(k!=j)
			{
				k=j;
				u2_printf("CT_YT%d",k);				
			}
		}
		
		else if((1==YDB_Flag)||(1==YDXB_Flag))    //�Ҵ�ۡ��Ҵ�С��
		{
			//ͨ���������ж������ۼ�
			if(1==dir)      //���У�����+
			{
				YDB_Runed++;
			}
			else           //���У�����-
			{
				YDB_Runed--;
			}
			j=YDB_Runed/(YDB_Lim/4);
			j=j+1;
			if(k!=j)
			{
				k=j;
				u2_printf("CT_YZ%d",k);				
			}
		}
		else if((1==YDT_Flag)||(1==YDXT_Flag))    //�Ҵ��ȡ��Ҵ�С��
		{
			//ͨ���������ж������ۼ�
			if(1==dir)      //���У�����+
			{
				YDT_Runed++;
			}
			else           //���У�����-
			{
				YDT_Runed--;
			}
			j=YDT_Runed/(YDT_Lim/4);
			j=j+1;
			if(k!=j)
			{
				k=j;
				u2_printf("CT_YT%d",k);				
			}
		}
		if(((YGB_Runed==0)&&(1==YXB_Flag))||
			((0==YT_Runed)&&(1==YXT_Flag))||
			((YDB_Runed==0)&&((1==YDB_Flag)||(1==YDXB_Flag)))||
			((0==YDT_Runed)&&((1==YDT_Flag)||(1==YDXT_Flag))))
		{
			k=0;     
		}
   }
	DG_PWM3=0;           //3�ŵ��ҵ����������ڵ͵�ƽ
	DG_PWM4=0;           //4�ŵ��ҵ����������ڸߵ�ƽ
	u2_printf("*%s*DG34*TT*/*/**",RX_BUF);
	TIM10_Stop();          //�رն�ʱ��
}

/*********************************************************************
*������       ��Fun_Hand_DG23()
*��������     ��2/3�ŵ��ҵ������������֫С��/С��
*����         ��m:����ڣ�pulse�������
*���         ����
***********************************************************************/
void Fun_Hand_DG23(u16 dir,u32 pulse)
{
	u8 len;
	int i,j,flag=1;       //flagΪ����ߵͱ�־λ
	static int k=0;		
    Hang_Init();          //�������ڳ�ʼ������
	if(1==dir)
	{
		DG_DIR2=1;  	  //1��ת��2��ת
		DG_DIR3=0;
		u2_printf("*%s*DG23*ZZ*/*/**",RX_BUF);
	}
	else
	{
		DG_DIR2=0;  	  //1��ת��2��ת
		DG_DIR3=1;
		u2_printf("*%s*DG23*FF*/*/**",RX_BUF);
	}	   
	
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);//�������2���ջ���			
	USART2_RX_LEN=0;
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);	//�������4���ջ���		
	UART4_RX_LEN=0;
	TIM10_Init(DG_Freq,25-1);    //�򿪶�ʱ��3
	for(i=0;i<pulse;i++)
	{ 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) );   //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��
		flag = !flag ;
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);             // ����жϱ�־λ
		
		DG_PWM2=flag; 
		DG_PWM3=flag; 
	  
		if(USART2_RX_LEN&0x8000)
		{
			len=USART2_RX_LEN&0x3fff;				
			USART2_RX_BUF[len]=0;			
			if((strstr((const char *)USART2_RX_BUF,(const char *)"BLSXS"))||
				(strstr((const char *)USART2_RX_BUF,(const char *)"BLSXX"))||
				(strstr((const char *)USART2_RX_BUF,(const char *)"BLSBS"))||
				(strstr((const char *)USART2_RX_BUF,(const char *)"BLSBX"))||
				(strstr((const char *)USART2_RX_BUF,(const char *)"TLSXS"))||
				(strstr((const char *)USART2_RX_BUF,(const char *)"TLSXX"))||
				(strstr((const char *)USART2_RX_BUF,(const char *)"TLSTS"))||
				(strstr((const char *)USART2_RX_BUF,(const char *)"TLSTX")))	
			{			
//				memcpy(RX_BUF,USART2_RX_BUF,15);
				u2_printf("break_flag==1");
				break;
			} 
			if(strstr((const char *)USART2_RX_BUF,(const char *)"SEND OK"))    //�����յ�Stop,������ѭ��	
			{	}
			else
			{
				u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���
				memset(USART2_RX_BUF,0,len);
				USART2_RX_LEN=0; 
			}
		}
		if(UART4_RX_LEN&0x8000)
		{
			len=UART4_RX_LEN&0x3fff;				
			UART4_RX_BUF[len]=0;			
			if((strstr((const char *)UART4_RX_BUF,(const char *)"BLSXS"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"BLSXX"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"BLSBS"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"BLSBX"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"TLSXS"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"TLSXX"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"TLSTS"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"TLSTX")))	
			{			
//				memcpy(RX_BUF,UART4_RX_BUF,15);
				u2_printf("break_flag==1");
				break;
			} 
			if(strstr((const char *)UART4_RX_BUF,(const char *)"SEND OK"))    //�����յ�Stop,������ѭ��	
			{	}
			else
			{
				u2_printf("NotRun");    //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���
				memset(UART4_RX_BUF,0,len);
				UART4_RX_LEN=0; 
			}
		}
		//�������Ҹ첲����ָ��
		if((1==ZYXB_Flag)||(1==ZYDXB_Flag))          //����С�ۡ����Ҵ�С��
		{
			//ͨ���������ж������ۼ�
			if(1==dir)      //���У�����+
			{
				ZYXB_Runed++;
			}
			else           //���У�����-
			{
				ZYXB_Runed--;
			}
			j=ZYXB_Runed/(ZYXB_Lim/9);
			j=j+1;
			if(k!=j)
			{
				k=j; 
				u2_printf("CT_ZYZ%d",(k+5));								
			}
		}
		else if((1==ZYXT_Flag)||(1==ZYDXT_Flag))     //����С�ȡ����Ҵ�С��
		{
			//ͨ���������ж������ۼ�
			if(1==dir)      //���У�����+
			{
				ZYXT_Runed++;
			}
			else           //���У�����-
			{
				ZYXT_Runed--;
			}
			j=ZYXT_Runed/(ZYXT_Lim/9);
			j=j+1;
			if(k!=j)
			{
				k=j;
				u2_printf("CT_ZYT%d",(k+5));								
			}
		}
		if(((ZYXB_Runed==0)&&((1==ZYXB_Flag)||(1==ZYDXB_Flag)))||
			((0==ZYXT_Runed)&&((1==ZYXT_Flag)||(1==ZYDXT_Flag))))
		{
			k=0;     
		}
	}
	DG_PWM2=0;           //1�ŵ��ҵ����������ڵ͵�ƽ
	DG_PWM3=0;           //2�ŵ��ҵ����������ڸߵ�ƽ 
	u2_printf("*%s*DG23*TT*/*/**",RX_BUF);
	TIM10_Stop();          //�رն�ʱ��
}

/*********************************************************************
*������       ��Fun_Hand_DG1234()
*��������     ��1/2/3/4�ŵ��ҵ������������֫
*����         ��dir:����ڣ�pulse��������
*���         ����
***********************************************************************/
void Fun_Hand_DG1234(u16 dir,u32 pulse)
{
	u8 len;
	int i,j,flag=1;       //flagΪ����ߵͱ�־λ
	static int k=0;	
    Hang_Init();          //�������ڳ�ʼ������
	if(1==dir)
	{
		DG_DIR1=0;
		DG_DIR2=1;  	  //1��ת��2��ת
		DG_DIR3=0;
		DG_DIR4=1; 
		u2_printf("*%s*DG1234*ZZZZ*/*/**",RX_BUF);
	}
	else
	{
		DG_DIR1=1;
		DG_DIR2=0;  	  //1��ת��2��ת
		DG_DIR3=1;
		DG_DIR4=0;
		u2_printf("*%s*DG1234*FFFF*/*/**",RX_BUF);
	}	
	
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			
	USART2_RX_LEN=0;	
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			
	UART4_RX_LEN=0;
	TIM10_Init(DG_Freq,25-1);    //�򿪶�ʱ��10
	for(i=0;i<pulse;i++)
  { 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) );   //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��
		flag = !flag ;
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);             // ����жϱ�־λ		
		DG_PWM1=flag;
	    DG_PWM2=flag;
	    DG_PWM3=flag;
		DG_PWM4=flag; 	  
		if(USART2_RX_LEN&0x8000)
		{
			len=USART2_RX_LEN&0x3fff;				
			USART2_RX_BUF[len]=0;			
			if((strstr((const char *)USART2_RX_BUF,(const char *)"BLSXS"))||
				(strstr((const char *)USART2_RX_BUF,(const char *)"BLSXX"))||
				(strstr((const char *)USART2_RX_BUF,(const char *)"BLSDS"))||
				(strstr((const char *)USART2_RX_BUF,(const char *)"BLSDX"))||
				(strstr((const char *)USART2_RX_BUF,(const char *)"BLSBS"))||
				(strstr((const char *)USART2_RX_BUF,(const char *)"BLSBX"))||
				(strstr((const char *)USART2_RX_BUF,(const char *)"TLSXS"))||
				(strstr((const char *)USART2_RX_BUF,(const char *)"TLSXX"))||	
				(strstr((const char *)USART2_RX_BUF,(const char *)"TLSDS"))||
				(strstr((const char *)USART2_RX_BUF,(const char *)"TLSDX"))||
				(strstr((const char *)USART2_RX_BUF,(const char *)"TLSTS"))||
				(strstr((const char *)USART2_RX_BUF,(const char *)"TLSTX")))		
			{			
//				memcpy(RX_BUF,USART2_RX_BUF,15);
				u2_printf("break_flag==1");
				break;
			} 
			else if(strstr((const char *)USART2_RX_BUF,(const char *)"SEND OK"))    //�����յ�Stop,������ѭ��	
			{	}
			else
			{
				u2_printf("NotRun");       //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���
				memset(USART2_RX_BUF,0,len);
				USART2_RX_LEN=0; 
			}
		}
		if(UART4_RX_LEN&0x8000)
		{
			len=UART4_RX_LEN&0x3fff;				
			UART4_RX_BUF[len]=0;			
			if((strstr((const char *)UART4_RX_BUF,(const char *)"BLSXS"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"BLSXX"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"BLSDS"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"BLSDX"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"BLSBS"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"BLSBX"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"TLSXS"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"TLSXX"))||	
				(strstr((const char *)UART4_RX_BUF,(const char *)"TLSDS"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"TLSDX"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"TLSTS"))||
				(strstr((const char *)UART4_RX_BUF,(const char *)"TLSTX")))		
			{			
//				memcpy(RX_BUF,UART4_RX_BUF,15);
				u2_printf("break_flag==1");
				break;
			} 
			else if(strstr((const char *)UART4_RX_BUF,(const char *)"SEND OK"))    //�����յ�Stop,������ѭ��	
			{	}
			else
			{
				u2_printf("NotRun");       //�յ�ָ�������ִ�е�ǰ�������޷�ȥִ��ȥ���յ���ָ���
				memset(UART4_RX_BUF,0,len);
				UART4_RX_LEN=0; 
			}
		}
		//�������Ҹ첲����ָ��
		if(1==ZYXB_Flag)          //����С��
		{
			//ͨ���������ж������ۼ�
			if(1==dir)      //���У�����+
			{
				ZYGB_Runed++;
			}
			else           //���У�����-
			{
				ZYGB_Runed--;
			}
			j=ZYGB_Runed/(ZYGB_Lim/4);
			j=j+1;
			if(k!=j)
			{
				k=j; 
				u2_printf("CT_ZYZ%d",k);				
			}
		}
		else if(1==ZYXT_Flag)     //����С��
		{
			//ͨ���������ж������ۼ�
			if(1==dir)      //���У�����+
			{
				ZYT_Runed++;
			}
			else           //���У�����-
			{
				ZYT_Runed--;
			}
			j=ZYT_Runed/(ZYT_Lim/4);
			j=j+1;
			if(k!=j)
			{
				k=j;
				u2_printf("CT_ZYT%d",k);				
			}
		}
		else if((1==ZYDB_Flag)||(1==ZYDXB_Flag))  //���Ҵ�ۡ����Ҵ�С��
		{
			//ͨ���������ж������ۼ�
			if(1==dir)      //���У�����+
			{
				ZYDB_Runed++;
			}
			else           //���У�����-
			{
				ZYDB_Runed--;
			}
			j=ZYDB_Runed/(ZYDB_Lim/4);
			j=j+1;
			if(k!=j)
			{
				k=j;  
				u2_printf("CT_ZYZ%d",k);				
			}
		}
		else if((1==ZYDT_Flag)||(1==ZYDXT_Flag))  //���Ҵ��ȡ����Ҵ�С��
		{
			//ͨ���������ж������ۼ�
			if(1==dir)      //���У�����+
			{
				ZYDT_Runed++;
			}
			else           //���У�����-
			{
				ZYDT_Runed--;
			}
			j=ZYDT_Runed/(ZYDT_Lim/4);
			j=j+1;
			if(k!=j)
			{
				k=j;
				u2_printf("CT_ZYT%d",k);				
			}
		}		
	}
	DG_PWM1=0; 	
	DG_PWM2=0;          
	DG_PWM3=0;  
	DG_PWM4=0; 	
    u2_printf("*%s*DG1234*TTTT*/*/**",RX_BUF);
	TIM10_Stop();          //�رն�ʱ��
}

/*********************************************************************
*������       ��Fun_ZBTG()
*��������     �������������ս�ǰ�Ƹ�������
*����         ��dir(���з���)��pulse(����������)
*���         ����
***********************************************************************/
void Fun_ZBTG(u8 dir,u32 pulse)
{	
	Motor_Init();
	int i,flag=1;          //flagΪ����ߵͱ�־λ	
	if(1==dir)
	{
		DIR6_2=1;
		u2_printf("*%s*M9*Z*/*/**",RX_BUF);
	}
	else
	{
		DIR6_2=0;
		u2_printf("*%s*M9*F*/*/**",RX_BUF);
	}
	
	RELAY6=1;//�򿪼̵���
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//�������2���ջ���		
	USART2_RX_LEN=0;
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);	//�������4���ջ���		
	UART4_RX_LEN=0;
//   TIM10_Init(1800-1,300-1);                       //�򿪶�ʱ��3600/50
	for(i=0;i<pulse;i++)
	{ 	
//		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) );   //�ȴ���ʱʱ�䵽��ʱ�䵽����ѭ��
		delay_ms(2);
		flag = !flag ;
		PWM6_2=flag;          //������ս����������������ڸ�/�͵�ƽ
//		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);             // ����жϱ�־λ		
		//�����������ж������ۼ�
		if(1==dir)           //���У�����+
		{
			ZBDTG_Runed++;
		}
		else                 //���У�����-
		{
			ZBDTG_Runed--;
		}
		//���Ͷ���ָ��
		if(ZBDTG_Runed==1)
		{
			u2_printf("CT_ZBTG1");
		}
		if(ZBDTG_Runed==(u16)(pulse/2))
		{
			u2_printf("CT_ZBTG2");
		}
		if(((ZBDTG_Runed==pulse)&&(1==dir))||((ZBDTG_Runed==pulse-1)&&(0==dir)))
		{
			u2_printf("CT_ZBTG3");
		}	
	}	
	PWM6_2=0;   //������ս����������Ӧ������������� 
	u2_printf("*%s*M9*T*/*/**",RX_BUF); 
//	TIM10_Stop();    //�رն�ʱ��
	RELAY6=0;//�رռ̵���
}



