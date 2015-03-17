//海吉科技，HJR3000型智能软启动控制装置，DSPIC30F6010A系统
//用户系统配置，常数定义及配置值 UserParms.h


#ifndef UserParms_H
#define UserParms_H

//**************  Oscillator （晶振） **************
#define dFoscExt        7200000					// 外部晶振频率(Hz)
#define dPLL            8						// PLL倍数
#define dTimer1         0.0025					// 定时器1中断时间(s)
#define dLoopTimeInSec 	0.000050 				// PWM 周期时间(s) - 50 uS, 20Khz PWM
#define dDeadTimeSec 	0.0000002 				// 以秒为单位的死区时间(s)
//#define dBaudRate		9600					// 串行通讯波特率
#define dI2CBaudRate	100000					// I2C通讯波特率


//*************   Derived   *****************************
#define dFosc       	(dFoscExt*dPLL)     					// 内部时钟频率					57600000
#define dFcy        	(dFosc/4)           					// 指令频率						14400000
#define dTcy        	(1.0/dFcy)          					// 指令周期时间					0.00000006944444444
#define dTImer1Tcy  	(int)(dTimer1*dFcy) 					// 定时器1计数值					36000	
#define dLoopInTcy 		(int)(dLoopTimeInSec*dFcy) 				// 以Tcy 为单位的基本循环周期	720
#define dDeadTime		(int)(dDeadTimeSec*dFcy)				// 以dTcys 为单位的死区时间		28.8		
//#define dBaudRateTcy	((dFcy/16/dBaudRate)-1)					// 串行波特率寄存器的值				92
#define dI2CBaudRateTcy	((dFcy/dI2CBaudRate)-(dFcy/1111111)-1)		// I2C波特率寄存器的值				92



//****************** EEPROM 存储单元常数 ***********************
#define 				WORD    		1						//EEPROM读写参数
#define 				ROW     		16
#define 				ALL_EEPROM      0xFFFF
#define 				ERROREE 		-1						//EEPROM读写参数变量




//************** 系统参数定标系数 **************

#define		SinTimeBy2		0.01								//正弦半波10mS
#define		DataGeiMax		(SinTimeBy2 / dLoopTimeInSec)		//正弦半波10mS,的PWM中断次数
#define		TimeMax			99.9000								//时间参数给定最大值 时间单位
#define		dwLoop			1000.0								//给定基本步长 加速度
#define		dwT1			400									//T1定时器的倒数，便于程序运算  1/0.0025=400
#define		IntTimeS		(TimeMax * dwT1)					//最大时间内的中断次数  99.9/0.0025=39960
#define		dwIntTimeS		(IntTimeS / (TimeMax * 10.0))		//单位给定时间内的中断次数  39960/(99.9*10)=40
#define		DataMax			(IntTimeS * dwLoop)					//数据最大值  39960*1000=39960000
#define		DataMaxLoop		(DataMax / dwIntTimeS)				//单位给定时间内的增量 39960000/40=999000
#define		dqDataGei		(DataMax / DataGeiMax)				//定标转换系数
#define		ActiveTime		0.000009
#define		ActivePWM		(ActiveTime * 2 / dTcy)
#define		ActiveLongAngle 75.0
#define		ActiveLongTime	(ActiveLongAngle * 0.02 / 360.0)
#define		ActiveLongPWM	(ActiveLongTime / dLoopTimeInSec)

#define		MinAngle		29.0
#define		MinAngleTime	(MinAngle * 0.02 / 360.0)
#define		OutDataMin		(MinAngleTime / dLoopTimeInSec)
#define		DataMin			(OutDataMin * dqDataGei)




//************** 数学常数1.15格式 **************
#define		PI				0x7FFF
#define		Sq3By2			0x6ED9
#define		OneBySq3		0x49E7

//************** 版本信息 **************
#define		VerDateYear			6		// 2006
#define		VerSoft				100		// 1.00
#define		VerGTO				2000	// 2000A
#define		VerDe				5		// 


#endif


