//海吉科技，HJR3000型智能软启动控制装置，DSPIC30F6010A系统
//电压同步信号处理，PhyVol.c

//头文件
#include "UserParms.h"	//用户系统配置，常数定义及配置值
#include "Function.h"	//系统外部调用函数声明，内部调用函数在对应文件内声明
#include "variable.h"	//系统全局变量声明，局部变量在对应文件内声明


//4－20mA输出OC1，OC2
void OutputDA(void)
{
	
	switch(DaOutParm.DaOutput1)
	{
		case 0:
			DaOutParm.OutData1 = ( (long) MeauParm.MainMeau * DaOutParm.OutData1Mul) >> 10;
			DaOutParm.OutData1 = DaOutParm.OutData1 + DaOutParm.OutData1Add;
			break;
		case 1:
			DaOutParm.OutData1 = ( (long) MeauParm.BackupMeau * DaOutParm.OutData1Mul) >> 10;
			DaOutParm.OutData1 = DaOutParm.OutData1 + DaOutParm.OutData1Add;
			break;
		case 2:
			DaOutParm.OutData1 = ( (long) CurParms.IUVW * DaOutParm.OutData1Mul) >> 10;
			DaOutParm.OutData1 = DaOutParm.OutData1 + DaOutParm.OutData1Add;
			break;
		default:
			DaOutParm.OutData1 = ( (long) MeauParm.MainMeau * DaOutParm.OutData1Mul) >> 10;
			DaOutParm.OutData1 = DaOutParm.OutData1 + DaOutParm.OutData1Add;
			break;
	}
	
	switch(DaOutParm.DaOutput2)
	{
		case 0:
			DaOutParm.OutData2 = ( (long) MeauParm.MainMeau * DaOutParm.OutData2Mul) >> 10;
			DaOutParm.OutData2 = DaOutParm.OutData2 + DaOutParm.OutData2Add;
			break;
		case 1:
			DaOutParm.OutData2 = ( (long) MeauParm.BackupMeau * DaOutParm.OutData2Mul) >> 10;
			DaOutParm.OutData2 = DaOutParm.OutData2 + DaOutParm.OutData2Add;
			break;
		case 2:
			DaOutParm.OutData2 = ( (long) CurParms.IUVW * DaOutParm.OutData2Mul) >> 10;
			DaOutParm.OutData2 = DaOutParm.OutData2 + DaOutParm.OutData2Add;
			break;
		default:
			DaOutParm.OutData2 = ( (long) MeauParm.BackupMeau * DaOutParm.OutData2Mul) >> 10;
			DaOutParm.OutData2 = DaOutParm.OutData2 + DaOutParm.OutData2Add;
			break;
	}
	
	if(DaOutParm.OutData1 > 0x0FF0)
		DaOutParm.OutData1 = 0x0FF0;
	else if(DaOutParm.OutData1 < 0x000F)
		DaOutParm.OutData1 = 0x000F;
	
	if(DaOutParm.OutData2 > 0x0FF0)
		DaOutParm.OutData2 = 0x0FF0;
	else if(DaOutParm.OutData2 < 0x000F)
		DaOutParm.OutData2 = 0x000F;

	OC2R = 0x0FFF - DaOutParm.OutData1;
	OC2RS = 0x0FFE;

	OC1R = 0x0FFF - DaOutParm.OutData2;
	OC1RS = 0x0FFE;
}
