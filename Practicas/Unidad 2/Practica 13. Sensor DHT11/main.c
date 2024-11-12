/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "i2c.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd.h"
#include <stdio.h>
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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void delay (uint16_t time)
{
	__HAL_TIM_SET_COUNTER(&htim2, 0);
	while ((__HAL_TIM_GET_COUNTER(&htim2)) < time);
}

void Display_Temp (float Temp)
{
	char str[20] = {0};
	Lcd_Gotoxy(1, 1);

	sprintf(str, "TEMP:- %.2f ", Temp);
	Lcd_Print(str);
	Lcd_Print("C");
}

void Display_Rh (float Rh)
{
	char str[20] = {0};
	Lcd_Gotoxy(1, 2);

	sprintf(str, "RH:- %.2f ", Rh);
	Lcd_Print(str);
	Lcd_Print("%");
}

uint8_t Rh_byte1, Rh_byte2, Temp_byte1, Temp_byte2;
uint16_t SUM, RH, TEMP;

float Temperature = 0;
float Humidity = 0;
uint8_t Presence = 0;

void Set_Pin_Output (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void Set_Pin_Input (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

#define DHT11_PORT	GPIOA
#define DHT11_PIN	GPIO_PIN_1

void DHT11_Start (void)
{
	Set_Pin_Output (DHT11_PORT, DHT11_PIN);  		// poner el pin como salida
	HAL_GPIO_WritePin (DHT11_PORT, DHT11_PIN, 0);   // iniciar el pin en 0
	HAL_Delay(18);   								// esperar 18ms
    HAL_GPIO_WritePin (DHT11_PORT, DHT11_PIN, 1);   // poner el pin en 1
	delay(30);   									// esperar 20us
	Set_Pin_Input(DHT11_PORT, DHT11_PIN);    		// poner el pin como entrada
}

uint8_t DHT11_Check_Response (void){
	uint8_t Response = 0;

	delay(40);
	if (!(HAL_GPIO_ReadPin (DHT11_PORT, DHT11_PIN))){
		delay (80);
		if ((HAL_GPIO_ReadPin (DHT11_PORT, DHT11_PIN))){
			Response = 1;
			delay(40);
		}
	}
	//while ((HAL_GPIO_ReadPin (DHT11_PORT, DHT11_PIN)));   // esperar a que el pin vaya a bajo

	return Response;
}

uint8_t DHT11_Read (void){
	uint8_t i, j;

	for (j=0; j < 8; j++){
		while (!(HAL_GPIO_ReadPin (DHT11_PORT, DHT11_PIN)));   	// esperar a que el pin vaya a alto
		delay(40);   											// esperar 40 us
		if (!(HAL_GPIO_ReadPin (DHT11_PORT, DHT11_PIN))){   	// si el pin es bajo
			i &= ~(1 << (7 - j));   							// escribir 0
		}
		else
			i |= (1 << (7 - j));  								// si el pin es alto, escribir 1
		while ((HAL_GPIO_ReadPin (DHT11_PORT, DHT11_PIN)));  	// esperar a que el pin vaya a bajo
	}
	return i;
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
	MX_I2C1_Init();
	MX_TIM2_Init();
	/* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start(&htim2);
	Lcd_Init();
	Lcd_Gotoxy(1, 1);
	Lcd_Print("INICIANDO>>>>");
	HAL_Delay(2000);
	Lcd_Command(LIMPIARLCD);
	HAL_Delay(10);
	Lcd_Gotoxy(1, 1);
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1)
	{
		Display_Temp(Temperature);
		Display_Rh(Humidity);

		DHT11_Start();
		Presence = DHT11_Check_Response();
		if(Presence){
			Rh_byte1 = DHT11_Read ();
			Rh_byte2 = DHT11_Read ();
			Temp_byte1 = DHT11_Read ();
			Temp_byte2 = DHT11_Read ();
			SUM = DHT11_Read();
		}

		if(SUM == (Rh_byte1 + Rh_byte2 + Temp_byte1 + Temp_byte2)){
			TEMP = Temp_byte1;
			RH = Rh_byte1;

			Temperature = (float) TEMP;
			Humidity = (float) RH;
		}


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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
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
