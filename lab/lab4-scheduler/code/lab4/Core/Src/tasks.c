/**
  ******************************************************************************
  * @file           : tasks.c
  * @brief          : Tasks implementation
  ******************************************************************************
  *                   Created on:	Nov 5th, 2021
  *                   Author:		Thien Long
  ******************************************************************************
  */

#include "main.h"
#include "tasks.h"

void task0(void) {
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_0);
}

void task1(void) {
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1);
}

void task2(void) {
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_2);
}

void task3(void) {
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_3);
}

void task4(void) {
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
}
