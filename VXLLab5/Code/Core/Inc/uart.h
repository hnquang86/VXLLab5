/*
 * uart.h
 *
 *  Created on: Dec 3, 2024
 *      Author: Admin
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include "main.h"
#include "string.h"
#include "stdio.h"
#include <stdint.h>
#include <stdlib.h>

#define BUFFERLENGTH 50

#define IDLE        0
#define FIND_START  1
#define FIND_END    2

extern UART_HandleTypeDef huart2;
extern uint8_t cmd_flag;
extern char* cmd_str;


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);


void uart_init();


void check_str_fsm();

char* substring(char* str, uint16_t start, uint16_t end);
uint8_t find_char(char* str, uint16_t* index, char character);











#endif /* INC_UART_H_ */
