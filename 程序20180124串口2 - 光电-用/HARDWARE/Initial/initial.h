#ifndef __INITIAL_H
#define __INITIAL_H
#include "sys.h"

/***************功能函数电机IO口*********************/

#define DIR1_Down PIout(3)  //支背下行信号线
#define DIR1_Up   PIout(7)  //支背上行信号线
#define DIR2_Down PIout(8)  //下曲腿信号线
#define DIR2_Up   PGout(10) //上曲腿信号线
#define DIR3 PDout(7)       //3号电机方向信号线     
#define DIR4 PDout(3)       //4号电机方向信号线
#define DIR5 PDout(2)       //5号电机方向信号线 
#define DIR6 PCout(12)      //6号电机方向信号线 
#define DIR6_1 PAout(5)     //6坐便袋收紧电机方向信号线 
#define DIR6_2 PHout(13)    //6坐便袋收紧电机推杆驱动信号线 
#define PWM6_2 PCout(4)     //6坐便袋收紧电机推杆驱动脉冲线  
#define RELAY6 PHout(12)    //控制坐便袋收紧电机通断的继电器
#define DIR7 PAout(6)       //7号电机方向信号线 

/***************吊挂电机方向口/脉冲口*********************/

#define DG_DIR1 PBout(9)   //1号吊挂电机方向信号线 
#define DG_DIR2 PBout(8)   //2号吊挂电机方向信号线 
#define DG_DIR3 PBout(7)   //3号吊挂电机方向信号线 
#define DG_DIR4 PBout(6)   //4号吊挂电机方向信号线

#define DG_PWM1 PGout(6)   //1号吊挂电机脉冲信号线 
#define DG_PWM2 PDout(13)  //2号吊挂电机脉冲信号线  
#define DG_PWM3 PGout(3)   //3号吊挂电机脉冲信号线 
#define DG_PWM4 PHout(11)  //4号吊挂电机脉冲信号线

/***************吊挂电机方向口*********************/

#define DG_Relay	PAout(12)		//吊挂继电器

/****************水箱***********************/

#define DIR_SB      PBout(11)          //水泵PB12
#define DIR_QB      PHout(3)           //气泵
#define DIR_HG      PBout(10)          //烘干
#define DIR_XZFPQ   PEout(3)           //旋转分配器
#define DIR_JR      PHout(3)           //加热-继电器
#define DIR_WD      PHout(8)           //温度传感器
#define Liq_Sensor  PHin(7)            //液位传感器

/************冲洗烘干推杆********************/

#define DIR_CXHG      PCout(1)     //冲洗烘干推杆方向口
#define PWM_CXHG      PBout(13)    //冲洗烘干脉冲方向口

/***************光电开关********************/

#define GD3_CS     PEin(6)       //3号电机光电开关
#define GD3_ZFZZ   PBin(15)      //左翻终止
#define GD3_YFZZ   PBin(14)      //右翻终止

#define GD4_CS     PEin(5)       //4号电机光电开关
#define GD4_ZFZZ   PEin(4)       //左翻终止
#define GD4_YFZZ   PHin(6)       //右翻终止

#define GD5_CS     PEin(2)       //5号电机光电开关
#define GD5_ZFZZ   PCin(13)      //左翻终止
#define GD5_YFZZ   PHin(9)   	 //右翻终止

#define GD6_CS     PCin(7)       //6号电机光电开关
#define GD6_ZZ     PCin(6) 
#define GD7_CS     PCin(8)       //7号电机光电开关
#define GD7_ZZ     PCin(9) 

#define GD3S  1
#define GD3LE 2
#define GD3RE 3

#define GD4S  4
#define GD4LE 5
#define GD4RE 6

#define GD5S 7
#define GD5LE 8
#define GD5RE	9

#define GD6S 10
#define GD6E 11

#define GD7S 12
#define GD7E 13

#define GD34S	14
#define GD34LE	15
#define GD34RE	16

//称重
extern unsigned long u1,u2,u3;       //测量得到的实物重量
extern unsigned int k,w,num;
extern u8 cz_time;

