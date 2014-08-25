/**
 * @file: 	systick.c
 * @brief:	   
 * @date: 	25 sie 2014
 * @author: Michal Ksiezopolski
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

#include <systick.h>
#include <stm32f4xx.h>

static uint32_t sysTicks;  ///< Delay timer.

void SYSTICK_Init(uint32_t freq) {

  RCC_ClocksTypeDef RCC_Clocks;

  RCC_GetClocksFreq(&RCC_Clocks); // Complete the clocks structure with current clock settings.

  SysTick_Config(RCC_Clocks.HCLK_Frequency / freq); // Set SysTick frequency

}

/**
 * @brief Interrupt handler for SysTick.
 */
void SysTick_Handler(void) {

  sysTicks++; // Update system time

}

uint32_t SYSTICK_GetTime(void) {
  return sysTicks;
}
