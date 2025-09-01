/* -------------------------------------------------------------------------
 * delay.c
 *
 * Microsecond Delay using SysTick Timer
 *
 * Author : Nathan Heil
 * Date   : 2025-04-19
 * Target : STM32L4A6ZG Nucleo Board
 * ------------------------------------------------------------------------- */

#include "delay.h"
#include "stm32l4xx.h"

void SysTick_Init(void) {
   SysTick->CTRL |= (SysTick_CTRL_ENABLE_Msk |
                     SysTick_CTRL_CLKSOURCE_Msk);
   SysTick->CTRL &= ~(SysTick_CTRL_TICKINT_Msk);
}

void DelayUs(uint32_t time_us) {
   SysTick->LOAD = (time_us * (SystemCoreClock / 1000000)) - 1;
   SysTick->VAL = 0;
   while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));
}
