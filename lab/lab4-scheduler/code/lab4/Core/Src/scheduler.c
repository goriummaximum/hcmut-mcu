/**
  ******************************************************************************
  * @file           : scheduler.c
  * @brief          : Co-operative scheduler implementation
  ******************************************************************************
  *                   Created on:	Nov 5th, 2021
  *                   Author:		Thien Long
  ******************************************************************************
  */

#include "scheduler.h"
#include "main.h"

sTask SCH_tasks_G[SCH_MAX_TASKS];

int Error_code_G = 0;

void SCH_Init(void) {
	unsigned char i;
	for (i = 0; i < SCH_MAX_TASKS; i++) {
		SCH_Delete_Task (i);
	}
	// Reset the global error variable
	// − SCH_Delete_Task() will generate an error code,
	// (because the task array is empty)
	Error_code_G = 0;
	//Timer_init() ;
	//Watchdog_init() ;
}

void SCH_Update(void) {
	unsigned char Index ;
	// NOTE: calculations are in *TICKS*
	for (Index = 0; Index < SCH_MAX_TASKS; Index++) {
		//Check if there is a task at this location
		if (SCH_tasks_G[Index].pTask) {
			if (SCH_tasks_G[Index].Delay == 0) {
				// The task is due to run
				// Inc. the ’RunMe’ flag
				SCH_tasks_G[Index].RunMe += 1;
				if (SCH_tasks_G[Index].Period) {
					// Schedule periodic tasks to run again
					SCH_tasks_G[Index].Delay = SCH_tasks_G[Index].Period;
				}
			} else {
				// Not yet ready to run : just decrement the delay
				SCH_tasks_G[Index].Delay -= 1;
			}
		}
	}
}

/*−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−*
 * SCH_Add_Task () Causes a task (function) to be executed at regular intervals
 * or after a user−defined delay
 */
/*−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−*/
unsigned char SCH_Add_Task(void (*pFunction)(), unsigned int DELAY, unsigned int PERIOD) {
	unsigned char Index = 0;
	// First find a gap in the array (if there is one)
	while ((SCH_tasks_G[Index].pTask != 0) && (Index < SCH_MAX_TASKS)) {
		Index++;
	}

	// Have we reached the end of the list?
	if (Index == SCH_MAX_TASKS) {
		//task list is full
		//set the global error variable
		Error_code_G = ERROR_SCH_TOO_MANY_TASKS;
		//Also return an error code
		return SCH_MAX_TASKS;
	}

	//If we ’re here, there is a space in the task array
	SCH_tasks_G[Index].pTask = pFunction;
	SCH_tasks_G[Index].Delay = DELAY;
	SCH_tasks_G[Index].Period = PERIOD;
	SCH_tasks_G[Index].RunMe = 0;
	SCH_tasks_G[Index].TaskID = (uint32_t)Index;
	// return position of task(to allow later deletion)
	return SCH_tasks_G[Index].TaskID;
}

void SCH_Dispatch_Tasks(void) {
	unsigned char Index;
	// Dispatches (runs) the next task (if one is ready)
	for (Index = 0; Index < SCH_MAX_TASKS; Index++) {
		if (SCH_tasks_G[Index].RunMe > 0) {
			(*SCH_tasks_G[Index].pTask)(); // Run the task
			SCH_tasks_G[Index].RunMe -= 1; // Reset / reduce RunMe flag
			// Periodic tasks will automatically run again
			// − if this is a ’one shot ’ task , remove it from the array
			if (SCH_tasks_G[Index].Period == 0) {
				SCH_Delete_Task(Index);
			}
		}
	}
	// Report system status
	SCH_Report_Status();
	// The scheduler enters idle mode at this point
	//SCH_Go_To_Sleep();
}

unsigned char SCH_Delete_Task(const unsigned char TASK_INDEX) {
	unsigned char Return_code;
	if (SCH_tasks_G[TASK_INDEX].pTask == 0) {
		// No task at this location...
		// Set the global error variable
		Error_code_G = ERROR_SCH_CANNOT_DELETE_TASK;
		Return_code = RETURN_ERROR;
	} else {
		Return_code = RETURN_NORMAL;
	}

	SCH_tasks_G[TASK_INDEX].pTask = 0x0000;
	SCH_tasks_G[TASK_INDEX].Delay = 0;
	SCH_tasks_G[TASK_INDEX].Period = 0;
	SCH_tasks_G[TASK_INDEX].RunMe = 0;
	SCH_tasks_G[TASK_INDEX].TaskID = 0;

	return Return_code;
}

void SCH_Report_Status(void) {
#ifdef SCH_REPORT_ERRORS
	// ONLY APPLIES IF WE ARE REPORTING ERRORS
	// Check for a new  error code
	if (Error_code_G != Last_error_code_G) {
		// Negative logic on LEDs assumed
		Error_port = 255 - Error_code_G;
		Last_error_code_G = Error_code_G;

		if (Error_code_G != 0) {
			Error_tick_count_G = 60000;
		} else {
			Error_tick_count_G = 0;
		}
	} else {
		if (Error_tick_count_G != 0) {
			if (--Error_tick_count_G == 0) {
				Error_code_G = 0; // Reset error code
			}
		}
	}
#endif
}