//wifi
extern u8 device_num;                //用于计算当前WiFi连接设备数

extern u8 *p;
extern u8 RX_BUF[]; 

//WiFi配置-热点-默认名称和密码
extern u8 wifi_ssid[];	            //热点名称
extern u8 wifi_ssid_password[];	    //热点密码    

//WiFi配置-路由-默认值
extern u8 wifi_station[];			//路由器名称
extern u8 wifi_station_password[];	//路由器密码
extern u8 wifi_ap_ip[];             //IP地址
extern u16 wifi_ap_port;            //端口号

//WiFi配置数组
extern u8 wifi_ip_address[];        //ip地址
extern u8 wifi_name[];              //WiFi名称
extern u8 wifi_password[];          //密码

extern const u8 modeap_buf[];       //ap模式写入数组，此模式写入AP
extern const u8 modesta_buf[];      //STA模式写入数组,此模式写入ST


//复位状态标志位1：未复位 ； 0：复位到初始状态
extern u8 ZB_Flag;         //支背
extern u8 SQT_Flag;        //上曲腿
extern u8 XQT_Flag;        //下曲腿
extern u8 ZF_Flag;         //左翻
extern u8 YF_Flag;         //右翻
extern u8 ZBH_Flag;        //左背部护理
extern u8 YBH_Flag;        //右背部护理
extern u8 ZYH_Flag;        //左腰部护理
extern u8 YYH_Flag;        //右腰部护理
extern u8 ZBQ_Flag;        //坐便器
extern u8 ZDZBQ_Flag;      //自动坐便器
extern u8 YL_Flag;         //就餐娱乐一体桌
extern u8 JRAM_Flag;       //肌肉按摩
extern u8 CXHG_Flag;       //冲洗烘干
extern u8 SD_Flag;         //一键锁定程序
extern u8 GZ_Flag;         //电机故障标志位

//方向标志位
extern u8 ZB_Dir_flag;     //支背方向标志位
extern u8 ZF_Dir_flag;     //左翻方向标志位
extern u8 YF_Dir_flag;     //右翻方向标志位
extern u8 ZBH_Dir_flag;    //左背部护理方向标志位
extern u8 YBH_Dir_flag;    //右背部护理方向标志位
extern u8 ZYH_Dir_flag;    //左腰部护理方向标志位
extern u8 YYH_Dir_flag;    //右腰部护理方向标志位
extern u8 ZDZBQ_Dir_flag;  //自动坐便器方向标志位
extern u8 JRAM_Dir_flag;   //肌肉按摩方向标志
extern u8 SD_Dir_flag;     //键锁标志
extern u8 XQT_State;       //自动坐便时记录曲腿是否已处于动作状态
extern u8 ZB_State;        //自动坐便时记录支背是否已处于动作状态
extern u32 WD1_flag;       //温度标志
extern u32 WD2_flag;       //温度标志

//方向状态标志位
extern u8 ZBH_Dir_flag;   //左背部护理方向标志位
extern u8 YBH_Dir_flag;   //右背部护理方向标志位
extern u8 ZYH_Dir_flag;   //左腰部护理方向标志位
extern u8 YYH_Dir_flag;   //右腰部护理方向标志位

extern u8 CX_Flag;        //手动冲洗标志位
extern u8 HG_Flag;        //手动烘干标志位

extern u8 XQT_State;      //自动坐便时记录曲腿是否已处于动作状态
extern u8 ZB_State;       //自动坐便时记录支背是否已处于动作状态
//吊挂功能
extern u8 ZXB_Flag;      //左小臂
extern u8 ZXT_Flag;      //左小腿
extern u8 YXB_Flag;      //右小臂
extern u8 YXT_Flag;      //右小腿
extern u8 ZDB_Flag;      //左大臂
extern u8 ZDT_Flag;      //左大腿
extern u8 YDB_Flag;      //右大臂
extern u8 YDT_Flag;      //右大腿
extern u8 ZDXB_Flag;     //左大小臂
extern u8 ZDXT_Flag;     //左大小腿
extern u8 YDXB_Flag;     //右大小臂
extern u8 YDXT_Flag;     //右大小腿
extern u8 ZYXB_Flag;     //左右小臂
extern u8 ZYXT_Flag;     //左右小腿
extern u8 ZYDB_Flag;     //左右大臂
extern u8 ZYDT_Flag;     //左右大腿
extern u8 ZYDXB_Flag;    //左右大小臂
extern u8 ZYDXT_Flag;    //左右大小腿

