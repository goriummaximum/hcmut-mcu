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

#include <software_timer1.h>
#include "main.h"
#include "led_matrix.h"

//store the state of led matrix
static uint8_t ledMatrixBuffer[NUMBER_OF_ROWS] = {0x00,0x38,0x44,0x44,0x44,0x7c,0x44,0x44};

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
		GPIO_PIN_SET,
		GPIO_PIN_RESET
}; //idx 0 - RESET, idx 1 - SET

//mapping clock value 0-NUMBER_OF_CLOCK_VALUES to row, col of buffer
static uint8_t ledMatrixBufferClockConversion[NUMBER_OF_CLOCK_VALUES][2] = {
		{0, 2}, {0, 3}, {1, 4}, {2, 4}, {3, 4}, {4, 3}, {4, 2}, {4, 1}, {3, 0}, {2, 0}, {1, 0}, {0, 1}
};

/*------------lab2-------------*/
static int ledMatrixIdx = 0;

void ledMatrixBuffer_Reset(void) {
	for (uint8_t row = 1; row < NUMBER_OF_ROWS; row++) {
		ledMatrixBuffer[row] = 0x00;
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

	ledMatrixBuffer[row] &= ~(0x01 << col);
	ledMatrixBuffer[row] |= (stateIdx << col);
	return 1;
}

void ledMatrixDriver_Reset(void) {
	  HAL_GPIO_WritePin(GPIO_PORT_ROW, PIN_R0|PIN_R1|PIN_R2|PIN_R3
	                          |PIN_R4|PIN_R5|PIN_R6|PIN_R7,ledMatrixRowStates[0]);

	  HAL_GPIO_WritePin(GPIO_PORT_COL, PIN_C0|PIN_C1|PIN_C2|PIN_C3
              	  	  	  	  |PIN_C4|PIN_C5|PIN_C6|PIN_C7, ledMatrixColStates[0]);
}

void ledMatrixDriver_Drive(void) {
	for (uint8_t row = 0; row < NUMBER_OF_ROWS; row++) {
		ledMatrixDriver_Reset();
		HAL_GPIO_WritePin(GPIO_PORT_ROW, ledMatrixRowPins[row], ledMatrixRowStates[1]); //on row
		HAL_GPIO_WritePin(GPIO_PORT_COL, ledMatrixBuffer[row] << 0x08, ledMatrixColStates[1]); //on col
		//HAL_Delay(DRIVER_DELAY_INTERVAL_MS);

		while (get_timer1_flag_value()) {
			setTimer1(DRIVER_DELAY_INTERVAL_US);
		}
	}
}

void clearAllClock(void) {
	ledMatrixBuffer_Reset();
	ledMatrixDriver_Reset();
}

uint8_t setNumberOnClock(int num) {
	if (num < 0 || num >= NUMBER_OF_CLOCK_VALUES) {
		return 0;
	}

	uint8_t row = ledMatrixBufferClockConversion[num][0];
	uint8_t col = ledMatrixBufferClockConversion[num][1];

	if (!ledMatrixBuffer_Write(row, col, 1)) {
		return 0;
	}

	return 1;
}

uint8_t clearNumberOnClock(int num) {
	if (num < 0 || num >= NUMBER_OF_CLOCK_VALUES) {
		return 0;
	}

	uint8_t row = ledMatrixBufferClockConversion[num][0];
	uint8_t col = ledMatrixBufferClockConversion[num][1];

	if (!ledMatrixBuffer_Write(row, col, 0)) {
		return 0;
	}

	return 1;
}

void runClock(void) {
	for (uint8_t hour = 0; hour < NUMBER_OF_CLOCK_VALUES; hour++) {
		if (!setNumberOnClock(hour)) {
			return;
		}

		for (uint8_t min = 0; min < NUMBER_OF_CLOCK_VALUES; min++) {
			if (min != hour) {
				if (!setNumberOnClock(min)) {
						return;
					}

					for (uint8_t sec = 0; sec < NUMBER_OF_CLOCK_VALUES; sec++) {
						if (sec != hour && sec != min) {
							if (!setNumberOnClock(sec)) {
									return;
							}

							for (uint8_t delayCount = 0; delayCount < DELAY_SEC_CLOCK_COUNT; delayCount++) {
									ledMatrixDriver_Drive();
							}

							if (!clearNumberOnClock(sec)) {
								return;
							}
						}
					}
				if (!clearNumberOnClock(min)) {
					return;
				}
			}
		}
		if (!clearNumberOnClock(hour)) {
			return;
		}
	}
}

/*------------lab2-------------*/
void updateLEDMatrix(void) {
	ledMatrixDriver_Reset();

	HAL_GPIO_WritePin(GPIO_PORT_ROW, ledMatrixRowPins[ledMatrixIdx], ledMatrixRowStates[1]); //on row
	HAL_GPIO_WritePin(GPIO_PORT_COL, ledMatrixBuffer[ledMatrixIdx] << 0x08, ledMatrixColStates[1]); //on col

	ledMatrixIdx++;

	if (ledMatrixIdx == NUMBER_OF_ROWS) {
		ledMatrixIdx = 0;
	}
}


uint8_t ledMatrixBuffer_cyclicShiftLeft(uint8_t n) {
	if (n <= 0 || n > NUMBER_OF_COLS) {
		return 0;
	}

	for (uint8_t row = 0; row < NUMBER_OF_ROWS; row++) {
		ledMatrixBuffer[row] = (ledMatrixBuffer[row] >> n) | (ledMatrixBuffer[row] << (NUMBER_OF_COLS - n));
	}

	return 1;
}

uint8_t ledMatrixBuffer_cyclicShiftRight(uint8_t n) {
	if (n <= 0 || n > NUMBER_OF_COLS) {
		return 0;
	}

	for (uint8_t row = 0; row < NUMBER_OF_ROWS; row++) {
		ledMatrixBuffer[row] = (ledMatrixBuffer[row] << n) | (ledMatrixBuffer[row] >> (NUMBER_OF_COLS - n));
	}

	return 1;
}

uint8_t ledMatrixBuffer_cyclicShiftUp(uint8_t n) {
	if (n <= 0 || n > NUMBER_OF_ROWS) {
		return 0;
	}

	uint8_t bufferTemp[NUMBER_OF_ROWS];

	for (uint8_t row = 0; row < NUMBER_OF_ROWS; row++) {
		bufferTemp[row] = ledMatrixBuffer[row];
	}

	for (uint8_t row = 0; row < NUMBER_OF_ROWS; row++) {
		ledMatrixBuffer[row] = bufferTemp[(row + n) % NUMBER_OF_ROWS];
	}

	return 1;
}

uint8_t ledMatrixBuffer_cyclicShiftDown(uint8_t n) {
	if (n <= 0 || n > NUMBER_OF_ROWS) {
		return 0;
	}

	uint8_t bufferTemp[NUMBER_OF_ROWS];

	for (uint8_t row = 0; row < NUMBER_OF_ROWS; row++) {
		bufferTemp[row] = ledMatrixBuffer[row];
	}

	for (uint8_t row = NUMBER_OF_ROWS - 1; row >= n; row--) {
		ledMatrixBuffer[row] = bufferTemp[(row - n) % NUMBER_OF_ROWS];
	}

	for (uint8_t row = n - 1; row >= 0; row--) {
		ledMatrixBuffer[row] = bufferTemp[NUMBER_OF_ROWS - n];
	}

	return 1;
}