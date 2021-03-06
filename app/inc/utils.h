/**
 * @file    utils.h
 * @brief   Utility and help functions.
 * @date    20 lip 2014
 * @author  Michal Ksiezopolski
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

#ifndef UTILS_H_
#define UTILS_H_

#include <inttypes.h>

/**
 * @defgroup  UTILS UTILS
 * @brief     Common utility functions and macros
 */

/**
 * @addtogroup UTILS
 * @{
 */

void      UTILS_Hexdump     (const uint8_t* buf, uint32_t length);
void      UTILS_HexdumpC    (const uint8_t const *buf, uint32_t length);
void      UTILS_Hexdump16C  (const uint16_t const *buf, uint32_t length);
uint32_t  UTILS_Ntohl       (uint32_t val);
uint8_t   UTILS_IsBigEndian (void);

/**
 * @}
 */

#endif /* UTILS_H_ */
