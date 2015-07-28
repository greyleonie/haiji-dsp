#ifndef MODBUS_H
#define MODBUS_H

/* Modbus function codes */
#define MODBUS_FC_READ_COILS                0x01
#define MODBUS_FC_READ_DISCRETE_INPUTS      0x02
#define MODBUS_FC_READ_HOLDING_REGISTERS    0x03
#define MODBUS_FC_READ_INPUT_REGISTERS      0x04
#define MODBUS_FC_WRITE_SINGLE_COIL         0x05
#define MODBUS_FC_WRITE_SINGLE_REGISTER     0x06
#define MODBUS_FC_READ_EXCEPTION_STATUS     0x07
#define MODBUS_FC_WRITE_MULTIPLE_COILS      0x0F
#define MODBUS_FC_WRITE_MULTIPLE_REGISTERS  0x10
#define MODBUS_FC_REPORT_SLAVE_ID           0x11
#define MODBUS_FC_MASK_WRITE_REGISTER       0x16
#define MODBUS_FC_WRITE_AND_READ_REGISTERS  0x17

#define MODBUS_BROADCAST_ADDRESS	0
#define MODBUS_MAX_NODE_ADDRESS		247

/* Consequently:
 * - RTU MODBUS ADU = 253 bytes + Server address (1 byte) + CRC (2 bytes) = 256
 *   bytes.
 * - TCP MODBUS ADU = 249 bytes + MBAP (7 bytes) = 256 bytes.
 * so the maximum of both backend in 260 bytes. This size can used to allocate
 * an array of bytes to store responses and it will be compatible with the two
 * backends.
 */
#define MODBUS_MAX_ADU_LENGTH	256

/* The size of the MODBUS PDU is limited by the size constraint inherited from
 * the first MODBUS implementation on Serial Line network (max. RS485 ADU = 256
 * bytes). Therefore, MODBUS PDU for serial line communication = 256 - Server
 * address (1 byte) - CRC (2 bytes) = 253 bytes.
 */
#define MODBUS_MAX_PDU_LENGTH	(MODBUS_MAX_ADU_LENGTH - 3)

/* Modbus_Application_Protocol_V1_1b.pdf (chapter 6 section 1 page 12)
 * Quantity of Coils to read (2 bytes): 1 to 2000 (0x7D0)
 * (chapter 6 section 11 page 29)
 * Quantity of Coils to write (2 bytes): 1 to 1968 (0x7B0)
 */
#define MODBUS_MAX_READ_BITS	2000
#define MODBUS_MAX_WRITE_BITS	1968

/* Modbus_Application_Protocol_V1_1b.pdf (chapter 6 section 3 page 15)
 * Quantity of Registers to read (2 bytes): 1 to 125 (0x7D)
 * (chapter 6 section 12 page 31)
 * Quantity of Registers to write (2 bytes) 1 to 123 (0x7B)
 * (chapter 6 section 17 page 38)
 * Quantity of Registers to write in R/W registers (2 bytes) 1 to 121 (0x79)
 */
#define MODBUS_MAX_READ_REGISTERS		125
#define MODBUS_MAX_WRITE_REGISTERS		123
#define MODBUS_MAX_WR_WRITE_REGISTERS	121
#define MODBUS_MAX_WR_READ_REGISTERS	125

/* Random number to avoid errno conflicts */
#define MODBUS_ENOBASE 112345678

/* Protocol exceptions */
enum {
	MODBUS_EXCEPTION_ILLEGAL_FUNCTION = 0x01,
	MODBUS_EXCEPTION_ILLEGAL_DATA_ADDRESS,
	MODBUS_EXCEPTION_ILLEGAL_DATA_VALUE,
	MODBUS_EXCEPTION_SLAVE_OR_SERVER_FAILURE,
	MODBUS_EXCEPTION_ACKNOWLEDGE,
	MODBUS_EXCEPTION_SLAVE_OR_SERVER_BUSY,
	MODBUS_EXCEPTION_NEGATIVE_ACKNOWLEDGE,
	MODBUS_EXCEPTION_MEMORY_PARITY,
	MODBUS_EXCEPTION_NOT_DEFINED,
	MODBUS_EXCEPTION_GATEWAY_PATH,
	MODBUS_EXCEPTION_GATEWAY_TARGET,
	MODBUS_EXCEPTION_MAX
};


/* define modbus protocol request struct */
typedef struct _modbus_request {
	unsigned char adr;
	unsigned char function;
	union {
		struct {
			unsigned short address;
			unsigned short count;
		} read_single;	//01,02,03,04

		struct {
			unsigned short address;
			unsigned short value;
		} write_single; //05,06

		struct {
			unsigned short address;
			unsigned short count;
			unsigned char count_of_byte;
			unsigned char data[MODBUS_MAX_PDU_LENGTH - 6];
		} write_multiple; // 15,16

		struct {
			unsigned short address;
			unsigned short add_mask;
			unsigned short or_mask;
		} mask_write; //22

		struct {
			unsigned short read_address;
			unsigned short read_count;
			unsigned short write_address;
			unsigned short write_count;
			unsigned char write_count_of_byte;
			unsigned char data[MODBUS_MAX_PDU_LENGTH - 11];
		} read_write_registers; //23

		struct {
			unsigned char emi_type;
			unsigned char read_dev_id;
			unsigned char object_id;
		} read_dev_code; //43
		
	} data;
	unsigned short crc;
	
} modbus_request;

/* define modbus response struct */
typedef struct _modbus_response {
	unsigned char data[MODBUS_MAX_ADU_LENGTH];
	unsigned short length;
} modbus_response;

/* define modbus driver struct */
typedef struct _modbus {
	unsigned char adr;
	
	enum {
		MODBUS_ST_RECV_IDLE,
		MODBUS_ST_RECV_ADR,
		MODBUS_ST_RECV_FUNCTION,
		MODBUS_ST_RECV_DATA,
		MODBUS_ST_RECV_CRC,
		MODBUS_ST_MAKE_RESPONSE,
		MODBUS_ST_SEND_RESPONSE,
		MODBUS_ST_EXCEPTION,
		MODBUS_ST_MAKE_EXCEPTION,
		MODBUS_ST_SEND_EXCEPTION,
		MODBUS_ST_SEND_DONE
	} state;

	modbus_request 	request;
	modbus_response	response;

	unsigned short recv_cnt;
	unsigned short send_cnt;

	unsigned short crc;

} modbus;

/* define functions */
extern int modbus_init(unsigned char adr);
extern void modbus_receive(unsigned char c);
extern void modbus_slave(void);
extern char modbus_is_send_done(void);
extern char modbus_send(void);
extern void modbus_reset(void);


#define HIGH	1
#define	LOW		0


#endif
