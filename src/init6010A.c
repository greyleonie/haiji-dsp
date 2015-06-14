//海吉科技，HJR3000型智能软启动控制装置，DSPIC30F6010A系统
//系统初始化函数，init4011.c

//头文�?
#include "UserParms.h"	//用户系统配置，常数定义及配置�?
#include "Function.h"	//系统外部调用函数声明，内部调用函数在对应文件内声�?
#include "variable.h"	//系统全局变量声明，局部变量在对应文件内声�?

int AX_int_Init = 0;

//读EEP，配置系统参�?
void SysConfig(void)
{
	//读串口波特率单元，KeyParm.SaveParms[0x1B]
	EEPROMADDR = 0xF000+2*0x1B;
  	ReadEE(__builtin_tblpage(&EPConfigS[0]),EEPROMADDR,&KeyParm.SaveParms[0x1B], WORD);
	
	if(KeyParm.SaveParms[0x1B] == 0)
		Uart2Parm.dBaudRate = 1200;
	else if(KeyParm.SaveParms[0x1B] == 1)
		Uart2Parm.dBaudRate = 2400;
	else if(KeyParm.SaveParms[0x1B] == 2)
		Uart2Parm.dBaudRate = 4800;
	else if(KeyParm.SaveParms[0x1B] == 3)
		Uart2Parm.dBaudRate = 9600;
	else Uart2Parm.dBaudRate = 9600;
	
	Uart2Parm.dBaudRateTcy =  ( dFcy / 16 / Uart2Parm.dBaudRate) - 1;
	Uart1Parm.dBaudRateTcy =  ( dFcy / 16 / 4800) - 1;
	
	EEPROMADDR = 0xF000+2*0x1C;
  	ReadEE(__builtin_tblpage(&EPConfigS[0]),EEPROMADDR,&KeyParm.SaveParms[0x1C], WORD);
	
	if(KeyParm.SaveParms[0x1C]>3)
		KeyParm.SaveParms[0x1C]=1;
	else if(KeyParm.SaveParms[0x1C]<0)
		KeyParm.SaveParms[0x1C]=1;
	Uart2Parm.dPDSEL = KeyParm.SaveParms[0x1C];
	
	Uart1Parm.dPDSEL = 0;
	
}



void StateInit(void)
{
	unsigned int i = 0;
	
	//************* 读运行参�?******************
	for(i = 0; i < 128; i ++)
    {
    	EEPROMADDR = 0xF000 + 2 * i;
    	ReadEE(__builtin_tblpage(&EPConfigS[0]),EEPROMADDR,&KeyParm.SaveParms[i], WORD);
	}
	
	for(i=0;i<16;i++)
    {
    	EEPROMADDR = 0xF000 + 2 * i + 256;
    	ReadEE(__builtin_tblpage(&EPEndErrorSave[0]),EEPROMADDR,&ErrorParm.EndErrorSave[i], WORD);
		
    	EEPROMADDR = 0xF000 + 2 * i + 288;
    	ReadEE(__builtin_tblpage(&EPErrorSaveState[0]),EEPROMADDR,&ErrorParm.ErrorSaveState[i], WORD);

    	EEPROMADDR = 0xF000 + 2 * i + 320;
    	ReadEE(__builtin_tblpage(&EPErrorSaveMainMeau[0]),EEPROMADDR,&ErrorParm.ErrorSaveMainMeau[i], WORD);

    	EEPROMADDR = 0xF000 + 2 * i + 352;
    	ReadEE(__builtin_tblpage(&EPErrorSaveBackupMeau[0]),EEPROMADDR,&ErrorParm.ErrorSaveBackupMeau[i], WORD);

    	EEPROMADDR = 0xF000 + 2 * i + 384;
    	ReadEE(__builtin_tblpage(&EPErrorSaveIUVW[0]),EEPROMADDR,&ErrorParm.ErrorSaveIUVW[i], WORD);

    	EEPROMADDR = 0xF000 + 2 * i + 416;
    	ReadEE(__builtin_tblpage(&EPErrorSaveUin[0]),EEPROMADDR,&ErrorParm.ErrorSaveUin[i], WORD);

	}
	
//************* 计算参数�?******************
	//可编程IO输入
	if(KeyParm.SaveParms[0x40]>18)
		KeyParm.SaveParms[0x40]=18;
	else if(KeyParm.SaveParms[0x40]<0)
		KeyParm.SaveParms[0x40]=18;
	KeyParm.In1=KeyParm.SaveParms[0x40];
	
	if(KeyParm.SaveParms[0x41]>18)
		KeyParm.SaveParms[0x41]=18;
	else if(KeyParm.SaveParms[0x41]<0)
		KeyParm.SaveParms[0x41]=18;
	KeyParm.In2=KeyParm.SaveParms[0x41];
	
	if(KeyParm.SaveParms[0x42]>18)
		KeyParm.SaveParms[0x42]=18;
	else if(KeyParm.SaveParms[0x42]<0)
		KeyParm.SaveParms[0x42]=18;
	KeyParm.In3=KeyParm.SaveParms[0x42];
	
	if(KeyParm.SaveParms[0x43]>18)
		KeyParm.SaveParms[0x43]=18;
	else if(KeyParm.SaveParms[0x43]<0)
		KeyParm.SaveParms[0x43]=18;
	KeyParm.In4=KeyParm.SaveParms[0x43];
	
	if(KeyParm.SaveParms[0x44]>18)
		KeyParm.SaveParms[0x44]=18;
	else if(KeyParm.SaveParms[0x44]<0)
		KeyParm.SaveParms[0x44]=18;
	KeyParm.In5=KeyParm.SaveParms[0x44];

	if(KeyParm.SaveParms[0x45]>18)
		KeyParm.SaveParms[0x45]=18;
	else if(KeyParm.SaveParms[0x45]<0)
		KeyParm.SaveParms[0x45]=18;
	KeyParm.In6=KeyParm.SaveParms[0x45];
	
	if(KeyParm.SaveParms[0x46]>18)
		KeyParm.SaveParms[0x46]=18;
	else if(KeyParm.SaveParms[0x46]<0)
		KeyParm.SaveParms[0x46]=18;
	KeyParm.In7=KeyParm.SaveParms[0x46];
	
	if(KeyParm.SaveParms[0x47]>18)
		KeyParm.SaveParms[0x47]=18;
	else if(KeyParm.SaveParms[0x47]<0)
		KeyParm.SaveParms[0x47]=18;
	KeyParm.In8=KeyParm.SaveParms[0x47];
	
	KeyParm.InLogic=KeyParm.SaveParms[0x48];
	
	
	//可编程IO输出
	if(KeyParm.SaveParms[0x50]>21)
		KeyParm.SaveParms[0x50]=21;
	else if(KeyParm.SaveParms[0x50]<0)
		KeyParm.SaveParms[0x50]=21;
	KeyParm.Out1=KeyParm.SaveParms[0x50];
	
	if(KeyParm.SaveParms[0x51]>21)
		KeyParm.SaveParms[0x51]=21;
	else if(KeyParm.SaveParms[0x51]<0)
		KeyParm.SaveParms[0x51]=21;
	KeyParm.Out2=KeyParm.SaveParms[0x51];
	
	if(KeyParm.SaveParms[0x52]>21)
		KeyParm.SaveParms[0x52]=21;
	else if(KeyParm.SaveParms[0x52]<0)
		KeyParm.SaveParms[0x52]=8;
	KeyParm.Out3=KeyParm.SaveParms[0x52];
	
	if(KeyParm.SaveParms[0x53]>21)
		KeyParm.SaveParms[0x53]=21;
	else if(KeyParm.SaveParms[0x53]<0)
		KeyParm.SaveParms[0x53]=21;
	KeyParm.Out4=KeyParm.SaveParms[0x53];
	
	if(KeyParm.SaveParms[0x54]>21)
		KeyParm.SaveParms[0x54]=21;
	else if(KeyParm.SaveParms[0x54]<0)
		KeyParm.SaveParms[0x54]=21;
	KeyParm.Out5=KeyParm.SaveParms[0x54];
	
	if(KeyParm.SaveParms[0x55]>21)
		KeyParm.SaveParms[0x55]=21;
	else if(KeyParm.SaveParms[0x55]<0)
		KeyParm.SaveParms[0x55]=21;
	KeyParm.Out6=KeyParm.SaveParms[0x55];
	
	if(KeyParm.SaveParms[0x56]>21)
		KeyParm.SaveParms[0x56]=21;
	else if(KeyParm.SaveParms[0x56]<0)
		KeyParm.SaveParms[0x56]=21;
	KeyParm.Out7=KeyParm.SaveParms[0x56];
	
	if(KeyParm.SaveParms[0x57]>21)
		KeyParm.SaveParms[0x57]=21;
	else if(KeyParm.SaveParms[0x57]<0)
		KeyParm.SaveParms[0x57]=21;
	KeyParm.Out8=KeyParm.SaveParms[0x57];

	if(KeyParm.SaveParms[0x58]>21)
		KeyParm.SaveParms[0x58]=21;
	else if(KeyParm.SaveParms[0x58]<0)
		KeyParm.SaveParms[0x58]=21;
	KeyParm.Out9=KeyParm.SaveParms[0x58];
	
	if(KeyParm.SaveParms[0x59]>21)
		KeyParm.SaveParms[0x59]=21;
	else if(KeyParm.SaveParms[0x59]<0)
		KeyParm.SaveParms[0x59]=21;
	KeyParm.Out10=KeyParm.SaveParms[0x59];

	KeyParm.OutLogic=KeyParm.SaveParms[0x5A];
	KeyParm.OutLogic = - KeyParm.OutLogic;
	KeyParm.OutLogic = KeyParm.OutLogic - 1;
	
	
	//控制模式
	if(KeyParm.SaveParms[0x10]>1)
		KeyParm.SaveParms[0x10]=0;
	else if(KeyParm.SaveParms[0x10]<0)
		KeyParm.SaveParms[0x10]=0;
	KeyParm.CtrMode=KeyParm.SaveParms[0x10];
	
	//启动模式
	if(KeyParm.SaveParms[0x11]>3)
		KeyParm.SaveParms[0x11]=0;
	else if(KeyParm.SaveParms[0x11]<0)
		KeyParm.SaveParms[0x11]=0;
	KeyParm.StartMode=KeyParm.SaveParms[0x11];

	//停止模式
	if(KeyParm.SaveParms[0x12]>2)
		KeyParm.SaveParms[0x12]=0;
	else if(KeyParm.SaveParms[0x12]<0)
		KeyParm.SaveParms[0x12]=0;
	KeyParm.StopMode=KeyParm.SaveParms[0x12];
	
	//运行方式
	if(KeyParm.SaveParms[0x13]>1)
		KeyParm.SaveParms[0x13]=0;
	else if(KeyParm.SaveParms[0x13]<0)
		KeyParm.SaveParms[0x13]=0;
	KeyParm.RunMode=KeyParm.SaveParms[0x13];
	
	//测量量程
	if(KeyParm.SaveParms[0x14]>19999)
		KeyParm.SaveParms[0x14]=0;
	else if(KeyParm.SaveParms[0x14]<0)
		KeyParm.SaveParms[0x14]=0;
	MeauParm.MainMeauMax=KeyParm.SaveParms[0x14];
	
	MeauParm.MainMul = 1121;
	MeauParm.MainAdd = 99614;
	
	//测量整定
	if(KeyParm.SaveParms[0x15]>19999)
		KeyParm.SaveParms[0x15]=10000;
	else if(KeyParm.SaveParms[0x15]<0)
		KeyParm.SaveParms[0x15]=10000;
	if(KeyParm.SaveParms[0x15] > 9999)
		MeauParm.MainMeauFine=KeyParm.SaveParms[0x15];
	else MeauParm.MainMeauFine = 10000 - KeyParm.SaveParms[0x15];
	
	//电压整定
	if(KeyParm.SaveParms[0x17] < 0)
		KeyParm.SaveParms[0x17] = 4000;
	else if(KeyParm.SaveParms[0x17] > 19999)
		KeyParm.SaveParms[0x17] = 4000;	
	SysParms.MaxMeauVol = KeyParm.SaveParms[0x17];
	
	//电流整定
	if(KeyParm.SaveParms[0x18] < 0)
		KeyParm.SaveParms[0x18] = 3000;
	else if(KeyParm.SaveParms[0x18] > 29999)
		KeyParm.SaveParms[0x18] = 3000;	
	SysParms.MaxMeauCur = KeyParm.SaveParms[0x18];
	
	//电压修正
	if(KeyParm.SaveParms[0x19] < 0)
		KeyParm.SaveParms[0x19] = 3000;
	else if(KeyParm.SaveParms[0x19] > 19999)
		KeyParm.SaveParms[0x19] = 3000;	
	SysParms.AddMeauVol = KeyParm.SaveParms[0x19];
	
	//串口地址
	if(KeyParm.SaveParms[0x1A]>255)
		KeyParm.SaveParms[0x1A]=1;
	else if(KeyParm.SaveParms[0x1A]<0)
		KeyParm.SaveParms[0x1A]=1;
	Uart2Parm.Addr = KeyParm.SaveParms[0x1A];											

	//功能参数
	if(KeyParm.SaveParms[0X60] < 10)
		KeyParm.SaveParms[0X60] = 300;
	else if(KeyParm.SaveParms[0X60] > 10000)
		KeyParm.SaveParms[0X60] = 300;
	SysParms.RatePower = KeyParm.SaveParms[0X60];
	
	if(KeyParm.SaveParms[0X61] < 20)
		KeyParm.SaveParms[0X61] = 600;
	else if(KeyParm.SaveParms[0X61] > 19999)
		KeyParm.SaveParms[0X61] = 600;
	SysParms.RateCur = KeyParm.SaveParms[0X61];	
	
	if(KeyParm.SaveParms[0X62] < 220)
		KeyParm.SaveParms[0X62] = 380;
	else if(KeyParm.SaveParms[0X62] > 440)
		KeyParm.SaveParms[0X62] = 380;
	SysParms.RateVol = KeyParm.SaveParms[0X62] * 10;	
	
	
	if(KeyParm.SaveParms[0X63] < 100)
		KeyParm.SaveParms[0X63] = 450;
	else if(KeyParm.SaveParms[0X63] > 500)
		KeyParm.SaveParms[0X63] = 450;
	SysParms.LimitCar = ( (long)SysParms.RateCur * KeyParm.SaveParms[0X63])  / 100;	
	
	if(KeyParm.SaveParms[0X64] < 0)
		KeyParm.SaveParms[0X64] = 100;
	else if(KeyParm.SaveParms[0X64] > 5999)
		KeyParm.SaveParms[0X64] = 6000;
	SoftRunParms.PrepareTime = KeyParm.SaveParms[0X64] * 10;
	
	if(KeyParm.SaveParms[0X65] < 0)
		KeyParm.SaveParms[0X65] = 100;
	else if(KeyParm.SaveParms[0X65] > 5999)
		KeyParm.SaveParms[0X65] = 5999;
	SoftRunParms.PrepareDelay = KeyParm.SaveParms[0X65] * 10;
	
	if(KeyParm.SaveParms[0X66] > 19999)
		KeyParm.SaveParms[0X66] = 100;
	else if(KeyParm.SaveParms[0X66]<0)
		KeyParm.SaveParms[0X66]=100;
	MeauParm.BackupMeauMax=KeyParm.SaveParms[0X66];
	
	MeauParm.BackupMul = 1121;
	MeauParm.BackupAdd = 99614;
	
	if(KeyParm.SaveParms[0X67]>19999)
		KeyParm.SaveParms[0X67]=10000;
	else if(KeyParm.SaveParms[0X67]<0)
		KeyParm.SaveParms[0X67]=10000;
	if(KeyParm.SaveParms[0X67] > 9999)
		MeauParm.BackupMeauFine=KeyParm.SaveParms[0X67];
	else MeauParm.BackupMeauFine = 10000 - KeyParm.SaveParms[0X67];
	
	if(KeyParm.SaveParms[0X68]>19999)
		KeyParm.SaveParms[0X68]=75;
	else if(KeyParm.SaveParms[0X68]<0)
		KeyParm.SaveParms[0X68]=75;
	AutoRunParm.FillGas=KeyParm.SaveParms[0X68];
	
	if(KeyParm.SaveParms[0X69]>19999)
		KeyParm.SaveParms[0X69]=40;
	else if(KeyParm.SaveParms[0X69]<0)
		KeyParm.SaveParms[0X69]=40;
	AutoRunParm.FillOil=KeyParm.SaveParms[0X69];
	
	
	if(KeyParm.SaveParms[0X6A] < 0)
		KeyParm.SaveParms[0X6A] = 0;
	else if(KeyParm.SaveParms[0X6A] > 1)
		KeyParm.SaveParms[0X6A] = 0;
	KeyParm.FillGasMode = KeyParm.SaveParms[0X6A];
	
	if(KeyParm.SaveParms[0X6b] < 1)
		KeyParm.SaveParms[0X6b] = 1;
	else if(KeyParm.SaveParms[0X6b] > 8)
		KeyParm.SaveParms[0X6b] = 1;
	Uart1Parm.Addr = KeyParm.SaveParms[0X6b] - 1;
	
	if(KeyParm.SaveParms[0X6c] < 1)
		KeyParm.SaveParms[0X6c] = 9;
	else if(KeyParm.SaveParms[0X6c] > 8)
		KeyParm.SaveParms[0X6c] = 9;
	Uart1Parm.AddrMax = KeyParm.SaveParms[0X6c] - 1;
	
	if(KeyParm.SaveParms[0X6d] < 0)
		KeyParm.SaveParms[0X6d] = 250;
	else if(KeyParm.SaveParms[0X6d] > 9999)
		KeyParm.SaveParms[0X6d] = 250;
	KeyParm.BackupMeauHigh = KeyParm.SaveParms[0X6d];
	
	if(KeyParm.SaveParms[0X6e] < 0)
		KeyParm.SaveParms[0X6e] = 160;
	else if(KeyParm.SaveParms[0X6e] > 9999)
		KeyParm.SaveParms[0X6e] = 160;
	KeyParm.BackupMeauLow = KeyParm.SaveParms[0X6e];

	//电机保护参数
	if(KeyParm.SaveParms[0x20] < 1)
		KeyParm.SaveParms[0x20] = 1;
	else if(KeyParm.SaveParms[0x20] > 999)
		KeyParm.SaveParms[0x20] = 10;
	ErrorParm.HotCommTime = KeyParm.SaveParms[0x20];
	
	if(KeyParm.SaveParms[0x21] < 1)
		KeyParm.SaveParms[0x21] = 1;
	else if(KeyParm.SaveParms[0x21] > 999)
		KeyParm.SaveParms[0x21] = 10;
	ErrorParm.ConnectCurTime = KeyParm.SaveParms[0x21];
	
	if(KeyParm.SaveParms[0x22] < 50)
		KeyParm.SaveParms[0x22] = 100;
	else if(KeyParm.SaveParms[0x22] > 500)
		KeyParm.SaveParms[0x22] = 100;
	CurParms.OverCur = ( (long) SysParms.RateCur * KeyParm.SaveParms[0x22] ) / 100;
	
	if(KeyParm.SaveParms[0x23] < 1)
		KeyParm.SaveParms[0x23] = 1;
	else if(KeyParm.SaveParms[0x23] > 999)
		KeyParm.SaveParms[0x23] = 10;
	CurParms.OverCurTime = KeyParm.SaveParms[0x23];	
	
	
	if(KeyParm.SaveParms[0x24] < 10)
		KeyParm.SaveParms[0x24] = 10;
	else if(KeyParm.SaveParms[0x24] > 100)
		KeyParm.SaveParms[0x24] = 10;
	CurParms.UnbalanceCur = ( (long) SysParms.RateCur * KeyParm.SaveParms[0x24] ) / 100;
	
	if(KeyParm.SaveParms[0x25] < 1)
		KeyParm.SaveParms[0x25] = 1;
	else if(KeyParm.SaveParms[0x25] > 999)
		KeyParm.SaveParms[0x25] = 10;
	CurParms.UnbalanceCurTime = KeyParm.SaveParms[0x25];
	
	if(KeyParm.SaveParms[0x26] < 10)
		KeyParm.SaveParms[0x26] = 10;
	else if(KeyParm.SaveParms[0x26] > 100)
		KeyParm.SaveParms[0x26] = 10;
	CurParms.LowCur = ( (long) SysParms.RateCur * KeyParm.SaveParms[0x26] ) / 100;
	
	if(KeyParm.SaveParms[0x27] < 1)
		KeyParm.SaveParms[0x27] = 1;
	else if(KeyParm.SaveParms[0x27] > 999)
		KeyParm.SaveParms[0x27] = 10;
	CurParms.LowCurTime = KeyParm.SaveParms[0x27] ;
	
	if(KeyParm.SaveParms[0x28] < 100)
		KeyParm.SaveParms[0x28] = 100;
	else if(KeyParm.SaveParms[0x28] > 200)
		KeyParm.SaveParms[0x28] = 100;
	VolParms.HighVol = ( (long) SysParms.RateVol * KeyParm.SaveParms[0x28] ) / 100;
	
	if(KeyParm.SaveParms[0x29] < 1)
		KeyParm.SaveParms[0x29] = 1;
	else if(KeyParm.SaveParms[0x29] > 999)
		KeyParm.SaveParms[0x29] = 10;
	VolParms.HighVolTime = KeyParm.SaveParms[0x29];
	
	if(KeyParm.SaveParms[0x2a] < 10)
		KeyParm.SaveParms[0x2a] = 10;
	else if(KeyParm.SaveParms[0x2a] > 100)
		KeyParm.SaveParms[0x2a] = 10;
	VolParms.LowVol = ( (long) SysParms.RateVol * KeyParm.SaveParms[0x2a] ) / 100;
	
	if(KeyParm.SaveParms[0x2b] < 1)
		KeyParm.SaveParms[0x2b] = 1;
	else if(KeyParm.SaveParms[0x2b] > 999)
		KeyParm.SaveParms[0x2b] = 10;
	VolParms.LowVolTime = KeyParm.SaveParms[0x2b];
	
	if(KeyParm.SaveParms[0x2c] < 1)
		KeyParm.SaveParms[0x2c] = 1;
	else if(KeyParm.SaveParms[0x2c] > 9)
		KeyParm.SaveParms[0x2c] = 3;
	CurParms.UnLimitTimeCur = KeyParm.SaveParms[0x2c] * 5000;
	CurParms.UnLimitCur = SysParms.RateCur * 120 / 100;
	
	if(KeyParm.SaveParms[0x2d] < 1)
		KeyParm.SaveParms[0x2d] = 1;
	else if(KeyParm.SaveParms[0x2d] > 999)
		KeyParm.SaveParms[0x2d] = 10;
	ErrorParm.DisconTime = KeyParm.SaveParms[0x2d] * 20;                     
	
	
	ErrorParm.PassError = KeyParm.SaveParms[0x2e];
	ErrorParm.PassError = ErrorParm.PassError & 0xFFFF;
	ErrorParm.PassError = - ErrorParm.PassError;
	ErrorParm.PassError = ErrorParm.PassError - 1;
	
	//起停参数
	if(KeyParm.SaveParms[0x30] < 10)
		KeyParm.SaveParms[0x30] = 30;
	else if(KeyParm.SaveParms[0x30] > 80)
		KeyParm.SaveParms[0x30] = 30;
	AX_int_Init = 100 - KeyParm.SaveParms[0x30];
	SoftRunParms.StartData = ( (long) DataMax  / 100 ) * AX_int_Init;				//电压斜坡启动初始电压
	
	if(KeyParm.SaveParms[0x31] < 1)
		KeyParm.SaveParms[0x31] = 100;
	else if(KeyParm.SaveParms[0x31] > 9999)
		KeyParm.SaveParms[0x31] = 100;
	SoftRunParms.LoopData = DataMaxLoop / KeyParm.SaveParms[0x31];					//电压斜坡启动步长
	
		
	if(KeyParm.SaveParms[0x32] < 10)
		KeyParm.SaveParms[0x32] = 40;
	else if(KeyParm.SaveParms[0x32] > 80)
		KeyParm.SaveParms[0x32] = 40;
	AX_int_Init = 100 - KeyParm.SaveParms[0x32];
	SoftRunParms.JumpStartData = ( (long) DataMax  / 100 ) * AX_int_Init;			//突跳力矩启动电压	
	
	if(KeyParm.SaveParms[0x33] < 1)
		KeyParm.SaveParms[0x33] = 5;
	else if(KeyParm.SaveParms[0x33] > 100)
		KeyParm.SaveParms[0x33] = 5;
	SoftRunParms.JumpLoopData = ( (long) KeyParm.SaveParms[0x33] * 1000 ) / 25;		//突跳力矩启动步长
	
	if(KeyParm.SaveParms[0x34] < 100)
		KeyParm.SaveParms[0x34] = 200;
	else if(KeyParm.SaveParms[0x34] > 500)
		KeyParm.SaveParms[0x34] = 200;
	SoftRunParms.LimitCar = ( (long) SysParms.RateCur * KeyParm.SaveParms[0x34] ) / 100;	//限流启动限流电流
	
	if(KeyParm.SaveParms[0x35] < 60)
		KeyParm.SaveParms[0x35] = 85;
	else if(KeyParm.SaveParms[0x35] > 100)
		KeyParm.SaveParms[0x35] = 85;
	AX_int_Init = 100 - KeyParm.SaveParms[0x35];
	SoftRunParms.EndData = ( (long) DataMax  / 100 ) * AX_int_Init;					//启动限制电压
	
	if(KeyParm.SaveParms[0x36] < 10)
		KeyParm.SaveParms[0x36] = 40;
	else if(KeyParm.SaveParms[0x36] > 100)
		KeyParm.SaveParms[0x36] = 40;
	AX_int_Init = 100 - KeyParm.SaveParms[0x36];
	SoftRunParms.SoftStopStartData = ( (long) DataMax  / 100 ) * AX_int_Init;		//软停机初始电�?
	SoftRunParms.SoftStopEndData = ( (long) DataMax  / 100 ) * 70;
	
	if(KeyParm.SaveParms[0x37] < 1)
		KeyParm.SaveParms[0x37] = 10;
	else if(KeyParm.SaveParms[0x37] > 999)
		KeyParm.SaveParms[0x37] = 10;
	SoftRunParms.SoftStopLoopData = DataMaxLoop / KeyParm.SaveParms[0x37];			//软停机步�?
		
	if(KeyParm.SaveParms[0x38] < 10)
		KeyParm.SaveParms[0x38] = 50;
	else if(KeyParm.SaveParms[0x38] > 100)
		KeyParm.SaveParms[0x38] = 50;
	AX_int_Init = 100 - KeyParm.SaveParms[0x38];
	SoftRunParms.StopEndData = ( (long) DataMax  / 100 ) * AX_int_Init;
	SoftRunParms.StopEndData = SoftRunParms.StopEndData / dqDataGei;				//刹车电压
	
		
	if(KeyParm.SaveParms[0x39] < 1)
		KeyParm.SaveParms[0x39] = 3;
	else if(KeyParm.SaveParms[0x39] > 999)
		KeyParm.SaveParms[0x39] = 3;
	SoftRunParms.StopLoopData = DataMaxLoop / KeyParm.SaveParms[0x39];				//刹车停止步长
	
	//自动运行参数
	if(KeyParm.SaveParms[0x00]>19999)
		KeyParm.SaveParms[0x00]=220;
	else if(KeyParm.SaveParms[0x00]<0)
		KeyParm.SaveParms[0x00]=220;
	AutoRunParm.Normal=KeyParm.SaveParms[0x00];
	
	if(KeyParm.SaveParms[0x01]>19999)
		KeyParm.SaveParms[0x01]=210;
	else if(KeyParm.SaveParms[0x01]<0)
		KeyParm.SaveParms[0x01]=210;
	AutoRunParm.Backup=KeyParm.SaveParms[0x01];
	
	if(KeyParm.SaveParms[0x02]>19999)
		KeyParm.SaveParms[0x02]=205;
	else if(KeyParm.SaveParms[0x02]<0)
		KeyParm.SaveParms[0x02]=205;
	AutoRunParm.Backup2=KeyParm.SaveParms[0x02];
	
	if(KeyParm.SaveParms[0x03]>19999)
		KeyParm.SaveParms[0x03]=200;
	else if(KeyParm.SaveParms[0x03]<0)
		KeyParm.SaveParms[0x03]=200;
	AutoRunParm.Backup3=KeyParm.SaveParms[0x03];
	
	if(KeyParm.SaveParms[0x04]>19999)
		KeyParm.SaveParms[0x04]=195;
	else if(KeyParm.SaveParms[0x04]<0)
		KeyParm.SaveParms[0x04]=195;
	AutoRunParm.Backup4=KeyParm.SaveParms[0x04];
	
	if(KeyParm.SaveParms[0x05]>19999)
		KeyParm.SaveParms[0x05]=190;
	else if(KeyParm.SaveParms[0x05]<0)
		KeyParm.SaveParms[0x05]=190;
	AutoRunParm.Backup5=KeyParm.SaveParms[0x05];
	
	if(KeyParm.SaveParms[0x06]>19999)
		KeyParm.SaveParms[0x06]=185;
	else if(KeyParm.SaveParms[0x06]<0)
		KeyParm.SaveParms[0x06]=185;
	AutoRunParm.Backup6=KeyParm.SaveParms[0x06];
	
	if(KeyParm.SaveParms[0x07]>19999)
		KeyParm.SaveParms[0x07]=180;
	else if(KeyParm.SaveParms[0x07]<0)
		KeyParm.SaveParms[0x07]=180;
	AutoRunParm.Backup7=KeyParm.SaveParms[0x07];
	
	if(KeyParm.SaveParms[0x08]>19999)
		KeyParm.SaveParms[0x08]=240;
	else if(KeyParm.SaveParms[0x08]<0)
		KeyParm.SaveParms[0x08]=240;
	AutoRunParm.Stop=KeyParm.SaveParms[0x08];
	
	if(KeyParm.SaveParms[0x09]>19999)
		KeyParm.SaveParms[0x09]=300;
	else if(KeyParm.SaveParms[0x09]<0)
		KeyParm.SaveParms[0x09]=300;
	AutoRunParm.Limit=KeyParm.SaveParms[0x09];
	
	if(KeyParm.SaveParms[0x0a]>19999)
		KeyParm.SaveParms[0x0a]=270;
	else if(KeyParm.SaveParms[0x0a]<0)
		KeyParm.SaveParms[0x0a]=270;
	AutoRunParm.OverHigh=KeyParm.SaveParms[0x0a];
	
	if(KeyParm.SaveParms[0x0b]>19999)
		KeyParm.SaveParms[0x0b]=160;
	else if(KeyParm.SaveParms[0x0b]<0)
		KeyParm.SaveParms[0x0b]=160;
	AutoRunParm.OverLow=KeyParm.SaveParms[0x0b];
	
	if(KeyParm.SaveParms[0x0c]>19999)
		KeyParm.SaveParms[0x0c]=280;
	else if(KeyParm.SaveParms[0x0c]<0)
		KeyParm.SaveParms[0x0B]=280;
	AutoRunParm.AboveHigh=KeyParm.SaveParms[0x0c];
	
	if(KeyParm.SaveParms[0x0d]>19999)
		KeyParm.SaveParms[0x0d]=130;
	else if(KeyParm.SaveParms[0x0d]<0)
		KeyParm.SaveParms[0x0d]=130;
	AutoRunParm.AboveLow=KeyParm.SaveParms[0x0d];
	
	if(KeyParm.SaveParms[0x0e]>19999)
		KeyParm.SaveParms[0x0e]=1;
	else if(KeyParm.SaveParms[0x0e]<0)
		KeyParm.SaveParms[0x0e]=1;
	AutoRunParm.ChangeTimes = KeyParm.SaveParms[0x0e];
	
	if(KeyParm.SaveParms[0x5b]>2)
		KeyParm.SaveParms[0x5b]=0;
	else if(KeyParm.SaveParms[0x5b]<0)
		KeyParm.SaveParms[0x5b]=0;
	DaOutParm.DaOutput1=KeyParm.SaveParms[0x5b];
	
	if(KeyParm.SaveParms[0x5c]>2)
		KeyParm.SaveParms[0x5c]=1;
	else if(KeyParm.SaveParms[0x5c]<0)
		KeyParm.SaveParms[0x5c]=1;
	DaOutParm.DaOutput2=KeyParm.SaveParms[0x5c];
	
	
	DaOutParm.OutData1Add = 1278;
	DaOutParm.OutData2Add = 1278;
	
	switch(DaOutParm.DaOutput1)
	{
		case 0:
			DaOutParm.OutData1Mul = 2333696 / MeauParm.MainMeauMax;
			break;
		case 1:
			DaOutParm.OutData1Mul = 2333696 / MeauParm.BackupMeauMax;
			break;
		case 2:
			DaOutParm.OutData1Mul = 2333696 / SysParms.MaxMeauCur;
			break;
		default:
			DaOutParm.OutData1Mul = 2333696 / MeauParm.MainMeauMax;
			break;
	}
	
	switch(DaOutParm.DaOutput2)
	{
		case 0:
			DaOutParm.OutData2Mul = 2333696 /  MeauParm.MainMeauMax;
			break;
		case 1:
			DaOutParm.OutData2Mul = 2333696 / MeauParm.BackupMeauMax;
			break;
		case 2:
			DaOutParm.OutData2Mul = 2333696 / SysParms.MaxMeauCur;
			break;
		default:
			DaOutParm.OutData2Mul = 2333696 / MeauParm.BackupMeauMax;
			break;
	}
	
	if(AutoRunParm.Normal > AutoRunParm.Stop)
		RunState.HighByLow = 0;
	else RunState.HighByLow = 1;
	
	AutoRunParm.RunParm[0] = AutoRunParm.Normal;
	AutoRunParm.RunParm[1] = AutoRunParm.Backup;
	AutoRunParm.RunParm[2] = AutoRunParm.Backup2;
	AutoRunParm.RunParm[3] = AutoRunParm.Backup3;
	AutoRunParm.RunParm[4] = AutoRunParm.Backup4;
	AutoRunParm.RunParm[5] = AutoRunParm.Backup5;
	AutoRunParm.RunParm[6] = AutoRunParm.Backup6;
	AutoRunParm.RunParm[7] = AutoRunParm.Backup7;
	
	
	// **************** 变量赋初�?************************
	PWMParams.StartOut = 0;
	PwmState.StartOut = 0;
	PwmState.UoutPhyH = 0;
	PwmState.UoutPhyL = 0;
	PwmState.VoutPhyH = 0;
	PwmState.VoutPhyL = 0;
	PwmState.WoutPhyH = 0;
	PwmState.WoutPhyL = 0;
	PwmState.UoutH = 0;
	PwmState.UoutL = 0;
	PwmState.VoutH = 0;
	PwmState.VoutL = 0;
	PwmState.WoutH = 0;
	PwmState.WoutL = 0;
	PWMParams.Duty1H = 0;
	PWMParams.Duty1L = 0;
	PWMParams.Duty2H = 0;
	PWMParams.Duty2L = 0;
	PWMParams.Duty3H = 0;
	PWMParams.Duty3L = 0;
	PWMParams.Delay1H = 0;
	PWMParams.Delay1L = 0;
	PWMParams.Delay2H = 0;
	PWMParams.Delay2L = 0;
	PWMParams.Delay3H = 0;
	PWMParams.Delay3L = 0;
	SoftRunParms.RunTime = 0;
	SoftRunParms.EndTime = 0;
	StartState.SoftStopEnd = 0;
	StartState.SoftStopStartEnd = 0;
	StartState.SoftRunEnd = 0;
	StartState.SoftStartEnd = 0;
	SoftRunParms.LimitCarTimes = 0;
	CurParms.MaxIU = 0;
	CurParms.CarDescendTimesIU = 0;
	CurParms.CarUpTimesIU = 0;
	StartState.UpCarIU = 0;
	CurParms.MaxIV = 0;
	CurParms.CarDescendTimesIV = 0;
	CurParms.CarUpTimesIV = 0;
	StartState.UpCarIV = 0;
	CurParms.MaxIW = 0;
	CurParms.CarDescendTimesIW = 0;
	CurParms.CarUpTimesIW = 0;
	StartState.UpCarIW = 0;
	StartState.LessCar = 0;
	CurParms.LessCarIUVW = 0;
	SoftRunParms.JumpRunTimes = 0;
	StartState.JumpRun = 0;
	StartState.BenJiRun = 0;
	StartState.ShaChe = 0;
	
	InsideIOState.Stop = 0;
	InsideIOState.IoStop = 0;
	
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
	
	Uart1Parm.RxErrorEnumerate = 6001;
	Uart1Parm.TxTimesEnumerate = 0;
	StartState.RoadRun = 0;
    StartState.PreStart = 0;
    StartState.SoftStart = 0;
    StartState.SoftStop = 0;
	Uart2Parm.TxTimes = 250;
	MainState.UartTxOff = 0;
    MainState.UartTxOn = 0;
    MainState.UartRx = 0;
    MainState.UartTx = 0;
    ErrorParm.EndError = 0;
    ErrorParm.InitError = 0;
    ErrorParm.ErrorTimes = 0;
    InsideIOState.ByPassOut = 1;
    InsideIOState.ComponentHot = 1;
    PWMParams.OnPWM = ActiveLongPWM;
    RunState.MainOpen = 1;
    RunState.BackupOpen = 1;
    RunState.StopOff = 1;
    
    Dsp_State_Start = RCON;
    RCON = 0;
    Dsp_State_Start = Dsp_State_Start & 0x0080;
    if(Dsp_State_Start == 0x0080)
    {
	    KeyParm.SaveParms[127] = 0;
		EEPROMADDR = 0xF000 + 2 * 127;
        EraseEE(__builtin_tblpage(&EPConfigS[0]),EEPROMADDR, WORD);
        WriteEE(&KeyParm.SaveParms[127],__builtin_tblpage(&EPConfigS[0]),EEPROMADDR, WORD);
	}

	LATCbits.LATC13 = 1;
    LATCbits.LATC14 = 1;
    LATDbits.LATD2 = 1;
    LATDbits.LATD3 = 1;
    LATDbits.LATD4 = 1;
    LATDbits.LATD5 = 1;
    LATDbits.LATD6 = 1;
    LATDbits.LATD7 = 1;
    LATDbits.LATD13= 1;
    LATDbits.LATD14 = 1;
    LATDbits.LATD15 = 1;
    LATGbits.LATG0 = 1; 
     
	if(Uart1Parm.Addr == 0)
		Uart1State.UartTx = 1;
    Uart1TxData();
    Uart1Parm.RunNumber = 0;
    AutoRunParm.RunNumber = Uart1Parm.Addr - Uart1Parm.RunNumber;
    
    //启动系统功能单元
	T1CONbits.TON = 1;              // start the timer1
    ADCON1bits.ADON=1;				//开AD转换
    IEC0bits.IC1IE = 1;				//允许IC1中断
    IEC0bits.IC2IE = 1;             //允许IC2中断
	IEC1bits.IC3IE = 1;             //允许IC3中断  
	IEC1bits.IC4IE = 1;             //允许IC4中断  
	IEC2bits.PWMIE = 1;  			// 使能PWM中断
	IEC0bits.SI2CIE = 1;			// 1 允许SI2C中断  
	IEC1bits.U2TXIE = 1;			// 1 允许U2TX中断 
	IEC1bits.U2RXIE = 1;			// 1 允许U2RX中断 
	IEC0bits.U1TXIE = 1;			// 1 允许U2TX中断 
	IEC0bits.U1RXIE = 1;			// 1 允许U2RX中断   
	
	
	if(Uart1Parm.AddrMax == 8)
	{
		IEC0bits.U1TXIE = 0;			// 1 允许U2TX中断 
		IEC0bits.U1RXIE = 0;			// 1 允许U2RX中断   
	}

	LATFbits.LATF0 = 0;
}


