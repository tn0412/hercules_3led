#include <my_lib/dma_circular.h>

static uint8_t  dma_rx_buf[DMA_RX_SIZE];
static uint16_t last_pos = 0;

void DMA_Init(UART_HandleTypeDef *huart)
{
	HAL_UART_Receive_DMA(huart, dma_rx_buf, DMA_RX_SIZE);
	__HAL_DMA_DISABLE_IT(huart->hdmarx, DMA_IT_HT);
	last_pos = 0;
}

// DMA circular
void DMA_Ctrl(UART_HandleTypeDef *huart, RingBuffer_t *rb)
{
	uint16_t pos = DMA_RX_SIZE - __HAL_DMA_GET_COUNTER(huart->hdmarx);
	if(pos != last_pos)
	{
		if(pos > last_pos)
		{
			DMA_RX(last_pos, pos, rb);
		}
		else
		{
			DMA_RX(last_pos, DMA_RX_SIZE, rb);
			DMA_RX(0, pos, rb);
		}
		last_pos = pos;
	}
}

void DMA_RX(uint16_t i_first, uint16_t i_last, RingBuffer_t *rb)
{
	for(uint16_t i = i_first; i < i_last; i++)
	{
		uint8_t b = dma_rx_buf[i];
		RB_Push(rb, b);
	}
}
