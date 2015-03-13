//海吉科技，HJR3000型智能软启动控制装置，DSPIC30F6010A系统
//系统外部调用函数声明，内部调用函数在对应文件内声明  Function.h

#ifndef Function_H
#define Function_H   
   
//读EEP，配置系统参数
extern  void SysConfig(void);
//初始化各端口1
extern  void SetupPorts(void);
//初始化定时器
extern  void InitTimer(void);
//初始化PWM
extern void  InitPWM(void);
//初始化AD
extern void  InitAD(void);
//初始化捕获单元
extern void InitIC( void );
//初始化正交编码单元
extern void InitQEI(void);
//初始化CN
extern void InitCN(void);
// I2C 总线初始化
extern void InitI2C(void);
// UART1 串行通讯初始化
extern void InitUART1(void);
// UART2 串行通讯初始化
extern void InitUART2(void);
//输出比较初始化
extern void InitOC(void);
//读EEPROM
extern int ReadEE(int Page, int Offset, int* DataOut, int Size);
//擦除EEPROM
extern int EraseEE(int Page, int Offset, int Size);
//写EEPROM
extern int WriteEE(int* DataIn, int Page, int Offset, int Size);
// Calculate qSin,qCos from iAngle
extern void SinCos(void);     
 
extern void __attribute__((__interrupt__)) _PWMInterrupt(void);
extern void __attribute__((__interrupt__)) _T1Interrupt(void);
extern void __attribute__((__interrupt__)) _FLTAInterrupt(void);
extern void __attribute__((__interrupt__)) _CNInterrupt(void);
extern void __attribute__((__interrupt__)) _ADCInterrupt(void);
extern void __attribute__((__interrupt__)) _IC1Interrupt (void);
extern void __attribute__((__interrupt__)) _IC2Interrupt (void);
extern void __attribute__((__interrupt__)) _IC3Interrupt (void);
extern void __attribute__((__interrupt__)) _IC4Interrupt (void);
extern void __attribute__((__interrupt__)) _SI2CInterrupt (void);
extern void __attribute__((__interrupt__)) _MI2CInterrupt (void);
extern void __attribute__((__interrupt__)) _U2RXInterrupt (void);
extern void __attribute__((__interrupt__)) _U2TXInterrupt (void);
extern void __attribute__((__interrupt__)) _U1RXInterrupt (void);
extern void __attribute__((__interrupt__)) _U1TXInterrupt (void);


//读EEP，设置PWM调制频率
extern void readEEP(void);
//PWM启动
extern void StarPWM(void);
//PWM停止
extern void StopPWM(void);
//读EEPROM并设置程序初始参数值，启动初始功能单元

extern void IORead(void);		//读IO口状态
extern void IOCorp(void);		//IO口状态处理
extern void IOWrite(void);		//IO口输出
extern void CurProtect(void);
extern void Uart1Tx(void);
extern void Uart2Tx(void);
extern void TrnData(void);
extern void MainCtrl(void);
extern void I2CParmSave(void);
extern void AutoRun(void);
extern void Uart1TxData(void);
extern void OutputDA(void);
extern void SysTest(void);

extern void PingJun0(void);
extern void PingJun1(void);
extern void PingJun2(void);
extern void PingJun3(void);
extern void PingJun4(void);
extern void PingJun5(void);
extern void PingJun6(void);
extern void PingJun7(void);

#endif 

