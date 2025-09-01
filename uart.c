    /*
 * uart.c
 *
 *  Created on: May 3, 2025
 *      Author: 16573
 */
#include "stm32l4xx.h"
#include "uart.h"

void LPUART_init(void) {
    // power & clocks
    PWR->CR2   |= PWR_CR2_IOSV;
    RCC->AHB2ENR  |= RCC_AHB2ENR_GPIOGEN;
    RCC->APB1ENR2 |= RCC_APB1ENR2_LPUART1EN;

    // PG7/PG8 → AF8
    GPIOG->MODER  = (GPIOG->MODER & ~((3<<14)|(3<<16)))
                  |  ((2<<14)|(2<<16));
    GPIOG->AFR[0] = (GPIOG->AFR[0] & ~(0xF<<28)) | (8<<28);
    GPIOG->AFR[1] = (GPIOG->AFR[1] & ~(0xF<< 0)) | (8<< 0);
    GPIOG->OSPEEDR |= (3<<14)|(3<<16);
    GPIOG->OTYPER  &= ~(GPIO_OTYPER_OT7|GPIO_OTYPER_OT8);
    GPIOG->PUPDR   &= ~(GPIO_PUPDR_PUPD7|GPIO_PUPDR_PUPD8);

    // UART CR1/MSR
    LPUART1->CR1 &= ~USART_CR1_UE;                 // ← disable
    LPUART1->CR1 &= ~(USART_CR1_M1|USART_CR1_M0);  // 8-bit, no parity
    LPUART1->CR1 |=  (USART_CR1_TE|USART_CR1_RE);  // enable TX & RX

    RCC->CCIPR &= ~RCC_CCIPR_LPUART1SEL;
    RCC->CCIPR |= RCC_CCIPR_LPUART1SEL_0;
    LPUART1->BRR = 0x22b9;             //
    LPUART1->CR1 |= USART_CR1_UE;                  // ← enable last

    // interrupts (optional)
    LPUART1->CR1 |= USART_CR1_RXNEIE;
    NVIC->ISER[2] = 1 << (LPUART1_IRQn & 0x1F);
    __enable_irq();
}


void LPUART_Print( const char* message ) {
   uint16_t iStrIdx = 0;
   while ( message[iStrIdx] != 0 ) {
      while(!(LPUART1->ISR & USART_ISR_TXE)) // wait for empty xmit buffer
         ;
      LPUART1->TDR = message[iStrIdx];       // send this character
	iStrIdx++;                             // advance index to next char
   }
}
volatile int player_row = 12;
volatile int player_col = 40;
volatile uint8_t esc_seq_state = 0;

void DrawPlayer(int row, int col, char symbol) {
    char buf[20];
    sprintf(buf, "\x1B[%d;%dH%c", row, col, symbol);
    LPUART_Print(buf);
}


void LPUART1_IRQHandler( void  ) {
   uint8_t charRecv;
   if (LPUART1->ISR & USART_ISR_RXNE) {
      charRecv = LPUART1->RDR;


      // Handle VT100 arrow key sequences
           if (esc_seq_state == 0) {
               if (charRecv == 0x1B) {
                   esc_seq_state = 1;
                   return;
               }
           } else if (esc_seq_state == 1) {
               if (charRecv == '[') {
                   esc_seq_state = 2;
                   return;
               } else {
                   esc_seq_state = 0;
               }
           } else if (esc_seq_state == 2) {
               // Erase current player
               DrawPlayer(player_row, player_col, ' ');

               if (charRecv == 'A') {
                   player_row = (player_row <= 2) ? 23 : player_row - 1;   // up, wrap from top to bottom
               }
               else if (charRecv == 'B') {
                   player_row = (player_row >= 23) ? 2 : player_row + 1;   // down, wrap from bottom to top
               }
               else if (charRecv == 'C') {
                   player_col = (player_col >= 79) ? 2 : player_col + 1;   // right, wrap to left
               }
               else if (charRecv == 'D') {
                   player_col = (player_col <= 2) ? 79 : player_col - 1;   // left, wrap to right
               }

               DrawPlayer(player_row, player_col, '@');
               esc_seq_state = 0;
               return;
           }


		switch ( charRecv ) {
		       case 'R':
				   LPUART_Print("\x1B[31m");  // red
				   break;
			   case 'G':
				   LPUART_Print("\x1B[32m");  // green
				   break;
			   case 'B':
				   LPUART_Print("\x1B[34m");  // blue
				   break;
			   case 'W':
				   LPUART_Print("\x1B[0m");       // reset color
				   break;

			   case '\r':  // user presses Enter
			       game_start = 1;  // set flag to launch game
			       break;

				   break;
			 //  other ESCape code cases */
		default:
		  while( !(LPUART1->ISR & USART_ISR_TXE) )
               ;    // wait for empty TX buffer
		LPUART1->TDR = charRecv;  // echo char to terminal
	}  // end switch
   }
}

void LPUART_ESC_Splash(void) {
    LPUART_Print("\x1B[3B");
    LPUART_Print("\x1B[5C");
    LPUART_Print("All good students read the");

    LPUART_Print("\x1B[1B");
    LPUART_Print("\x1B[21D");
    LPUART_Print("\x1B[5m");
    LPUART_Print("Reference Manual");

    LPUART_Print("\x1B[H");
    LPUART_Print("\x1B[0m");
    LPUART_Print("Input: ");
}
