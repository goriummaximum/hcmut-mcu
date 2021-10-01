/**
  ******************************************************************************
  * @file           : clock_buffer.h
  * @brief          : Header for clock_buffer.c file.
  *                   This file contains the buffer storing clock value.
  *
  *                   Created on:	Sep 28th, 2021
  *                   Author:		Thien Long
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#ifndef __CLOCK_BUFFER_H
#define __CLOCK_BUFFER_H

#define DOT_PIN							GPIO_PIN_4
#define DOT_PORT						GPIOA

//run clock
void updateClock(void);

//update dot
void updateDot(void);

#endif
