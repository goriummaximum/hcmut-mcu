/**
  ******************************************************************************
  * @file           : led_matrix.h
  * @brief          : Header for led_matrix.c file.
  *                   This file contains the buffer-driver define for controlling
  *                    a 8x8 led matrix.
  *
  *                   Created on:	Sep 15th, 2021
  *                   Author:		Thien Long
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#ifndef __LED_MATRIX_H
#define __LED_MATRIX_H

#define PIN_R0 		GPIO_PIN_0
#define PIN_R1 		GPIO_PIN_1
#define PIN_R2 		GPIO_PIN_2
#define PIN_R3 		GPIO_PIN_3
#define PIN_R4 		GPIO_PIN_4
#define PIN_R5 		GPIO_PIN_5
#define PIN_R6 		GPIO_PIN_6
#define PIN_R7 		GPIO_PIN_7
#define PIN_C0 		GPIO_PIN_8
#define PIN_C1 		GPIO_PIN_9
#define PIN_C2 		GPIO_PIN_10
#define PIN_C3 		GPIO_PIN_11
#define PIN_C4 		GPIO_PIN_12
#define PIN_C5 		GPIO_PIN_13
#define PIN_C6 		GPIO_PIN_14
#define PIN_C7 		GPIO_PIN_15

#define GPIO_PORT		GPIOB

#define NUMBER_OF_ROWS		8
#define NUMBER_OF_COLS		8

#define NUMBER_OF_STATES	2

#define DRIVER_DELAY_INTERVAL_MS	5

//initialize buffer
void ledMatrixBuffer_Reset(void);

//buffer write a state (0 or 1) to a certain (row, col) of 2d array matrix
uint8_t ledMatrixBuffer_Write(uint8_t row, uint8_t col, uint8_t stateIdx);

//driver reset all pin
void ledMatrixDriver_Reset(void);

//driver drive the 2d array matrix buffer to led matrix 1 time,
//note: it take 40ms to finish 1 display
//(due to delaying for a small time to create the illusion)
void ledMatrixDriver_Drive();

//specific functions


#endif /* __LED_MATRIX_H */
