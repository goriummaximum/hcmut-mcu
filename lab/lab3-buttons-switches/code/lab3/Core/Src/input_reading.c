/**
  ******************************************************************************
  * @file           : input_reading.c
  * @brief          : This file contain the implementation of reading buttons and
  * 				deboucing machanism.
  *
  *                   Created on:	Oct 19th, 2021
  *                   Author:		Thien Long
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#include "main.h"
#include "input_reading.h"

//we aim to work with more than one buttons
#define NO_OF_BUTTONS					3
//timer interrupt duration is 10ms, so to pass 1 second ,
//we need to jump to the interrupt service routine 100 time
#define DURATION_FOR_AUTO_INCREASING	100

#define BUTTON_IS_PRESSED 				GPIO_PIN_RESET
#define BUTTON_IS_RELEASED 				GPIO_PIN_SET

static GPIO_TypeDef *buttonPort[NO_OF_BUTTONS] = {
		BUTTON_0_GPIO_Port,
		BUTTON_1_GPIO_Port,
		BUTTON_2_GPIO_Port
};

static unit16_t buttonPin[NO_OF_BUTTONS] = {
		BUTTON_0_Pin,
		BUTTON_1_Pin,
		BUTTON_2_Pin
};

//the buffer that the final result is stored after
// debouncing
static GPIO_PinState buttonBuffer[NO_OF_BUTTONS];
//we define two buffers for debouncing
static GPIO_PinState debounceButtonBuffer1[NO_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer2[NO_OF_BUTTONS];
//we define a flag for a button pressed more than 1 second.
static uint8_t flagForButtonPress1s[N0_OF_BUTTONS];
//we define counter for automatically increasing the value
//after the button is pressed more than 1 second.
static uint16_t counterForButtonPress1s[N0_OF_BUTTONS];

void button_reading(void) {
	for (char i = 0; i < NO_OF_BUTTONS; i++) {
		debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
		debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(buttonPort[i], buttonPin[i]);
	}

	if (debounceButtonBuffer1[i] == debounceButtonBuffer2[i]) {
		buttonBuffer[i] = debounceButtonBuffer1[i];
		if (buttonBuffer[i] == BUTTON_IS_PRESSED) {
			//if a button is pressed , we start counting
			if (counterForButtonPress1s[i] < DURATION_FOR_AUTO_INCREASING) {
				counterForButtonPress1s[i]++;
			}

			else {
				//the flag is turned on when 1 second has passed
				//since the button is pressed.
				flagForButtonPress1s[i] = 1;
				//todo
			}
		}

		else {
			counterForButtonPress1s[i] = 0;
			flagForButtonPress1s[i] = 0;
		}
	}
}

//checking a button is pressed or not
unsigned char is_button_pressed(uint8_t index) {
	if (index >= NO_OF_BUTTONS) return 0;
	return (buttonBuffer[index] == BUTTON_IS_PRESSED);
}

//Checking a button is pressed more than a second or not
unsigned char is_button_pressed_1s(unsigned char index) {
	if(index >= N0_OF_BUTTONS) return 0xff;
	return (flagForButtonPress1s[index] == 1);
}

