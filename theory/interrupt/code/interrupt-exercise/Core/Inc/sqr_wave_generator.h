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

#define GPIO_PORT				GPIOA
#define	SELECT_ALL_PINS			0xff

//setup
void sqrWaveGenerator_setup(void);

//driver to generate the square wave
void sqrWaveGeneratorDriver_drive(void);

//callback function
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif
