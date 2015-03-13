//�����Ƽ���HJR3000����������������װ�ã�DSPIC30F6010Aϵͳ
//���ļ���MainCont.c

//ͷ�ļ�
#include "UserParms.h"	//�û�ϵͳ���ã��������弰����ֵ
#include "Function.h"	//ϵͳ�ⲿ���ú����������ڲ����ú����ڶ�Ӧ�ļ�������
#include "variable.h"	//ϵͳȫ�ֱ����������ֲ������ڶ�Ӧ�ļ�������


tSinCosParms SinCosParms;			//��SinCos�����
tPWMParams PWMParams;				//PWM���������ṹ
tRunState RunState;						//ϵͳ����״̬��־��λ�����ṹ
tKeyParm KeyParm;  
tCurParms CurParms;
tVolParms VolParms;
tICParms ICParms;
tSoftRunParms SoftRunParms;
tMainState MainState;
tErrorParm ErrorParm;  
tUart2Parm Uart2Parm;  
tI2CParm I2CParm;  
tPwmState PwmState; 
tSysParms SysParms;
tInputState InputState;
tOutputState OutputState;
tInputIO InputIO;
tOutputIO OutputIO;
tInputLogic InputLogic;
tInsideIOState InsideIOState;
tMeauParm MeauParm;  
tAutoRunParm AutoRunParm;  
tUart1Parm Uart1Parm;
tStartState StartState;
tMainParm MainParm;
tUart1State Uart1State;   
tDaOutParm DaOutParm;  
tSysTestState SysTestState; 

unsigned int Dsp_State_Start=0;

 
//�����趨����EEPROM�洢���飬64������
unsigned int _EEDATA(128) EPConfigS[128]={
							220,210,205,200,  195,190,185,180,		
							240,300,270,160,  280,130,1,0,			//���в���
							
							0,0,0,0,  400,10000,0,1897,
							3000,2626,1,3,  0,0,0,0,					//ϵͳ����
							
							500,15,130,200,  20,500,20,200,  
							135,500,65,500,  8,100,0x007F,0,  		   	//�������
							
							30,100,40,5,  200,85,40,10,
							50,3,0,0,  0,0,0,0,					//��ͣ����
							
							15,15,15,15,      15,15,15,15,
							0x0000,0,0,0,  0,0,0,0,					//����ӿ�
							
							19,19,19,19,  19,19,19,19,
							19,19,0x0000,0,  1,0,0,0,		  			//����ӿ�
							
							300,600,380,450,  0,0,0,10000,  
							75,40,0,1,   2,9999,0,0,					//���ܲ���
							
							0,0,0,0,   0,0,0,0,
							0,0,0,0,   0,0,0,0
							};
unsigned int EEPROMADDR;	//EEPROM�洢��ַ����
unsigned int _EEDATA(16) EPEndErrorSave[16];
unsigned int _EEDATA(16) EPErrorSaveState[16];
unsigned int _EEDATA(16) EPErrorSaveMainMeau[16];
unsigned int _EEDATA(16) EPErrorSaveBackupMeau[16];
unsigned int _EEDATA(16) EPErrorSaveIUVW[16];
unsigned int _EEDATA(16) EPErrorSaveUin[16];


int AX_int_Mian = 0;
int BX_int_Main = 0;

//***********************************������ ***********************************************************//
int main(void)
{
//��EEP������ϵͳ����
	SysConfig();
//��ʼ�����˿�
    SetupPorts();	
//��ʼ����ʱ��
    InitTimer();
//��ʼ��PWM
    InitPWM();
//��ʼ��AD
    InitAD();
//��ʼ������Ԫ	
	InitIC();
//��ʼ������ͨѶ1
	InitUART1();
//��ʼ������ͨѶ2
	InitUART2();
//��ʼ��I2C����
	InitI2C();
//��ʼ��CN
//	InitCN();
//����Ƚϳ�ʼ��
	InitOC();

//��EEPROM�����ó����ʼ����ֵ��������ʼ���ܵ�Ԫ
    StateInit();
     

    
	while(1)//��ѭ��
    {
	    
	    if(I2CSTATbits.I2COV == 1)
	    	I2CSTATbits.I2COV = 0;
	    if(InsideIOState.SysReset == 0)
	    {
		    asm("CLRWDT");
		}	
	    
	    
	    I2CCONbits.SCLREL = 1;
	    
	    CurProtect();
	    
	    if(MainState.T1Main == 1)
	    {
		    MainState.T1Main = 0;
		    MainCtrl();
		}
		
		if(MainState.T1Five == 1)
		{
			MainState.T1Five = 0;
			
			MainParm.ResetCount = MainParm.ResetCount + 1;
			if(MainParm.ResetCount > 300)
			{
				LATGbits.LATG0 = 0;
				MainParm.ResetCount = 0;
				MainParm.ResetCount = 0;
				MainParm.ResetCount = 0;
				LATGbits.LATG0 = 1;
			}
			AX_int_Mian = ErrorParm.InitError & 0x7000;
			if(AX_int_Mian == 0x7000)
			{
				SysTestState.SysTest = 1;
				SysTest();
			}else
				SysTestState.SysTest = 0;
			
					 
    
			AutoRun();
			OutputDA();
			Uart2Tx();
			if(Uart1Parm.AddrMax == 8)
			{
				Uart1Parm.RunNumber = 0;
  				AutoRunParm.RunNumber = Uart1Parm.Addr - Uart1Parm.RunNumber;
			}else
			{
				Uart1Tx();
			}
			if(RunState.AutoRun == 1)
			{
				if(ErrorParm.EndError != 0)
				{
					if(ErrorParm.ErrorTimes < 16)
					{
						ErrorParm.TimeEnumerate = ErrorParm.TimeEnumerate + 1;
						if(ErrorParm.TimeEnumerate > 18000 )
						{
							ErrorParm.EndError = 0;
							ErrorParm.InitError = 0;
							ErrorParm.ErrorTimes = ErrorParm.ErrorTimes + 1;
							RunState.MeanRun = 0;
							RunState.UnitRun = 0;
							RunState.ImRun = 0;
							ErrorParm.TimeEnumerate = 0;
							AutoRunParm.OutputState = AutoRunParm.OutputState & 0xFFF3;
							OutputState.Normal = 0;
							OutputState.Backup = 0;
							IFS2bits.FLTAIF = 0;   //ֻ���һ�ι��������ж� 
							IEC2bits.FLTAIE = 1;    //ʹ��FLTA�����ж�
			
						}
					}
				}
			}
		}
		
		if(MainState.I2CRcv == 1)
		{
			if(StartState.PreStart == 0)
			{
				MainState.I2CRcv = 0;
				I2CParmSave();
			}
		}
		
		if(MainState.TrnData == 1)
		{
			MainState.TrnData = 0;
			TrnData();
			
		}
		
			
 				
	}  
}	//end of main()
