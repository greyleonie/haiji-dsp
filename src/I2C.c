//海吉科技，HJR3000型智能软启动控制装置，DSPIC30F6010A系统
//I2C通讯程序 I2C.c

//头文件
#include "UserParms.h"	//用户系统配置，常数定义及配置值
#include "Function.h"	//系统外部调用函数声明，内部调用函数在对应文件内声明
#include "variable.h"	//系统全局变量声明，局部变量在对应文件内声明

int AX_int_I2C = 0, BX_int_I2C = 0, CX_int_I2C = 0, AX_int_I2CTrn;
unsigned int AX_Unint_I2C = 0;

void __attribute__((__interrupt__)) _SI2CInterrupt (void)
{
	if((I2CSTATbits.P == 0) && (I2CSTATbits.S == 1))
	{
		MainParm.ResetCount = 0;
		if(I2CSTATbits.D_A == 0)
		{
			if(I2CSTATbits.R_W == 0) 
			{
				I2CParm.RcvCurData = I2CRCV;
				
			}else
			{
				I2CParm.RcvCurData = I2CRCV;
				
				if(MainState.I2CTrn == 0)
				{
					MainState.I2CTrn = 1;
					
					while(I2CSTATbits.IWCOL == 1)
					{
						I2CSTATbits.IWCOL = 0;
					}
					if(MainState.TrnParam == 1)
					{
						if(I2CParm.TrnTimes == 0)
						{
							I2CParm.TrnTimes = 1;
							I2CParm.TrnCurData = 0xAA;
							I2CTRN = I2CParm.TrnCurData;
							I2CCONbits.SCLREL = 1;			
		
						}else if(I2CParm.TrnTimes == 1)
						{
							I2CParm.TrnTimes = 2;
							I2CParm.TrnCurData = 0x55;
							I2CTRN = I2CParm.TrnCurData;
							I2CCONbits.SCLREL = 1;			
							I2CParm.TrnDataCheck = 255;
							
						}else if(I2CParm.TrnTimes > 251)
						{
							I2CParm.TrnTimes = 0;
							I2CParm.TrnCurData = - I2CParm.TrnDataCheck;
							I2CParm.TrnCurData = I2CParm.TrnCurData & 0x00FF;
							I2CParm.TrnDataCheck = 0;
							I2CTRN = I2CParm.TrnCurData;
							I2CCONbits.SCLREL = 1;
							MainState.TrnParam = 0;
							
						}else
						{
							AX_int_I2CTrn = I2CParm.TrnTimes - 2;
							AX_int_I2CTrn = AX_int_I2CTrn % 2;
							if(AX_int_I2CTrn == 0)
								I2CParm.TrnCurData = KeyParm.SaveParms[((I2CParm.TrnTimes - 2) / 2)];
							else if(AX_int_I2CTrn == 1)
								I2CParm.TrnCurData = KeyParm.SaveParms[((I2CParm.TrnTimes - 2) / 2)] >> 8;
							I2CParm.TrnDataCheck = I2CParm.TrnDataCheck + I2CParm.TrnCurData;
							I2CTRN = I2CParm.TrnCurData;
							I2CCONbits.SCLREL = 1;			
							I2CParm.TrnTimes = I2CParm.TrnTimes + 1;
						}	
					}else if(MainState.TrnError == 1)
					{
						if(I2CParm.TrnTimes == 0)
						{
							I2CParm.TrnTimes = 1;
							I2CParm.TrnCurData = 0xAA;
							I2CTRN = I2CParm.TrnCurData;
							I2CCONbits.SCLREL = 1;			
							
						}else if(I2CParm.TrnTimes == 1)
						{
							I2CParm.TrnTimes = 2;
							I2CParm.TrnCurData = 0x55;
							I2CTRN = I2CParm.TrnCurData;
							I2CCONbits.SCLREL = 1;			
							I2CParm.TrnDataCheck = 255;
							
						}else if(I2CParm.TrnTimes > 161)
						{
							I2CParm.TrnTimes = 0;
							I2CParm.TrnCurData = - I2CParm.TrnDataCheck;
							I2CParm.TrnCurData = I2CParm.TrnCurData & 0x00FF;
							I2CParm.TrnDataCheck = 0;
							I2CTRN = I2CParm.TrnCurData;
							I2CCONbits.SCLREL = 1;
							MainState.TrnError = 0;
							
						}else
						{
							AX_int_I2CTrn = I2CParm.TrnTimes - 2;
							AX_int_I2CTrn = AX_int_I2CTrn % 10;
							if(AX_int_I2CTrn == 0)
								I2CParm.TrnCurData = ErrorParm.EndErrorSave[((I2CParm.TrnTimes - 2) / 10)];
							else if(AX_int_I2CTrn == 1)
								I2CParm.TrnCurData = ErrorParm.EndErrorSave[((I2CParm.TrnTimes - 2) / 10)] >> 8;
							if(AX_int_I2CTrn == 2)
								I2CParm.TrnCurData = ErrorParm.ErrorSaveState[((I2CParm.TrnTimes - 2) / 10)];
							else if(AX_int_I2CTrn == 3)
								I2CParm.TrnCurData = ErrorParm.ErrorSaveState[((I2CParm.TrnTimes - 2) / 10)] >> 8;
							if(AX_int_I2CTrn == 4)
								I2CParm.TrnCurData = ErrorParm.ErrorSaveMainMeau[((I2CParm.TrnTimes - 2) / 10)];
							else if(AX_int_I2CTrn == 5)
								I2CParm.TrnCurData = ErrorParm.ErrorSaveMainMeau[((I2CParm.TrnTimes - 2) / 10)] >> 8;
							if(AX_int_I2CTrn == 6)
								I2CParm.TrnCurData = ErrorParm.ErrorSaveIUVW[((I2CParm.TrnTimes - 2) / 10)];
							else if(AX_int_I2CTrn == 7)
								I2CParm.TrnCurData = ErrorParm.ErrorSaveIUVW[((I2CParm.TrnTimes - 2) / 10)] >> 8;
							if(AX_int_I2CTrn == 8)
								I2CParm.TrnCurData = ErrorParm.ErrorSaveUin[((I2CParm.TrnTimes - 2) / 10)];
							else if(AX_int_I2CTrn == 9)
								I2CParm.TrnCurData = ErrorParm.ErrorSaveUin[((I2CParm.TrnTimes - 2) / 10)] >> 8;
							
							I2CParm.TrnDataCheck = I2CParm.TrnDataCheck + I2CParm.TrnCurData;
							I2CTRN = I2CParm.TrnCurData;
							I2CCONbits.SCLREL = 1;			
							I2CParm.TrnTimes = I2CParm.TrnTimes + 1;
						}	
					}else
					{	
						if(I2CParm.TrnTimes > 22)
						{
							I2CParm.TrnTimes = 0;
							I2CParm.TrnCurData = - I2CParm.TrnDataCheck;
							I2CParm.TrnCurData = I2CParm.TrnCurData & 0x00FF;
							I2CParm.TrnDataCheck = 0;
							I2CTRN = I2CParm.TrnCurData;
							I2CCONbits.SCLREL = 1;
						}else
						{
							I2CParm.TrnCurData = I2CParm.TrnData[I2CParm.TrnTimes];
							I2CParm.TrnDataCheck = I2CParm.TrnDataCheck + I2CParm.TrnCurData;
							I2CTRN = I2CParm.TrnCurData;
							I2CCONbits.SCLREL = 1;			
							I2CParm.TrnTimes = I2CParm.TrnTimes + 1;
						}
					}
					
				}else 
				{
					MainState.I2CTrn = 0;
					I2CCONbits.SCLREL = 1;	
				}
			}
		}else 
		{
			
			if(I2CSTATbits.RBF == 1)
			{
				I2CParm.RcvCurData = I2CRCV;
				
				if(I2CParm.RcvTimes == 0)
				{
					if(I2CParm.RcvCurData == 0x00AA)
					{
						I2CParm.RcvTimes = 1;
						
					}else I2CParm.RcvTimes = 0;
				}else if(I2CParm.RcvTimes == 1)
				{
					if(I2CParm.RcvCurData == 0x0055)
					{
						I2CParm.RcvTimes = 2;
						I2CParm.RcvSaveTimes = 0;
												
					}else I2CParm.RcvTimes = 0;
				}else if(I2CParm.RcvTimes == 2)
				{
					if(I2CParm.RcvCurData == 0x0050)
					{
						I2CParm.RcvTimes = 3;
						I2CParm.RcvSaveTimes = 0;
						I2CParm.RcvDataCheck = 0x004F;
						
					}else if(I2CParm.RcvCurData == 0x00A0)
					{
						I2CParm.RcvTimes = 10;
						I2CParm.RcvDataCheck = 0x009F;
						
					}else if(I2CParm.RcvCurData == 0x00A1)
					{
						I2CParm.RcvTimes = 20;
						I2CParm.RcvDataCheck = 0x00A0;
						
					}else if(I2CParm.RcvCurData == 0x00A5)
					{
						I2CParm.RcvTimes = 30;
						I2CParm.RcvDataCheck = 0x00A4;
						
					}else I2CParm.RcvTimes = 0;
				}else if(I2CParm.RcvTimes == 3)
				{
					if(I2CParm.RcvSaveTimes > 249)
					{
						I2CParm.RcvSaveTimes = 0;
						I2CParm.RcvTimes = 1;
						I2CParm.RcvDataCheck = I2CParm.RcvDataCheck + I2CParm.RcvCurData;
						I2CParm.RcvDataCheck = I2CParm.RcvDataCheck & 0x00FF;
						if(I2CParm.RcvDataCheck == 0)
						{
							MainState.I2CRcv = 1;
							
						}
					
					}else
					{
						I2CParm.RcvData[I2CParm.RcvSaveTimes] = I2CParm.RcvCurData;
						I2CParm.RcvDataCheck = I2CParm.RcvDataCheck + I2CParm.RcvCurData;
						I2CParm.RcvSaveTimes = I2CParm.RcvSaveTimes + 1;
					
					}
					
				}else if(I2CParm.RcvTimes == 10)
				{
					I2CParm.RcvTimes = 0;
					if(I2CParm.RcvCurData == I2CParm.RcvDataCheck)
					{
						MainState.TrnParam = 1;
						MainState.TrnError = 0;
						I2CParm.TrnTimes = 0;		
					}
				}else if(I2CParm.RcvTimes == 20)
				{
					I2CParm.RcvTimes = 0;
					if(I2CParm.RcvCurData == I2CParm.RcvDataCheck)
					{
						MainState.TrnError = 1;
						MainState.TrnParam = 0;
						I2CParm.TrnTimes = 0;		
					}
				}else if(I2CParm.RcvTimes == 30)
				{
					I2CParm.RcvTimes = 0;
					if(I2CParm.RcvCurData == I2CParm.RcvDataCheck)
					{
						MainState.RcvTrnData = 1;
						MainState.TrnError = 0;
						MainState.TrnParam = 0;
						I2CParm.TrnTimes = 0;		
					}
				}else
				{
					I2CParm.RcvTimes = 0;
				}
			}
		}	

	}
	IFS0bits.SI2CIF = 0;
	return;
}

