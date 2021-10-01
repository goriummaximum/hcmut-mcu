/**
  ******************************************************************************
  * @file           : software_timer.h
  * @brief          : Header for software_timer.c file.
  *                   This file contains the software timer using definition using
  *                   a counter and a flag.
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

#define TIMER_CYCLE		250 //ms

//get timer0_flag value
int get_timer0_flag_value(void);

//set the timer0_counter respects to the duration and TIMER_CYCLE
void setTimer0(int duration);

//count down timer0_counter to 0 and raise the timer_flag
void timer_run(void);

#endif
