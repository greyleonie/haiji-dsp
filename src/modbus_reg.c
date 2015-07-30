#include "variable.h"

/* define modbus register address map */
#define MAX_REGISTERS			256
#define REGISTERS_BASE_ADDRESS 	0x0000
#define REGISTERS_SIZE			144

typedef struct _register_map {
	struct _register {
		int	addr;
		void *reg;
	} reg[MAX_REGISTERS];

	int cnt;
} register_map;

register_map reg_map;

#define MODBUS_MAP_SET(X,Y) reg_map.reg[index].addr=(X);\
							reg_map.reg[index++].reg=&(Y);\
							reg_map.cnt++

void modbus_map_init(void)
{
	int index = 0;
	reg_map.cnt = 0;

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
}

unsigned short modbus_rd_reg(int addr)
{
	int i;
	for (i = 0; i < 200; ++i) {
		if (reg_map.reg[i].addr == addr) {
			return *(unsigned short *)(reg_map.reg[i].reg);
		}
	}//end for
	return 0xFFFF;
}


int modbus_wr_reg(int addr, unsigned short val)
{
	int i;
	for (i = 0; i < 200; ++i) {
		if (reg_map.reg[i].addr == addr) {
			*(unsigned short *)(reg_map.reg[i].reg) = val;
			break;
		}
	}//end for
	if (i == 200)
		return 0;
	else
		return 1;
}

void modbus_rd_regs(unsigned char *dst, int start_addr, int cnt)
{
	int i, j = 0;
	unsigned short val;

	for (i = 0; i < cnt; ++i) {
		val = modbus_rd_reg(start_addr + i);
		dst[j++] = ((unsigned char *)&val)[1];
		dst[j++] = ((unsigned char *)&val)[0];
	}
}

void modbus_wr_regs(unsigned char *src, int start_addr, int cnt)
{
	int i, j = 0;
	unsigned short val;

	for (i = 0; i < cnt; ++i) {
		((unsigned char *)&val)[1] = src[j++];
		((unsigned char *)&val)[0] = src[j++];
		modbus_wr_reg(start_addr + i, val);
	}
}

int is_register_addr_valid(int start_addr, int cnt)
{
	if (start_addr >= REGISTERS_BASE_ADDRESS
		&& (start_addr + cnt) < (REGISTERS_BASE_ADDRESS + REGISTERS_SIZE))
		return 1;
	else
		return 0;
}

