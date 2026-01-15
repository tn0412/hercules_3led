#pragma once

#ifndef INC_MY_LIB_DMA_IDLE_H_
#define INC_MY_LIB_DMA_IDLE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_hal.h"
#include <stdint.h>

#include "my_lib/led_ctrl.h"
#include "string.h"

#define DMA_RX_SIZE 256

void DMA_IDLE_Init(UART_HandleTypeDef *huart);
void UART_DMAIdle_Callback(UART_HandleTypeDef *huart, Led_Ctrl *ledCtrl);

#ifdef __cplusplus
}
#endif

#endif /* INC_MY_LIB_DMA_IDLE_H_ */
