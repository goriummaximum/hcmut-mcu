/**
  ******************************************************************************
  * @file           : led_7seg.c
  * @brief          :
  *                   This file contains the buffer-driver define for controlling 1D 7-seg LEDs.
  *
  *                   Created on:	Sep 28th, 2021
  *                   Author:		Thien Long
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#include "main.h"
#include "led_7seg.h"

static uint8_t led7SegBuffer[NUMBER_OF_LEDS_7SEG];

static uint16_t led7SegArrayPins[NUMBER_OF_SEGS] = {
		GPIO_PIN_0,
		GPIO_PIN_1,
		GPIO_PIN_2,
		GPIO_PIN_3,
		GPIO_PIN_4,
		GPIO_PIN_5,
		GPIO_PIN_6
};

static GPIO_PinState led7SegPinState[2] = {
		GPIO_PIN_SET,
		GPIO_PIN_RESET
};

static uint8_t led7SegValueConversion[NUMBER_OF_VALUES_7SEG] = {
		0x3F,
		0x06,
		0x5B,
		0x4F,
		0x66,
		0x6D,
		0x7D,
		0x07,
		0x7F,
		0x6F,
		0x77,
		0x7C,
		0x39,
		0x5E,
		0x79,
		0x71
};

static GPIO_PinState enPinState[2] = {
		GPIO_PIN_SET,
		GPIO_PIN_RESET
};

static uint16_t enSel = EN0_PIN;
static int ledNum[NUMBER_OF_LEDS_7SEG] = {1, 2, 3, 0};

//ex3
static const int MAX_LED = 4;
static int index_led = 0;
static int led_buffer[NUMBER_OF_LEDS_7SEG] = {1, 2, 3, 4};

//clock var
static int second = 0;
static int minute = 0;
static int hour = 0;

uint8_t led7SegBuffer_Write(uint8_t ledPos, uint8_t value) {
	if (ledPos >= NUMBER_OF_LEDS_7SEG) {
		return 0;
	}

	if (value >= NUMBER_OF_VALUES_7SEG) {
		return 0;
	}

	led7SegBuffer[ledPos] = value;

	return 1;
}

void led7SegDriver_Drive(uint8_t ledPos) {
	uint8_t segValue = led7SegValueConversion[led7SegBuffer[ledPos]];
	for (uint8_t segPos = 0; segPos < NUMBER_OF_SEGS; segPos++) {
		if (segValue & (0x01 << segPos)) {
			HAL_GPIO_WritePin(GPIO_PORT_7SEG, led7SegArrayPins[segPos], led7SegPinState[1]);
		}

		else {
			HAL_GPIO_WritePin(GPIO_PORT_7SEG, led7SegArrayPins[segPos], led7SegPinState[0]);
		}
	}
}

void display7SEG(uint8_t ledPos, int num) {
	if(!led7SegBuffer_Write(ledPos, (uint8_t)num)) {
		return;
	}

	led7SegDriver_Drive(ledPos);
}

void selectEn(uint16_t selPin) {
	//off all
	HAL_GPIO_WritePin(EN_PORT, 0xFFFF, enPinState[0]);
	//write pin according to sel
	HAL_GPIO_WritePin(EN_PORT, selPin, enPinState[1]);
}

void led7fsm(void) {
	selectEn(enSel);
	switch (enSel) {
	case EN0_PIN: {
		display7SEG(0, ledNum[0]);
		enSel = EN1_PIN;
		break;
	}

	case EN1_PIN: {
		display7SEG(1, ledNum[1]);
		enSel = EN2_PIN;
		break;
	}

	case EN2_PIN: {
		display7SEG(2, ledNum[2]);
		enSel = EN3_PIN;
		break;
	}

	case EN3_PIN: {
		display7SEG(3, ledNum[3]);
		enSel = EN0_PIN;
		break;
	}

	default:
		break;
	}
}

void update7SEG(void) {
	if (index_led < 0 || index_led > 3) {
		return;
	}

	switch (index_led) {
	case 0:
		selectEn(EN0_PIN);
		display7SEG(index_led, led_buffer[index_led]);
		index_led = 1;
		break;

	case 1:
		selectEn(EN1_PIN);
		display7SEG(index_led, led_buffer[index_led]);
		index_led = 2;
		break;

	case 2:
		selectEn(EN2_PIN);
		display7SEG(index_led, led_buffer[index_led]);
		index_led = 3;
		break;

	case 3:
		selectEn(EN3_PIN);
		display7SEG(index_led, led_buffer[index_led]);
		index_led = 0;
		break;

	default:
		break;
	}
}

uint8_t updateClockBuffer(int hour, int min) {
	if (hour > 23 || hour < 0 || min > 59 || min < 0) {
		return 0;
	}

	led_buffer[0] = hour / 10;
	led_buffer[1] = hour % 10;
	led_buffer[2] = min / 10;
	led_buffer[3] = min % 10;

	return 1;
}

void updateClock(void) {
	second++;
	if (second >= 60) {
		second = 0;
		minute++;
	}

	if (minute >= 60) {
		minute = 0;
		hour++;
	}

	if (hour >= 24) {
		hour = 0;
	}

	if (!updateClockBuffer(hour, minute)) {
		return;
	}
}
