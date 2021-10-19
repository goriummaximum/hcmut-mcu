/**
  ******************************************************************************
  * @file           : software_timer.c
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

#include "software_timer.h"
#include "main.h"

static int timer_counter = 0;
static int timer_flag = 0;

int get_timer_flag_value(void) {
	return timer_flag;
}

void setTimer(int duration) {
	timer_counter = duration / TIMER_CYCLE;
	timer_flag = 0;
}

void timer_run(void) {
	if (timer_counter > 0) {
		timer_counter--;

		if (timer_counter == 0) {
			timer_flag = 1;
		}
	}
}