//IO口功能初始化
void SetupPorts( void )
{
// ============= Port A ==============

//        absent
//        absent
//        absent
//        absent

//        absent
//        absent
//        absent
//        absent

//        absent
// RA9    VREF-            
// RA10   VREF+      
//        absent

//        absent
//        absent
// RA14   INT3
// RA15   INT4

	TRISA = 0xFFFF;
	LATA = 0xFFFF;
	

// ============= Port B ==============

// RB0    PGD/EMUD/AN0/CN2			PGD
// RB1    PGC/EMUC/AN1/CN3			PGC
// RB2    AN2/SS1/CN4     			IN1-RB2		可编程输入接�?
// RB3    AN3/INDX/CN5				IN2-RB3 	可编程输入接�?

// RB4    AN4/QEA/CN6				IN3-RB4 	可编程输入接�?  
// RB5    AN5/QEB/CN7				IN4-RB5 	可编程输入接�?  
// RB6    AN6/OCFA					IN5-RB6 	可编程输入接�?  
// RB7    AN7						IN6-RB7 	可编程输入接�?  

// RB8    AN8						IN7-RB8 	可编程输入接�?  
// RB9    AN9						IN8-RB9 	可编程输入接�?  
// RB10   AN10						YF-AN10 	备用测量输入
// RB11   AN11						PF-AN11 	主测量输�?

// RB12   AN12						UF-AN12 	输入电压
// RB13   AN13						UIF-AN13 	U相电�?
// RB14   AN14						UIF-AN14 	V相电�?
// RB15   AN15						UIF-AN15 	W相电�?

    TRISB = 0xFFFF; 
    LATB  = 0XFFFF;

// ============= Port C ==============

//        absent
// RC1	  T2CK						GR-RC1		过热保护
//        absent
// RC3	  T4CK						PLIN-RC3	旁路接触器闭合检�?

//        absent
//        absent
//        absent
//        absent

//        absent
//        absent
//        absent
//        absent

//        absent
// RC13   EMUD1/SOSCI				OU0-RD0			旁路接触器输�?
// RC14   EMUC1/SOSCO/T1CK/CN0		OU1-RD1			可编程输�?	
// RC15   OSC2/CLKO                 	OSC2		晶振

    TRISC = 0x1FFF;     
    LATC  = 0XFFFF;

// ============= Port D ==============

// RD0    EMUC2/OC1				OU20mA1			4-20mA输出1	
// RD1    EMUD2/OC2				OU20mA1			4-20mA输出2	
// RD2    OC3                   OU2-RD2			可编程输�?	
// RD3    OC4                   OU3-RD3			可编程输�?	

// RD4    OC5/CN13              OU4-RD4			可编程输�?	
// RD5    OC6/CN14              OU5-RD5			可编程输�?
// RD6    OC7/CN15              OU6-RD6			可编程输�?
// RD7    OC8/CN16/UPDN         OU7-RD7			可编程输�?

// RD8    IC1					UAIN-IC1		A相电压同�?
// RD9    IC2					UBIN-IC2		B相电压同�?
// RD10   IC3					UCIN-IC3		C相电压同�?
// RD11   IC4					IAIN-IC4		A相电流同�?

// RD12   IC5
// RD13	  IC6					OU8-RD13		可编程输�?
// RD14	  IC7					OU9-RD14		可编程输�?
// RD15	  IC8					OU10-RD15		可编程输�?0

    TRISD = 0x0F00;
    LATD  = 0XFFFF;  

// ============= Port E ==============

// RE0    PWM1L                 Phase1 L
// RE1    PWM1H                 Phase1 H
// RE2    PWM2L                 Phase2 L
// RE3    PWM2H                 Phase2 H

// RE4    PWM3L                 Phase3 L
// RE5    PWM3H                 Phase3 H
// RE6    PWM4L
// RE7    PWM4H

// RE8    FLTA/INT1             FaultA
// RE9    FLTA/INT2
//        absent
//        absent

//        absent
//        absent
//        absent
//        absent

    TRISE = 0xFFC0;     
    LATE  = 0XFFFF;

// ============= Port F ==============

// RF0    C1RX                  	TRCS2-RF0		RS485外部通讯接口收发控制
// RF1    C1TX                      TRCS1-RF1		RS485并联通讯接口收发控制
// RF2    U1RX						U1RX			RS485并联通讯接口
// RF3    U1TX        				U1TX			RS485并联通讯接口

// RF4    U2RX/CN17                	U2RX			RS485外部通讯接口
// RF5    U2TX/CN18                	U2TX			RS485外部通讯接口
// RF6    EMUC3/SCK1/INT0			RUN-RF6			手动运行输入
// RF7    SDI1						STOP-RF7		停止运行输入
// RF8    EMUD3/SDO1				AUTO-RF8		自动运行输入
//        absent
//        absent
//        absent

//        absent
//        absent
//        absent
//        absent

    TRISF = 0xFFFC;     
    LATF  = 0XFFFF;

// ============= Port G ==============

// RG0    C2RX						RG0			LCD复位
// RG1    C2TX
// RG2    SCL						SCL			键盘接口
// RG3    SDA						SDA			键盘接口

//        absent
//        absent
// RG6    SCK2/CN8					BD0-RG6		拨码开�?�?
// RG7    SDI2/CN9					BD1-RG7		拨码开�?�?

// RG8    SDO2/CN10					BD2-RG7		拨码开�?�?
// RG9    SS2/CN11					BD3-RG8		拨码开�?�?        
//        absent               
//        absent

//        absent
//        absent
// 		  absent
//        absent
	
	TRISG = 0xFFFE;     
    LATG  = 0XFFFF;


}

