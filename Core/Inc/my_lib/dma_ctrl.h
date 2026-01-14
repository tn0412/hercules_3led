#pragma once

#ifndef INC_MY_LIB_DMA_CTRL_H_
#define INC_MY_LIB_DMA_CTRL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_hal.h"
#include <stdint.h>

#include "my_lib/ringbuf.h"

#define DMA_RX_SIZE 256

//extern uint16_t last_pos;
//extern uint8_t dma_rx_buf[DMA_RX_SIZE];

void DMA_Init(UART_HandleTypeDef *huart);
void DMA_Ctrl(UART_HandleTypeDef *huart, RingBuffer_t *rb);
void DMA_RX(uint16_t i_first, uint16_t i_last, RingBuffer_t *rb);

#ifdef __cplusplus
}
#endif

#endif
