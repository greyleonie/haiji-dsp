//海吉科技，HJR3000型智能软启动控制装置，DSPIC30F6010A系统
//主控制文件，T1_CTRL.c

//头文件
#include "UserParms.h"	//用户系统配置，常数定义及配置值
#include "Function.h"	//系统外部调用函数声明，内部调用函数在对应文件内声明
#include "variable.h"	//系统全局变量声明，局部变量在对应文件内声明

//系统调试模式
void SysTest(void)
{
	if(PORTGbits.RG6 == 0)
	{
		SysTestState.Phy = ! SysTestState.Phy;
		if(SysTestState.Phy == 1)
		{
			PwmState.UoutPhyH = ! PwmState.UoutPhyH;
			PwmState.UoutPhyL = ! PwmState.UoutPhyL;
			PwmState.VoutPhyH = ! PwmState.VoutPhyH;
			PwmState.VoutPhyL = ! PwmState.VoutPhyL;
			PwmState.WoutPhyH = ! PwmState.WoutPhyH;
			PwmState.WoutPhyL = ! PwmState.WoutPhyL;
		}
       
       	if(InputState.Stop == 1)
		{
			StopPWM();
		}
			
			
		if(InsideIOState.Men == 1)
		{
			SoftRunParms.Data = DataMax;
			SoftRunParms.OutData = 0;
			PwmState.StartOut = 1;
			StarPWM();
		}
			
	}
	
	
}
