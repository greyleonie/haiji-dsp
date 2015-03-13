//海吉科技，HJR3000型智能软启动控制装置，DSPIC30F6010A系统
//并联串行通讯程序 Uart1.c

//头文件
#include "UserParms.h"	//用户系统配置，常数定义及配置值
#include "Function.h"	//系统外部调用函数声明，内部调用函数在对应文件内声明
#include "variable.h"	//系统全局变量声明，局部变量在对应文件内声明

int AX_int_Uart1 = 0, BX_int_Uart1 = 0;

void __attribute__((__interrupt__)) _U1RXInterrupt (void)
{
	Uart1Parm.RxCurData = U1RXREG;
	if(Uart1Parm.RxTimes == 0)
	{
		if(Uart1Parm.RxCurData == 0x00AA)
		{
			Uart1Parm.RxTimes = 1;
			
		}else Uart1Parm.RxTimes = 0;
	}else if(Uart1Parm.RxTimes == 1)
	{
		if(Uart1Parm.RxCurData == 0x0055)
		{
			Uart1Parm.RxTimes = 2;
			
		}else Uart1Parm.RxTimes = 0;
	}else if(Uart1Parm.RxTimes == 2)
	{
		Uart1Parm.RxData[2] = Uart1Parm.RxCurData;
		Uart1Parm.RxData[12] = Uart1Parm.RxData[2] + 0x00FF;
		Uart1Parm.RxTimes = 3;
	}else if(Uart1Parm.RxTimes == 3)
	{
		Uart1Parm.RxData[3] = Uart1Parm.RxCurData;
		Uart1Parm.RxData[12] = Uart1Parm.RxData[12] + Uart1Parm.RxData[3];
		Uart1Parm.RxTimes = 4;
	}else if(Uart1Parm.RxTimes == 4)
	{
		Uart1Parm.RxData[4] = Uart1Parm.RxCurData;
		Uart1Parm.RxData[12] = Uart1Parm.RxData[12] + Uart1Parm.RxData[4];
		Uart1Parm.RxTimes = 5;
	}else if(Uart1Parm.RxTimes == 5)
	{
		Uart1Parm.RxData[5] = Uart1Parm.RxCurData;
		Uart1Parm.RxData[12] = Uart1Parm.RxData[12] + Uart1Parm.RxData[5];
		Uart1Parm.RxTimes = 6;
	}else if(Uart1Parm.RxTimes == 6)
	{
		Uart1Parm.RxData[6] = Uart1Parm.RxCurData;
		Uart1Parm.RxData[12] = Uart1Parm.RxData[12] + Uart1Parm.RxData[6];
		Uart1Parm.RxTimes = 7;
	}else if(Uart1Parm.RxTimes == 7)
	{
		Uart1Parm.RxData[7] = Uart1Parm.RxCurData;
		Uart1Parm.RxData[12] = Uart1Parm.RxData[12] + Uart1Parm.RxData[7];
		Uart1Parm.RxTimes = 8;
	}else if(Uart1Parm.RxTimes == 8)
	{
		Uart1Parm.RxData[8] = Uart1Parm.RxCurData;
		Uart1Parm.RxData[12] = Uart1Parm.RxData[12] + Uart1Parm.RxData[8];
		Uart1Parm.RxTimes = 9;
	}else if(Uart1Parm.RxTimes == 9)
	{
		Uart1Parm.RxData[9] = Uart1Parm.RxCurData;
		Uart1Parm.RxData[12] = Uart1Parm.RxData[12] + Uart1Parm.RxData[9];
		Uart1Parm.RxTimes = 10;
	}else if(Uart1Parm.RxTimes == 10)
	{
		Uart1Parm.RxData[10] = Uart1Parm.RxCurData;
		Uart1Parm.RxData[12] = Uart1Parm.RxData[12] + Uart1Parm.RxData[10];
		Uart1Parm.RxTimes = 11;
	}else if(Uart1Parm.RxTimes == 11)
	{
		Uart1Parm.RxData[11] = Uart1Parm.RxCurData;
		Uart1Parm.RxData[12] = Uart1Parm.RxData[12] + Uart1Parm.RxData[11];
		Uart1Parm.RxTimes = 12;
	}else if(Uart1Parm.RxTimes == 12)
	{
		Uart1Parm.RxData[12] = Uart1Parm.RxData[12] & 0x00FF;
		if(Uart1Parm.RxData[12] == Uart1Parm.RxCurData)
		{
			Uart1State.UartRx = 1;
			Uart1Parm.AddrEnumerate	= 0;
		}
		Uart1Parm.RxTimes = 0;
	
	}else 
	{
		Uart1Parm.RxTimes = 0;
	}
		
	
	IFS0bits.U1RXIF = 0;
	return;
}

