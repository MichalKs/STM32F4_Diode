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
#include <uart2.h>
#include <utils.h>

#define SYSTICK_FREQ 1000 ///< Frequency of the SysTick.

void softTimerCallback(void);

int main(void) {
	
	UART2_Init(); // Initialize USART2 (for printf)
	TIMER_Init(SYSTICK_FREQ); // Initialize timer

	// Add a soft timer
	int8_t timerID = TIMER_AddSoftTimer(1000,softTimerCallback);
	TIMER_StartSoftTimer(timerID);

	LED_Init(LED0); // Add an LED
	LED_Init(LED1); // Add an LED
	LED_Init(LED2); // Add an LED
	LED_Init(LED3); // Add an LED

	printf("Starting program\r\n"); // Print a string to UART2

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


	printf("Test string sent from STM32F4!!!\r\n"); // Print test string
	counter++;
}