//定时器初始化
void InitTimer( void )
{
//  Timer1初始�?

    T1CON = 0;					// 关闭定时�?
    TMR1 = 0;          			// clear timer1 register 
    T1CONbits.TSIDL = 0;        // 空闲模式下停止工�?  
    T1CONbits.TCS = 0; 			// set internal clock source
	T1CONbits.TCKPS = 0;		// Tcy / 1 作为输入时钟  
    PR1 = dTImer1Tcy;			// set period1 register 
    IPC0bits.T1IP = 5; 			// set priority level 
    IFS0bits.T1IF = 0; 			//clear interrupt flag 
    IEC0bits.T1IE = 1; 			// enable interrupts 
    SRbits.IPL = 3;    			//enable CPU priority levels 4-7

//Timer2初始�?

    T2CON = 0;                   // 关闭定时�?
    TMR2 = 0;                    // 复位定时�?计数�?
    T2CONbits.TSIDL = 0;         // 空闲模式下停止工�?
    T2CONbits.TGATE = 0;         // 禁止门控定时器累�?
    T2CONbits.TCS = 0;           // 使用Tcy 作为源时�?
    T2CONbits.TCKPS = 0;         // Tcy / 64 作为输入时钟
    T2CONbits.TON = 1;           // 开启timer2
    PR2 = 0x0FFF;                  // 中断周期 = 0.008 秒，预分频器分频比为64[3750suan]
    IPC1bits.T2IP = 5;
    IFS0bits.T2IF = 0;           // 清零timer2 中断标志
    IEC0bits.T2IE = 0;           // 允许timer2 中断 


//Timer3初始�?

    T3CON= 0;                    // 关闭定时�?
    TMR3 = 0;                    // 复位定时器计3数器
    T3CONbits.TSIDL = 0;         // 空闲模式下停止工�?
    T3CONbits.TGATE = 0;         // 禁止门控定时器累�?
    T3CONbits.TCS = 0;           // 使用Tcy 作为源时�?
    T3CONbits.TCKPS = 3;         // Tcy / 8 作为输入时钟
    T3CONbits.TON = 1;           // 开启timer3
    PR3 = 0x7FFF;                
    IEC0bits.T3IE = 0;           // 禁止timer3 中断


//  Timer4初始�?
/*
    T4CON = 0;
    T4CONbits.TSIDL = 1;        // 空闲模式下停止工�?  
    TMR4 = 0;          			// clear timer1 register 
    PR4 = dTImer4Tcy; 			// set period1 register 
    T4CONbits.TCS = 0; 			// set internal clock source 
    IPC5bits.T4IP = 5; 			// set priority level 
    IFS1bits.T4IF = 0; 			//clear interrupt flag 
    IEC1bits.T4IE = 1; 			// enable interrupts 
*/
}