//发送图片
extern u8 ZB_Pic;    //支背
extern u8 SQT_Pic;   //上曲腿
extern u8 XQT_Pic;   //下曲腿
extern u8 YL_Pic;    //小桌子
extern u8 ZBQ_Pic;   //坐便器
extern u8 ZF_Pic;    //左翻身
extern u8 ZCF_Pic;   //左小侧翻
extern u8 YF_Pic;    //右翻身
extern u8 YCF_Pic;   //右小侧翻
extern u8 ZBH_Pic;   //左背部护理
extern u8 ZYH_Pic;   //左腰部护理
extern u8 YBH_Pic;   //右背部护理
extern u8 YYH_Pic;   //右腰部护理

//错误状态标志位
//驱动器返回-电机过载
extern u8 ZF3_GZ;       //左翻身
extern u8 ZF4_GZ;       //左翻身
extern u8 ZF5_GZ;       //左翻身
extern u8 YF3_GZ;       //右翻身
extern u8 YF4_GZ;       //右翻身
extern u8 YF5_GZ;       //右翻身
extern u8 ZBQ_GZ;       //自动坐便
extern u8 YL_GZ;        //就餐娱乐一体桌
extern u8 ZBH_GZ;       //左背部护理
extern u8 YBH_GZ;       //右背部护理
extern u8 ZYH_GZ;       //左腰部护理
extern u8 YYH_GZ;       //右腰部护理

//驱动器返回-电机失步
extern u8 ZF_SB;      //左翻身
extern u8 YF_SB;      //右翻身
extern u8 ZBQ_SB;     //自动坐便
extern u8 YL_SB;      //就餐娱乐一体桌
extern u8 ZBH_SB;     //左背部护理
extern u8 YBH_SB;     //右背部护理
extern u8 ZYH_SB;     //左腰部护理
extern u8 YYH_SB;     //右腰部护理

//发送图片
extern u8 ZB_Pic;        //支背
extern u8 SQT_Pic;       //上曲腿
extern u8 XQT_Pic;       //下曲腿
extern u8 YL_Pic;        //小桌子
extern u8 ZBQ_Pic;       //坐便器
extern u8 ZF_Pic;        //左翻身
extern u8 ZCF_Pic;       //左小侧翻
extern u8 YF_Pic;        //右翻身
extern u8 YCF_Pic;       //右小侧翻


//参数设定界面设置极限运行参数
extern u8  ZB_Lim;           //上位机设定支背运行角度
extern u8  SQT_Lim;          //上位机设定上曲腿运行角度
extern u8  XQT_Lim;          //上位机设定下曲腿运行角度
extern u8  ZF_Lim;           //上位机设定左翻运行角度
extern u8  YF_Lim;           //上位机设定右翻运行角度
extern u8  YL_Lim;           //上位机设定娱乐小桌子运动距离
extern u8  CXHG_Time;        //上位机设定娱乐坐便冲洗烘干时间
extern u32 ZBQ_Max;          //坐便器运行下，计时器的arr（重装载值）-6号电机

//已运行脉冲值
//基本功能电机
extern u16 ZB_Runed;             //支背，调整后的自动重装载值
extern u16 SQT_Runed;            //上曲腿，调整后的自动重装载值
extern u16 XQT_Runed;            //下曲腿，调整后的自动重装载值
extern u16 ZF_Runed;             //左翻，调整后的自动重装载值
extern u16 ZBH_Runed;            //左背护，调整后的自动重装载值
extern u16 ZYH_Runed;            //左腰护，调整后的自动重装载值
extern u16 YF_Runed;             //右翻，调整后的自动重装载值
extern u16 YBH_Runed;            //右背护，调整后的自动重装载值
extern u16 YYH_Runed;            //右腰护，调整后的自动重装载值
extern u32 YL_Runed;             //桌子，调整后的自动重装载值
extern u16 add_arr;              //为保证复位到初始位置，另加额外脉冲值

