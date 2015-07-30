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

unsigned int AX_int_Uart = 0, BX_int_Uart = 0;
unsigned char AX_char_Uart = 0,BX_char_Uart = 0;

void __attribute__((__interrupt__)) _U2RXInterrupt (void)
{
	Uart2Parm.RxCurData = U2RXREG;
	modbus_receive(Uart2Parm.RxCurData);

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

	IFS1bits.U2TXIF = 0;
	return;
}

void Uart2Tx(void)
{
	modbus_slave();				
}

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