//IO口跳变检测功能初始化
/*
void InitCN(void)
{
    CNEN1 = 0;
    CNEN2 = 0;
    CNEN1bits.CN0IE = 1; 				//开�?CN0 电平跳变引脚
    CNEN1bits.CN1IE = 1; 				//开�?CN1 电平跳变引脚
    CNEN1bits.CN2IE = 1; 				//开�?CN2 电平跳变引脚
    CNEN1bits.CN3IE = 1; 				//开�?CN3 电平跳变引脚
    CNEN1bits.CN4IE = 1; 				//开�?CN4 电平跳变引脚
    CNEN1bits.CN5IE = 1; 				//开�?CN5 电平跳变引脚
    
    CNPU1 = 0;
    CNPU2 = 0;
    CNPU1bits.CN0PUE = 1;				//开�?CN0 电平变化上拉
    CNPU1bits.CN1PUE = 1;				//开�?CN1 电平变化上拉
    CNPU1bits.CN2PUE = 1;				//开�?CN2 电平变化上拉
    CNPU1bits.CN3PUE = 1;				//开�?CN3 电平变化上拉
    CNPU1bits.CN4PUE = 1;				//开�?CN4 电平变化上拉
    CNPU1bits.CN5PUE = 1;				//开�?CN5 电平变化上拉
    

    IPC3bits.CNIP = 3;              //设置中断优先级为5
    IFS0bits.CNIF = 0;              //清零中断标志
    IEC0bits.CNIE = 1;              //允许CN中断
    
}
*/

