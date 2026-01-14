#ifndef INC_MY_LIB_RINGBUF_H_
#define INC_MY_LIB_RINGBUF_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_hal.h"
#include <stdint.h>
#include <stdbool.h>

#define SIZE_BUF 128

typedef struct
{
	uint8_t buf[SIZE_BUF];
	volatile uint16_t head;
	volatile uint16_t tail;
} RingBuffer_t;

void RB_Init(RingBuffer_t *rb);

void RB_Push(RingBuffer_t *rb, uint8_t data);
void RB_Pop(RingBuffer_t *rb, uint8_t* data);
bool RB_Empty(RingBuffer_t *rb);
bool RB_Full(RingBuffer_t *rb);

#ifdef __cplusplus
}
#endif

#endif
