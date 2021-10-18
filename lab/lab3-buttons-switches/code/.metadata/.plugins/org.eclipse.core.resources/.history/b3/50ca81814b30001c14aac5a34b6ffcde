/*
  ******************************************************************************
  * @file           : timer.c
  * @brief          : This file contain the timer interrupt for reading buttons.
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

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if(htim ->Instance == TIM2){
		button_reading();
	}
}