//吊挂康复训练脉冲值计算
//左肢
extern u32 ZGB_Runed;        //相对起始位置已运行脉冲数   
extern u32 ZGB_Lim;          //极限脉冲
extern u32 ZT_Runed;         //相对起始位置已运行脉冲数   
extern u32 ZT_Lim;           //极限脉冲
//右肢
extern u32 YGB_Runed;        //相对起始位置已运行脉冲数  
extern u32 YGB_Lim;          //极限脉冲
extern u32 YT_Runed;         //相对起始位置已运行脉冲数  
extern u32 YT_Lim;           //极限脉冲
//左右肢
extern u32 ZYGB_Runed;       //相对起始位置已运行脉冲数  
extern u32 ZYGB_Lim;         //极限脉冲
extern u32 ZYT_Runed;        //相对起始位置已运行脉冲数  
extern u32 ZYT_Lim;          //极限脉冲
//左小臂/小腿
extern u32 ZXB_Runed;        //相对起始位置已运行脉冲数  
extern u32 ZXB_Lim;          //极限脉冲
extern u32 ZXT_Runed;        //相对起始位置已运行脉冲数  
extern u32 ZXT_Lim;          //极限脉冲
//左大臂/大腿
extern u32 ZDB_Lim;          //极限脉冲    
extern u32 ZDB_Runed;        //相对起始位置已运行脉冲数
extern u32 ZDT_Lim;          //极限脉冲    
extern u32 ZDT_Runed;        //相对起始位置已运行脉冲数
//右小臂/小腿
extern u32 YXB_Lim;          //极限脉冲     
extern u32 YXB_Runed;        //相对起始位置已运行脉冲数
extern u32 YXT_Lim;          //极限脉冲     
extern u32 YXT_Runed;        //相对起始位置已运行脉冲数
//右大臂/大腿
extern u32 YDB_Lim;          //极限脉冲   
extern u32 YDB_Runed;        //相对起始位置已运行脉冲数
extern u32 YDT_Lim;          //极限脉冲   
extern u32 YDT_Runed;        //相对起始位置已运行脉冲数
//左右小臂/小腿
extern u32 ZYXB_Lim;         //极限脉冲     
extern u32 ZYXB_Runed;       //相对起始位置已运行脉冲数
extern u32 ZYXT_Lim;         //极限脉冲     
extern u32 ZYXT_Runed;       //相对起始位置已运行脉冲数
//左右大臂/大腿
extern u32 ZYDB_Lim;         //极限脉冲     
extern u32 ZYDB_Runed;       //相对起始位置已运行脉冲数
extern u32 ZYDT_Lim;         //极限脉冲     
extern u32 ZYDT_Runed;       //相对起始位置已运行脉冲数

//冲洗烘干推杆
extern u32 CXHG1_Runed;      //相对起始位置已运行脉冲数
extern u32 CXHG1_Lim;        //极限脉冲
extern u32 CXHG_Runed;       //冲洗烘干前推杆相对起始位置已运行脉冲数  
extern u32 CXHG_Lim;         //冲洗烘干前推杆极限脉冲

//坐便袋收进前移动的推杆
extern u32 ZBDTG_Runed;       //相对起始位置已运行脉冲数  
extern u32 ZBDTG_Lim;         //极限脉冲
extern u32 ZBD_Lim;           //极限脉冲

extern u32 DG_Freq;           //控制吊挂电机运行速度

//光电补偿
extern u16 M3GDL_BC;				  //3号电机左翻复位补偿
extern u16 M3GDR_BC;			  	//3号电机右翻复位补偿
extern u16 M4GDL_BC;				  //4号电机左翻复位补偿
extern u16 M4GDR_BC;				  //4号电机右翻复位补偿
extern u16 M5GDL_BC;				  //5号电机左翻复位补偿
extern u16 M5GDR_BC;				  //5号电机右翻复位补偿

#endif


