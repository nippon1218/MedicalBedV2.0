#include "initial.h"
#include "sys.h"

/**************全局变量******************/

//称重
unsigned long u1=0,u2=0,u3=0;       //测量得到的实物重量
unsigned int k,w,num=1;
u8 cz_time;

//wifi
u8 device_num;    //用于计算当前WiFi连接设备数

u8 *p;
u8 RX_BUF[15];   //保存智能终端发送来的指令

//WiFi配置-热点-默认名称和密码
u8 wifi_ssid[20]="Medical_Bed";	            //热点名称
u8 wifi_ssid_password[20]="12345678";	    //热点密码    

//WiFi配置-路由-默认值
u8 wifi_station[20]="tmqs";					//路由器名称
u8 wifi_station_password[20]="daizhiwen";	//路由器密码
u8 wifi_ap_ip[15]="192.168.1.115";          //IP地址
u16 wifi_ap_port=8086;                      //端口号

//WiFi配置数组
u8 wifi_ip_address[20]={0};                 //ip地址
u8 wifi_name[20]={0};                       //WiFi名称
u8 wifi_password[20]={0};                   //密码

const u8 modeap_buf[2]={"AP"};              //ap模式写入数组，此模式写入AP
const u8 modesta_buf[2]={"ST"};             //STA模式写入数组,此模式写入ST


//上位机设定角度极限值-默认值
u8  ZB_Lim=90;               //上位机设定支背运行角度
u8  SQT_Lim=40;              //上位机设定上曲腿运行角度
u8  XQT_Lim=80;              //上位机设定下曲腿运行角度
u8  ZF_Lim=60;               //上位机设定左翻运行角度
u8  YF_Lim=50;               //上位机设定右翻运行角度
u8  YL_Lim=100;              //上位机设定娱乐小桌子运动距离
u8  CXHG_Time=1;             //上位机设定娱乐坐便冲洗烘干时间/分钟
u32 ZBQ_Max=33000;           //坐便器运行下，计时器的arr（重装载值）12000

//已运行脉冲值
//基本功能电机
u16 ZB_Runed=0;             //支背，调整后的自动重装载值
u16 SQT_Runed=0;            //上曲腿，调整后的自动重装载值
u16 XQT_Runed=0;            //下曲腿，调整后的自动重装载值
u16 ZF_Runed=0;             //左翻，调整后的自动重装载值
u16 ZBH_Runed=0;            //左背护，调整后的自动重装载值
u16 ZYH_Runed=0;            //左腰护，调整后的自动重装载值
u16 YF_Runed=0;             //右翻，调整后的自动重装载值
u16 YBH_Runed=0;            //右背护，调整后的自动重装载值
u16 YYH_Runed=0;            //右腰护，调整后的自动重装载值
u32 YL_Runed=0;             //桌子，调整后的自动重装载值
u16 add_arr=5000;           //为保证复位到初始位置，另加额外脉冲值

//吊挂电机
//左肢
u32 ZGB_Runed=0;            //相对起始位置已运行脉冲数             
u32 ZGB_Lim=1000000;        //极限脉冲值 
u32 ZT_Runed=0;             //相对起始位置已运行脉冲数             
u32 ZT_Lim=1500000;         //极限脉冲值 
//右肢
u32 YGB_Runed=0;            //相对起始位置已运行脉冲数            
u32 YGB_Lim=1000000;        //极限脉冲值 
u32 YT_Runed=0;             //相对起始位置已运行脉冲数            
u32 YT_Lim=1500000;         //极限脉冲值 
//左右肢
u32 ZYGB_Runed=0;           //相对起始位置已运行脉冲数        
u32 ZYGB_Lim=1000000;       //极限脉冲值 
u32 ZYT_Runed=0;            //相对起始位置已运行脉冲数        
u32 ZYT_Lim=1500000;        //极限脉冲值 
//左小臂/小腿
u32 ZXB_Runed=0;            //相对起始位置已运行脉冲数        
u32 ZXB_Lim=500000;         //极限脉冲值 
u32 ZXT_Runed=0;            //相对起始位置已运行脉冲数        
u32 ZXT_Lim=500000;         //极限脉冲值 
//左大臂/大腿
u32 ZDB_Lim=1000000;        //极限脉冲值       
u32 ZDB_Runed=0;            //相对起始位置已运行脉冲数
u32 ZDT_Lim=1500000;        //极限脉冲值       
u32 ZDT_Runed=0;            //相对起始位置已运行脉冲数
//右小臂/小腿
u32 YXB_Lim=500000;         //极限脉冲值      
u32 YXB_Runed=0;            //相对起始位置已运行脉冲数
u32 YXT_Lim=500000;         //极限脉冲值      
u32 YXT_Runed=0;            //相对起始位置已运行脉冲数
//右大臂/大腿
u32 YDB_Lim=1000000;        //极限脉冲值      
u32 YDB_Runed=0;            //相对起始位置已运行脉冲数
u32 YDT_Lim=1500000;        //极限脉冲值      
u32 YDT_Runed=0;            //相对起始位置已运行脉冲数
//左右小臂/腿
u32 ZYXB_Lim=500000;        //极限脉冲值 
u32 ZYXB_Runed=0;           //相对起始位置已运行脉冲数
u32 ZYXT_Lim=500000;        //极限脉冲值 
u32 ZYXT_Runed=0;           //相对起始位置已运行脉冲数
//左右大臂/大腿
u32 ZYDB_Lim=1000000;       //极限脉冲值 
u32 ZYDB_Runed=0;           //相对起始位置已运行脉冲数
u32 ZYDT_Lim=1500000;       //极限脉冲值 
u32 ZYDT_Runed=0;           //相对起始位置已运行脉冲数

