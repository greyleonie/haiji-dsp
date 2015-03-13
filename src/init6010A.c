//�����Ƽ���HJR3000����������������װ�ã�DSPIC30F6010Aϵͳ
//ϵͳ��ʼ��������init4011.c

//ͷ�ļ�
#include "UserParms.h"	//�û�ϵͳ���ã��������弰����ֵ
#include "Function.h"	//ϵͳ�ⲿ���ú����������ڲ����ú����ڶ�Ӧ�ļ�������
#include "variable.h"	//ϵͳȫ�ֱ����������ֲ������ڶ�Ӧ�ļ�������

int AX_int_Init = 0;

//��EEP������ϵͳ����
void SysConfig(void)
{
	//�����ڲ����ʵ�Ԫ��KeyParm.SaveParms[0x1B]
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
	
	//************* �����в��� ******************
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
	
//************* �������ֵ ******************
	//�ɱ��IO����
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
	
	
	//�ɱ��IO���
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
	
	
	//����ģʽ
	if(KeyParm.SaveParms[0x10]>1)
		KeyParm.SaveParms[0x10]=0;
	else if(KeyParm.SaveParms[0x10]<0)
		KeyParm.SaveParms[0x10]=0;
	KeyParm.CtrMode=KeyParm.SaveParms[0x10];
	
	//����ģʽ
	if(KeyParm.SaveParms[0x11]>3)
		KeyParm.SaveParms[0x11]=0;
	else if(KeyParm.SaveParms[0x11]<0)
		KeyParm.SaveParms[0x11]=0;
	KeyParm.StartMode=KeyParm.SaveParms[0x11];

	//ֹͣģʽ
	if(KeyParm.SaveParms[0x12]>2)
		KeyParm.SaveParms[0x12]=0;
	else if(KeyParm.SaveParms[0x12]<0)
		KeyParm.SaveParms[0x12]=0;
	KeyParm.StopMode=KeyParm.SaveParms[0x12];
	
	//���з�ʽ
	if(KeyParm.SaveParms[0x13]>1)
		KeyParm.SaveParms[0x13]=0;
	else if(KeyParm.SaveParms[0x13]<0)
		KeyParm.SaveParms[0x13]=0;
	KeyParm.RunMode=KeyParm.SaveParms[0x13];
	
	//��������
	if(KeyParm.SaveParms[0x14]>19999)
		KeyParm.SaveParms[0x14]=0;
	else if(KeyParm.SaveParms[0x14]<0)
		KeyParm.SaveParms[0x14]=0;
	MeauParm.MainMeauMax=KeyParm.SaveParms[0x14];
	
	MeauParm.MainMul = 1121;
	MeauParm.MainAdd = 99614;
	
	//��������
	if(KeyParm.SaveParms[0x15]>19999)
		KeyParm.SaveParms[0x15]=10000;
	else if(KeyParm.SaveParms[0x15]<0)
		KeyParm.SaveParms[0x15]=10000;
	if(KeyParm.SaveParms[0x15] > 9999)
		MeauParm.MainMeauFine=KeyParm.SaveParms[0x15];
	else MeauParm.MainMeauFine = 10000 - KeyParm.SaveParms[0x15];
	
	//��ѹ����
	if(KeyParm.SaveParms[0x17] < 0)
		KeyParm.SaveParms[0x17] = 4000;
	else if(KeyParm.SaveParms[0x17] > 19999)
		KeyParm.SaveParms[0x17] = 4000;	
	SysParms.MaxMeauVol = KeyParm.SaveParms[0x17];
	
	//��������
	if(KeyParm.SaveParms[0x18] < 0)
		KeyParm.SaveParms[0x18] = 3000;
	else if(KeyParm.SaveParms[0x18] > 29999)
		KeyParm.SaveParms[0x18] = 3000;	
	SysParms.MaxMeauCur = KeyParm.SaveParms[0x18];
	
	//��ѹ����
	if(KeyParm.SaveParms[0x19] < 0)
		KeyParm.SaveParms[0x19] = 3000;
	else if(KeyParm.SaveParms[0x19] > 19999)
		KeyParm.SaveParms[0x19] = 3000;	
	SysParms.AddMeauVol = KeyParm.SaveParms[0x19];
	
	//���ڵ�ַ
	if(KeyParm.SaveParms[0x1A]>255)
		KeyParm.SaveParms[0x1A]=1;
	else if(KeyParm.SaveParms[0x1A]<0)
		KeyParm.SaveParms[0x1A]=1;
	Uart2Parm.Addr = KeyParm.SaveParms[0x1A];											

	//���ܲ���
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

	//�����������
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
	
	//��ͣ����
	if(KeyParm.SaveParms[0x30] < 10)
		KeyParm.SaveParms[0x30] = 30;
	else if(KeyParm.SaveParms[0x30] > 80)
		KeyParm.SaveParms[0x30] = 30;
	AX_int_Init = 100 - KeyParm.SaveParms[0x30];
	SoftRunParms.StartData = ( (long) DataMax  / 100 ) * AX_int_Init;				//��ѹб��������ʼ��ѹ
	
	if(KeyParm.SaveParms[0x31] < 1)
		KeyParm.SaveParms[0x31] = 100;
	else if(KeyParm.SaveParms[0x31] > 9999)
		KeyParm.SaveParms[0x31] = 100;
	SoftRunParms.LoopData = DataMaxLoop / KeyParm.SaveParms[0x31];					//��ѹб����������
	
		
	if(KeyParm.SaveParms[0x32] < 10)
		KeyParm.SaveParms[0x32] = 40;
	else if(KeyParm.SaveParms[0x32] > 80)
		KeyParm.SaveParms[0x32] = 40;
	AX_int_Init = 100 - KeyParm.SaveParms[0x32];
	SoftRunParms.JumpStartData = ( (long) DataMax  / 100 ) * AX_int_Init;			//ͻ������������ѹ	
	
	if(KeyParm.SaveParms[0x33] < 1)
		KeyParm.SaveParms[0x33] = 5;
	else if(KeyParm.SaveParms[0x33] > 100)
		KeyParm.SaveParms[0x33] = 5;
	SoftRunParms.JumpLoopData = ( (long) KeyParm.SaveParms[0x33] * 1000 ) / 25;		//ͻ��������������
	
	if(KeyParm.SaveParms[0x34] < 100)
		KeyParm.SaveParms[0x34] = 200;
	else if(KeyParm.SaveParms[0x34] > 500)
		KeyParm.SaveParms[0x34] = 200;
	SoftRunParms.LimitCar = ( (long) SysParms.RateCur * KeyParm.SaveParms[0x34] ) / 100;	//����������������
	
	if(KeyParm.SaveParms[0x35] < 60)
		KeyParm.SaveParms[0x35] = 85;
	else if(KeyParm.SaveParms[0x35] > 100)
		KeyParm.SaveParms[0x35] = 85;
	AX_int_Init = 100 - KeyParm.SaveParms[0x35];
	SoftRunParms.EndData = ( (long) DataMax  / 100 ) * AX_int_Init;					//�������Ƶ�ѹ
	
	if(KeyParm.SaveParms[0x36] < 10)
		KeyParm.SaveParms[0x36] = 40;
	else if(KeyParm.SaveParms[0x36] > 100)
		KeyParm.SaveParms[0x36] = 40;
	AX_int_Init = 100 - KeyParm.SaveParms[0x36];
	SoftRunParms.SoftStopStartData = ( (long) DataMax  / 100 ) * AX_int_Init;		//��ͣ����ʼ��ѹ
	SoftRunParms.SoftStopEndData = ( (long) DataMax  / 100 ) * 70;
	
	if(KeyParm.SaveParms[0x37] < 1)
		KeyParm.SaveParms[0x37] = 10;
	else if(KeyParm.SaveParms[0x37] > 999)
		KeyParm.SaveParms[0x37] = 10;
	SoftRunParms.SoftStopLoopData = DataMaxLoop / KeyParm.SaveParms[0x37];			//��ͣ������
		
	if(KeyParm.SaveParms[0x38] < 10)
		KeyParm.SaveParms[0x38] = 50;
	else if(KeyParm.SaveParms[0x38] > 100)
		KeyParm.SaveParms[0x38] = 50;
	AX_int_Init = 100 - KeyParm.SaveParms[0x38];
	SoftRunParms.StopEndData = ( (long) DataMax  / 100 ) * AX_int_Init;
	SoftRunParms.StopEndData = SoftRunParms.StopEndData / dqDataGei;				//ɲ����ѹ
	
		
	if(KeyParm.SaveParms[0x39] < 1)
		KeyParm.SaveParms[0x39] = 3;
	else if(KeyParm.SaveParms[0x39] > 999)
		KeyParm.SaveParms[0x39] = 3;
	SoftRunParms.StopLoopData = DataMaxLoop / KeyParm.SaveParms[0x39];				//ɲ��ֹͣ����
	
	//�Զ����в���
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
	
	
	// **************** ��������ֵ ************************
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
    
    //����ϵͳ���ܵ�Ԫ
	T1CONbits.TON = 1;              // start the timer1
    ADCON1bits.ADON=1;				//��ADת��
    IEC0bits.IC1IE = 1;				//����IC1�ж�
    IEC0bits.IC2IE = 1;             //����IC2�ж�
	IEC1bits.IC3IE = 1;             //����IC3�ж�  
	IEC1bits.IC4IE = 1;             //����IC4�ж�  
	IEC2bits.PWMIE = 1;  			// ʹ��PWM�ж�
	IEC0bits.SI2CIE = 1;			// 1 ����SI2C�ж�  
	IEC1bits.U2TXIE = 1;			// 1 ����U2TX�ж� 
	IEC1bits.U2RXIE = 1;			// 1 ����U2RX�ж� 
	IEC0bits.U1TXIE = 1;			// 1 ����U2TX�ж� 
	IEC0bits.U1RXIE = 1;			// 1 ����U2RX�ж�   
	
	
	if(Uart1Parm.AddrMax == 8)
	{
		IEC0bits.U1TXIE = 0;			// 1 ����U2TX�ж� 
		IEC0bits.U1RXIE = 0;			// 1 ����U2RX�ж�   
	}
}