void InitIC( void )
{
//	IC1初始�?
    IC1CON=0;                        //禁止捕捉模块
    IC1CONbits.ICTMR = 0;            //捕捉事件时捕捉TMR3的内�?
    IC1CONbits.ICI = 0;              //�?次捕捉事件中断一�?
    IC1CONbits.ICM = 1;              //每次下降沿捕捉事�?
   
    IPC0bits.IC1IP = 6;              //设置中断优先级为5
    IFS0bits.IC1IF = 0;              //清零中断标志
    IEC0bits.IC1IE = 0;              // 1 允许IC1中断

//	IC2初始�?
	IC2CON=0;                        //禁止捕捉模块
    IC2CONbits.ICTMR = 0;            //捕捉事件时捕捉TMR3的内�?
    IC2CONbits.ICI = 0;              //�?次捕捉事件中断一�?
    IC2CONbits.ICM = 1;              //每次下降沿捕捉事�?
   
    IPC1bits.IC2IP = 6;              //设置中断优先级为5
    IFS0bits.IC2IF = 0;              //清零中断标志
    IEC0bits.IC2IE = 0;              // 1 允许IC2中断
    
//	IC3初始�?
	IC3CON=0;                        //禁止捕捉模块
    IC3CONbits.ICTMR = 0;            //捕捉事件时捕捉TMR3的内�?
    IC3CONbits.ICI = 0;              //�?次捕捉事件中断一�?
    IC3CONbits.ICM = 1;              //每次下降沿捕捉事�?
   
    IPC7bits.IC3IP = 6;              //设置中断优先级为5
    IFS1bits.IC3IF = 0;              //清零中断标志
    IEC1bits.IC3IE = 0;              // 1 允许IC7中断  
    
//	IC4初始�?
	IC4CON=0;                        //禁止捕捉模块
    IC4CONbits.ICTMR = 0;            //捕捉事件时捕捉TMR3的内�?
    IC4CONbits.ICI = 0;              //�?次捕捉事件中断一�?
    IC4CONbits.ICM = 1;              //每次下降沿捕捉事�?
   
    IPC7bits.IC4IP = 6;              //设置中断优先级为5
    IFS1bits.IC4IF = 0;              //清零中断标志
    IEC1bits.IC4IE = 0;              // 1 允许IC7中断  


}

