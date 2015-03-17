//海吉科技，HJR3000型智能软启动控制装置，DSPIC30F6010A系统
//系统全局变量声明，局部变量在对应文件内声明  variable.h


#ifndef variable_H
#define variable_H   

#include <p30F6010A.h>

//****************** 独立全局变量**********************
extern unsigned int EEPROMADDR;		//地址给定 
extern unsigned int _EEDATA(128) EPConfigS[128];	//EEPROM数据存储
extern unsigned int _EEDATA(16) EPEndErrorSave[16];
extern unsigned int _EEDATA(16) EPErrorSaveState[16];
extern unsigned int _EEDATA(16) EPErrorSaveMainMeau[16];
extern unsigned int _EEDATA(16) EPErrorSaveBackupMeau[16];
extern unsigned int _EEDATA(16) EPErrorSaveIUVW[16];
extern unsigned int _EEDATA(16) EPErrorSaveUin[16];
extern unsigned int Dsp_State_Start;

//****************** 结构变量**********************

//定义状态位标识
typedef struct{
	unsigned Run:1;
    unsigned AutoRun:1;
	unsigned HighByLow:1;
	unsigned MeanRun:1;
	unsigned PreRun:1;
	unsigned ImRun:1;
	unsigned UnitRun:1;
	unsigned FillGas:1;
	unsigned MainOpen:1;
	unsigned BackupOpen:1;
	unsigned StopOff:1;
	unsigned StopGasOff:1;
	unsigned :1;
    unsigned :1;
	unsigned :1;
	unsigned :1;		
}tRunState;
extern tRunState RunState;

//定义状态位标识
typedef struct{
	unsigned SoftStartEnd:1;
    unsigned SoftRunEnd:1;
	unsigned SoftStopEnd:1;
	unsigned PreStart:1;
	unsigned SoftStart:1;
	unsigned RoadRun:1;
	unsigned SoftStopStartEnd:1;
	unsigned LessCar:1;
	unsigned UpCarIU:1;
	unsigned UpCarIV:1;
	unsigned UpCarIW:1;
	unsigned SoftStop:1;
	unsigned JumpRun:1;
    unsigned ShaChe:1;
	unsigned BenJiRun:1;
	unsigned :1;		
}tStartState;
extern tStartState StartState;
 

//定义状态位标识
typedef struct{
	unsigned UoutH:1;
    unsigned VoutH:1;
	unsigned WoutH:1;
	unsigned UoutPhyH:1;
	unsigned VoutPhyH:1;
	unsigned WoutPhyH:1;
	unsigned UoutPhyL:1;
	unsigned VoutPhyL:1;
	unsigned WoutPhyL:1;
	unsigned UoutL:1;
    unsigned VoutL:1;
	unsigned WoutL:1;
	unsigned StartOut:1;
	unsigned :1;
	unsigned :1;
	unsigned :1;		
}tPwmState;
extern tPwmState PwmState; 

//定义状态位标识
typedef struct{
	unsigned Cur:1;
    unsigned I2CTrn:1;
	unsigned TrnData:1;
	unsigned DisconTime:1;
	unsigned UartTx:1;
	unsigned UartTxOff:1;
	unsigned UartTxOn:1;
	unsigned T1Main:1;
	unsigned I2CRcv:1;
	unsigned UartRx:1;	
	unsigned TrnParam:1;
	unsigned TrnError:1;
	unsigned RcvTrnData:1;
	unsigned T1Five:1;
	unsigned :1;
	unsigned :1;
    	
}tMainState;
extern tMainState MainState; 


//定义状态位标识
typedef struct{
	unsigned Phy:1;
    unsigned :1;
	unsigned :1;
	unsigned :1;
	unsigned :1;
	unsigned :1;
	unsigned :1;
	unsigned :1;
	unsigned :1;
	unsigned :1;	
	unsigned :1;
	unsigned :1;
	unsigned :1;
	unsigned :1;
	unsigned SysTest:1;
	unsigned :1;
    	
}tSysTestState;
extern tSysTestState SysTestState; 


//定义状态位标识
typedef struct{
	unsigned UartTx:1;
	unsigned UartTxOff:1;
	unsigned UartTxOn:1;
	unsigned UartRx:1;	
	unsigned UartTR:1;
	unsigned Change:1;
	unsigned :1;
	unsigned :1;
	unsigned :1;
	unsigned :1;	
	unsigned :1;
	unsigned :1;
	unsigned :1;
	unsigned :1;
	unsigned :1;
	unsigned :1;
    	
}tUart1State;
extern tUart1State Uart1State; 

