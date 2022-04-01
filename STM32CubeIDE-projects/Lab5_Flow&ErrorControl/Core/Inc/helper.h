/*
 * helper.h
 *
 *  Created on: 4 Dec 2021
 *      Author: WIN 10
 */

#ifndef INC_HELPER_H_
#define INC_HELPER_H_

extern UART_HandleTypeDef huart2;
extern ADC_HandleTypeDef hadc1;
extern uint8_t cmdBuffer[];
extern uint8_t cmd_length;

void resetBuffer();
void printADC(int indicator);

#endif /* INC_HELPER_H_ */
