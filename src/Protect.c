//海吉科技，HJR3000型智能软启动控制装置，DSPIC30F6010A系统
//过流保护功能处理，CurrProtect.c

//头文件
#include "UserParms.h"	//用户系统配置，常数定义及配置值
#include "Function.h"	//系统外部调用函数声明，内部调用函数在对应文件内声明
#include "variable.h"	//系统全局变量声明，局部变量在对应文件内声明

void IOCorp(void);		//IO口状态处理
int AX_int_Protect = 0, BX_int_Protect = 0;
long AX_long_Protect = 0, BX_long_Protect = 0;

//PWM故障中断
void __attribute__((__interrupt__)) _FLTAInterrupt(void)
{
	if(StartState.PreStart == 1)
	{
		++ PWMParams.FLTA_Js;
		if(PWMParams.FLTA_Js >= ErrorParm.ConnectCurTime)
		{
			PWMParams.FLTA_Js = 0;
			StopPWM();
			ErrorParm.InitError = ErrorParm.InitError | 0x8000;
			IEC2bits.FLTAIE = 0;    //使能FLTA故障中断

		}else
		{
			IFS2bits.FLTAIF = 0;   //只清除一次过流故障中断 
		}
	}else IFS2bits.FLTAIF = 0;   //只清除一次过流故障中断 
	
	return; 
}

