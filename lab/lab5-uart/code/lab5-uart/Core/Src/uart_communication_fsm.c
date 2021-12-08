/**
  ******************************************************************************
  * @file           : uart_communication_fsm.c
  * @brief          : This file contain the implementation of uart communication fsm.
  *
  *
  *                   Created on:	Dec 8th, 2021
  *                   Author:		Thien Long
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#include "main.h"
#include "uart_communication_fsm.h"
#include "software_timer.h"

enum CommandState {
	BEGIN,
	OK,
	WAIT_OK,
	RST,
	RETRANSMIT
};

static enum CommandState commandState = BEGIN;
static char str[10];
static int len = 0;

void uart_communication_fsm(void) {
	switch(commandState) {
	case BEGIN:
		if (strcmp(&command_data, "RST") == 0 && command_flag == 1) {
			commandState = RST;
		}
		break;

	case WAIT_OK:
		if (get_timer_flag_value(0)) {
			commandState = RETRANSMIT;
		}

		else if (strcmp(&command_data, "OK") == 0 && command_flag == 1) {
			commandState = OK;
		}

		else {
			command_flag = 0;
		}
		break;

	case OK:
		//action
		command_flag = 0;
		//transition
		commandState = BEGIN;
		break;

	case RST:
		ADC_value = HAL_ADC_GetValue(&hadc1);
		len = sprintf(str, "!%hu#\r\n", ADC_value);
		HAL_UART_Transmit(&huart2, &str, len, 1000);
		command_flag = 0;
		setTimer(0, 1000);
		commandState = WAIT_OK;
		break;

	case RETRANSMIT:
		len = sprintf(str, "!%hu#\r\n", ADC_value);
		HAL_UART_Transmit(&huart2, &str, len, 1000);
		setTimer(0, 1000);

		commandState = WAIT_OK;
		break;
	}
}
