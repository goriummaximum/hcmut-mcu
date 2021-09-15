/**
  ******************************************************************************
  * @file           : led_matrix.c
  * @brief          :
  *                   This file contains the buffer-driver implement for controlling
  *                    1D array LED.
  *
  *                   Created on:	Sep 15th, 2021
  *                   Author:		Thien Long
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#include "main.h"
#include "led_matrix.h"

//store the state of led matrix
static uint8_t ledMatrixBuffer[NUMBER_OF_ROWS][NUMBER_OF_COLS];

static uint16_t ledMatrixRowPins[NUMBER_OF_ROWS] = {
		PIN_R0,
		PIN_R1,
		PIN_R2,
		PIN_R3,
		PIN_R4,
		PIN_R5,
		PIN_R6,
		PIN_R7
};

static uint16_t ledMatrixColPins[NUMBER_OF_COLS] = {
		PIN_C0,
		PIN_C1,
		PIN_C2,
		PIN_C3,
		PIN_C4,
		PIN_C5,
		PIN_C6,
		PIN_C7
};

static GPIO_PinState ledMatrixRowStates[NUMBER_OF_STATES] = {
		GPIO_PIN_SET,
		GPIO_PIN_RESET
}; //idx 0 - SET, idx 1 - RESET

static GPIO_PinState ledMatrixColStates[NUMBER_OF_STATES] = {
		GPIO_PIN_RESET,
		GPIO_PIN_SET
}; //idx 0 - RESET, idx 1 - SET

void ledMatrixBuffer_Reset(void) {
	for (uint8_t row = 1; row < NUMBER_OF_ROWS; row++) {
		for (uint8_t col = 0; col < NUMBER_OF_COLS; col++) {
			ledMatrixBuffer[row][col] = 0x00;
		}
	}
}

uint8_t ledMatrixBuffer_Write(uint8_t row, uint8_t col, uint8_t stateIdx) {
	if (row >= NUMBER_OF_ROWS) {
		return 0;
	}

	if (col >= NUMBER_OF_COLS) {
		return 0;
	}

	if (stateIdx >= NUMBER_OF_STATES) {
		return 0;
	}

	ledMatrixBuffer[row][col] = stateIdx;
	return 1;
}

void ledMatrixDriver_Drive(void) {
	for (uint8_t row = 0; row < NUMBER_OF_ROWS; row++) {
		//select row pin
		HAL_GPIO_WritePin(GPIO_PORT, ledMatrixRowPins[row], ledMatrixRowStates[1]); //on row
		for (uint8_t col = 0; col < NUMBER_OF_COLS; col++) {
			//select col pin
			HAL_GPIO_WritePin(GPIO_PORT, ledMatrixColPins[col], ledMatrixColStates[ledMatrixBuffer[row][col]]); //on col
		}

		HAL_Delay(5);

		for (uint8_t col = 0; col < NUMBER_OF_COLS; col++) {
			HAL_GPIO_WritePin(GPIO_PORT, ledMatrixColPins[col], ledMatrixColStates[0]); //off col
		}
		HAL_GPIO_WritePin(GPIO_PORT, ledMatrixRowPins[row], ledMatrixRowStates[0]); //off row
	}
}
