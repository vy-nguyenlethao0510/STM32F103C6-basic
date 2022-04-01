/*
 * global.h
 *
 *  Created on: Nov 11, 2021
 *      Author: PCPV
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#define SCH_MAX_TASKS 					5
#define DESIRED_NUMBER_OF_TASKS 		2
#define INIT_ADD 						0
#define PERIODIC_ADD 					1

typedef struct {
	void (*pTask)(void);
	uint32_t Delay;
	uint32_t Period;
	uint8_t RunMe;
	uint8_t TaskID;
	//uint8_t Taskpos;
} sTask;

typedef struct {
	sTask TASK_QUEUE[SCH_MAX_TASKS];
	int numofTask;
} taskList;



#endif /* INC_GLOBAL_H_ */
