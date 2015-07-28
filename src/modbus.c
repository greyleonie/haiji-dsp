#include "modbus.h"
#include "variable.h"
#include "Function.h"

extern void Uart2TxSend(unsigned char c);
extern void Uart2TxEn(void);
extern void Uart2TxDis(void);
extern void timer4_reset(void);
extern void timer4_stop(void);
extern void CRC16_for_char(unsigned short *crc, unsigned char c);
extern unsigned short CRC16(unsigned char *p, unsigned short len);
extern void modbus_map_init(void);
extern int modbus_wr_reg(int addr, unsigned short val);
extern void modbus_rd_regs(unsigned char *dst, int start_addr, int cnt);
extern int is_register_addr_valid(int start_addr, int cnt);

modbus mb;

int modbus_init(unsigned char adr)
{
	modbus_map_init();
	if (adr >= 1 && adr <= MODBUS_MAX_NODE_ADDRESS) {
		mb.adr = adr;
		mb.state = MODBUS_ST_RECV_IDLE;
		return 0;
	} else {
		return -1;
	}
}

void modbus_receive(unsigned char c)
{
	timer4_reset();
	switch (mb.state) {
		case MODBUS_ST_RECV_IDLE:
			if (c == mb.adr || c == 0) {
				mb.request.adr = c;
				mb.state = MODBUS_ST_RECV_FUNCTION;
				mb.crc = 0xFFFF;
				CRC16_for_char(&mb.crc, c);
			}
			break;

		case MODBUS_ST_RECV_FUNCTION:
			if (c == MODBUS_FC_READ_COILS
				|| c == MODBUS_FC_READ_DISCRETE_INPUTS
				|| c == MODBUS_FC_READ_HOLDING_REGISTERS
				|| c == MODBUS_FC_READ_INPUT_REGISTERS
				|| c == MODBUS_FC_WRITE_SINGLE_COIL
				|| c == MODBUS_FC_WRITE_SINGLE_REGISTER
				|| c == MODBUS_FC_WRITE_MULTIPLE_COILS
				|| c == MODBUS_FC_WRITE_MULTIPLE_REGISTERS
				|| c == MODBUS_FC_WRITE_AND_READ_REGISTERS) {
				mb.request.function = c;
				mb.recv_cnt = 0;
				mb.state = MODBUS_ST_RECV_DATA;
				CRC16_for_char(&mb.crc, c);
			} else {
				mb.state = MODBUS_ST_EXCEPTION;
			}
			break;

		case MODBUS_ST_RECV_DATA:
			switch (mb.request.function) {
				case MODBUS_FC_READ_COILS:
				case MODBUS_FC_READ_DISCRETE_INPUTS:
				case MODBUS_FC_READ_HOLDING_REGISTERS:
				case MODBUS_FC_READ_INPUT_REGISTERS:
					if (mb.recv_cnt == 0) {
						((unsigned char *)&mb.request.data.read_single.address)[HIGH] = c;
						mb.recv_cnt++;
					} else if (mb.recv_cnt == 1) {
						((unsigned char *)&mb.request.data.read_single.address)[LOW] = c;
						mb.recv_cnt++;
					} else if (mb.recv_cnt == 2) {
						((unsigned char *)&mb.request.data.read_single.count)[HIGH] = c;
						mb.recv_cnt++;
					} else if (mb.recv_cnt == 3) {
						((unsigned char *)&mb.request.data.read_single.count)[LOW] = c;
						mb.recv_cnt = 0;
						mb.state = MODBUS_ST_RECV_CRC;
					}//*/
					break;

				case MODBUS_FC_WRITE_SINGLE_COIL:
				case MODBUS_FC_WRITE_SINGLE_REGISTER:
					if (mb.recv_cnt == 0) {
						((unsigned char *)&mb.request.data.write_single.address)[HIGH] = c;
						mb.recv_cnt++;
					} else if (mb.recv_cnt == 1) {
						((unsigned char *)&mb.request.data.write_single.address)[LOW] = c;
						mb.recv_cnt++;
					} else if (mb.recv_cnt == 2) {
						((unsigned char *)&mb.request.data.write_single.value)[HIGH] = c;
						mb.recv_cnt++;
					} else if (mb.recv_cnt == 3) {
						((unsigned char *)&mb.request.data.write_single.value)[LOW] = c;
						mb.recv_cnt = 0;
						mb.state = MODBUS_ST_RECV_CRC;
					}
					break;

				case MODBUS_FC_WRITE_MULTIPLE_COILS:
				case MODBUS_FC_WRITE_MULTIPLE_REGISTERS:
					if (mb.recv_cnt == 0) {
						((unsigned char *)&mb.request.data.write_multiple.address)[HIGH] = c;
						mb.recv_cnt++;
					} else if (mb.recv_cnt == 1) {
						((unsigned char *)&mb.request.data.write_multiple.address)[LOW] = c;
						mb.recv_cnt++;
					} else if (mb.recv_cnt == 2) {
						((unsigned char *)&mb.request.data.write_multiple.count)[HIGH] = c;
						mb.recv_cnt++;
					} else if (mb.recv_cnt == 3) {
						((unsigned char *)&mb.request.data.write_multiple.count)[LOW] = c;
						mb.recv_cnt++;
					} else if (mb.recv_cnt == 4) {
						mb.request.data.write_multiple.count_of_byte = c;
						mb.recv_cnt++;
					} else {
						mb.request.data.write_multiple.data[mb.recv_cnt - 5] = c;
						mb.recv_cnt++;
						if ((mb.recv_cnt - 5) == mb.request.data.write_multiple.count_of_byte) {
							mb.recv_cnt = 0;
							mb.state = MODBUS_ST_RECV_CRC;
						}
					}
					break;

				case MODBUS_FC_MASK_WRITE_REGISTER:
					break;

				case MODBUS_FC_WRITE_AND_READ_REGISTERS:
					if (mb.recv_cnt == 0) {
						((unsigned char *)&mb.request.data.read_write_registers.read_address)[HIGH] = c;
						mb.recv_cnt++;
					} else if (mb.recv_cnt == 1) {
						((unsigned char *)&mb.request.data.read_write_registers.read_address)[LOW] = c;
						mb.recv_cnt++;
					} else if (mb.recv_cnt == 2) {
						((unsigned char *)&mb.request.data.read_write_registers.read_count)[HIGH] = c;
						mb.recv_cnt++;
					} else if (mb.recv_cnt == 3) {
						((unsigned char *)&mb.request.data.read_write_registers.read_count)[LOW] = c;
						mb.recv_cnt++;
					} else if (mb.recv_cnt == 4) {
						((unsigned char *)&mb.request.data.read_write_registers.write_address)[HIGH] = c;
						mb.recv_cnt++;
					} else if (mb.recv_cnt == 5) {
						((unsigned char *)&mb.request.data.read_write_registers.write_address)[LOW] = c;
						mb.recv_cnt++;
					} else if (mb.recv_cnt == 6) {
						((unsigned char *)&mb.request.data.read_write_registers.write_count)[HIGH] = c;
						mb.recv_cnt++;
					} else if (mb.recv_cnt == 7) {
						((unsigned char *)&mb.request.data.read_write_registers.write_count)[LOW] = c;
						mb.recv_cnt++;
					} else if (mb.recv_cnt == 8) {
						mb.request.data.read_write_registers.write_count_of_byte = c;
						mb.recv_cnt++;
					} else {
						mb.request.data.read_write_registers.data[mb.recv_cnt - 9] = c;
						mb.recv_cnt++;
						if ((mb.recv_cnt - 9) == mb.request.data.read_write_registers.write_count_of_byte) {
							mb.recv_cnt = 0;
							mb.state = MODBUS_ST_RECV_CRC;
						}
					}
					break;

				default:
					break;
			} // end switch (mb.function)
			CRC16_for_char(&mb.crc, c);
			break;
			
		case MODBUS_ST_RECV_CRC:
			if (mb.recv_cnt == 0) {
				((unsigned char *)&mb.request.crc)[HIGH] = c;
				mb.recv_cnt++;
			} else if (mb.recv_cnt == 1) {
				((unsigned char *)&mb.request.crc)[LOW] = c;
				mb.recv_cnt = 0;
				mb.state = MODBUS_ST_MAKE_RESPONSE;
				timer4_stop();
			}
			break;
	
		case MODBUS_ST_EXCEPTION:
			//drop data, and wait timeout
			break;

		default:
			break;
	}// end switch
}

