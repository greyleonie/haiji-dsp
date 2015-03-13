//海吉科技，HJR3000型智能软启动控制装置，DSPIC30F6010A系统
//主文件，MainCont.c

//头文件
#include "UserParms.h"	//用户系统配置，常数定义及配置值
#include "Function.h"	//系统外部调用函数声明，内部调用函数在对应文件内声明
#include "variable.h"	//系统全局变量声明，局部变量在对应文件内声明


tSinCosParms SinCosParms;			//查SinCos表参数
tPWMParams PWMParams;				//PWM参数变量结构
tRunState RunState;						//系统运行状态标志，位变量结构
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

 
//键盘设定参数EEPROM存储数组，64个参数
unsigned int _EEDATA(128) EPConfigS[128]={
							220,210,205,200,  195,190,185,180,		
							240,300,270,160,  280,130,1,0,			//运行参数
							
							0,0,0,0,  400,10000,0,1897,
							3000,2626,1,3,  0,0,0,0,					//系统参数
							
							500,15,130,200,  20,500,20,200,  
							135,500,65,500,  8,100,0x007F,0,  		   	//电机参数
							
							30,100,40,5,  200,85,40,10,
							50,3,0,0,  0,0,0,0,					//启停参数
							
							15,15,15,15,      15,15,15,15,
							0x0000,0,0,0,  0,0,0,0,					//输入接口
							
							19,19,19,19,  19,19,19,19,
							19,19,0x0000,0,  1,0,0,0,		  			//输出接口
							
							300,600,380,450,  0,0,0,10000,  
							75,40,0,1,   2,9999,0,0,					//功能参数
							
							0,0,0,0,   0,0,0,0,
							0,0,0,0,   0,0,0,0
							};
unsigned int EEPROMADDR;	//EEPROM存储地址给定
unsigned int _EEDATA(16) EPEndErrorSave[16];
unsigned int _EEDATA(16) EPErrorSaveState[16];
unsigned int _EEDATA(16) EPErrorSaveMainMeau[16];
unsigned int _EEDATA(16) EPErrorSaveBackupMeau[16];
unsigned int _EEDATA(16) EPErrorSaveIUVW[16];
unsigned int _EEDATA(16) EPErrorSaveUin[16];


int AX_int_Mian = 0;
int BX_int_Main = 0;

//***********************************主程序 ***********************************************************//
int main(void)
{
//读EEP，配置系统参数
	SysConfig();
//初始化各端口
    SetupPorts();	
//初始化定时器
    InitTimer();
//初始化PWM
    InitPWM();
//初始化AD
    InitAD();
//初始化捕获单元	
	InitIC();
//初始化串行通讯1
	InitUART1();
//初始化串行通讯2
	InitUART2();
//初始化I2C总线
	InitI2C();
//初始化CN
//	InitCN();
//输出比较初始化
	InitOC();

//读EEPROM并设置程序初始参数值，启动初始功能单元
    StateInit();
     

    
	while(1)//主循环
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
							IFS2bits.FLTAIF = 0;   //只清除一次过流故障中断 
							IEC2bits.FLTAIE = 1;    //使能FLTA故障中断
			
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
