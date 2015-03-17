#include <stdlib.h>
#include "RingBuffer.h"

extern void RingBufferInit(RingBuffer &buf, unsigned int size)
{
	if (size == 0)
		return;
	
	buf.pBuf = (WORD *)malloc(sizeof(WORD) * size);
	buf.size = size;
	buf.head = 0;
	buf.tail = 0;
}

extern void RingBufferFree(RingBuffer &buf)
{
	free(buf.pBuf);
}

extern WORD RingBufferGet(RingBuffer &buf)
{
	WORD c = buf.pBuf[buf.head];
	buf.head = (buf.head + 1) % buf.size;
	return c;
}

extern void RingBufferPut(RingBuffer &buf, WORD c)
{
	buf.pBuf[buf.tail] = c;
	buf.tail = (buf.tail + 1) % buf.size;
}

extern char IsRingBufferEmpty(RingBuffer &buf)
{
	return (buf.tail == buf.head);
}

extern char IsRingBufferFull(RingBuffer &buf)
{
	return ((buf.tail + 1) % buf.size == buf.head);
}