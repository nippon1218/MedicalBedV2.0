#include "Hang.h"
#include "sys.h"
#include "usart.h"
#include "led.h"
#include "motor.h"
#include "function.h"
#include "pcf8574.h"
#include "delay.h"
#include "initial.h"

void HangRun(u8 dir,u8 height,u8 hang1,u8 hang2,u8 hang3,u8 hang4)
{
	Hang_Init();         //电机方向口初始化函数
	int i,flag=1;        //flag为脉冲高低标志位
	int j=0,k=0;
	
	DG_DIR1=dir;         //1号吊挂电机转动方向控制，高电平Up，低电平Down
	DG_DIR2=!dir;		 //2号吊挂电机转动方向控制，高电平Down，低电平Up
	DG_DIR3=dir;	     //3号吊挂电机转动方向控制，高电平Up，低电平Down
	DG_DIR4=!dir;		 //4号吊挂电机转动方向控制，高电平Down，低电平Up
	
	memset(USART2_RX_BUF,0,USART2_MAX_RECV_LEN);			
	USART2_RX_LEN=0; 
	TIM10_Init(70-1,25-1);                       //打开定时器3
	
    for(i=0;i<100000*height;i++)   //最终确定为3000000
    { 	
			while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) );   //等待定时时间到，时间到跳出循环
			flag = !flag ;
			__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF);             //清除中断标志位
			if(hang1==1)
			{
				DG_PWM1=flag;               //3号吊挂电机脉冲输出口高电平
			}
			if(hang2==1)
			{
				DG_PWM2=flag;               //3号吊挂电机脉冲输出口高电平
			}
			if(hang3==1)
			{
				DG_PWM3=flag;               //3号吊挂电机脉冲输出口高电平
			}
			if(hang4==1)
			{
				DG_PWM4=flag;               //3号吊挂电机脉冲输出口高电平
			}
	  }
		DG_PWM1=0;              //3号吊挂电机对应脉冲输出口拉低 
		DG_PWM2=0; 
		DG_PWM3=0; 
		DG_PWM4=0; 
		TIM10_Stop();             //关闭定时器
		u2_printf("%d\r\n",height);
			if(hang1==1)
			{
				u2_printf("hang1\r\n");
			}
			if(hang2==1)
			{
				u2_printf("hang2\r\n");
			}
			if(hang3==1)
			{
				u2_printf("hang3\r\n"); 
			}
			if(hang4==1)
			{
				u2_printf("hang4\r\n");
			}
}




