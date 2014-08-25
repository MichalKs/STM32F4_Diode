/**
 * @file: 	led_hal.c
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

#include "led_hal.h"
#include <stm32f4xx.h>

static GPIO_TypeDef* ledPort[MAX_LEDS] = {
    GPIOD,
    GPIOD,
    GPIOD,
    GPIOD};

static uint32_t ledPin[MAX_LEDS] = {
    GPIO_Pin_12,
    GPIO_Pin_13,
    GPIO_Pin_14,
    GPIO_Pin_15};

static uint32_t ledClk[MAX_LEDS] = {
    RCC_AHB1Periph_GPIOD,
    RCC_AHB1Periph_GPIOD,
    RCC_AHB1Periph_GPIOD,
    RCC_AHB1Periph_GPIOD};

/**
 * @brief Add an LED.
 * @param led LED init structure.
 */
void LED_HAL_Init(uint8_t led) {

  RCC_AHB1PeriphClockCmd(ledClk[led], ENABLE);

  GPIO_InitTypeDef GPIO_InitStructure;

  // Configure pin in output push/pull mode
  GPIO_InitStructure.GPIO_Pin   = ledPin[led];
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // less interference
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;

  GPIO_Init(ledPort[led], &GPIO_InitStructure);

}

/**
 * @brief Toggle an LED.
 * @param led LED number.
 */
void LED_HAL_Toggle(uint8_t led) {

  ledPort[led]->ODR ^= ledPin[led];
}

/**
 * @brief Change the state of an LED.
 * @param led LED number.
 * @param state New state.
 */
void LED_HAL_ChangeState(uint8_t led, uint8_t state) {

  if (state == 1) {
    ledPort[led]->BSRRL = ledPin[led]; // set bit
  } else {
    ledPort[led]->BSRRH = ledPin[led]; // reset bit
  }

}
