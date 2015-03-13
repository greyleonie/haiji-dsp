//海吉科技，HJR3000型智能软启动控制装置，DSPIC30F6010A系统
//并联串行通讯程序 Uart1.c

//头文件
#include "UserParms.h"	//用户系统配置，常数定义及配置值
#include "Function.h"	//系统外部调用函数声明，内部调用函数在对应文件内声明
#include "variable.h"	//系统全局变量声明，局部变量在对应文件内声明

static int AX_int_AutoRun = 0;
static int BX_int_AutoRun = 0;
static int CX_int_AutoRun = 0;

void AutoRun(void)
{
	Uart1Parm.MainData[Uart1Parm.Addr] = MeauParm.MainMeauCom;
	Uart1Parm.BackupData[Uart1Parm.Addr] = MeauParm.BackupMeau;
	Uart1Parm.ErrorData[Uart1Parm.Addr] = ErrorParm.EndError;
	Uart1Parm.StateData[Uart1Parm.Addr] = AutoRunParm.OutputState;
	if(RunState.MainOpen == 0)
	{
		if(Uart1Parm.RxErrorEnumerate < 2000)
		{
			CX_int_AutoRun = MeauParm.MainMeauMax >> 4;
			AX_int_AutoRun = CX_int_AutoRun + MeauParm.MainMeauCom;
			BX_int_AutoRun = MeauParm.MainMeauCom - CX_int_AutoRun;
			if(BX_int_AutoRun < 0)
				BX_int_AutoRun = 0;
			
			if(Uart1Parm.AddrMax < 1)
				MeauParm.MainMeau = MeauParm.MainMeauCom;
			else if(Uart1Parm.AddrMax < 2)
			{
				PingJun0();
				PingJun1();
				MeauParm.MainMeau = MeauParm.MainMeau2;	
				
			}else if(Uart1Parm.AddrMax < 3)
			{
				PingJun0();
				PingJun1();
				PingJun2();
				MeauParm.MainMeau = MeauParm.MainMeau3;	
				
			}else if(Uart1Parm.AddrMax < 4)
			{	
				PingJun0();
				PingJun1();
				PingJun2();
				PingJun3();
				MeauParm.MainMeau = MeauParm.MainMeau4;	
				
			}else if(Uart1Parm.AddrMax < 5)
			{
				PingJun0();
				PingJun1();
				PingJun2();
				PingJun3();
				PingJun4();
				MeauParm.MainMeau = MeauParm.MainMeau5;	
				
			}else if(Uart1Parm.AddrMax < 6)
			{			
				PingJun0();
				PingJun1();
				PingJun2();
				PingJun3();
				PingJun4();
				PingJun5();
				MeauParm.MainMeau = MeauParm.MainMeau6;	
				
			}else if(Uart1Parm.AddrMax < 7)
			{
				PingJun0();
				PingJun1();
				PingJun2();
				PingJun3();
				PingJun4();
				PingJun5();
				PingJun6();
				MeauParm.MainMeau = MeauParm.MainMeau7;	
				
			}else if(Uart1Parm.AddrMax > 8)
			{	
				PingJun0();
				PingJun1();
				PingJun2();
				PingJun3();
				PingJun4();
				PingJun5();
				PingJun6();
				PingJun7();
				MeauParm.MainMeau = MeauParm.MainMeau8;	
				
			}else 
			{
				MeauParm.MainMeau = MeauParm.MainMeauCom;
			}
			
		}else
		{
			MeauParm.MainMeau = MeauParm.MainMeauCom;
		}
	}else
		MeauParm.MainMeau = MeauParm.MainMeauCom;
			
	if(OutputState.Stop == 1)
	{
		AutoRunParm.StopEnumerate = AutoRunParm.StopEnumerate + 1;
		if( (long) AutoRunParm.StopEnumerate > SoftRunParms.PrepareDelay)
			OutputState.Stop = 0;
	}else AutoRunParm.StopEnumerate = 0;
	
	if(OutputIO.StopFillGas == 1)
	{
		AutoRunParm.StopFillGasEnumerate = AutoRunParm.StopFillGasEnumerate + 1;
		if( (long) AutoRunParm.StopFillGasEnumerate > SoftRunParms.PrepareDelay)
			OutputIO.StopFillGas = 0;
	}else AutoRunParm.StopFillGasEnumerate = 0;
	
	if(AutoRunParm.ChangeTimes == AutoRunParm.ChangeEnumerate)
	{
		AutoRunParm.ChangeEnumerate = 0;
		Uart1Parm.RunNumber = Uart1Parm.RunNumber + 1;
		if(Uart1Parm.RunNumber > Uart1Parm.AddrMax)
			Uart1Parm.RunNumber = 0;
		Uart1State.Change = 1;
	}	
	if(Uart1Parm.RunNumber > Uart1Parm.AddrMax)
		Uart1Parm.RunNumber = 0;
		
	if(InputState.Stop == 1)
	{
		RunState.PreRun = 0;
		RunState.AutoRun = 0;
		ErrorParm.EndError = 0;
		ErrorParm.InitError = 0;
		OutputState.Men = 0;
		OutputState.Auto = 0;
		if(RunState.StopOff == 0)
		{
			RunState.StopOff = 1;
			OutputState.Stop = 1;
		}
		if(RunState.StopGasOff == 0)
		{
			OutputIO.StopFillGas = 1;
			RunState.StopGasOff = 1;
		}					
		AutoRunParm.OutputState = AutoRunParm.OutputState & 0xFFFC;
		AutoRunParm.OutputState = AutoRunParm.OutputState & 0xFFF3;	
	}
	
	if(RunState.MainOpen == 0)
	{
		if(MeauParm.MainMeau > AutoRunParm.OverHigh)
		{
			AutoRunParm.OutputState = AutoRunParm.OutputState | 0x0100;
			AutoRunParm.OutputState = AutoRunParm.OutputState | 0x8000;
			OutputState.OverHigh = 1;
		}else if( (AutoRunParm.OverHigh - MeauParm.MainMeau) > 4)
		{
			AutoRunParm.OutputState = AutoRunParm.OutputState & 0xFEFF;	
			if(OutputState.OverLow == 0)
				AutoRunParm.OutputState = AutoRunParm.OutputState & 0x7FFF;	
			OutputState.OverHigh = 0;
		}
		
		if(MeauParm.MainMeau < AutoRunParm.OverLow)
		{
			AutoRunParm.OutputState = AutoRunParm.OutputState | 0x0200;
			AutoRunParm.OutputState = AutoRunParm.OutputState | 0x8000;
			OutputState.OverLow = 1;
		}else if( (MeauParm.MainMeau - AutoRunParm.OverLow) > 4)
		{
			AutoRunParm.OutputState = AutoRunParm.OutputState & 0xFDFF;	
			if(OutputState.OverHigh == 0)
				AutoRunParm.OutputState = AutoRunParm.OutputState & 0x7FFF;	
			OutputState.OverLow = 0;
		}
		
		if(MeauParm.MainMeau > AutoRunParm.AboveHigh)
		{
			AutoRunParm.OutputState = AutoRunParm.OutputState | 0x0400;
			OutputState.AboveHigh = 1;
		}else if( (AutoRunParm.AboveHigh - MeauParm.MainMeau) > 4)
		{
			AutoRunParm.OutputState = AutoRunParm.OutputState & 0xFBFF;	
			OutputState.AboveHigh = 0;
		}
			
		if(MeauParm.MainMeau < AutoRunParm.AboveLow)
		{
			AutoRunParm.OutputState = AutoRunParm.OutputState | 0x0800;
			OutputState.AboveLow = 1;
		}else if( (MeauParm.MainMeau - AutoRunParm.AboveLow) > 4)
		{
			AutoRunParm.OutputState = AutoRunParm.OutputState & 0xF7FF;
			OutputState.AboveLow = 0;	
		}
	}else
	{
		AutoRunParm.OutputState = AutoRunParm.OutputState & 0xF0FF;		
		OutputState.AboveLow = 0;	
		OutputState.AboveHigh = 0;
		OutputState.OverLow = 0;
		OutputState.OverHigh = 0;
	}
	
	if(RunState.BackupOpen == 0)
		{
			if(MeauParm.BackupMeau > KeyParm.BackupMeauHigh)
			{
				if( (OutputState.OverHigh == 0) && (OutputState.OverLow == 0) )
					AutoRunParm.OutputState = AutoRunParm.OutputState | 0x0100;
				OutputIO.BackupMeauHigh = 1;
			}else if( (KeyParm.BackupMeauHigh - MeauParm.BackupMeau) > 4)
			{
				if(OutputState.OverHigh == 0)
					AutoRunParm.OutputState = AutoRunParm.OutputState & 0xFEFF;	
				OutputIO.BackupMeauHigh = 0;
			}
				
			if(MeauParm.BackupMeau < KeyParm.BackupMeauLow)
			{
				if( (OutputState.OverHigh == 0) && (OutputState.OverLow == 0) )
					AutoRunParm.OutputState = AutoRunParm.OutputState | 0x0200;
				OutputIO.BackupMeauLow = 1;
			}else if( (MeauParm.BackupMeau - KeyParm.BackupMeauLow) > 4)
			{
				if(OutputState.OverLow == 0)
					AutoRunParm.OutputState = AutoRunParm.OutputState & 0xFDFF;	
				OutputIO.BackupMeauLow = 0;
			}
		}else
		{
			OutputIO.BackupMeauHigh = 0;
			OutputIO.BackupMeauLow = 0;
			if(OutputState.OverHigh == 0)
				AutoRunParm.OutputState = AutoRunParm.OutputState & 0xFEFF;	
			if(OutputState.OverLow == 0)
				AutoRunParm.OutputState = AutoRunParm.OutputState & 0xFDFF;	
		}
			
	if( (InsideIOState.Men == 1) && (InsideIOState.Stop == 0) && (InsideIOState.IoStop == 0) )
	{
		RunState.PreRun = 1;
		RunState.AutoRun = 0;
		OutputState.Men = 1;
		OutputState.Auto = 0;
		OutputState.StopMent = 0;
		AutoRunParm.OutputState = AutoRunParm.OutputState | 0x0001;
		AutoRunParm.OutputState = AutoRunParm.OutputState & 0xFFFD;	
		if(KeyParm.SaveParms[127] == 1)
		{
			KeyParm.SaveParms[127] = 0;
			EEPROMADDR = 0xF000 + 2 * 127;
	        EraseEE(__builtin_tblpage(&EPConfigS[0]),EEPROMADDR, WORD);
	        WriteEE(&KeyParm.SaveParms[127],__builtin_tblpage(&EPConfigS[0]),EEPROMADDR, WORD);
		}		
	}else if( (InsideIOState.Auto == 1) || (InsideIOState.IoAuto == 1) )
	{
		RunState.PreRun = 0;
		RunState.AutoRun = 1;
		OutputState.Men = 0;
		OutputState.Auto = 1;
		OutputState.StopMent = 0;
		AutoRunParm.OutputState = AutoRunParm.OutputState | 0x0002;
		AutoRunParm.OutputState = AutoRunParm.OutputState & 0xFFFE;
		Uart1Parm.RunNumber = Uart1Parm.Addr;
		AutoRunParm.RunNumber = 0;
		Uart1State.Change = 1;
		if(KeyParm.SaveParms[127] == 0)
		{ 
			KeyParm.SaveParms[127] = 1;
			EEPROMADDR = 0xF000 + 2 * 127;
	        EraseEE(__builtin_tblpage(&EPConfigS[0]),EEPROMADDR, WORD);
	        WriteEE(&KeyParm.SaveParms[127],__builtin_tblpage(&EPConfigS[0]),EEPROMADDR, WORD);
		}
	}else if( (InsideIOState.Stop == 1) || (InsideIOState.IoStop == 1) )
	{
		RunState.PreRun = 0;
		RunState.AutoRun = 0;
		ErrorParm.EndError = 0;
		ErrorParm.InitError = 0;
		OutputState.Men = 0;
		OutputState.Auto = 0;
		OutputState.Stay = 0;
		OutputState.StopMent = 1;
		RunState.FillGas = 0;
		OutputState.FillGas = 0;
		if(RunState.StopOff == 0)
		{
			RunState.StopOff = 1;
			OutputState.Stop = 1;
		}
		if(RunState.StopGasOff == 0)
		{
			OutputIO.StopFillGas = 1;
			RunState.StopGasOff = 1;
		}
		AutoRunParm.OutputState = AutoRunParm.OutputState & 0xFFDF;
		AutoRunParm.OutputState = AutoRunParm.OutputState & 0xFFFC;
		AutoRunParm.OutputState = AutoRunParm.OutputState & 0xFFF3;	
		if(KeyParm.SaveParms[127] == 1)
		{
			KeyParm.SaveParms[127] = 0;
			EEPROMADDR = 0xF000 + 2 * 127;
	        EraseEE(__builtin_tblpage(&EPConfigS[0]),EEPROMADDR, WORD);
	        WriteEE(&KeyParm.SaveParms[127],__builtin_tblpage(&EPConfigS[0]),EEPROMADDR, WORD);
		}
	}else if(KeyParm.SaveParms[127] == 1)
	{
		if(RunState.AutoRun == 0)
		{
			AutoRunParm.OutputState = AutoRunParm.OutputState | 0x0002;
			AutoRunParm.OutputState = AutoRunParm.OutputState & 0xFFFE;

			AutoRunParm.AutoEnumerate = AutoRunParm.AutoEnumerate + 1;
			if(AutoRunParm.AutoEnumerate > 1000)
			{
				RunState.PreRun = 0;
				RunState.AutoRun = 1;
				OutputState.Men = 0;
				OutputState.Auto = 1;
				OutputState.StopMent = 0;
				AutoRunParm.OutputState = AutoRunParm.OutputState | 0x0002;
				AutoRunParm.OutputState = AutoRunParm.OutputState & 0xFFFE;
				Uart1Parm.RunNumber = Uart1Parm.Addr;
				AutoRunParm.RunNumber = 0;
				Uart1State.Change = 1;
				AutoRunParm.AutoEnumerate = 0;
			}
		}
	}
	
	if(RunState.AutoRun == 1)
	{
		if(RunState.BackupOpen == 0)
		{
			
			
			if(KeyParm.FillGasMode == 1)
			{
			
				if(RunState.FillGas == 0)
				{
					if(MeauParm.BackupMeau > AutoRunParm.FillGas )
						RunState.FillGas = 1;
					OutputState.FillGas = 0;
					AutoRunParm.OutputState = AutoRunParm.OutputState & 0xFFDF;
				}else
				{
					if(MeauParm.BackupMeau < AutoRunParm.FillOil )
					{
						if(RunState.FillGas == 1)
						{
							RunState.FillGas = 0;
							OutputIO.StopFillGas = 1;
						}
					}
					
					if(OutputState.FillGas == 0)
					{
						if(MeauParm.MainMeau < (AutoRunParm.Normal + ( (AutoRunParm.Stop - AutoRunParm.Normal) >> 1) ) )
						{
							OutputIO.StopFillGas = 0;
							OutputState.FillGas = 1;
							RunState.StopGasOff = 0;
							AutoRunParm.OutputState = AutoRunParm.OutputState | 0x0020;
						}
						
						if(RunState.StopGasOff == 0)
						{
							AutoRunParm.StopFillGasOnEnumerate = AutoRunParm.StopFillGasOnEnumerate + 1;
							if(AutoRunParm.StopFillGasOnEnumerate > 20)
							{
								OutputIO.StopFillGas = 1;
								RunState.StopGasOff = 1;
								AutoRunParm.OutputState = AutoRunParm.OutputState & 0xFFDF;
								AutoRunParm.StopFillGasOnEnumerate = 0;
							}
						}
						
						AutoRunParm.OutputState = AutoRunParm.OutputState & 0xFFDF;
					}else
					{
						OutputState.FillGas = 1;
						RunState.StopGasOff = 0;
						if(MeauParm.MainMeau > AutoRunParm.Stop)
						{
							OutputState.FillGas = 0;
						}
						AutoRunParm.StopFillGasOnEnumerate = 0;
						AutoRunParm.OutputState = AutoRunParm.OutputState | 0x0020;
					}
				}			
			}
		}else
		{
			AutoRunParm.OutputState = AutoRunParm.OutputState & 0xFFDF;		
			OutputState.FillGas = 0;
			RunState.FillGas = 0;
			
		}
		
		if(RunState.MainOpen == 0)
		{
			if(RunState.HighByLow == 1)
			{
				if(RunState.MeanRun == 0)
				{
					if(MeauParm.MainMeau < AutoRunParm.RunParm[AutoRunParm.RunNumber])
					{
						RunState.MeanRun = 1;
						if(AutoRunParm.RunNumber == 0)
						{
							AutoRunParm.OutputState = AutoRunParm.OutputState | 0x0004;
							OutputState.Normal = 1;
						}else
						{
							AutoRunParm.OutputState = AutoRunParm.OutputState | 0x0008;
							OutputState.Backup = 1;
						}
					}
					if(Uart1Parm.AddrMax != 8)
					{
						if(MeauParm.MainMeau < AutoRunParm.RunParm[Uart1Parm.AddrMax] )
						{
							RunState.MeanRun = 1;
							AutoRunParm.OutputState = AutoRunParm.OutputState | 0x0008;
							OutputState.Backup = 1;
						}
					}			
				}else
				{
					if(MeauParm.MainMeau > AutoRunParm.Stop)
					{
						RunState.MeanRun = 0;
						AutoRunParm.OutputState = AutoRunParm.OutputState & 0xFFF3;
						OutputState.Normal = 0;
						OutputState.Backup = 0;
						if(AutoRunParm.RunNumber == 0)
							AutoRunParm.ChangeEnumerate = AutoRunParm.ChangeEnumerate + 1;
					}
				}
				
				
			}else
			{
				if(RunState.MeanRun == 0)
				{
					if(MeauParm.MainMeau > AutoRunParm.RunParm[AutoRunParm.RunNumber])
					{
						RunState.MeanRun = 1;
						if(AutoRunParm.RunNumber == 0)
						{
							AutoRunParm.OutputState = AutoRunParm.OutputState | 0x0004;
							OutputState.Normal = 1;
						}else
						{
							AutoRunParm.OutputState = AutoRunParm.OutputState | 0x0008;
							OutputState.Backup = 1;
						}
					}
					if(Uart1Parm.AddrMax != 8)
					{
						if(MeauParm.MainMeau > AutoRunParm.RunParm[Uart1Parm.AddrMax] )
						{
							RunState.MeanRun = 1;
							AutoRunParm.OutputState = AutoRunParm.OutputState | 0x0008;
							OutputState.Backup = 1;
						}
					}				
				}else
				{
					if(MeauParm.MainMeau < AutoRunParm.Stop)
					{
						RunState.MeanRun = 0;
						AutoRunParm.OutputState = AutoRunParm.OutputState & 0xFFF3;
						OutputState.Normal = 0;
						OutputState.Backup = 0;
						if(AutoRunParm.RunNumber == 0)
							AutoRunParm.ChangeEnumerate = AutoRunParm.ChangeEnumerate + 1;
					}
				}
			}
		}else
		{
			RunState.MeanRun = 0;
			//AutoRunParm.OutputState = AutoRunParm.OutputState & 0xFFF3;
			//OutputState.Normal = 0;
			//OutputState.Backup = 0;
		}			
						
		if(KeyParm.CtrMode == 0)
		{
			if(RunState.ImRun == 0)
			{
				if(InputState.ImRun == 1)
				{
					RunState.ImRun = 1;
				}
			}else
			{
				if(InputState.ImStop == 1)
				{
					RunState.ImRun = 0;
				}
			}
			
			if(RunState.UnitRun == 0)
			{
				switch(AutoRunParm.RunNumber)
    			{
					case 0:
						if(InputState.NormalRun == 1)
						{
							RunState.UnitRun = 1;
							AutoRunParm.OutputState = AutoRunParm.OutputState | 0x0004;
							OutputState.Normal = 1;
							OutputState.Backup = 0;
						}
						break;
					case 1:
						if(InputState.BackupRun == 1)
						{
							RunState.UnitRun = 1;
							AutoRunParm.OutputState = AutoRunParm.OutputState | 0x0008;
							OutputState.Backup = 1;
							OutputState.Normal = 0;
						}
						break;
					case 2:
						if(InputState.Backup2Run == 1)
						{
							RunState.UnitRun = 1;
							AutoRunParm.OutputState = AutoRunParm.OutputState | 0x0008;
							OutputState.Backup = 1;
							OutputState.Normal = 0;
						}
						break;
					case 3:
						if(InputState.Backup3Run == 1)
						{
							RunState.UnitRun = 1;
							AutoRunParm.OutputState = AutoRunParm.OutputState | 0x0008;
							OutputState.Backup = 1;
							OutputState.Normal = 0;
						}
						break;
					case 4:
						if(InputState.Backup4Run == 1)
						{
							RunState.UnitRun = 1;
							AutoRunParm.OutputState = AutoRunParm.OutputState | 0x0008;
							OutputState.Backup = 1;
							OutputState.Normal = 0;
						}
						break;
					case 5:
						if(InputState.Backup5Run == 1)
						{
							RunState.UnitRun = 1;
							AutoRunParm.OutputState = AutoRunParm.OutputState | 0x0008;
							OutputState.Backup = 1;
							OutputState.Normal = 0;
						}
						break;
					case 6:
						if(InputState.Backup6Run == 1)
						{
							RunState.UnitRun = 1;
							AutoRunParm.OutputState = AutoRunParm.OutputState | 0x0008;
							OutputState.Backup = 1;
							OutputState.Normal = 0;
						}
						break;
					case 7:
						if(InputState.Backup7Run == 1)
						{
							RunState.UnitRun = 1;
							AutoRunParm.OutputState = AutoRunParm.OutputState | 0x0008;
							OutputState.Backup = 1;
							OutputState.Normal = 0;
						}
						break;
					default:
						if(InputState.NormalRun == 1)
						{
							RunState.UnitRun = 1;
							AutoRunParm.OutputState = AutoRunParm.OutputState | 0x0004;
							OutputState.Backup = 0;
							OutputState.Normal = 1;
						}
						break;
				}
					
			}else
			{
				if(OutputState.Backup == 1)
				{
					if(InsideIOState.BackupStop == 1)
					{
						RunState.UnitRun = 0;
						AutoRunParm.OutputState = AutoRunParm.OutputState & 0xFFF3;
						OutputState.Backup = 0;
						if(AutoRunParm.RunNumber == 0)
							AutoRunParm.ChangeEnumerate = AutoRunParm.ChangeEnumerate + 1;
					}
				}
				if(InputState.AutoStop == 1)
				{
					RunState.UnitRun = 0;
					AutoRunParm.OutputState = AutoRunParm.OutputState & 0xFFF3;
					if(AutoRunParm.RunNumber == 0)
						AutoRunParm.ChangeEnumerate = AutoRunParm.ChangeEnumerate + 1;OutputState.Normal = 0;
					OutputState.Backup = 0;
				}
				
			}
		}else
		{
			if(InputState.ImLog == 1)
			{
				RunState.ImRun = 1;
			}else
			{
				RunState.ImRun = 0;
			}
				
				switch(AutoRunParm.RunNumber)
    			{
					case 0:
						if(InputState.NormalRun == 1)
						{
							RunState.UnitRun = 1;
							AutoRunParm.OutputState = AutoRunParm.OutputState | 0x0004;
							OutputState.Normal = 1;
						}else
						{
							RunState.UnitRun = 0;
							AutoRunParm.OutputState = AutoRunParm.OutputState & 0xFFF3;
							AutoRunParm.ChangeEnumerate = AutoRunParm.ChangeEnumerate + 1;
							OutputState.Normal = 0;
							OutputState.Backup = 0;
						}
						break;
					case 1:
						if(InputState.BackupRun == 1)
						{
							RunState.UnitRun = 1;
							AutoRunParm.OutputState = AutoRunParm.OutputState | 0x0008;
							OutputState.Backup = 1;
						}else
						{
							RunState.UnitRun = 0;
							AutoRunParm.OutputState = AutoRunParm.OutputState & 0xFFF3;
							OutputState.Normal = 0;
							OutputState.Backup = 0;
						}
						break;
					case 2:
						if(InputState.Backup2Run == 1)
						{
							RunState.UnitRun = 1;
							AutoRunParm.OutputState = AutoRunParm.OutputState | 0x0008;
							OutputState.Backup = 1;
						}else
						{
							RunState.UnitRun = 0;
							AutoRunParm.OutputState = AutoRunParm.OutputState & 0xFFF3;
							OutputState.Normal = 0;
							OutputState.Backup = 0;
						}
						break;
					case 3:
						if(InputState.Backup3Run == 1)
						{
							RunState.UnitRun = 1;
							AutoRunParm.OutputState = AutoRunParm.OutputState | 0x0008;
							OutputState.Backup = 1;
						}else
						{
							RunState.UnitRun = 0;
							AutoRunParm.OutputState = AutoRunParm.OutputState & 0xFFF3;
							OutputState.Normal = 0;
							OutputState.Backup = 0;
						}
						break;
					case 4:
						if(InputState.Backup4Run == 1)
						{
							RunState.UnitRun = 1;
							AutoRunParm.OutputState = AutoRunParm.OutputState | 0x0008;
							OutputState.Backup = 1;
						}else
						{
							RunState.UnitRun = 0;
							AutoRunParm.OutputState = AutoRunParm.OutputState & 0xFFF3;
							OutputState.Normal = 0;
							OutputState.Backup = 0;
						}
						break;
					case 5:
						if(InputState.Backup5Run == 1)
						{
							RunState.UnitRun = 1;
							AutoRunParm.OutputState = AutoRunParm.OutputState | 0x0008;
							OutputState.Backup = 1;
						}else
						{
							RunState.UnitRun = 0;
							AutoRunParm.OutputState = AutoRunParm.OutputState & 0xFFF3;
							OutputState.Normal = 0;
							OutputState.Backup = 0;
						}
						break;
					case 6:
						if(InputState.Backup6Run == 1)
						{
							RunState.UnitRun = 1;
							AutoRunParm.OutputState = AutoRunParm.OutputState | 0x0008;
							OutputState.Backup = 1;
						}else
						{
							RunState.UnitRun = 0;
							AutoRunParm.OutputState = AutoRunParm.OutputState & 0xFFF3;
							OutputState.Normal = 0;
							OutputState.Backup = 0;
						}
						break;
					case 7:
						if(InputState.Backup7Run == 1)
						{
							RunState.UnitRun = 1;
							AutoRunParm.OutputState = AutoRunParm.OutputState | 0x0008;
							OutputState.Backup = 1;
						}else
						{
							RunState.UnitRun = 0;
							AutoRunParm.OutputState = AutoRunParm.OutputState & 0xFFF3;
							OutputState.Normal = 0;
							OutputState.Backup = 0;
						}
						break;
					default:
						if(InputState.NormalRun == 1)
						{
							RunState.UnitRun = 1;
							AutoRunParm.OutputState = AutoRunParm.OutputState | 0x0004;
							OutputState.Normal = 1;
						}else
						{
							RunState.UnitRun = 0;
							AutoRunParm.OutputState = AutoRunParm.OutputState & 0xFFF3;
							OutputState.Normal = 0;
							OutputState.Backup = 0;
						}
						break;
				}
		}
		
		if( (RunState.MeanRun == 0) && (RunState.UnitRun == 0) && (RunState.ImRun == 0) )
		{
			RunState.PreRun = 0;
			AutoRunParm.StayOutEnumerate = AutoRunParm.StayOutEnumerate + 1;
			if(AutoRunParm.StayOutEnumerate > 1200)
			{
				AutoRunParm.StayOutEnumerate = 2500;
				OutputState.Stay = 1;
			}
		}else 
		{
			RunState.PreRun = 1;
			OutputState.Stay = 0;
			AutoRunParm.StayOutEnumerate = 0;
		}
		
	}else 
	{
		RunState.MeanRun = 0;
		RunState.UnitRun = 0;
		RunState.ImRun = 0;
		AutoRunParm.OutputState = AutoRunParm.OutputState & 0xFFF3;
		OutputState.Normal = 0;
		OutputState.Backup = 0;
		if(AutoRunParm.RunNumber == 0)
		{
			Uart1Parm.RunNumber = Uart1Parm.Addr + 1;
			if(Uart1Parm.RunNumber > Uart1Parm.AddrMax)
				Uart1Parm.RunNumber = 0;
			Uart1State.Change = 1;
		}
		
		RunState.FillGas = 0;
		OutputState.FillGas = 0;
		if(RunState.StopGasOff == 0)
		{
			OutputIO.StopFillGas = 1;
			RunState.StopGasOff = 1;
		}
	}
	
	
	if(ErrorParm.EndError != 0)
		RunState.PreRun = 0;
		
	if(InputState.RunLimit == 1)
	{
		RunState.PreRun = 0;
		AutoRunParm.OutputState = AutoRunParm.OutputState | 0x4000;
	}else if( (RunState.HighByLow == 1) && (MeauParm.MainMeau > AutoRunParm.Limit) && (RunState.MainOpen == 0) )
	{
		RunState.PreRun = 0;
		AutoRunParm.OutputState = AutoRunParm.OutputState | 0x4000;
	}else if( (RunState.HighByLow == 0) && (MeauParm.MainMeau < AutoRunParm.Limit) && (RunState.MainOpen == 0) )
	{
		RunState.PreRun = 0;
		AutoRunParm.OutputState = AutoRunParm.OutputState | 0x4000;
	}else
		AutoRunParm.OutputState = AutoRunParm.OutputState & 0xBFFF;
		
		
	if(RunState.PreRun == 1)
	{
		if(SoftRunParms.PrepareTime == 0)
			RunState.Run = 1;
		else if(SoftRunParms.PrepareTime > 59990)
		{
			if(RunState.Run == 0)
			{
				if(InputState.RunPrePare == 1)
				{
					AutoRunParm.PrepareEnumerate += 1;
					if( AutoRunParm.PrepareEnumerate > 1000)	//准备闭环延时时间
					{
						RunState.Run = 1;
						AutoRunParm.PrepareEnumerate = 0;
						AutoRunParm.OutputState = AutoRunParm.OutputState & 0xFFEF;
					}
				}else
				{
					OutputState.Prepare = 1;
					AutoRunParm.OutputState = AutoRunParm.OutputState | 0x0010;
				}
			}else
			{
				AutoRunParm.PrepareEnumerate += 1;
				if( AutoRunParm.PrepareEnumerate > SoftRunParms.PrepareDelay)
					OutputState.Prepare = 0;
			}
		}else 
		{
			if(RunState.Run == 0)
			{
				OutputState.Prepare = 1;
				AutoRunParm.OutputState = AutoRunParm.OutputState | 0x0010;
				AutoRunParm.PrepareEnumerate += 1;
				if( AutoRunParm.PrepareEnumerate > SoftRunParms.PrepareTime)
				{
					RunState.Run = 1;
					AutoRunParm.PrepareEnumerate = 0;
					AutoRunParm.OutputState = AutoRunParm.OutputState & 0xFFEF;
				}
			}else
			{
				AutoRunParm.PrepareEnumerate += 1;
				if( AutoRunParm.PrepareEnumerate > SoftRunParms.PrepareDelay)
					OutputState.Prepare = 0;
			}
		}
	}else
	{
		RunState.Run = 0;
		OutputState.Prepare = 0;
		AutoRunParm.PrepareEnumerate = 0;
		AutoRunParm.OutputState = AutoRunParm.OutputState & 0xFFEF;
	}
	
	if( (RunState.Run == 1) || (StartState.RoadRun == 1) || (StartState.BenJiRun == 1) )
	{
		AutoRunParm.OutputState = AutoRunParm.OutputState | 0x0040;
		OutputState.Start = 1;
	}else
	{
		AutoRunParm.OutputState = AutoRunParm.OutputState & 0xFFBF;
		OutputState.Start = 0;
		AutoRunParm.RunOutEnumerate = 0;
		if(RunState.StopOff == 0)
		{
			RunState.StopOff = 1;
			OutputState.Stop = 1;
		}
	}

	if( ((StartState.RoadRun == 1) || (StartState.BenJiRun == 1)) && (RunState.Run == 1) )
	{
		AutoRunParm.RunOutEnumerate = AutoRunParm.RunOutEnumerate + 1;
		if(AutoRunParm.RunOutEnumerate > 20)
		{
			AutoRunParm.RunOutEnumerate = 2500;
			AutoRunParm.OutputState = AutoRunParm.OutputState | 0x0080;	
			OutputState.Run = 1;
			RunState.StopOff = 0;
		}
		
	}else
	{
		AutoRunParm.OutputState = AutoRunParm.OutputState & 0xFF7F;
		OutputState.Run = 0;
	}
	
	IOWrite();						//IO口输出
	IORead();						//读IO口状态
	IOCorp();						//IO口状态处理
	
}

