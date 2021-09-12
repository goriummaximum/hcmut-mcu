/**
  ******************************************************************************
  * @file           : 1darray_led.c
  * @brief          :
  *                   This file contains the buffer-driver define for controlling 1D array LED.
  *
  *                   Created on:	Sep 12th, 2021
  *                   Author:		Thien Long
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#include "main.h"
#include "1darray_led.h"

static uint8_t ledArrayBuffer[NUMBER_OF_LEDS];
static uint8_t ledArrayPins[NUMBER_OF_LEDS] = {GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7};
static uint8_t ledArrayEncoder[NUMBER_OF_VALUES] = {GPIO_PIN_SET, GPIO_PIN_RESET}; //idx 0 - SET, idx 1 - RESET

uint8_t ledArrayBuffer_Write(uint8_t value) {
	if (value >= NUMBER_OF_LEDS*2) {
		return 0;
	}

	for (uint8_t i = 0; i < NUMBER_OF_LEDS; i++) {
		ledArrayBuffer[i] = (value >> i) & 0x01; //write the i bit from smallest to highest order to buffer
	}

	return 1;
}

void ledArrayDriver_Drive(void) {
	for (uint8_t i = 0; i < NUMBER_OF_LEDS; i++) {
		HAL_GPIO_WritePin(GPIO_PORT_LED_ARRAY, ledArrayPins[i], ledArrayEncoder[ledArrayBuffer[i]]); //write pin
	}
}

void displayLedArray(uint8_t value) {
	if(!ledArrayBuffer_Write(value)) {
		return;
	}

	ledArrayDriver_Drive();
}
