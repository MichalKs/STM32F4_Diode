/**
 * @file    main.c
 * @brief   LED test
 * @date    9 kwi 2014
 * @author  Michal Ksiezopolski
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

#include <stdio.h>
#include <string.h>
#include "common_hal.h"
#include "timers.h"
#include "comm.h"
#include "led.h"

#define DEBUG

#ifdef DEBUG
#define print(str, args...) printf(""str"%s",##args,"")
#define println(str, args...) printf("MAIN--> "str"%s",##args,"\r\n")
#else
#define print(str, args...) (void)0
#define println(str, args...) (void)0
#endif

#define COMM_BAUD_RATE 115200UL ///< Baud rate for communication with PC

/**
 * @brief Callback for performing periodic tasks
 */
void softTimerCallback(void) {
  LED_Toggle(_LED2);
  println("Hello world!");
}

/**
  * @brief  Main program
  */
int main(void) {

  COMMON_HAL_Init();

  COMM_Init(COMM_BAUD_RATE);
  println("Starting program"); // Print a string to terminal

  LED_Init(_LED0); // Add an LED
  LED_Init(_LED1); // Add an LED
  LED_Init(_LED2); // Add an LED

  // Add a soft timer with callback running every 1000ms
  int8_t timerID = TIMER_AddSoftTimer(500, softTimerCallback);
  TIMER_StartSoftTimer(timerID); // start the timer

  uint8_t buf[64]; // buffer for receiving commands from PC
  uint8_t len;      // length of command
  while (1) {
    // check for new frames from PC
    if (!COMM_GetFrame(buf, &len)) {
      println("Got frame of length %d: %s", (int)len, (char*)buf);

      // control LED0 from terminal
      if (!strcmp((char*)buf, ":LED 0 ON")) {
        LED_ChangeState(_LED0, LED_ON);
      }
      if (!strcmp((char*)buf, ":LED 0 OFF")) {
        LED_ChangeState(_LED0, LED_OFF);
      }
      if (!strcmp((char*)buf, ":LED 1 ON")) {
        LED_ChangeState(_LED1, LED_ON);
      }
      if (!strcmp((char*)buf, ":LED 1 OFF")) {
        LED_ChangeState(_LED1, LED_OFF);
      }
    }

    TIMER_SoftTimersUpdate();
  }
}


//int main(void) {

////  KEYS_Init(); // Initialize matrix keyboard
//
//
//  // test another way of measuring time delays
//  uint32_t softTimer = TIMER_GetTime(); // get start time for delay

//  while (1) {

    // test delay method
//    if (TIMER_DelayTimer(1000, softTimer)) {
//      LED_Toggle(LED3);
//      softTimer = TIMER_GetTime(); // get start time for delay
//    }
//

//
////    KEYS_Update(); // run keyboard
//  }
//}

