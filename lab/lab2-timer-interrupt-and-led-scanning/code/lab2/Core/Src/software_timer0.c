/**
  ******************************************************************************
  * @file           : software_timer0.c
  * @brief          :
  *                   This file contains implementation of software timer using
  *                   a counter and a flag (precision to 1ms).
  *
  *                   Created on:	Oct 2nd, 2021
  *                   Author:		Thien Long
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#include <software_timer0.h>
#include "main.h"

static int timer0_counter = 0;
static int timer0_flag = 0;

int get_timer0_flag_value(void) {
	return timer0_flag;
}

void setTimer0(int duration) {
	if (duration < 0) {
		return;
	}

	timer0_counter = duration / TIMER0_CYCLE;
	timer0_flag = 0;
}

void timer0_run(void) {
	if (timer0_counter > 0) {
		timer0_counter--;

		if (timer0_counter == 0) {
			timer0_flag = 1;
		}
	}
}
