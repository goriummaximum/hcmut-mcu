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

#define PIN_C0 		GPIO_PIN_8
#define PIN_C1 		GPIO_PIN_9
#define PIN_C2 		GPIO_PIN_10
#define PIN_C3 		GPIO_PIN_11
#define PIN_C4 		GPIO_PIN_12
#define PIN_C5 		GPIO_PIN_13
#define PIN_C6 		GPIO_PIN_14
#define PIN_C7 		GPIO_PIN_15
#define PIN_R0 		GPIO_PIN_2
#define PIN_R1 		GPIO_PIN_3
#define PIN_R2 		GPIO_PIN_10
#define PIN_R3 		GPIO_PIN_11
#define PIN_R4 		GPIO_PIN_12
#define PIN_R5 		GPIO_PIN_13
#define PIN_R6 		GPIO_PIN_14
#define PIN_R7 		GPIO_PIN_15

#define GPIO_PORT_COL		GPIOB
#define GPIO_PORT_ROW		GPIOA

#define NUMBER_OF_ROWS		8
#define NUMBER_OF_COLS		8

#define NUMBER_OF_STATES	2

#define DRIVER_DELAY_INTERVAL_MS	5
#define DRIVER_DELAY_INTERVAL_US	2000 //take 2 * 8 = 16ms to finish one led scan cycle

#define NUMBER_OF_CLOCK_VALUES		12
#define DELAY_SEC_CLOCK_COUNT		2

//initialize buffer
void ledMatrixBuffer_Reset(void);

//buffer write a state (0 or 1) to a certain (row, col) of 2d array matrix
uint8_t ledMatrixBuffer_Write(uint8_t row, uint8_t col, uint8_t stateIdx);

//driver reset all pin
void ledMatrixDriver_Reset(void);

//driver drive the 2d array matrix buffer to led matrix 1 time,
//note: it take 40ms to finish 1 display
//(due to delaying for a small time to create the illusion)
void ledMatrixDriver_Drive(void);

/*specific functions*/
//clear buffer and turn off all the leds
void clearAllClock(void);

//turn on the led of the clock according to num.
//note: write to buffer
uint8_t setNumberOnClock(int num);

//turn off the led of the clock according to num.
//note: write to buffer
uint8_t clearNumberOnClock(int num);

//run the clock with sec, min, hour
//note: write to buffer
void runClock(void);

/*------------lab2-------------*/

//update led matrix with index
void updateLEDMatrix(void);

//cyclic shift value of buffer to the left n bit
uint8_t ledMatrixBuffer_cyclicShiftLeft(uint8_t n);

//cyclic shift value of buffer to the right n bit
uint8_t ledMatrixBuffer_cyclicShiftRight(uint8_t n);

//cyclic shift value of buffer up n bit
uint8_t ledMatrixBuffer_cyclicShiftUp(uint8_t n);

//cyclic shift value of buffer down n bit
uint8_t ledMatrixBuffer_cyclicShiftDown(uint8_t n);

#endif /* __LED_MATRIX_H */