//IO�ڹ��ܳ�ʼ��
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
// RB2    AN2/SS1/CN4     			IN1-RB2		�ɱ������ӿ�1
// RB3    AN3/INDX/CN5				IN2-RB3 	�ɱ������ӿ�2

// RB4    AN4/QEA/CN6				IN3-RB4 	�ɱ������ӿ�3  
// RB5    AN5/QEB/CN7				IN4-RB5 	�ɱ������ӿ�4  
// RB6    AN6/OCFA					IN5-RB6 	�ɱ������ӿ�5  
// RB7    AN7						IN6-RB7 	�ɱ������ӿ�6  

// RB8    AN8						IN7-RB8 	�ɱ������ӿ�7  
// RB9    AN9						IN8-RB9 	�ɱ������ӿ�8  
// RB10   AN10						YF-AN10 	���ò�������
// RB11   AN11						PF-AN11 	����������

// RB12   AN12						UF-AN12 	�����ѹ
// RB13   AN13						UIF-AN13 	U�����
// RB14   AN14						UIF-AN14 	V�����
// RB15   AN15						UIF-AN15 	W�����

    TRISB = 0xFFFF; 
    LATB  = 0XFFFF;

// ============= Port C ==============

//        absent
// RC1	  T2CK						GR-RC1		���ȱ���
//        absent
// RC3	  T4CK						PLIN-RC3	��·�Ӵ����պϼ��

