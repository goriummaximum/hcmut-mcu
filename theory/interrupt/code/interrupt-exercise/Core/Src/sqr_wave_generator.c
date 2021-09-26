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

static uint16_t timerCounter1 = 0;
static uint16_t timerCounter2 = 0;

void sqrWaveGenerator_setup(void) {
	HAL_TIM_Base_Start(&htim3);
	timerCounter1 = __HAL_TIM_GET_COUNTER(&htim3);
	timerCounter2 = __HAL_TIM_GET_COUNTER(&htim3);
}

void sqrWaveGeneratorDriver_drive(void) {
	while (1) {
		if (__HAL_TIM_GET_COUNTER(&htim3) - timerCounter1 > COUNTER_ELAPSED_VAL_PIN_1) {
			HAL_GPIO_TogglePin(GPIO_PORT, OUTPUT_PIN_1);
			timerCounter1 = __HAL_TIM_GET_COUNTER(&htim3);
		}

		if (__HAL_TIM_GET_COUNTER(&htim3) - timerCounter2 > COUNTER_ELAPSED_VAL_PIN_2) {
			HAL_GPIO_TogglePin(GPIO_PORT, OUTPUT_PIN_2);
			timerCounter2 = __HAL_TIM_GET_COUNTER(&htim3);
		}
	}
}
