//海吉科技，HJR3000型智能软启动控制装置，DSPIC30F6010A系统
//主控制文件，T1_CTRL.c

//头文件
#include "UserParms.h"	//用户系统配置，常数定义及配置值
#include "Function.h"	//系统外部调用函数声明，内部调用函数在对应文件内声明
#include "variable.h"	//系统全局变量声明，局部变量在对应文件内声明


void SoftRun(void);
void SoftStop(void);

int AX_int_T1 = 0;
long AX_long_T1 = 0;

//**********T1中断服务程序*************//
void __attribute__((__interrupt__)) _T1Interrupt(void)
{
		
	MainState.T1Main = 1;
	
	MainParm.T1Times = MainParm.T1Times + 1;
	if(MainParm.T1Times > 3)
	{
		MainParm.T1Times = 0;
		MainState.DisconTime = 1;
		MainState.I2CTrn = 0;
		MainState.TrnData = 1;
		MainState.T1Five = 1;
	}
	
    IFS0bits.T1IF=0;				//clear interrupt flag//
    return;
}    
 
 
void MainCtrl(void)
{
	if(StartState.RoadRun == 0)
	{
		if(StartState.PreStart == 0)
		{
			if(RunState.Run == 1)
			{
				InsideIOState.ByPassOut = 1;
				StartState.PreStart = 1;	
				if(KeyParm.StartMode == 3 )
				{
					InsideIOState.ByPassOut = 0;
					
				}else if(KeyParm.StartMode == 2 )
				{
					SoftRunParms.Data = SoftRunParms.JumpStartData;
					AX_int_T1 = (long) SoftRunParms.Data / dqDataGei;
					if(AX_int_T1 < OutDataMin)
						AX_int_T1 = OutDataMin;
					SoftRunParms.OutData = AX_int_T1;
					StarPWM();
				}else
				{
					SoftRunParms.Data = SoftRunParms.StartData;
					AX_int_T1 = (long) SoftRunParms.Data / dqDataGei;
					if(AX_int_T1 < OutDataMin)
						AX_int_T1 = OutDataMin;
					SoftRunParms.OutData = AX_int_T1;
					StarPWM();
				}
			}else if(SysTestState.SysTest == 0)
			{
				StopPWM();
				InsideIOState.ByPassOut = 1;
				StartState.PreStart = 0;
			}					
		}else if(RunState.Run == 1)
		{
			if(StartState.SoftStop == 0)
			{
				if(InputState.Stop == 1)
				{
					StopPWM();
					InsideIOState.ByPassOut = 1;
					StartState.PreStart = 0;
				}else
				{
					SoftRun();
				}
			}else
			{
				SoftStop();
			}
		}else
		{
			if(StartState.SoftStartEnd == 1)
			{
				if(InputState.Stop == 1)
				{
					StopPWM();
					InsideIOState.ByPassOut = 1;
					StartState.PreStart = 0;
				}else
				{
					StartState.SoftStop = 1;
					SoftStop();
				}
			}else
			{
				StopPWM();
				InsideIOState.ByPassOut = 1;
				StartState.PreStart = 0;
			}
		}				
				
	}else
	{
		if(StartState.SoftStop == 0)
		{
			if(RunState.Run == 1)
			{
				if(InputState.Stop == 1)
				{
					StopPWM();
					InsideIOState.ByPassOut = 1;
					StartState.PreStart = 0;
					StartState.RoadRun = 0;
				}else
				{
					InsideIOState.ByPassOut = 0;
					if(InsideIOState.ByPassIn == 0)
					{
						ErrorParm.InitError = ErrorParm.InitError | 0x0080;
						StopPWM();
						InsideIOState.ByPassOut = 1;
						StartState.PreStart = 0;
						StartState.RoadRun = 0;
					}
				}
				
			}else
			{
				if(InsideIOState.ByPassIn == 1)
					SoftStop();
				else
				{
					ErrorParm.InitError = ErrorParm.InitError | 0x0080;
					StopPWM();
					InsideIOState.ByPassOut = 1;
					StartState.PreStart = 0;
					StartState.RoadRun = 0;
				}
			}
		}else
		{
			if(InputState.Stop == 0)
			{
				SoftStop();
			}else
			{
				StopPWM();
				InsideIOState.ByPassOut = 1;
				StartState.PreStart = 0;
				StartState.RoadRun = 0;
			}
		}
	}
}
 
