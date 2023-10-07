/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_Pin GPIO_PIN_13
#define LED_GPIO_Port GPIOC
#define R_UP_R_Pin GPIO_PIN_0
#define R_UP_R_GPIO_Port GPIOA
#define R_UP_L_Pin GPIO_PIN_1
#define R_UP_L_GPIO_Port GPIOA
#define R_L_Y_Pin GPIO_PIN_4
#define R_L_Y_GPIO_Port GPIOA
#define R_L_X_Pin GPIO_PIN_5
#define R_L_X_GPIO_Port GPIOA
#define R_R_Y_Pin GPIO_PIN_6
#define R_R_Y_GPIO_Port GPIOA
#define R_R_X_Pin GPIO_PIN_7
#define R_R_X_GPIO_Port GPIOA
#define KEY_L_1_Pin GPIO_PIN_0
#define KEY_L_1_GPIO_Port GPIOB
#define KEY_L_2_Pin GPIO_PIN_1
#define KEY_L_2_GPIO_Port GPIOB
#define KEY_R_1_Pin GPIO_PIN_12
#define KEY_R_1_GPIO_Port GPIOB
#define KEY_R_2_Pin GPIO_PIN_13
#define KEY_R_2_GPIO_Port GPIOB
#define KEY_R_3_Pin GPIO_PIN_14
#define KEY_R_3_GPIO_Port GPIOB
#define SWITCH2_Pin GPIO_PIN_15
#define SWITCH2_GPIO_Port GPIOB
#define SWITCH1_Pin GPIO_PIN_8
#define SWITCH1_GPIO_Port GPIOA
#define LED2_Pin GPIO_PIN_9
#define LED2_GPIO_Port GPIOA
#define LED1_Pin GPIO_PIN_10
#define LED1_GPIO_Port GPIOA
#define SWITCH_TOTAL_Pin GPIO_PIN_11
#define SWITCH_TOTAL_GPIO_Port GPIOA
#define KEY_UP_L_Pin GPIO_PIN_12
#define KEY_UP_L_GPIO_Port GPIOA
#define KEY_L_4_Pin GPIO_PIN_15
#define KEY_L_4_GPIO_Port GPIOA
#define KEY_R_4_Pin GPIO_PIN_3
#define KEY_R_4_GPIO_Port GPIOB
#define KEY_UP_R_Pin GPIO_PIN_4
#define KEY_UP_R_GPIO_Port GPIOB
#define KEY_L_3_Pin GPIO_PIN_5
#define KEY_L_3_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
