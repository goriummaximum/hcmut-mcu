/**
  ******************************************************************************
  * @file           : sqr_wave_generator.c
  * @brief          : square wave generator using timer3 interrupt
  ******************************************************************************
  *
  ******************************************************************************
  */
#include "main.h"
#include "sqr_wave_generator.h"

static uint8_t counter = 0x0;

void sqrWaveGenerator_setup(void) {
	HAL_TIM_Base_Start_IT(&htim3);

}

void sqrWaveGeneratorDriver_drive(void) {

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim == &htim3) {
		HAL_GPIO_WritePin(GPIO_PORT, SELECT_ALL_PINS, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIO_PORT, counter++, GPIO_PIN_SET);

		if (counter == 0xff) {
			counter = 0x0;
		}
	}
}