void __attribute__((__interrupt__)) _U1TXInterrupt (void)
{
	if(Uart1Parm.TxTimes == 0)
	{
		Uart1Parm.TxTimes = 1;
		Uart1Parm.TxCurData = Uart1Parm.TxData[Uart1Parm.TxTimes];
		U1TXREG = Uart1Parm.TxCurData;
		
	}else if(Uart1Parm.TxTimes == 1)
	{
		Uart1Parm.TxTimes = 2;
		Uart1Parm.TxCurData = Uart1Parm.TxData[Uart1Parm.TxTimes];
		U1TXREG = Uart1Parm.TxCurData;
	}else if(Uart1Parm.TxTimes == 2)
	{
		Uart1Parm.TxTimes = 3;
		Uart1Parm.TxCurData = Uart1Parm.TxData[Uart1Parm.TxTimes];
		U1TXREG = Uart1Parm.TxCurData;
	}else if(Uart1Parm.TxTimes == 3)
	{
		Uart1Parm.TxTimes = 4;
		Uart1Parm.TxCurData = Uart1Parm.TxData[Uart1Parm.TxTimes];
		U1TXREG = Uart1Parm.TxCurData;
	}else if(Uart1Parm.TxTimes == 4)
	{
		Uart1Parm.TxTimes = 5;
		Uart1Parm.TxCurData = Uart1Parm.TxData[Uart1Parm.TxTimes];
		U1TXREG = Uart1Parm.TxCurData;
	}else if(Uart1Parm.TxTimes == 5)
	{
		Uart1Parm.TxTimes = 6;
		Uart1Parm.TxCurData = Uart1Parm.TxData[Uart1Parm.TxTimes];
		U1TXREG = Uart1Parm.TxCurData;
	}else if(Uart1Parm.TxTimes == 6)
	{
		Uart1Parm.TxTimes = 7;
		Uart1Parm.TxCurData = Uart1Parm.TxData[Uart1Parm.TxTimes];
		U1TXREG = Uart1Parm.TxCurData;
	}else if(Uart1Parm.TxTimes == 7)
	{
		Uart1Parm.TxTimes = 8;
		Uart1Parm.TxCurData = Uart1Parm.TxData[Uart1Parm.TxTimes];
		U1TXREG = Uart1Parm.TxCurData;
	}else if(Uart1Parm.TxTimes == 8)
	{
		Uart1Parm.TxTimes = 9;
		Uart1Parm.TxCurData = Uart1Parm.TxData[Uart1Parm.TxTimes];
		U1TXREG = Uart1Parm.TxCurData;
	}else if(Uart1Parm.TxTimes == 9)
	{
		Uart1Parm.TxTimes = 10;
		Uart1Parm.TxCurData = Uart1Parm.TxData[Uart1Parm.TxTimes];
		U1TXREG = Uart1Parm.TxCurData;
	}else if(Uart1Parm.TxTimes == 10)
	{
		Uart1Parm.TxTimes = 11;
		Uart1Parm.TxCurData = Uart1Parm.TxData[Uart1Parm.TxTimes];
		U1TXREG = Uart1Parm.TxCurData;
	}else if(Uart1Parm.TxTimes == 11)
	{
		Uart1Parm.TxTimes = 12;
		Uart1Parm.TxCurData = Uart1Parm.TxData[Uart1Parm.TxTimes];
		U1TXREG = Uart1Parm.TxCurData;
	}else Uart1Parm.TxTimes = 250;
	
	
	IFS0bits.U1TXIF = 0;
	return;
	
}


