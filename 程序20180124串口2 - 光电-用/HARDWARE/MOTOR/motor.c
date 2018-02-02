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
*函数名       ：Motor_Init()
*函数功能     ：6台电机方向口初始化
*输入         ：无
*输出         ：无
***********************************************************************/
void Motor_Init(void)
{
	GPIO_InitTypeDef GPIO_Initure;
	__HAL_RCC_GPIOA_CLK_ENABLE();           //开启GPIOA时钟
	__HAL_RCC_GPIOC_CLK_ENABLE();           //开启GPIOC时钟
	__HAL_RCC_GPIOD_CLK_ENABLE();           //开启GPIOD时钟
	__HAL_RCC_GPIOG_CLK_ENABLE();           //开启GPIOG时钟 
	__HAL_RCC_GPIOH_CLK_ENABLE();           //开启GPIOH时钟	
	__HAL_RCC_GPIOI_CLK_ENABLE();           //开启GPIOI时钟
	
    GPIO_Initure.Pin=GPIO_PIN_5|GPIO_PIN_6;            //PA5/6  
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;             //推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;                     //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;                //高速
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
	
	GPIO_Initure.Pin= GPIO_PIN_4|GPIO_PIN_12;           //PC4/12
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;              //推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;                      //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;                 //高速
    HAL_GPIO_Init(GPIOC,&GPIO_Initure);	
	
	GPIO_Initure.Pin=GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_7;  //PD2/3/7
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;              //推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;                      //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;                 //高速
    HAL_GPIO_Init(GPIOD,&GPIO_Initure);		
			
	GPIO_Initure.Pin=GPIO_PIN_13;                       //PH13
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;              //推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;                      //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;                 //高速
    HAL_GPIO_Init(GPIOH,&GPIO_Initure);	
	
//坐便袋扎紧电机继电器，控制电机的通断：常开触点，高电平有效
	
	GPIO_Initure.Pin=GPIO_PIN_12;                       //PH12
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;              //推挽输出
    GPIO_Initure.Pull=GPIO_PULLDOWN;                    //下拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;                 //高速
    HAL_GPIO_Init(GPIOH,&GPIO_Initure);
	
//电动推杆		
	GPIO_Initure.Pin=GPIO_PIN_8|GPIO_PIN_3|GPIO_PIN_7;
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
    HAL_GPIO_Init(GPIOI,&GPIO_Initure);

	GPIO_Initure.Pin=GPIO_PIN_10;           //PG10
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
    HAL_GPIO_Init(GPIOG,&GPIO_Initure);		
	
}

/*********************************************************************
*函数名       ：Hang_Init()
*函数功能     ：吊挂电机方向口、脉冲口初始化
*输入         ：无
*输出         ：无
***********************************************************************/
void Hang_Init(void)
{
	GPIO_InitTypeDef GPIO_Initure;
	__HAL_RCC_GPIOA_CLK_ENABLE();           //开启GPIOA时钟
    __HAL_RCC_GPIOB_CLK_ENABLE();           //开启GPIOB时钟
	__HAL_RCC_GPIOD_CLK_ENABLE();           //开启GPIOD时钟  
    __HAL_RCC_GPIOG_CLK_ENABLE();           //开启GPIOG时钟
	__HAL_RCC_GPIOH_CLK_ENABLE();           //开启GPIOH时钟 

   GPIO_Initure.Pin=GPIO_PIN_12;               //PD13
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;      //推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;              //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;         //高速	
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);

	GPIO_Initure.Pin=GPIO_PIN_6 | GPIO_PIN_7|  GPIO_PIN_8|GPIO_PIN_9;  //PB6/7/8//9
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;      //推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;              //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;         //高速	
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
	
	
  	
	GPIO_Initure.Pin=GPIO_PIN_13;               //PD13
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;      //推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;              //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;         //高速	
    HAL_GPIO_Init(GPIOD,&GPIO_Initure);

	GPIO_Initure.Pin=GPIO_PIN_11;              //PH11
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;     //推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;             //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;        //高速	
    HAL_GPIO_Init(GPIOH,&GPIO_Initure);
	
	GPIO_Initure.Pin=GPIO_PIN_3|GPIO_PIN_6;    //PG3/6
	GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;     //推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;             //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;        //高速
    HAL_GPIO_Init(GPIOG,&GPIO_Initure);
}

/*********************************************************************
*函数名       ：MotorStart()
*函数功能     ：电机启动
*输入         ：MotorID-电机ID，dir-方向，定时器重装载值arr(自动重装载值)，psc(分频值)
*输出         ：无
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
			    DIR1_Down=0 ;   //支背上行
			    DIR1_Up=1 ;  		
		    }
			else
			{
				DIR1_Down=1 ;   //支背下行
				DIR1_Up=0 ; 	
			}
		    break;
		    case 2:
		    if(dir==1)
	        {
			   DIR2_Down=0 ;   //上曲腿
			   DIR2_Up=1 ;  		
		    }
		    else
		   {
			  DIR2_Down=1 ;   //下曲腿
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
	        TIM8_PWM2(arr,psc);  //3号电机
			break;
		case 4:
			DIR4=dir;
	        TIM5_PWM4(arr,psc);  //4号电机
			break;
		case 5:
			DIR5=dir;
	        TIM8_PWM1(arr,psc);  //5号电机
			break;
		case 6:
			DIR6=dir;			
	        TIM3_PWM2(arr,psc);  //6号电机		
			break;
		case 7:
			DIR7=dir;
	        TIM1_PWM4(arr,psc);  //7号电机		
			break;
		case 8:                  //345号电机
			DIR3=dir;
			DIR4=dir;
			DIR5=dir;
			TIM8_PWM2(arr,psc);     //TIM8通道 2 PWM输出函数 ，3号电机
			TIM5_PWM4(arr,psc);		//TIM5通道 4 PWM输出函数 ，4号电机
			TIM8_PWM1(arr,psc);     //TIM8通道 1 PWM输出函数 ,5号电机
	    }
	}
}

/*********************************************************************
*函数名       ：MotorStop()
*函数功能     ：电机停止
*输入         ：MotorID-电机ID
*输出         ：无
***********************************************************************/ 
void MotorStop(u8 i)
{
	switch(i)
	{
		case 1:
			DIR1_Down=0 ;     //对应脉冲口拉低
			DIR1_Up=0 ; 
		  break;
		case 2:
			DIR2_Down=0 ;     //对应脉冲口拉低
			DIR2_Up=0 ; 
		  break;
		case 3:
			Motor_Init();                      //电机3方向口初始化函数
			TIM8->CCER&=~(1<<4); 
			break;
		case 4:
			Motor_Init();                      //电机4方向口初始化函数
			TIM5->CCER&=~(1<<12); 
			break;
		case 5:
			Motor_Init();                      //电机5方向口初始化函数
			TIM8->CCER&=~(1<<0);     
			break;
		case 6:
			Motor_Init();                      //电机6方向口初始化函数
			TIM3->CCER&=~(1<<4); 
			break;
		case 7:
			Motor_Init();                      //电机7方向口初始化函数
			TIM1->CCER&=~(1<<12); 	
			break;
		case 8:
			Motor_Init();                      //电机345方向口初始化函数
			TIM8->CCER&=~(1<<4); 
			TIM5->CCER&=~(1<<12); 
			TIM8->CCER&=~(1<<0);
			break;
	}
}

