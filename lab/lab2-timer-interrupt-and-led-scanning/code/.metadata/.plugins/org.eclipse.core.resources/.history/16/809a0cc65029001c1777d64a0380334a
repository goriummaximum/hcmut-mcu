/**
  ******************************************************************************
  * @file           : software_timer1.c
  * @brief          :
  *                   This file contains implementation of software timer using
  *                   a counter and a flag (precision to 1us).
  *
  *                   Created on:	Oct 3nd, 2021
  *                   Author:		Thien Long
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#include <software_timer1.h>
#include "main.h"

static int timer1_counter = 0;
static int timer1_flag = 0;

int get_timer1_flag_value(void) {
	return timer1_flag;
}

void setTimer1(int duration) {
	timer1_counter = duration / TIMER1_CYCLE;
	timer1_flag = 0;
}

void timer1_run(void) {
	if (timer1_counter > 0) {
		timer1_counter--;

		if (timer1_counter == 0) {
			timer1_flag = 1;
		}
	}
}
