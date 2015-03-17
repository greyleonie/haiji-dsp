//海吉科技，HJR3000型智能软启动控制装置，DSPIC30F6010A系统
//IO口处理子程序集 IO.c

//头文件
#include "UserParms.h"	//用户系统配置，常数定义及配置值
#include "Function.h"	//系统外部调用函数声明，内部调用函数在对应文件内声明
#include "variable.h"	//系统全局变量声明，局部变量在对应文件内声明

int AX_int_IO = 0;

void IORead(void)
{
	static unsigned int JSIO1=0,JSIO2=0,JSIO3=0,JSIO4=0,JSIO5=0,JSIO6=0,JSIO7=0,JSIO8=0,JSIO9=0,JSIOA=0,JSIOB=0,JSIOC=0,JSIOD=0,JSIOE=0,JSIOF=0,JSIOG=0,JSIOH=0,JPIO=0;
	static unsigned int JSIO1P=0,JSIO2P=0,JSIO3P=0,JSIO4P=0,JSIO5P=0,JSIO6P=0,JSIO7P=0,JSIO8P=0,JSIO9P=0,JSIOAP=0,JSIOBP=0,JSIOCP=0,JSIODP=0,JSIOEP=0,JSIOFP=0,JSIOGP=0,JSIOHP=0;
	
	
	if(!PORTBbits.RB2)
	{
		JSIO1P=0;
		++JSIO1;
		if(JSIO1>=25)
		{
			InputIO.In1 = 1;
			JSIO1=2500;
		}
	}else 
	{
		JSIO1=0;
		++JSIO1P;
		if(JSIO1P>=25)
		{
			InputIO.In1 = 0;
			JSIO1P=2500;
		}
	}
	
	if(!PORTBbits.RB3)
	{
		JSIO2P=0;
		++JSIO2;
		if(JSIO2>=25)
		{
			InputIO.In2 = 1;
			JSIO2=2500;
		}
	}else 
	{
		JSIO2=0;
		++JSIO2P;
		if(JSIO2P>=25)
		{
			InputIO.In2 = 0;
			JSIO2P=2500;
		}
	}
	
	if(!PORTBbits.RB4)
	{
		JSIO3P=0;
		++JSIO3;
		if(JSIO3>=25)
		{
			InputIO.In3 = 1;
			JSIO3=2500;
		}
	}else 
	{
		JSIO3=0;
		++JSIO3P;
		if(JSIO3P>=25)
		{
			InputIO.In3 = 0;
			JSIO3P=2500;
		}
	}
	
	if(!PORTBbits.RB5)
	{
		JSIO4P=0;
		++JSIO4;
		if(JSIO4>=25)
		{
			InputIO.In4 = 1;
			JSIO4=2500;
		}
	}else 
	{
		JSIO4=0;
		++JSIO4P;
		if(JSIO4P>=25)
		{
			InputIO.In4 = 0;
			JSIO4P=2500;
		}
	}
	
	if(!PORTBbits.RB6)
	{
		JSIO5P=0;
		++JSIO5;
		if(JSIO5>=25)
		{
			InputIO.In5 = 1;
			JSIO5=2500;
		}
	}else 
	{
		JSIO5=0;
		++JSIO5P;
		if(JSIO5P>=25)
		{
			InputIO.In5 = 0;
			JSIO5P=2500;
		}
	}
	
	if(!PORTBbits.RB7)
	{
		JSIO6P=0;
		++JSIO6;
		if(JSIO6>=25)
		{
			InputIO.In6 = 1;
			JSIO6=2500;
		}
	}else 
	{
		JSIO6=0;
		++JSIO6P;
		if(JSIO6P>=25)
		{
			InputIO.In6 = 0;
			JSIO6P=2500;
		}
	}
	
	if(!PORTBbits.RB8)
	{
		JSIO7P=0;
		++JSIO7;
		if(JSIO7>=25)
		{
			InputIO.In7 = 1;
			JSIO7=2500;
		}
	}else 
	{
		JSIO7=0;
		++JSIO7P;
		if(JSIO7P>=25)
		{
			InputIO.In7 = 0;
			JSIO7P=2500;
		}
	}
	
	if(!PORTBbits.RB9)
	{
		JSIO8P=0;
		++JSIO8;
		if(JSIO8>=25)
		{
			InputIO.In8 = 1;
			JSIO8=2500;
		}
	}else 
	{
		JSIO8=0;
		++JSIO8P;
		if(JSIO8P>=25)
		{
			InputIO.In8 = 0;
			JSIO8P=2500;
		}
	}
	
	if(!PORTFbits.RF6)
	{
		JSIO9P=0;
		++JSIO9;
		if(JSIO9>=25)
		{
			InsideIOState.Men = 1;
			JSIO9=2500;
		}
	}else 
	{
		JSIO9=0;
		++JSIO9P;
		if(JSIO9P>=25)
		{
			InsideIOState.Men = 0;
			JSIO9P=2500;
		}
	}
	
	if(!PORTFbits.RF7)
	{
		JSIOAP=0;
		++JSIOA;
		if(JSIOA>=25)
		{
			InsideIOState.Stop = 1;
			if(JSIOA >= 150)
			{
				InsideIOState.SysReset = 1;
				JSIOA=2500;
			}
		}
	}else 
	{
		JSIOA=0;
		++JSIOAP;
		if(JSIOAP>=25)
		{
			InsideIOState.Stop = 0;
			JSIOAP=2500;
		}
	}
	
	
	if(!PORTFbits.RF8)
	{
		JSIOBP=0;
		++JSIOB;
		if(JSIOB>=25)
		{
			InsideIOState.Auto = 1;
			JSIOB=2500;
		}
	}else 
	{
		JSIOB=0;
		++JSIOBP;
		if(JSIOBP>=25)
		{
			InsideIOState.Auto = 0;
			JSIOBP=2500;
		}
	}
	
	if(!PORTCbits.RC1)
	{
		JSIOCP=0;
		++JSIOC;
		if(JSIOC>=25)
		{
			InsideIOState.ComponentHot = 1;
			JSIOC=2500;
		}
	}else 
	{
		JSIOC=0;
		++JSIOCP;
		if(JSIOCP>=25)
		{
			InsideIOState.ComponentHot = 0;
			JSIOCP=2500;
		}
	}
	
	if(!PORTCbits.RC3)
	{
		JSIODP=0;
		++JSIOD;
		if(JSIOD>=25)
		{
			InsideIOState.ByPassIn = 1;
			JSIOD=2500;
		}
	}else 
	{
		JSIOD=0;
		++JSIODP;
		if(JSIODP>=25)
		{
			InsideIOState.ByPassIn = 0;
			JSIODP=2500;
		}
	}
	
	if(!PORTGbits.RG6)
	{
		JSIOEP=0;
		++JSIOE;
		if(JSIOE>=25)
		{
			InsideIOState.Bd0 = 1;
			JSIOE=2500;
		}
	}else 
	{
		JSIOE=0;
		++JSIOEP;
		if(JSIOEP>=25)
		{
			InsideIOState.Bd0 = 0;
			JSIOEP=2500;
		}
	}
	
	if(!PORTGbits.RG7)
	{
		JSIOFP=0;
		++JSIOF;
		if(JSIOF>=25)
		{
			InsideIOState.Bd1 = 1;
			JSIOF=2500;
		}
	}else 
	{
		JSIOF=0;
		++JSIOFP;
		if(JSIOFP>=25)
		{
			InsideIOState.Bd1 = 0;
			JSIOFP=2500;
		}
	}
	
	if(!PORTGbits.RG8)
	{
		JSIOGP=0;
		++JSIOG;
		if(JSIOG>=25)
		{
			InsideIOState.Bd2 = 1;
			JSIOG=2500;
		}
	}else 
	{
		JSIOG=0;
		++JSIOGP;
		if(JSIOGP>=25)
		{
			InsideIOState.Bd2 = 0;
			JSIOGP=2500;
		}
	}
	
	if(!PORTGbits.RG9)
	{
		JSIOHP=0;
		++JSIOH;
		if(JSIOH>=25)
		{
			InsideIOState.Bd3 = 1;
			JSIOH=2500;
		}
	}else 
	{
		JSIOH=0;
		++JSIOHP;
		if(JSIOHP>=25)
		{
			InsideIOState.Bd3 = 0;
			JSIOHP=2500;
		}
	}
	
	
	
	if(JPIO > 300)
	{
		JPIO = 2500;
		AX_int_IO = KeyParm.InLogic;
		AX_int_IO = AX_int_IO & 0x0001;
		if(AX_int_IO == 0x0001)
			InputLogic.In1 = ! InputIO.In1;
		else InputLogic.In1 = InputIO.In1;
		
		AX_int_IO = KeyParm.InLogic;
		AX_int_IO = AX_int_IO & 0x0002;
		if(AX_int_IO == 0x0002)
			InputLogic.In2 = ! InputIO.In2;
		else InputLogic.In2 = InputIO.In2;
		
		AX_int_IO = KeyParm.InLogic;
		AX_int_IO = AX_int_IO & 0x0004;
		if(AX_int_IO == 0x0004)
			InputLogic.In3 = ! InputIO.In3;
		else InputLogic.In3 = InputIO.In3;
		
		AX_int_IO = KeyParm.InLogic;
		AX_int_IO = AX_int_IO & 0x0008;
		if(AX_int_IO == 0x0008)
			InputLogic.In4 = ! InputIO.In4;
		else InputLogic.In4 = InputIO.In4;
		
		AX_int_IO = KeyParm.InLogic;
		AX_int_IO = AX_int_IO & 0x0010;
		if(AX_int_IO == 0x0010)
			InputLogic.In5 = ! InputIO.In5;
		else InputLogic.In5 = InputIO.In5;
		
		AX_int_IO = KeyParm.InLogic;
		AX_int_IO = AX_int_IO & 0x0020;
		if(AX_int_IO == 0x0020)
			InputLogic.In6 = ! InputIO.In6;
		else InputLogic.In6 = InputIO.In6;
		
		AX_int_IO = KeyParm.InLogic;
		AX_int_IO = AX_int_IO & 0x0040;
		if(AX_int_IO == 0x0040)
			InputLogic.In7 = ! InputIO.In7;
		else InputLogic.In7 = InputIO.In7;
		
		AX_int_IO = KeyParm.InLogic;
		AX_int_IO = AX_int_IO & 0x0080;
		if(AX_int_IO == 0x0080)
			InputLogic.In8 = ! InputIO.In8;
		else InputLogic.In8 = InputIO.In8;
		
		
	}else
	{
		++JPIO;
	}
	
}


