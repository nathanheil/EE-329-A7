/*
 * uart.h
 *
 *  Created on: May 3, 2025
 *      Author: 16573
 */

#ifndef INC_UART_H_
#define INC_UART_H_

extern volatile uint8_t game_start;
void LPUART_init(void);
void LPUART_Print(const char *msg);
void LPUART_ESC_Splash(void);
void DrawPlayer(int row, int col, char symbol);

#endif /* INC_UART_H_ */