void CurProtect(void)
{
	if(MainState.DisconTime == 1)
	{
		MainState.DisconTime = 0;
		
		ErrorParm.DisconEnumerateU = ErrorParm.DisconEnumerateU + 1;
		if(ErrorParm.DisconEnumerateU > ErrorParm.DisconTime)
		{
			ErrorParm.InitError = ErrorParm.InitError | 0x1000;
			ErrorParm.DisconEnumerateU = 2500;
		}
			
		ErrorParm.DisconEnumerateV = ErrorParm.DisconEnumerateV + 1;
		if(ErrorParm.DisconEnumerateV > ErrorParm.DisconTime)
		{
			ErrorParm.InitError = ErrorParm.InitError | 0x2000;
			ErrorParm.DisconEnumerateV = 2500;
		}
		
		ErrorParm.DisconEnumerateW = ErrorParm.DisconEnumerateW + 1;
		if(ErrorParm.DisconEnumerateW > ErrorParm.DisconTime)
		{
			ErrorParm.InitError = ErrorParm.InitError | 0x4000;
			ErrorParm.DisconEnumerateW = 2500;
		}
				
		ErrorParm.DisconEnumerateUV = ErrorParm.DisconEnumerateUV + 1;
		if(ErrorParm.DisconEnumerateUV > ErrorParm.DisconTime)
		{
			ErrorParm.InitError = ErrorParm.InitError | 0x1000;
			ErrorParm.DisconEnumerateUV = 2500;
		}else
		{
			ErrorParm.InitError = ErrorParm.InitError & 0xEFFF;
		}
		
		ErrorParm.DisconEnumerateVW = ErrorParm.DisconEnumerateVW + 1;
		if(ErrorParm.DisconEnumerateVW > ErrorParm.DisconTime)
		{
			ErrorParm.InitError = ErrorParm.InitError | 0x2000;
			ErrorParm.DisconEnumerateVW = 2500;
		}else
		{
			ErrorParm.InitError = ErrorParm.InitError & 0xDFFF;
		}
		
		ErrorParm.DisconEnumerateWU = ErrorParm.DisconEnumerateWU + 1;
		if(ErrorParm.DisconEnumerateWU > ErrorParm.DisconTime)
		{
			ErrorParm.InitError = ErrorParm.InitError | 0x4000;
			ErrorParm.DisconEnumerateWU = 2500;
		}else
		{
			ErrorParm.InitError = ErrorParm.InitError & 0xBFFF;
		}

		
		if(InsideIOState.ComponentHot == 0)
		{
			ErrorParm.HotCompEnumerate = ErrorParm.HotCompEnumerate + 1;
			if(ErrorParm.HotCompEnumerate > ErrorParm.HotCommTime)
			{
				ErrorParm.InitError = ErrorParm.InitError | 0x0001;
				ErrorParm.HotCompEnumerate = 0;
			}
		}else
		{
			ErrorParm.HotCompOnEnumerate = ErrorParm.HotCompOnEnumerate + 1;
			if(ErrorParm.HotCompOnEnumerate > 10000)
			{
				ErrorParm.InitError = ErrorParm.InitError & 0xFFFE;
				ErrorParm.HotCompOnEnumerate = 0;
			}
		}
	
	}
	
	if(MainState.Cur == 1)
	{
	 	MainState.Cur = 0;
		
		if((StartState.RoadRun == 1) || (StartState.BenJiRun == 1))
		{
			if(CurParms.IUVW > CurParms.OverCur)
			{
				CurParms.OverCurEnumerate = CurParms.OverCurEnumerate + 1;
				if(CurParms.OverCurEnumerate > CurParms.OverCurTime)
					ErrorParm.InitError = ErrorParm.InitError | 0x0002;
			}else
			{
				CurParms.OverCurEnumerate = 0;
			}
		
			if(CurParms.IUVW > CurParms.UnLimitCur)
			{
				AX_int_Protect = CurParms.IUVW - CurParms.UnLimitCur;
				CurParms.UnLimitTimeCurEnumerate = CurParms.UnLimitTimeCurEnumerate + AX_int_Protect;
				AX_int_Protect = CurParms.UnLimitTimeCurEnumerate >> 8;
				if(AX_int_Protect > CurParms.UnLimitTimeCur)
					ErrorParm.InitError = ErrorParm.InitError | 0x0008;
			}else
			{
				CurParms.UnLimitTimeCurEnumerate = 0;
			}
			if(StartState.SoftStop == 0)
			{
				if(CurParms.IUVW < CurParms.LowCur)
				{
					CurParms.LowCurEnumerate = CurParms.LowCurEnumerate + 1;
					if(CurParms.LowCurEnumerate > CurParms.LowCurTime)
						ErrorParm.InitError = ErrorParm.InitError | 0x0004;
				}else
				{
					CurParms.LowCurEnumerate = 0;
				}
			}
		}
			
		if(StartState.PreStart == 1)
		{
			AX_int_Protect = CurParms.IU - CurParms.IV;
			if(AX_int_Protect < 0)
				AX_int_Protect = - AX_int_Protect;
			if(AX_int_Protect > CurParms.UnbalanceCur)
			{
				CurParms.UnbalanceCurEnumerate = CurParms.UnbalanceCurEnumerate + 1;
				if(CurParms.UnbalanceCurEnumerate > CurParms.UnbalanceCurTime)
					ErrorParm.InitError = ErrorParm.InitError | 0x0010;
			}else
			{
				AX_int_Protect = CurParms.IV - CurParms.IW;
				if(AX_int_Protect < 0)
					AX_int_Protect = - AX_int_Protect;
				if(AX_int_Protect > CurParms.UnbalanceCur)
				{
					CurParms.UnbalanceCurEnumerate = CurParms.UnbalanceCurEnumerate + 1;
					if(CurParms.UnbalanceCurEnumerate > CurParms.UnbalanceCurTime)
						ErrorParm.InitError = ErrorParm.InitError | 0x0010;
				}else
				{
					AX_int_Protect = CurParms.IW - CurParms.IU;
					if(AX_int_Protect < 0)
						AX_int_Protect = - AX_int_Protect;
					if(AX_int_Protect > CurParms.UnbalanceCur)
					{
						CurParms.UnbalanceCurEnumerate = CurParms.UnbalanceCurEnumerate + 1;
						if(CurParms.UnbalanceCurEnumerate > CurParms.UnbalanceCurTime)
							ErrorParm.InitError = ErrorParm.InitError | 0x0010;
					}else
					{
						CurParms.UnbalanceCurEnumerate = 0;
					}
				}
			}
		}
		
		if(VolParms.Uin < VolParms.LowVol)
		{
			VolParms.HighVolEnumerate = 0;
			VolParms.LowVolEnumerate = VolParms.LowVolEnumerate + 1;
			if(VolParms.LowVolEnumerate > VolParms.LowVolTime)
			{
				ErrorParm.InitError = ErrorParm.InitError | 0x0040;
				
			}
		}else if(VolParms.Uin > VolParms.HighVol)
		{
			VolParms.LowVolEnumerate = 0;
			VolParms.HighVolEnumerate = VolParms.HighVolEnumerate + 1;
			if(VolParms.HighVolEnumerate > VolParms.HighVolTime)
			{
				ErrorParm.InitError = ErrorParm.InitError | 0x0020;
				
			}
		}else
		{
			VolParms.HighVolEnumerate = 0;
			VolParms.LowVolEnumerate = 0;
			ErrorParm.InitError = ErrorParm.InitError & 0xFFBF;
			ErrorParm.InitError = ErrorParm.InitError & 0xFFDF;
		}
	}
	
	 
	ErrorParm.EndError = ErrorParm.InitError & ErrorParm.PassError;
	if(ErrorParm.EndError != 0)
	{
		OutputState.Error = 1;
		if(StartState.PreStart == 1)
		{
			StopPWM();
			InsideIOState.ByPassOut = 1;
			StartState.PreStart = 0;
			StartState.RoadRun = 0;
		}	
		RunState.PreRun = 0;
		if(AutoRunParm.RunNumber == 0)
		{
			Uart1Parm.RunNumber = Uart1Parm.Addr + 1;
			if(Uart1Parm.RunNumber > Uart1Parm.AddrMax)
				Uart1Parm.RunNumber = 0;
			Uart1State.Change = 1;
		}
			
		
	}else
	{
		OutputState.Error = 0;
		ErrorParm.AgoEndError = ErrorParm.EndError;
		ErrorParm.TimeEnumerate = 0;
	}
	
	if(StartState.PreStart == 0)
	{
		if(InsideIOState.Stop == 1)
		{
			ErrorParm.EndError = 0;
			ErrorParm.InitError = 0;
			ErrorParm.ErrorTimes = 0;
		}
	}	
		
	
	if(ErrorParm.EndError == 0)
		ErrorParm.AgoEndError = ErrorParm.EndError;
		
	if(ErrorParm.EndError != ErrorParm.AgoEndError)
	{
		for(AX_int_Protect = 15; AX_int_Protect > 0; AX_int_Protect -- )
		{
			BX_int_Protect = AX_int_Protect - 1;
			ErrorParm.EndErrorSave[AX_int_Protect] = ErrorParm.EndErrorSave[BX_int_Protect];
			ErrorParm.ErrorSaveState[AX_int_Protect] = ErrorParm.ErrorSaveState[BX_int_Protect];
			ErrorParm.ErrorSaveMainMeau[AX_int_Protect] = ErrorParm.ErrorSaveMainMeau[BX_int_Protect];
			ErrorParm.ErrorSaveBackupMeau[AX_int_Protect] = ErrorParm.ErrorSaveBackupMeau[BX_int_Protect];
			ErrorParm.ErrorSaveIUVW[AX_int_Protect] = ErrorParm.ErrorSaveIUVW[BX_int_Protect];
			ErrorParm.ErrorSaveUin[AX_int_Protect] = ErrorParm.ErrorSaveUin[BX_int_Protect];
		}
		ErrorParm.EndErrorSave[0] = ErrorParm.EndError;
		ErrorParm.ErrorSaveState[0] = AutoRunParm.OutputState;
		ErrorParm.ErrorSaveMainMeau[0] = MeauParm.MainMeau;
		ErrorParm.ErrorSaveBackupMeau[0] = MeauParm.BackupMeau;
		ErrorParm.ErrorSaveIUVW[0] = CurParms.IUVW;
		ErrorParm.ErrorSaveUin[0] = VolParms.Uin;
		
		for(AX_int_Protect = 0;AX_int_Protect < 16;AX_int_Protect ++ )
		{
			EEPROMADDR = 0xF000 + 2 * AX_int_Protect + 256;
        	EraseEE(__builtin_tblpage(&EPEndErrorSave[0]),EEPROMADDR, WORD);
        	WriteEE(&ErrorParm.EndErrorSave[AX_int_Protect],__builtin_tblpage(&EPEndErrorSave[0]),EEPROMADDR, WORD);
        	
        	EEPROMADDR = 0xF000 + 2 * AX_int_Protect + 288;
        	EraseEE(__builtin_tblpage(&EPErrorSaveState[0]),EEPROMADDR, WORD);
        	WriteEE(&ErrorParm.ErrorSaveState[AX_int_Protect],__builtin_tblpage(&EPErrorSaveState[0]),EEPROMADDR, WORD);
        	        	
        	EEPROMADDR = 0xF000 + 2 * AX_int_Protect + 320;
        	EraseEE(__builtin_tblpage(&EPErrorSaveMainMeau[0]),EEPROMADDR, WORD);
        	WriteEE(&ErrorParm.ErrorSaveMainMeau[AX_int_Protect],__builtin_tblpage(&EPErrorSaveMainMeau[0]),EEPROMADDR, WORD);
        	
        	EEPROMADDR = 0xF000 + 2 * AX_int_Protect + 352;
        	EraseEE(__builtin_tblpage(&EPErrorSaveBackupMeau[0]),EEPROMADDR, WORD);
        	WriteEE(&ErrorParm.ErrorSaveBackupMeau[AX_int_Protect],__builtin_tblpage(&EPErrorSaveBackupMeau[0]),EEPROMADDR, WORD);
        	
        	EEPROMADDR = 0xF000 + 2 * AX_int_Protect + 384;
        	EraseEE(__builtin_tblpage(&EPErrorSaveIUVW[0]),EEPROMADDR, WORD);
        	WriteEE(&ErrorParm.ErrorSaveIUVW[AX_int_Protect],__builtin_tblpage(&EPErrorSaveIUVW[0]),EEPROMADDR, WORD);
        	
        	EEPROMADDR = 0xF000 + 2 * AX_int_Protect + 416;
        	EraseEE(__builtin_tblpage(&EPErrorSaveUin[0]),EEPROMADDR, WORD);
        	WriteEE(&ErrorParm.ErrorSaveUin[AX_int_Protect],__builtin_tblpage(&EPErrorSaveUin[0]),EEPROMADDR, WORD);
        	
		}
		ErrorParm.AgoEndError = ErrorParm.EndError;
	}
	
}
