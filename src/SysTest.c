//�����Ƽ���HJR3000����������������װ�ã�DSPIC30F6010Aϵͳ
//�������ļ���T1_CTRL.c

//ͷ�ļ�
#include "UserParms.h"	//�û�ϵͳ���ã��������弰����ֵ
#include "Function.h"	//ϵͳ�ⲿ���ú����������ڲ����ú����ڶ�Ӧ�ļ�������
#include "variable.h"	//ϵͳȫ�ֱ����������ֲ������ڶ�Ӧ�ļ�������

//ϵͳ����ģʽ
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
