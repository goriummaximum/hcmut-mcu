/**
  ******************************************************************************
  * @file           : sqr_wave_generator.h
  * @brief          : square wave generator using HAL_Delay
  ******************************************************************************
  *
  ******************************************************************************
  */
#ifndef __SQR_WAVE_GENRATOR_H
#define __SQR_WAVE_GENRATOR_H

#define OUTPUT_PIN		GPIO_PIN_5
#define GPIO_PORT		GPIOA

#define OUT_FREQUENCY	1000 //Hz

//driver to generate the square wave
void sqrWaveGeneratorDriver_drive(void);

#endif