//PWM功能初始�?
void InitPWM( void )
{
	                      
	PTCON = 0x0000;    			// 禁止PWM ,自由运行模式,时基为Tcy
	PTPER = dLoopInTcy;     	// PWM计数周期设定
    PWMCON1 = 0x0777;  			// 复位后使能PWM 1,2,3 对工作在独立模式
    PWMCON2 = 0x0000;  			// PWM特殊事件触发器分频比�?�?，禁止改写，是能占空比更�?
    PWMCON2bits.IUE = 0;		// PDC寄存器立即更�?
    PWMCON2bits.OSYNC = 1;		// 改写同步
    
    PDC1 = 0x0000;     			// 初始化占空比  
    PDC2 = 0x0000;
    PDC3 = 0x0000;
    
	DTCON1 = (dDeadTime>>1);	// 死区时基2分频时的时间
    DTCON1bits.DTAPS=1;			//死区时基2分频
    OVDCON = 0x0000;     		//开始由PWM发生器控�?

	FLTACON = 0x0007;  			//故障引脚为低电平时，6路PWM输出无效 
    FLTACONbits.FLTAM=0;
    
	IPC10bits.FLTAIP=7;     	//设置过流故障中断为最高优先级中断
	IFS2bits.FLTAIF=0;      	//清FLTA故障中断标志�?（FLTA为过流故障）
	IEC2bits.FLTAIE = 1;    	//使能FLTA故障中断

            
    SEVTCMP = 0;             	// 0 不由PWM启动AD转换
    SEVTCMPbits.SEVTDIR = 0; 	// 0 ,特殊事件触发信号将在PWM 时基的向上计数周期产�?
    IPC9bits.PWMIP = 7;			// 
    IFS2bits.PWMIF = 0;   		// 清PWM中断标志�?
    IEC2bits.PWMIE = 1;  		// 使能PWM中断
    
    
}


