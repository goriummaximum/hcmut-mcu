/**
  ******************************************************************************
  * @file           : command_parser_fsm.c
  * @brief          : This file contain the implementation of command parser FSM.
  *
  *
  *                   Created on:	Dec 8th, 2021
  *                   Author:		Thien Long
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#include "command_parser_fsm.h"
#include "uart_communication_fsm.h"
#include "main.h"
#include "string.h"

enum CharState {
	BEGIN,
	BODY,
	END
};

static enum CharState cState = BEGIN;
static char *commandStr = NULL;

void command_parser_fsm(char inputChar) {
	switch (cState) {
	case BEGIN:
		commandStr = NULL;
		HAL_UART_Transmit(&huart2, &inputChar, 1, 50);
		if (inputChar == '!') {
			cState = BODY;
		}
		break;

	case BODY:
		strcat(commandStr, &inputChar);
		HAL_UART_Transmit(&huart2, &inputChar, 1, 50);
		if (inputChar == '#') {
			cState = END;
		}
		break;

	case END:
		strcpy(command_data, commandStr);
		HAL_UART_Transmit(&huart2, &inputChar, 1, 50);
		command_flag = 1;
		HAL_UART_Transmit(&huart2, &command_flag, 1, 50);

		cState = BEGIN;
		break;
	}
}