//定义故障状态位标识
typedef struct {
    unsigned FLTA_Error:1;
    unsigned ImbalanceCar_Error:1;
	unsigned OverCar_Error:1;
	unsigned LowCar_Error:1;
	unsigned UnLimitCar_Error:1;
	unsigned :1;
	unsigned :1;
	unsigned HighVol_Error:1;
	unsigned LowVol_Error:1;
	unsigned :1;
	unsigned :1;
	unsigned :1;
	unsigned DisconU_Error:1;
    unsigned DisconV_Error:1;
	unsigned DisconW_Error:1;
	unsigned ComponentHot_Error:1;	
} tErrorState;
extern tErrorState ErrorState;

//定义IO口输入标识
typedef struct{
	unsigned  ImRun:1;
	unsigned  ImStop:1;
	unsigned  ImLog:1;
	unsigned  Stop:1;
	unsigned  NormalRun:1;
	unsigned  BackupRun:1;
	unsigned  Backup2Run:1;
	unsigned  Backup3Run:1;
	unsigned  Backup4Run:1;
	unsigned  Backup5Run:1;
	unsigned  Backup6Run:1;
	unsigned  Backup7Run:1;
	unsigned  AutoStop:1;
	unsigned  RunLimit:1;
	unsigned  RunPrePare:1;
	unsigned  :1;
}tInputState;
extern tInputState InputState;

//定义IO口输入标识
typedef struct{
	unsigned  Men:1;
	unsigned  Stop:1;
	unsigned  Auto:1;
	unsigned  ComponentHot:1;
	unsigned  ByPassIn:1;
	unsigned  Bd0:1;
	unsigned  Bd1:1;
	unsigned  Bd2:1;
	unsigned  Bd3:1;
	unsigned  SysReset:1;
	unsigned  ByPassOut:1;
	unsigned  IoAuto:1;
	unsigned  IoStop:1;
	unsigned  BackupStop:1;
	unsigned  :1;
	unsigned  :1;
}tInsideIOState;
extern tInsideIOState InsideIOState;

//定义IO口输出标识
typedef struct{
	unsigned  Error:1;
	unsigned  OverHigh:1;
	unsigned  OverLow:1;
	unsigned  AboveHigh:1;
	unsigned  AboveLow:1;
	unsigned  Run:1;
	unsigned  Normal:1;
	unsigned  Backup:1;
	unsigned  FillGas:1;
	unsigned  Stay:1;
	unsigned  Auto:1;
	unsigned  Men:1;
	unsigned  Stop:1;
	unsigned  Prepare:1;
	unsigned  Start:1;
	unsigned  StopMent:1;
}tOutputState;
extern tOutputState OutputState;



//定义IO口输入状态标识
typedef struct{
	unsigned  In1:1;
	unsigned  In2:1;
	unsigned  In3:1;
	unsigned  In4:1;
	unsigned  In5:1;
	unsigned  In6:1;
	unsigned  In7:1;
	unsigned  In8:1;
	unsigned  :1;
	unsigned  :1;
	unsigned  :1;
	unsigned  :1;
	unsigned  :1;
	unsigned  :1;
	unsigned  :1;
	unsigned  :1;
	
}tInputIO;
extern tInputIO InputIO;

//定义IO口输出状态标识
typedef struct{
	unsigned  OU1:1;
	unsigned  OU2:1;
	unsigned  OU3:1;
	unsigned  OU4:1;
	unsigned  OU5:1;
	unsigned  OU6:1;
	unsigned  OU7:1;
	unsigned  OU8:1;
	unsigned  OU9:1;
	unsigned  OU10:1;
	unsigned  StopFillGas:1;
	unsigned  MainMeauError:1;
	unsigned  BackupMeauError:1;
	unsigned  BackupMeauHigh:1;
	unsigned  BackupMeauLow:1;
	unsigned  :1;
	
}tOutputIO;
extern tOutputIO OutputIO;

//定义IO口输入状态逻辑变换标识
typedef struct{
	unsigned  In1:1;
	unsigned  In2:1;
	unsigned  In3:1;
	unsigned  In4:1;
	unsigned  In5:1;
	unsigned  In6:1;
	unsigned  In7:1;
	unsigned  In8:1;
	unsigned  :1;
	unsigned  :1;
	unsigned  :1;
	unsigned  :1;
	unsigned  :1;
	unsigned  :1;
	unsigned  :1;
	unsigned  :1;
	
}tInputLogic;
extern tInputLogic InputLogic;


typedef struct {
    unsigned int T1Times;
	unsigned int ResetCount;
	
}tMainParm;
extern tMainParm MainParm;  