//正交编码器初始化
/*
void InitQEI( void )
{
    ADPCFG = 0x0030;           			// 将QEI 引脚配置为数字输�?
    QEICONbits.QEIM = 0;         		// 禁止QEI 模块
    QEICONbits.CNTERR = 0;       		// 清除任何计数错误
    QEICONbits.QEISIDL = 1;      		// 休眠期间禁止工作
    QEICONbits.SWPAB = 0;        		// QEA 和QEB 不交�?
    QEICONbits.PCDOUT = 0;       		// 正常I/O 引脚操作，无需方向输出
    QEICONbits.POSRES = 0;       		// 禁止索引脉冲复位
    DFLTCONbits.CEID = 1;        		// 禁止计数错误中断
    DFLTCONbits.QEOUT = 0;       		// 对于QEn 引脚，禁止数字滤波器输出
	DFLTCONbits.QECK = 0;        		// 将QEn 的数字滤波器设置�?:1时钟分频[suan]
	DFLTCONbits.INDOUT = 0;      		// 索引脉冲滤波禁止
    POSCNT = 0;                  		// 复位位置计数�?
	MAXCNT = MotorParm.iCntsPerRev;		//2400;	//设成最大转一圈的最大脉�?
    QEICONbits.QEIM = 7;         		// 开启QEI，X4 模式，通过�?MAXCNT)匹配复位位置计数�?
}
*/

//AD转换功能初始�?
void InitAD(void)
{
// 1.配置端口引脚作为模拟输入，将相应位置0
    ADPCFG = 0xFFFF;        // Set all ports digital
    ADPCFGbits.PCFG10 = 0;   // AN5 analog
    ADPCFGbits.PCFG11 = 0;   // AN6 analog
    ADPCFGbits.PCFG12 = 0;   // AN7 analog
    ADPCFGbits.PCFG13 = 0;   // AN8 analog
    ADPCFGbits.PCFG14 = 0;   // AN7 analog
    ADPCFGbits.PCFG15 = 0;   // AN8 analog
    
// 2.选择参考电压源 ADCON2�?3—�?5�?
    ADCON2 = 0x0000;        
    ADCON2bits.VCFG = 1;    // 1 使用外部参考电�?
    ADCON2bits.CSCNA = 1;   // 扫描输入
    ADCON2bits.CHPS = 0;    // 转化CH0
    ADCON2bits.SMPI = 5;    // �?次转化完产成中断
    ADCON2bits.ALTS = 0;    // 总是采用MUX A开�?

// 3.选择模拟转换时钟ADCON3
    ADCON3 =  0x0000;        //使用内部时钟 
    ADCON3bits.SAMC = 0x02;
    ADCON3bits.ADCS = 0x3F;    // AD转换时钟选择 TAD =  6*Tcy  
 
// 4.AD输入选择ADCHS
    ADCHS=0x0000;
    ADCHSbits.CH0SA = 10;               // CH0,通道选择AN6
    ADCHSbits.CH0NA = 0;               
    
    //ADCHSbits.CH123SA = 1;               // CH0,通道选择AN6
    //ADCHSbits.CH123NA = 0;               
      
    
// 5.配置ADCSSL扫描选择寄存�?，不扫描�?
    ADCSSL = 0x0000;    
    ADCSSLbits.CSSL10 = 1;    //扫描输入2.3.6通道
    ADCSSLbits.CSSL11 = 1;
    ADCSSLbits.CSSL12 = 1;
    ADCSSLbits.CSSL13 = 1;
    ADCSSLbits.CSSL14 = 1;
    ADCSSLbits.CSSL15 = 1;
    
// 6.配置采样/转换过程ADCON1
    ADCON1 = 0;
    ADCON1bits.FORM = 0;    // 转换结果格式
	ADCON1bits.SSRC = 7;    //  "0" 手动启动AD转换
    ADCON1bits.ASAM = 1;    // 转换结束，自动采样开始为，置1使能
    ADCON1bits.SIMSAM = 1;	// 同时采样
    
// 7.开启A/D采样通道
//    ADCON1bits.ADON = 1;    // 开�?AD 模块  

// 8.配置AD中断
    IPC2bits.ADIP = 5;   
    IFS0bits.ADIF = 0;   //清AD中断标志�?
    IEC0bits.ADIE = 1;   //使能AD中断
}

// I2C 总线初始�?
void InitI2C(void)
{
	I2CCON = 0;
	I2CCONbits.I2CEN = 1;		// 使能 I2C
	I2CCONbits.I2CSIDL = 1;		// 空闲模式
	I2CCONbits.SCLREL = 1;		// 释放SCL时钟
	I2CCONbits.IPMIEN = 0;		// 使能IPMI支持模式
	I2CCONbits.A10M = 0;		// 7位从器件地址
	I2CCONbits.GCEN = 0;		// 接受广播呼叫
	I2CCONbits.STREN = 0;		// 使能电平延长
	I2CCONbits.RCEN = 0;		// 使能接受模式
	I2CCONbits.ACKDT = 1;		
	
	I2CBRG = dI2CBaudRateTcy;
	I2CADD = 0x0055;
	
	IEC0bits.SI2CIE = 0;		// 1 允许SI2C中断  
	IFS0bits.SI2CIF = 0;
	IPC3bits.SI2CIP = 6;
	
//	IEC0bits.MI2CIE = 1;
//	IFS0bits.MI2CIF = 0;
//	IPC3bits.MI2CIP = 5;
	
}

// UART2 串行通讯初始�?
void InitUART2(void)
{	
	U2MODE = 0;
	U2MODEbits.UARTEN = 1;					// 使能UART
	U2MODEbits.USIDL = 1;					// 空闲模式
	U2MODEbits.ABAUD = 0;					// 自动波特�?
	U2MODEbits.PDSEL = Uart2Parm.dPDSEL;		// 数据格式
	
	U2STA = 0;
	U2STAbits.UTXEN = 1;
	U2STAbits.UTXISEL = 1;
		
	U2BRG = Uart2Parm.dBaudRateTcy;		// 设置波特�?
	
	IEC1bits.U2TXIE = 0;				// 1 允许U2TX中断  
	IEC1bits.U2RXIE = 0;				// 1 允许U2RX中断  
	IFS1bits.U2TXIF = 0;
	IFS1bits.U2RXIF = 0;
	IPC6bits.U2TXIP = 5;
	IPC6bits.U2RXIP = 5;
	
}

// UART1 串行通讯初始�?
void InitUART1(void)
{	
	U1MODE = 0;
	U1MODEbits.UARTEN = 1;					// 使能UART
	U1MODEbits.USIDL = 1;					// 空闲模式
	U1MODEbits.ABAUD = 0;					// 自动波特�?
	U1MODEbits.PDSEL = Uart1Parm.dPDSEL;		// 数据格式
	
	U1STA = 0;
	U1STAbits.UTXEN = 1;
	U1STAbits.UTXISEL = 1;
		
	U1BRG = Uart1Parm.dBaudRateTcy;		// 设置波特�?
	
	IEC0bits.U1TXIE = 0;				// 1 允许U2TX中断  
	IEC0bits.U1RXIE = 0;				// 1 允许U2RX中断  
	IFS0bits.U1TXIF = 0;
	IFS0bits.U1RXIF = 0;
	IPC2bits.U1TXIP = 5;
	IPC2bits.U1RXIP = 5;
	
}

//输出比较初始�?
void InitOC(void)
{	
	OC1CON = 0;
	OC1CONbits.OCTSEL = 0;
	OC1CONbits.OCM = 5;
	
	OC2CON = 0;
	OC2CONbits.OCTSEL = 0;
	OC2CONbits.OCM = 5;
}