void Uart1Tx(void)
{
	if(Uart1Parm.Addr == 0)
	{
		Uart1Parm.AddrEnumerate = Uart1Parm.AddrEnumerate + 1;
		if(Uart1Parm.AddrEnumerate > 1000)
		{
			Uart1Parm.AddrEnumerate = 0;
			Uart1TxData();
			Uart1State.UartTx = 1;
			Uart1State.UartTR = 0;
		}
	}
	
	if(Uart1State.UartTR == 1)
	{
		Uart1Parm.TxEnumerate = Uart1Parm.TxEnumerate + 1;
		if(Uart1Parm.TxEnumerate > 100)
		{
			Uart1Parm.TxEnumerate = 0;
			Uart1TxData();
			Uart1State.UartTx = 1;
			Uart1State.UartTR = 0;
			Uart1Parm.TxTimesEnumerate = Uart1Parm.TxTimesEnumerate + 1;
			if(Uart1Parm.TxTimesEnumerate > 3)
			{
				Uart1State.UartTx = 0;
				Uart1Parm.RunNumber = 0;
    			AutoRunParm.RunNumber = Uart1Parm.Addr - Uart1Parm.RunNumber;
    			Uart1Parm.TxTimesEnumerate = 0;
			}
		}
	}
				
	if(Uart1State.UartTxOff == 1)
	{
		if(U1STAbits.TRMT == 1)
		{
			Uart1State.UartTxOff = 0;
			Uart1State.UartTR = 1;
			Uart1Parm.TxEnumerate = 0;
		}
	}else
	{	
		if(Uart1State.UartTxOn == 1)
		{
			Uart1State.UartTxOff = 1;
			Uart1State.UartTxOn = 0;
	
			Uart1Parm.TxTimes = 0;
			Uart1Parm.TxCurData = Uart1Parm.TxData[Uart1Parm.TxTimes];
			U1TXREG = Uart1Parm.TxCurData;
		}else
		{
			if(Uart1State.UartTx == 1)
			{
			    Uart1State.UartTx = 0;
				LATFbits.LATF1 = 1;
				Uart1State.UartTxOn = 1;
			}else
			{
				LATFbits.LATF1 = 0;
			}
		}
	}
	
	if(Uart1State.UartRx == 1)
	{
		Uart1State.UartRx = 0;
		Uart1Parm.RxErrorEnumerate = 0;
		Uart1Parm.DataAddr = Uart1Parm.RxData[2];
		Uart1Parm.MainData[Uart1Parm.DataAddr] = Uart1Parm.RxData[4] + (Uart1Parm.RxData[5] * 256);
		Uart1Parm.BackupData[Uart1Parm.DataAddr] = Uart1Parm.RxData[6] + (Uart1Parm.RxData[7] * 256);
		Uart1Parm.ErrorData[Uart1Parm.DataAddr] = Uart1Parm.RxData[10] + (Uart1Parm.RxData[11] * 256);
		Uart1Parm.StateData[Uart1Parm.DataAddr] = Uart1Parm.RxData[8] + (Uart1Parm.RxData[9] * 256);
		if(Uart1State.Change == 1)
		{
			if(Uart1Parm.RunNumber == Uart1Parm.RxData[3])
				Uart1State.Change = 0;
		}else Uart1Parm.RunNumber = Uart1Parm.RxData[3];
			
		if(Uart1Parm.Addr < Uart1Parm.RunNumber)
			AutoRunParm.RunNumber = Uart1Parm.AddrMax + 1 + Uart1Parm.Addr - Uart1Parm.RunNumber;
		else AutoRunParm.RunNumber = Uart1Parm.Addr - Uart1Parm.RunNumber;
			
		if(AutoRunParm.RunNumber > Uart1Parm.AddrMax)
			AutoRunParm.RunNumber = Uart1Parm.AddrMax;
		
		AX_int_Uart1 = Uart1Parm.DataAddr + 1;
		if(AX_int_Uart1 > Uart1Parm.AddrMax)
			AX_int_Uart1 = 0;		
		if(Uart1Parm.Addr == AX_int_Uart1)
		{
			Uart1TxData();
			Uart1State.UartTx = 1;
			Uart1State.UartTR = 0;
		}else
		{
			AX_int_Uart1 = Uart1Parm.Addr + 1;
			if(AX_int_Uart1 > Uart1Parm.AddrMax)
				AX_int_Uart1 = 0;		
			if(Uart1Parm.DataAddr == AX_int_Uart1)
				Uart1State.UartTR = 0;
		}
		
		if(Uart1Parm.DataAddr == 0)
			Uart1State.UartTR = 0;
	}else
	{
		Uart1Parm.RxErrorEnumerate = Uart1Parm.RxErrorEnumerate + 1;
		if( Uart1Parm.RxErrorEnumerate > 6000 )
		{
			Uart1Parm.RunNumber = 0;
    		AutoRunParm.RunNumber = Uart1Parm.Addr - Uart1Parm.RunNumber;
    		Uart1Parm.RxErrorEnumerate = 6001;
    	}
    }	
	
}


