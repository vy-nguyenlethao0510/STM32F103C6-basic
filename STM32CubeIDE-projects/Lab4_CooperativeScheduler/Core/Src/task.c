/*
 * task.c
 *
 *  Created on: Nov 7, 2021
 *      Author: PCPV
 */

#include "main.h"
#include "global.h"
#include "task.h"
#include <stdio.h>

void task_display1() {
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}
void task_display2() {
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_6);
}
void task_display3() {
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_7);
}
void task_display4() {
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_8);
}
void task_display5() {
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
}