//        absent
//        absent
//        absent
//        absent

//        absent
//        absent
//        absent
//        absent

//        absent
// RC13   EMUD1/SOSCI				OU0-RD0			��·�Ӵ������
// RC14   EMUC1/SOSCO/T1CK/CN0		OU1-RD1			�ɱ�����1	
// RC15   OSC2/CLKO                 	OSC2		����

    TRISC = 0x1FFF;     
    LATC  = 0XFFFF;

// ============= Port D ==============

// RD0    EMUC2/OC1				OU20mA1			4-20mA���1	
// RD1    EMUD2/OC2				OU20mA1			4-20mA���2	
// RD2    OC3                   OU2-RD2			�ɱ�����2	
// RD3    OC4                   OU3-RD3			�ɱ�����3	

// RD4    OC5/CN13              OU4-RD4			�ɱ�����4	
// RD5    OC6/CN14              OU5-RD5			�ɱ�����5
// RD6    OC7/CN15              OU6-RD6			�ɱ�����6
// RD7    OC8/CN16/UPDN         OU7-RD7			�ɱ�����7

// RD8    IC1					UAIN-IC1		A���ѹͬ��
// RD9    IC2					UBIN-IC2		B���ѹͬ��
// RD10   IC3					UCIN-IC3		C���ѹͬ��
// RD11   IC4					IAIN-IC4		A�����ͬ��

