/**
  ******************************************************************************
  * @file           : software_timer.h
  * @brief          : Header for software_timer.c file.
  *                   This file contains the software timer using definition using
  *                   a counter and a flag. (precision to 1ms)
  *
  *                   Created on:	Oct 2nd, 2021
  *                   Author:		Thien Long
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __SOFTWARE_TIMER_H
#define __SOFTWARE_TIMER_H

#define NO_OF_TIMERS	1

#define TIMER_CYCLE		100 //ms

void software_timer_init(void);

//get timer_flag value
int get_timer_flag_value(int idx);

//set the timer_counter respects to the duration and TIMER_CYCLE
void setTimer(int idx, int duration);

//count down timer_counter to 0 and raise the timer_flag
void timer_run(int idx);

#endif