void IOWrite(void)
{
	LATCbits.LATC13 = InsideIOState.ByPassOut;
	

	switch(KeyParm.Out1)
    {
		case 0:
			OutputIO.OU1 = OutputState.Error;
			break;
        case 1:
        	OutputIO.OU1 = OutputState.OverHigh;
			break;
		case 2:
        	OutputIO.OU1 = OutputState.OverLow;
			break;
		case 3:
        	OutputIO.OU1 = OutputState.AboveHigh;
			break;
		case 4:
        	OutputIO.OU1 = OutputState.AboveLow;
			break;
		case 5:
        	OutputIO.OU1 = OutputState.Run;
			break;	
		case 6:
        	OutputIO.OU1 = OutputState.Normal;
			break;	
		case 7:
        	OutputIO.OU1 = OutputState.Backup;
			break;	
		case 8:
        	OutputIO.OU1 = OutputState.FillGas;
			break;	
		case 9:
        	OutputIO.OU1 = OutputState.Stay;
			break;	
		case 10:
        	OutputIO.OU1 = OutputState.Auto;
			break;	
		case 11:
        	OutputIO.OU1 = OutputState.Stop;
			break;	
		case 12:
        	OutputIO.OU1 = OutputState.StopMent;
			break;	
		case 13:
        	OutputIO.OU1 = OutputState.Men;
			break;	
		case 14:
        	OutputIO.OU1 = OutputState.Prepare;
			break;	
		case 15:
        	OutputIO.OU1 = OutputState.Start;
			break;	
		case 16:
        	OutputIO.OU1 = OutputIO.StopFillGas;
			break;	
		case 17:
        	OutputIO.OU1 = OutputIO.MainMeauError;
			break;	
		case 18:
        	OutputIO.OU1 = OutputIO.BackupMeauError;
			break;	
		case 19:
        	OutputIO.OU1 = OutputIO.BackupMeauHigh;
			break;	
		case 20:
        	OutputIO.OU1 = OutputIO.BackupMeauLow;
			break;	
		case 21:
        	OutputIO.OU1 = 0;
			break;	
		default:
			OutputIO.OU1 = 0;
			break;
	}

switch(KeyParm.Out2)
    {
		case 0:
			OutputIO.OU2 = OutputState.Error;
			break;
        case 1:
        	OutputIO.OU2 = OutputState.OverHigh;
			break;
		case 2:
        	OutputIO.OU2 = OutputState.OverLow;
			break;
		case 3:
        	OutputIO.OU2 = OutputState.AboveHigh;
			break;
		case 4:
        	OutputIO.OU2 = OutputState.AboveLow;
			break;
		case 5:
        	OutputIO.OU2 = OutputState.Run;
			break;	
		case 6:
        	OutputIO.OU2 = OutputState.Normal;
			break;	
		case 7:
        	OutputIO.OU2 = OutputState.Backup;
			break;	
		case 8:
        	OutputIO.OU2 = OutputState.FillGas;
			break;	
		case 9:
        	OutputIO.OU2 = OutputState.Stay;
			break;	
		case 10:
        	OutputIO.OU2 = OutputState.Auto;
			break;	
		case 11:
        	OutputIO.OU2 = OutputState.Stop;
			break;	
		case 12:
        	OutputIO.OU2 = OutputState.StopMent;
			break;	
		case 13:
        	OutputIO.OU2 = OutputState.Men;
			break;	
		case 14:
        	OutputIO.OU2 = OutputState.Prepare;
			break;	
		case 15:
        	OutputIO.OU2 = OutputState.Start;
			break;	
		case 16:
        	OutputIO.OU2 = OutputIO.StopFillGas;
			break;	
		case 17:
        	OutputIO.OU2 = OutputIO.MainMeauError;
			break;	
		case 18:
        	OutputIO.OU2 = OutputIO.BackupMeauError;
			break;	
		case 19:
        	OutputIO.OU2 = OutputIO.BackupMeauHigh;
			break;	
		case 20:
        	OutputIO.OU2 = OutputIO.BackupMeauLow;
			break;	
		case 21:
        	OutputIO.OU2 = 0;
			break;	
		default:
			OutputIO.OU2 = 0;
			break;
	}

switch(KeyParm.Out3)
    {
		case 0:
			OutputIO.OU3 = OutputState.Error;
			break;
        case 1:
        	OutputIO.OU3 = OutputState.OverHigh;
			break;
		case 2:
        	OutputIO.OU3 = OutputState.OverLow;
			break;
		case 3:
        	OutputIO.OU3 = OutputState.AboveHigh;
			break;
		case 4:
        	OutputIO.OU3 = OutputState.AboveLow;
			break;
		case 5:
        	OutputIO.OU3 = OutputState.Run;
			break;	
		case 6:
        	OutputIO.OU3 = OutputState.Normal;
			break;	
		case 7:
        	OutputIO.OU3 = OutputState.Backup;
			break;	
		case 8:
        	OutputIO.OU3 = OutputState.FillGas;
			break;	
		case 9:
        	OutputIO.OU3 = OutputState.Stay;
			break;	
		case 10:
        	OutputIO.OU3 = OutputState.Auto;
			break;	
		case 11:
        	OutputIO.OU3 = OutputState.Stop;
			break;	
		case 12:
        	OutputIO.OU3 = OutputState.StopMent;
			break;	
		case 13:
        	OutputIO.OU3 = OutputState.Men;
			break;	
		case 14:
        	OutputIO.OU3 = OutputState.Prepare;
			break;	
		case 15:
        	OutputIO.OU3 = OutputState.Start;
			break;	
		case 16:
        	OutputIO.OU3 = OutputIO.StopFillGas;
			break;	
		case 17:
        	OutputIO.OU3 = OutputIO.MainMeauError;
			break;	
		case 18:
        	OutputIO.OU3 = OutputIO.BackupMeauError;
			break;	
		case 19:
        	OutputIO.OU3 = OutputIO.BackupMeauHigh;
			break;	
		case 20:
        	OutputIO.OU3 = OutputIO.BackupMeauLow;
			break;	
		case 21:
        	OutputIO.OU3 = 0;
			break;	
		default:
			OutputIO.OU3 = 0;
			break;
	}

switch(KeyParm.Out4)
    {
		case 0:
			OutputIO.OU4 = OutputState.Error;
			break;
        case 1:
        	OutputIO.OU4 = OutputState.OverHigh;
			break;
		case 2:
        	OutputIO.OU4 = OutputState.OverLow;
			break;
		case 3:
        	OutputIO.OU4 = OutputState.AboveHigh;
			break;
		case 4:
        	OutputIO.OU4 = OutputState.AboveLow;
			break;
		case 5:
        	OutputIO.OU4 = OutputState.Run;
			break;	
		case 6:
        	OutputIO.OU4 = OutputState.Normal;
			break;	
		case 7:
        	OutputIO.OU4 = OutputState.Backup;
			break;	
		case 8:
        	OutputIO.OU4 = OutputState.FillGas;
			break;	
		case 9:
        	OutputIO.OU4 = OutputState.Stay;
			break;	
		case 10:
        	OutputIO.OU4 = OutputState.Auto;
			break;	
		case 11:
        	OutputIO.OU4 = OutputState.Stop;
			break;	
		case 12:
        	OutputIO.OU4 = OutputState.StopMent;
			break;	
		case 13:
        	OutputIO.OU4 = OutputState.Men;
			break;	
		case 14:
        	OutputIO.OU4 = OutputState.Prepare;
			break;	
		case 15:
        	OutputIO.OU4 = OutputState.Start;
			break;	
		case 16:
        	OutputIO.OU4 = OutputIO.StopFillGas;
			break;	
		case 17:
        	OutputIO.OU4 = OutputIO.MainMeauError;
			break;	
		case 18:
        	OutputIO.OU4 = OutputIO.BackupMeauError;
			break;	
		case 19:
        	OutputIO.OU4 = OutputIO.BackupMeauHigh;
			break;	
		case 20:
        	OutputIO.OU4 = OutputIO.BackupMeauLow;
			break;	
		case 21:
        	OutputIO.OU4 = 0;
			break;	
		default:
			OutputIO.OU4 = 0;
			break;
	}

switch(KeyParm.Out5)
    {
		case 0:
			OutputIO.OU5 = OutputState.Error;
			break;
        case 1:
        	OutputIO.OU5 = OutputState.OverHigh;
			break;
		case 2:
        	OutputIO.OU5 = OutputState.OverLow;
			break;
		case 3:
        	OutputIO.OU5 = OutputState.AboveHigh;
			break;
		case 4:
        	OutputIO.OU5 = OutputState.AboveLow;
			break;
		case 5:
        	OutputIO.OU5 = OutputState.Run;
			break;	
		case 6:
        	OutputIO.OU5 = OutputState.Normal;
			break;	
		case 7:
        	OutputIO.OU5 = OutputState.Backup;
			break;	
		case 8:
        	OutputIO.OU5 = OutputState.FillGas;
			break;	
		case 9:
        	OutputIO.OU5 = OutputState.Stay;
			break;	
		case 10:
        	OutputIO.OU5 = OutputState.Auto;
			break;	
		case 11:
        	OutputIO.OU5 = OutputState.Stop;
			break;	
		case 12:
        	OutputIO.OU5 = OutputState.StopMent;
			break;	
		case 13:
        	OutputIO.OU5 = OutputState.Men;
			break;	
		case 14:
        	OutputIO.OU5 = OutputState.Prepare;
			break;	
		case 15:
        	OutputIO.OU5 = OutputState.Start;
			break;	
		case 16:
        	OutputIO.OU5 = OutputIO.StopFillGas;
			break;	
		case 17:
        	OutputIO.OU5 = OutputIO.MainMeauError;
			break;	
		case 18:
        	OutputIO.OU5 = OutputIO.BackupMeauError;
			break;	
		case 19:
        	OutputIO.OU5 = OutputIO.BackupMeauHigh;
			break;	
		case 20:
        	OutputIO.OU5 = OutputIO.BackupMeauLow;
			break;	
		case 21:
        	OutputIO.OU5 = 0;
			break;	
		default:
			OutputIO.OU5 = 0;
			break;
	}

switch(KeyParm.Out6)
    {
		case 0:
			OutputIO.OU6 = OutputState.Error;
			break;
        case 1:
        	OutputIO.OU6 = OutputState.OverHigh;
			break;
		case 2:
        	OutputIO.OU6 = OutputState.OverLow;
			break;
		case 3:
        	OutputIO.OU6 = OutputState.AboveHigh;
			break;
		case 4:
        	OutputIO.OU6 = OutputState.AboveLow;
			break;
		case 5:
        	OutputIO.OU6 = OutputState.Run;
			break;	
		case 6:
        	OutputIO.OU6 = OutputState.Normal;
			break;	
		case 7:
        	OutputIO.OU6 = OutputState.Backup;
			break;	
		case 8:
        	OutputIO.OU6 = OutputState.FillGas;
			break;	
		case 9:
        	OutputIO.OU6 = OutputState.Stay;
			break;	
		case 10:
        	OutputIO.OU6 = OutputState.Auto;
			break;	
		case 11:
        	OutputIO.OU6 = OutputState.Stop;
			break;	
		case 12:
        	OutputIO.OU6 = OutputState.StopMent;
			break;	
		case 13:
        	OutputIO.OU6 = OutputState.Men;
			break;	
		case 14:
        	OutputIO.OU6 = OutputState.Prepare;
			break;	
		case 15:
        	OutputIO.OU6 = OutputState.Start;
			break;	
		case 16:
        	OutputIO.OU6 = OutputIO.StopFillGas;
			break;	
		case 17:
        	OutputIO.OU6 = OutputIO.MainMeauError;
			break;	
		case 18:
        	OutputIO.OU6 = OutputIO.BackupMeauError;
			break;	
		case 19:
        	OutputIO.OU6 = OutputIO.BackupMeauHigh;
			break;	
		case 20:
        	OutputIO.OU6 = OutputIO.BackupMeauLow;
			break;	
		case 21:
        	OutputIO.OU6 = 0;
			break;	
		default:
			OutputIO.OU6 = 0;
			break;
	}

switch(KeyParm.Out7)
    {
		case 0:
			OutputIO.OU7 = OutputState.Error;
			break;
        case 1:
        	OutputIO.OU7 = OutputState.OverHigh;
			break;
		case 2:
        	OutputIO.OU7 = OutputState.OverLow;
			break;
		case 3:
        	OutputIO.OU7 = OutputState.AboveHigh;
			break;
		case 4:
        	OutputIO.OU7 = OutputState.AboveLow;
			break;
		case 5:
        	OutputIO.OU7 = OutputState.Run;
			break;	
		case 6:
        	OutputIO.OU7 = OutputState.Normal;
			break;	
		case 7:
        	OutputIO.OU7 = OutputState.Backup;
			break;	
		case 8:
        	OutputIO.OU7 = OutputState.FillGas;
			break;	
		case 9:
        	OutputIO.OU7 = OutputState.Stay;
			break;	
		case 10:
        	OutputIO.OU7 = OutputState.Auto;
			break;	
		case 11:
        	OutputIO.OU7 = OutputState.Stop;
			break;	
		case 12:
        	OutputIO.OU7 = OutputState.StopMent;
			break;	
		case 13:
        	OutputIO.OU7 = OutputState.Men;
			break;	
		case 14:
        	OutputIO.OU7 = OutputState.Prepare;
			break;	
		case 15:
        	OutputIO.OU7 = OutputState.Start;
			break;	
		case 16:
        	OutputIO.OU7 = OutputIO.StopFillGas;
			break;	
		case 17:
        	OutputIO.OU7 = OutputIO.MainMeauError;
			break;	
		case 18:
        	OutputIO.OU7 = OutputIO.BackupMeauError;
			break;	
		case 19:
        	OutputIO.OU7 = OutputIO.BackupMeauHigh;
			break;	
		case 20:
        	OutputIO.OU7 = OutputIO.BackupMeauLow;
			break;	
		case 21:
        	OutputIO.OU7 = 0;
			break;	
		default:
			OutputIO.OU7 = 0;
			break;
	}

switch(KeyParm.Out8)
    {
		case 0:
			OutputIO.OU8 = OutputState.Error;
			break;
        case 1:
        	OutputIO.OU8 = OutputState.OverHigh;
			break;
		case 2:
        	OutputIO.OU8 = OutputState.OverLow;
			break;
		case 3:
        	OutputIO.OU8 = OutputState.AboveHigh;
			break;
		case 4:
        	OutputIO.OU8 = OutputState.AboveLow;
			break;
		case 5:
        	OutputIO.OU8 = OutputState.Run;
			break;	
		case 6:
        	OutputIO.OU8 = OutputState.Normal;
			break;	
		case 7:
        	OutputIO.OU8 = OutputState.Backup;
			break;	
		case 8:
        	OutputIO.OU8 = OutputState.FillGas;
			break;	
		case 9:
        	OutputIO.OU8 = OutputState.Stay;
			break;	
		case 10:
        	OutputIO.OU8 = OutputState.Auto;
			break;	
		case 11:
        	OutputIO.OU8 = OutputState.Stop;
			break;	
		case 12:
        	OutputIO.OU8 = OutputState.StopMent;
			break;	
		case 13:
        	OutputIO.OU8 = OutputState.Men;
			break;	
		case 14:
        	OutputIO.OU8 = OutputState.Prepare;
			break;	
		case 15:
        	OutputIO.OU8 = OutputState.Start;
			break;	
		case 16:
        	OutputIO.OU8 = OutputIO.StopFillGas;
			break;	
		case 17:
        	OutputIO.OU8 = OutputIO.MainMeauError;
			break;	
		case 18:
        	OutputIO.OU8 = OutputIO.BackupMeauError;
			break;	
		case 19:
        	OutputIO.OU8 = OutputIO.BackupMeauHigh;
			break;	
		case 20:
        	OutputIO.OU8 = OutputIO.BackupMeauLow;
			break;	
		case 21:
        	OutputIO.OU8 = 0;
			break;	
		default:
			OutputIO.OU8 = 0;
			break;
	}

switch(KeyParm.Out9)
    {
		case 0:
			OutputIO.OU9 = OutputState.Error;
			break;
        case 1:
        	OutputIO.OU9 = OutputState.OverHigh;
			break;
		case 2:
        	OutputIO.OU9 = OutputState.OverLow;
			break;
		case 3:
        	OutputIO.OU9 = OutputState.AboveHigh;
			break;
		case 4:
        	OutputIO.OU9 = OutputState.AboveLow;
			break;
		case 5:
        	OutputIO.OU9 = OutputState.Run;
			break;	
		case 6:
        	OutputIO.OU9 = OutputState.Normal;
			break;	
		case 7:
        	OutputIO.OU9 = OutputState.Backup;
			break;	
		case 8:
        	OutputIO.OU9 = OutputState.FillGas;
			break;	
		case 9:
        	OutputIO.OU9 = OutputState.Stay;
			break;	
		case 10:
        	OutputIO.OU9 = OutputState.Auto;
			break;	
		case 11:
        	OutputIO.OU9 = OutputState.Stop;
			break;	
		case 12:
        	OutputIO.OU9 = OutputState.StopMent;
			break;	
		case 13:
        	OutputIO.OU9 = OutputState.Men;
			break;	
		case 14:
        	OutputIO.OU9 = OutputState.Prepare;
			break;	
		case 15:
        	OutputIO.OU9 = OutputState.Start;
			break;	
		case 16:
        	OutputIO.OU9 = OutputIO.StopFillGas;
			break;	
		case 17:
        	OutputIO.OU9 = OutputIO.MainMeauError;
			break;	
		case 18:
        	OutputIO.OU9 = OutputIO.BackupMeauError;
			break;	
		case 19:
        	OutputIO.OU9 = OutputIO.BackupMeauHigh;
			break;	
		case 20:
        	OutputIO.OU9 = OutputIO.BackupMeauLow;
			break;	
		case 21:
        	OutputIO.OU9 = 0;
			break;	
		default:
			OutputIO.OU9 = 0;
			break;
	}

switch(KeyParm.Out10)
    {
		case 0:
			OutputIO.OU10 = OutputState.Error;
			break;
        case 1:
        	OutputIO.OU10 = OutputState.OverHigh;
			break;
		case 2:
        	OutputIO.OU10 = OutputState.OverLow;
			break;
		case 3:
        	OutputIO.OU10 = OutputState.AboveHigh;
			break;
		case 4:
        	OutputIO.OU10 = OutputState.AboveLow;
			break;
		case 5:
        	OutputIO.OU10 = OutputState.Run;
			break;	
		case 6:
        	OutputIO.OU10 = OutputState.Normal;
			break;	
		case 7:
        	OutputIO.OU10 = OutputState.Backup;
			break;	
		case 8:
        	OutputIO.OU10 = OutputState.FillGas;
			break;	
		case 9:
        	OutputIO.OU10 = OutputState.Stay;
			break;	
		case 10:
        	OutputIO.OU10 = OutputState.Auto;
			break;	
		case 11:
        	OutputIO.OU10 = OutputState.Stop;
			break;	
		case 12:
        	OutputIO.OU10 = OutputState.StopMent;
			break;	
		case 13:
        	OutputIO.OU10 = OutputState.Men;
			break;	
		case 14:
        	OutputIO.OU10 = OutputState.Prepare;
			break;	
		case 15:
        	OutputIO.OU10 = OutputState.Start;
			break;	
		case 16:
        	OutputIO.OU10 = OutputIO.StopFillGas;
			break;	
		case 17:
        	OutputIO.OU10 = OutputIO.MainMeauError;
			break;	
		case 18:
        	OutputIO.OU10 = OutputIO.BackupMeauError;
			break;	
		case 19:
        	OutputIO.OU10 = OutputIO.BackupMeauHigh;
			break;	
		case 20:
        	OutputIO.OU10 = OutputIO.BackupMeauLow;
			break;	
		case 21:
        	OutputIO.OU10 = 0;
			break;	
		default:
			OutputIO.OU10 = 0;
			break;
	}


	AX_int_IO = KeyParm.OutLogic;
	AX_int_IO = AX_int_IO & 0x0001;
	if(AX_int_IO == 0x0001)
		LATCbits.LATC14 = ! OutputIO.OU1;
	else LATCbits.LATC14 = OutputIO.OU1;
	
	AX_int_IO = KeyParm.OutLogic;
	AX_int_IO = AX_int_IO & 0x0002;
	if(AX_int_IO == 0x0002)
		LATDbits.LATD2 = ! OutputIO.OU2;
	else LATDbits.LATD2 = OutputIO.OU2;
	
	AX_int_IO = KeyParm.OutLogic;
	AX_int_IO = AX_int_IO & 0x0004;
	if(AX_int_IO == 0x0004)
		LATDbits.LATD3 = ! OutputIO.OU3;
	else LATDbits.LATD3 = OutputIO.OU3;
	
	AX_int_IO = KeyParm.OutLogic;
	AX_int_IO = AX_int_IO & 0x0008;
	if(AX_int_IO == 0x0008)
		LATDbits.LATD4 = ! OutputIO.OU4;
	else LATDbits.LATD4 = OutputIO.OU4;
	
	AX_int_IO = KeyParm.OutLogic;
	AX_int_IO = AX_int_IO & 0x0010;
	if(AX_int_IO == 0x0010)
		LATDbits.LATD5 = ! OutputIO.OU5;
	else LATDbits.LATD5 = OutputIO.OU5;
	
	AX_int_IO = KeyParm.OutLogic;
	AX_int_IO = AX_int_IO & 0x0020;
	if(AX_int_IO == 0x0020)
		LATDbits.LATD6 = ! OutputIO.OU6;
	else LATDbits.LATD6 = OutputIO.OU6;
	
	AX_int_IO = KeyParm.OutLogic;
	AX_int_IO = AX_int_IO & 0x0040;
	if(AX_int_IO == 0x0040)
		LATDbits.LATD7 = ! OutputIO.OU7;
	else LATDbits.LATD7 = OutputIO.OU7;
	
	AX_int_IO = KeyParm.OutLogic;
	AX_int_IO = AX_int_IO & 0x0080;
	if(AX_int_IO == 0x0080)
		LATDbits.LATD13 = ! OutputIO.OU8;
	else LATDbits.LATD13 = OutputIO.OU8;
	
	AX_int_IO = KeyParm.OutLogic;
	AX_int_IO = AX_int_IO & 0x0100;
	if(AX_int_IO == 0x0100)
		LATDbits.LATD14 = ! OutputIO.OU9;
	else LATDbits.LATD14 = OutputIO.OU9;
	
	AX_int_IO = KeyParm.OutLogic;
	AX_int_IO = AX_int_IO & 0x0200;
	if(AX_int_IO == 0x0200)
		LATDbits.LATD15 = ! OutputIO.OU10;
	else LATDbits.LATD15 = OutputIO.OU10;

}



