/*
 * fsm.c
 *
 *  Created on: 4 Dec 2021
 *      Author: WIN 10
 */
#include <string.h>
#include "main.h"
#include "fsm.h"

const uint8_t cmd_RST[] = "!RST#";
const uint8_t cmd_OK[] = "!OK#";
uint8_t UARTstate = IDLE;
uint8_t buffer_flag = 0;

void uart_communiation_fsm() {
	switch(UARTstate) {
	case IDLE:
		break;
	case RESPONSE_ADC:
		printADC(GET_NEW_ADC);
		setTimer();
		UARTstate = WAIT_FOR_REPLY;
		break;
	case WAIT_FOR_REPLY:
		if (timeout_flag == 1) {
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
			resetBuffer();
			printADC(GET_OLD_ADC);
			setTimer();
		}
		break;
	case ERROR:
		printERROR();
		resetBuffer();
		UARTstate = IDLE;
		break;
	}
}

void command_parser_fsm() {
	switch(cmd_length) {
	case 0:
	case 1:
	case 2:
		ERROR_CODE = CMD_NOT_EXISTED;
		UARTstate = ERROR;
		break;
	case 4: 	// "!OK#"
		if (strcmp((void*)cmdBuffer, (void*)cmd_OK) == 0)
			UARTstate = IDLE;
		else {
			ERROR_CODE = CMD_NOT_EXISTED;
			UARTstate = ERROR;
		}
		break;
	case 5:		// "!RST#"
		if (strcmp((void*)cmdBuffer, (void*)cmd_RST) == 0)
			UARTstate = RESPONSE_ADC;
		else {
			ERROR_CODE = CMD_NOT_EXISTED;
			UARTstate = ERROR;
		}
		break;
	}
	resetBuffer();
}
