/**
 * @file: 	keys.c
 * @brief:	   
 * @date: 	5 maj 2014
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


#include <keys.h>
#include <timers.h>
#include <stdio.h>
#include <keys_hal.h>

#ifndef DEBUG
  #define DEBUG
#endif

#ifdef DEBUG
  #define print(str, args...) printf("COMM--> "str"%s",##args,"\r")
  #define println(str, args...) printf("COMM--> "str"%s",##args,"\r\n")
#else
  #define print(str, args...) (void)0
  #define println(str, args...) (void)0
#endif


/**
 * Key structure typedef.
 */
typedef struct {
	uint8_t id;		///<
	void (*PressCallback)(void);
	void (*RepeatCallback)(void);
	uint16_t len;	///<
	uint16_t count;	///<
} KEY_TypeDef;


uint8_t currentColumn; ///< Selected keyboard column

void KEYS_Init(void) {

  KEYS_HAL_Init();
  currentColumn = 0;

  // select first column as default
  KEYS_HAL_SelectColumn(0);

}

void KEYS_Update(void) {

  int8_t row = KEYS_HAL_ReadRow();

  if (row != -1) {
    println("You pressed a key in row %d, column %d.", row, currentColumn);
  }

  currentColumn++;

  if (currentColumn == 4) {
    currentColumn = 0;
  }

  KEYS_HAL_SelectColumn(currentColumn);
  TIMER_Delay(50);

}


