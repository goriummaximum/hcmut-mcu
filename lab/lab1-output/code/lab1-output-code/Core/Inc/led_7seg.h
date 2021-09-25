/**
  ******************************************************************************
  * @file           : led_7seg.h
  * @brief          : Header for led_7seg.c file.
  *                   This file contains the buffer-driver define for controlling 7-seg LEDs.
  *
  *                   Created on:	Sep 12th, 2021
  *                   Author:		Thien Long
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#ifndef __LED_7SEG_H
#define __LED_7SEG_H

#define NUMBER_OF_LEDS_7SEG			1
#define NUMBER_OF_VALUES_7SEG		16
#define NUMBER_OF_SEGS				7
#define GPIO_PORT_7SEG 				GPIOB

//Write value to led at ledPos in buffer
uint8_t led7SegBuffer_Write(uint8_t ledPos, uint8_t value);

//drive the led at ledPos
void led7SegDriver_Drive(uint8_t ledPos);

//display7SEG
void display7SEG(uint8_t ledPos, int num);

//count down for t interval
void displayCountDownFor(uint8_t ledPos, int t);

#endif /* __LED_7SEG_H */