void Uart1TxData(void)
{
	
			Uart1Parm.TxData[0] = 0xAA;
			Uart1Parm.TxData[1] = 0x55;
			Uart1Parm.TxData[2] = Uart1Parm.Addr & 0x00FF;
			Uart1Parm.TxData[12] = Uart1Parm.TxData[2] + 0x00FF; 
			Uart1Parm.TxData[3] = Uart1Parm.RunNumber & 0x00FF;
			Uart1Parm.TxData[12] = Uart1Parm.TxData[12] + Uart1Parm.TxData[3]; 
			Uart1Parm.TxData[4] = MeauParm.MainMeauCom & 0x00FF;
			Uart1Parm.TxData[12] = Uart1Parm.TxData[12] + Uart1Parm.TxData[4]; 
			Uart1Parm.TxData[5] = (MeauParm.MainMeauCom & 0xFF00) >> 8;
			Uart1Parm.TxData[12] = Uart1Parm.TxData[12] + Uart1Parm.TxData[5]; 
			Uart1Parm.TxData[6] = MeauParm.BackupMeau & 0x00FF;
			Uart1Parm.TxData[12] = Uart1Parm.TxData[12] + Uart1Parm.TxData[6]; 
			Uart1Parm.TxData[7] = (MeauParm.BackupMeau & 0xFF00) >> 8;
			Uart1Parm.TxData[12] = Uart1Parm.TxData[12] + Uart1Parm.TxData[7]; 
			Uart1Parm.TxData[8] = AutoRunParm.OutputState & 0x00FF;
			Uart1Parm.TxData[12] = Uart1Parm.TxData[12] + Uart1Parm.TxData[8]; 
			Uart1Parm.TxData[9] = (AutoRunParm.OutputState & 0xFF00) >> 8;
			Uart1Parm.TxData[12] = Uart1Parm.TxData[12] + Uart1Parm.TxData[9]; 
			Uart1Parm.TxData[10] = ErrorParm.EndError & 0x00FF;
			Uart1Parm.TxData[12] = Uart1Parm.TxData[12] + Uart1Parm.TxData[10]; 
			Uart1Parm.TxData[11] = (ErrorParm.EndError & 0xFF00) >> 8;
			Uart1Parm.TxData[12] = Uart1Parm.TxData[12] + Uart1Parm.TxData[11]; 
			Uart1Parm.RxData[12] = Uart1Parm.RxData[12] & 0x00FF;
			
}
