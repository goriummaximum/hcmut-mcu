/**
  ******************************************************************************
  * @file           : led_7seg.c
  * @brief          :
  *                   This file contains the buffer-driver define for controlling 1D 7-seg LEDs.
  *
  *                   Created on:	Sep 12th, 2021
  *                   Author:		Thien Long
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#include "main.h"
#include "led_7seg.h"

static uint8_t led7SegBuffer[NUMBER_OF_LEDS_7SEG][VALUE_BIT_WIDTH_7SEG];
static uint8_t led7SegArrayPins[NUMBER_OF_SEGS] = {
		GPIO_PIN_0,
		GPIO_PIN_1,
		GPIO_PIN_2,
		GPIO_PIN_3,
		GPIO_PIN_4,
		GPIO_PIN_5,
		GPIO_PIN_6
};

uint8_t led7SegBuffer_Write(uint8_t ledPos, uint8_t value) {
	if (ledPos >= NUMBER_OF_LEDS_7SEG) {
		return 0;
	}

	if (value >= NUMBER_OF_VALUES_7SEG) {
		return 0;
	}

	//extract bit i from value to bit i in bit array
	for (uint8_t i = 0; i < VALUE_BIT_WIDTH_7SEG; i++) {
		led7SegBuffer[ledPos][i] = (value >> (3 - i)) & 0x01;
	}

	return 1;
}

void led7SegDriver_Drive(uint8_t ledPos) {
	HAL_GPIO_WritePin(GPIO_PORT_7SEG, led7SegArrayPins[0], !(
			(!led7SegBuffer[ledPos][1]&&!led7SegBuffer[ledPos][3])
			|| led7SegBuffer[ledPos][2]
			|| (led7SegBuffer[ledPos][1]&&led7SegBuffer[ledPos][3])
			|| led7SegBuffer[ledPos][0])
			);
	HAL_GPIO_WritePin(GPIO_PORT_7SEG, led7SegArrayPins[1],  !(
			!led7SegBuffer[ledPos][1]
			|| (!led7SegBuffer[ledPos][2]&&!led7SegBuffer[ledPos][3])
			|| (led7SegBuffer[ledPos][2]&&led7SegBuffer[ledPos][3]))
			);
	HAL_GPIO_WritePin(GPIO_PORT_7SEG, led7SegArrayPins[2],  !(
			!led7SegBuffer[ledPos][2]
			|| led7SegBuffer[ledPos][3]
			|| led7SegBuffer[ledPos][1])
			);
	HAL_GPIO_WritePin(GPIO_PORT_7SEG, led7SegArrayPins[3],  !(
			(!led7SegBuffer[ledPos][1]&&!led7SegBuffer[ledPos][3])
			|| (!led7SegBuffer[ledPos][1]&&led7SegBuffer[ledPos][2])
			|| (led7SegBuffer[ledPos][1]&&!led7SegBuffer[ledPos][2]&&led7SegBuffer[ledPos][3])
			|| (led7SegBuffer[ledPos][2]&&!led7SegBuffer[ledPos][3])
			|| led7SegBuffer[ledPos][0])
			);
	HAL_GPIO_WritePin(GPIO_PORT_7SEG, led7SegArrayPins[4],  !(
			(!led7SegBuffer[ledPos][1]&&!led7SegBuffer[ledPos][3])
			|| (led7SegBuffer[ledPos][2]&&!led7SegBuffer[ledPos][3]))
			);
	HAL_GPIO_WritePin(GPIO_PORT_7SEG, led7SegArrayPins[5],  !(
			(!led7SegBuffer[ledPos][2]&&!led7SegBuffer[ledPos][3])
			|| (led7SegBuffer[ledPos][1]&&!led7SegBuffer[ledPos][2])
			|| (led7SegBuffer[ledPos][1]&&!led7SegBuffer[ledPos][3])
			|| led7SegBuffer[ledPos][0])
			);
	HAL_GPIO_WritePin(GPIO_PORT_7SEG, led7SegArrayPins[6],  !(
			(!led7SegBuffer[ledPos][1]&&led7SegBuffer[ledPos][2])
			|| (led7SegBuffer[ledPos][1]&&!led7SegBuffer[ledPos][2])
			|| led7SegBuffer[ledPos][0]
			|| (led7SegBuffer[ledPos][2]&&!led7SegBuffer[ledPos][3]))
			);
}

void display7SEG(uint8_t ledPos, int num)
{
	if(!led7SegBuffer_Write(ledPos, (uint8_t)num)) {
		return;
	}

	led7SegDriver_Drive(ledPos);
}
