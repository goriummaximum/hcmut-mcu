/**
  ******************************************************************************
  * @file           : software_timer.c
  * @brief          :
  *                   This file contains implementation of software timer using
  *                   a counter and a flag.
  *
  *                   Created on:	Oct 2nd, 2021
  *                   Author:		Thien Long
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#include "main.h"
#include "software_timer.h"

static int timer0_counter = 0;
static int timer0_flag = 0;

int get_timer0_flag_value(void) {
	return timer0_flag;
}

void setTimer0(int duration) {
	timer0_counter = duration / TIMER_CYCLE;
	timer0_flag = 0;
}

void timer_run(void) {
	if (timer0_counter > 0) {
		timer0_counter--;

		if (timer0_counter == 0) {
			timer0_flag = 1;
		}
	}
}
