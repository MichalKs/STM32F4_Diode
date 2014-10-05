/**
 * @file: 	main.c
 * @brief:	LED test
 * @date: 	9 kwi 2014
 * @author: Michal Ksiezopolski
 *
 *
 * @verbatim
 * Copyright (c) 2014 Michal Ksiezopolski.
 * All rights reserved. This program and the
 * accompanying materials are made available
 * under the terms of the GNU Public License
 * v3.0 which accompanies this distribution,
 * and is available at
 * http://www.gnu.org/licenses/gpl.html
 * @endverbatim
 */

#include <stm32f4xx.h>
#include <stdio.h>
#include <stdlib.h>

#include <timers.h>
#include <led.h>
#include <comm.h>
#include <utils.h>

#define SYSTICK_FREQ 1000 ///< Frequency of the SysTick set at 1kHz.

void softTimerCallback(void);

#define DEBUG

#ifdef DEBUG
#define d_print(str, args...) printf("MAIN--> "str"%s",##args,"\r")
#define d_println(str, args...) printf("MAIN--> "str"%s",##args,"\r\n")
#else
#define d_print(str, args...) (void)0
#define d_println(str, args...) (void)0
#endif


int main(void) {
	
  COMM_Init(9600);
  d_println("Starting program"); // Print a string to terminal

	TIMER_Init(SYSTICK_FREQ); // Initialize timer

	// Add a soft timer with callback running every 1000ms
	int8_t timerID = TIMER_AddSoftTimer(1000, softTimerCallback);
	TIMER_StartSoftTimer(timerID);

	LED_Init(LED0); // Add an LED
	LED_Init(LED1); // Add an LED
	LED_Init(LED2); // Add an LED
	LED_Init(LED3); // Add an LED
	LED_Init(LED5);
	LED_ChangeState(LED5, LED_ON);

	while (1) {
		TIMER_SoftTimersUpdate();
	}
}
/**
 * @brief Callback function called on every soft timer overflow
 */
void softTimerCallback(void) {

  static uint8_t counter;

  switch (counter % 4) {

  case 0:
    LED_ChangeState(LED0, LED_ON);
    LED_ChangeState(LED1, LED_OFF);
    LED_ChangeState(LED2, LED_OFF);
    LED_ChangeState(LED3, LED_OFF);
    break;

  case 1:
    LED_ChangeState(LED0, LED_OFF);
    LED_ChangeState(LED1, LED_ON);
    LED_ChangeState(LED2, LED_OFF);
    LED_ChangeState(LED3, LED_OFF);
    break;

  case 2:
    LED_ChangeState(LED0, LED_OFF);
    LED_ChangeState(LED1, LED_OFF);
    LED_ChangeState(LED2, LED_ON);
    LED_ChangeState(LED3, LED_OFF);
    break;

  case 3:
    LED_ChangeState(LED0, LED_OFF);
    LED_ChangeState(LED1, LED_OFF);
    LED_ChangeState(LED2, LED_OFF);
    LED_ChangeState(LED3, LED_ON);
    break;
  }


  d_println("Test string sent from STM32F4!!!"); // Print test string
	counter++;
}
