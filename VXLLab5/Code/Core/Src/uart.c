/*
 * uart.c
 *
 *  Created on: Dec 3, 2024
 *      Author: Admin
 *
 */

#include <uart.h>



uint8_t data;
uint8_t receive_flag = 0;
uint8_t buffer[BUFFERLENGTH];
uint16_t buffer_index;
uint8_t buffer_flag = 0;


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == huart2.Instance){
		if(buffer_index == 0 && data == '!')
		{
			receive_flag = 1;
		}

		if(receive_flag){
			buffer[buffer_index++] = data;

			if(data == '#'){
				receive_flag = 0;
				buffer_index = 0;
				buffer_flag = 1;
			}
		}
		HAL_UART_Transmit(&huart2, &data, 1, 10);

		HAL_UART_Receive_IT(&huart2, &data, 1);
	}

}

void uart_init(){
	HAL_UART_Receive_IT(&huart2, &data, 1);
}



uint8_t state = IDLE;
uint16_t current_index = 0;
uint16_t start_index = 0;
uint16_t end_index = 0;

uint8_t cmd_flag = 0;
char* cmd_str;




uint8_t find_char(char* str, uint16_t* index, char character){
    if(str[(*index)] == character){
        return 1;
    }
    (*index)++;
    return 0;
}
char* substring(char* str, uint16_t start, uint16_t end){
    uint16_t len = end - start + 1;
    char* sub = (char*)malloc(len+1);

    strncpy(sub, str + start, len);
    sub[len] = '\0';
    return sub;
}


void check_str_fsm(){
	 switch(state){
	 	 case IDLE:
	 		 if(buffer_flag)
	 		 {
	 			 state = FIND_START;
	 			current_index = 0;
	 		 }
	 		 break;
	 	 case FIND_START:

	 		 if(find_char((char*)buffer, &current_index, '!')){
	 			 start_index = current_index;
	 			 state = FIND_END;
	 			 break;
	 		 }

	 		 if(buffer[current_index] == '\0'){
	 			 state = IDLE;
	 			 buffer_flag = 0;
	 		 }
	 		 break;
	 	 case FIND_END:
	 		 if(find_char((char*)buffer, &current_index, '#')){
	 			 end_index = current_index;
	 			 buffer_flag = 0;
	 			 cmd_str = substring((char*)buffer, start_index+1, end_index-1);
	 			 cmd_flag = 1;
	 			 state = IDLE;
	 			 break;
	 		 }

	 		 if(buffer[current_index] == '\0'){
	 			 state = IDLE;
	 			 buffer_flag = 0;
	 		 }
	 		 break;
	 }

}





