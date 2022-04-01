/*
 * scheduler.h
 *
 *  Created on: Nov 7, 2021
 *      Author: PCPV
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

taskList SCH_TASK_LIST;

void insert_to_list(sTask task);

void SCH_Update();
void SCH_Add_Task(uint8_t id, void (*pFunction)(), uint32_t delay, uint32_t period);
void SCH_Dispatch();
void SCH_Report();
void SCH_Delete();

void taskList_display();

#endif /* INC_SCHEDULER_H_ */