void StarPWM(void)
{
	
	OVDCON = 0x0000;
	PWMParams.OnPWM = ActiveLongPWM;
	PWMParams.StartOut = 0;
	PwmState.StartOut = 0;
	PwmState.UoutPhyH = 0;
	PwmState.UoutPhyL = 0;
	PwmState.VoutPhyH = 0;
	PwmState.VoutPhyL = 0;
	PwmState.WoutPhyH = 0;
	PwmState.WoutPhyL = 0;
	PwmState.UoutH = 0;
	PwmState.UoutL = 0;
	PwmState.VoutH = 0;
	PwmState.VoutL = 0;
	PwmState.WoutH = 0;
	PwmState.WoutL = 0;
	PWMParams.Duty1H = 0;
	PWMParams.Duty1L = 0;
	PWMParams.Duty2H = 0;
	PWMParams.Duty2L = 0;
	PWMParams.Duty3H = 0;
	PWMParams.Duty3L = 0;
	PWMParams.Delay1H = 0;
	PWMParams.Delay1L = 0;
	PWMParams.Delay2H = 0;
	PWMParams.Delay2L = 0;
	PWMParams.Delay3H = 0;
	PWMParams.Delay3L = 0;
	SoftRunParms.RunTime = 0;
	SoftRunParms.EndTime = 0;
	StartState.SoftStopEnd = 0;
	StartState.SoftStopStartEnd = 0;
	StartState.SoftRunEnd = 0;
	StartState.SoftStartEnd = 0;
	SoftRunParms.LimitCarTimes = 0;
	CurParms.MaxIU = 0;
	CurParms.CarDescendTimesIU = 0;
	CurParms.CarUpTimesIU = 0;
	StartState.UpCarIU = 0;
	CurParms.MaxIV = 0;
	CurParms.CarDescendTimesIV = 0;
	CurParms.CarUpTimesIV = 0;
	StartState.UpCarIV = 0;
	CurParms.MaxIW = 0;
	CurParms.CarDescendTimesIW = 0;
	CurParms.CarUpTimesIW = 0;
	StartState.UpCarIW = 0;
	StartState.LessCar = 0;
	CurParms.LessCarIUVW = 0;
	SoftRunParms.JumpRunTimes = 0;
	StartState.JumpRun = 0;
	StartState.BenJiRun = 0;
	StartState.ShaChe = 0;
	PTCON = 0x8000;
   	OVDCON = 0x0000;
}

void StopPWM(void)
{
	OVDCON = 0x0000;
	PTCON = 0x0000;
	StartState.SoftStop = 0;
	SoftRunParms.RunTime = 0;
	SoftRunParms.EndTime = 0;
	StartState.SoftStopEnd = 0;
	StartState.SoftStopStartEnd = 0;
	SoftRunParms.JumpRunTimes = 0;
	StartState.JumpRun = 0;
	StartState.BenJiRun = 0;
	StartState.ShaChe = 0;
	PWMParams.OnPWM = ActiveLongPWM;
	
}


