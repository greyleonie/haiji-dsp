//�����Ƽ���HJR3000����������������װ�ã�DSPIC30F6010Aϵͳ
//�û�ϵͳ���ã��������弰����ֵ UserParms.h


#ifndef UserParms_H
#define UserParms_H

//**************  Oscillator ������ **************
#define dFoscExt        7200000					// �ⲿ����Ƶ��(Hz)
#define dPLL            8						// PLL����
#define dTimer1         0.0025					// ��ʱ��1�ж�ʱ��(s)
#define dLoopTimeInSec 	0.000050 				// PWM ����ʱ��(s) - 50 uS, 20Khz PWM
#define dDeadTimeSec 	0.0000002 				// ����Ϊ��λ������ʱ��(s)
//#define dBaudRate		9600					// ����ͨѶ������
#define dI2CBaudRate	100000					// I2CͨѶ������


//*************   Derived   *****************************
#define dFosc       	(dFoscExt*dPLL)     					// �ڲ�ʱ��Ƶ��					57600000
#define dFcy        	(dFosc/4)           					// ָ��Ƶ��						14400000
#define dTcy        	(1.0/dFcy)          					// ָ������ʱ��					0.00000006944444444
#define dTImer1Tcy  	(int)(dTimer1*dFcy) 					// ��ʱ��1����ֵ					36000	
#define dLoopInTcy 		(int)(dLoopTimeInSec*dFcy) 				// ��Tcy Ϊ��λ�Ļ���ѭ������	720
#define dDeadTime		(int)(dDeadTimeSec*dFcy)				// ��dTcys Ϊ��λ������ʱ��		28.8		
//#define dBaudRateTcy	((dFcy/16/dBaudRate)-1)					// ���в����ʼĴ�����ֵ				92
#define dI2CBaudRateTcy	((dFcy/dI2CBaudRate)-(dFcy/1111111)-1)		// I2C�����ʼĴ�����ֵ				92



//****************** EEPROM �洢��Ԫ���� ***********************
#define 				WORD    		1						//EEPROM��д����
#define 				ROW     		16
#define 				ALL_EEPROM      0xFFFF
#define 				ERROREE 		-1						//EEPROM��д��������




//************** ϵͳ��������ϵ�� **************

#define		SinTimeBy2		0.01								//���Ұ벨10mS
#define		DataGeiMax		(SinTimeBy2 / dLoopTimeInSec)		//���Ұ벨10mS,��PWM�жϴ���
#define		TimeMax			99.9000								//ʱ������������ֵ ʱ�䵥λ
#define		dwLoop			1000.0								//������������ ���ٶ�
#define		dwT1			400									//T1��ʱ���ĵ��������ڳ�������  1/0.0025=400
#define		IntTimeS		(TimeMax * dwT1)					//���ʱ���ڵ��жϴ���  99.9/0.0025=39960
#define		dwIntTimeS		(IntTimeS / (TimeMax * 10.0))		//��λ����ʱ���ڵ��жϴ���  39960/(99.9*10)=40
#define		DataMax			(IntTimeS * dwLoop)					//�������ֵ  39960*1000=39960000
#define		DataMaxLoop		(DataMax / dwIntTimeS)				//��λ����ʱ���ڵ����� 39960000/40=999000
#define		dqDataGei		(DataMax / DataGeiMax)				//����ת��ϵ��
#define		ActiveTime		0.000009
#define		ActivePWM		(ActiveTime * 2 / dTcy)
#define		ActiveLongAngle 75.0
#define		ActiveLongTime	(ActiveLongAngle * 0.02 / 360.0)
#define		ActiveLongPWM	(ActiveLongTime / dLoopTimeInSec)

#define		MinAngle		29.0
#define		MinAngleTime	(MinAngle * 0.02 / 360.0)
#define		OutDataMin		(MinAngleTime / dLoopTimeInSec)
#define		DataMin			(OutDataMin * dqDataGei)




//************** ��ѧ����1.15��ʽ **************
#define		PI				0x7FFF
#define		Sq3By2			0x6ED9
#define		OneBySq3		0x49E7

//************** �汾��Ϣ **************
#define		VerDateYear			6		// 2006
#define		VerSoft				100		// 1.00
#define		VerGTO				2000	// 2000A
#define		VerDe				5		// 


#endif


