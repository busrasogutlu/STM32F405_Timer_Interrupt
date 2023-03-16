
#include "stm32f4xx.h"

#include "CK_SYSTEM.h"
#include "CK_TIME_HAL.h"
#include "CK_GPIO.h"

#include "CK_LED.h"

int main(void)
{
	CK_SYSTEM_SetSystemClock(SYSTEM_CLK_180MHz);

	HAL_Init();

	// I copied from flight controller. Later set pins and timers for stm32f429 board
	// GPIO G13, G14 are used.
	CK_GPIOx_ClockEnable(GPIOG);
	CK_GPIOx_Init(GPIOG, 14, CK_GPIO_INPUT, CK_GPIO_NOAF, CK_GPIO_PUSHPULL, CK_GPIO_VERYHIGH, CK_GPIO_NOPUPD);

	/*
	CK_LED_Init();

	CK_LED_ChangeFrequency(10);
	CK_LED_SetDutyCycle(5);
	CK_TIME_DelayMicroSec(100);
	*/
	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOG_CLK_ENABLE();

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	GPIO_InitStruct.Pin = GPIO_PIN_13 | GPIO_PIN_14;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

	while(1){

		HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_13);
		HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_14);
		CK_TIME_DelayMilliSec(100);


	}

}
