/**
 * @file    uart6.h
 * @brief   Controlling UART6
 * @date    14.04.2016
 * @author  Michal Ksiezopolski
 * 
 * @verbatim
 * Copyright (c) 2016 Michal Ksiezopolski.
 * All rights reserved. This program and the 
 * accompanying materials are made available 
 * under the terms of the GNU Public License 
 * v3.0 which accompanies this distribution, 
 * and is available at 
 * http://www.gnu.org/licenses/gpl.html
 * @endverbatim
 */

#ifndef UART_H_
#define UART_H_

#include <inttypes.h>
#include <stm32f4xx_hal.h>

/**
 * @defgroup  UART6 UART6
 * @brief     UART6 low level functions
 */

/**
 * @addtogroup UART6
 * @{
 */

// Definition for USARTx clock resources
#define USARTx                           USART6
#define USARTx_CLK_ENABLE()              __HAL_RCC_USART6_CLK_ENABLE()
#define USARTx_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOC_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOC_CLK_ENABLE()

#define USARTx_FORCE_RESET()             __HAL_RCC_USART6_FORCE_RESET()
#define USARTx_RELEASE_RESET()           __HAL_RCC_USART6_RELEASE_RESET()

// Definition for USARTx Pins
#define USARTx_TX_PIN                    GPIO_PIN_6
#define USARTx_TX_GPIO_PORT              GPIOC
#define USARTx_TX_AF                     GPIO_AF8_USART6
#define USARTx_RX_PIN                    GPIO_PIN_7
#define USARTx_RX_GPIO_PORT              GPIOC
#define USARTx_RX_AF                     GPIO_AF8_USART6

// Definition for USARTx's NVIC
#define USARTx_IRQn                      USART6_IRQn
#define USARTx_IRQHandler                USART6_IRQHandler

#define UART_BUF_LEN_TX 64 ///< Buffer length for UART peripheral

// HAL functions for use in higher level
#define COMM_HAL_Init         UART6_Init
#define COMM_HAL_TxEnable()   UART6_SendData()
#define COMM_HAL_IsTxActive() UART6_IsSendingData()
#define COMM_HAL_IrqEnable()  HAL_NVIC_EnableIRQ(USARTx_IRQn);
#define COMM_HAL_IrqDisable() HAL_NVIC_DisableIRQ(USARTx_IRQn);

void    UART6_Init(int baud, void(*rxCb)(char), int(*txCb)(char*));
int     UART6_IsSendingData(void);
void    UART6_SendData(void);

/**
 * @}
 */

#endif /* UART_H_ */
