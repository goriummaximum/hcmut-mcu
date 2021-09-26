/**
  ******************************************************************************
  * @file           : sqr_wave_generator.c
  * @brief          : square wave generator using HAL_Delay
  ******************************************************************************
  *
  ******************************************************************************
  */
#include "main.h"
#include "sqr_wave_generator.h"

void sqrWaveGeneratorDriver_drive(void) {
	while (1) {
		HAL_Delay(5);
		HAL_GPIO_TogglePin(GPIO_PORT, OUTPUT_PIN);
	}
}