void SoftRun(void)
{
	switch(KeyParm.StartMode)
    {
		case 0:
			if(StartState.SoftRunEnd == 1)
			{
				if(InsideIOState.ByPassIn == 1)
				{
					InsideIOState.ByPassOut = 0;
					SoftRunParms.EndTime = SoftRunParms.EndTime + 1;
					if(SoftRunParms.EndTime > 200)
					{
						StartState.RoadRun = 1;
						SoftRunParms.EndTime = 0;
						StopPWM();
					}else
					{
						SoftRunParms.OutData = OutDataMin;
					}
				
				}else
				{
					InsideIOState.ByPassOut = 0;
					SoftRunParms.OutData = OutDataMin;
					SoftRunParms.EndTime = SoftRunParms.EndTime + 1;
					if(SoftRunParms.EndTime > 10000)
					{
						ErrorParm.InitError = ErrorParm.InitError | 0x0080;
						StopPWM();
						InsideIOState.ByPassOut = 1;
						StartState.PreStart = 0;
						StartState.RoadRun = 0;
					}
				}
			}else if(StartState.SoftStartEnd == 1)
			{
				SoftRunParms.OutData = OutDataMin;
				if(KeyParm.RunMode == 0)
				{
					SoftRunParms.RunTime = SoftRunParms.RunTime + 1;
					if(SoftRunParms.RunTime > 500)
					{
						InsideIOState.ByPassOut = 0;
						StartState.SoftRunEnd = 1;
						SoftRunParms.EndTime = 0;
						SoftRunParms.RunTime = 0;
					}				
				}else
				{
					StartState.BenJiRun = 1;
				}
			}else
			{
				SoftRunParms.Data = (long) SoftRunParms.Data - SoftRunParms.LoopData;
				if(SoftRunParms.Data < DataMin )
				{
					SoftRunParms.Data = DataMin;
					StartState.SoftStartEnd = 1;
					SoftRunParms.RunTime = 0;
				}
				if(StartState.LessCar == 1)
				{
					SoftRunParms.Data = 1;
					StartState.SoftStartEnd = 1;
					SoftRunParms.RunTime = 0;
					StartState.LessCar = 0;
				}
				AX_int_T1 = (long) SoftRunParms.Data / dqDataGei;
				if(AX_int_T1 < OutDataMin)
					AX_int_T1 = OutDataMin;
				SoftRunParms.OutData = AX_int_T1;
			}
			
			break;
		case 1:
			if(StartState.SoftRunEnd == 1)
			{
				if(InsideIOState.ByPassIn == 1)
				{
					InsideIOState.ByPassOut = 0;
					SoftRunParms.EndTime = SoftRunParms.EndTime + 1;
					if(SoftRunParms.EndTime > 200)
					{
						StartState.RoadRun = 1;
						SoftRunParms.EndTime = 0;
						StopPWM();
					}else
					{
						SoftRunParms.OutData = OutDataMin;
					}
					
				}else
				{
					InsideIOState.ByPassOut = 0;
					SoftRunParms.OutData = OutDataMin;
					SoftRunParms.EndTime = SoftRunParms.EndTime + 1;
					if(SoftRunParms.EndTime > 10000)
					{
						ErrorParm.InitError = ErrorParm.InitError | 0x0080;
						StopPWM();
						InsideIOState.ByPassOut = 1;
						StartState.PreStart = 0;
						StartState.RoadRun = 0;
					}
				}
			}else if(StartState.SoftStartEnd == 1)
			{
				SoftRunParms.OutData = OutDataMin;
				if(KeyParm.RunMode == 0)
				{
					SoftRunParms.RunTime = SoftRunParms.RunTime + 1;
					if(SoftRunParms.RunTime > 500)
					{
						InsideIOState.ByPassOut = 0;
						StartState.SoftRunEnd = 1;
						SoftRunParms.EndTime = 0;
						SoftRunParms.RunTime = 0;
					}				
				}else
				{
					StartState.BenJiRun = 1;
				}
			}else
			{
				if(CurParms.IUVW < SoftRunParms.LimitCar)
				{
					SoftRunParms.Data = (long) SoftRunParms.Data - SoftRunParms.LoopData;
					if(SoftRunParms.Data < DataMin)
					{
						SoftRunParms.Data = DataMin;
						StartState.SoftStartEnd = 1;
						SoftRunParms.RunTime = 0;
					}else if(StartState.LessCar == 1)
					{
						SoftRunParms.Data = 1;
						StartState.SoftStartEnd = 1;
						SoftRunParms.RunTime = 0;
						StartState.LessCar = 0;
					}
				}else
				{
					if(StartState.LessCar == 1)
					{
						SoftRunParms.Data = 1;
						StartState.SoftStartEnd = 1;
						SoftRunParms.RunTime = 0;
					}else
					{
						SoftRunParms.LimitCarTimes = SoftRunParms.LimitCarTimes + 1;
						AX_int_T1 = SoftRunParms.LimitCarTimes >> 8;
						if(AX_int_T1 > 30)
						{
							StopPWM();
							InsideIOState.ByPassOut = 1;
							StartState.PreStart = 0;
							SoftRunParms.LimitCarTimes = 0;
						}
						
					}
				}
				AX_int_T1 = (long) SoftRunParms.Data / dqDataGei;
				if(AX_int_T1 < OutDataMin)
					AX_int_T1 = OutDataMin;
				SoftRunParms.OutData = AX_int_T1;
			}
			break;
		
		case 2:
        	if(StartState.SoftRunEnd == 1)
			{
				if(InsideIOState.ByPassIn == 1)
				{
					InsideIOState.ByPassOut = 0;
					SoftRunParms.EndTime = SoftRunParms.EndTime + 1;
					if(SoftRunParms.EndTime > 200)
					{
						StartState.RoadRun = 1;
						SoftRunParms.EndTime = 0;
						StopPWM();
					}else
					{
						SoftRunParms.OutData = OutDataMin;
					}
				}else
				{
					InsideIOState.ByPassOut = 0;
					SoftRunParms.OutData = OutDataMin;
					SoftRunParms.EndTime = SoftRunParms.EndTime + 1;
					if(SoftRunParms.EndTime > 10000)
					{
						ErrorParm.InitError = ErrorParm.InitError | 0x0080;
						StopPWM();
						InsideIOState.ByPassOut = 1;
						StartState.PreStart = 0;
						StartState.RoadRun = 0;
					}
				}
			}else if(StartState.SoftStartEnd == 1)
			{
				SoftRunParms.OutData = OutDataMin;
				if(KeyParm.RunMode == 0)
				{
					SoftRunParms.RunTime = SoftRunParms.RunTime + 1;
					if(SoftRunParms.RunTime > 500)
					{
						InsideIOState.ByPassOut = 0;
						StartState.SoftRunEnd = 1;
						SoftRunParms.EndTime = 0;
						SoftRunParms.RunTime = 0;
					}				
				}else
				{
					StartState.BenJiRun = 1;
				}
			}else
			{
				if(StartState.JumpRun == 1)
				{
					SoftRunParms.Data = (long) SoftRunParms.Data - SoftRunParms.LoopData;
					if(SoftRunParms.Data < DataMin)
					{
						SoftRunParms.Data = DataMin;
						StartState.SoftStartEnd = 1;
						SoftRunParms.RunTime = 0;
					}else if(StartState.LessCar == 1)
					{
						SoftRunParms.Data = 1;
						StartState.SoftStartEnd = 1;
						SoftRunParms.RunTime = 0;
						StartState.LessCar = 0;
					}
					AX_int_T1 = (long) SoftRunParms.Data / dqDataGei;
					if(AX_int_T1 < OutDataMin)
						AX_int_T1 = OutDataMin;
					SoftRunParms.OutData = AX_int_T1;
										
				}else
				{
					if(StartState.LessCar == 1)
					{
						SoftRunParms.Data = 1;
						StartState.SoftStartEnd = 1;
						SoftRunParms.RunTime = 0;
					}else
					{
						SoftRunParms.JumpRunTimes = SoftRunParms.JumpRunTimes + 1;
						if(SoftRunParms.JumpRunTimes > SoftRunParms.JumpLoopData)
						{
							StartState.JumpRun = 1;
							SoftRunParms.Data = SoftRunParms.JumpStartData;
							SoftRunParms.JumpRunTimes = 0;
						}
					}
					AX_int_T1 = (long) SoftRunParms.JumpStartData / dqDataGei;
					if(AX_int_T1 < OutDataMin)
						AX_int_T1 = OutDataMin;
					SoftRunParms.OutData = AX_int_T1;
					
				}
				
				
			}
			break;
		case 3:
        	InsideIOState.ByPassOut = 0;
        	if(InsideIOState.ByPassIn == 1)
			   	StartState.RoadRun = 1;
				
			break;
		default:
			StopPWM();
			InsideIOState.ByPassOut = 1;
			StartState.PreStart = 0;
			StartState.RoadRun = 0;
			StartState.SoftStop = 0;
			SoftRunParms.OutData = DataGeiMax;
			SoftRunParms.SoftStopEndTime = 0;
			break;	
	}
}


