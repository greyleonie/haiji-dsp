//海吉科技，HJR3000型智能软启动控制装置，DSPIC30F6010A系统
//AD转换中断程序文件，ADInterrupt.c，根据运行模式，进行转差矢量控制计算

//头文件
#include "UserParms.h"	//用户系统配置，常数定义及配置值
#include "Function.h"	//系统外部调用函数声明，内部调用函数在对应文件内声明
#include "variable.h"	//系统全局变量声明，局部变量在对应文件内声明

unsigned int AX_int_AD = 0;
unsigned long AX_long_AD = 0;

void CarDescend(void);

//***************** AD转换中断 ***********************************//
void __attribute__((__interrupt__)) _ADCInterrupt(void)
{
	MeauParm.BackupMeauPeak = ADCBUF0;
	if(MeauParm.BackupMeauPeak > (MeauParm.BackupMeauPeakOld + 50) )
		MeauParm.BackupMeauPeak = MeauParm.BackupMeauPeakOld + 50;
	else if(MeauParm.BackupMeauPeak < (MeauParm.BackupMeauPeakOld - 50) )
		MeauParm.BackupMeauPeak = MeauParm.BackupMeauPeakOld - 50;
	MeauParm.BackupMeauPeakOld = MeauParm.BackupMeauPeak;
		
	MeauParm.MainMeauPeak = ADCBUF1;
	if(MeauParm.MainMeauPeak > (MeauParm.MainMeauPeakOld + 50) )
		MeauParm.MainMeauPeak = MeauParm.MainMeauPeakOld + 50;
	else if(MeauParm.MainMeauPeak < (MeauParm.MainMeauPeakOld - 50) )
		MeauParm.MainMeauPeak = MeauParm.MainMeauPeakOld - 50;
	MeauParm.MainMeauPeakOld = MeauParm.MainMeauPeak;
	
	AX_int_AD = ADCBUF2;
	VolParms.PeakUin = ( (long) SysParms.MaxMeauVol * AX_int_AD) >> 10;	
	if(VolParms.PeakUin > (VolParms.PeakUinOld + 50) )
		VolParms.PeakUin = VolParms.PeakUinOld + 50;
	else if(VolParms.PeakUin < (VolParms.PeakUinOld - 50) )
		VolParms.PeakUin = VolParms.PeakUinOld - 50;
	VolParms.PeakUinOld = VolParms.PeakUin;
	
	AX_int_AD = ADCBUF3;
	CurParms.PeakIU = ( (long) SysParms.MaxMeauCur * AX_int_AD) >> 10;
	if(CurParms.PeakIU > (CurParms.PeakIUOld + 50) )
		CurParms.PeakIU = CurParms.PeakIUOld + 50;
	else if(CurParms.PeakIU < (CurParms.PeakIUOld - 50) )
		CurParms.PeakIU = CurParms.PeakIUOld - 50;
	CurParms.PeakIUOld = CurParms.PeakIU;
	
	AX_int_AD = ADCBUF4;
	CurParms.PeakIV = ( (long) SysParms.MaxMeauCur * AX_int_AD) >> 10;
	if(CurParms.PeakIV > (CurParms.PeakIVOld + 50) )
		CurParms.PeakIV = CurParms.PeakIVOld + 50;
	else if(CurParms.PeakIV < (CurParms.PeakIVOld - 50) )
		CurParms.PeakIV = CurParms.PeakIVOld - 50;
	CurParms.PeakIVOld = CurParms.PeakIV;
	
	AX_int_AD = ADCBUF5;
	CurParms.PeakIW = ( (long) SysParms.MaxMeauCur * AX_int_AD) >> 10;
	if(CurParms.PeakIW > (CurParms.PeakIWOld + 50) )
		CurParms.PeakIW = CurParms.PeakIWOld + 50;
	else if(CurParms.PeakIW < (CurParms.PeakIWOld - 50) )
		CurParms.PeakIW = CurParms.PeakIWOld - 50;
	CurParms.PeakIWOld = CurParms.PeakIW;
	
	CurParms.Times = CurParms.Times + 1;
	if(CurParms.Times > 4095 )
	{
		CurParms.Times = 0;
		MainState.Cur = 1;
		CurParms.IU = (long) CurParms.AccIU >> 11;
		CurParms.IV = (long) CurParms.AccIV >> 11;
		CurParms.IW = (long) CurParms.AccIW >> 11;
		VolParms.Uin = (long) VolParms.AccUin >> 12;
		VolParms.Uin = (long) VolParms.Uin + SysParms.AddMeauVol;
		MeauParm.MainMeauInit[0] = (long) MeauParm.MainMeauAcc >> 12;
		if(MeauParm.MainMeauInit[0] < 30)
		{
			AutoRunParm.OutputState = AutoRunParm.OutputState | 0x1000;
			OutputIO.MainMeauError = 1;
			RunState.MainOpen = 1;
			MeauParm.MainMeau = 0;
			MeauParm.MainMeauCom = 0;
			MeauParm.MainMeauInit[7] = 0;
			MeauParm.MainMeauInit[6] = 0;
			MeauParm.MainMeauInit[5] = 0;
			MeauParm.MainMeauInit[4] = 0;
			MeauParm.MainMeauInit[3] = 0;
			MeauParm.MainMeauInit[2] = 0;
			MeauParm.MainMeauInit[1] = 0;
		}else
		{
			AX_long_AD = (long) MeauParm.MainMeauInit[0] * MeauParm.MainMul;
			MeauParm.MainMeauInit[0] =  ( (long) AX_long_AD - MeauParm.MainAdd) >> 10;
			if(MeauParm.MainMeauInit[0] < 0)
				MeauParm.MainMeauInit[0] = 0;
			MeauParm.MainMeauInit[0] = ( (long)MeauParm.MainMeauInit[0] * MeauParm.MainMeauMax) >> 10;
			MeauParm.MainMeauInit[0] = MeauParm.MainMeauInit[0] + MeauParm.MainMeauFine - 10000 ;
			if(MeauParm.MainMeauInit[0] < 0)
				MeauParm.MainMeauInit[0] = 0;
			if(RunState.MainOpen == 1)
			{
				MeauParm.MainEnumerate = MeauParm.MainEnumerate + 1;
				if(MeauParm.MainEnumerate > 10)
				{
					RunState.MainOpen = 0;
					AutoRunParm.OutputState = AutoRunParm.OutputState & 0xEFFF;
					OutputIO.MainMeauError = 0;
					MeauParm.MainEnumerate = 0;
				}
			}else 
			{
				AutoRunParm.OutputState = AutoRunParm.OutputState & 0xEFFF;
				OutputIO.MainMeauError = 0;
			}
			MeauParm.MainMeauCom = ( (long) MeauParm.MainMeauInit[0] + MeauParm.MainMeauInit[1] + MeauParm.MainMeauInit[2] + MeauParm.MainMeauInit[3]) >> 2;// + MeauParm.MainMeauInit[4] + MeauParm.MainMeauInit[5] + MeauParm.MainMeauInit[6] + MeauParm.MainMeauInit[7]) >> 3;
			//MeauParm.MainMeauInit[7] = MeauParm.MainMeauInit[6];
			//MeauParm.MainMeauInit[6] = MeauParm.MainMeauInit[5];
			//MeauParm.MainMeauInit[5] = MeauParm.MainMeauInit[4];
			//MeauParm.MainMeauInit[4] = MeauParm.MainMeauInit[3];
			MeauParm.MainMeauInit[3] = MeauParm.MainMeauInit[2];
			MeauParm.MainMeauInit[2] = MeauParm.MainMeauInit[1];
			MeauParm.MainMeauInit[1] = MeauParm.MainMeauInit[0];
		}
		MeauParm.BackupMeauInit[0] = (long) MeauParm.BackupMeauAcc >> 12;
		if(MeauParm.BackupMeauInit[0] < 30)
		{
			AutoRunParm.OutputState = AutoRunParm.OutputState | 0x2000;
			OutputIO.BackupMeauError = 1;
			RunState.BackupOpen = 1;
			MeauParm.BackupMeau = 0;
			MeauParm.BackupMeauInit[7] = 0;
			MeauParm.BackupMeauInit[6] = 0;
			MeauParm.BackupMeauInit[5] = 0;
			MeauParm.BackupMeauInit[4] = 0;
			MeauParm.BackupMeauInit[3] = 0;
			MeauParm.BackupMeauInit[2] = 0;
			MeauParm.BackupMeauInit[1] = 0;
		}else
		{
			AX_long_AD = (long) MeauParm.BackupMeauInit[0] * MeauParm.BackupMul;
			MeauParm.BackupMeauInit[0] =  ( (long) AX_long_AD - MeauParm.BackupAdd) >> 10;
			if(MeauParm.BackupMeauInit[0] < 0)
				MeauParm.BackupMeauInit[0] = 0;
			MeauParm.BackupMeauInit[0] = ( (long) MeauParm.BackupMeauInit[0] * MeauParm.BackupMeauMax) >> 10;
			MeauParm.BackupMeauInit[0] = MeauParm.BackupMeauInit[0] + MeauParm.BackupMeauFine - 10000 ;
			if(MeauParm.BackupMeauInit[0] < 0)
				MeauParm.BackupMeauInit[0] = 0;
			if(RunState.BackupOpen == 1)
			{
				MeauParm.BackupEnumerate = MeauParm.BackupEnumerate + 1;
				if(MeauParm.BackupEnumerate > 10)
				{
					RunState.BackupOpen = 0;
					AutoRunParm.OutputState = AutoRunParm.OutputState & 0xDFFF;
					OutputIO.BackupMeauError = 0;
					MeauParm.BackupEnumerate = 0;
				}
			}else 
			{
				AutoRunParm.OutputState = AutoRunParm.OutputState & 0xDFFF;
				OutputIO.BackupMeauError = 0;
			}
			MeauParm.BackupMeau = ( (long) MeauParm.BackupMeauInit[0] + MeauParm.BackupMeauInit[1] + MeauParm.BackupMeauInit[2] + MeauParm.BackupMeauInit[3]) >> 2;// + MeauParm.BackupMeauInit[4] + MeauParm.BackupMeauInit[5] + MeauParm.BackupMeauInit[6] + MeauParm.BackupMeauInit[7]) >> 3;
			//MeauParm.BackupMeauInit[7] = MeauParm.BackupMeauInit[6];
			//MeauParm.BackupMeauInit[6] = MeauParm.BackupMeauInit[5];
			//MeauParm.BackupMeauInit[5] = MeauParm.BackupMeauInit[4];
			//MeauParm.BackupMeauInit[4] = MeauParm.BackupMeauInit[3];
			MeauParm.BackupMeauInit[3] = MeauParm.BackupMeauInit[2];
			MeauParm.BackupMeauInit[2] = MeauParm.BackupMeauInit[1];
			MeauParm.BackupMeauInit[1] = MeauParm.BackupMeauInit[0];
		}
		
		CurParms.IUVW = (CurParms.IU + CurParms.IV + CurParms.IW + CurParms.IU ) >> 2;
		
		CurParms.AccIU = (long) CurParms.PeakIU;
		CurParms.AccIV = (long) CurParms.PeakIV;
		CurParms.AccIW = (long) CurParms.PeakIW;
		VolParms.AccUin = (long) VolParms.PeakUin;
		MeauParm.MainMeauAcc = (long) MeauParm.MainMeauPeak;
		MeauParm.BackupMeauAcc = (long) MeauParm.BackupMeauPeak;
		
		CarDescend();
	}else
	{
		CurParms.AccIU = (long) CurParms.AccIU + CurParms.PeakIU;
		CurParms.AccIV = (long) CurParms.AccIV + CurParms.PeakIV;
		CurParms.AccIW = (long) CurParms.AccIW + CurParms.PeakIW;
		VolParms.AccUin = (long) VolParms.AccUin + VolParms.PeakUin;
		MeauParm.MainMeauAcc = (long) MeauParm.MainMeauAcc + MeauParm.MainMeauPeak;
		MeauParm.BackupMeauAcc = (long) MeauParm.BackupMeauAcc + MeauParm.BackupMeauPeak;
		
	}

	IFS0bits.ADIF = 0;   //清AD中断标志位
    return;    
	
}


