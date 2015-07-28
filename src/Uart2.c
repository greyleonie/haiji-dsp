//海吉科技，HJR3000型智能软启动控制装置，DSPIC30F6010A系统
//接口串行通讯程序 Uart2.c

//头文�?
#include "UserParms.h"	//用户系统配置，常数定义及配置�?
#include "Function.h"	//系统外部调用函数声明，内部调用函数在对应文件内声�?
#include "variable.h"	//系统全局变量声明，局部变量在对应文件内声�?

extern void modbus_receive(unsigned char c);
extern void modbus_slave(void);
extern char modbus_send();
extern char modbus_is_send_done(void);
extern void modbus_send_done(void);
void UartCRC(unsigned int DataCRC);

unsigned int AX_int_Uart = 0, BX_int_Uart = 0;
unsigned char AX_char_Uart = 0,BX_char_Uart = 0;

void __attribute__((__interrupt__)) _U2RXInterrupt (void)
{
	Uart2Parm.RxCurData = U2RXREG;
	modbus_receive(Uart2Parm.RxCurData);
/*
	if(Uart2Parm.RxTimes == 0)
	{
		if(Uart2Parm.RxCurData == Uart2Parm.Addr)
		{
			Uart2Parm.RxTimes = 1;
			Uart2Parm.UartCRC = 0xFFFF;
			UartCRC(Uart2Parm.RxCurData);
		}else Uart2Parm.RxTimes = 0;
	}else if(Uart2Parm.RxTimes == 1)
	{
		if(Uart2Parm.RxCurData == 3)
		{
			Uart2Parm.RxTimes = 10;
			UartCRC(Uart2Parm.RxCurData);
		}else if(Uart2Parm.RxCurData == 6)
		{
			Uart2Parm.RxTimes = 20;
			UartCRC(Uart2Parm.RxCurData);
		}else Uart2Parm.RxTimes = 0;
	}else if(Uart2Parm.RxTimes == 10)
	{
		Uart2Parm.DataAddrH = Uart2Parm.RxCurData;
		UartCRC(Uart2Parm.RxCurData);
		Uart2Parm.RxTimes = 11;
	}else if(Uart2Parm.RxTimes == 11)
	{
		Uart2Parm.DataAddrL = Uart2Parm.RxCurData;
		UartCRC(Uart2Parm.RxCurData);
		Uart2Parm.RxTimes = 12;
	}else if(Uart2Parm.RxTimes == 12)
	{
		Uart2Parm.LowCRC = Uart2Parm.RxCurData;
		Uart2Parm.RxTimes = 13;
	}else if(Uart2Parm.RxTimes == 13)
	{
		Uart2Parm.HighCRC = Uart2Parm.RxCurData;
		Uart2Parm.HighCRC = Uart2Parm.HighCRC << 8;
		Uart2Parm.HighCRC = Uart2Parm.HighCRC + Uart2Parm.LowCRC;	
		Uart2Parm.RxTimes = 0;
	//	if(Uart2Parm.HighCRC == Uart2Parm.UartCRC)
			MainState.UartRx = 1;	//成功接收到读命令，需要发送响应数�?
	}else if(Uart2Parm.RxTimes == 20)
	{
		if(Uart2Parm.RxCurData == 0)
		{
			Uart2Parm.RxTimes = 21;
			UartCRC(Uart2Parm.RxCurData);
		}else Uart2Parm.RxTimes = 0;
	}else if(Uart2Parm.RxTimes == 21)
	{
		Uart2Parm.KeyParamAddr = Uart2Parm.RxCurData;
		UartCRC(Uart2Parm.RxCurData);
		Uart2Parm.RxTimes = 22;
	}else if(Uart2Parm.RxTimes == 22)
	{
		Uart2Parm.KeyParamDataH = Uart2Parm.RxCurData;
		UartCRC(Uart2Parm.RxCurData);
		Uart2Parm.RxTimes = 23;
	}else if(Uart2Parm.RxTimes == 23)
	{
		Uart2Parm.KeyParamDataL = Uart2Parm.RxCurData;
		UartCRC(Uart2Parm.RxCurData);
		Uart2Parm.RxTimes = 24;
	}else if(Uart2Parm.RxTimes == 24)
	{
		Uart2Parm.LowCRC = Uart2Parm.RxCurData;
		Uart2Parm.RxTimes = 25;
	}else if(Uart2Parm.RxTimes == 25)
	{
		Uart2Parm.HighCRC = Uart2Parm.RxCurData;
		Uart2Parm.HighCRC = Uart2Parm.HighCRC << 8;
		Uart2Parm.HighCRC = Uart2Parm.HighCRC + Uart2Parm.LowCRC;	
		Uart2Parm.RxTimes = 0;
		if(Uart2Parm.HighCRC == Uart2Parm.UartCRC)
		{
			Uart2Parm.KeyParamDataL = Uart2Parm.KeyParamDataL + (Uart2Parm.KeyParamDataH * 256);
			KeyParm.SaveParms[Uart2Parm.KeyParamAddr] = Uart2Parm.KeyParamDataL;
			EEPROMADDR = 0xF000 + 2 * Uart2Parm.KeyParamAddr;
       		EraseEE(__builtin_tblpage(&EPConfigS[0]),EEPROMADDR, WORD);
      		WriteEE(&KeyParm.SaveParms[Uart2Parm.KeyParamAddr],__builtin_tblpage(&EPConfigS[0]),EEPROMADDR, WORD);
		}
	}else 
	{
		Uart2Parm.RxTimes = 0;
	}
		
//*/	
	
	IFS1bits.U2RXIF = 0;
	return;
}


