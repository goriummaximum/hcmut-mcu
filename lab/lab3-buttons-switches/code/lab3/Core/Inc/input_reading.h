/**
  ******************************************************************************
  * @file           : input_reading.h
  * @brief          : This file contain the implementation of reading buttons and
  * 				deboucing machanism.
  *
  *
  *                   Created on:	Oct 19th, 2021
  *                   Author:		Thien Long
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef INC_INPUT_READING_H_
#define INC_INPUT_READING_H_

#define BUTTON_1_GPIO_Port		GPIOA
#define BUTTON_1_Pin			GPIO_PIN_0

void button_reading(void);
unsigned char is_button_pressed(unsigned char index);
unsigned char is_button_pressed_1s(unsigned char index);

#endif /* INC_INPUT_READING_H_ */