/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
#include "stm32f7xx_hal.h"

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
#define FlashIO2_Pin GPIO_PIN_2
#define FlashIO2_GPIO_Port GPIOE
#define Sensor6_CS_Pin GPIO_PIN_3
#define Sensor6_CS_GPIO_Port GPIOE
#define Sensor6_CNVST_Pin GPIO_PIN_4
#define Sensor6_CNVST_GPIO_Port GPIOE
#define Speaker_Pin GPIO_PIN_5
#define Speaker_GPIO_Port GPIOE
#define Motor1IN2_Pin GPIO_PIN_6
#define Motor1IN2_GPIO_Port GPIOE
#define Motor1IN1_Pin GPIO_PIN_13
#define Motor1IN1_GPIO_Port GPIOC
#define SW2_Pin GPIO_PIN_14
#define SW2_GPIO_Port GPIOC
#define SW1_Pin GPIO_PIN_15
#define SW1_GPIO_Port GPIOC
#define SENSOR_LED_EN_Pin GPIO_PIN_0
#define SENSOR_LED_EN_GPIO_Port GPIOH
#define ONE_WIRE_Pin GPIO_PIN_1
#define ONE_WIRE_GPIO_Port GPIOH
#define Motor2IN2_Pin GPIO_PIN_0
#define Motor2IN2_GPIO_Port GPIOC
#define Motor2IN1_Pin GPIO_PIN_1
#define Motor2IN1_GPIO_Port GPIOC
#define Motor3IN2_Pin GPIO_PIN_2
#define Motor3IN2_GPIO_Port GPIOC
#define Motor3IN1_Pin GPIO_PIN_3
#define Motor3IN1_GPIO_Port GPIOC
#define Encoder2A_Pin GPIO_PIN_0
#define Encoder2A_GPIO_Port GPIOA
#define Encoder2B_Pin GPIO_PIN_1
#define Encoder2B_GPIO_Port GPIOA
#define Motor1PWM_Pin GPIO_PIN_2
#define Motor1PWM_GPIO_Port GPIOA
#define Motor2PWM_Pin GPIO_PIN_3
#define Motor2PWM_GPIO_Port GPIOA
#define Motor4IN2_Pin GPIO_PIN_4
#define Motor4IN2_GPIO_Port GPIOA
#define Sensor56_SCK_Pin GPIO_PIN_5
#define Sensor56_SCK_GPIO_Port GPIOA
#define Sensor56_MISO_Pin GPIO_PIN_6
#define Sensor56_MISO_GPIO_Port GPIOA
#define Sensor56_MOSI_Pin GPIO_PIN_7
#define Sensor56_MOSI_GPIO_Port GPIOA
#define Bat_Pin GPIO_PIN_4
#define Bat_GPIO_Port GPIOC
#define Bat3V3_Pin GPIO_PIN_5
#define Bat3V3_GPIO_Port GPIOC
#define Motor3PWM_Pin GPIO_PIN_0
#define Motor3PWM_GPIO_Port GPIOB
#define Motor4PWM_Pin GPIO_PIN_1
#define Motor4PWM_GPIO_Port GPIOB
#define FlashCLK_Pin GPIO_PIN_2
#define FlashCLK_GPIO_Port GPIOB
#define GyroINT1_Pin GPIO_PIN_7
#define GyroINT1_GPIO_Port GPIOE
#define GyroINT1_EXTI_IRQn EXTI9_5_IRQn
#define GyroINT2_Pin GPIO_PIN_8
#define GyroINT2_GPIO_Port GPIOE
#define GyroINT2_EXTI_IRQn EXTI9_5_IRQn
#define Encoder1A_Pin GPIO_PIN_9
#define Encoder1A_GPIO_Port GPIOE
#define Motor4IN1_Pin GPIO_PIN_10
#define Motor4IN1_GPIO_Port GPIOE
#define Encoder1B_Pin GPIO_PIN_11
#define Encoder1B_GPIO_Port GPIOE
#define Gyro_SCK_Pin GPIO_PIN_12
#define Gyro_SCK_GPIO_Port GPIOE
#define Gyro_MISO_Pin GPIO_PIN_13
#define Gyro_MISO_GPIO_Port GPIOE
#define Gyro_MOSI_Pin GPIO_PIN_14
#define Gyro_MOSI_GPIO_Port GPIOE
#define Gyro_CS_Pin GPIO_PIN_15
#define Gyro_CS_GPIO_Port GPIOE
#define FlashNCS_Pin GPIO_PIN_10
#define FlashNCS_GPIO_Port GPIOB
#define Sensor7_CS_Pin GPIO_PIN_11
#define Sensor7_CS_GPIO_Port GPIOB
#define Sensor7_CNVST_Pin GPIO_PIN_12
#define Sensor7_CNVST_GPIO_Port GPIOB
#define Sensor78_SCK_Pin GPIO_PIN_13
#define Sensor78_SCK_GPIO_Port GPIOB
#define Sensor78_MISO_Pin GPIO_PIN_14
#define Sensor78_MISO_GPIO_Port GPIOB
#define Sensor78_MOSI_Pin GPIO_PIN_15
#define Sensor78_MOSI_GPIO_Port GPIOB
#define Sensor8_CS_Pin GPIO_PIN_8
#define Sensor8_CS_GPIO_Port GPIOD
#define Sensor8_CNVST_Pin GPIO_PIN_9
#define Sensor8_CNVST_GPIO_Port GPIOD
#define Sensor8_EOC_Pin GPIO_PIN_10
#define Sensor8_EOC_GPIO_Port GPIOD
#define Sensor8_EOC_EXTI_IRQn EXTI15_10_IRQn
#define FlashIO0_Pin GPIO_PIN_11
#define FlashIO0_GPIO_Port GPIOD
#define FlashIO1_Pin GPIO_PIN_12
#define FlashIO1_GPIO_Port GPIOD
#define FlashIO3_Pin GPIO_PIN_13
#define FlashIO3_GPIO_Port GPIOD
#define Sensor7_EOC_Pin GPIO_PIN_14
#define Sensor7_EOC_GPIO_Port GPIOD
#define Sensor7_EOC_EXTI_IRQn EXTI15_10_IRQn
#define Sensor1_EOC_Pin GPIO_PIN_15
#define Sensor1_EOC_GPIO_Port GPIOD
#define Sensor1_EOC_EXTI_IRQn EXTI15_10_IRQn
#define Encoder4A_Pin GPIO_PIN_6
#define Encoder4A_GPIO_Port GPIOC
#define Encoder4B_Pin GPIO_PIN_7
#define Encoder4B_GPIO_Port GPIOC
#define Sensor1_CNVST_Pin GPIO_PIN_8
#define Sensor1_CNVST_GPIO_Port GPIOC
#define Sensor1_CS_Pin GPIO_PIN_9
#define Sensor1_CS_GPIO_Port GPIOC
#define Sensor2_CS_Pin GPIO_PIN_8
#define Sensor2_CS_GPIO_Port GPIOA
#define UsartTx_Pin GPIO_PIN_9
#define UsartTx_GPIO_Port GPIOA
#define UsartRx_Pin GPIO_PIN_10
#define UsartRx_GPIO_Port GPIOA
#define Sensor2_CNVST_Pin GPIO_PIN_11
#define Sensor2_CNVST_GPIO_Port GPIOA
#define Sensor2_EOC_Pin GPIO_PIN_12
#define Sensor2_EOC_GPIO_Port GPIOA
#define Sensor2_EOC_EXTI_IRQn EXTI15_10_IRQn
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWDCLK_Pin GPIO_PIN_14
#define SWDCLK_GPIO_Port GPIOA
#define Sensor3_CS_Pin GPIO_PIN_15
#define Sensor3_CS_GPIO_Port GPIOA
#define Sensor12_SCK_Pin GPIO_PIN_10
#define Sensor12_SCK_GPIO_Port GPIOC
#define Sensor12_MISO_Pin GPIO_PIN_11
#define Sensor12_MISO_GPIO_Port GPIOC
#define Sensor12_MOSI_Pin GPIO_PIN_12
#define Sensor12_MOSI_GPIO_Port GPIOC
#define Sensor3_CNVST_Pin GPIO_PIN_0
#define Sensor3_CNVST_GPIO_Port GPIOD
#define Sensor3_EOC_Pin GPIO_PIN_1
#define Sensor3_EOC_GPIO_Port GPIOD
#define Sensor3_EOC_EXTI_IRQn EXTI1_IRQn
#define Sensor4_EOC_Pin GPIO_PIN_2
#define Sensor4_EOC_GPIO_Port GPIOD
#define Sensor4_EOC_EXTI_IRQn EXTI2_IRQn
#define Sensor4_CNVST_Pin GPIO_PIN_3
#define Sensor4_CNVST_GPIO_Port GPIOD
#define Sensor4_CS_Pin GPIO_PIN_4
#define Sensor4_CS_GPIO_Port GPIOD
#define Sensor6_EOC_Pin GPIO_PIN_5
#define Sensor6_EOC_GPIO_Port GPIOD
#define Sensor6_EOC_EXTI_IRQn EXTI9_5_IRQn
#define Sensor5_EOC_Pin GPIO_PIN_6
#define Sensor5_EOC_GPIO_Port GPIOD
#define Sensor5_EOC_EXTI_IRQn EXTI9_5_IRQn
#define Sensor34_MOSI_Pin GPIO_PIN_7
#define Sensor34_MOSI_GPIO_Port GPIOD
#define Sensor34_SCK_Pin GPIO_PIN_3
#define Sensor34_SCK_GPIO_Port GPIOB
#define Sensor34_MISO_Pin GPIO_PIN_4
#define Sensor34_MISO_GPIO_Port GPIOB
#define LED_Pin GPIO_PIN_5
#define LED_GPIO_Port GPIOB
#define Encoder3A_Pin GPIO_PIN_6
#define Encoder3A_GPIO_Port GPIOB
#define Encoder3B_Pin GPIO_PIN_7
#define Encoder3B_GPIO_Port GPIOB
#define Sensor5_CS_Pin GPIO_PIN_0
#define Sensor5_CS_GPIO_Port GPIOE
#define Sensor5_CNVST_Pin GPIO_PIN_1
#define Sensor5_CNVST_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
