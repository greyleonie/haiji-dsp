//海吉科技，HJR3000型智能软启动控制装置，DSPIC30F6010A系统
//PWM中断处理，PWMInterrupt.c

//头文件
#include "UserParms.h"	//用户系统配置，常数定义及配置值
#include "Function.h"	//系统外部调用函数声明，内部调用函数在对应文件内声明
#include "variable.h"	//系统全局变量声明，局部变量在对应文件内声明




//PWM中断
void __attribute__((__interrupt__)) _PWMInterrupt(void)
{
	if(PwmState.StartOut == 0)
	{
		PwmState.UoutH = 0;
		PwmState.UoutL = 0;
		PwmState.VoutH = 0;
		PwmState.VoutL = 0;
		PwmState.WoutH = 0;
		PwmState.WoutL = 0;
		OVDCON = 0x0000;
		if(PwmState.UoutPhyH == 1)
		{
			PwmState.UoutPhyH = 0;
			PwmState.UoutPhyL = 0;
			PwmState.VoutPhyH = 0;
			PwmState.VoutPhyL = 0;
			PwmState.WoutPhyH = 0;
			PwmState.WoutPhyL = 0;
			PWMParams.StartOut = PWMParams.StartOut + 1;
			if( (long) PWMParams.StartOut > 30)
			{
				PWMParams.StartOut = 0;
				PwmState.StartOut = 1;
			}
		}
	}else
	{		
				
		if(PwmState.UoutH == 1)
		{
			
			PWMParams.Duty1H = PWMParams.Duty1H + 1;
			
			if( (long) PWMParams.Duty1H > PWMParams.OnPWM)
			{
				PwmState.UoutH = 0;
				PWMParams.Duty1H = 0;
				OVDCONbits.POUT1H = 0;
				OVDCONbits.POVD1H = 0;
			}
		}else
		{
			PWMParams.Duty1H = 0;
			if(PwmState.UoutPhyH == 1)
			{
				PWMParams.Delay1H = PWMParams.Delay1H + 1;
				if( (long) PWMParams.Delay1H > SoftRunParms.OutData)
				{
					PwmState.UoutH = 1;
					PwmState.UoutPhyH = 0;
					PWMParams.Delay1H = 0;
					PDC1 = ActivePWM;
					OVDCONbits.POVD1H = 1;
				}
			}else
			{
				OVDCONbits.POUT1H = 0;
				OVDCONbits.POVD1H = 0;
				PWMParams.Delay1H = 0;
			}
		}
		
		if(PwmState.UoutL == 1)
		{
			
			PWMParams.Duty1L = PWMParams.Duty1L + 1;
			if( (long) PWMParams.Duty1L > PWMParams.OnPWM)
			{
				PwmState.UoutL = 0;
				PWMParams.Duty1L = 0;
				OVDCONbits.POUT1L = 0;
				OVDCONbits.POVD1L = 0;
			}
		}else
		{
			PWMParams.Duty1L = 0;
			if(PwmState.UoutPhyL == 1)
			{
				PWMParams.Delay1L = PWMParams.Delay1L + 1;
				if( (long) PWMParams.Delay1L > SoftRunParms.OutData)
				{
					PwmState.UoutL = 1;
					PwmState.UoutPhyL = 0;
					PWMParams.Delay1L = 0;
					if(StartState.ShaChe == 0)
					{
						PDC1 = ActivePWM;
						OVDCONbits.POVD1L = 1;
					}else
					{
						OVDCONbits.POUT1L = 0;
						OVDCONbits.POVD1L = 0;
						PWMParams.Delay1L = 0;
					}
				}
			}else
			{
				OVDCONbits.POUT1L = 0;
				OVDCONbits.POVD1L = 0;
			}
		}
		
		if(PwmState.VoutH == 1)
		{
			
			PWMParams.Duty2H = PWMParams.Duty2H + 1;
			if( (long) PWMParams.Duty2H > PWMParams.OnPWM)
			{
				PwmState.VoutH = 0;
				PWMParams.Duty2H = 0;
				OVDCONbits.POUT2H = 0;
				OVDCONbits.POVD2H = 0;
			}
		}else
		{
			PWMParams.Duty2H = 0;
			if(PwmState.VoutPhyH == 1)
			{
				PWMParams.Delay2H = PWMParams.Delay2H + 1;
				if( (long) PWMParams.Delay2H > SoftRunParms.OutData)
				{
					PwmState.VoutH = 1;
					PwmState.VoutPhyH = 0;
					PWMParams.Delay2H = 0;
					PDC2 = ActivePWM;
					OVDCONbits.POVD2H = 1;
				}
			}else
			{
				OVDCONbits.POUT2H = 0;
				OVDCONbits.POVD2H = 0;
				PWMParams.Delay2H = 0;
			}
		}
		
		if(PwmState.VoutL == 1)
		{
			
			PWMParams.Duty2L = PWMParams.Duty2L + 1;
			if( (long) PWMParams.Duty2L > PWMParams.OnPWM)
			{
				PwmState.VoutL = 0;
				PWMParams.Duty2L = 0;
				OVDCONbits.POUT2L = 0;
				OVDCONbits.POVD2L = 0;
			}
		}else
		{
			PWMParams.Duty2L = 0;
			if(PwmState.VoutPhyL == 1)
			{
				PWMParams.Delay2L = PWMParams.Delay2L + 1;
				if( (long) PWMParams.Delay2L > SoftRunParms.OutData)
				{
					PwmState.VoutL = 1;
					PwmState.VoutPhyL = 0;
					PWMParams.Delay2L = 0;
					PDC2 = ActivePWM;
					OVDCONbits.POVD2L = 1;
				}
			}else
			{
				OVDCONbits.POUT2L = 0;
				OVDCONbits.POVD2L = 0;
				PWMParams.Delay2L = 0;
			}
		}
		
		if(PwmState.WoutH == 1)
		{
			
			PWMParams.Duty3H = PWMParams.Duty3H + 1;
			if( (long) PWMParams.Duty3H > PWMParams.OnPWM)
			{
				PwmState.WoutH = 0;
				PWMParams.Duty3H = 0;
				OVDCONbits.POUT3H = 0;
				OVDCONbits.POVD3H = 0;
			}
		}else
		{
			PWMParams.Duty3H = 0;
			if(PwmState.WoutPhyH == 1)
			{
				PWMParams.Delay3H = PWMParams.Delay3H + 1;
				if( (long) PWMParams.Delay3H > SoftRunParms.OutData)
				{
					PwmState.WoutH = 1;
					PwmState.WoutPhyH = 0;
					PWMParams.Delay3H = 0;
					PDC3 = ActivePWM;
					OVDCONbits.POVD3H = 1;
				}
			}else
			{
				OVDCONbits.POUT3H = 0;
				OVDCONbits.POVD3H = 0;
				PWMParams.Delay3H = 0;
			}
		}
		
		if(PwmState.WoutL == 1)
		{
			
			PWMParams.Duty3L = PWMParams.Duty3L + 1;
			if( (long) PWMParams.Duty3L > PWMParams.OnPWM)
			{
				PwmState.WoutL = 0;
				PWMParams.Duty3L = 0;
				OVDCONbits.POUT3L = 0;
				OVDCONbits.POVD3L = 0;
			}
		}else
		{
			PWMParams.Duty3L = 0;
			if(PwmState.WoutPhyL == 1)
			{
				PWMParams.Delay3L = PWMParams.Delay3L + 1;
				if( (long) PWMParams.Delay3L > SoftRunParms.OutData)
				{
					PwmState.WoutL = 1;
					PwmState.WoutPhyL = 0;
					PWMParams.Delay3L = 0;
					if(StartState.ShaChe == 0)
					{
						PDC3 = ActivePWM;
						OVDCONbits.POVD3L = 1;
					}else
					{
						OVDCONbits.POUT3L = 0;
						OVDCONbits.POVD3L = 0;
					}
				}
			}else
			{
				OVDCONbits.POUT3L = 0;
				OVDCONbits.POVD3L = 0;
				PWMParams.Delay3L = 0;
			}
		} 
	
	}
	
    IFS2bits.PWMIF = 0;   //清PWM中断标志位
    return;

}


