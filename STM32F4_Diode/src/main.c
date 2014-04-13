/**
 * @file: 	main.c
 * @brief:	Blinking LED test program with printf redirected to USART2
 * redirected to USART.
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
#include "timers.h"
#include "led.h"
#include "uart.h"

extern void Reset_Handler();

#define SYSTICK_FREQ 1000 ///< Frequency of the SysTick.

/**
 * Main function
 * @return Nothing
 */
int main(void) {

	UART2_Init(); // Initialize USART2 (for printf)
	TimerInit(SYSTICK_FREQ); // Initialize timer

	LED_TypeDef led;
	led.nr=LED0;
	led.gpio=GPIOD;
	led.pin=12;
	led.clk=RCC_AHB1Periph_GPIOD;

	LED_Add(&led); // Add an LED

//	char c;

	printf("Starting program\r\n");
	printf("Value: %08x\r\n", (unsigned int)Reset_Handler);

	while (1) {

		LED_Toggle(LED0); // Toggle LED
		LED_Toggle(LED1); // Toggle inexistent LED

//		c = USART2_Getc();
//		USART2_Putc(c);
		printf("Test string sent from STM32F4!!!\r\n"); // Print test string

		TimerDelay(2000); // Delay

	}

	return 0;
}