void __attribute__((__interrupt__)) _U2TXInterrupt (void)
{
	if (!modbus_is_send_done()) {
		U2TXREG = modbus_send();
	} else {
		modbus_send_done();
	}
/*
	if(Uart2Parm.TxTimes == 0)
	{
		Uart2Parm.TxTimes = 1;
		Uart2Parm.TxCurData = Uart2Parm.TxData[Uart2Parm.TxTimes];
		U2TXREG = Uart2Parm.TxCurData;
		
	}else if(Uart2Parm.TxTimes == 1)
	{
		Uart2Parm.TxTimes = 2;
		Uart2Parm.TxCurData = Uart2Parm.TxData[Uart2Parm.TxTimes];
		U2TXREG = Uart2Parm.TxCurData;
	}else if(Uart2Parm.TxTimes == 2)
	{
		Uart2Parm.TxTimes = 3;
		Uart2Parm.TxCurData = Uart2Parm.TxData[Uart2Parm.TxTimes];
		U2TXREG = Uart2Parm.TxCurData;
	}else if(Uart2Parm.TxTimes == 3)
	{
		Uart2Parm.TxTimes = 4;
		Uart2Parm.TxCurData = Uart2Parm.TxData[Uart2Parm.TxTimes];
		U2TXREG = Uart2Parm.TxCurData;
	}else if(Uart2Parm.TxTimes == 4)
	{
		Uart2Parm.TxTimes = 5;
		Uart2Parm.TxCurData = Uart2Parm.TxData[Uart2Parm.TxTimes];
		U2TXREG = Uart2Parm.TxCurData;
	}else Uart2Parm.TxTimes = 250;
//*/	
	
	IFS1bits.U2TXIF = 0;
	return;
	
}