/*********************************************************************
*函数名       ：M345DelayStop()
*函数功能     ：3、4、5电机停止
*输入         ：MotorID-电机ID
*输出         ：无
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
*函数名       ：Motor4_BC()
*函数功能     ：4号电机驱动
*输入         ：arr(自动重装载值)，psc(分频值)
*输出         ：无
***********************************************************************/
void Motor4_BC(u8 dir,u16 time_arr,u16 arr,u16 psc)
{
	if(1==dir)
	{
		MotorStart(4,1,1400-1,25-1);//电机启动
	}
	else
	{
		MotorStart(4,0,1400-1,25-1);//电机启动
	}
	TIM10_Init(time_arr,65000);    //打开定时器
	__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //清除定时器中断标志位
	while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)) )//等待定时时间到
	{

	}
	MotorStop(4);//电机停止
	TIM10_Stop();//关闭定时器
	__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //清除定时器中断标志位
}

/*********************************************************************
*函数名       ：Motor_BC()
*函数功能     ：电机驱动
*输入         ：MotorNum:电机号，3,4,5 dir:方向  arr(自动重装载值)，psc(分频值)
*输出         ：无
***********************************************************************/
void Motor_BC(u8 MotorNum,u8 dir,u16 time_arr,u16 arr,u16 psc)
{
	u8 err=0;
	if((MotorNum==3)||(MotorNum==4)||(MotorNum)==5)
	{err=0;}
	else{err=1;}
	if(err==0)
	{
		MotorStart(MotorNum,dir,1400-1,25-1);//电机启动
		TIM10_Init(time_arr,65000);    //打开定时器
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //清除定时器中断标志位
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)) )//等待定时时间到
		{			}
		MotorStop(MotorNum);//电机停止
		TIM10_Stop();//关闭定时器
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); //清除定时器中断标志位
	}
}

/*********************************************************************
*函数名       ：ZBD_Start()
*函数功能     ：坐便器袋子收紧电机驱动
*输入         ：arr(自动重装载值)，psc(分频值)
*输出         ：无
***********************************************************************/
void ZBD_Start(u16 arr,u16 psc)
{
	Motor_Init();           //电机方向口初始化函数
	TIM8_PWM4(arr,psc);     //TIM8通道 4 PWM输出函数 
}
/*********************************************************************
*函数名       ：ZBD_Stop()
*函数功能     ：坐便器袋子收紧电机停止
*输入         ：无
*输出         ：无
***********************************************************************/
void ZBD_Stop(void)
{
	Motor_Init();              //电机方向口初始化函数
	TIM8->CCER&=~(1<<12);      //定时器8通道4
}
/*********************************************************************
*函数名       ：Motor_All_Stop()
*函数功能     ：所有电机停止
*输入         ：无
*输出         ：无
***********************************************************************/
void Motor_All_Stop(void)
{      
	MotorStop(1);               //支背电机停止函数
	MotorStop(2);               //曲腿电机停止函数
	MotorStop(3);               //背部电机停止函数
	MotorStop(4);               //腰部支背电机停止函数
	MotorStop(5);               //侧翻电机停止函数
	MotorStop(6);               //坐便器电机停止函数
	MotorStop(7);               //小桌子电机停止函数
	MotorStop(8);               //左/右翻身电机停止函数	
	ZBD_Stop();                 //坐便袋扎紧电机停止函数		
}

/*********************************************************************
*函数名       ：Fun_Auto_DG2()
*函数功能     ：2号吊挂电机驱动
*输入         ：dir(方向:1正0反)，pulse(脉冲数)
*输出         ：无
***********************************************************************/
void Fun_Auto_DG2(u16 dir,u32 pulse)
{
    Hang_Init();                      //电机方向口初始化函数
	int i,flag=1;                     //flag为脉冲高低标志位
	int j=0,k=0;
	if(1==dir)
	{
		DG_DIR2=1;                    //1号吊挂电机转动方向控制，高电平正转，低电平反转		
		u2_printf("*%s*DG2*Z*/*/**",RX_BUF);
	}
	else
	{
		DG_DIR2=0;                    //1号吊挂电机转动方向控制，高电平正转，低电平反转		
		u2_printf("*%s*DG2*F*/*/**",RX_BUF);
	}	
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);//清除串口2接收缓存			
	USART2_RX_LEN=0;
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);	//清除串口4接收缓存		
	UART4_RX_LEN=0;
	
    TIM10_Init(DG_Freq,25-1);                   //打开定时器3
    for(i=0;i<pulse;i++)
     { 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) );   //等待定时时间到，时间到跳出循环
		flag = !flag ;
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);             // 清除中断标志位			
		DG_PWM2=flag;              //1号吊挂电机脉冲输出口高电平 
		if(ZXB_Flag==1)    //左胳膊
		{
			//通过上下行判断脉冲累加
			if(1==dir)     //上行，脉冲+
			{
				ZXB_Runed++;
			}
			else           //下行，脉冲-
			{
				ZXB_Runed--;
			}
			//发送左胳膊吊挂动画指令
			j=ZGB_Runed/(ZGB_Lim/9);
			j=j+1;			
			if(k!=j)
			{
				k=j;
				u2_printf("CT_ZZ%d",(k+5));				
			}				
		}
		else if( ZXT_Flag==1)    //左腿
		{
			//通过上下行判断脉冲累加
			if(1==dir)     //上行，脉冲+
			{				
				ZXT_Runed++; 
			}
			else           //下行，脉冲-
			{
				ZXT_Runed--;
			}
			//发送左腿吊挂动画指令						
			j=ZT_Runed/(ZT_Lim/9);
			j=j+1;						
			if(k!=j)
			{
				k=j;
				u2_printf("CT_ZT%d",(k+5));						
			}
		}
	}
	DG_PWM2=0;                      //1号吊挂电机对应脉冲输出口拉低
	u2_printf("*%s*DG2*T*/*/**",RX_BUF);
	TIM10_Stop();                     //关闭定时器
}
/*********************************************************************
*函数名       ：Fun_Auto_DG3()
*函数功能     ：3号吊挂电机驱动
*输入         ：dir(方向:1正0反)，n(脉冲数)
*输出         ：无
***********************************************************************/
void Fun_Auto_DG3(u16 dir,u32 pulse)
{
	Hang_Init();         //电机方向口初始化函数
	int i,flag=1;        //flag为脉冲高低标志位
	int j=0,k=0;
	if(1==dir)
	{
		DG_DIR3=0;       //3号吊挂电机转动方向控制，高电平正转，低电平反转   		
		u2_printf("*%s*DG3*Z*/*/**",RX_BUF);
	}
 	else
	{
		DG_DIR3=1;       //3号吊挂电机转动方向控制，高电平正转，低电平反转   		
		u2_printf("*%s*DG3*F*/*/**",RX_BUF);
	}	
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);//清除串口2接收缓存				
	USART2_RX_LEN=0; 
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);	//清除串口4接收缓存			
	UART4_RX_LEN=0; 
	TIM10_Init(DG_Freq,25-1);                       //打开定时器3
    for(i=0;i<pulse;i++)
     { 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) );   //等待定时时间到，时间到跳出循环
		flag = !flag ;
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);             //清除中断标志位
		DG_PWM3=flag;          //3号吊挂电机脉冲输出口高电平
		if(YXB_Flag==1)    //右胳膊
		{
			//通过上下行判断脉冲累加
			if(1==dir)     //上行，脉冲+
			{
				YXB_Runed++;
			}
			else           //下行，脉冲-
			{
				YXB_Runed--;
			}			
			//发送左胳膊吊挂动画指令
			j=YGB_Runed/(YGB_Lim/9);
			j=j+1;
			
			if(k!=j)
			{
				k=j;
				u2_printf("CT_YZ%d",(k+5));								
			}					
		}
		if( YXT_Flag==1)    //右腿
		{
			//通过上下行判断脉冲累加
			if(1==dir)     //上行，脉冲+
			{				
				YXT_Runed++; 
			}
			else           //下行，脉冲-
			{
				YXT_Runed--;
			}
			//发送左腿吊挂动画指令						
			j=YT_Runed/(YT_Lim/9);
			j=j+1;
						
			if(k!=j)
			{
				k=j;
				u2_printf("CT_YTd%",(k+5));						
			}
		}		 
	}
	DG_PWM3=0;              //3号吊挂电机对应脉冲输出口拉低 
	u2_printf("*%s*DG3*T*/*/**",RX_BUF);
	TIM10_Stop();             //关闭定时器
}
/*********************************************************************
*函数名       ：Fun_Auto_DG12()
*函数功能     ：1/2号吊挂电机驱动
*输入         ：dir(方向:1正0反)，pulse(脉冲数)
*输出         ：无
***********************************************************************/
void Fun_Auto_DG12(u16 dir,u32 pulse)
{
	Hang_Init();        //电机方向口初始化函数
	int i,flag=1;       //flag为脉冲高低标志位
	u8 j=0,k=0;
    if(dir==1)
     {
		DG_DIR1=0;    //1号吊挂电机转动方向控制，高电平正转
		DG_DIR2=1;    //2号吊挂电机转动方向控制，高电平正转
		u2_printf("*%s*DG12*ZZ*/*/**",RX_BUF);
	 }
    else
     {
		DG_DIR1=1;   //1号吊挂电机转动方向控制，低电平反转
		DG_DIR2=0;   //2号吊挂电机转动方向控制，高电平正转
		u2_printf("*%s*DG12*FF*/*/**",RX_BUF);
	 }
    memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);//清除串口2接收缓存		
	USART2_RX_LEN=0; 
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);	//清除串口4接收缓存			
	UART4_RX_LEN=0; 
    TIM10_Init(DG_Freq,25-1);    //打开定时器3
    for(i=0;i<pulse;i++)
     { 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF)));    //等待定时时间到，时间到跳出循环
		flag = !flag ;
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);             // 清除中断标志位
		
		DG_PWM1=flag; 
		DG_PWM2=flag;
		if(ZXB_Flag==1)    //左胳膊
		{
			//通过上下行判断脉冲累加
			if(1==dir)     //上行，脉冲+
			{
				ZGB_Runed++;
			}
			else           //下行，脉冲-
			{
				ZGB_Runed--;
			}
			//发送左胳膊吊挂动画指令	
			j=ZGB_Runed/(ZGB_Lim/4);
			j=j+1;
			
			if(k!=j)
			{
				k=j;
				u2_printf("CT_ZZ%d",k);							
			}
		}
		if( ZXT_Flag==1)    //左腿
		{
			//通过上下行判断脉冲累加
			if(1==dir)     //上行，脉冲+
			{				
				ZT_Runed++; 
			}
			else           //下行，脉冲-
			{
				ZT_Runed--;
			}
			//发送左腿吊挂动画指令						
			j=ZT_Runed/(ZT_Lim/4);
			j=j+1;
			
			if(k!=j)
			{
				k=j;
				u2_printf("CT_ZT%d",(k+5));							
			}
		}		
	}
	DG_PWM1=0;           //1号吊挂电机脉冲输出口低电平
	DG_PWM2=0;           //2号吊挂电机脉冲输出口高电平 
	u2_printf("*%s*DG12*TT*/*/**",RX_BUF);
	TIM10_Stop();          //关闭定时器
}

/*********************************************************************
*函数名       ：Fun_Auto_DG23()
*函数功能     ：2/3号吊挂电机驱动
*输入         ：dir(方向:1正0反)，pulse(脉冲数)
*输出         ：无
***********************************************************************/
void Fun_Auto_DG23(u16 dir,u32 pulse)
{
	Hang_Init();        //电机方向口初始化函数
	int i,flag=1;       //flag为脉冲高低标志位
	int j=0,k=0;
	if(dir==1)
     {
		DG_DIR2=1;    //1号吊挂电机转动方向控制，高电平正转
		DG_DIR3=0;    //2号吊挂电机转动方向控制，高电平正转
		u2_printf("*%s*DG23*ZZ*/*/**",RX_BUF);
	 }
    else
     {
		DG_DIR2=0;   //1号吊挂电机转动方向控制，低电平反转
		DG_DIR3=1;   //2号吊挂电机转动方向控制，高电平正转
		u2_printf("*%s*DG23*FF*/*/**",RX_BUF);
	 }
    
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);//清除串口2接收缓存			
	USART2_RX_LEN=0;
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);	//清除串口4接收缓存			
	UART4_RX_LEN=0; 	 
	TIM10_Init(DG_Freq,25-1);//打开定时器3
	for(i=0;i<pulse;i++)
     { 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) );   //等待定时时间到，时间到跳出循环
		flag = !flag ;
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);             //清除中断标志位
		DG_PWM2=flag;   //1号吊挂电机脉冲输出口高/低电平
		DG_PWM3=flag;   //2号吊挂电机脉冲输出口高/低电平	
 		if(ZYXB_Flag==1)    //左右胳膊
		{
			//通过上下行判断脉冲累加
			if(1==dir)     //上行，脉冲+
			{
				ZYXB_Runed++;
			}
			else           //下行，脉冲-
			{
				ZYXB_Runed--;
			}
			//发送左YOU胳膊吊挂动画指令
			j=ZYGB_Runed/(ZYGB_Lim/9);
			j=j+1;
			
			if(k!=j)
			{
				k=j;
				u2_printf("CT_ZYZ%d",(k+5));								
			}
		}
		if( ZYXT_Flag==1)    //左右腿
		{
			//通过上下行判断脉冲累加
			if(1==dir)     //上行，脉冲+
			{				
				ZYXT_Runed++; 
			}
			else           //下行，脉冲-
			{
				ZYXT_Runed--;
			}
			//发送左YOU腿吊挂动画指令						
			j=ZYT_Runed/(ZYT_Lim/9);
			j=j+1;						
			if(k!=j)
			{
				k=j;
				u2_printf("CT_ZYT%d",(k+5));						
			}
		}  
	}
	DG_PWM2=0;          //1号吊挂电机脉冲输出口低电平
	DG_PWM3=0;          //3号吊挂电机脉冲输出口高电平
	u2_printf("*%s*DG23*TT*/*/**",RX_BUF);
	TIM10_Stop();         //关闭定时器
}


/*********************************************************************
*函数名       ：Fun_Auto_DG34()
*函数功能     ：3/4号吊挂电机驱动
*输入         ：dir(方向:1正0反)，pulse(脉冲数)
*输出         ：无
***********************************************************************/
void Fun_Auto_DG34(u16 dir,u32 pulse)
{
	Hang_Init();         //电机方向口初始化函数
	int i,flag=1;        //flag为脉冲高低标志位
	u8 j=0,k=0;	
	if(dir==1)
     {
		DG_DIR3=0;    //3号吊挂电机转动方向控制，高电平正转
		DG_DIR4=1;    //4号吊挂电机转动方向控制，高电平正转
		u2_printf("*%s*DG34*ZZ*/*/**",RX_BUF);
	 }
    else
     {
		DG_DIR3=1;   //3号吊挂电机转动方向控制，低电平反转
		DG_DIR4=0;   //4号吊挂电机转动方向控制，高电平正转
		u2_printf("*%s*DG34*FF*/*/**",RX_BUF);
	 }
   
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);//清除串口2接收缓存		
	USART2_RX_LEN=0;
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);	//清除串口4接收缓存			
	UART4_RX_LEN=0; 
	TIM10_Init(DG_Freq,25-1);//打开定时器3
	for(i=0;i<pulse;i++)
     { 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) );   //等待定时时间到，时间到跳出循环
		flag = !flag ;
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); // 清除中断标志位
			
		DG_PWM3=flag;          //3号吊挂电机脉冲输出口高电平
		DG_PWM4=flag;          //4号吊挂电机脉冲输出口高电平
		if(YXB_Flag==1)        //右胳膊
		{
			//通过上下行判断脉冲累加
			if(1==dir)     //上行，脉冲+
			{
				YGB_Runed++;
			}
			else           //下行，脉冲-
			{
				YGB_Runed--;
			}
			//发送右胳膊吊挂动画指令	
			j=YGB_Runed/(YGB_Lim/4);
			j=j+1;
			
			if(k!=j)
			{
				k=j;
				u2_printf("CT_YZ%d",k);							
			}
		}
		if( YXT_Flag==1)    //右腿
		{
			//通过上下行判断脉冲累加
			if(1==dir)     //上行，脉冲+
			{				
				YT_Runed++; 
			}
			else           //下行，脉冲-
			{
				YT_Runed--;
			}
			//发送右腿吊挂动画指令						
			j=YT_Runed/(YT_Lim/4);
			j=j+1;
			
			if(k!=j)
			{
				k=j;
				u2_printf("CT_YT%d",k);							
			}
		}		
	}
	DG_PWM3=0;           //3号吊挂电机脉冲输出口低电平
	DG_PWM4=0;           //4号吊挂电机脉冲输出口高电平 
	u2_printf("*%s*DG34*TT*/*/**",RX_BUF);
	TIM10_Stop();          //关闭定时器
}

