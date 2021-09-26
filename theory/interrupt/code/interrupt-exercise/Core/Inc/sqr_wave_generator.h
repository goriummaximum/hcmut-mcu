/**
  ******************************************************************************
  * @file           : sqr_wave_generator.h
  * @brief          : square wave generator using timer3 interrupt
  ******************************************************************************
  *
  ******************************************************************************
  */
#ifndef __SQR_WAVE_GENRATOR_H
#define __SQR_WAVE_GENRATOR_H

#define OUTPUT_PIN_1		GPIO_PIN_1
#define OUTPUT_PIN_2		GPIO_PIN_7
#define GPIO_PORT			GPIOA

#define COUNTER_ELAPSED_VAL_PIN_1		10

//setup
void sqrWaveGenerator_setup(void);

//driver to generate the square wave
void sqrWaveGeneratorDriver_drive(void);

//callback function
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif
