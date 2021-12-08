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
	BODY
};

static enum CharState cState = BEGIN;
static char commandStr[COMMAND_BUFFER];
static int str_index = 0;

void command_parser_fsm(char inputChar) {
	switch (cState) {
	case BEGIN:
		commandStr[0] = '\0';
		HAL_UART_Transmit(&huart2, "!", 1, 50);
		if (inputChar == '!') {
			cState = BODY;
		}
		break;

	case BODY:
		if (inputChar == '#') {
			commandStr[str_index] = '\0';
			str_index = 0;
			strcpy(command_data, commandStr);
			command_flag = 1;
			HAL_UART_Transmit(&huart2, "#\r\n", 3, 50);

			cState = BEGIN;
		}

		else {
			commandStr[str_index++] = inputChar;

			if (str_index == COMMAND_BUFFER) {
				str_index = 0;
			}

			HAL_UART_Transmit(&huart2, &inputChar, 1, 50);
		}

		break;
	}
}
