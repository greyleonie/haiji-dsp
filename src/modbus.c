#include <stdlib.h>

#include "modbus.h"

extern modbus mb;

void modbus_init(unsigned char id)
{
	mb.modbus_id = id;
	mb.modbus_state = MODBUS_STATE_RECV_ADR;
	mb.head = mb.tail = (struct _modbus_request *)malloc(sizeof(struct _modbus_request));
	mb.head->data = null;
	mb.head->next = null;
	mb.head->resp = null;
}

void modbus_receive(unsigned char c)
{
	switch(mb.modbus_state) {
		case MODBUS_STATE_RECV_ADR:
			mb.head->adr = c;
			mb.modbus_state = MODBUS_STATE_RECV_FUNCTION;
			break;

		case MODBUS_STATE_RECV_FUNCTION:
			mb.head->function = c;
			mb.modbus_state = MODBUS_STATE_RECV_ADDRESS_HIGH;
			break;

		case MODBUS_STATE_RECV_ADDRESS_HIGH:
			((unsigned char *)&mb.head->address)[HIGH] = c;
			mb.modbus_state = MODBUS_STATE_RECV_ADDRESS_LOW;
			break;

		case MODBUS_STATE_RECV_ADDRESS_LOW:
			((unsigned char *)&mb.head->address)[LOW] = c;
			mb.modbus_state = MODBUS_STATE_RECV_LENGTH_HIGH;
			break;

		case MODBUS_STATE_RECV_LENGTH_HIGH:
			((unsigned char *)&mb.head->length)[HIGH] = c;
			mb.modbus_state = MODBUS_STATE_RECV_LENGTH_LOW;
			break;
			
		case MODBUS_STATE_RECV_LENGTH_LOW:
			((unsigned char *)&mb.head->length)[LOW] = c;

			if (mb.head->function == MODBUS_FC_WRITE_SINGLE_COIL
			|| mb.head->function == MODBUS_FC_WRITE_SINGLE_REGISTER
			|| mb.head->function == MODBUS_FC_WRITE_MULTIPLE_COILS
			|| mb.head->function == MODBUS_FC_WRITE_MULTIPLE_REGISTERS
			|| mb.head->function == MODBUS_FC_MASK_WRITE_REGISTER
			|| mb.head->function == MODBUS_FC_WRITE_AND_READ_REGISTERS) {
				mb.head->data = (unsigned char *)malloc(sizeof(unsigned char) * mb.head->length);
				mb.recv_cnt = 0;
				mb.modbus_state = MODBUS_STATE_RECV_DATA;
			}
			else {
				mb.modbus_state = MODBUS_STATE_RECV_CRC_HIGH;
			}

			break;

		case MODBUS_STATE_RECV_DATA:
			mb.head->data[mb.recv_cnt] = c;
			mb.recv_cnt++;
			if (mb.recv_cnt == mb.head->length) {
				mb.recv_cnt = 0;
				mb.modbus_state = MODBUS_STATE_RECV_CRC_HIGH;
			}
			break;
			
		case MODBUS_STATE_RECV_CRC_HIGH:
			((unsigned char *)&mb.head->crc)[HIGH] = c;
			mb.modbus_state = MODBUS_STATE_RECV_CRC_LOW;
			break;
			
		case MODBUS_STATE_RECV_CRC_LOW:
			((unsigned char *)&mb.head->crc)[LOW] = c;
			//mb.tail = (struct _modbus_request *)malloc(sizeof(struct _modbus_request));
			//mb.head->next = mb.tail;
			mb.modbus_state = MODBUS_STATE_MAKE_RESPONSE;
			break;

		default:
			break;
	}// end switch
}

void modbus_slave(void)
{
	switch (mb.modbus_state) {
		case MODBUS_STATA_CHECK_REQUEST:
			if (mb.head->adr != mb.modbus_adr) {
				if (mb.head->data != null)
					free(mb.head->data);
				struct _modbus_request *t = mb.head;
				mb.head = mb.head->next;
				free(t);	
			}
			else if () {
			}
			else {
			}
			break;

		case MODBUS_STATE_MAKE_RESPONSE:
			if (mb.head->adr != mb.modbus_adr) {
			}
			break;

		case MODBUS_STATE_SEND_RESPONSE_DONE:
			free(mb.head->resp->data);
			free(mb.head->resp);
			free(mb.head->data);
			struct _modbus_resquest *t = mb.head;
			mb.head = mb.head->next;
			free(t);

			mb.modbus_state = MODBUS_STATE_RECV_ADR;
			break;
		case MODBUS_STATE_SEND_RESPONSE:
			
			break;

		default:
			break;
	}// end switch
}

char modbus_send(void)
{
	char c = mb.head->resp->data[mb.send_cnt];
	mb.send_cnt++;
	if (mb.send_cnt == mb.head->resp->length)
		mb.modbus_state = MODBUS_STATE_SEND_RESPONSE_DONE;
	return c;
}

char modbus_is_send_done(void)
{
	return (mb.send_cnt == mb.head->resp->length);
}
