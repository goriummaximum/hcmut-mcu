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

static uint16_t timerCounter = 0;

void sqrWaveGenerator_setup(void) {
	HAL_TIM_Base_Start(&htim3);
	timerCounter = __HAL_TIM_GET_COUNTER(&htim3);
}

void sqrWaveGeneratorDriver_drive(void) {
	while (1) {
		if (__HAL_TIM_GET_COUNTER(&htim3) - timerCounter > COUNTER_ELAPSED_VAL) {
			HAL_GPIO_TogglePin(GPIO_PORT, OUTPUT_PIN);
			timerCounter = __HAL_TIM_GET_COUNTER(&htim3);
		}
	}
}
