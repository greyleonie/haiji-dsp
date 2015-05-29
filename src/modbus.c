#include "modbus.h"

extern void Uart2TxStart(unsigned char c);
extern void timer4_reset(void);
extern void timer4_stop(void);

modbus mb;

int modbus_init(unsigned char adr)
{
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

void modbus_slave(void)
{
	switch (mb.state) {
		case MODBUS_ST_MAKE_RESPONSE:
			//check request
			if (1) {
				// make response packet
			

				mb.send_cnt = 0;
				//Uart2TxStart(modbus_send());
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
			mb.state = MODBUS_ST_SEND_DONE;
			break;
		
		case MODBUS_ST_SEND_DONE:
			mb.send_cnt = 0;
			mb.state = MODBUS_ST_RECV_IDLE;
			break;
	
		default:
			break;
	}// end switch
}

char modbus_send(void)
{
	char c = mb.response.data[mb.send_cnt];
	mb.send_cnt++;
	if (mb.send_cnt == mb.response.length)
		mb.state = MODBUS_ST_SEND_DONE;
	return c;
}

char modbus_is_send_done(void)
{
	return (mb.send_cnt == mb.response.length);
}

void modbus_reset(void)
{
	mb.state = MODBUS_ST_RECV_IDLE;
}