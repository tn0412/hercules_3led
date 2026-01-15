#include "my_lib/dma_idle.h"

static uint8_t dma_rx_buf[DMA_RX_SIZE];

void DMA_IDLE_Init(UART_HandleTypeDef *huart)
{
	HAL_UART_Receive_DMA(huart, dma_rx_buf, DMA_RX_SIZE);
	__HAL_UART_ENABLE_IT(huart, UART_IT_IDLE);
}

void UART_DMAIdle_Callback(UART_HandleTypeDef *huart, Led_Ctrl *ledCtrl)
{
	uint16_t rx_len;

	HAL_UART_DMAStop(huart);

	rx_len = DMA_RX_SIZE - __HAL_DMA_GET_COUNTER(huart->hdmarx);
	if(rx_len > 0)
	{
		for(uint16_t i = 0; i < rx_len; i++)
		{
			LedCtrl_FeedByte(&ledCtrl, dma_rx_buf[i]);
		}
	}

	memset(dma_rx_buf, 0, DMA_RX_SIZE);

	HAL_UART_Receive_DMA(huart, dma_rx_buf, DMA_RX_SIZE);
}
