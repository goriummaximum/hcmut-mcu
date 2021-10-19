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

static int timer_counter[NO_OF_TIMERS];
static int timer_flag[NO_OF_TIMERS];

void software_timer_init(void) {
	for (char i = 0; i < NO_OF_TIMERS; i++) {
		timer_counter[i] = 0;
		timer_flag[i] = 0;
	}
}

int get_timer_flag_value(int idx) {
	if (idx < 0 || idx > NO_OF_TIMERS) {
		return -1;
	}

	return timer_flag[idx];
}

void setTimer(int idx, int duration) {
	if (idx < 0 || idx > NO_OF_TIMERS || duration < 0) {
		return;
	}

	timer_counter[idx] = duration / TIMER_CYCLE;
	timer_flag[idx] = 0;
}

void timer_run(int idx) {
	if (idx < 0 || idx > NO_OF_TIMERS) {
		return;
	}

	if (timer_counter[idx] > 0) {
		timer_counter[idx]--;

		if (timer_counter[idx] == 0) {
			timer_flag[idx] = 1;
		}
	}
}
