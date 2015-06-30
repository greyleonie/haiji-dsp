#include "variable.h"

/* define modbus register address map */
typedef struct _modbus_register{
	int	addr;
	void *reg;
} modbus_register;

modbus_register mb_reg[256];

#define MODBUS_MAP_SET(X,Y) mb_reg[index].addr=(X);\
							mb_reg[index++].reg=&(Y)

void modbus_map_init(void)
{
	int index = 0;

	MODBUS_MAP_SET(0x0001,MeauParm.MainMeau);
	MODBUS_MAP_SET(0x0002,MeauParm.BackupMeau);
	MODBUS_MAP_SET(0x0003,CurParms.IU);
	MODBUS_MAP_SET(0x0004,CurParms.IV);
	MODBUS_MAP_SET(0x0005,CurParms.IW);
	MODBUS_MAP_SET(0x0006,VolParms.Uin);
	MODBUS_MAP_SET(0x0007,ErrorParm.EndError);
	MODBUS_MAP_SET(0x0008,AutoRunParm.OutputState);

	int i;
	for (i = 0; i < 128; ++i) {
		MODBUS_MAP_SET((0x0010 + i),(KeyParm.SaveParms[i]));
	}

	MODBUS_MAP_SET(0x0101,Uart1Parm.MainData[0]);
	MODBUS_MAP_SET(0x0102,Uart1Parm.BackupData[0]);
	MODBUS_MAP_SET(0x0103,CurParms.IU);
	MODBUS_MAP_SET(0x0104,CurParms.IV);
	MODBUS_MAP_SET(0x0105,CurParms.IW);
	MODBUS_MAP_SET(0x0106,VolParms.Uin);
	MODBUS_MAP_SET(0x0107,Uart1Parm.ErrorData[0]);
	MODBUS_MAP_SET(0x0108,Uart1Parm.ErrorData[0]);

	MODBUS_MAP_SET(0x0201,Uart1Parm.MainData[1]);
	MODBUS_MAP_SET(0x0202,Uart1Parm.BackupData[1]);
	MODBUS_MAP_SET(0x0203,CurParms.IU);
	MODBUS_MAP_SET(0x0204,CurParms.IV);
	MODBUS_MAP_SET(0x0205,CurParms.IW);
	MODBUS_MAP_SET(0x0206,VolParms.Uin);
	MODBUS_MAP_SET(0x0207,Uart1Parm.ErrorData[1]);
	MODBUS_MAP_SET(0x0208,Uart1Parm.ErrorData[1]);

	MODBUS_MAP_SET(0x0301,Uart1Parm.MainData[2]);
	MODBUS_MAP_SET(0x0302,Uart1Parm.BackupData[2]);
	MODBUS_MAP_SET(0x0303,CurParms.IU);
	MODBUS_MAP_SET(0x0304,CurParms.IV);
	MODBUS_MAP_SET(0x0305,CurParms.IW);
	MODBUS_MAP_SET(0x0306,VolParms.Uin);
	MODBUS_MAP_SET(0x0307,Uart1Parm.ErrorData[2]);
	MODBUS_MAP_SET(0x0308,Uart1Parm.ErrorData[2]);

	MODBUS_MAP_SET(0x0401,Uart1Parm.MainData[3]);
	MODBUS_MAP_SET(0x0402,Uart1Parm.BackupData[3]);
	MODBUS_MAP_SET(0x0403,CurParms.IU);
	MODBUS_MAP_SET(0x0404,CurParms.IV);
	MODBUS_MAP_SET(0x0405,CurParms.IW);
	MODBUS_MAP_SET(0x0406,VolParms.Uin);
	MODBUS_MAP_SET(0x0407,Uart1Parm.ErrorData[3]);
	MODBUS_MAP_SET(0x0408,Uart1Parm.ErrorData[3]);

	MODBUS_MAP_SET(0x0501,Uart1Parm.MainData[4]);
	MODBUS_MAP_SET(0x0502,Uart1Parm.BackupData[4]);
	MODBUS_MAP_SET(0x0503,CurParms.IU);
	MODBUS_MAP_SET(0x0504,CurParms.IV);
	MODBUS_MAP_SET(0x0505,CurParms.IW);
	MODBUS_MAP_SET(0x0506,VolParms.Uin);
	MODBUS_MAP_SET(0x0507,Uart1Parm.ErrorData[4]);
	MODBUS_MAP_SET(0x0508,Uart1Parm.ErrorData[4]);

	MODBUS_MAP_SET(0x0601,Uart1Parm.MainData[5]);
	MODBUS_MAP_SET(0x0602,Uart1Parm.BackupData[5]);
	MODBUS_MAP_SET(0x0603,CurParms.IU);
	MODBUS_MAP_SET(0x0604,CurParms.IV);
	MODBUS_MAP_SET(0x0605,CurParms.IW);
	MODBUS_MAP_SET(0x0606,VolParms.Uin);
	MODBUS_MAP_SET(0x0607,Uart1Parm.ErrorData[5]);
	MODBUS_MAP_SET(0x0608,Uart1Parm.ErrorData[5]);

	MODBUS_MAP_SET(0x0701,Uart1Parm.MainData[6]);
	MODBUS_MAP_SET(0x0702,Uart1Parm.BackupData[6]);
	MODBUS_MAP_SET(0x0703,CurParms.IU);
	MODBUS_MAP_SET(0x0704,CurParms.IV);
	MODBUS_MAP_SET(0x0705,CurParms.IW);
	MODBUS_MAP_SET(0x0706,VolParms.Uin);
	MODBUS_MAP_SET(0x0707,Uart1Parm.ErrorData[6]);
	MODBUS_MAP_SET(0x0708,Uart1Parm.ErrorData[6]);

	MODBUS_MAP_SET(0x0801,Uart1Parm.MainData[7]);
	MODBUS_MAP_SET(0x0802,Uart1Parm.BackupData[7]);
	MODBUS_MAP_SET(0x0803,CurParms.IU);
	MODBUS_MAP_SET(0x0804,CurParms.IV);
	MODBUS_MAP_SET(0x0805,CurParms.IW);
	MODBUS_MAP_SET(0x0806,VolParms.Uin);
	MODBUS_MAP_SET(0x0807,Uart1Parm.ErrorData[7]);
	MODBUS_MAP_SET(0x0808,Uart1Parm.ErrorData[7]);
}

unsigned short modbus_rd_reg(int addr)
{
	int i;
	for (i = 0; i < 200; ++i) {
		if (mb_reg[i].addr == addr) {
			return *(unsigned short *)(mb_reg[i].reg);
		}
	}//end for
	return 0xFFFF;
}


void modbus_wr_reg(int addr, unsigned short val)
{
	int i;
	for (i = 0; i < 200; ++i) {
		if (mb_reg[i].addr == addr) {
			*(unsigned short *)(mb_reg[i].reg) = val;
			break;
		}
	}//end for
}

void modbus_rd_regs(unsigned char *dst, int start_addr, int cnt)
{
	int i, j = 0;
	unsigned short val;

	for (i = 0; i < cnt; ++i) {
		val = modbus_rd_reg(start_addr + i);
		dst[j++] = val & 0x00FF;
		dst[j++] = (val & 0xFF00) >> 8;
	}
}

void modbus_wr_regs(unsigned char *src, int start_addr, int cnt)
{
	int i, j = 0;
	unsigned short val;

	for (i = 0; i < cnt; ++i) {
		((unsigned char *)&val)[0] = src[j++];
		((unsigned char *)&val)[1] = src[j++];
		modbus_wr_reg(start_addr + i, val);
	}
}