// RD12   IC5
// RD13	  IC6					OU8-RD13		�ɱ�����8
// RD14	  IC7					OU9-RD14		�ɱ�����9
// RD15	  IC8					OU10-RD15		�ɱ�����10

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

// RF0    C1RX                  	TRCS2-RF0		RS485�ⲿͨѶ�ӿ��շ�����
// RF1    C1TX                      TRCS1-RF1		RS485����ͨѶ�ӿ��շ�����
// RF2    U1RX						U1RX			RS485����ͨѶ�ӿ�
// RF3    U1TX        				U1TX			RS485����ͨѶ�ӿ�

// RF4    U2RX/CN17                	U2RX			RS485�ⲿͨѶ�ӿ�
// RF5    U2TX/CN18                	U2TX			RS485�ⲿͨѶ�ӿ�
// RF6    EMUC3/SCK1/INT0			RUN-RF6			�ֶ���������
// RF7    SDI1						STOP-RF7		ֹͣ��������
// RF8    EMUD3/SDO1				AUTO-RF8		�Զ���������
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

// RG0    C2RX						RG0			LCD��λ
// RG1    C2TX
// RG2    SCL						SCL			���̽ӿ�
// RG3    SDA						SDA			���̽ӿ�

//        absent
//        absent
// RG6    SCK2/CN8					BD0-RG6		���뿪��0λ
// RG7    SDI2/CN9					BD1-RG7		���뿪��1λ

// RG8    SDO2/CN10					BD2-RG7		���뿪��2λ
// RG9    SS2/CN11					BD3-RG8		���뿪��3λ         
//        absent               
//        absent

//        absent
//        absent
// 		  absent
//        absent
	
	TRISG = 0xFFFE;     
    LATG  = 0XFFFF;


}

