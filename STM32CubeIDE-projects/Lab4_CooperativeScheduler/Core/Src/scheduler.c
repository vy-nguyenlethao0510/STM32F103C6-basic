/*
 * scheduler.c
 *
 *  Created on: Nov 7, 2021
 *      Author: PCPV
 */

#include "main.h"
#include "global.h"
#include "task.h"
#include "scheduler.h"
#include <stdio.h>

uint8_t ERROR_CODE = 0;

void taskList_display() {
	printf("Number of tasks = %d\r\n", SCH_TASK_LIST.numofTask);
	if (SCH_TASK_LIST.numofTask == 0) {
		printf("No task to display\r\n");
		return;
	}
	for (int i = 0; i < SCH_TASK_LIST.numofTask; i++) {
		printf("--index = %d: ", i);
		printf("TaskID = %d - Delay = %lu\r\n", SCH_TASK_LIST.TASK_QUEUE[i].TaskID, SCH_TASK_LIST.TASK_QUEUE[i].Delay);
	}
}
void insert_to_list(sTask task) {
	// NO TASK IN LIST
	if (SCH_TASK_LIST.numofTask == 0) {
		SCH_TASK_LIST.TASK_QUEUE[0] = task;
		SCH_TASK_LIST.numofTask += 1;
		return;
	} else {
	// 1+ TASK(S) IN LIST
		int pos = 0;
		int prev = SCH_TASK_LIST.TASK_QUEUE[0].Delay;
		int sum = SCH_TASK_LIST.TASK_QUEUE[0].Delay;
		// loop until find the right position
		while (pos < SCH_TASK_LIST.numofTask && task.Delay > sum) {
			pos += 1;
			if (pos < SCH_TASK_LIST.numofTask) {
				prev = sum;
				sum += SCH_TASK_LIST.TASK_QUEUE[pos].Delay;
			}
		}
		if (pos == SCH_TASK_LIST.numofTask) {
			// ADD TO REAR -> update delay of new task only
			task.Delay -= sum;
			SCH_TASK_LIST.TASK_QUEUE[pos] = task;
			SCH_TASK_LIST.numofTask += 1;
			return;
		}
		else {
			// shift elements
			for (int i = SCH_TASK_LIST.numofTask; i > pos; i--) {
				SCH_TASK_LIST.TASK_QUEUE[i] = SCH_TASK_LIST.TASK_QUEUE[i - 1];
			}
			if (pos == 0) {
				// ADD TO FRONT
				SCH_TASK_LIST.TASK_QUEUE[pos] = task;
				sum = 0;
				prev = task.Delay;
			} else {
				// ADD TO MIDDLE
				task.Delay -= prev;
				sum = prev;
				prev += task.Delay;
				SCH_TASK_LIST.TASK_QUEUE[pos] = task;
			}
			// update delay of [pos + 1]
			sum += SCH_TASK_LIST.TASK_QUEUE[pos + 1].Delay;
			SCH_TASK_LIST.TASK_QUEUE[pos + 1].Delay = sum - prev;

			SCH_TASK_LIST.numofTask += 1;
			printf("Insert at pos %d\r\n", pos);
		}
	}
	taskList_display();
}
void SCH_Add_Task(uint8_t id, void (*pFunction)(), uint32_t delay, uint32_t period) {
	//printf("ADD TASK\r\n");
	if (SCH_TASK_LIST.numofTask >= SCH_MAX_TASKS) {
		ERROR_CODE = 1;
		return;
	}
	sTask temp;
	temp.pTask = pFunction;
	temp.Delay = delay;
	temp.Period = period;
	temp.RunMe = 0;
	temp.TaskID = id;
	insert_to_list(temp);
}
void SCH_Update() {
	if (!SCH_TASK_LIST.TASK_QUEUE[0].pTask) {
		ERROR_CODE = 3;
	}
	else {
		if (SCH_TASK_LIST.TASK_QUEUE[0].Delay == 0) {
			SCH_TASK_LIST.TASK_QUEUE[0].RunMe += 1;
			if (SCH_TASK_LIST.TASK_QUEUE[0].Period) {
				SCH_TASK_LIST.TASK_QUEUE[0].Delay = SCH_TASK_LIST.TASK_QUEUE[0].Period;
			}
		}
		else SCH_TASK_LIST.TASK_QUEUE[0].Delay -= 1;
	}
}
void SCH_Delete() {
	int index = 0;
	int add_back_flag = 0;
	sTask temp;
	if (SCH_TASK_LIST.TASK_QUEUE[index].Period) {
		add_back_flag = 1;
		temp = SCH_TASK_LIST.TASK_QUEUE[index];
	}
	for (; index < (SCH_TASK_LIST.numofTask - 1); index++) {
		SCH_TASK_LIST.TASK_QUEUE[index] = SCH_TASK_LIST.TASK_QUEUE[index + 1];
	}
	SCH_TASK_LIST.TASK_QUEUE[index].pTask = 0x0000;
	SCH_TASK_LIST.TASK_QUEUE[index].Delay = 0;
	SCH_TASK_LIST.TASK_QUEUE[index].Period = 0;
	SCH_TASK_LIST.TASK_QUEUE[index].RunMe = 0;
	SCH_TASK_LIST.numofTask -= 1;
	if (add_back_flag == 1) {
		insert_to_list(temp);
	}
}
void SCH_Report() {
	if (ERROR_CODE != 0) {
		switch(ERROR_CODE) {
		case 1:
			printf("ERROR: TOO MANY TASKS!\r\n");
			break;
		case 2:
			printf("ERROR: CANNOT DELETE TASK!\r\n");
			break;
		case 3:
			printf("ERROR: NO TASK AVAILABLE!\r\n");
		}
	} else taskList_display();
}
void SCH_Dispatch() {
	uint8_t index = 0;
	for (; index < SCH_MAX_TASKS; index++) {
		if (SCH_TASK_LIST.TASK_QUEUE[index].RunMe > 0) {
			printf("\r\n> Run task (ID %d) at index = %d\r\n", SCH_TASK_LIST.TASK_QUEUE[index].TaskID, index);
			(*SCH_TASK_LIST.TASK_QUEUE[index].pTask)();
			SCH_TASK_LIST.TASK_QUEUE[index].RunMe -= 1;
			SCH_Delete(index);
		}
	}
	SCH_Report();
}