void SoftStop(void)
{
	if(KeyParm.StartMode == 3 )
	{
		StopPWM();
		InsideIOState.ByPassOut = 1;
		StartState.PreStart = 0;
		StartState.RoadRun = 0;
		StartState.SoftStop = 0;
		SoftRunParms.OutData = DataGeiMax;
		SoftRunParms.SoftStopEndTime = 0;
	}else if( ErrorParm.EndError != 0 )
	{
		StopPWM();
		InsideIOState.ByPassOut = 1;
		StartState.PreStart = 0;
		StartState.RoadRun = 0;
		StartState.SoftStop = 0;
		SoftRunParms.OutData = DataGeiMax;
		SoftRunParms.SoftStopEndTime = 0;
	}else
	{
		if(KeyParm.StopMode == 0)
		{
			if(StartState.SoftStop == 0)
			{
				if(InsideIOState.ByPassIn == 1)
				{
					StartState.SoftStop = 1;	
					SoftRunParms.Data = DataMax;
					SoftRunParms.OutData = OutDataMin;
					SoftRunParms.SoftStopRunTime = 0;
					SoftRunParms.SoftStopEndTime = 0;
					PwmState.StartOut = 1;
					StarPWM();
					
				}else
				{
					ErrorParm.InitError = ErrorParm.InitError | 0x0080;
					StopPWM();
					InsideIOState.ByPassOut = 1;
					StartState.PreStart = 0;
					StartState.RoadRun = 0;
					StartState.SoftStop = 0;
					SoftRunParms.OutData = DataGeiMax;
					SoftRunParms.SoftStopEndTime = 0;
				}
			}else
			{
				if(StartState.SoftStopEnd == 1)
				{
					SoftRunParms.SoftStopEndTime = SoftRunParms.SoftStopEndTime + 1;
					if( (long) SoftRunParms.SoftStopEndTime > 100)
					{
						StopPWM();
						InsideIOState.ByPassOut = 1;
						StartState.PreStart = 0;
						StartState.RoadRun = 0;
						StartState.SoftStop = 0;
						SoftRunParms.OutData = DataGeiMax;
						SoftRunParms.SoftStopEndTime = 0;
					}else
					{
						SoftRunParms.OutData = OutDataMin;
						
					}
					
					
					
				}else if(StartState.SoftStopStartEnd == 1)
				{
					if(InsideIOState.ByPassIn == 0)
					{
						InsideIOState.ByPassOut = 1;
						StartState.SoftStopEnd = 1;
						SoftRunParms.Data = SoftRunParms.SoftStopStartData;
						SoftRunParms.SoftStopEndTime = 0;
					}else
					{
						SoftRunParms.SoftStopEndTime = SoftRunParms.SoftStopEndTime + 1;
						if( (long) SoftRunParms.SoftStopEndTime > 10000)
						{
							ErrorParm.InitError = ErrorParm.InitError | 0x0080;
							StopPWM();
							InsideIOState.ByPassOut = 1;
							StartState.PreStart = 0;
							StartState.RoadRun = 0;
							StartState.SoftStop = 0;
							SoftRunParms.OutData = DataGeiMax;
							SoftRunParms.SoftStopEndTime = 0;
						}
					}
					SoftRunParms.OutData = OutDataMin;
					
				}else
				{
					SoftRunParms.SoftStopRunTime = SoftRunParms.SoftStopRunTime + 1;
					if( (long) SoftRunParms.SoftStopRunTime > 300)
					{
						InsideIOState.ByPassOut = 1;
						StartState.SoftStopStartEnd = 1;
						SoftRunParms.SoftStopEndTime = 0;
						SoftRunParms.SoftStopRunTime = 0;
					}
					SoftRunParms.OutData = OutDataMin;
					
					
				}
			}
		}else if(KeyParm.StopMode == 1)
		{
			if(StartState.SoftStop == 0)
			{
				if(InsideIOState.ByPassIn == 1)
				{
					StartState.SoftStop = 1;	
					SoftRunParms.Data = DataMax;
					SoftRunParms.OutData = OutDataMin;
					SoftRunParms.SoftStopRunTime = 0;
					SoftRunParms.SoftStopEndTime = 0;
					PwmState.StartOut = 1;
					StarPWM();
				}else
				{
					ErrorParm.InitError = ErrorParm.InitError | 0x0080;
					StopPWM();
					InsideIOState.ByPassOut = 1;
					StartState.PreStart = 0;
					StartState.RoadRun = 0;
					StartState.SoftStop = 0;
					SoftRunParms.OutData = DataGeiMax;
					SoftRunParms.SoftStopEndTime = 0;
				}
				
			}else
			{
				if(StartState.SoftStopEnd == 1)
				{
					SoftRunParms.Data = (long) SoftRunParms.Data + SoftRunParms.SoftStopLoopData;
					if(SoftRunParms.Data > SoftRunParms.SoftStopEndData )
					{
						StopPWM();
						InsideIOState.ByPassOut = 1;
						StartState.PreStart = 0;
						StartState.RoadRun = 0;
						StartState.SoftStop = 0;
						SoftRunParms.OutData = DataGeiMax;
					}else
					{
						AX_int_T1 = (long) SoftRunParms.Data / dqDataGei;
						if(AX_int_T1 < OutDataMin)
							AX_int_T1 = OutDataMin;
						SoftRunParms.OutData = AX_int_T1;
						
					}
					
					
					
				}else if(StartState.SoftStopStartEnd == 1)
				{
					if(InsideIOState.ByPassIn == 0)
					{
						InsideIOState.ByPassOut = 1;
						StartState.SoftStopEnd = 1;
						SoftRunParms.Data = SoftRunParms.SoftStopStartData;
						SoftRunParms.SoftStopEndTime = 0;
					}else
					{
						SoftRunParms.SoftStopEndTime = SoftRunParms.SoftStopEndTime + 1;
						if( (long) SoftRunParms.SoftStopEndTime > 10000)
						{
							ErrorParm.InitError = ErrorParm.InitError | 0x0080;
							StopPWM();
							InsideIOState.ByPassOut = 1;
							StartState.PreStart = 0;
							StartState.RoadRun = 0;
							StartState.SoftStop = 0;
							SoftRunParms.OutData = DataGeiMax;
							SoftRunParms.SoftStopEndTime = 0;
						}
					}
					SoftRunParms.OutData = OutDataMin;
					
				}else
				{
					SoftRunParms.SoftStopRunTime = SoftRunParms.SoftStopRunTime + 1;
					if( (long) SoftRunParms.SoftStopRunTime > 300)
					{
						InsideIOState.ByPassOut = 1;
						StartState.SoftStopStartEnd = 1;
						SoftRunParms.SoftStopEndTime = 0;
						SoftRunParms.SoftStopRunTime = 0;
					}
					SoftRunParms.OutData = OutDataMin;
				
					
				}
			}
		}else if(KeyParm.StopMode == 2)
		{
			if(StartState.SoftStop == 0)
			{
				if(InsideIOState.ByPassIn == 1)
				{
					StartState.SoftStop = 1;	
					SoftRunParms.Data = DataMax;
					SoftRunParms.OutData = OutDataMin;
					SoftRunParms.SoftStopRunTime = 0;
					SoftRunParms.SoftStopEndTime = 0;
					PwmState.StartOut = 1;
					StarPWM();
				}else
				{
					ErrorParm.InitError = ErrorParm.InitError | 0x0080;
					StopPWM();
					InsideIOState.ByPassOut = 1;
					StartState.PreStart = 0;
					StartState.RoadRun = 0;
					StartState.SoftStop = 0;
					SoftRunParms.OutData = DataGeiMax;
					SoftRunParms.SoftStopEndTime = 0;
				}
				
			}else
			{
				if(StartState.SoftStopEnd == 1)
				{
					SoftRunParms.Data = (long) SoftRunParms.Data + SoftRunParms.StopLoopData;
					if(SoftRunParms.Data > DataMax )
					{
						StopPWM();
						InsideIOState.ByPassOut = 1;
						StartState.PreStart = 0;
						StartState.RoadRun = 0;
						StartState.SoftStop = 0;
						SoftRunParms.OutData = DataGeiMax;
						StartState.ShaChe = 0;
					}else
					{
						SoftRunParms.OutData = SoftRunParms.StopEndData;
						StartState.ShaChe = 1;
					}
					
					
					
				}else if(StartState.SoftStopStartEnd == 1)
				{
					if(InsideIOState.ByPassIn == 0)
					{
						InsideIOState.ByPassOut = 1;
						StartState.SoftStopEnd = 1;
						SoftRunParms.Data = 0;
						SoftRunParms.SoftStopEndTime = 0;
					}else
					{
						SoftRunParms.SoftStopEndTime = SoftRunParms.SoftStopEndTime + 1;
						if( (long) SoftRunParms.SoftStopEndTime > 10000)
						{
							ErrorParm.InitError = ErrorParm.InitError | 0x0080;
							StopPWM();
							InsideIOState.ByPassOut = 1;
							StartState.PreStart = 0;
							StartState.RoadRun = 0;
							StartState.SoftStop = 0;
							SoftRunParms.OutData = DataGeiMax;
							SoftRunParms.SoftStopEndTime = 0;
						}
					}
					SoftRunParms.OutData = OutDataMin;
				}else
				{
					SoftRunParms.SoftStopRunTime = SoftRunParms.SoftStopRunTime + 1;
					if( (long) SoftRunParms.SoftStopRunTime > 300)
					{
						InsideIOState.ByPassOut = 1;
						StartState.SoftStopStartEnd = 1;
						SoftRunParms.SoftStopEndTime = 0;
						SoftRunParms.SoftStopRunTime = 0;
						StartState.ShaChe = 0;
					}
					SoftRunParms.OutData = OutDataMin;
					
				}
			}
		}else
		{
			StopPWM();
			InsideIOState.ByPassOut = 1;
			StartState.PreStart = 0;
			StartState.RoadRun = 0;
			StartState.SoftStop = 0;
			SoftRunParms.OutData = DataGeiMax;
			SoftRunParms.SoftStopEndTime = 0;
			
			
		}
	}
}
