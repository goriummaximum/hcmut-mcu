/**
  ******************************************************************************
  * @file           : 1darray_led.h
  * @brief          : Header for 1darray_led.c file.
  *                   This file contains the buffer-driver define for controlling 1D array LED
  *                   respect to a certain GPIO Port.
  *
  *                   Created on:	Sep 12th, 2021
  *                   Author:		Thien Long
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#ifndef __1DARRAY_LED_H
#define __1DARRAY_LED_H

#define NUMBER_OF_LEDS		3
#define NUMBER_OF_VALUES	2

#define GPIO_PORT 			GPIOA
#define LR_PIN				GPIO_PIN_1
#define LA_PIN				GPIO_PIN_2
#define LG_PIN				GPIO_PIN_3

//buffer extract each bit of value corresponding to each position of buffer
uint8_t ledArrayBuffer_Write(uint8_t value);

//driver encode value to SET or RESET, write value to each led
void ledArrayDriver_Drive(void);

//display led array
void displayLedArray(uint8_t value);

#endif /* __1DARRAY_LED_H */