/*********************************************************************
*函数名       ：Fun_Auto_DG1234()
*函数功能     ：1/2/3/4号吊挂电机驱动
*输入         ：dir(方向:1正0反)，pulse(脉冲数)
*输出         ：无
***********************************************************************/
void Fun_Auto_DG1234(u16 dir,u32 pulse)
{
	Hang_Init();         //电机方向口初始化函数
	int i,flag=1;        //flag为脉冲高低标志位
	u8 j=0,k=0;
	if(dir==1)
    {
		DG_DIR1=0;    //1号吊挂电机转动方向控制，高电平正转
		DG_DIR2=1;    //2号吊挂电机转动方向控制，高电平正转
		DG_DIR3=0;    //3号吊挂电机转动方向控制，高电平正转
		DG_DIR4=1;    //4号吊挂电机转动方向控制，高电平正转
		u2_printf("*%s*DG1234*ZZZZ*/*/**",RX_BUF);
	}
    else
    {
		DG_DIR1=1;   //1号吊挂电机转动方向控制，低电平反转
		DG_DIR2=0;   //2号吊挂电机转动方向控制，高电平正转
		DG_DIR3=1;   //3号吊挂电机转动方向控制，高电平正转
		DG_DIR4=0;   //4号吊挂电机转动方向控制，高电平正转
		u2_printf("*%s*DG1234*FFFF*/*/**",RX_BUF);
	}
  
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//清除串口2接收缓存		
	USART2_RX_LEN=0;
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);	//清除串口4接收缓存			
	UART4_RX_LEN=0; 
	TIM10_Init(DG_Freq,25-1);                       //打开定时器3
	for(i=0;i<pulse;i++)
     { 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) );   //等待定时时间到，时间到跳出循环
		flag = !flag ;
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);             //清除中断标志位
		DG_PWM1=flag;   //1号吊挂电机脉冲输出口高/低电平
		DG_PWM2=flag;   //2号吊挂电机脉冲输出口高/低电平
		DG_PWM3=flag;   //3号吊挂电机脉冲输出口高/低电平
		DG_PWM4=flag;   //4号吊挂电机脉冲输出口高/低电平	
		if(ZYXB_Flag==1)    //左右胳膊
		{
			//通过上下行判断脉冲累加
			if(1==dir)     //上行，脉冲+
			{
				ZYGB_Runed++;
			}
			else           //下行，脉冲-
			{
				ZYGB_Runed--;
			}
			//发送左胳膊吊挂动画指令	
			j=ZYGB_Runed/(ZYGB_Lim/4);
			j=j+1;
			
			if(k!=j)
			{
				k=j;
				u2_printf("CT_ZYZ%d",k);							
			}	
			
		}
		if( ZYXT_Flag==1)    //左右腿
		{
			//通过上下行判断脉冲累加
			if(1==dir)     //上行，脉冲+
			{				
				ZYT_Runed++; 
			}
			else           //下行，脉冲-
			{
				ZYT_Runed--;
			}
			//发送左腿吊挂动画指令						
			j=ZYT_Runed/(ZYT_Lim/4);
			j=j+1;
			
			if(k!=j)
			{
				k=j;
				u2_printf("CT_ZYT%d",k);							
			}
		}	  		 
	}
	DG_PWM1=0;           //1号吊挂电机脉冲输出口低电平
	DG_PWM2=0;           //2号吊挂电机脉冲输出口高电平 
	DG_PWM3=0;           //3号吊挂电机脉冲输出口低电平
	DG_PWM4=0;           //4号吊挂电机脉冲输出口高电平
	u2_printf("*%s*DG1234*TTTT*/*/**",RX_BUF);
	TIM10_Stop();          //关闭定时器
}

