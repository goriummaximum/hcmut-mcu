/**
  ******************************************************************************
  * @file           : scheduler.c
  * @brief          : Co-operative scheduler declaration
  ******************************************************************************
  *                   Created on:	Nov 5th, 2021
  *                   Author:		Thien Long
  ******************************************************************************
  */
#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "stdio.h"

typedef struct {
	// Pointer to the task (must be a ’void (void)’ function)
	void (*pTask) (void);
	// Delay (ticks) until the function will (next) be run
	uint32_t Delay;
	// Interval (ticks) between subsequent runs
	uint32_t Period;
	// Incremented (by scheduler) when task is due to execute
	uint8_t RunMe;
	//This is a hint to solve the question below
	uint32_t TaskID;
} sTask;

// MUST BE ADJUSTED FOR EACH NEW PROJECT
#define SCH_MAX_TASKS 	40
#define NO_TASK_ID 		0

#define ERROR_SCH_TOO_MANY_TASKS 		0
#define ERROR_SCH_CANNOT_DELETE_TASK	1
#define RETURN_ERROR					2
#define RETURN_NORMAL					3

void SCH_Init(void);
void SCH_Update(void);
unsigned char SCH_Add_Task(void (*pFunction)(), unsigned int DELAY, unsigned int PERIOD);
void SCH_Dispatch_Tasks(void);
unsigned char SCH_Delete_Task(const unsigned char TASK_INDEX);
void SCH_Report_Status(void);

#endif