typedef struct {
    unsigned int InitError;
    unsigned int EndError;
    unsigned int PassError;
	int HotCompOnEnumerate;
	unsigned int AgoEndError;
	unsigned int ErrorSaveState[16];
	unsigned int EndErrorSave[16];
	unsigned int ErrorSaveMainMeau[16];
	unsigned int ErrorSaveBackupMeau[16];
	unsigned int ErrorSaveIUVW[16];
	unsigned int ErrorSaveUin[16];
	int HotCommTime;
	int HotCompEnumerate;
	int ConnectCurTime;
	int ConnectCurEnumerate;
    int DisconTime;
    int DisconEnumerateU;
    int DisconEnumerateV;
	int DisconEnumerateW;
	int DisconEnumerateUV;
    int DisconEnumerateVW;
	int DisconEnumerateWU;
	unsigned int TimeEnumerate;
	unsigned int ErrorTimes;
	
}tErrorParm;
extern tErrorParm ErrorParm;  

//定义键盘给定参数
typedef struct {
    unsigned int In1;
    unsigned int In2;
    unsigned int In3;
    unsigned int In4;
    unsigned int In5;
    unsigned int In6;
    unsigned int In7;
    unsigned int In8;
    unsigned int Out1;
    unsigned int Out2;
    unsigned int Out3;
    unsigned int Out4;
    unsigned int Out5;
    unsigned int Out6;
    unsigned int Out7;
    unsigned int Out8;
    unsigned int Out9;
    unsigned int Out10;
    unsigned int CtrMode;
    unsigned int StartMode;
    unsigned int StopMode;
    unsigned int SaveParms[128];
    unsigned int InLogic;
    unsigned int OutLogic;
 	unsigned int RunMode;
 	unsigned int FillGasMode;
 	unsigned int BackupMeauHigh;
 	unsigned int BackupMeauLow;
 	   
}tKeyParm;
extern tKeyParm KeyParm;  

//定义检测参数
typedef struct {
    int MainMeauMax;
    int MainMeauFine;
    int BackupMeauMax;
    int BackupMeauFine;
    int MainMeauPeak;
    int BackupMeauPeak;
    int MainMeauPeakOld;
    int BackupMeauPeakOld;
    long MainMeauAcc;
    long BackupMeauAcc;
    int MainMeauInit[8];
    int BackupMeauInit[8];
    int MainMeau;
    int MainMeauCom;
    int BackupMeau;
    int BackupMul;
    int MainMul;
    long BackupAdd;
    long MainAdd;
    unsigned int MainEnumerate;
    unsigned int BackupEnumerate;
    
    int MainMeau1;
    int MainMeau2;
    int MainMeau3;
    int MainMeau4;
    int MainMeau5;
    int MainMeau6;
    int MainMeau7;
    int MainMeau8;
       
}tMeauParm;
extern tMeauParm MeauParm;  

//定义自动运行参数
typedef struct {
    unsigned int FillGas;
    unsigned int FillOil;
    unsigned int Normal;
    unsigned int Backup;
    unsigned int Backup2;
    unsigned int Backup3;
    unsigned int Backup4;
    unsigned int Backup5;
    unsigned int Backup6;
    unsigned int Backup7;
    unsigned int Stop;
    unsigned int OverHigh;
    unsigned int OverLow;
    unsigned int AboveHigh;
    unsigned int AboveLow;
    unsigned int Limit;
    unsigned int RunParm[8];
    unsigned int OutputState;
    unsigned int PrepareEnumerate;
    unsigned int RunOutEnumerate;
    unsigned int StayOutEnumerate;
    unsigned int ChangeTimes;
    unsigned int ChangeEnumerate;
    unsigned int RunNumber;
    unsigned int StopEnumerate;
    unsigned int StopFillGasEnumerate;
    unsigned int StopFillGasOnEnumerate;
    unsigned int AutoEnumerate; 
      
}tAutoRunParm;
extern tAutoRunParm AutoRunParm;  


//定义SinCos查表参数
typedef struct {
	short	qAngle;
    short	qSin;
    short   qCos;
    
    } tSinCosParms;   
extern tSinCosParms SinCosParms;

//定义PWM输出参数
typedef struct{
	int Duty1H;
	int Duty2H;
	int Duty3H;
	int Delay1H;
	int Delay2H;
	int Delay3H;
	int Duty1L;
	int Duty2L;
	int Duty3L;
	int Delay1L;
	int Delay2L;
	int Delay3L;
	int FLTA_Js;				//FLTA中断（PWM故障）尝试清除计数器，
	int OnPWM;
	unsigned int StartOut;
}tPWMParams;
extern tPWMParams PWMParams;


