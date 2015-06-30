#include "UserParms.h"	//用户系统配置，常数定义及配置�?
#include "Function.h"	//系统外部调用函数声明，内部调用函数在对应文件内声�?
#include "variable.h"	//系统全局变量声明，局部变量在对应文件内声�?

extern void modbus_reset(void);

void timer4_init(void)
{
 	T4CON = 0;
    T4CONbits.TSIDL = 1;        // 空闲模式下停止工�?  
    TMR4 = 0;          			// clear timer1 register 
    PR4 = ((dFcy * 3.5 * 10) / Uart2Parm.dBaudRate); 	// set period1 register 
    T4CONbits.TCS = 0; 			// set internal clock source 
    IPC5bits.T4IP = 5; 			// set priority level 
    IFS1bits.T4IF = 0; 			//clear interrupt flag 
    IEC1bits.T4IE = 1; 			// enable interrupts 
}

void timer4_reset(void)
{
	T4CONbits.TON = 0;
	TMR4 = 0;
	T4CONbits.TON = 1;
}

void timer4_stop(void)
{
	T4CONbits.TON = 0;
}

void __attribute__((__interrupt__)) _T4Interrupt(void)
{
	IFS1bits.T4IF = 0;
	T4CONbits.TON = 0;
	modbus_reset();
}