void __attribute__((__interrupt__)) _MI2CInterrupt (void)
{
	
	IFS0bits.MI2CIF = 0;
	return;
}

void TrnData(void)
{
		
		I2CParm.TrnData[0] = 0x00AA;
		I2CParm.TrnData[1] = 0x0055;
	
		I2CParm.TrnData[2] = MeauParm.MainMeau & 0x00FF;
		I2CParm.TrnData[3] = (MeauParm.MainMeau & 0xFF00) >> 8;
	
		I2CParm.TrnData[4] = MeauParm.BackupMeau & 0x00FF;
		I2CParm.TrnData[5] = (MeauParm.BackupMeau & 0xFF00) >> 8;
	
		I2CParm.TrnData[6] = CurParms.IUVW & 0x00FF;
		I2CParm.TrnData[7] = (CurParms.IUVW & 0xFF00) >> 8;
	
		I2CParm.TrnData[8] = VolParms.Uin & 0x00FF;
		I2CParm.TrnData[9] = (VolParms.Uin & 0xFF00) >> 8;
	
		I2CParm.TrnData[10] = ErrorParm.EndError & 0x00FF;
		I2CParm.TrnData[11] = (ErrorParm.EndError & 0xFF00) >> 8;
			
		I2CParm.TrnData[12] = AutoRunParm.OutputState & 0x00FF;
		I2CParm.TrnData[13] = (AutoRunParm.OutputState & 0xFF00) >> 8;
	
		I2CParm.TrnData[14] = VerDateYear & 0x00FF;
		I2CParm.TrnData[15] = VerDe & 0xFF00;
		
		I2CParm.TrnData[16] = VerSoft & 0x00FF;
		I2CParm.TrnData[17] = (VerSoft & 0xFF00) >> 8;
		
		I2CParm.TrnData[18] = VerGTO & 0x00FF;
		I2CParm.TrnData[19] = (VerGTO & 0xFF00) >> 8;
		
		I2CParm.TrnData[20] = 0;
		I2CParm.TrnData[21] = 0;
			
		I2CParm.TrnData[22] = 0;
		I2CParm.TrnData[23] = 0xFF;
	
}


void I2CParmSave(void)
{
	
	
	for(AX_int_I2C = 0; AX_int_I2C < 126; AX_int_I2C ++)
	{
		
		AX_Unint_I2C = AX_int_I2C * 2;
		BX_int_I2C = I2CParm.RcvData[AX_Unint_I2C];
		BX_int_I2C = BX_int_I2C & 0x00FF;
		AX_Unint_I2C = AX_Unint_I2C + 1;
		CX_int_I2C = I2CParm.RcvData[AX_Unint_I2C];
		CX_int_I2C = CX_int_I2C << 8;
		CX_int_I2C = CX_int_I2C & 0xFF00;
		BX_int_I2C = BX_int_I2C | CX_int_I2C;
			
	
		EEPROMADDR = 0xF000 + 2 * AX_int_I2C;
        EraseEE(__builtin_tblpage(&EPConfigS[0]),EEPROMADDR, WORD);
        WriteEE(&BX_int_I2C,__builtin_tblpage(&EPConfigS[0]),EEPROMADDR, WORD);
	}
	
	asm("RESET");
	
}