void Uart2Tx(void)
{
	modbus_slave();
	//判断系统是否处于等待UART发送结束的状�?
/*	if(MainState.UartTxOff == 1)	
	{
		//检查UART2发送结束标志是否置1
		if(U2STAbits.TRMT == 1)		
		{
			//系统退出等待UART发送结束的状�?
			MainState.UartTxOff = 0;	
			
		}
	}else
	{	
		//系统处于未发送状态，检查UART数据发送是否开�?
		if(MainState.UartTxOn == 1)
		{
			//UART数据开始发送，数据发送结束检查标志置1
			MainState.UartTxOff = 1;
			//清除判断标志
			MainState.UartTxOn = 0;
			//将数据写入UART发送寄存器
			Uart2Parm.TxTimes = 0;
			Uart2Parm.TxCurData = Uart2Parm.TxData[Uart2Parm.TxTimes];
			U2TXREG = Uart2Parm.TxCurData;
					
		}else
		{
			//检查是否有数据需要通过UART发�?
			if(MainState.UartTx == 1)
			{
				//清空判断标志�?
			    MainState.UartTx = 0;
				//通用端口F0�?
				LATFbits.LATF0 = 1;
				//开启UART数据发�?
				MainState.UartTxOn = 1;
			}else
			{
				//通用端口F0�?
				LATFbits.LATF0 = 0;
			}
		}
	}
//*/
	//检查是否需要发送响应数�?
/*	if(MainState.UartRx == 1)
	{
		MainState.UartRx = 0;
		Uart2Parm.TxData[0] = Uart2Parm.Addr;
		Uart2Parm.TxData[1] = 3;
		
		Uart2Parm.DataAddrH = Uart2Parm.DataAddrH << 8;
		Uart2Parm.DataAddrH = Uart2Parm.DataAddrH & 0xFF00;
		Uart2Parm.DataAddrL = Uart2Parm.DataAddrL & 0x00FF;
		Uart2Parm.DataAddrL = Uart2Parm.DataAddrL | Uart2Parm.DataAddrH;
		
		if(Uart2Parm.DataAddrL == 0x0001)
		{
			Uart2Parm.TxData[3] = MeauParm.MainMeau & 0x00FF;
			Uart2Parm.TxData[2] = (MeauParm.MainMeau & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0002)
		{
			Uart2Parm.TxData[3] = MeauParm.BackupMeau & 0x00FF;
			Uart2Parm.TxData[2] = (MeauParm.BackupMeau & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0003)
		{
			Uart2Parm.TxData[3] = CurParms.IU & 0x00FF;
			Uart2Parm.TxData[2] = (CurParms.IU & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0004)
		{
			Uart2Parm.TxData[3] = CurParms.IV & 0x00FF;
			Uart2Parm.TxData[2] = (CurParms.IV & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0005)
		{
			Uart2Parm.TxData[3] = CurParms.IW & 0x00FF;
			Uart2Parm.TxData[2] = (CurParms.IW & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0006)
		{
			Uart2Parm.TxData[3] = VolParms.Uin & 0x00FF;
			Uart2Parm.TxData[2] = (VolParms.Uin & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0007)
		{
			Uart2Parm.TxData[3] = ErrorParm.EndError & 0x00FF;
			Uart2Parm.TxData[2] = (ErrorParm.EndError & 0x8F00) >> 8;                   //通讯屏蔽断相   2014.4.14    0XFF00改为0X8F00
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0008)
		{
			Uart2Parm.TxData[3] = AutoRunParm.OutputState & 0x00FF;
			Uart2Parm.TxData[2] = (AutoRunParm.OutputState & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if((Uart2Parm.DataAddrL > 0x000F) && (Uart2Parm.DataAddrL < 0x0090))
		{
			AX_int_Uart = Uart2Parm.DataAddrL - 0x0010;
			Uart2Parm.TxData[3] = KeyParm.SaveParms[AX_int_Uart] & 0x00FF;
			Uart2Parm.TxData[2] = (KeyParm.SaveParms[AX_int_Uart] & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0101)
		{
			Uart2Parm.TxData[3] = Uart1Parm.MainData[0x0000] & 0x00FF;
			Uart2Parm.TxData[2] = (Uart1Parm.MainData[0x0000] & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0102)
		{
			Uart2Parm.TxData[3] = Uart1Parm.BackupData[0x0000] & 0x00FF;
			Uart2Parm.TxData[2] = (Uart1Parm.BackupData[0x0000] & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0103)
		{
			Uart2Parm.TxData[3] = CurParms.IU & 0x00FF;
			Uart2Parm.TxData[2] = (CurParms.IU & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0104)
		{
			Uart2Parm.TxData[3] = CurParms.IV & 0x00FF;
			Uart2Parm.TxData[2] = (CurParms.IV & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0105)
		{
			Uart2Parm.TxData[3] = CurParms.IW & 0x00FF;
			Uart2Parm.TxData[2] = (CurParms.IW & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0106)
		{
			Uart2Parm.TxData[3] = VolParms.Uin & 0x00FF;
			Uart2Parm.TxData[2] = (VolParms.Uin & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0107)
		{
			Uart2Parm.TxData[3] = Uart1Parm.ErrorData[0x0000] & 0x00FF;
			Uart2Parm.TxData[2] = (Uart1Parm.ErrorData[0x0000] & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0108)
		{
			Uart2Parm.TxData[3] = Uart1Parm.StateData[0x0000] & 0x00FF;
			Uart2Parm.TxData[2] = (Uart1Parm.StateData[0x0000] & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0201)
		{
			Uart2Parm.TxData[3] = Uart1Parm.MainData[0x0001] & 0x00FF;
			Uart2Parm.TxData[2] = (Uart1Parm.MainData[0x0001] & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0202)
		{
			Uart2Parm.TxData[3] = Uart1Parm.BackupData[0x0001] & 0x00FF;
			Uart2Parm.TxData[2] = (Uart1Parm.BackupData[0x0001] & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0203)
		{
			Uart2Parm.TxData[3] = CurParms.IU & 0x00FF;
			Uart2Parm.TxData[2] = (CurParms.IU & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0204)
		{
			Uart2Parm.TxData[3] = CurParms.IV & 0x00FF;
			Uart2Parm.TxData[2] = (CurParms.IV & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0205)
		{
			Uart2Parm.TxData[3] = CurParms.IW & 0x00FF;
			Uart2Parm.TxData[2] = (CurParms.IW & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0206)
		{
			Uart2Parm.TxData[3] = VolParms.Uin & 0x00FF;
			Uart2Parm.TxData[2] = (VolParms.Uin & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0207)
		{
			Uart2Parm.TxData[3] = Uart1Parm.ErrorData[0x0001] & 0x00FF;
			Uart2Parm.TxData[2] = (Uart1Parm.ErrorData[0x0001] & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0208)
		{
			Uart2Parm.TxData[3] = Uart1Parm.StateData[0x0001] & 0x00FF;
			Uart2Parm.TxData[2] = (Uart1Parm.StateData[0x0001] & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0301)
		{
			Uart2Parm.TxData[3] = Uart1Parm.MainData[0x0002] & 0x00FF;
			Uart2Parm.TxData[2] = (Uart1Parm.MainData[0x0002] & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0302)
		{
			Uart2Parm.TxData[3] = Uart1Parm.BackupData[0x0002] & 0x00FF;
			Uart2Parm.TxData[2] = (Uart1Parm.BackupData[0x0002] & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0303)
		{
			Uart2Parm.TxData[3] = CurParms.IU & 0x00FF;
			Uart2Parm.TxData[2] = (CurParms.IU & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0304)
		{
			Uart2Parm.TxData[3] = CurParms.IV & 0x00FF;
			Uart2Parm.TxData[2] = (CurParms.IV & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0305)
		{
			Uart2Parm.TxData[3] = CurParms.IW & 0x00FF;
			Uart2Parm.TxData[2] = (CurParms.IW & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0306)
		{
			Uart2Parm.TxData[3] = VolParms.Uin & 0x00FF;
			Uart2Parm.TxData[2] = (VolParms.Uin & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0307)
		{
			Uart2Parm.TxData[3] = Uart1Parm.ErrorData[0x0002] & 0x00FF;
			Uart2Parm.TxData[2] = (Uart1Parm.ErrorData[0x0002] & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0308)
		{
			Uart2Parm.TxData[3] = Uart1Parm.StateData[0x0002] & 0x00FF;
			Uart2Parm.TxData[2] = (Uart1Parm.StateData[0x0002] & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0401)
		{
			Uart2Parm.TxData[3] = Uart1Parm.MainData[0x0003] & 0x00FF;
			Uart2Parm.TxData[2] = (Uart1Parm.MainData[0x0003] & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0402)
		{
			Uart2Parm.TxData[3] = Uart1Parm.BackupData[0x0003] & 0x00FF;
			Uart2Parm.TxData[2] = (Uart1Parm.BackupData[0x0003] & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0403)
		{
			Uart2Parm.TxData[3] = CurParms.IU & 0x00FF;
			Uart2Parm.TxData[2] = (CurParms.IU & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0404)
		{
			Uart2Parm.TxData[3] = CurParms.IV & 0x00FF;
			Uart2Parm.TxData[2] = (CurParms.IV & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0405)
		{
			Uart2Parm.TxData[3] = CurParms.IW & 0x00FF;
			Uart2Parm.TxData[2] = (CurParms.IW & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0406)
		{
			Uart2Parm.TxData[3] = VolParms.Uin & 0x00FF;
			Uart2Parm.TxData[2] = (VolParms.Uin & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0407)
		{
			Uart2Parm.TxData[3] = Uart1Parm.ErrorData[0x0003] & 0x00FF;
			Uart2Parm.TxData[2] = (Uart1Parm.ErrorData[0x0003] & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0408)
		{
			Uart2Parm.TxData[3] = Uart1Parm.StateData[0x0001] & 0x00FF;
			Uart2Parm.TxData[2] = (Uart1Parm.StateData[0x0001] & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0501)
		{
			Uart2Parm.TxData[3] = Uart1Parm.MainData[0x0004] & 0x00FF;
			Uart2Parm.TxData[2] = (Uart1Parm.MainData[0x0004] & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0502)
		{
			Uart2Parm.TxData[3] = Uart1Parm.BackupData[0x0004] & 0x00FF;
			Uart2Parm.TxData[2] = (Uart1Parm.BackupData[0x0004] & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0503)
		{
			Uart2Parm.TxData[3] = CurParms.IU & 0x00FF;
			Uart2Parm.TxData[2] = (CurParms.IU & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0504)
		{
			Uart2Parm.TxData[3] = CurParms.IV & 0x00FF;
			Uart2Parm.TxData[2] = (CurParms.IV & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0505)
		{
			Uart2Parm.TxData[3] = CurParms.IW & 0x00FF;
			Uart2Parm.TxData[2] = (CurParms.IW & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0506)
		{
			Uart2Parm.TxData[3] = VolParms.Uin & 0x00FF;
			Uart2Parm.TxData[2] = (VolParms.Uin & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0507)
		{
			Uart2Parm.TxData[3] = Uart1Parm.ErrorData[0x0001] & 0x00FF;
			Uart2Parm.TxData[2] = (Uart1Parm.ErrorData[0x0001] & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0508)
		{
			Uart2Parm.TxData[3] = Uart1Parm.StateData[0x0004] & 0x00FF;
			Uart2Parm.TxData[2] = (Uart1Parm.StateData[0x0004] & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0601)
		{
			Uart2Parm.TxData[3] = Uart1Parm.MainData[0x0005] & 0x00FF;
			Uart2Parm.TxData[2] = (Uart1Parm.MainData[0x0005] & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0602)
		{
			Uart2Parm.TxData[3] = Uart1Parm.BackupData[0x0005] & 0x00FF;
			Uart2Parm.TxData[2] = (Uart1Parm.BackupData[0x0005] & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0603)
		{
			Uart2Parm.TxData[3] = CurParms.IU & 0x00FF;
			Uart2Parm.TxData[2] = (CurParms.IU & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0604)
		{
			Uart2Parm.TxData[3] = CurParms.IV & 0x00FF;
			Uart2Parm.TxData[2] = (CurParms.IV & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0605)
		{
			Uart2Parm.TxData[3] = CurParms.IW & 0x00FF;
			Uart2Parm.TxData[2] = (CurParms.IW & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0606)
		{
			Uart2Parm.TxData[3] = VolParms.Uin & 0x00FF;
			Uart2Parm.TxData[2] = (VolParms.Uin & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0607)
		{
			Uart2Parm.TxData[3] = Uart1Parm.ErrorData[0x0005] & 0x00FF;
			Uart2Parm.TxData[2] = (Uart1Parm.ErrorData[0x0005] & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0608)
		{
			Uart2Parm.TxData[3] = Uart1Parm.StateData[0x0005] & 0x00FF;
			Uart2Parm.TxData[2] = (Uart1Parm.StateData[0x0005] & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0701)
		{
			Uart2Parm.TxData[3] = Uart1Parm.MainData[0x0006] & 0x00FF;
			Uart2Parm.TxData[2] = (Uart1Parm.MainData[0x0006] & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0702)
		{
			Uart2Parm.TxData[3] = Uart1Parm.BackupData[0x0006] & 0x00FF;
			Uart2Parm.TxData[2] = (Uart1Parm.BackupData[0x0006] & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0703)
		{
			Uart2Parm.TxData[3] = CurParms.IU & 0x00FF;
			Uart2Parm.TxData[2] = (CurParms.IU & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0704)
		{
			Uart2Parm.TxData[3] = CurParms.IV & 0x00FF;
			Uart2Parm.TxData[2] = (CurParms.IV & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0705)
		{
			Uart2Parm.TxData[3] = CurParms.IW & 0x00FF;
			Uart2Parm.TxData[2] = (CurParms.IW & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0706)
		{
			Uart2Parm.TxData[3] = VolParms.Uin & 0x00FF;
			Uart2Parm.TxData[2] = (VolParms.Uin & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0707)
		{
			Uart2Parm.TxData[3] = Uart1Parm.ErrorData[0x0006] & 0x00FF;
			Uart2Parm.TxData[2] = (Uart1Parm.ErrorData[0x0006] & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0708)
		{
			Uart2Parm.TxData[3] = Uart1Parm.StateData[0x0006] & 0x00FF;
			Uart2Parm.TxData[2] = (Uart1Parm.StateData[0x0006] & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0801)
		{
			Uart2Parm.TxData[3] = Uart1Parm.MainData[0x0007] & 0x00FF;
			Uart2Parm.TxData[2] = (Uart1Parm.MainData[0x0007] & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0802)
		{
			Uart2Parm.TxData[3] = Uart1Parm.BackupData[0x0007] & 0x00FF;
			Uart2Parm.TxData[2] = (Uart1Parm.BackupData[0x0007] & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0803)
		{
			Uart2Parm.TxData[3] = CurParms.IU & 0x00FF;
			Uart2Parm.TxData[2] = (CurParms.IU & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0804)
		{
			Uart2Parm.TxData[3] = CurParms.IV & 0x00FF;
			Uart2Parm.TxData[2] = (CurParms.IV & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0805)
		{
			Uart2Parm.TxData[3] = CurParms.IW & 0x00FF;
			Uart2Parm.TxData[2] = (CurParms.IW & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0806)
		{
			Uart2Parm.TxData[3] = VolParms.Uin & 0x00FF;
			Uart2Parm.TxData[2] = (VolParms.Uin & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0807)
		{
			Uart2Parm.TxData[3] = Uart1Parm.ErrorData[0x0007] & 0x00FF;
			Uart2Parm.TxData[2] = (Uart1Parm.ErrorData[0x0007] & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}else if(Uart2Parm.DataAddrL == 0x0808)
		{
			Uart2Parm.TxData[3] = Uart1Parm.StateData[0x0007] & 0x00FF;
			Uart2Parm.TxData[2] = (Uart1Parm.StateData[0x0007] & 0xFF00) >> 8;
			MainState.UartTx = 1;
		}
		
		Uart2Parm.UartCRC = 0xFFFF;
		UartCRC(Uart2Parm.TxData[0]);
		UartCRC(Uart2Parm.TxData[1]);
		UartCRC(Uart2Parm.TxData[2]);
		UartCRC(Uart2Parm.TxData[3]);
		AX_int_Uart = Uart2Parm.UartCRC;
		
		Uart2Parm.TxData[4] = AX_int_Uart & 0x00FF;
		Uart2Parm.TxData[5] = (AX_int_Uart & 0xFF00) >> 8;
		
		
	}	
			
//*/				
}
/*
void UartCRC(unsigned int DataCRC)
{
	Uart2Parm.UartCRC = Uart2Parm.UartCRC ^ DataCRC;
		
	for(AX_int_Uart = 0; AX_int_Uart < 8 ; AX_int_Uart ++)
	{
		BX_int_Uart = Uart2Parm.UartCRC & 0x0001;
		Uart2Parm.UartCRC = Uart2Parm.UartCRC >> 1;
		Uart2Parm.UartCRC = Uart2Parm.UartCRC & 0x7FFF;
		if(BX_int_Uart == 1)
		{
			Uart2Parm.UartCRC = Uart2Parm.UartCRC ^ 0xA001;
		}
	}
}
//*/
void Uart2TxSend(unsigned char c)
{
	U2TXREG = c;
}

void Uart2TxEn(void)
{
	LATFbits.LATF0 = 1;
}

void Uart2TxDis(void)
{
	LATFbits.LATF0 = 0;
}

