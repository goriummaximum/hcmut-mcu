/**
  ******************************************************************************
  * @file           : clock_buffer.c
  * @brief          :
  *                   This file contains the buffer storing clock value.
  *
  *                   Created on:	Sep 28th, 2021
  *                   Author:		Thien Long
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#include "main.h"
#include "clock_buffer.h"

//clock var
static int second = 0;
static int minute = 30;
static int hour = 12;

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

void setInitialDot(GPIO_PinState st) {
	HAL_GPIO_WritePin(DOT_PORT, DOT_PIN, st);
}

void updateDot(void) {
	HAL_GPIO_TogglePin(DOT_PORT, DOT_PIN);
}