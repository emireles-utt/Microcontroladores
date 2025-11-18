/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define SYSCLK		72000000
#define PRESCALER	72

#define Do			523
#define Re			587
#define Mi			659
#define Fa			698
#define Sol			784
#define La			880
#define Si			988

#define T1			500
#define T2			100

#define MUSICSIZE	48
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
typedef struct{
	uint16_t freq;
	uint16_t time;
}SoundTypeDef;

const SoundTypeDef Music[MUSICSIZE] = {
	{Do, T1},
	{Do, T1},
	{Sol, T1},
	{Sol, T1},
	{La, T1},
	{La, T1},
	{Sol, T1},
	{0, T2},
	{Fa, T1},
	{Fa, T1},
	{Mi, T1},
	{Mi, T1},
	{Re, T1},
	{Re, T1},
	{Do, T1},
	{0, T2},
	{Do, T1},
	{Do, T1},
	{Sol, T1},
	{Sol, T1},
	{La, T1},
	{La, T1},
	{Sol, T1},
	{0, T2},
	{Fa, T1},
	{Fa, T1},
	{Mi, T1},
	{Mi, T1},
	{Re, T1},
	{Re, T1},
	{Do, T1},
	{0, T2},
	{Sol, T1},
	{Sol, T1},
	{Fa, T1},
	{Fa, T1},
	{Mi, T1},
	{Mi, T1},
	{Re, T1},
	{0, T2},
	{Sol, T1},
	{Sol, T1},
	{Fa, T1},
	{Fa, T1},
	{Mi, T1},
	{Mi, T1},
	{Re, T1},
	{0, T2},
};

int paso_sonido = 0;
char play_musica = 0;
int timer_sonido;
int sound_counter;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void sound(int freq, int time_ms){
	if(freq > 0){
		__HAL_TIM_SET_AUTORELOAD(&htim4, SYSCLK / PRESCALER / freq);
		__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, __HAL_TIM_GET_AUTORELOAD(&htim4) / 2);
	}else{
		__HAL_TIM_SET_AUTORELOAD(&htim4, 1000);
		__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);
	}
	__HAL_TIM_SET_COUNTER(&htim4, 0);
	timer_sonido = ((SYSCLK / PRESCALER / __HAL_TIM_GET_AUTORELOAD(&htim4)) * time_ms) / 1000;
	sound_counter = 0;
	HAL_TIM_PWM_Start_IT(&htim4, TIM_CHANNEL_1);
}

void Sonido_Init(void){
	paso_sonido = 0;
	play_musica = 1;
	sound(Music[paso_sonido].freq, Music[paso_sonido].time);
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim){
	if(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC4) != RESET){
			__HAL_TIM_CLEAR_IT(htim, TIM_IT_CC4);
			sound_counter++;

			if(sound_counter > timer_sonido){
				if(play_musica == 0){
					__HAL_TIM_DISABLE(htim);
				}else{
					// mientras el indice "paso_sonido" sea menor del total MUSICSIZE
					// de notas de la partitura
					if(paso_sonido < MUSICSIZE - 1){
						if(__HAL_TIM_GET_COMPARE(htim, TIM_CHANNEL_1) == 0){
							// pasamos a la siguiente nota a reproducir
							paso_sonido++;
							// reproducimos la frecuencia de la nota de la partitura
							sound(Music[paso_sonido].freq, Music[paso_sonido].time);
						}else{
							sound(0, 30);	// silencio durante 30 de tiempo
						}
					}else{
						play_musica = 0;
						__HAL_TIM_DISABLE(htim);
					}
				}
			}
			if(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC4OF) != RESET){
				__HAL_TIM_CLEAR_FLAG(htim, TIM_FLAG_CC4OF);
			}
		}
}
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
	MX_TIM4_Init();
	/* USER CODE BEGIN 2 */
	Sonido_Init();		// iniciamos los parametros que inician la melodia

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1)
	{
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
#ifdef USE_FULL_ASSERT
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