//��ʱ����ʼ��
void InitTimer( void )
{
//  Timer1��ʼ�� 

    T1CON = 0;					// �رն�ʱ��1
    TMR1 = 0;          			// clear timer1 register 
    T1CONbits.TSIDL = 0;        // ����ģʽ��ֹͣ����   
    T1CONbits.TCS = 0; 			// set internal clock source
	T1CONbits.TCKPS = 0;		// Tcy / 1 ��Ϊ����ʱ��  
    PR1 = dTImer1Tcy;			// set period1 register 
    IPC0bits.T1IP = 5; 			// set priority level 
    IFS0bits.T1IF = 0; 			//clear interrupt flag 
    IEC0bits.T1IE = 1; 			// enable interrupts 
    SRbits.IPL = 3;    			//enable CPU priority levels 4-7

//Timer2��ʼ��

    T2CON = 0;                   // �رն�ʱ��2
    TMR2 = 0;                    // ��λ��ʱ��2������
    T2CONbits.TSIDL = 0;         // ����ģʽ��ֹͣ����
    T2CONbits.TGATE = 0;         // ��ֹ�ſض�ʱ���ۼ�
    T2CONbits.TCS = 0;           // ʹ��Tcy ��ΪԴʱ��
    T2CONbits.TCKPS = 0;         // Tcy / 64 ��Ϊ����ʱ��
    T2CONbits.TON = 1;           // ����timer2
    PR2 = 0x0FFF;                  // �ж����� = 0.008 �룬Ԥ��Ƶ����Ƶ��Ϊ64[3750suan]
    IPC1bits.T2IP = 5;
    IFS0bits.T2IF = 0;           // ����timer2 �жϱ�־
    IEC0bits.T2IE = 0;           // ����timer2 �ж� 


//Timer3��ʼ��

    T3CON= 0;                    // �رն�ʱ��3
    TMR3 = 0;                    // ��λ��ʱ����3����
    T3CONbits.TSIDL = 0;         // ����ģʽ��ֹͣ����
    T3CONbits.TGATE = 0;         // ��ֹ�ſض�ʱ���ۼ�
    T3CONbits.TCS = 0;           // ʹ��Tcy ��ΪԴʱ��
    T3CONbits.TCKPS = 3;         // Tcy / 8 ��Ϊ����ʱ��
    T3CONbits.TON = 1;           // ����timer3
    PR3 = 0x7FFF;                
    IEC0bits.T3IE = 0;           // ��ֹtimer3 �ж�


//  Timer4��ʼ�� 
/*
    T4CON = 0;
    T4CONbits.TSIDL = 1;        // ����ģʽ��ֹͣ����   
    TMR4 = 0;          			// clear timer1 register 
    PR4 = dTImer4Tcy; 			// set period1 register 
    T4CONbits.TCS = 0; 			// set internal clock source 
    IPC5bits.T4IP = 5; 			// set priority level 
    IFS1bits.T4IF = 0; 			//clear interrupt flag 
    IEC1bits.T4IE = 1; 			// enable interrupts 
*/
}


//IO�������⹦�ܳ�ʼ��
/*
void InitCN(void)
{
    CNEN1 = 0;
    CNEN2 = 0;
    CNEN1bits.CN0IE = 1; 				//���� CN0 ��ƽ��������
    CNEN1bits.CN1IE = 1; 				//���� CN1 ��ƽ��������
    CNEN1bits.CN2IE = 1; 				//���� CN2 ��ƽ��������
    CNEN1bits.CN3IE = 1; 				//���� CN3 ��ƽ��������
    CNEN1bits.CN4IE = 1; 				//���� CN4 ��ƽ��������
    CNEN1bits.CN5IE = 1; 				//���� CN5 ��ƽ��������
    
    CNPU1 = 0;
    CNPU2 = 0;
    CNPU1bits.CN0PUE = 1;				//���� CN0 ��ƽ�仯����
    CNPU1bits.CN1PUE = 1;				//���� CN1 ��ƽ�仯����
    CNPU1bits.CN2PUE = 1;				//���� CN2 ��ƽ�仯����
    CNPU1bits.CN3PUE = 1;				//���� CN3 ��ƽ�仯����
    CNPU1bits.CN4PUE = 1;				//���� CN4 ��ƽ�仯����
    CNPU1bits.CN5PUE = 1;				//���� CN5 ��ƽ�仯����
    

    IPC3bits.CNIP = 3;              //�����ж����ȼ�Ϊ5
    IFS0bits.CNIF = 0;              //�����жϱ�־
    IEC0bits.CNIE = 1;              //����CN�ж�
    
}
*/

