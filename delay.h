/* -------------------------------------------------------------------------
 * delay.h
 *
 * Microsecond Delay using SysTick Timer
 *
 * Author : Nathan Heil
 * Date   : 2025-04-19
 * Target : STM32L4A6ZG Nucleo Board
 * ------------------------------------------------------------------------- */

#ifndef INC_DELAY_H_
#define INC_DELAY_H_

#include <stdint.h>

void SysTick_Init(void);
void DelayUs(uint32_t time_us);

#endif /* INC_DELAY_H_ */
