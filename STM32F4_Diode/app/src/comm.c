/**
 * @file: 	comm.c
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

#include <comm.h>
#include <fifo.h>
// HAL
#include <uart2.h>

#define COMM_BUF_LEN     2048    ///< COMM buffer lengths
#define COMM_TERMINATOR '\n'     ///< COMM frame terminator character

static uint8_t rxBuffer[COMM_BUF_LEN]; ///< Buffer for received data.
static uint8_t txBuffer[COMM_BUF_LEN]; ///< Buffer for transmitted data.

static FIFO_TypeDef rxFifo; ///< RX FIFO
static FIFO_TypeDef txFifo; ///< TX FIFO

static uint8_t gotFrame;  ///< Nonzero signals a new frame (number of received frames)

#define COMM_HAL_Init     UART2_Init
#define COMM_HAL_TxEnable UART2_TxEnable

uint8_t COMM_TxCallback(uint8_t* c);
void    COMM_RxCallback(uint8_t c);

/**
 * @brief Initialize communication terminal interface.
 *
 * @param baud Required baud rate
 */
void COMM_Init(uint32_t baud) {

  COMM_HAL_Init(baud, COMM_RxCallback, COMM_TxCallback);

  // Initialize RX FIFO
  rxFifo.buf = rxBuffer;
  rxFifo.len = COMM_BUF_LEN;
  FIFO_Add(&rxFifo);

  // Initialize TX FIFO
  txFifo.buf = txBuffer;
  txFifo.len = COMM_BUF_LEN;
  FIFO_Add(&txFifo);

}

/**
 * @brief Send a char to USART2.
 * @param c Char to send.
 */
void COMM_Putc(uint8_t c) {

  FIFO_Push(&txFifo,c); // Put data in TX buffer
  COMM_HAL_TxEnable(); // Enable low level transmitter

}
/**
 * @brief Get a char from USART2
 * @return Received char.
 * @warning Blocking function!
 */
uint8_t COMM_Getc(void) {

  uint8_t c;

  while (FIFO_IsEmpty(&rxFifo) == 1); // wait until buffer is not empty
  // buffer not empty => char was received

//  USART_ITConfig(USART2, USART_IT_RXNE, DISABLE); // disable RX interrupt

  FIFO_Pop(&rxFifo,&c); // Get data from RX buffer

//  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); // enable RX interrupt

  return c;
}
/**
 * @brief Get a complete frame from USART2 (nonblocking)
 * @param buf Buffer for data (data will be null terminated for easier string manipulation)
 * @param len Length not including terminator character
 * @retval 0 Received frame
 * @retval 1 No frame in buffer
 * @retval 2
 */
uint8_t USART2_GetFrame(uint8_t* buf, uint8_t* len) {

  uint8_t c;
  *len = 0; // zero out length variable

  if (gotFrame) {

    while (1) {

      // no more data and terminator wasn't reached => error
      if (FIFO_IsEmpty(&rxFifo)) {
        *len = 0;
        return 2;
      }

      buf[(*len)++] =  FIFO_Pop(&rxFifo, &c);

      // if end of frame
      if (c == COMM_TERMINATOR) {
        (*len)--; // length without terminator character
        buf[*len] = 0; // USART terminator character converted to NULL terminator
        break;
      }

    }
    gotFrame--;
    return 0;

  } else {

    return 1;
  }

}

void COMM_RxCallback(uint8_t c) {
  uint8_t res = FIFO_Push(&rxFifo, c); // Put data in RX buffer

  // Checking res to ensure no buffer overflow occurred
  if ((c == COMM_TERMINATOR) && (res == 0)) {
    gotFrame++;
  }
}

uint8_t COMM_TxCallback(uint8_t* c) {

  if (FIFO_Pop(&txFifo, c) == 0) { // If buffer not empty
    return 1;
  } else {
    return 0;
  }

}



