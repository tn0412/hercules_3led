#ifndef LED_CTRL_H
#define LED_CTRL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include <stdint.h>

typedef enum
{
	LED_CH_NONE = 0,
	LED_CH1,
	LED_CH2,
	LED_CH3,
	LED_CH4,
} ChannelTimer;

typedef struct
{
	UART_HandleTypeDef *huart;
	TIM_HandleTypeDef *htim;

	uint32_t tim_ch[5];
	ChannelTimer currentCh;

	uint8_t rx;
	char rxBuf[32];
	uint8_t rxIndex;
} Led_Ctrl;

void LedCtrl_Init(Led_Ctrl *lc, UART_HandleTypeDef *huart, TIM_HandleTypeDef *htim);
void LedCtrl_ChooseChannel(Led_Ctrl *lc, uint8_t ch);
void LedCtrl_Value(Led_Ctrl *lc, uint8_t digit);
void LedCtrl_Final(Led_Ctrl *lc);
void LedCtrl_UartRxCpltCallback(Led_Ctrl *lc, UART_HandleTypeDef *huart);

#ifdef __cplusplus
}
#endif

#endif
