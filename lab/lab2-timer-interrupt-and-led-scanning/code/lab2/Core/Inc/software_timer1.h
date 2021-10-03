/**
  ******************************************************************************
  * @file           : software_timer1.h
  * @brief          : Header for software_timer1.c file.
  *                   This file contains the software timer using definition using
  *                   a counter and a flag. (precision to 1us)
  *
  *                   Created on:	Oct 3nd, 2021
  *                   Author:		Thien Long
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __SOFTWARE_TIMER1H
#define __SOFTWARE_TIMER1_H

#define TIMER1_CYCLE		1000 //us

//get timer1_flag value
int get_timer1_flag_value(void);

//set the timer1_counter respects to the duration and TIMER_CYCLE
void setTimer1(int duration);

//count down timer1_counter to 0 and raise the timer_flag
void timer1_run(void);

#endif
