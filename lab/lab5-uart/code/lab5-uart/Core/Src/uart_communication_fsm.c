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

enum CommandState {
	BEGIN,
	OK,
	RST,
	RETRANSMIT
};

static enum CommandState commandState = BEGIN;
static char *str;
static int len = 0;

void uart_communication_fsm(void) {
	switch(commandState) {
	case BEGIN:
		if (command_data == "OK") {
			commandState = OK;
		}

		else if (command_data == "RST") {
			commandState = RST;
		}

		else if (is_timeout == 1) {
			commandState = RETRANSMIT;
		}
		break;

	case OK:
		//action

		//transition
		commandState = BEGIN;
		break;

	case RST:
		ADC_value = HAL_ADC_GetValue(&hadc1);
		len = sprintf(str, "!%hu#\r\n", ADC_value);
		HAL_UART_Transmit(&huart2, (void *)str, len, 1000);

		commandState = BEGIN;
		break;

	case RETRANSMIT:
		is_timeout = 0;
		len = sprintf(str, "!%hu#\r\n", ADC_value);
		HAL_UART_Transmit(&huart2, (void *)str, len, 1000);

		commandState = BEGIN;
		break;
	}
}