void PingJun0(void)
{
				if(AX_int_AutoRun > Uart1Parm.MainData[0])
				{
					if(Uart1Parm.MainData[0] > BX_int_AutoRun)
						MeauParm.MainMeau1 = ( (long) MeauParm.MainMeauCom + Uart1Parm.MainData[0] ) >> 1;
					else
						MeauParm.MainMeau1 = MeauParm.MainMeauCom;
				}else
					MeauParm.MainMeau1 = MeauParm.MainMeauCom;
}
void PingJun1(void)
{
				if(AX_int_AutoRun > Uart1Parm.MainData[1])
				{
					if(Uart1Parm.MainData[1] > BX_int_AutoRun)
						MeauParm.MainMeau2 = ( (long) MeauParm.MainMeau1 + Uart1Parm.MainData[1] ) >> 1;
					else
						MeauParm.MainMeau2 = MeauParm.MainMeau1;
				}else
					MeauParm.MainMeau2 = MeauParm.MainMeau1;
}					
void PingJun2(void)
{					
				if(AX_int_AutoRun > Uart1Parm.MainData[2])
				{
					if(Uart1Parm.MainData[2] > BX_int_AutoRun)
						MeauParm.MainMeau3 = ( (long) MeauParm.MainMeau2 + Uart1Parm.MainData[2] ) >> 1;
					else
						MeauParm.MainMeau3 = MeauParm.MainMeau2;
				}else
					MeauParm.MainMeau3 = MeauParm.MainMeau2;
}
void PingJun3(void)
{
				if(AX_int_AutoRun > Uart1Parm.MainData[3])
				{
					if(Uart1Parm.MainData[3] > BX_int_AutoRun)
						MeauParm.MainMeau4 = ( (long) MeauParm.MainMeau3 + Uart1Parm.MainData[3] ) >> 1;
					else
						MeauParm.MainMeau4 = MeauParm.MainMeau3;
				}else
					MeauParm.MainMeau4 = MeauParm.MainMeau3;
}
void PingJun4(void)
{
				if(AX_int_AutoRun > Uart1Parm.MainData[4])
				{
					if(Uart1Parm.MainData[4] > BX_int_AutoRun)
						MeauParm.MainMeau5 = ( (long) MeauParm.MainMeau4 + Uart1Parm.MainData[4] ) >> 1;
					else
						MeauParm.MainMeau5 = MeauParm.MainMeau4;
				}else
					MeauParm.MainMeau5 = MeauParm.MainMeau4;	
}
void PingJun5(void)
{
				if(AX_int_AutoRun > Uart1Parm.MainData[5])
				{
					if(Uart1Parm.MainData[5] > BX_int_AutoRun)
						MeauParm.MainMeau6 = ( (long) MeauParm.MainMeau5 + Uart1Parm.MainData[5] ) >> 1;
					else
						MeauParm.MainMeau6 = MeauParm.MainMeau5;
				}else
					MeauParm.MainMeau6 = MeauParm.MainMeau5;
}
void PingJun6(void)
{
				if(AX_int_AutoRun > Uart1Parm.MainData[6])
				{
					if(Uart1Parm.MainData[6] > BX_int_AutoRun)
						MeauParm.MainMeau7 = ( (long) MeauParm.MainMeau6 + Uart1Parm.MainData[6] ) >> 1;
					else
						MeauParm.MainMeau7 = MeauParm.MainMeau6;
				}else
					MeauParm.MainMeau7 = MeauParm.MainMeau6;
}
void PingJun7(void)
{
			if(AX_int_AutoRun > Uart1Parm.MainData[7])
			{
				if(Uart1Parm.MainData[7] > BX_int_AutoRun)
					MeauParm.MainMeau8 = ( (long) MeauParm.MainMeau7 + Uart1Parm.MainData[7] ) >> 1;
				else
					MeauParm.MainMeau8 = MeauParm.MainMeau7;
			}else
				MeauParm.MainMeau8 = MeauParm.MainMeau7;
}
