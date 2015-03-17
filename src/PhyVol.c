//海吉科技，HJR3000型智能软启动控制装置，DSPIC30F6010A系统
//电压同步信号处理，PhyVol.c

//头文件
#include "UserParms.h"	//用户系统配置，常数定义及配置值
#include "Function.h"	//系统外部调用函数声明，内部调用函数在对应文件内声明
#include "variable.h"	//系统全局变量声明，局部变量在对应文件内声明

int AX_int_IC = 0;

void __attribute__((__interrupt__)) _IC1Interrupt (void)
{
	while(IC1CONbits.ICBNE == 1)
	{
		ICParms.EndTimeIC1 = IC1BUF;
	}
	
	ICParms.EndTimeIC1 = IC1BUF;
		
	AX_int_IC = ICParms.EndTimeIC1 - ICParms.StartTimeIC1;
	if(AX_int_IC < 0)
		AX_int_IC = - AX_int_IC;
	if(AX_int_IC > 450)
	{
		if(PORTDbits.RD8 == 0)
			PwmState.UoutPhyH = 1;
		else PwmState.UoutPhyL = 1;
		
		ErrorParm.DisconEnumerateU = 0;
			
		ICParms.CurTimeIC1 = ICParms.EndTimeIC1;
		if(ICParms.EndTimeIC3 != ICParms.OldTimeIC3)
		{
			AX_int_IC = ICParms.CurTimeIC1 - ICParms.CurTimeIC2;
			
			if(AX_int_IC < 0)
				AX_int_IC = - AX_int_IC;
			if(AX_int_IC > 100)
			{
				if(AX_int_IC < 450)
					ErrorParm.DisconEnumerateVW = 0;
			}
		}
		if(ICParms.EndTimeIC2 != ICParms.OldTimeIC2)
		{		
			AX_int_IC = ICParms.CurTimeIC3 - ICParms.CurTimeIC1;
			if(AX_int_IC < 0)
				AX_int_IC = - AX_int_IC;
			if(AX_int_IC > 100)
			{
				if(AX_int_IC < 450)
					ErrorParm.DisconEnumerateWU = 0;
			}	
		}
		
		AX_int_IC = ICParms.CurTimeIC2 - ICParms.CurTimeIC3;
		if(AX_int_IC < 0)
			AX_int_IC = - AX_int_IC;
		if(AX_int_IC > 100)
		{
			if(AX_int_IC < 450)
				ErrorParm.DisconEnumerateUV = 0;
		}
			
	}
		
	
	ICParms.StartTimeIC1 = ICParms.EndTimeIC1;
	
	IFS0bits.IC1IF = 0;              //清零中断标志
	return;
}
	
void __attribute__((__interrupt__)) _IC2Interrupt (void)
{
	while(IC2CONbits.ICBNE == 1)
	{
		ICParms.EndTimeIC2 = IC2BUF;
	}
	ICParms.EndTimeIC2 = IC2BUF;
	ICParms.OldTimeIC2 = ICParms.StartTimeIC2;
	
	AX_int_IC = ICParms.EndTimeIC2 - ICParms.StartTimeIC2;
	if(AX_int_IC < 0)
		AX_int_IC = - AX_int_IC;
	if(AX_int_IC > 450)
	{
		if(PORTDbits.RD9 == 0)
			PwmState.VoutPhyH = 1;
		else PwmState.VoutPhyL = 1;
		ErrorParm.DisconEnumerateV = 0;
		
		ICParms.CurTimeIC2 = ICParms.EndTimeIC2;
	}
	ICParms.StartTimeIC2 = ICParms.EndTimeIC2;
	
	IFS0bits.IC2IF = 0;              //清零中断标志
	return;
}


void __attribute__((__interrupt__)) _IC3Interrupt (void)
{
	while(IC3CONbits.ICBNE == 1)
	{
		ICParms.EndTimeIC3 = IC3BUF;
	}
	ICParms.EndTimeIC3 = IC3BUF;
	ICParms.OldTimeIC3 = ICParms.StartTimeIC3;
	
	AX_int_IC = ICParms.EndTimeIC3 - ICParms.StartTimeIC3;
	if(AX_int_IC < 0)
		AX_int_IC = - AX_int_IC;
	if(AX_int_IC > 450)
	{
		if(PORTDbits.RD10 == 0)
			PwmState.WoutPhyH = 1;
		else PwmState.WoutPhyL = 1;
		ErrorParm.DisconEnumerateW = 0;
		
		ICParms.CurTimeIC3 = ICParms.EndTimeIC3;
	}
	ICParms.StartTimeIC3 = ICParms.EndTimeIC3;
	
	IFS1bits.IC3IF = 0;              //清零中断标志
	return;
}


void __attribute__((__interrupt__)) _IC4Interrupt (void)
{
	while(IC4CONbits.ICBNE == 1)
	{
		//ICParms.EndTimeIC3 = IC4BUF;
	}
	
	
	
	IFS1bits.IC4IF = 0;              //清零中断标志
	return;
}
