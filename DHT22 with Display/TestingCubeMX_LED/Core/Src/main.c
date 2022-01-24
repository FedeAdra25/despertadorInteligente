/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "MY_DHT22.h"
#include <stdio.h>
#include "gp_drive.h"
#include "systick_time.h"
#include "SPI_Drive.h"
#include "n5110_drive.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
float Temperature, Humidity;

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
	

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
	
  /* USER CODE BEGIN 2 */

	/* AUX VARIABLES */
	char buf[50];
	char onMsg[] = "ON\n\r";
	char offMsg[] = "OFF\n\r";
	int dayCounter = 0;
	
	unsigned char n5110_buffer[6][84];	//6 Rows 84 Columns
	

	
	/*Systick Init*/
	//systick_init();	//For some reason, this crashes everything 
	
	/*DHT22 Init*/
	DHT22_Init(GPIOB, GPIO_PIN_15);
	
	/* SPI 1 Init*/
	spi_init(1);
	
	/* N5110 Init */
	n5110_init(1);
	
	/* DISPLAY IMAGES*/
	/* INDEX 
			0 = NO-DAY-SELECTED
			1 = LUNES
			2 = MARTES
			3 = MIERCOLES
			4 = JUEVES
			5 = VIERNES
			6 = SABADO
			7 = DOMINGO
	*/
	ImgType display_pic = {.h = display_rows, .w = display_cols, .x = 0, .y = 0};
	display_pic.image[0] = display;
	display_pic.image[1] = display_lunes;
	display_pic.image[2] = display_martes;
	display_pic.image[3] = display_miercoles;
	display_pic.image[4] = display_jueves;
	display_pic.image[5] = display_viernes;
	display_pic.image[6] = display_sabado;
	display_pic.image[7] = display_domingo;
	
	/*Welcome Screen */
	ImgType welcome_pic = {.h = welcome_screen_rows, .w = welcome_screen_cols, .x = 0, .y = 0};
	welcome_pic.image[0] = welcome_screen;
	
	
	
	
	n5110_clear();
	n5110_clear_buffer(n5110_buffer);
	
	/* Welcome Screen 5 seconds delay */
	n5110_update_buffer(welcome_pic, 0, n5110_buffer);
	HAL_Delay(1000);
	n5110_print_buffer(n5110_buffer);
	HAL_Delay(5000);
	
	n5110_update_buffer(display_pic, 0, n5110_buffer);
	/* MEMO: Con el update str buffer podes agregar una string 
	si el fondo no tiene nada. 
	Asi que podemos poner la hora, abajo la temperatura y humedad por separado.
		Y despues hacer el Clear de todo junto y repetir*/

	
	
	
	
	//La lectura queda en bucle infinito. Solo puedo leeer el DHT22 una UNICA vez. Sad
	if (DHT22_GetTemp_Humidity(&Temperature,&Humidity) == 1 ){
	sprintf(buf, "T %.1f H %.1f%%", Temperature, Humidity);
	HAL_UART_Transmit(&huart1,(uint8_t *)buf,strlen(buf),HAL_MAX_DELAY);
	HAL_Delay(1000);
	}
	
	n5110_update_str_buffer(1,6,buf,n5110_buffer);
	n5110_update_str_buffer(3,20,"HH:MM:SS",n5110_buffer);
	
	n5110_print_buffer(n5110_buffer);
	
	
	

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		

		/*
		//Old Display Code
		n5110_print(0,0,buf,1);
		HAL_Delay(5000); //Delay of 5s because Simulator
		toggle_GP(PA,2);
		*/
		
		
		
		//DelayMs(50);
		HAL_Delay(1000);
		
			if (DHT22_GetTemp_Humidity(&Temperature,&Humidity) == 1 ){
	sprintf(buf, "T %.1f H %.1f%%", Temperature, Humidity);
	HAL_UART_Transmit(&huart1,(uint8_t *)buf,strlen(buf),HAL_MAX_DELAY);
	HAL_Delay(1000);
	}
		
		/*
		spi_tx(1,'H');
		spi_tx(1,'e');
		spi_tx(1,'l');
		spi_tx(1,'l');
		spi_tx(1,'o');
		*/
		
		/* spi_msg(1,"Hello Dude"); */
		
		
		
		/* Enciendo y apago el LED PC13 indefinidamente*/
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);
		HAL_UART_Transmit(&huart1,(uint8_t *)onMsg,strlen(onMsg),HAL_MAX_DELAY);
		HAL_Delay(1000);

		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_RESET);
		HAL_UART_Transmit(&huart1,(uint8_t *)offMsg,strlen(offMsg),HAL_MAX_DELAY);
		HAL_Delay(1000);


		
		
		
		

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12|TANGO_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LED2_Pin */
  GPIO_InitStruct.Pin = LED2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PB15 */
  GPIO_InitStruct.Pin = GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PA12 TANGO_LED_Pin */
  GPIO_InitStruct.Pin = GPIO_PIN_12|TANGO_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
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

