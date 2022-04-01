/*
 * helper.c
 *
 *  Created on: 4 Dec 2021
 *      Author: WIN 10
 */

#include "main.h"
#include "helper.h"

uint32_t ADC_value = 0;
char ADC_print[4];

uint8_t response_format_1_old[] = "\r\n!ADC=";
uint8_t response_format_1_new[] = "!ADC=";
uint8_t response_format_2[] = "#\r\n";

void resetBuffer() {
	memset(cmdBuffer, 0, CMD_MAX_LENGTH);
	cmd_length = 0;
}

void printADC(int indicator) {
	if (indicator == GET_OLD_ADC)
		HAL_UART_Transmit(&huart2, response_format_1_old, sizeof(response_format_1_old), 100);
	else if (indicator == GET_NEW_ADC) {
		HAL_UART_Transmit(&huart2, response_format_1_new, sizeof(response_format_1_new), 100);
		ADC_value = HAL_ADC_GetValue(&hadc1);
		sprintf(ADC_print, "%d", (int)ADC_value);
	}

	HAL_UART_Transmit(&huart2, (uint8_t*)ADC_print, sizeof(ADC_print), 100);
	HAL_UART_Transmit(&huart2, response_format_2, sizeof(response_format_2), 100);
}