void HangRunAuto(u8 dir,u8 turn,u8 ArmLeg,u8 times,u16 height)
{
	Hang_Init();         //电机方向口初始化函数
	int i,flag=1;        //flag为脉冲高低标志位
	int j=0,k=0;					
	
	DG_DIR1=dir;       //1号吊挂电机转动方向控制，高电平Up，低电平Down
	DG_DIR2=!dir;			 //2号吊挂电机转动方向控制，高电平Down，低电平Up
	DG_DIR3=dir;			 //3号吊挂电机转动方向控制，高电平Up，低电平Down
	DG_DIR4=!dir;		  	//4号吊挂电机转动方向控制，高电平Down，低电平Up
	
	TIM10_Init(70-1,25-1);                       //打开定时器3

	for(i=0;i<100000*height;i++)   //最终确定为3000000
	{
		while(!(__HAL_TIM_GET_FLAG(&TIM10_Handler, TIM_SR_CC1IF) ) );
		flag=!flag;
		__HAL_TIM_CLEAR_FLAG(&TIM10_Handler, TIM_SR_CC1IF); 
		if(turn==0)
		{
			DG_PWM2=flag;
			if(i%times==0)
			{DG_PWM1=!DG_PWM1;}
			
			if(ArmLeg==0)	//臂，0
			{
				if(1==dir)
				{ZGB_Runed++;}
				else
				{ZGB_Runed--;}
				
				j=ZGB_Runed/(100000*height/4);
				j=j+1;
				
				if(k!=j)
				{
					k=j;
					if(k==1)	
					{
						u2_printf("CT_ZZ1");
					}
					else if(k==2)	
					{
						u2_printf("CT_ZZ2");
					}
					else if(k==3)
					{
						u2_printf("CT_ZZ3");
					}
					else if(k==4)
					{
						u2_printf("CT_ZZ4");
					}
					else if(k==5)
					{
						u2_printf("CT_ZZ5");
					}			
				}	
				
			}
			else		//腿，1
			{
				if(1==dir)
				{ZT_Runed++;}
				else
				{ZT_Runed--;}
				
				j=ZT_Runed/(100000*height/4);
				j=j+1;
				
				if(k!=j)
				{
					k=j;
					if(k==1)	
					{
						u2_printf("CT_ZT1");
					}
					else if(k==2)	
					{
						u2_printf("CT_ZT2");
					}
					else if(k==3)
					{
						u2_printf("CT_ZT3");
					}
					else if(k==4)
					{
						u2_printf("CT_ZT4");
					}
					else if(k==5)
					{
						u2_printf("CT_ZT5");
					}			
				}	
			}	
		}
		else
		{
			DG_PWM3=!DG_PWM3;
			if(i%times==0)
			{DG_PWM4=!DG_PWM4  ;}
			
			if(ArmLeg==0)	//臂，0
			{
				if(1==dir)
				{YGB_Runed++;}
				else
				{YGB_Runed--;}
				
				j=YGB_Runed/(100000*height/4);
				j=j+1;
				
				if(k!=j)
				{
					k=j;
					if(k==1)	
					{
						u2_printf("CT_YZ1");
					}
					else if(k==2)	
					{
						u2_printf("CT_YZ2");
					}
					else if(k==3)
					{
						u2_printf("CT_YZ3");
					}
					else if(k==4)
					{
						u2_printf("CT_YZ4");
					}
					else if(k==5)
					{
						u2_printf("CT_YZ5");
					}			
				}					
			}
			else		//腿，1
			{
				if(1==dir)
				{YT_Runed++;}
				else
				{YT_Runed--;}
				
				j=YT_Runed/(100000*height/4);
				j=j+1;
		
				if(k!=j)
				{
					k=j;
					if(k==1)	
					{
						u2_printf("CT_YT1");
					}
					else if(k==2)	
					{
						u2_printf("CT_YT2");
					}
					else if(k==3)
					{
						u2_printf("CT_YT3");
					}
					else if(k==4)
					{
						u2_printf("CT_YT4");
					}
					else if(k==5)
					{
						u2_printf("CT_YT5");
					}			
				}	
			}			
		}
	}
	DG_DIR1=0;              //3号吊挂电机对应脉冲输出口拉低 
	DG_PWM2=0; 
	DG_PWM3=0; 
	DG_PWM4=0; 		
	TIM10_Stop();             //关闭定时器
	u2_printf("\r\ndir=%d,turn=%d,ArmLeg=%d,times=%d,height=%d\r\n",dir,turn,ArmLeg,times,height);
}

void Uart_Auto_Arm_Leg(u8 dir,u8 turn,u8 ArmLeg,u8 times,u16 height)
{
	int j;
	if((SD_Flag==1)&&(0==ZB_Flag)&&(0==SQT_Flag)&&(0==XQT_Flag)&&(0==ZBQ_Flag)&&(0==ZF_Flag)&&(0==YF_Flag))
   { 
		 DG_Relay=1;	
		 if(strstr((const char *)USART2_RX_BUF,(const char *)"BZZ"))
		 {
			 if(ZXT_Flag==0)       //防止按键误触发，导致标志位置位
			{	
				ZXB_Flag=1;
				delay_ms(200);
				u2_printf("KS");
				delay_ms(200);
				u2_printf("DGZZKS");				
			}
		 }
		else if(strstr((const char *)USART2_RX_BUF,(const char *)"TZZ"))    //左腿
		{
			if(ZXB_Flag==0)      //防止按键误触发，导致标志位置位
			{	
				ZXT_Flag=1;
				delay_ms(200);
				u2_printf("KS");
				delay_ms(200);
				u2_printf("DGZTKS");
				delay_ms(200);
			}			
		}		 
		HangRunAuto(1,0,0,2,15);
		delay_ms(1000);	 
		for(j=0;j<1;j++)                   //进行t此左肢康复训练
		{
			Fun_Auto_DG2(1,75000);     //向上运动
			delay_ms(1000);
			Fun_Auto_DG2(0,75000);     //向下运动
			delay_ms(1000);	
		}					 
	 }
}



