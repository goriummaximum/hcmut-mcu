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

static uint16_t pin1Counter = 0;

void sqrWaveGenerator_setup(void) {
	HAL_TIM_Base_Start_IT(&htim3);

}

void sqrWaveGeneratorDriver_drive(void) {

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim == &htim3) {
		HAL_GPIO_TogglePin(GPIO_PORT, OUTPUT_PIN_2);

		pin1Counter++;
		if (pin1Counter == 10) {
			HAL_GPIO_TogglePin(GPIO_PORT, OUTPUT_PIN_1);
			pin1Counter = 0;
		}
	}
}
