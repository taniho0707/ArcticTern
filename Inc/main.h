/**
  ******************************************************************************
  * File Name          : main.hpp
  * Description        : This file contains the common defines of the application
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
  /* Includes ------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define FlashIO2_Pin GPIO_PIN_2
#define FlashIO2_GPIO_Port GPIOE
#define Sensor7_CS_Pin GPIO_PIN_3
#define Sensor7_CS_GPIO_Port GPIOE
#define Sensor7_CNVST_Pin GPIO_PIN_4
#define Sensor7_CNVST_GPIO_Port GPIOE
#define Speaker_Pin GPIO_PIN_5
#define Speaker_GPIO_Port GPIOE
#define Motor1IN2_Pin GPIO_PIN_6
#define Motor1IN2_GPIO_Port GPIOE
#define Motor1IN1_Pin GPIO_PIN_13
#define Motor1IN1_GPIO_Port GPIOC
#define SW1_Pin GPIO_PIN_14
#define SW1_GPIO_Port GPIOC
#define SW2_Pin GPIO_PIN_15
#define SW2_GPIO_Port GPIOC
#define Motor2IN2_Pin GPIO_PIN_0
#define Motor2IN2_GPIO_Port GPIOC
#define Motor2IN1_Pin GPIO_PIN_1
#define Motor2IN1_GPIO_Port GPIOC
#define Motor3IN2_Pin GPIO_PIN_2
#define Motor3IN2_GPIO_Port GPIOC
#define Motor3IN1_Pin GPIO_PIN_3
#define Motor3IN1_GPIO_Port GPIOC
#define Encoder3A_Pin GPIO_PIN_0
#define Encoder3A_GPIO_Port GPIOA
#define Encoder3B_Pin GPIO_PIN_1
#define Encoder3B_GPIO_Port GPIOA
#define Motor1PWM_Pin GPIO_PIN_2
#define Motor1PWM_GPIO_Port GPIOA
#define Motor2PWM_Pin GPIO_PIN_3
#define Motor2PWM_GPIO_Port GPIOA
#define Motor4IN2_Pin GPIO_PIN_4
#define Motor4IN2_GPIO_Port GPIOA
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
#define GyroINT2_Pin GPIO_PIN_8
#define GyroINT2_GPIO_Port GPIOE
#define Encoder1A_Pin GPIO_PIN_9
#define Encoder1A_GPIO_Port GPIOE
#define Motor4IN1_Pin GPIO_PIN_10
#define Motor4IN1_GPIO_Port GPIOE
#define Encoder1B_Pin GPIO_PIN_11
#define Encoder1B_GPIO_Port GPIOE
#define GyroSCK_Pin GPIO_PIN_12
#define GyroSCK_GPIO_Port GPIOE
#define GyroMISO_Pin GPIO_PIN_13
#define GyroMISO_GPIO_Port GPIOE
#define GyroMOSI_Pin GPIO_PIN_14
#define GyroMOSI_GPIO_Port GPIOE
#define GyroCS_Pin GPIO_PIN_15
#define GyroCS_GPIO_Port GPIOE
#define FlashNCS_Pin GPIO_PIN_10
#define FlashNCS_GPIO_Port GPIOB
#define Sensor3_CS_Pin GPIO_PIN_11
#define Sensor3_CS_GPIO_Port GPIOB
#define Sensor3_CNVST_Pin GPIO_PIN_12
#define Sensor3_CNVST_GPIO_Port GPIOB
#define Sensor4_CS_Pin GPIO_PIN_8
#define Sensor4_CS_GPIO_Port GPIOD
#define Sensor4_CNVST_Pin GPIO_PIN_9
#define Sensor4_CNVST_GPIO_Port GPIOD
#define Sensor4_EOC_Pin GPIO_PIN_10
#define Sensor4_EOC_GPIO_Port GPIOD
#define FlashIO0_Pin GPIO_PIN_11
#define FlashIO0_GPIO_Port GPIOD
#define FlashIO1_Pin GPIO_PIN_12
#define FlashIO1_GPIO_Port GPIOD
#define FlashIO3_Pin GPIO_PIN_13
#define FlashIO3_GPIO_Port GPIOD
#define Sensor3_EOC_Pin GPIO_PIN_14
#define Sensor3_EOC_GPIO_Port GPIOD
#define Sensor5_EOC_Pin GPIO_PIN_15
#define Sensor5_EOC_GPIO_Port GPIOD
#define Encoder4A_Pin GPIO_PIN_6
#define Encoder4A_GPIO_Port GPIOC
#define Encoder4B_Pin GPIO_PIN_7
#define Encoder4B_GPIO_Port GPIOC
#define Sensor5_CNVST_Pin GPIO_PIN_8
#define Sensor5_CNVST_GPIO_Port GPIOC
#define Sensor5_CS_Pin GPIO_PIN_9
#define Sensor5_CS_GPIO_Port GPIOC
#define Sensor6_CS_Pin GPIO_PIN_8
#define Sensor6_CS_GPIO_Port GPIOA
#define UsartTx_Pin GPIO_PIN_9
#define UsartTx_GPIO_Port GPIOA
#define UsartRx_Pin GPIO_PIN_10
#define UsartRx_GPIO_Port GPIOA
#define Sensor6_CNVST_Pin GPIO_PIN_11
#define Sensor6_CNVST_GPIO_Port GPIOA
#define Sensor6_EOC_Pin GPIO_PIN_12
#define Sensor6_EOC_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWDCLK_Pin GPIO_PIN_14
#define SWDCLK_GPIO_Port GPIOA
#define Sensor2_CS_Pin GPIO_PIN_15
#define Sensor2_CS_GPIO_Port GPIOA
#define Sensor2_CNVST_Pin GPIO_PIN_0
#define Sensor2_CNVST_GPIO_Port GPIOD
#define Sensor2_EOC_Pin GPIO_PIN_1
#define Sensor2_EOC_GPIO_Port GPIOD
#define Sensor1_EOC_Pin GPIO_PIN_2
#define Sensor1_EOC_GPIO_Port GPIOD
#define Sensor1_CNVST_Pin GPIO_PIN_3
#define Sensor1_CNVST_GPIO_Port GPIOD
#define Sensor1_CS_Pin GPIO_PIN_4
#define Sensor1_CS_GPIO_Port GPIOD
#define Sensor8_EOC_Pin GPIO_PIN_5
#define Sensor8_EOC_GPIO_Port GPIOD
#define Sensor7_EOC_Pin GPIO_PIN_6
#define Sensor7_EOC_GPIO_Port GPIOD
#define Encoder2A_Pin GPIO_PIN_6
#define Encoder2A_GPIO_Port GPIOB
#define Encoder2B_Pin GPIO_PIN_7
#define Encoder2B_GPIO_Port GPIOB
#define Sensor8_CS_Pin GPIO_PIN_0
#define Sensor8_CS_GPIO_Port GPIOE
#define Sensor8_CNVST_Pin GPIO_PIN_1
#define Sensor8_CNVST_GPIO_Port GPIOE

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the 
  *        HAL drivers code
  */
/* #define USE_FULL_ASSERT    1U */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
 extern "C" {
#endif
void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#ifdef __cplusplus
}
#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MAIN_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
