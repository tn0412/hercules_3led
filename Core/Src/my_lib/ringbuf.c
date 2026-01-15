#include "my_lib/ringbuf.h"

// Phù hợp stream byte liên tục

void RB_Init(RingBuffer_t *rb)
{
	rb->head = 0;
	rb->tail = 0;
	for(uint16_t i = 0; i < sizeof(rb->buf); i++)
		rb->buf[i] = 0;
}

bool RB_Empty(RingBuffer_t *rb)
{
	return(rb->head == rb->tail);
}

bool RB_Full(RingBuffer_t *rb)
{
	uint16_t next = rb->head + 1;
	if(next == sizeof(rb->buf)) next = 0;
	return(next == rb->tail);
}

void RB_Push(RingBuffer_t *rb, uint8_t data)
{
	if(RB_Full(rb)) return;
	rb->buf[rb->head] = data;
	rb->head++;
	if(rb->head == sizeof(rb->buf)) rb->head = 0;
}

void RB_Pop(RingBuffer_t *rb, uint8_t* data)
{
	if(RB_Empty(rb)) return;
	*data = rb->buf[rb->tail];
	rb->tail++;
	if(rb->tail == sizeof(rb->buf)) rb->tail = 0;
}
