//�����Ƽ���HJR3000����������������װ�ã�DSPIC30F6010Aϵͳ
//��ѹͬ���źŴ���PhyVol.c

//ͷ�ļ�
#include "UserParms.h"	//�û�ϵͳ���ã��������弰����ֵ
#include "Function.h"	//ϵͳ�ⲿ���ú����������ڲ����ú����ڶ�Ӧ�ļ�������
#include "variable.h"	//ϵͳȫ�ֱ����������ֲ������ڶ�Ӧ�ļ�������


//4��20mA���OC1��OC2
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