//冲洗烘干推杆
u32 CXHG_Runed=0;           //相对起始位置已运行脉冲数  
u32 CXHG_Lim=10000;         //极限脉冲
u32 CXHG1_Runed=0;          //相对起始位置已运行脉冲数  
u32 CXHG1_Lim=10000;        //极限脉冲

//坐便袋收紧前移动的推杆
u32 ZBDTG_Runed=0;          //相对起始位置已运行脉冲数  
u32 ZBDTG_Lim=8500;         //极限脉冲
//坐便袋收线
u32 ZBD_Lim=15000;          //极限脉冲

//复位状态标志位1：未复位 ； 0：复位到初始状态
//基本功能
u8 ZB_Flag=0;               //支背
u8 SQT_Flag=0;              //上曲腿
u8 XQT_Flag=0;              //下曲腿
u8 ZF_Flag=0;               //左翻
u8 YF_Flag=0;               //右翻
u8 ZBH_Flag=0;              //左背部护理
u8 YBH_Flag=0;              //右背部护理
u8 ZYH_Flag=0;              //左腰部护理
u8 YYH_Flag=0;              //右腰部护理
u8 ZBQ_Flag=0;              //坐便器
u8 ZDZBQ_Flag=0;            //自动坐便器
u8 YL_Flag=0;               //就餐娱乐一体桌
u8 JRAM_Flag=0;             //肌肉按摩
u8 CXHG_Flag=0;             //冲洗烘干
u8 SD_Flag=1;               //一键锁定程序
u8 GZ_Flag=0;               //电机故障标志位
u8 CX_Flag=0;               //手动冲洗标志位
u8 HG_Flag=0;               //手动烘干标志位

//吊挂功能
u8 ZXB_Flag=0;      //左小臂
u8 ZXT_Flag=0;      //左小腿
u8 YXB_Flag=0;      //右小臂
u8 YXT_Flag=0;      //右小腿
u8 ZDB_Flag=0;      //左大臂
u8 ZDT_Flag=0;      //左大腿
u8 YDB_Flag=0;      //右大臂
u8 YDT_Flag=0;      //右大腿
u8 ZDXB_Flag=0;     //左大小臂
u8 ZDXT_Flag=0;     //左大小腿
u8 YDXB_Flag=0;     //右大小臂
u8 YDXT_Flag=0;     //右大小腿
u8 ZYXB_Flag=0;     //左右小臂
u8 ZYXT_Flag=0;     //左右小腿
u8 ZYDB_Flag=0;     //左右大臂
u8 ZYDT_Flag=0;     //左右大腿
u8 ZYDXB_Flag=0;    //左右大小臂
u8 ZYDXT_Flag=0;    //左右大小腿

//发送图片
u8 ZB_Pic=0;    //支背
u8 SQT_Pic=0;   //上曲腿
u8 XQT_Pic=0;   //下曲腿
u8 YL_Pic=0;    //小桌子
u8 ZBQ_Pic=0;   //坐便器
u8 ZF_Pic=0;    //左翻身
u8 ZCF_Pic=0;   //左小侧翻
u8 YF_Pic=0;    //右翻身
u8 YCF_Pic=0;   //右小侧翻
u8 ZBH_Pic=0;   //左背部护理
u8 ZYH_Pic=0;   //左腰部护理
u8 YBH_Pic=0;   //右背部护理
u8 YYH_Pic=0;   //右腰部护理

//错误状态标志位
//驱动器返回-电机过载
u8 ZF3_GZ=0;    //左翻身
u8 ZF4_GZ=0;          
u8 ZF5_GZ=0;         
u8 YF3_GZ=0;    //右翻身
u8 YF4_GZ=0;         
u8 YF5_GZ=0;        
u8 ZBQ_GZ=0;    //自动坐便
u8 YL_GZ=0;     //就餐娱乐一体桌
u8 ZBH_GZ=0;    //左背部护理
u8 YBH_GZ=0;    //右背部护理
u8 ZYH_GZ=0;    //左腰部护理
u8 YYH_GZ=0;    //右腰部护理

//驱动器返回-电机失步
u8 ZF_SB=0;    //左翻身         
u8 YF_SB=0;    //右翻身         
u8 ZBQ_SB=0;   //自动坐便
u8 YL_SB=0;    //就餐娱乐一体桌
u8 ZBH_SB=0;   //左背部护理
u8 YBH_SB=0;   //右背部护理
u8 ZYH_SB=0;   //左腰部护理
u8 YYH_SB=0;   //右腰部护理

//方向标志位
u8 ZB_Dir_flag=0;     //支背方向标志位
u8 ZF_Dir_flag=0;     //左翻方向标志位
u8 YF_Dir_flag=0;     //右翻方向标志位
u8 ZBH_Dir_flag=0;    //左背部护理方向标志位
u8 YBH_Dir_flag=0;    //右背部护理方向标志位
u8 ZYH_Dir_flag=0;    //左腰部护理方向标志位
u8 YYH_Dir_flag=0;    //右腰部护理方向标志位
u8 ZDZBQ_Dir_flag=0;  //自动坐便器方向标志位
u8 JRAM_Dir_flag=0;   //肌肉按摩方向标志
u8 SD_Dir_flag=0;     //键锁标志
u8 XQT_State=0;       //自动坐便时记录曲腿是否已处于动作状态
u8 ZB_State=0;        //自动坐便时记录支背是否已处于动作状态
u32 WD1_flag=1;       //温度标志
u32 WD2_flag=1;       //温度标志

//吊挂电机频率
u32 DG_Freq=70-1;     //控制吊挂电机运行速度70-1

