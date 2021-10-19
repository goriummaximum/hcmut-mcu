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

#include "traffic_light_processing.h"
#include "input_reading.h"
#include "main.h"

enum ButtonModeState {
	NORMAL_MODE,
	RED_LED_DURATION_MODIFICATION,
	RED_LED_INCREASE_DURATION,
	AMBER_LED_DURATION_MODIFICATION,
	AMBER_LED_INCREASE_DURATION,
	GREEN_LED_DURATION_MODIFICATION,
	GREEN_LED_INCREASE_DURATION
};

static enum ButtonModeState buttonModeState = NORMAL_MODE;

void traffic_light_processing_fsm(void) {
	switch (buttonModeState) {
	case NORMAL_MODE:
		//todo

		if (is_button_pressed(0)) {
			buttonModeState = RED_LED_DURATION_MODIFICATION;
		}
		break;

	case RED_LED_DURATION_MODIFICATION:
		//todo

		if (is_button_pressed(0)) {
			buttonModeState = AMBER_LED_DURATION_MODIFICATION;
		}

		else if (is_button_pressed(1)) {
			buttonModeState = RED_LED_INCREASE_DURATION;
		}

		else if (in_button_pressed(2)) {
			buttonModeState = NORMAL_MODE;
		}
		break;

	case RED_LED_INCREASE_DURATION:
		//todo

		buttonModeState = RED_LED_DURATION_MODIFICATION;
		break;

	case AMBER_LED_DURATION_MODIFICATION:
		//todo

		if (is_button_pressed(0)) {
			buttonModeState = GREEN_LED_DURATION_MODIFICATION;
		}

		else if (is_button_pressed(1)) {
			buttonModeState = AMBER_LED_INCREASE_DURATION;
		}

		else if (in_button_pressed(2)) {
			buttonModeState = NORMAL_MODE;
		}
		break;

	case AMBER_LED_INCREASE_DURATION:
		//todo

		buttonModeState = AMBER_LED_DURATION_MODIFICATION;
		break;

	case GREEN_LED_DURATION_MODIFICATION:
		//todo

		if (is_button_pressed(0)) {
			buttonModeState = NORMAL_MODE;
		}

		else if (is_button_pressed(1)) {
			buttonModeState = GREEN_LED_INCREASE_DURATION;
		}

		else if (in_button_pressed(2)) {
			buttonModeState = NORMAL_MODE;
		}
		break;

	case GREEN_LED_INCREASE_DURATION:
		//todo

		buttonModeState = GREEN_LED_DURATION_MODIFICATION;
		break;
	}
}
