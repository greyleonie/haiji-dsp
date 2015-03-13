//�����Ƽ���HJR3000����������������װ�ã�DSPIC30F6010Aϵͳ
//ϵͳ�ⲿ���ú����������ڲ����ú����ڶ�Ӧ�ļ�������  Function.h

#ifndef Function_H
#define Function_H   
   
//��EEP������ϵͳ����
extern  void SysConfig(void);
//��ʼ�����˿�1
extern  void SetupPorts(void);
//��ʼ����ʱ��
extern  void InitTimer(void);
//��ʼ��PWM
extern void  InitPWM(void);
//��ʼ��AD
extern void  InitAD(void);
//��ʼ������Ԫ
extern void InitIC( void );
//��ʼ���������뵥Ԫ
extern void InitQEI(void);
//��ʼ��CN
extern void InitCN(void);
// I2C ���߳�ʼ��
extern void InitI2C(void);
// UART1 ����ͨѶ��ʼ��
extern void InitUART1(void);
// UART2 ����ͨѶ��ʼ��
extern void InitUART2(void);
//����Ƚϳ�ʼ��
extern void InitOC(void);
//��EEPROM
extern int ReadEE(int Page, int Offset, int* DataOut, int Size);
//����EEPROM
extern int EraseEE(int Page, int Offset, int Size);
//дEEPROM
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


//��EEP������PWM����Ƶ��
extern void readEEP(void);
//PWM����
extern void StarPWM(void);
//PWMֹͣ
extern void StopPWM(void);
//��EEPROM�����ó����ʼ����ֵ��������ʼ���ܵ�Ԫ

extern void IORead(void);		//��IO��״̬
extern void IOCorp(void);		//IO��״̬����
extern void IOWrite(void);		//IO�����
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

