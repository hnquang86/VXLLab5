/*
 * handle.c
 *
 *  Created on: Dec 3, 2024
 *      Author: Admin
 */
#include "handle.h"
#include "software_timer.h"
extern ADC_HandleTypeDef hadc1;

uint32_t ADC_value = 0;
char str[50];


uint8_t handle_state = IDLE;
void handle_fsm(){
	 switch(handle_state){
	 	 case IDLE:
	 		 //if cmd_flag = 1 --> change to CMD_CHECK
	 		 if(cmd_flag){
	 			handle_state = CMD_CHECK;
	 		 }
	 		 break;
	 	 case CMD_CHECK:
	 		 //check whether cmd_str == RST ? YES -> change to SEND, NO -> return IDLE, cmd_flag = 0
	 		 if(strcmp(cmd_str, "RST") == 0){
	 			handle_state = SEND;
	 		 }
	 		 else{
	 			cmd_flag = 0;
	 			handle_state = IDLE;
	 		 }
	 		 break;
	 	 case SEND:
	 		 //read ADC
	 		 	 	 /* code */
	 		 ADC_value = HAL_ADC_GetValue(&hadc1);
	 		ADC_value = 1351;
	 		 //send data and setup time to timeout, change to ACK, cmd_flag = 0 to check receive string
	 		 HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "!ADC=%d#\n", (int)ADC_value), 100);
	 		 cmd_flag = 0;
	 		 handle_state = ACK;
	 		 setTimer(0, 3000);
	 		 break;
	 	 case ACK:
	 		 //wait to ACK from user and return IDLE, if timeout -> change to RESEND
	 		 if(cmd_flag && strcmp(cmd_str, "OK") == 0){
	 			HAL_UART_Transmit(&huart2, (uint8_t*)"Done", 6, 10);
	 			cmd_flag = 0;
	 			handle_state = IDLE;
	 		 }
	 		 else if(getTimerFlag(0)){		//timeout
	 			handle_state = RESEND;
	 		 }
	 		 break;
	 	 case RESEND:
	 		 	//after resend -> change to IDLE
	 		HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "!ADC=%d#\n", (int)ADC_value), 100);
	 		handle_state = IDLE;
	 		 break;
	 }
}


void init(){

}



