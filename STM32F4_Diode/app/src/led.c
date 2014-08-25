/**
 * @file:   led.c
 * @brief:  Light Emitting Diode control functions.
 * @date:   9 kwi 2014
 * @author: Michal Ksiezopolski
 * 
 * @details This is a very simple library for controlling
 * LEDs.
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
 *
 */

#include <stdio.h>
#include <led.h>
#include <led_hal.h>

/**
 * @addtogroup LED
 * @{
 */

LED_State_TypeDef ledState[MAX_LEDS]; ///< States of the LEDs

/**
 * @brief Add an LED.
 * @param led LED init structure.
 */
void LED_Init(LED_Number_TypeDef led) {

  // Check if LED number is correct.
  if (led >= MAX_LEDS) {
    printf("Error: Incorrect LED number!\r\n");
    return;
  }

  LED_HAL_Init(led);
  ledState[led] = LED_OFF;
}
/**
 * @brief Change the state of an LED.
 * @param led LED number.
 * @param state New state.
 */
void LED_ChangeState(LED_Number_TypeDef led, LED_State_TypeDef state) {

  if (led >= MAX_LEDS) {
    printf("Error: Incorrect LED number!\r\n");
    return;
  }

  if (ledState[led] != LED_UNUSED) {
    if (state == LED_OFF) {
      LED_HAL_ChangeState(led, 0);
    } else if (state == LED_ON) {
      LED_HAL_ChangeState(led, 1);
    }
  }

  ledState[led] = state;
}

/**
 * @brief Toggle an LED.
 * @param led LED number.
 */
void LED_Toggle(LED_Number_TypeDef led) {

  if (led >= MAX_LEDS) {
    printf("Error: Incorrect LED number!\r\n");
    return;
  }

  if (ledState[led] != LED_UNUSED) {

    if (ledState[led] == LED_OFF) {
      ledState[led] = LED_ON;
    } else if (ledState[led] == LED_ON) {
      ledState[led]= LED_OFF;
    }
    LED_HAL_Toggle(led);

  }
}

/**
 * @}
 */
