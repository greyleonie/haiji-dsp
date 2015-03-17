#ifndef RING_BUFFER_H
#define RING_BUFFER_H

typedef unsigned int WORD;

typedef struct _RingBuffer{
	WORD *pBuf;			// buffer memory pointer
	unsigned int size;	// buffer size
	unsigned int head;	// buffer head pointer
	unsigned int tail;	// buffer current pointer
}RingBuffer;

extern void RingBufferInit(RingBuffer &buf, unsigned int size);
extern void RingBufferFree(RingBuffer &buf);
extern WORD RingBufferGet(RingBuffer &buf);
extern void RingBufferPut(RingBuffer &buf, WORD c);
extern char IsRingBufferEmpty(RingBuffer &buf);
extern char IsRingBufferFull(RingBuffer &buf);


#endif