void modbus_exception(unsigned char exception_code)
{
	unsigned short crc;
	int i;

	mb.response.data[0] = mb.adr;
	mb.response.data[1] = (mb.request.function | 0x80);
	mb.response.data[2] = exception_code;
	crc = CRC16(&mb.response.data[0], 3);
	mb.response.data[3] = ((unsigned char *)&crc)[HIGH];
	mb.response.data[4] = ((unsigned char *)&crc)[LOW];
	mb.response.length = 5;

	for (i = 0; i < 16; ++i);	//fix it, waiting for Uart TX flag
}

void modbus_read_holding_registers(void)
{
	unsigned short crc;
	unsigned char cnt;

	// check read registers count
	if (mb.request.data.read_single.count < 1
		|| mb.request.data.read_single.count > MODBUS_MAX_READ_REGISTERS) {
		modbus_exception(MODBUS_EXCEPTION_ILLEGAL_DATA_VALUE);
		return;
	}

	// check read registers address and offest
	if (!is_register_addr_valid(mb.request.data.read_single.address,
								mb.request.data.read_single.count)) {
		modbus_exception(MODBUS_EXCEPTION_ILLEGAL_DATA_ADDRESS);
		return;
	}

	// read registers, and create response packet
	mb.response.data[0] = mb.adr;
	mb.response.data[1] = mb.request.function;

	cnt = (mb.request.data.read_single.count << 1) & 0x00FF;
	mb.response.data[2] = cnt;
	modbus_rd_regs(&mb.response.data[3], 
					mb.request.data.read_single.address, 
					mb.request.data.read_single.count);	

	crc = CRC16(&mb.response.data[0], cnt + 3);
	mb.response.data[cnt + 3] = ((unsigned char *)&crc)[HIGH];
	mb.response.data[cnt + 4] = ((unsigned char *)&crc)[LOW];

	mb.response.length = cnt + 5;
}

