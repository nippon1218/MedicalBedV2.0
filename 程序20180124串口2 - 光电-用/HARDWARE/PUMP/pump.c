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
*函数名       ：Pump_Init()
*函数功能     ：水箱IO口初始化
*输入         ：无
*输出         ：无

***********************************************************************/
void Pump_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOB_CLK_ENABLE();                         //开启GPIOB时钟
	__HAL_RCC_GPIOC_CLK_ENABLE();                         //开启GPIOC时钟
	__HAL_RCC_GPIOE_CLK_ENABLE();                         //开启GPIOE时钟
	__HAL_RCC_GPIOH_CLK_ENABLE();                         //开启GPIOH时钟
		
    GPIO_Initure.Pin=GPIO_PIN_2|GPIO_PIN_3;               //PH2/3/7
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;                //推挽输出
    GPIO_Initure.Pull=GPIO_PULLDOWN;                      //下拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;                   //高速
    HAL_GPIO_Init(GPIOH,&GPIO_Initure);
	  
	GPIO_Initure.Pin=GPIO_PIN_10|GPIO_PIN_11;             //PB10/11
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;                //推挽输出
    GPIO_Initure.Pull=GPIO_PULLDOWN;                      //下拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;                   //高速
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);		
	
	GPIO_Initure.Pin=GPIO_PIN_3;                          //PE3
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;                //推挽输出
    GPIO_Initure.Pull=GPIO_PULLDOWN;                      //下拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;                   //高速
    HAL_GPIO_Init(GPIOE,&GPIO_Initure);	
	
	GPIO_Initure.Pin=GPIO_PIN_1;             
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;                //推挽输出
    GPIO_Initure.Pull=GPIO_PULLDOWN;                      //下拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;                   //高速
    HAL_GPIO_Init(GPIOC,&GPIO_Initure);		
}

/*********************************************************************
*函数名       ：Sensor_Init()
*函数功能     ：传感器IO口初始化
*输入         ：无
*输出         ：无

***********************************************************************/
void Sensor_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOB_CLK_ENABLE();                       //开启GPIOB时钟
	__HAL_RCC_GPIOC_CLK_ENABLE();                       //开启GPIOB时钟
	__HAL_RCC_GPIOE_CLK_ENABLE();                       //开启GPIOE时钟 
	__HAL_RCC_GPIOH_CLK_ENABLE();                       //开启GPIOH时钟 

    GPIO_Initure.Pin=GPIO_PIN_14|GPIO_PIN_15;           //PB14/15
    GPIO_Initure.Mode=GPIO_MODE_INPUT;                  //输入浮空
    GPIO_Initure.Pull=GPIO_PULLUP;                      //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;                 //高速
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);

	GPIO_Initure.Pin=GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_13;  //PC6/7/8/9/13
    GPIO_Initure.Mode=GPIO_MODE_INPUT;                  //输入浮空
    GPIO_Initure.Pull=GPIO_PULLUP;                      //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;                 //高速
    HAL_GPIO_Init(GPIOC,&GPIO_Initure);	
	  
	GPIO_Initure.Pin=GPIO_PIN_2|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;  //PE2/4/5/6
    GPIO_Initure.Mode=GPIO_MODE_INPUT;                  //输入浮空
    GPIO_Initure.Pull=GPIO_PULLUP;                      //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;                 //高速
    HAL_GPIO_Init(GPIOE,&GPIO_Initure);
 	
	GPIO_Initure.Pin=GPIO_PIN_6|GPIO_PIN_9;             //PH679
    GPIO_Initure.Mode=GPIO_MODE_INPUT;                  //输入浮空
    GPIO_Initure.Pull=GPIO_PULLUP;                      //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;                 //高速
    HAL_GPIO_Init(GPIOH,&GPIO_Initure);
	
	GPIO_Initure.Pin=GPIO_PIN_7;  						//PH7
    GPIO_Initure.Mode=GPIO_MODE_INPUT;                  //输入浮空
    GPIO_Initure.Pull=GPIO_PULLUP;                      //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;                 //高速
    HAL_GPIO_Init(GPIOH,&GPIO_Initure);	
}

/*********************************************************************
*函数名       ：CXHG_Init()
*函数功能     ：冲洗烘干推杆方向口和脉冲口初始化
*输入         ：无
*输出         ：无

***********************************************************************/
void CXHG_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOB_CLK_ENABLE();           //开启GPIOB时钟
	__HAL_RCC_GPIOC_CLK_ENABLE();           //开启GPIOC时钟

	GPIO_Initure.Pin=GPIO_PIN_13;           //PB13
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //输出
    GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
	
	GPIO_Initure.Pin=GPIO_PIN_1;            //PC1
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //输出
    GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
    HAL_GPIO_Init(GPIOC,&GPIO_Initure);		
}