void CarDescend(void)
{
	if(StartState.PreStart == 1)
	{
		if(StartState.RoadRun == 0)
		{
			if(CurParms.IU < CurParms.AgoIU)
			{
				CurParms.CarDescendTimesIU = CurParms.CarDescendTimesIU + 1;
				if(CurParms.CarDescendTimesIU > 5)
				{
					CurParms.LessCarIUVW = CurParms.LessCarIUVW | 0x0001;
					CurParms.CarDescendTimesIU = 0;
				}
					
			}else if(CurParms.IU > CurParms.AgoIU)
			{
				CurParms.CarUpTimesIU = CurParms.CarUpTimesIU + 1;
				if(CurParms.CarUpTimesIU > 10)
				{
					StartState.UpCarIU = 1;
					CurParms.CarDescendTimesIU = 0;
				}
			}
			
			CurParms.AgoIU = CurParms.IU;
			
			if(CurParms.IU > CurParms.MaxIU)
			{
				CurParms.MaxIU = CurParms.IU;
			}else if(CurParms.IU < CurParms.MaxIU)
			{
				if(StartState.UpCarIU == 1)
				{
					AX_int_AD = CurParms.MaxIU >> 1;
					if(CurParms.IU < AX_int_AD)
					{
						CurParms.LessCarIUVW = CurParms.LessCarIUVW | 0x0001;
					}else if(CurParms.IU < SysParms.RateCur)
					{
						CurParms.LessCarIUVW = CurParms.LessCarIUVW | 0x0001;
					}
				}
			}
			
			if(CurParms.IV < CurParms.AgoIV)
			{
				CurParms.CarDescendTimesIV = CurParms.CarDescendTimesIV + 1;
				if(CurParms.CarDescendTimesIV > 5)
				{
					CurParms.LessCarIUVW = CurParms.LessCarIUVW | 0x0002;
					CurParms.CarDescendTimesIV = 0;
				}
					
			}else if(CurParms.IV > CurParms.AgoIV)
			{
				CurParms.CarUpTimesIV = CurParms.CarUpTimesIV + 1;
				if(CurParms.CarUpTimesIV > 10)
				{
					StartState.UpCarIV = 1;
					CurParms.CarDescendTimesIV = 0;
				}
			}
			
			CurParms.AgoIV = CurParms.IV;
			
			if(CurParms.IV > CurParms.MaxIV)
			{
				CurParms.MaxIV = CurParms.IV;
			}else if(CurParms.IV < CurParms.MaxIV)
			{
				if(StartState.UpCarIV == 1)
				{
					AX_int_AD = CurParms.MaxIV >> 1;
					if(CurParms.IV < AX_int_AD)
					{
						CurParms.LessCarIUVW = CurParms.LessCarIUVW | 0x0002;
					}else if(CurParms.IV < SysParms.RateCur)
					{
						CurParms.LessCarIUVW = CurParms.LessCarIUVW | 0x0001;
					}
				}
			}
			
			if(CurParms.IW < CurParms.AgoIW)
			{
				CurParms.CarDescendTimesIW = CurParms.CarDescendTimesIW + 1;
				if(CurParms.CarDescendTimesIW > 5)
				{
					CurParms.LessCarIUVW = CurParms.LessCarIUVW | 0x0004;
					CurParms.CarDescendTimesIW = 0;
				}
					
			}else if(CurParms.IW > CurParms.AgoIW)
			{
				CurParms.CarUpTimesIW = CurParms.CarUpTimesIW + 1;
				if(CurParms.CarUpTimesIW > 10)
				{
					StartState.UpCarIW = 1;
					CurParms.CarDescendTimesIW = 0;
				}
			}
			
			CurParms.AgoIW = CurParms.IW;
			
			if(CurParms.IW > CurParms.MaxIW)
			{
				CurParms.MaxIW = CurParms.IW;
			}else if(CurParms.IW < CurParms.MaxIW)
			{
				if(StartState.UpCarIW == 1)
				{
					AX_int_AD = CurParms.MaxIW >> 1;
					if(CurParms.IW < AX_int_AD)
					{
						CurParms.LessCarIUVW = CurParms.LessCarIUVW | 0x0004;
					}else if(CurParms.IW < SysParms.RateCur)
					{
						CurParms.LessCarIUVW = CurParms.LessCarIUVW | 0x0001;
					}
				}
			}
			
			if(CurParms.LessCarIUVW == 7)
				StartState.LessCar = 1;
		}				
	}
}