//定义电流检测参数
typedef struct{
    short IU;
    short PeakIU;
    long AccIU;
    short PeakIUOld;
    
    short IV;
    short PeakIV;
    long AccIV;
    short PeakIVOld;
    
    short IW;
    short PeakIW;
    long AccIW;
    short PeakIWOld;
    
    short IUVW;
    
    short OverCur;
    short UnbalanceCur;
    short LowCur;
    short UnLimitCur;
    
    
    int CarDescendTimesIU;
    int CarUpTimesIU;
    int AgoIU;
    int MaxIU;
    
    int CarDescendTimesIV;
    int CarUpTimesIV;
    int AgoIV;
    int MaxIV;
    
    int CarDescendTimesIW;
    int CarUpTimesIW;
    int AgoIW;
    int MaxIW;
    
    
    int OverCurTime;
    int UnbalanceCurTime;
    int LowCurTime;
    int UnLimitTimeCur;
    
    int OverCurEnumerate;
    int UnbalanceCurEnumerate;
    int LowCurEnumerate;
    int UnLimitTimeCurEnumerate;
    
    
    int LessCarIUVW;
    
    short Times;
    
}tCurParms;
extern tCurParms CurParms;

typedef struct{
    short Uin;
    short PeakUin;
    long AccUin;
    short PeakUinOld;
    
    short HighVol;
    short LowVol;
    int LowVolTime;
    int HighVolTime;
    int LowVolEnumerate;
    int HighVolEnumerate;
    
}tVolParms;
extern tVolParms VolParms;

typedef struct{
    short RateCur;
    short RateVol;
    short RatePower;
    short LimitCar;
    short MaxMeauCur;
    short MaxMeauVol;
    short AddMeauVol;
    
}tSysParms;
extern tSysParms SysParms;

typedef struct{
    short StartTimeIC1;
    short StartTimeIC2;
    short StartTimeIC3;
    
    short EndTimeIC1;
    short EndTimeIC2;
    short EndTimeIC3;
    short CurTimeIC1;
    short CurTimeIC2;
    short CurTimeIC3;
    short OldTimeIC2;
    short OldTimeIC3;
    
}tICParms;
extern tICParms ICParms;

typedef struct{
    long Data;
    int OutData;
    long LoopData;
    long ImmedLoopData;
    long SoftStopLoopData;
    long StopLoopData;
    int RunTime;
    int EndTime;
    int SoftStopRunTime;
    int SoftStopEndTime;
    long StartData;
    long SoftStopStartData;
    long EndData;
    long SoftStopEndData;
    long JumpStartData;
    long StopEndData;
    int LimitCar;
    int LimitCarTimes;
    int JumpRunTimes;
    int JumpLoopData;
    unsigned int PrepareTime;
    unsigned int PrepareDelay;
    
    
}tSoftRunParms;
extern tSoftRunParms SoftRunParms;

//
typedef struct {
    unsigned int RxTimes;
    unsigned int TxTimes;
    unsigned int RxCurData;
	unsigned int TxCurData;
	unsigned int TxData[8];
	int dBaudRate;
	int dBaudRateTcy;
	unsigned int Addr;
	unsigned int DataAddrH;
	unsigned int DataAddrL;
	unsigned int HighCRC;
	unsigned int LowCRC;
    unsigned int dPDSEL;
    unsigned int UartCRC;
    unsigned int KeyParamDataL;
    unsigned int KeyParamDataH;
    unsigned int KeyParamAddr;
    
}tUart2Parm;
extern tUart2Parm Uart2Parm;  

//
typedef struct {
    unsigned int RxTimes;
    unsigned int TxTimes;
    unsigned int RxCurData;
	unsigned int TxCurData;
	unsigned int TxData[16];
	int dBaudRate;
	int dBaudRateTcy;
	unsigned int Addr;
	unsigned int DataAddr;
	unsigned int AddrMax;
	unsigned int dPDSEL;
    unsigned int RunNumber;
    unsigned int ErrorData[8];
    unsigned int StateData[8];
    unsigned int MainData[8];
    unsigned int BackupData[8];
    unsigned int TxEnumerate;
    unsigned int RxData[16];
    unsigned int AddrEnumerate;
    unsigned int RxErrorEnumerate;
    unsigned int TxTimesEnumerate;
    
	
}tUart1Parm;
extern tUart1Parm Uart1Parm;  

typedef struct {
    unsigned int RcvTimes;
    unsigned int TrnTimes;
    unsigned int RcvSaveTimes;
	unsigned int RcvCurData;
	unsigned int TrnCurData;
	unsigned int RcvData[256];
	unsigned int TrnData[24];
	unsigned int RcvDataCheck;
	unsigned int TrnDataCheck;
	
	
}tI2CParm;
extern tI2CParm I2CParm;  

typedef struct {
    unsigned int DaOutput1;
    unsigned int DaOutput2;
    int OutData1;
    int OutData2;
    int OutData1Mul;
    int OutData2Mul;
    int OutData1Add;
    int OutData2Add;
    
       
}tDaOutParm;
extern tDaOutParm DaOutParm;  


#endif  
