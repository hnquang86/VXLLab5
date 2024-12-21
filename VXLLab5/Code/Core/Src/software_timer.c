/*
 * software_timer.c
 *
 *  Created on: Oct 28, 2024
 *      Author: Admin
 */

#include "software_timer.h"

#define TICK 10
#define NO_OF_TIMER 10

// khoi tao cac bien cho cac sotware timer
static uint32_t timer_counter[NO_OF_TIMER];
static uint8_t timer_flag[NO_OF_TIMER];

void setTimer(uint32_t index, uint32_t counter){
	timer_counter[index] = counter/TICK;  // chia cho TICK de dam bao rang 1 second = 1000
	timer_flag[index] = 0;
}

void timeRun(){
	for(uint32_t i = 0; i < NO_OF_TIMER; i++){
		if(timer_counter[i] >= 0){
			timer_counter[i]--;
			if(timer_counter[i] <= 0){
				timer_flag[i] = 1;
			}
		}
	}
}

uint8_t getTimerFlag(uint32_t index){
	return timer_flag[index];
}
void setTimerFlag(uint32_t index, uint8_t value){
	timer_flag[index] = value;
}
