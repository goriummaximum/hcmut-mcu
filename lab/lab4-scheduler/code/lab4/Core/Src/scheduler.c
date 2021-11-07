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
static uint32_t min_delay = 0;
static unsigned char min_index = 0;

void SCH_Init(void) {
	unsigned char i;
	for (i = 0; i < SCH_MAX_TASKS; i++) {
		SCH_Delete_Task(i);
	}
	// Reset the global error variable
	// − SCH_Delete_Task() will generate an error code,
	// (because the task array is empty)
	Error_code_G = 0;
	//Timer_init() ;
	//Watchdog_init() ;
}

/*
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
*/

void SCH_Update(void) {
	if (SCH_tasks_G[min_index].pTask) {
		//jump to here whenever a task is done
		if (SCH_tasks_G[min_index].Delay == 0) {
			//task ready to be dispatched
			SCH_tasks_G[min_index].RunMe += 1;
			if (SCH_tasks_G[min_index].Period) {
				// Schedule periodic tasks to run again
				SCH_tasks_G[min_index].Delay = SCH_tasks_G[min_index].Period;
			}
		}

		else {
			//jump here every time
			SCH_tasks_G[min_index].Delay -= 1;
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
		Error_code_G = ERROR_SCH_TOO_MANY_TASKS;

		return SCH_MAX_TASKS;
	}

	//If we ’re here, there is a space in the task array
	SCH_tasks_G[Index].pTask = pFunction;
	SCH_tasks_G[Index].Delay = DELAY;
	SCH_tasks_G[Index].Period = PERIOD;
	SCH_tasks_G[Index].RunMe = 0;
	SCH_tasks_G[Index].TaskID = (uint32_t)Index;
	// return position of task(to allow later deletion)
	return Index;
}

void SCH_Dispatch_Tasks(void) {
	unsigned int curr_index = min_index;
	if (SCH_tasks_G[curr_index].pTask) {
		if (SCH_tasks_G[curr_index].RunMe > 0) {
			update_min_task();
			(*SCH_tasks_G[curr_index].pTask)(); // Run the task
			SCH_tasks_G[curr_index].RunMe -= 1; // Reset / reduce RunMe flag
			// − if this is a ’one shot ’ task , remove it from the array
			if (SCH_tasks_G[curr_index].Period == 0) {
				SCH_Delete_Task(curr_index);
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

void update_min_task(void) {
	//update other tasks
	unsigned char Index;
	for (Index = 0; Index < SCH_MAX_TASKS; Index++) {
		if (SCH_tasks_G[Index].pTask) {
			if (Index != min_index) {
				SCH_tasks_G[Index].Delay -= min_delay;
			}
		}
	}

	//find min task
	find_min_task();
}

void find_min_task(void) {
	//find first existed task in task array
	unsigned char Index = 0;
	while (!SCH_tasks_G[Index].pTask) {
		Index++;
	}
	min_delay = SCH_tasks_G[Index].Delay;
	min_index = Index;
	//find min delay
	for (Index = min_index + 1; Index < SCH_MAX_TASKS; Index++) {
		if (SCH_tasks_G[Index].pTask) {
			if (SCH_tasks_G[Index].Delay <= min_delay) {
				min_delay = SCH_tasks_G[Index].Delay;
				min_index = Index;
			}
		}
	}
}






