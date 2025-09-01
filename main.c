/* -------------------------------------------------------------------------
 * main.c
 *
 * Main program for EE 329 UART terminal splash game.
 *
 * Author : Nathan Heil
 * Date   : 2025-05-07
 * Target : STM32L4A6ZG Nucleo Board
 * ------------------------------------------------------------------------- */


#include "main.h"
#include "uart.h"
#include "delay.h"

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
volatile uint8_t game_start = 0;

extern volatile int player_row;
extern volatile int player_col;

void DrawGameBox(void) {
    for (int col = 1; col <= 80; col++) {
        // Top and bottom borders
        char top[20], bottom[20];
        sprintf(top, "\x1B[1;%dH#", col);     // row 1
        sprintf(bottom, "\x1B[24;%dH#", col); // row 24
        LPUART_Print(top);
        LPUART_Print(bottom);
    }

    for (int row = 2; row < 24; row++) {
        // Left and right borders
        char left[20], right[20];
        sprintf(left, "\x1B[%d;1H#", row);     // col 1
        sprintf(right, "\x1B[%d;80H#", row);   // col 80
        LPUART_Print(left);
        LPUART_Print(right);
    }
}
int main(void){

	HAL_Init();             //  run HAL first
	SystemClock_Config();   //  set clocks
	MX_GPIO_Init();         //  setup GPIOs (includes AF config)
	LPUART_init();



	LPUART_Print("\x1B[2J");       // clear screen
	LPUART_Print("\x1B[H");        // move to top-left
	LPUART_ESC_Splash();
	 while (!game_start);  // wait here until user presses Enter
	    LPUART_Print("\x1B[2J");  // Clear screen
	    LPUART_Print("\x1B[H");   // Cursor home

	    LPUART_Print("\x1B[32m");      // Bright green (classic terminal vibe)

	        LPUART_Print(" ███████╗██╗  ██╗ █████╗ ██╗     ██╗     \r\n");
	        LPUART_Print(" ██╔════╝██║  ██║██╔══██╗██║     ██║     \r\n");
	        LPUART_Print(" ███████╗███████║███████║██║     ██║     \r\n");
	        LPUART_Print(" ╚════██║██╔══██║██╔══██║██║     ██║     \r\n");
	        LPUART_Print(" ███████║██║  ██║██║  ██║███████╗███████╗\r\n");
	        LPUART_Print(" ╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝╚══════╝\r\n");
	        LPUART_Print("\r\n");

	        LPUART_Print(" ██     ██ ███████     ██████╗ ██╗      █████╗ ██╗   ██╗\r\n");
	        LPUART_Print(" ██     ██ ██╔════     ██╔══██╗██║     ██╔══██╗╚██╗ ██╔╝\r\n");
	        LPUART_Print(" ██  █  ██ █████╗      ██████╔╝██║     ███████║ ╚████╔╝ \r\n");
	        LPUART_Print(" ██ ███ ██ ██╔══╝      ██╔═══╝ ██║     ██╔══██║  ╚██╔╝  \r\n");
	        LPUART_Print("  ███ ███  ███████╗    ██║     ███████╗██║  ██║   ██║   \r\n");
	        LPUART_Print("   ╚═╝╚═╝  ╚══════╝    ╚═╝     ╚══════╝╚═╝  ╚═╝   ╚═╝   \r\n");
	        LPUART_Print("\r\n");

	        LPUART_Print(" █████╗     ██████╗  █████╗ ███╗   ███╗███████╗    \r\n");
	        LPUART_Print("██╔══██╗   ██╔════╝ ██╔══██╗████╗ ████║██╔════╝    \r\n");
	        LPUART_Print("███████║   ██║  ███╗███████║██╔████╔██║█████╗        \r\n");
	        LPUART_Print("██╔══██║   ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝       \r\n");
	        LPUART_Print("██║  ██║   ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗    \r\n");
	        LPUART_Print("╚═╝  ╚═╝    ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝    \r\n");


	        LPUART_Print("\x1B[0m");  // Reset text attributes

	        DelayUs(45000000);
	        DelayUs(10000000);

	        LPUART_Print("\x1B[2J");  // Clear screen
	        DrawGameBox();
	       	LPUART_Print("\x1B[H");   // Cursor home

	       	LPUART_Print("\033[?25l");

	       	player_row = 12;
	       	player_col = 40;
	       	DrawPlayer(player_row, player_col, '@');

  while (1)
  {

  }
}


void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  HAL_PWREx_EnableVddIO2();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LD3_Pin|LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(USB_PowerSwitchOn_GPIO_Port, USB_PowerSwitchOn_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD3_Pin LD2_Pin */
  GPIO_InitStruct.Pin = LD3_Pin|LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_OverCurrent_Pin */
  GPIO_InitStruct.Pin = USB_OverCurrent_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USB_OverCurrent_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_PowerSwitchOn_Pin */
  GPIO_InitStruct.Pin = USB_PowerSwitchOn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(USB_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : STLK_RX_Pin STLK_TX_Pin */
  GPIO_InitStruct.Pin = STLK_RX_Pin|STLK_TX_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF8_LPUART1;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : USB_SOF_Pin USB_ID_Pin USB_DM_Pin USB_DP_Pin */
  GPIO_InitStruct.Pin = USB_SOF_Pin|USB_ID_Pin|USB_DM_Pin|USB_DP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF10_OTG_FS;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}


void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

