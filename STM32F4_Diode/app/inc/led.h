/**
 * @file:   led.h
 * @brief:  Light Emitting Diode control functions.
 * @date:   9 kwi 2014
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

#ifndef LED_H_
#define LED_H_

#include <stm32f4xx.h>


/**
 * @defgroup  LED LED
 * @brief     Light Emitting Diode control functions.
 */

/**
 * @addtogroup LED
 * @{
 */

/**
 * @brief LED enum - for identifying an LED.
 */
typedef enum {
  LED0,//!< LED0
  LED1,//!< LED1
  LED2,//!< LED2
  LED3,//!< LED3
  LED4,//!< LED4
  LED5,//!< LED5
  LED6,//!< LED6
  LED7,//!< LED7
  LED8,//!< LED8
  LED9,//!< LED9

} LED_Number_TypeDef;

/**
 * @brief State of an LED.
 */
typedef enum {
  LED_UNUSED, //!< LED_UNUSED
  LED_OFF,    //!< LED_OFF Turn off LED
  LED_ON,     //!< LED_ON Turn on LED
} LED_State_TypeDef;


void LED_Init         (LED_Number_TypeDef led);
void LED_Toggle       (LED_Number_TypeDef led);
void LED_ChangeState  (LED_Number_TypeDef led, LED_State_TypeDef state);

/**
 * @}
 */

#endif /* LED_H_ */