/*********************************************************************
*函数名       ：Fun_Hand_DG2()
*函数功能     ：2号吊挂电机：左肢小臂
*输入         ：dir:方向口；n：脉冲口
*输出         ：无
***********************************************************************/
void Fun_Hand_DG2(u16 dir,u32 pulse)
{
	u8 len;
	int i,j,flag=1;            //flag为脉冲高低标志位	
	static int k=0;	
    Hang_Init();               //电机方向口初始化函数
	if(1==dir)
	{
		DG_DIR2=1;  		   //1正转，0反转 
		u2_printf("*%s*DG2*Z*/*/**",RX_BUF);
	}
	else
	{
		DG_DIR2=0;  		   //1正转，0反转 
		u2_printf("*%s*DG2*F*/*/**",RX_BUF);
	}
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);//清除串口2接收缓存			
	USART2_RX_LEN=0;
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);	//清除串口4接收缓存			
	UART4_RX_LEN=0; 
	
	TIM10_Init(DG_Freq,25-1);    //打开定时器10
	for(i=0;i<pulse;i++)
    { 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) );   //等待定时时间到，时间到跳出循环
		flag = !flag ;
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);             // 清除中断标志位		
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
			if(strstr((const char *)USART2_RX_BUF,(const char *)"SEND OK"))    //若接收到Stop,则跳出循环	
			{	}
			else
			{
				u2_printf("USART2_RX_BUF=%s",USART2_RX_BUF);
				u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数
				memset(USART2_RX_BUF,0,len);   //清除接收
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
			if(strstr((const char *)UART4_RX_BUF,(const char *)"SEND OK"))    //若接收到Stop,则跳出循环	
			{	}
			else
			{
				u2_printf("UART4_RX_BUF=%s",UART4_RX_BUF);
				u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数
				memset(UART4_RX_BUF,0,len);   //清除接收
				UART4_RX_LEN=0; 
			}			
		}
		//发送左小臂动画指令
		if((1==ZXB_Flag)||(1==ZDXB_Flag))        //左小臂、左大小臂
		{
			//通过上下行判断脉冲累计
			if(1==dir)      //上行，脉冲+
			{
				ZXB_Runed++;
			}
			else           //下行，脉冲-
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
		else if((1==ZXT_Flag)||(1==ZDXT_Flag))   //左小腿、左大小腿
		{
			//通过上下行判断脉冲累计
			if(1==dir)      //上行，脉冲+
			{
				ZXT_Runed++;
			}
			else           //下行，脉冲-
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
	DG_PWM2=0;           //1号吊挂电机脉冲输出口低电平
	u2_printf("*%s*DG2*T*/*/**",RX_BUF);
	TIM10_Stop();          //关闭定时器
}

/*********************************************************************
*函数名       ：Fun_Hand_DG12()
*函数功能     ：1/2号吊挂电机联动：左肢
*输入         ：m:方向口；pulse：脉冲口
*输出         ：无
***********************************************************************/
void Fun_Hand_DG12(u16 dir,u32 pulse)
{
	u8 len;
	int i,j,flag=1;     //flag为脉冲高低标志位
	static int k=0;
    Hang_Init();        //电机方向口初始化函数
	if(1==dir)
	{
		DG_DIR1=0;  	//1正转，2反转
		DG_DIR2=1;
		u2_printf("*%s*DG12*ZZ*/*/**",RX_BUF);
	}
	else
	{
		DG_DIR1=1;  	//1正转，2反转
		DG_DIR2=0;
		u2_printf("*%s*DG12*FF*/*/**",RX_BUF);
	}	   
	
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//清除串口4接收缓存		
	USART2_RX_LEN=0;
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);	//清除串口4接收缓存		
	UART4_RX_LEN=0;
	TIM10_Init(DG_Freq,25-1);    //打开定时器3
	for(i=0;i<pulse;i++)
	{ 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) );   //等待定时时间到，时间到跳出循环
		flag = !flag ;
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);             // 清除中断标志位
		
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
			if(strstr((const char *)USART2_RX_BUF,(const char *)"SEND OK"))    //若接收到Stop,则跳出循环	
			{	}
			else
			{
				u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数
				memset(USART2_RX_BUF,0,len);   //清除接收
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
			if(strstr((const char *)UART4_RX_BUF,(const char *)"SEND OK"))    //若接收到Stop,则跳出循环	
			{	}
			else
			{
				u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数
				memset(UART4_RX_BUF,0,len);   //清除接收
				UART4_RX_LEN=0; 
			}
		}
		//发送左胳膊动画指令
		if(1==ZXB_Flag)        //左小臂
		{
			//通过上下行判断脉冲累计
			if(1==dir)      //上行，脉冲+
			{
				ZGB_Runed++;
			}
			else           //下行，脉冲-
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
		else if((1==ZDB_Flag)||(1==ZDXB_Flag))   //左大臂、左大小臂
		{
			//通过上下行判断脉冲累计
			if(1==dir)      //上行，脉冲+
			{
				ZDB_Runed++;
			}
			else           //下行，脉冲-
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
		//发送左腿动画指令
		else if(1==ZXT_Flag)   //左小腿
		{
			//通过上下行判断脉冲累计
			if(1==dir)      //上行，脉冲+
			{
				ZT_Runed++;
			}
			else           //下行，脉冲-
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
		else if((1==ZDT_Flag)||(1==ZDXT_Flag))   //左大腿、左大小腿
		{
			//通过上下行判断脉冲累计
			if(1==dir)      //上行，脉冲+
			{
				ZDT_Runed++;
			}
			else           //下行，脉冲-
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
	DG_PWM1=0;           //1号吊挂电机脉冲输出口低电平
	DG_PWM2=0;           //2号吊挂电机脉冲输出口高电平
	u2_printf("*%s*DG12*TT*/*/**",RX_BUF);
	TIM10_Stop();          //关闭定时器
}

/*********************************************************************
*函数名       ：Fun_Hand_DG3()
*函数功能     ：3号吊挂电机：右肢小臂
*输入         ：m:方向口；n：脉冲口
*输出         ：无
***********************************************************************/
void Fun_Hand_DG3(u16 dir,u32 pulse)
{
	u8 len;
	int i,j,flag=1;          //flag为脉冲高低标志位	
	static int k=0;		
    Hang_Init();             //电机方向口初始化函数
	if(1==dir)
	{
		DG_DIR3=0;  		 //1正转，2反转 
		u2_printf("*%s*DG3*Z*/*/**",RX_BUF);
	}
	else
	{
		DG_DIR3=1;  		 //1正转，2反转 
		u2_printf("*%s*DG3*F*/*/**",RX_BUF);
	}
	
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);//清除串口2接收缓存		
	USART2_RX_LEN=0;
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);	//清除串口4接收缓存		
	UART4_RX_LEN=0;
	TIM10_Init(DG_Freq,25-1);    //打开定时器10
	for(i=0;i<pulse;i++)
	{ 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) );   //等待定时时间到，时间到跳出循环
		flag = !flag ;
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);             // 清除中断标志位		
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
			if(strstr((const char *)USART2_RX_BUF,(const char *)"SEND OK"))    //若接收到Stop,则跳出循环	
			{	}
			else
			{
				u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数
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
			if(strstr((const char *)UART4_RX_BUF,(const char *)"SEND OK"))    //若接收到Stop,则跳出循环	
			{	}
			else
			{
				u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数
				memset(UART4_RX_BUF,0,len);
				UART4_RX_LEN=0; 
			}
		}
		//发送右小臂动画指令
		if((1==YXB_Flag)||(1==YDXB_Flag))         //右小臂、右大小臂
		{
			//通过上下行判断脉冲累计
			if(1==dir)      //上行，脉冲+
			{
				YXB_Runed++;
			}
			else           //下行，脉冲-
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
		else if((1==YXT_Flag)||(1==YDXT_Flag))    //右小腿、右大小腿
		{
			//通过上下行判断脉冲累计
			if(1==dir)      //上行，脉冲+
			{
				YXT_Runed++;
			}
			else           //下行，脉冲-
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
	DG_PWM3=0;           //3号吊挂电机脉冲输出口低电平
	u2_printf("*%s*DG3*T*/*/**",RX_BUF);
	TIM10_Stop();          //关闭定时器
}


/*********************************************************************
*函数名       ：Fun_Hand_DG34()
*函数功能     ：3/4号吊挂电机联动：右肢
*输入         ：dir:方向口；pulse：脉冲数
*输出         ：无
***********************************************************************/
void Fun_Hand_DG34(u16 dir,u32 pulse)
{
	u8 len;
	int i,j,flag=1;       //flag为脉冲高低标志位
	static int k=0;	
    Hang_Init();          //电机方向口初始化函数
	if(1==dir)
	{
		DG_DIR3=0;  	  //1正转，2反转
		DG_DIR4=1;
		u2_printf("*%s*DG34*ZZ*/*/**",RX_BUF);
	}
	else
	{
		DG_DIR3=1;  	  //1正转，2反转
		DG_DIR4=0;
		u2_printf("*%s*DG34*FF*/*/**",RX_BUF);
	}	 
	
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//清除串口2接收缓存		
	USART2_RX_LEN=0;	
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);		//清除串口4接收缓存	
	UART4_RX_LEN=0;
	TIM10_Init(DG_Freq,25-1);    //打开定时器10
	for(i=0;i<pulse;i++)
	{ 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) );   //等待定时时间到，时间到跳出循环
		flag = !flag ;
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);             // 清除中断标志位		
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
			if(strstr((const char *)USART2_RX_BUF,(const char *)"SEND OK"))    //若接收到Stop,则跳出循环	
			{	}
			else
			{
				u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数
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
			if(strstr((const char *)UART4_RX_BUF,(const char *)"SEND OK"))    //若接收到Stop,则跳出循环	
			{	}
			else
			{
				u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数
				memset(UART4_RX_BUF,0,len);
				UART4_RX_LEN=0; 
			}			
		}
		//发送右胳膊动画指令
		if(1==YXB_Flag)            //右小臂
		{
			//通过上下行判断脉冲累计
			if(1==dir)      //上行，脉冲+
			{
				YGB_Runed++;
			}
			else           //下行，脉冲-
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
		else if(1==YXT_Flag)       //右小腿
		{
			//通过上下行判断脉冲累计
			if(1==dir)      //上行，脉冲+
			{
				YT_Runed++;
			}
			else           //下行，脉冲-
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
		
		else if((1==YDB_Flag)||(1==YDXB_Flag))    //右大臂、右大小臂
		{
			//通过上下行判断脉冲累计
			if(1==dir)      //上行，脉冲+
			{
				YDB_Runed++;
			}
			else           //下行，脉冲-
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
		else if((1==YDT_Flag)||(1==YDXT_Flag))    //右大腿、右大小腿
		{
			//通过上下行判断脉冲累计
			if(1==dir)      //上行，脉冲+
			{
				YDT_Runed++;
			}
			else           //下行，脉冲-
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
	DG_PWM3=0;           //3号吊挂电机脉冲输出口低电平
	DG_PWM4=0;           //4号吊挂电机脉冲输出口高电平
	u2_printf("*%s*DG34*TT*/*/**",RX_BUF);
	TIM10_Stop();          //关闭定时器
}

/*********************************************************************
*函数名       ：Fun_Hand_DG23()
*函数功能     ：2/3号吊挂电机联动：左右肢小臂/小腿
*输入         ：m:方向口；pulse：脉冲口
*输出         ：无
***********************************************************************/
void Fun_Hand_DG23(u16 dir,u32 pulse)
{
	u8 len;
	int i,j,flag=1;       //flag为脉冲高低标志位
	static int k=0;		
    Hang_Init();          //电机方向口初始化函数
	if(1==dir)
	{
		DG_DIR2=1;  	  //1正转，2反转
		DG_DIR3=0;
		u2_printf("*%s*DG23*ZZ*/*/**",RX_BUF);
	}
	else
	{
		DG_DIR2=0;  	  //1正转，2反转
		DG_DIR3=1;
		u2_printf("*%s*DG23*FF*/*/**",RX_BUF);
	}	   
	
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);//清除串口2接收缓存			
	USART2_RX_LEN=0;
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);	//清除串口4接收缓存		
	UART4_RX_LEN=0;
	TIM10_Init(DG_Freq,25-1);    //打开定时器3
	for(i=0;i<pulse;i++)
	{ 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) );   //等待定时时间到，时间到跳出循环
		flag = !flag ;
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);             // 清除中断标志位
		
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
			if(strstr((const char *)USART2_RX_BUF,(const char *)"SEND OK"))    //若接收到Stop,则跳出循环	
			{	}
			else
			{
				u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数
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
			if(strstr((const char *)UART4_RX_BUF,(const char *)"SEND OK"))    //若接收到Stop,则跳出循环	
			{	}
			else
			{
				u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数
				memset(UART4_RX_BUF,0,len);
				UART4_RX_LEN=0; 
			}
		}
		//发送左右胳膊动画指令
		if((1==ZYXB_Flag)||(1==ZYDXB_Flag))          //左右小臂、左右大小臂
		{
			//通过上下行判断脉冲累计
			if(1==dir)      //上行，脉冲+
			{
				ZYXB_Runed++;
			}
			else           //下行，脉冲-
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
		else if((1==ZYXT_Flag)||(1==ZYDXT_Flag))     //左右小腿、左右大小腿
		{
			//通过上下行判断脉冲累计
			if(1==dir)      //上行，脉冲+
			{
				ZYXT_Runed++;
			}
			else           //下行，脉冲-
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
	DG_PWM2=0;           //1号吊挂电机脉冲输出口低电平
	DG_PWM3=0;           //2号吊挂电机脉冲输出口高电平 
	u2_printf("*%s*DG23*TT*/*/**",RX_BUF);
	TIM10_Stop();          //关闭定时器
}

/*********************************************************************
*函数名       ：Fun_Hand_DG1234()
*函数功能     ：1/2/3/4号吊挂电机联动：左右肢
*输入         ：dir:方向口；pulse：脉冲数
*输出         ：无
***********************************************************************/
void Fun_Hand_DG1234(u16 dir,u32 pulse)
{
	u8 len;
	int i,j,flag=1;       //flag为脉冲高低标志位
	static int k=0;	
    Hang_Init();          //电机方向口初始化函数
	if(1==dir)
	{
		DG_DIR1=0;
		DG_DIR2=1;  	  //1正转，2反转
		DG_DIR3=0;
		DG_DIR4=1; 
		u2_printf("*%s*DG1234*ZZZZ*/*/**",RX_BUF);
	}
	else
	{
		DG_DIR1=1;
		DG_DIR2=0;  	  //1正转，2反转
		DG_DIR3=1;
		DG_DIR4=0;
		u2_printf("*%s*DG1234*FFFF*/*/**",RX_BUF);
	}	
	
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			
	USART2_RX_LEN=0;	
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			
	UART4_RX_LEN=0;
	TIM10_Init(DG_Freq,25-1);    //打开定时器10
	for(i=0;i<pulse;i++)
  { 	
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) );   //等待定时时间到，时间到跳出循环
		flag = !flag ;
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);             // 清除中断标志位		
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
			else if(strstr((const char *)USART2_RX_BUF,(const char *)"SEND OK"))    //若接收到Stop,则跳出循环	
			{	}
			else
			{
				u2_printf("NotRun");       //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数
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
			else if(strstr((const char *)UART4_RX_BUF,(const char *)"SEND OK"))    //若接收到Stop,则跳出循环	
			{	}
			else
			{
				u2_printf("NotRun");       //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数
				memset(UART4_RX_BUF,0,len);
				UART4_RX_LEN=0; 
			}
		}
		//发送左右胳膊动画指令
		if(1==ZYXB_Flag)          //左右小臂
		{
			//通过上下行判断脉冲累计
			if(1==dir)      //上行，脉冲+
			{
				ZYGB_Runed++;
			}
			else           //下行，脉冲-
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
		else if(1==ZYXT_Flag)     //左右小腿
		{
			//通过上下行判断脉冲累计
			if(1==dir)      //上行，脉冲+
			{
				ZYT_Runed++;
			}
			else           //下行，脉冲-
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
		else if((1==ZYDB_Flag)||(1==ZYDXB_Flag))  //左右大臂、左右大小臂
		{
			//通过上下行判断脉冲累计
			if(1==dir)      //上行，脉冲+
			{
				ZYDB_Runed++;
			}
			else           //下行，脉冲-
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
		else if((1==ZYDT_Flag)||(1==ZYDXT_Flag))  //左右大腿、左右大小腿
		{
			//通过上下行判断脉冲累计
			if(1==dir)      //上行，脉冲+
			{
				ZYDT_Runed++;
			}
			else           //下行，脉冲-
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
	TIM10_Stop();          //关闭定时器
}

/*********************************************************************
*函数名       ：Fun_ZBTG()
*函数功能     ：坐便器袋子收紧前推杆驱动，
*输入         ：dir(运行方向)，pulse(运行脉冲数)
*输出         ：无
***********************************************************************/
void Fun_ZBTG(u8 dir,u32 pulse)
{	
	Motor_Init();
	int i,flag=1;          //flag为脉冲高低标志位	
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
	
	RELAY6=1;//打开继电器
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);	//清除串口2接收缓存		
	USART2_RX_LEN=0;
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);	//清除串口4接收缓存		
	UART4_RX_LEN=0;
//   TIM10_Init(1800-1,300-1);                       //打开定时器3600/50
	for(i=0;i<pulse;i++)
	{ 	
//		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) );   //等待定时时间到，时间到跳出循环
		delay_ms(2);
		flag = !flag ;
		PWM6_2=flag;          //坐便袋收紧驱动电机脉冲输出口高/低电平
//		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);             // 清除中断标志位		
		//根据上下行判断脉冲累计
		if(1==dir)           //上行，脉冲+
		{
			ZBDTG_Runed++;
		}
		else                 //下行，脉冲-
		{
			ZBDTG_Runed--;
		}
		//发送动画指令
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
	PWM6_2=0;   //坐便袋收紧驱动电机对应脉冲输出口拉低 
	u2_printf("*%s*M9*T*/*/**",RX_BUF); 
//	TIM10_Stop();    //关闭定时器
	RELAY6=0;//关闭继电器
}



