#include "modbus.h"
#include "variable.h"
#include "Function.h"

extern void Uart2TxSend(unsigned char c);
extern void Uart2TxEn(void);
extern void Uart2TxDis(void);
extern void Uart2TxBuf(unsigned char *buf, int len);
extern void timer4_reset(void);
extern void timer4_stop(void);
extern void CRC16_for_char(unsigned short *crc, unsigned char c);
extern unsigned short CRC16(unsigned char *p, unsigned short len);
extern void modbus_map_init(void);
extern unsigned short modbus_rd_reg(int addr);
extern void modbus_wr_reg(int addr, unsigned short val);
extern void modbus_rd_regs(unsigned char *dst, int start_addr, int cnt);
extern void modbus_wr_regs(unsigned char *src, int start_addr, int cnt);
 
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
				//start timer 
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


void modbus_read_holding_registers(void)
{
	unsigned short crc;
	unsigned char cnt = (mb.request.data.read_single.count << 1) & 0x00FF;

	mb.response.data[0] = mb.adr;
	mb.response.data[1] = mb.request.function;

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

	if (mb.request.data.write_single.address < 128) {
		// write KeyParm
		Uart2Parm.KeyParamAddr = mb.request.data.write_single.address;
		KeyParm.SaveParms[Uart2Parm.KeyParamAddr] = mb.request.data.write_single.value;

		// write EEPROM
		EEPROMADDR = 0xF000 + 2 * Uart2Parm.KeyParamAddr;
	    EraseEE(__builtin_tblpage(&EPConfigS[0]),EEPROMADDR, 1);
	    WriteEE(&KeyParm.SaveParms[Uart2Parm.KeyParamAddr],__builtin_tblpage(&EPConfigS[0]),EEPROMADDR, 1);
		ReadEE(__builtin_tblpage(&EPConfigS[0]), EEPROMADDR, (int *)&value, 1);
		if (value == mb.request.data.write_single.value) {
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
		} else {
			// write data error
			mb.response.data[0] = mb.adr;
			mb.response.data[1] = (MODBUS_EXCEPTION_SLAVE_OR_SERVER_FAILURE | 0x80); // data error
			crc = CRC16(&mb.response.data[0], 2);
			mb.response.data[2] = ((unsigned char *)&crc)[HIGH];
			mb.response.data[3] = ((unsigned char *)&crc)[LOW];
			mb.response.length = 4;
		}
	} else { //if (mb.request.data.write_single.address < 128)
		// address invalid
		mb.response.data[0] = mb.adr;
		mb.response.data[1] = (MODBUS_EXCEPTION_ILLEGAL_DATA_ADDRESS | 0x80); // invalid address
		crc = CRC16(&mb.response.data[0], 2);
		mb.response.data[2] = ((unsigned char *)&crc)[HIGH];
		mb.response.data[3] = ((unsigned char *)&crc)[LOW];
		mb.response.length = 4;
	}
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
				switch (mb.request.function) {
					case MODBUS_FC_READ_HOLDING_REGISTERS:
						Uart2TxEn();
						modbus_read_holding_registers();
						break;

					case MODBUS_FC_WRITE_SINGLE_REGISTER:
						Uart2TxEn();
						modbus_write_single_register();
						break;

					case MODBUS_FC_WRITE_MULTIPLE_REGISTERS:
						break;

					default:
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
			mb.state = MODBUS_ST_SEND_EXCEPTION;
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

