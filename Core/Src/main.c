/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "crc.h"
#include "dma.h"
#include "i2c.h"
#include "usart.h"
#include "tim.h"
#include "gpio.h"
#include "app_x-cube-ai.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <math.h>
#include <stdio.h>
#include "MPU6050.h"
#include "BC20.h"
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
MPU6050_t MPU6050;
gps_msg gpsmsg;
BC20_Data_TypeDef BC20_GPS_Data;

extern float aiwindow_Ax[2000];
extern float aiwindow_Ay[2000];
extern float aiwindow_Az[2000];
extern float aiwindow_APitch[2000];
extern float aiwindow_Gx[2000];
extern float aiwindow_Gy[2000];
extern float aiwindow_Gz[2000];
extern float aiwindow_GPitch[2000];
uint8_t BC20flag = 0;
uint8_t Fallflag = 0;
uint8_t usart1_rx_flag = 0;
uint16_t usart1_rx_len = 0;

uint8_t usart1_dma_buffer[1024];
uint8_t usart1_rx_buffer[2048];

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

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
    MX_DMA_Init();
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_LPUART1_UART_Init();
  MX_CRC_Init();
  MX_USART1_UART_Init();
  MX_DMA_Init();
  MX_I2C2_Init();
  MX_TIM6_Init();
  MX_TIM7_Init();
  MX_X_CUBE_AI_Init();
  /* USER CODE BEGIN 2 */
    HAL_TIM_Base_Start_IT(&htim6);
    HAL_TIM_Base_Start_IT(&htim7);

    __HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);
    __HAL_UART_CLEAR_IDLEFLAG(&huart1);          	//清除串口1空闲中断标志位
    HAL_UART_Receive_DMA(&huart1, (uint8_t *)&usart1_dma_buffer, 1024);

    printf("6050初始化...\r\n");
    while (MPU6050_Init(&hi2c2) == 1); 						//初始化6050模块
    printf("6050初始化完毕\r\n");

    printf("BC20初始化...\r\n");
    BC20_Init();
    printf("BC20联网完毕\r\n");

    printf("BC20 GPS初始化...\r\n");
    BC20_GNSS_INIT();
    printf("BC20 GPS初始化完毕\r\n");


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    while (1)
    {
    /* USER CODE END WHILE */

  MX_X_CUBE_AI_Process();
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV6;
  RCC_OscInitStruct.PLL.PLLN = 85;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the peripherals clocks
  */
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_LPUART1
                              |RCC_PERIPHCLK_I2C2;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_PCLK1;
  PeriphClkInit.I2c2ClockSelection = RCC_I2C2CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* tim_baseHandle) //定时器触发中断
{
    int j=200;

    if(tim_baseHandle->Instance == htim7.Instance && BC20flag==1)
    {
        MPU6050_Read_All(&hi2c2, &MPU6050);
        int16_t i = 1999;
        while (i > 0)
        {
            aiwindow_Ax[i] = aiwindow_Ax[i - 1];
            aiwindow_Ay[i] = aiwindow_Ay[i - 1];
            aiwindow_Az[i] = aiwindow_Az[i - 1];
            aiwindow_APitch[i] = aiwindow_APitch[i - 1];

            aiwindow_Gx[i] = aiwindow_Gx[i - 1];
            aiwindow_Gy[i] = aiwindow_Gy[i - 1];
            aiwindow_Gz[i] = aiwindow_Gz[i - 1];
            aiwindow_GPitch[i] = aiwindow_GPitch[i - 1];

            i--;
        }

        aiwindow_Ax[0] = MPU6050.Ax;
        aiwindow_Ay[0] = MPU6050.Ay;
        aiwindow_Az[0] = MPU6050.Az;
        aiwindow_APitch[0] = atan2(aiwindow_Ax[0], aiwindow_Az[0]);
        aiwindow_Gx[0] = MPU6050.Gx;
        aiwindow_Gy[0] = MPU6050.Gy;
        aiwindow_Gz[0] = MPU6050.Gz;
        aiwindow_GPitch[0] = atan2(aiwindow_Gx[0], aiwindow_Gz[0]);
    }
    if(tim_baseHandle->Instance == htim6.Instance && BC20flag==1)
    {
        j--;
        if(j==0)
        {
            printf("发送GPS数据");
            j=200;
        }
        if(j==100)
        {
            BC20_SendMes(123,"Normal");
        }
    }


}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == GPIO_PIN_13)
    {

        HAL_GPIO_WritePin(RING_GPIO_Port,RING_Pin,GPIO_PIN_SET);
        //设置蜂鸣器的电平为低电平

        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_13);
    }
}

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
