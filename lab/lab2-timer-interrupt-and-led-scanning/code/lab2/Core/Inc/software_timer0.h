/**
  ******************************************************************************
  * @file           : software_timer0.h
  * @brief          : Header for software_timer0.c file.
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
#ifndef __SOFTWARE_TIMER0_H
#define __SOFTWARE_TIMER0_H

#define TIMER0_CYCLE		250 //ms

//get timer0_flag value
int get_timer0_flag_value(void);

//set the timer0_counter respects to the duration and TIMER_CYCLE
void setTimer0(int duration);

//count down timer0_counter to 0 and raise the timer_flag
void timer0_run(void);

#endif