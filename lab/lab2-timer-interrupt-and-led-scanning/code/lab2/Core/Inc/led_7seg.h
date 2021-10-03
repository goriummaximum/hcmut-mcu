/**
  ******************************************************************************
  * @file           : led_7seg.h
  * @brief          : Header for led_7seg.c file.
  *                   This file contains the buffer-driver define for controlling 7-seg LEDs.
  *
  *                   Created on:	Sep 28th, 2021
  *                   Author:		Thien Long
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#ifndef __LED_7SEG_H
#define __LED_7SEG_H

#define NUMBER_OF_LEDS_7SEG			4
#define NUMBER_OF_VALUES_7SEG		16
#define NUMBER_OF_SEGS				7
#define GPIO_PORT_7SEG 				GPIOB

#define EN_PORT		GPIOA
#define EN0_PIN		GPIO_PIN_6
#define EN1_PIN		GPIO_PIN_7
#define EN2_PIN		GPIO_PIN_8
#define EN3_PIN		GPIO_PIN_9

//Write value to led at ledPos in buffer
uint8_t led7SegBuffer_Write(uint8_t ledPos, uint8_t value);

//drive the led at ledPos
void led7SegDriver_Drive(uint8_t ledPos);

//display7SEG
void display7SEG(uint8_t ledPos, int num);

//EN select and display
void selectEn(uint16_t selPin);

//7seg FSM
void led7fsm(void);

//update 7led
void update7SEG(void);

//update clock buffer
uint8_t updateClockBuffer(int hour, int min);

#endif /* __LED_7SEG_H */