/*********************************************************************
*函数名       ：Fun_ZBCXHG()
*函数功能     ：冲洗烘干推杆驱动，
*输入         ：dir(方向信号：1：伸出；0：缩回)
*输出         ：无

***********************************************************************/
void Fun_ZBCXHG(u8 dir,u32 n)
{
	CXHG_Init();      //推杆初始化	
	u8 len;
	int j,flag=1;                   //flag为脉冲高低标志位	
	RELAY6=1;                       //继电器得电，常开触点闭合，坐便袋扎紧电机得电
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			
	USART2_RX_LEN=0;
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			
	UART4_RX_LEN=0;
	if(1==dir)
	{
		DIR_CXHG=1;                   //判断冲洗烘干推杆伸出或缩回
		u2_printf("*%s*M8*Z*/*/**",RX_BUF);
	}
	else
	{
		DIR_CXHG=0;                   //判断冲洗烘干推杆伸出或缩回
		u2_printf("*%s*M8*F*/*/**",RX_BUF);
	}
	TIM2_Init(3600-1,25-1);                                     //打开定时器
//	if(((1==dir)&&(CXHG1_Runed<CXHG1_Lim))||((0==dir)&&(CXHG1_Runed>0)))	
//	{	
		for(j=0;j<n;j++)
		{ 	
			while(!(__HAL_TIM_GET_FLAG(&TIM2_Handler,TIM_SR_CC3IF)));   //等待定时时间到，时间到跳出循环
			flag = !flag;
			__HAL_TIM_CLEAR_FLAG(&TIM2_Handler, TIM_SR_CC3IF);          //清除定时器中断标志位					
			PWM_CXHG=flag;                                              //冲洗烘干电机脉冲输出口高/低电平
			if(USART2_RX_LEN&0x8000)    //判断串口2是否收到指令信号
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
					u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数	
					memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			
					USART2_RX_LEN=0;
				}				
			}
			if(UART4_RX_LEN&0x8000) //判断串口4是否收到指令信号
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
					u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数	
					memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);			
					UART4_RX_LEN=0;
				}				
			}
			if(1==dir)   //根据上下行判断脉冲累计
			{
				CXHG1_Runed++;    //上行脉冲加
			}
			else
			{
				CXHG1_Runed--;	  //下行脉冲减	 			
			}
			//发送冲洗烘干推杆动画指令
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
	PWM_CXHG=0;            //冲洗烘干电机对应脉冲输出口拉低 
	u2_printf("*%s*M8*T*/*/**",RX_BUF);                             
	TIM2_Stop();                                       //关闭定时器
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);       //清除串口2缓冲区
	UART4_RX_LEN=0;
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);         //清除串口4缓冲区
	UART4_RX_LEN=0;
}	

/*********************************************************************
*函数名       ：Fun_ZBCX()
*函数功能     ：冲洗推杆驱动，
*输入         ：dir(方向信号：1：伸出；0：缩回)
*输出         ：无

***********************************************************************/
void Fun_ZBCX(u8 dir,u32 n)
{
	CXHG_Init();                    //推杆初始化
	static u16 k;                   //传第k张动画
	static u8 kj;
	u8 break_flag;
	u8 len;                         //接收的字符串长度	
	int j,flag=0;                   //flag为脉冲高低标志位	
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);    //清除串口2缓冲区			
	USART2_RX_LEN=0;
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);	    //清除串口4缓冲区		
	UART4_RX_LEN=0;	
	
	if(1==dir)
	{
		DIR_CXHG=1;                   //判断冲洗烘干推杆伸出或缩回
		u2_printf("*%s*M8*Z*/*/**",RX_BUF);
	}
	else
	{
		DIR_CXHG=0;                   //判断冲洗烘干推杆伸出或缩回
		u2_printf("*%s*M8*F*/*/**",RX_BUF);
	}
	TIM2_Init(3600-1,25-1);                                     //打开定时器