void InitIC( void )
{
//	IC1��ʼ��	
    IC1CON=0;                        //��ֹ��׽ģ��
    IC1CONbits.ICTMR = 0;            //��׽�¼�ʱ��׽TMR3������
    IC1CONbits.ICI = 0;              //ÿ1�β�׽�¼��ж�һ��
    IC1CONbits.ICM = 1;              //ÿ���½��ز�׽�¼�
   
    IPC0bits.IC1IP = 6;              //�����ж����ȼ�Ϊ5
    IFS0bits.IC1IF = 0;              //�����жϱ�־
    IEC0bits.IC1IE = 0;              // 1 ����IC1�ж�

//	IC2��ʼ��
	IC2CON=0;                        //��ֹ��׽ģ��
    IC2CONbits.ICTMR = 0;            //��׽�¼�ʱ��׽TMR3������
    IC2CONbits.ICI = 0;              //ÿ1�β�׽�¼��ж�һ��
    IC2CONbits.ICM = 1;              //ÿ���½��ز�׽�¼�
   
    IPC1bits.IC2IP = 6;              //�����ж����ȼ�Ϊ5
    IFS0bits.IC2IF = 0;              //�����жϱ�־
    IEC0bits.IC2IE = 0;              // 1 ����IC2�ж�
    
//	IC3��ʼ��
	IC3CON=0;                        //��ֹ��׽ģ��
    IC3CONbits.ICTMR = 0;            //��׽�¼�ʱ��׽TMR3������
    IC3CONbits.ICI = 0;              //ÿ1�β�׽�¼��ж�һ��
    IC3CONbits.ICM = 1;              //ÿ���½��ز�׽�¼�
   
    IPC7bits.IC3IP = 6;              //�����ж����ȼ�Ϊ5
    IFS1bits.IC3IF = 0;              //�����жϱ�־
    IEC1bits.IC3IE = 0;              // 1 ����IC7�ж�  
    
//	IC4��ʼ��
	IC4CON=0;                        //��ֹ��׽ģ��
    IC4CONbits.ICTMR = 0;            //��׽�¼�ʱ��׽TMR3������
    IC4CONbits.ICI = 0;              //ÿ1�β�׽�¼��ж�һ��
    IC4CONbits.ICM = 1;              //ÿ���½��ز�׽�¼�
   
    IPC7bits.IC4IP = 6;              //�����ж����ȼ�Ϊ5
    IFS1bits.IC4IF = 0;              //�����жϱ�־
    IEC1bits.IC4IE = 0;              // 1 ����IC7�ж�  


}

//PWM���ܳ�ʼ��
void InitPWM( void )
{
	                      
	PTCON = 0x0000;    			// ��ֹPWM ,��������ģʽ,ʱ��ΪTcy
	PTPER = dLoopInTcy;     	// PWM���������趨
    PWMCON1 = 0x0777;  			// ��λ��ʹ��PWM 1,2,3 �Թ����ڶ���ģʽ
    PWMCON2 = 0x0000;  			// PWM�����¼���������Ƶ��Ϊ1��1����ֹ��д������ռ�ձȸ���	
    PWMCON2bits.IUE = 0;		// PDC�Ĵ�����������
    PWMCON2bits.OSYNC = 1;		// ��дͬ��
    
    PDC1 = 0x0000;     			// ��ʼ��ռ�ձ�  
    PDC2 = 0x0000;
    PDC3 = 0x0000;
    
	DTCON1 = (dDeadTime>>1);	// ����ʱ��2��Ƶʱ��ʱ��
    DTCON1bits.DTAPS=1;			//����ʱ��2��Ƶ
    OVDCON = 0x0000;     		//��ʼ��PWM����������

	FLTACON = 0x0007;  			//��������Ϊ�͵�ƽʱ��6·PWM�����Ч 
    FLTACONbits.FLTAM=0;
    
	IPC10bits.FLTAIP=7;     	//���ù��������ж�Ϊ������ȼ��ж�
	IFS2bits.FLTAIF=0;      	//��FLTA�����жϱ�־λ ��FLTAΪ�������ϣ�
	IEC2bits.FLTAIE = 1;    	//ʹ��FLTA�����ж�

            
    SEVTCMP = 0;             	// 0 ����PWM����ADת��
    SEVTCMPbits.SEVTDIR = 0; 	// 0 ,�����¼������źŽ���PWM ʱ�������ϼ������ڲ���
    IPC9bits.PWMIP = 7;			// 
    IFS2bits.PWMIF = 0;   		// ��PWM�жϱ�־λ
    IEC2bits.PWMIE = 1;  		// ʹ��PWM�ж�
    
    
}


