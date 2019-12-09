#include "main.h"

#include "Led.h"
#include "Switch.h"
#include "ComPc.h"
#include "Speaker.h"
#include "Qspi.h"

#include "Gyro.h"
#include "LineSensorModule.h"

void SystemClock_Config(void);

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void) {
    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();
    /* Configure the system clock */
    SystemClock_Config();
    HAL_MspInit();

    Led* led = Led::getInstance();
    led->on(LedNumbers::TOP);

    Timer::start();

    ComPc* compc = ComPc::getInstance();
    compc->printf("Hello ArcticTern!\n");

    Switch* sw = Switch::getInstance();

    Speaker* speaker = Speaker::getInstance();
    speaker->playMusic(MusicNumber::KIRBY3_POWERON);

    Gyro* gyro = Gyro::getInstance();
    gyro->whoami();

    Qspi* qspi = Qspi::getInstance();
    // bool return_qspi = qspi->comManufactureDevice();
    // if (return_qspi) compc->printf("QSPI 1LINE Initialize Success!\n");
    // else compc->printf("XXX QSPI 1LINE Initialize Failed... XXX\n");

    compc->printf("%02X %02X %02X\n", qspi->comReadStatusRegister1(), qspi->comReadStatusRegister2(), qspi->comReadStatusRegister3());
    // qspi->comWriteEnable();
    // qspi->comWriteStatusRegister2(0x02);
    // compc->printf("%02X %02X %02X\n", qspi->comReadStatusRegister1(), qspi->comReadStatusRegister2(), qspi->comReadStatusRegister3());

    uint8_t qspidata[2];
    bool return_qspi = qspi->comManufactureDeviceQuad(qspidata);
    if (return_qspi) compc->printf("QSPI 4LINE Initialize Success!\n");
    else compc->printf("XXX QSPI 4LINE Initialize Failed... XXX\n");
    compc->printf("%02X %02X\n", qspidata[0], qspidata[1]);

    qspi->comGlobalBlockUnlock();

    uint8_t qspi_writedata[256];
    for (int i=0; i<256; ++i) {
        qspi_writedata[i] = i;
    }
    compc->printf("Erase: WriteEnable\n");
    qspi->comWriteEnable();
    compc->printf("Erase: BlockErase\n");
    qspi->comBlockErase(0x00);
    compc->printf("Erase: WaitUntilBusy\n");
    qspi->waitUntilBusy();
    
    compc->printf("Program: WriteEnable\n");
    qspi->comWriteEnable();
    compc->printf("Program: PageProgram\n");
    qspi->comQuadPageProgram(0x00, qspi_writedata);
    compc->printf("Program: WaitUntilBusy\n");
    qspi->waitUntilBusy();

    uint8_t qspi_blankdata[256];
    compc->printf("* QSPI Data\n");
    qspi->comFastReadData(0x0, qspi_blankdata, 256);
    for (int i=0; i<16; ++i) {
        compc->printf("%2d: %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X\n", i, qspi_blankdata[16*i], qspi_blankdata[16*i+1], qspi_blankdata[16*i+2], qspi_blankdata[16*i+3], qspi_blankdata[16*i+4], qspi_blankdata[16*i+5], qspi_blankdata[16*i+6], qspi_blankdata[16*i+7], qspi_blankdata[16*i+8], qspi_blankdata[16*i+9], qspi_blankdata[16*i+10], qspi_blankdata[16*i+11], qspi_blankdata[16*i+12], qspi_blankdata[16*i+13], qspi_blankdata[16*i+14], qspi_blankdata[16*i+15]);
    }

    LineSensorModule lm;
    lm.initialize(
        SPI3, GPIOC, GPIO_PIN_9,
        GPIOD, GPIO_PIN_15, EXTI15_10_IRQn,
        GPIOC, GPIO_PIN_8);

    HAL_Delay(1);
    led->on(LedNumbers::LED0);

    lm.configAutomatic();

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);
    HAL_GPIO_WritePin(GPIOH, GPIO_PIN_0, GPIO_PIN_SET);

    lm.readAllChannel();
    led->on(LedNumbers::LED1);

    float ang;

    led->off(LedNumbers::LED0);
    led->off(LedNumbers::LED1);
    led->off(LedNumbers::LED2);
    led->off(LedNumbers::LED3);
    led->off(LedNumbers::LED4);
    led->off(LedNumbers::LED5);
    led->off(LedNumbers::LED6);
    led->off(LedNumbers::LED7);

    while(1) {
        // HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
        // for(int i=0;i<100;++i) {}
        // HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);

        // led->on(LedNumbers::LED2);
        // HAL_Delay(100);

        // while(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_15) == 1);
        // led->on(LedNumbers::LED3);

        // lm.updateAllChannel();
        // led->on(LedNumbers::LED4);

        // for (int i=0; i<8; ++i) {
        //     compc->printf("%4d, ", lm.getSingleChannel(static_cast<LineSensorModuleNumber>(i)));
        // }
        // compc->printf("\n");
        ang = gyro->getTotalAngle();
        if (ang < 45) {
            led->off(LedNumbers::LED0);
            led->off(LedNumbers::LED1);
            led->off(LedNumbers::LED2);
            led->off(LedNumbers::LED3);
            led->off(LedNumbers::LED4);
            led->off(LedNumbers::LED5);
            led->off(LedNumbers::LED6);
            led->on(LedNumbers::LED7);
        } else if (ang < 90) {
            led->off(LedNumbers::LED0);
            led->off(LedNumbers::LED1);
            led->off(LedNumbers::LED2);
            led->off(LedNumbers::LED3);
            led->off(LedNumbers::LED4);
            led->off(LedNumbers::LED5);
            led->on(LedNumbers::LED6);
            led->off(LedNumbers::LED7);
        } else if (ang < 135) {
            led->off(LedNumbers::LED0);
            led->off(LedNumbers::LED1);
            led->off(LedNumbers::LED2);
            led->off(LedNumbers::LED3);
            led->off(LedNumbers::LED4);
            led->on(LedNumbers::LED5);
            led->off(LedNumbers::LED6);
            led->off(LedNumbers::LED7);
        } else if (ang < 180) {
            led->off(LedNumbers::LED0);
            led->off(LedNumbers::LED1);
            led->off(LedNumbers::LED2);
            led->off(LedNumbers::LED3);
            led->on(LedNumbers::LED4);
            led->off(LedNumbers::LED5);
            led->off(LedNumbers::LED6);
            led->off(LedNumbers::LED7);
        } else if (ang < 225) {
            led->off(LedNumbers::LED0);
            led->off(LedNumbers::LED1);
            led->off(LedNumbers::LED2);
            led->on(LedNumbers::LED3);
            led->off(LedNumbers::LED4);
            led->off(LedNumbers::LED5);
            led->off(LedNumbers::LED6);
            led->off(LedNumbers::LED7);
        } else if (ang < 270) {
            led->off(LedNumbers::LED0);
            led->off(LedNumbers::LED1);
            led->on(LedNumbers::LED2);
            led->off(LedNumbers::LED3);
            led->off(LedNumbers::LED4);
            led->off(LedNumbers::LED5);
            led->off(LedNumbers::LED6);
            led->off(LedNumbers::LED7);
        } else if (ang < 315) {
            led->off(LedNumbers::LED0);
            led->on(LedNumbers::LED1);
            led->off(LedNumbers::LED2);
            led->off(LedNumbers::LED3);
            led->off(LedNumbers::LED4);
            led->off(LedNumbers::LED5);
            led->off(LedNumbers::LED6);
            led->off(LedNumbers::LED7);
        } else {
            led->on(LedNumbers::LED0);
            led->off(LedNumbers::LED1);
            led->off(LedNumbers::LED2);
            led->off(LedNumbers::LED3);
            led->off(LedNumbers::LED4);
            led->off(LedNumbers::LED5);
            led->off(LedNumbers::LED6);
            led->off(LedNumbers::LED7);
        }

    }

    while (1) {
        if (sw->isPushing(SwitchNumbers::SW1)) {
            led->on(LedNumbers::LED0);
        } else {
            led->off(LedNumbers::LED0);
        }
        HAL_Delay(200);
    }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

    /** Configure the main internal regulator output voltage */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
    /** Initializes the CPU, AHB and APB busses clocks */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = 8;
    RCC_OscInitStruct.PLL.PLLN = 216;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 2;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }
    /** Activate the Over-Drive mode */
    if (HAL_PWREx_EnableOverDrive() != HAL_OK) {
        Error_Handler();
    }
    /** Initializes the CPU, AHB and APB busses clocks */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK) {
        Error_Handler();
    }
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_I2C1;
    PeriphClkInitStruct.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
    PeriphClkInitStruct.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
        Error_Handler();
    }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void) {
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    while(1) {
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
void assert_failed(uint8_t *file, uint32_t line) {
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
