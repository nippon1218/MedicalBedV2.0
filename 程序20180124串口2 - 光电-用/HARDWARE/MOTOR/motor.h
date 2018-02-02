#ifndef __MOTOR_H
#define __MOTOR_H
#include "sys.h"


/**************************************************************
                   吊挂电机驱动函数
                   dir：控制吊挂电机速度
				   pulse：控制吊挂电机运行时间
				   注：吊挂电机2/3为小臂电机；
				       吊挂电机1/4为大臂电机；
					   电机初始正方向为1010；
***************************************************************/
void Hang_Init(void);                          //吊挂电机方向口、脉冲口初始化
void Fun_Auto_DG2(u16 dir,u32 pulse);          //吊挂电机2号电机驱动2
void Fun_Auto_DG3(u16 dir,u32 pulse);          //吊挂电机3号电机驱动4
void Fun_Auto_DG12(u16 dir,u32 pulse);         //吊挂1/2号电机同时驱动
void Fun_Auto_DG23(u16 dir,u32 pulse);         //吊挂1/3号电机同时驱动
void Fun_Auto_DG34(u16 dir,u32 pulse);         //吊挂3/4号电机同时驱动
void Fun_Auto_DG1234(u16 dir,u32 pulse);       //吊挂1/2/3/4号电机同时驱动

void Fun_Hand_DG2(u16 dir,u32 pulse);          //吊挂电机2号电机驱动
void Fun_Hand_DG12(u16 dir,u32 pulse);         //吊挂1/2号电机同时驱动      
void Fun_Hand_DG3(u16 dir,u32 pulse);          //吊挂电机3号电机驱动
void Fun_Hand_DG34(u16 dir,u32 pulse);         //吊挂3/4号电机同时驱动
void Fun_Hand_DG23(u16 dir,u32 pulse);         //吊挂2/3号电机同时驱动
void Fun_Hand_DG1234(u16 dir,u32 pulse);       //吊挂1/2/3/4号电机同时驱动

/**************************************************************
                   功能函数电机驱动函数
                   arr：自动重装值
				   psc：时钟预分频数
***************************************************************/
void Motor_Init(void);             //电机IO口初始化函数

void MotorStart(u8 Motori,u8 dir,u16 arr,u16 psc);  //单个电机启动
void MotorStop(u8 Motori);                          //单个电机停止
void Motor_All_Stop(void);                          //所有电机停止
void Motor4_BC(u8 dir,u16 time_arr,u16 arr,u16 psc);//电机4补偿函数

void Fun_ZBTG(u8 dir,u32 pulse);    //坐便袋扎紧推杆驱动函数
void ZBD_Start(u16 arr,u16 psc);   //坐便袋收线驱动函数
void ZBD_Stop(void);

#endif