//	if(((1==dir)&&(CXHG_Runed<CXHG_Lim))||((0==dir)&&(CXHG_Runed>0)))	
//	{	
		for(j=0;j<n;j++)
		{ 	
			while(!(__HAL_TIM_GET_FLAG(&TIM2_Handler,TIM_SR_CC3IF)));   //等待定时时间到，时间到跳出循环
			flag = !flag;
			__HAL_TIM_CLEAR_FLAG(&TIM2_Handler, TIM_SR_CC3IF);          //清除定时器中断标志位					
			PWM_CXHG=flag;                                              //冲洗烘干电机脉冲输出口高/低电平
			if(USART2_RX_LEN&0x8000)   //判断串口2是否收到指令信号
			{			
				len=USART2_RX_LEN&0x3fff;				
				USART2_RX_BUF[len]=0;
				 //若接收到STOP,则跳出循环	
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
					u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数	
					memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);         //清除串口4缓冲区
					USART2_RX_LEN=0;
				}				
			}
			if(UART4_RX_LEN&0x8000)    //判断串口4是否收到指令信号
			{			
				len=UART4_RX_LEN&0x3fff;				
				UART4_RX_BUF[len]=0;
				 //若接收到STOP,则跳出循环	
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
					u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数	
					memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);         //清除串口4缓冲区
					UART4_RX_LEN=0;
				}				
			}
			//根据上下行判断脉冲累计
			if(1==dir)    
			{
				CXHG_Runed++;   //上行脉冲加
			}
			else
			{
				CXHG_Runed--;	//下行脉冲减				
			}
			//发送冲洗推杆动画指令						
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
	PWM_CXHG=0;  u2_printf("*%s*M8*T*/*/**",RX_BUF);   //冲洗烘干电机对应脉冲输出口拉低  
	TIM2_Stop();                                       //关闭定时器	
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);       //清除串口2缓冲区
	USART2_RX_LEN=0;
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);         //清除串口4缓冲区
	UART4_RX_LEN=0;	
}	


/*********************************************************************
*函数名       ：Fun_ZBHG()
*函数功能     ：烘干推杆驱动，
*输入         ：dir(方向信号：1：伸出；0：缩回)
*输出         ：无

***********************************************************************/
void Fun_ZBHG(u8 dir,u32 n)
{
	CXHG_Init();      //推杆初始化	
	u8 len;
	int j,flag=1;     //flag为脉冲高低标志位	
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);  //清除串口2缓冲区			
	USART2_RX_LEN=0;
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);	//清除串口4缓冲区	
	UART4_RX_LEN=0;
	if(1==dir)
	{
		DIR_CXHG=1; //判断冲洗烘干推杆伸出或缩回
		u2_printf("*%s*M8*Z*/*/**",RX_BUF);
	}
	else
	{
		DIR_CXHG=0; //判断冲洗烘干推杆伸出或缩回
		u2_printf("*%s*M8*F*/*/**",RX_BUF);
	}
	TIM2_Init(3600-1,25-1);           //打开定时器
//	if(((1==dir)&&(CXHG_Runed<CXHG_Lim))||((0==dir)&&(CXHG_Runed>0)))	
//	{	
		for(j=0;j<n;j++)
		{ 	
			while(!(__HAL_TIM_GET_FLAG(&TIM2_Handler,TIM_SR_CC3IF)));   //等待定时时间到，时间到跳出循环
			flag = !flag;
			__HAL_TIM_CLEAR_FLAG(&TIM2_Handler, TIM_SR_CC3IF);          //清除定时器中断标志位					
			PWM_CXHG=flag;                                              //冲洗烘干电机脉冲输出口高/低电平
			if(USART2_RX_LEN&0x8000)   //判断串口2是否收到指令信号
			{			
				len=USART2_RX_LEN&0x3fff;				
				USART2_RX_BUF[len]=0;			
				//若接收到STOP,则跳出循环	
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
					u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数	
					memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);         //清除串口2缓冲区
					USART2_RX_LEN=0;
				}				
			}
			if(UART4_RX_LEN&0x8000)	 //判断串口4是否收到指令信号
			{			
				len=UART4_RX_LEN&0x3fff;				
				UART4_RX_BUF[len]=0;			
				//若接收到STOP,则跳出循环	
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
					u2_printf("NotRun");    //收到指令，但正在执行当前函数，无法去执行去新收到的指令函数	
					memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);         //清除串口4缓冲区
					UART4_RX_LEN=0;
				}				
			}
			//通过上下行判断脉冲累计
			if(1==dir)
			{
				CXHG_Runed++;   //上行脉冲加
			}
			else
			{
				CXHG_Runed--;	//下行脉冲减				
			}
			//发送烘干推杆动画指令
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
	PWM_CXHG=0;   u2_printf("*%s*M8*T*/*/**",RX_BUF);     	 //冲洗烘干电机对应脉冲输出口拉低  
	TIM2_Stop();                                             //关闭定时器
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);             //清除串口2缓冲区
	USART2_RX_LEN=0;
	memset(UART4_RX_BUF,0,UART4_MAX_RECV_LEN);               //清除串口4缓冲区
	UART4_RX_LEN=0;
}	