//������������ʼ��
/*
void InitQEI( void )
{
    ADPCFG = 0x0030;           			// ��QEI ��������Ϊ��������
    QEICONbits.QEIM = 0;         		// ��ֹQEI ģ��
    QEICONbits.CNTERR = 0;       		// ����κμ�������
    QEICONbits.QEISIDL = 1;      		// �����ڼ��ֹ����
    QEICONbits.SWPAB = 0;        		// QEA ��QEB ������
    QEICONbits.PCDOUT = 0;       		// ����I/O ���Ų��������跽�����
    QEICONbits.POSRES = 0;       		// ��ֹ�������帴λ
    DFLTCONbits.CEID = 1;        		// ��ֹ���������ж�
    DFLTCONbits.QEOUT = 0;       		// ����QEn ���ţ���ֹ�����˲������
	DFLTCONbits.QECK = 0;        		// ��QEn �������˲�������Ϊ1:1ʱ�ӷ�Ƶ[suan]
	DFLTCONbits.INDOUT = 0;      		// ���������˲���ֹ
    POSCNT = 0;                  		// ��λλ�ü�����
	MAXCNT = MotorParm.iCntsPerRev;		//2400;	//������תһȦ���������
    QEICONbits.QEIM = 7;         		// ����QEI��X4 ģʽ��ͨ����(MAXCNT)ƥ�临λλ�ü�����
}
*/

//ADת�����ܳ�ʼ��
void InitAD(void)
{
// 1.���ö˿�������Ϊģ�����룬����Ӧλ��0
    ADPCFG = 0xFFFF;        // Set all ports digital
    ADPCFGbits.PCFG10 = 0;   // AN5 analog
    ADPCFGbits.PCFG11 = 0;   // AN6 analog
    ADPCFGbits.PCFG12 = 0;   // AN7 analog
    ADPCFGbits.PCFG13 = 0;   // AN8 analog
    ADPCFGbits.PCFG14 = 0;   // AN7 analog
    ADPCFGbits.PCFG15 = 0;   // AN8 analog
    
// 2.ѡ��ο���ѹԴ ADCON2��13����15λ
    ADCON2 = 0x0000;        
    ADCON2bits.VCFG = 1;    // 1 ʹ���ⲿ�ο���Դ
    ADCON2bits.CSCNA = 1;   // ɨ������
    ADCON2bits.CHPS = 0;    // ת��CH0
    ADCON2bits.SMPI = 5;    // ÿ6��ת��������ж�
    ADCON2bits.ALTS = 0;    // ���ǲ���MUX A����

// 3.ѡ��ģ��ת��ʱ��ADCON3
    ADCON3 =  0x0000;        //ʹ���ڲ�ʱ�� 
    ADCON3bits.SAMC = 0x02;
    ADCON3bits.ADCS = 0x3F;    // ADת��ʱ��ѡ�� TAD =  6*Tcy  
 
// 4.AD����ѡ��ADCHS
    ADCHS=0x0000;
    ADCHSbits.CH0SA = 10;               // CH0,ͨ��ѡ��AN6
    ADCHSbits.CH0NA = 0;               
    
    //ADCHSbits.CH123SA = 1;               // CH0,ͨ��ѡ��AN6
    //ADCHSbits.CH123NA = 0;               
      
    
// 5.����ADCSSLɨ��ѡ��Ĵ��� ����ɨ��ѡ0
    ADCSSL = 0x0000;    
    ADCSSLbits.CSSL10 = 1;    //ɨ������2.3.6ͨ��
    ADCSSLbits.CSSL11 = 1;
    ADCSSLbits.CSSL12 = 1;
    ADCSSLbits.CSSL13 = 1;
    ADCSSLbits.CSSL14 = 1;
    ADCSSLbits.CSSL15 = 1;
    
// 6.���ò���/ת������ADCON1
    ADCON1 = 0;
    ADCON1bits.FORM = 0;    // ת�������ʽ
	ADCON1bits.SSRC = 7;    //  "0" �ֶ�����ADת��
    ADCON1bits.ASAM = 1;    // ת���������Զ�������ʼΪ����1ʹ��
    ADCON1bits.SIMSAM = 1;	// ͬʱ����
    
// 7.����A/D����ͨ��
//    ADCON1bits.ADON = 1;    // ���� AD ģ��  

// 8.����AD�ж�
    IPC2bits.ADIP = 5;   
    IFS0bits.ADIF = 0;   //��AD�жϱ�־λ
    IEC0bits.ADIE = 1;   //ʹ��AD�ж�
}