void modbus_write_single_register(void)
{
	unsigned short crc;
	unsigned short value;

	// write register
	if (!modbus_wr_reg(mb.request.data.write_single.address,
					mb.request.data.write_single.value)) {
		modbus_exception(MODBUS_EXCEPTION_ILLEGAL_DATA_ADDRESS);
		return;
	}

	// write EEPROM
	if (mb.request.data.write_single.address >= 0x0010) {
		EEPROMADDR = 0xF000 + 2 * (mb.request.data.write_single.address - 0x0010);
	    EraseEE(__builtin_tblpage(&EPConfigS[0]), EEPROMADDR, 1);
	    WriteEE(&mb.request.data.write_single.value, __builtin_tblpage(&EPConfigS[0]), EEPROMADDR, 1);
		ReadEE(__builtin_tblpage(&EPConfigS[0]), EEPROMADDR, (int *)&value, 1);
		if (value != mb.request.data.write_single.value) {
			modbus_exception(MODBUS_EXCEPTION_SLAVE_OR_SERVER_FAILURE);
		 	return;
		}
	} // if (mb.request.data.write_single.address >= 0x0010)

	// create response packet
	mb.response.data[0] = mb.adr;
	mb.response.data[1] = mb.request.function;
	mb.response.data[2] = ((unsigned char *)&mb.request.data.write_single.address)[HIGH];
	mb.response.data[3] = ((unsigned char *)&mb.request.data.write_single.address)[LOW];
	mb.response.data[4] = ((unsigned char *)&value)[HIGH];
	mb.response.data[5] = ((unsigned char *)&value)[LOW];
	crc = CRC16(&mb.response.data[0], 6);
	mb.response.data[6] = ((unsigned char *)&crc)[HIGH];
	mb.response.data[7] = ((unsigned char *)&crc)[LOW];
	mb.response.length = 8;
}

char modbus_send(void)
{
	char c = mb.response.data[mb.send_cnt];
	mb.send_cnt++;

	return c;
}

void modbus_slave(void)
{
	switch (mb.state) {
		case MODBUS_ST_MAKE_RESPONSE:
			//check request
			if (mb.crc == mb.request.crc) {
				// make response packet
				Uart2TxEn();	//fix it
				switch (mb.request.function) {
					case MODBUS_FC_READ_HOLDING_REGISTERS:
						modbus_read_holding_registers();
						break;

					case MODBUS_FC_WRITE_SINGLE_REGISTER:
						modbus_write_single_register();
						break;

					default:
						modbus_exception(MODBUS_EXCEPTION_ILLEGAL_FUNCTION);
						break;

				}// end switch (mb.mb.request.function)
				mb.send_cnt = 0;
				Uart2TxSend(modbus_send());
				mb.state = MODBUS_ST_SEND_RESPONSE;
			} else {
				mb.state = MODBUS_ST_RECV_IDLE;
			}
			break;

		case MODBUS_ST_EXCEPTION:
			//wait timeout
			break;

		case MODBUS_ST_MAKE_EXCEPTION:
			break;

		case MODBUS_ST_SEND_RESPONSE:
		case MODBUS_ST_SEND_EXCEPTION:
			//wait send done
			break;
		
		case MODBUS_ST_SEND_DONE:
			Uart2TxDis();
			mb.state = MODBUS_ST_RECV_IDLE;
			break;
	
		default:
			break;
	}// end switch
}


char modbus_is_send_done(void)
{
	return (mb.send_cnt == mb.response.length);
}

void modbus_send_done(void)
{
	mb.state = MODBUS_ST_SEND_DONE;
}

void modbus_reset(void)
{
	mb.state = MODBUS_ST_RECV_IDLE;
}

