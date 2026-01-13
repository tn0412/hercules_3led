#include "my_lib/led_ctrl.h"
#include <stdlib.h>

void LedCtrl_Init(Led_Ctrl *lc, UART_HandleTypeDef *huart, TIM_HandleTypeDef *htim)
{
	if(!lc) return;
	lc->huart = huart;
	lc->htim = htim;

	lc->tim_ch[LED_CH1] = TIM_CHANNEL_1;
	lc->tim_ch[LED_CH2] = TIM_CHANNEL_2;
	lc->tim_ch[LED_CH3] = TIM_CHANNEL_3;
	lc->tim_ch[LED_CH4] = TIM_CHANNEL_4;

	lc->currentCh = LED_CH_NONE;
	lc->rx = 0;
	lc->rxIndex = 0;

	for(int i = 0; i < sizeof(lc->rxBuf); i++)
		lc->rxBuf[i] = 0;
}

void LedCtrl_ChooseChannel(Led_Ctrl *lc, uint8_t ch)
{
	if(!lc) return;
	if(ch == 'A') lc->currentCh = LED_CH2;
	else if(ch == 'B') lc->currentCh = LED_CH3;
	else if(ch == 'C') lc->currentCh = LED_CH4;
	else lc->currentCh = LED_CH_NONE;

	lc->rxIndex = 0;
}

void LedCtrl_Value(Led_Ctrl *lc, uint8_t digit)
{
	if(!lc) return;
	if(digit >= '0' && digit <= '9')
	{
		if(lc->rxIndex < sizeof(lc->rxBuf) - 1)
			lc->rxBuf[lc->rxIndex++] = (char)digit;
	}
}

void LedCtrl_Final(Led_Ctrl *lc)
{
	if(!lc || !lc->htim) return;
	if(lc->rxIndex > 0)
	{
		if(lc->currentCh == LED_CH_NONE)
		{
			lc->rxIndex = 0;
			return;
		}
		lc->rxBuf[lc->rxIndex] = 0;
		int led_value = atoi(lc->rxBuf);

		if(led_value < 0) led_value = 0;
		if(led_value > 255) led_value = 255;
		uint32_t tim_channel = lc->tim_ch[lc->currentCh];
		__HAL_TIM_SET_COMPARE(lc->htim, tim_channel, led_value);
		lc->currentCh = LED_CH_NONE;
		lc->rxIndex = 0;
	}
}

void LedCtrl_UartRxCpltCallback(Led_Ctrl *lc, UART_HandleTypeDef *huart)
{
	if(!lc || !lc->huart) return;
	if(huart->Instance != lc->huart->Instance) return;

	uint8_t ch = lc->rx;

	if(ch == 'A' || ch =='B' || ch == 'C')
		LedCtrl_ChooseChannel(lc, ch);
	else if(ch == ' ' || ch == '\r' || ch == '\n')
		LedCtrl_Final(lc);
	else if(ch >= '0' && ch <= '9')
		LedCtrl_Value(lc, ch);
	HAL_UART_Receive_IT(lc->huart, &lc->rx, 1); // quay lại nhận tiếp
}