// I2C ���߳�ʼ��
void InitI2C(void)
{
	I2CCON = 0;
	I2CCONbits.I2CEN = 1;		// ʹ�� I2C
	I2CCONbits.I2CSIDL = 1;		// ����ģʽ
	I2CCONbits.SCLREL = 1;		// �ͷ�SCLʱ��
	I2CCONbits.IPMIEN = 0;		// ʹ��IPMI֧��ģʽ
	I2CCONbits.A10M = 0;		// 7λ��������ַ
	I2CCONbits.GCEN = 0;		// ���ܹ㲥����
	I2CCONbits.STREN = 0;		// ʹ�ܵ�ƽ�ӳ�
	I2CCONbits.RCEN = 0;		// ʹ�ܽ���ģʽ
	I2CCONbits.ACKDT = 1;		
	
	I2CBRG = dI2CBaudRateTcy;
	I2CADD = 0x0055;
	
	IEC0bits.SI2CIE = 0;		// 1 ����SI2C�ж�  
	IFS0bits.SI2CIF = 0;
	IPC3bits.SI2CIP = 6;
	
//	IEC0bits.MI2CIE = 1;
//	IFS0bits.MI2CIF = 0;
//	IPC3bits.MI2CIP = 5;
	
}

// UART2 ����ͨѶ��ʼ��
void InitUART2(void)
{	
	U2MODE = 0;
	U2MODEbits.UARTEN = 1;					// ʹ��UART
	U2MODEbits.USIDL = 1;					// ����ģʽ
	U2MODEbits.ABAUD = 0;					// �Զ�������
	U2MODEbits.PDSEL = Uart2Parm.dPDSEL;		// ���ݸ�ʽ
	
	U2STA = 0;
	U2STAbits.UTXEN = 1;
	U2STAbits.UTXISEL = 1;
		
	U2BRG = Uart2Parm.dBaudRateTcy;		// ���ò�����
	
	IEC1bits.U2TXIE = 0;				// 1 ����U2TX�ж�  
	IEC1bits.U2RXIE = 0;				// 1 ����U2RX�ж�  
	IFS1bits.U2TXIF = 0;
	IFS1bits.U2RXIF = 0;
	IPC6bits.U2TXIP = 5;
	IPC6bits.U2RXIP = 5;
	
}

// UART1 ����ͨѶ��ʼ��
void InitUART1(void)
{	
	U1MODE = 0;
	U1MODEbits.UARTEN = 1;					// ʹ��UART
	U1MODEbits.USIDL = 1;					// ����ģʽ
	U1MODEbits.ABAUD = 0;					// �Զ�������
	U1MODEbits.PDSEL = Uart1Parm.dPDSEL;		// ���ݸ�ʽ
	
	U1STA = 0;
	U1STAbits.UTXEN = 1;
	U1STAbits.UTXISEL = 1;
		
	U1BRG = Uart1Parm.dBaudRateTcy;		// ���ò�����
	
	IEC0bits.U1TXIE = 0;				// 1 ����U2TX�ж�  
	IEC0bits.U1RXIE = 0;				// 1 ����U2RX�ж�  
	IFS0bits.U1TXIF = 0;
	IFS0bits.U1RXIF = 0;
	IPC2bits.U1TXIP = 5;
	IPC2bits.U1RXIP = 5;
	
}

//����Ƚϳ�ʼ��
void InitOC(void)
{	
	OC1CON = 0;
	OC1CONbits.OCTSEL = 0;
	OC1CONbits.OCM = 5;
	
	OC2CON = 0;
	OC2CONbits.OCTSEL = 0;
	OC2CONbits.OCM = 5;
}
