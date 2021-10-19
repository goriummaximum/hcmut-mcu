/**
  ******************************************************************************
  * @file           : traffic_light_processing.c
  * @brief          : This file contain the implementation of traffic light FSM.
  *
  *
  *                   Created on:	Oct 29th, 2021
  *                   Author:		Thien Long
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#include "output_display.h"
#include "main.h"
#include "input_reading.h"
#include "1darray_led.h"
#include "led_7seg.h"
#include "timer.h"
#include "traffic_light_processing.h"

enum ModeState {
	NORMAL_MODE,
	RED_LED_RUN,
	AMBER_LED_RUN,
	GREEN_LED_RUN,
	RED_LED_DURATION_MODIFICATION,
	RED_LED_INCREASE_DURATION,
	AMBER_LED_DURATION_MODIFICATION,
	AMBER_LED_INCREASE_DURATION,
	GREEN_LED_DURATION_MODIFICATION,
	GREEN_LED_INCREASE_DURATION
};

//light duration in ms
static unsigned int lightDuration[NUMBER_OF_LEDS] = {
		4000, //RED
		3000, //AMBER
		2000 //GREEN
};

static uint8_t lightSelector[NUMBER_OF_LEDS] = {
		0x1, //RED
		0x2, //AMBER
		0x4 //GREEN
};

static unsigned int countDownDuration = 1000;
static unsigned int downCounter = 0;

static enum ModeState modeState = NORMAL_MODE;

void traffic_light_init(void) {
	button_init();
	ledArray_init();
	displayLedArray(lightSelector[0]); //display red
	setTimer(1, lightDuration[0]);
	setTimer(2, countDownDuration);
}

void traffic_light_processing_fsm(void) {
	switch (modeState) {
	case NORMAL_MODE:
		//actions
		traffic_light_init();
		downCounter = lightDuration[0] / 1000;

		//transition
		if (is_button_pressed(1)) {
			modeState = RED_LED_DURATION_MODIFICATION;
		}

		else {
			modeState = RED_LED_RUN;
		}
		break;

	case RED_LED_RUN:
		//actions
		displayLedArray(lightSelector[0]); //select RED led
		//display 7seg leds
		updateLedBuffer(0, downCounter);
		if (get_timer_flag_value(2)) {
			updateLedBuffer(0, --downCounter);
			setTimer(2, countDownDuration);
		}
		update7SEG();

		//transitions
		if (is_button_pressed(0)) {
			modeState = RED_LED_DURATION_MODIFICATION;
		}

		else {
			if (get_timer_flag_value(1) == 1) {
				downCounter = lightDuration[1] / 1000;
				setTimer(1, lightDuration[1]);
				modeState = AMBER_LED_RUN;
			}
		}
		break;

	case AMBER_LED_RUN:
		//actions
		displayLedArray(lightSelector[1]); //select AMBER led
		//display 7seg leds
		updateLedBuffer(0, downCounter);
		if (get_timer_flag_value(2)) {
			updateLedBuffer(0, --downCounter);
			setTimer(2, countDownDuration);
		}
		update7SEG();

		//transitions
		if (is_button_pressed(0)) {
			modeState = RED_LED_DURATION_MODIFICATION;
		}

		else {
			if (get_timer_flag_value(1) == 1) {
				downCounter = lightDuration[2] / 1000;
				setTimer(1, lightDuration[2]);
				modeState = GREEN_LED_RUN;
			}
		}
		break;

	case GREEN_LED_RUN:
		//actions
		displayLedArray(lightSelector[2]); //select GREEN led
		//display 7seg leds
		updateLedBuffer(0, downCounter);
		if (get_timer_flag_value(2)) {
			updateLedBuffer(0, --downCounter);
			setTimer(2, countDownDuration);
		}
		update7SEG();

		//transitions
		if (is_button_pressed(0)) {
			modeState = RED_LED_DURATION_MODIFICATION;
		}

		else {
			if (get_timer_flag_value(1) == 1) {
				downCounter = lightDuration[0] / 1000;
				setTimer(1, lightDuration[0]);
				modeState = RED_LED_RUN;
			}
		}
		break;

	case RED_LED_DURATION_MODIFICATION:
		//actions
		displayLedArray(lightSelector[0]); //select RED led

		//transitions
		if (is_button_pressed(0)) {
			modeState = AMBER_LED_DURATION_MODIFICATION;
		}

		else if (is_button_pressed(1)) {
			modeState = RED_LED_INCREASE_DURATION;
		}

		else if (is_button_pressed(2)) {
			modeState = NORMAL_MODE;
		}

		else {
			modeState = RED_LED_DURATION_MODIFICATION;
		}
		break;

	case RED_LED_INCREASE_DURATION:
		//todo

		modeState = RED_LED_DURATION_MODIFICATION;
		break;

	case AMBER_LED_DURATION_MODIFICATION:
		//actions
		displayLedArray(lightSelector[1]); //select AMBER led

		//transitions
		if (is_button_pressed(0)) {
			modeState = GREEN_LED_DURATION_MODIFICATION;
		}

		else if (is_button_pressed(1)) {
			modeState = AMBER_LED_INCREASE_DURATION;
		}

		else if (is_button_pressed(2)) {
			modeState = NORMAL_MODE;
		}

		else {
			modeState = AMBER_LED_DURATION_MODIFICATION;
		}
		break;

	case AMBER_LED_INCREASE_DURATION:
		//todo

		modeState = AMBER_LED_DURATION_MODIFICATION;
		break;

	case GREEN_LED_DURATION_MODIFICATION:
		//actions
		displayLedArray(lightSelector[2]); //select GREEN led

		//transitions
		if (is_button_pressed(0)) {
			modeState = NORMAL_MODE;
		}

		else if (is_button_pressed(1)) {
			modeState = GREEN_LED_INCREASE_DURATION;
		}

		else if (is_button_pressed(2)) {
			modeState = NORMAL_MODE;
		}

		else {
			modeState = GREEN_LED_DURATION_MODIFICATION;
		}
		break;

	case GREEN_LED_INCREASE_DURATION:
		//todo

		modeState = GREEN_LED_DURATION_MODIFICATION;
		break;
	}
}
