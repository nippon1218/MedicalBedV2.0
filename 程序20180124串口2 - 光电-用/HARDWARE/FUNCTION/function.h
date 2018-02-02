#ifndef __FUN_H
#define __FUN_H
#include "sys.h"
#include "usart.h"
#include "common.h"

//集成函数 
void All_Init(void);   //系统初始化              					
void U2_Wifi_SZ(void); //WIFI设置         
void U2_CSSZ(void);    //上位机界面参数设置函数
void U2_JCGN(void);    //基础功能函数
void U2_GJGN(void);    //高级功能函数
void U2_FW(void);      //复位函数

//基本功能函数
void Fun_ZB(void);      //支背
void Fun_SQT(void);     //上曲腿
void Fun_XQT(void);     //下曲腿
void Fun_ZF(void);      //左翻
void Fun_YF(void);      //右翻
void Fun_YL(void);      //办公娱乐一体桌
void Fun_YL1(void);			 //办公娱乐一体桌1
void Fun_YL2(void); 			//办公娱乐一体桌2
void Fun_ZBH(void);     //左背部护理
void Fun_YBH(void);     //右背部护理 
void Fun_ZYH(void);     //左腰部护理
void Fun_YYH(void);     //右腰部护理
void Fun_JRAM(void);    //肌肉按摩
void Fun_JR(void);      //加热
void Fun_Get_Ang(void); //通过串口2获取上位机新的脉冲值

void DeskRunNew(void);

//护栏功能函数
void Fun_HL_ZB(void);    //支背
void Fun_HL_ZF(void);    //左翻身
void Fun_HL_YF(void);    //右翻身
void Fun_HL_BH(void);    //背部护理
void Fun_HL_YH(void);    //腰部护理
u8   Fun_HL_SD(void);    //一键锁定

//自动坐便
void Fun_ZDZBQ(void);      //自动坐便
void Fun_ZB_XQT(void);     //支背下曲腿同时运行
void Fun_ZBQ(u8 dir);      //坐便器打开/关闭
void Fun_ZBD(u8 dir);      //坐便袋收紧
void Fun_CXHG(void);       //冲洗烘干
void Fun_SDCX(void);       //手动冲洗
void Fun_SDHG(void);       //手动烘干
void Fun_ZDCX(void);       //自动冲洗
void Fun_ZDHG(void);       //自动烘干
u8   Fun_CZ(void);         //称重
u8   Fun_CZ1(void);        //称重


//专家系统
void Fun_ZJ_ZB(void);     //专家系统支背
void Fun_ZJ_ZYF(void);    //专家系统翻身
void Fun_ZJ_SXQT(void);   //专家系统曲腿
void Fun_ZJ_ZDZB(void);   //专家系统自动坐便

//吊挂康复训练
//自动
void Fun_ZD_ZZ(int t);    //左肢康复训练
void Fun_ZD_YZ(int t);    //右肢康复训练
void Fun_ZD_ZYZ(int t);   //左右肢康复训练 

//手动
void Fun_SD_ZXB(void);    //左小臂
void Fun_SD_ZDB(void);    //左大臂
void Fun_SD_ZB(void);     //左大小臂

void Fun_SD_ZXT(void);    //左小腿
void Fun_SD_ZDT(void);    //左大腿
void Fun_SD_ZT(void);     //左大小腿

void Fun_SD_YXB(void);    //右小臂
void Fun_SD_YDB(void);    //右大臂
void Fun_SD_YB(void);     //右大小臂

void Fun_SD_YXT(void);    //右小腿
void Fun_SD_YDT(void);    //右大腿
void Fun_SD_YT(void);     //右大小腿

void Fun_SD_ZYXB(void);   //左右小臂
void Fun_SD_ZYDB(void);   //左右大臂
void Fun_SD_ZYB(void);    //左右大小臂

void Fun_SD_ZYXT(void);   //左右小腿
void Fun_SD_ZYDT(void);   //左右大腿
void Fun_SD_ZYT(void);    //左右大小腿

//复位功能函数
void Fun_FW_ALL(void);    //掉电复位函数
void Fun_FW_ALL_GD(void);    //掉电复位函数
void Fun_FW_ZB(void);     //支背复位
void Fun_FW_QT(void);     //曲腿复位
void Fun_FW_YL(void);     //就餐娱乐一体桌复位
void Fun_FW_CF(u8 dir);   //5号电机反向复位0;正向复位1
void Fun_FW_ZF(void);     //左翻身复位
void Fun_FW_YF(void);     //右翻身复位

//联动函数
void Fun_LD(void);        //功能函数联动
void WriteInU2(char *p);  //将字符串写入到串口2的USART2_RX_BUF中
void WriteInU4(char *p);  //将字符串写到串口4中

//WIFI集成功能函数
void WIFI_JCGN(void);    //基础功能函数
void WIFI_GJGN(void);    //高级功能函数
void WIFI_FW(void);      //复位函数

void Wifi_Send(u8 *data);              //WiFi发送函数
void Wifi_ToPC(u8 *data);              //WiFi发送给PC函数
void WiFi_ToSJ(u8 *data);              //WiFi发送给手机APP函数
void WiFi_ToYKQ(u8 *data);             //WiFi发送给遥控器函数
void WiFi_ToHL(u8 *data);              //WiFi发送给护栏函数
void WiFi_ToPC(u8 *data);              //WiFi发送给PC棒函数

//将运行角度转化为脉冲数
u16 Ang_To_Arr_ZB(u8 angle);           //将支背运行角度转化为脉冲数
u16 Ang_To_Arr_SXQT(u8 angle);         //将曲腿运行角度转化为脉冲数
u16 Ang_To_Arr_ZYFS(u8 angle);         //将翻身运行角度转化为脉冲数
u16 Ang_To_Arr_YL(u8 distance);        //将桌子运行角度转化为脉冲数
u32 Ang_To_Arr_YL2(u8 distance);       //将桌子运行角度转化为脉冲数
void Read_Ang(void);                   //读取上位机设置的角度值和距离值

//调试电机函数
void IO_TEST(void);        //IO口测试函数 
//基本功能电机
void Motor1(u8 dir);			//1号电机运行
void Motor2(u8 dir);			//2号电机运行
void Motor3(u8 dir);			//3号电机运行
void Motor4(u8 dir);			//4号电机运行
void Motor5(u8 dir);			//5号电机运行
void Motor6(u8 dir);			//6号电机运行
void Motor7(u8 dir);			//7号电机运行
//吊挂电机
void TestAll(u8 dir);			//吊挂电机测试函数，4个吊挂一起运行
void Hang1(u8 dir);				//1号吊挂电机测试函数
void Hang2(u8 dir);				//2号吊挂电机测试函数
void Hang3(u8 dir);				//3号吊挂电机测试函数
void Hang4(u8 dir);				//4号吊挂电机测试函数

#endif