void IOCorp(void)
{
	switch(KeyParm.In1)
    {
		case 0:
			InputState.ImRun = InputLogic.In1;
			break;
        case 1:
        	InputState.ImStop = InputLogic.In1;
			break;
		case 2:
        	InputState.ImLog = InputLogic.In1;
			break;
		case 3:
        	InputState.Stop = InputLogic.In1;
			break;
		case 4:
        	InputState.NormalRun = InputLogic.In1;
			break;
		case 5:
        	InputState.BackupRun = InputLogic.In1;
			break;
		case 6:
        	InputState.Backup2Run = InputLogic.In1;
			break;
		case 7:
        	InputState.Backup3Run = InputLogic.In1;
			break;
		case 8:
        	InputState.Backup4Run = InputLogic.In1;
			break;
		case 9:
        	InputState.Backup5Run = InputLogic.In1;
			break;
		case 10:
        	InputState.Backup6Run = InputLogic.In1;
			break;
		case 11:
        	InputState.Backup7Run = InputLogic.In1;
			break;
		case 12:
        	InputState.AutoStop = InputLogic.In1;
			break;
		case 13:
        	InputState.RunLimit = InputLogic.In1;
			break;
		case 14:
        	InputState.RunPrePare = InputLogic.In1;
			break;
		case 15:
        	InsideIOState.IoAuto = InputLogic.In1;
			break;
		case 16:
        	InsideIOState.IoStop = InputLogic.In1;
			break;
		case 17:
        	InsideIOState.BackupStop = InputLogic.In1;
			break;
		case 18:
        	;
			break;
		default:
			;
			break;
	}
			
	switch(KeyParm.In2)
    {
		case 0:
			InputState.ImRun = InputLogic.In2;
			break;
        case 1:
        	InputState.ImStop = InputLogic.In2;
			break;
		case 2:
        	InputState.ImLog = InputLogic.In2;
			break;
		case 3:
        	InputState.Stop = InputLogic.In2;
			break;
		case 4:
        	InputState.NormalRun = InputLogic.In2;
			break;
		case 5:
        	InputState.BackupRun = InputLogic.In2;
			break;
		case 6:
        	InputState.Backup2Run = InputLogic.In2;
			break;
		case 7:
        	InputState.Backup3Run = InputLogic.In2;
			break;
		case 8:
        	InputState.Backup4Run = InputLogic.In2;
			break;
		case 9:
        	InputState.Backup5Run = InputLogic.In2;
			break;
		case 10:
        	InputState.Backup6Run = InputLogic.In2;
			break;
		case 11:
        	InputState.Backup7Run = InputLogic.In2;
			break;
		case 12:
        	InputState.AutoStop = InputLogic.In2;
			break;
		case 13:
        	InputState.RunLimit = InputLogic.In2;
			break;
		case 14:
        	InputState.RunPrePare = InputLogic.In2;
			break;
		case 15:
        	InsideIOState.IoAuto = InputLogic.In2;
			break;
		case 16:
        	InsideIOState.IoStop = InputLogic.In2;
			break;
		case 17:
        	InsideIOState.BackupStop = InputLogic.In2;
			break;
		case 18:
        	;
			break;
		default:
			;
			break;
	}
	
	switch(KeyParm.In3)
    {
		case 0:
			InputState.ImRun = InputLogic.In3;
			break;
        case 1:
        	InputState.ImStop = InputLogic.In3;
			break;
		case 2:
        	InputState.ImLog = InputLogic.In3;
			break;
		case 3:
        	InputState.Stop = InputLogic.In3;
			break;
		case 4:
        	InputState.NormalRun = InputLogic.In3;
			break;
		case 5:
        	InputState.BackupRun = InputLogic.In3;
			break;
		case 6:
        	InputState.Backup2Run = InputLogic.In3;
			break;
		case 7:
        	InputState.Backup3Run = InputLogic.In3;
			break;
		case 8:
        	InputState.Backup4Run = InputLogic.In3;
			break;
		case 9:
        	InputState.Backup5Run = InputLogic.In3;
			break;
		case 10:
        	InputState.Backup6Run = InputLogic.In3;
			break;
		case 11:
        	InputState.Backup7Run = InputLogic.In3;
			break;
		case 12:
        	InputState.AutoStop = InputLogic.In3;
			break;
		case 13:
        	InputState.RunLimit = InputLogic.In3;
			break;
		case 14:
        	InputState.RunPrePare = InputLogic.In3;
			break;
		case 15:
        	InsideIOState.IoAuto = InputLogic.In3;
			break;
		case 16:
        	InsideIOState.IoStop = InputLogic.In3;
			break;
		case 17:
        	InsideIOState.BackupStop = InputLogic.In3;
			break;
		case 18:
        	;
			break;
		default:
			;
			break;
	}
	
	switch(KeyParm.In4)
    {
		case 0:
			InputState.ImRun = InputLogic.In4;
			break;
        case 1:
        	InputState.ImStop = InputLogic.In4;
			break;
		case 2:
        	InputState.ImLog = InputLogic.In4;
			break;
		case 3:
        	InputState.Stop = InputLogic.In4;
			break;
		case 4:
        	InputState.NormalRun = InputLogic.In4;
			break;
		case 5:
        	InputState.BackupRun = InputLogic.In4;
			break;
		case 6:
        	InputState.Backup2Run = InputLogic.In4;
			break;
		case 7:
        	InputState.Backup3Run = InputLogic.In4;
			break;
		case 8:
        	InputState.Backup4Run = InputLogic.In4;
			break;
		case 9:
        	InputState.Backup5Run = InputLogic.In4;
			break;
		case 10:
        	InputState.Backup6Run = InputLogic.In4;
			break;
		case 11:
        	InputState.Backup7Run = InputLogic.In4;
			break;
		case 12:
        	InputState.AutoStop = InputLogic.In4;
			break;
		case 13:
        	InputState.RunLimit = InputLogic.In4;
			break;
		case 14:
        	InputState.RunPrePare = InputLogic.In4;
			break;
		case 15:
        	InsideIOState.IoAuto = InputLogic.In4;
			break;
		case 16:
        	InsideIOState.IoStop = InputLogic.In4;
			break;
		case 17:
        	InsideIOState.BackupStop = InputLogic.In4;
			break;
		case 18:
        	;
			break;
		default:
			;
			break;
	}
	
	switch(KeyParm.In5)
    {
		case 0:
			InputState.ImRun = InputLogic.In5;
			break;
        case 1:
        	InputState.ImStop = InputLogic.In5;
			break;
		case 2:
        	InputState.ImLog = InputLogic.In5;
			break;
		case 3:
        	InputState.Stop = InputLogic.In5;
			break;
		case 4:
        	InputState.NormalRun = InputLogic.In5;
			break;
		case 5:
        	InputState.BackupRun = InputLogic.In5;
			break;
		case 6:
        	InputState.Backup2Run = InputLogic.In5;
			break;
		case 7:
        	InputState.Backup3Run = InputLogic.In5;
			break;
		case 8:
        	InputState.Backup4Run = InputLogic.In5;
			break;
		case 9:
        	InputState.Backup5Run = InputLogic.In5;
			break;
		case 10:
        	InputState.Backup6Run = InputLogic.In5;
			break;
		case 11:
        	InputState.Backup7Run = InputLogic.In5;
			break;
		case 12:
        	InputState.AutoStop = InputLogic.In5;
			break;
		case 13:
        	InputState.RunLimit = InputLogic.In5;
			break;
		case 14:
        	InputState.RunPrePare = InputLogic.In5;
			break;
		case 15:
        	InsideIOState.IoAuto = InputLogic.In5;
			break;
		case 16:
        	InsideIOState.IoStop = InputLogic.In5;
			break;
		case 17:
        	InsideIOState.BackupStop = InputLogic.In5;
			break;
		case 18:
        	;
			break;
		default:
			;
			break;
	}
	
	
	switch(KeyParm.In6)
    {
		case 0:
			InputState.ImRun = InputLogic.In6;
			break;
        case 1:
        	InputState.ImStop = InputLogic.In6;
			break;
		case 2:
        	InputState.ImLog = InputLogic.In6;
			break;
		case 3:
        	InputState.Stop = InputLogic.In6;
			break;
		case 4:
        	InputState.NormalRun = InputLogic.In6;
			break;
		case 5:
        	InputState.BackupRun = InputLogic.In6;
			break;
		case 6:
        	InputState.Backup2Run = InputLogic.In6;
			break;
		case 7:
        	InputState.Backup3Run = InputLogic.In6;
			break;
		case 8:
        	InputState.Backup4Run = InputLogic.In6;
			break;
		case 9:
        	InputState.Backup5Run = InputLogic.In6;
			break;
		case 10:
        	InputState.Backup6Run = InputLogic.In6;
			break;
		case 11:
        	InputState.Backup7Run = InputLogic.In6;
			break;
		case 12:
        	InputState.AutoStop = InputLogic.In6;
			break;
		case 13:
        	InputState.RunLimit = InputLogic.In6;
			break;
		case 14:
        	InputState.RunPrePare = InputLogic.In6;
			break;
		case 15:
        	InsideIOState.IoAuto = InputLogic.In6;
			break;
		case 16:
        	InsideIOState.IoStop = InputLogic.In6;
			break;
		case 17:
        	InsideIOState.BackupStop = InputLogic.In6;
			break;
		case 18:
        	;
			break;
		default:
			;
			break;
	}
	
	switch(KeyParm.In7)
    {
		case 0:
			InputState.ImRun = InputLogic.In7;
			break;
        case 1:
        	InputState.ImStop = InputLogic.In7;
			break;
		case 2:
        	InputState.ImLog = InputLogic.In7;
			break;
		case 3:
        	InputState.Stop = InputLogic.In7;
			break;
		case 4:
        	InputState.NormalRun = InputLogic.In7;
			break;
		case 5:
        	InputState.BackupRun = InputLogic.In7;
			break;
		case 6:
        	InputState.Backup2Run = InputLogic.In7;
			break;
		case 7:
        	InputState.Backup3Run = InputLogic.In7;
			break;
		case 8:
        	InputState.Backup4Run = InputLogic.In7;
			break;
		case 9:
        	InputState.Backup5Run = InputLogic.In7;
			break;
		case 10:
        	InputState.Backup6Run = InputLogic.In7;
			break;
		case 11:
        	InputState.Backup7Run = InputLogic.In7;
			break;
		case 12:
        	InputState.AutoStop = InputLogic.In7;
			break;
		case 13:
        	InputState.RunLimit = InputLogic.In7;
			break;
		case 14:
        	InputState.RunPrePare = InputLogic.In7;
			break;
		case 15:
        	InsideIOState.IoAuto = InputLogic.In7;
			break;
		case 16:
        	InsideIOState.IoStop = InputLogic.In7;
			break;
		case 17:
        	InsideIOState.BackupStop = InputLogic.In7;
			break;
		case 18:
        	;
			break;
		default:
			;
			break;
	}
	
	switch(KeyParm.In8)
    {
		case 0:
			InputState.ImRun = InputLogic.In8;
			break;
        case 1:
        	InputState.ImStop = InputLogic.In8;
			break;
		case 2:
        	InputState.ImLog = InputLogic.In8;
			break;
		case 3:
        	InputState.Stop = InputLogic.In8;
			break;
		case 4:
        	InputState.NormalRun = InputLogic.In8;
			break;
		case 5:
        	InputState.BackupRun = InputLogic.In8;
			break;
		case 6:
        	InputState.Backup2Run = InputLogic.In8;
			break;
		case 7:
        	InputState.Backup3Run = InputLogic.In8;
			break;
		case 8:
        	InputState.Backup4Run = InputLogic.In8;
			break;
		case 9:
        	InputState.Backup5Run = InputLogic.In8;
			break;
		case 10:
        	InputState.Backup6Run = InputLogic.In8;
			break;
		case 11:
        	InputState.Backup7Run = InputLogic.In8;
			break;
		case 12:
        	InputState.AutoStop = InputLogic.In8;
			break;
		case 13:
        	InputState.RunLimit = InputLogic.In8;
			break;
		case 14:
        	InputState.RunPrePare = InputLogic.In8;
			break;
		case 15:
        	InsideIOState.IoAuto = InputLogic.In8;
			break;
		case 16:
        	InsideIOState.IoStop = InputLogic.In8;
			break;
		case 17:
        	InsideIOState.BackupStop = InputLogic.In8;
			break;
		case 18:
        	;
			break;
		default:
			;
			break;
	}
	
			
}
