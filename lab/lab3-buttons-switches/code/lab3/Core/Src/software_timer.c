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

static int timer_counter[NO_OF_TIMERS] = {0, 0};
static int timer_flag[NO_OF_TIMERS] = {0, 0};

int get_timer_flag_value(int idx) {
	return timer_flag[idx];
}

void setTimer(int idx, int duration) {
	timer_counter[idx] = duration / TIMER_CYCLE;
	timer_flag[idx] = 0;
}

void timer_run(int idx) {
	if (timer_counter[idx] > 0) {
		timer_counter[idx]--;

		if (timer_counter[idx] == 0) {
			timer_flag[idx] = 1;
		}
	}
}
