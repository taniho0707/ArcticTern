#include "main.h"
#include "stm32f7xx_hal.h"


int main(void) {
	HAL_Init();
	SystemClock_Config();

	// LED
	{
		__HAL_RCC_GPIOB_CLK_ENABLE();
		GPIO_InitTypeDef GPIO_InitStruct;
		GPIO_InitStruct.Pin = GPIO_PIN_5;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
	}

	// Speaker
	{
		__HAL_RCC_GPIOE_CLK_ENABLE();
		GPIO_InitTypeDef GPIO_InitStruct;
		GPIO_InitStruct.Pin = GPIO_PIN_5;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_SET);
	}

	// Motor2
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();
		__HAL_RCC_GPIOC_CLK_ENABLE();
		GPIO_InitTypeDef GPIO_InitStruct;
		GPIO_InitStruct.Pin = GPIO_PIN_3;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);

		GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);

		for (int i=0; i<1000; ++i) {
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
			HAL_Delay(1);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
			HAL_Delay(1);
		}
	}


	for (int i=0; i<200; ++i) {
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_SET);
		HAL_Delay(1);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_RESET);
		HAL_Delay(1);
	}

	HAL_Delay(300);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
	HAL_Delay(300);

	// __HAL_RCC_USART1_CLK_ENABLE();
	// char usartdata = 'Y';
	// MX_USART1_UART_Init();
	// HAL_UART_Transmit(&huart1, &usartdata, 1, 1000);

	// MX_GPIO_Init();
	// MX_SPI4_Init();
	// HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, GPIO_PIN_SET);

	// uint8_t bulkdata = 0x0;
	// HAL_SPI_Transmit(&hspi4, &bulkdata, 1, 1000);
	// HAL_Delay(1);

	// uint8_t readdata = 0x0;
	// uint8_t writedata = 0x8F;
	// HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, GPIO_PIN_RESET);
	// HAL_SPI_TransmitReceive(&hspi4, &writedata, &bulkdata, 1, 1000);
	// HAL_SPI_TransmitReceive(&hspi4, &bulkdata, &readdata, 1, 1000);
	// HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, GPIO_PIN_SET);

	// if (readdata == 0x69) {
	// 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
	// }

	while (1) {

	}
}

/** System Clock Configuration
*/
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct;
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

	/**Configure the main internal regulator output voltage */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	/**Initializes the CPU, AHB and APB busses clocks */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = 16;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLM = 8;
	RCC_OscInitStruct.PLL.PLLN = 216;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 2;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	/**Activate the Over-Drive mode */
	if (HAL_PWREx_EnableOverDrive() != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	/**Initializes the CPU, AHB and APB busses clocks */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
		|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_I2C1;
	PeriphClkInitStruct.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
	PeriphClkInitStruct.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	/**Configure the Systick interrupt time */
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

	/**Configure the Systick */
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

	/* SysTick_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

// /* ADC1 init function */
// static void MX_ADC1_Init(void) {

// 	ADC_ChannelConfTypeDef sConfig;

//     /**Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion) 
// 	 */
// 	hadc1.Instance = ADC1;
// 	hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
// 	hadc1.Init.Resolution = ADC_RESOLUTION_12B;
// 	hadc1.Init.ScanConvMode = DISABLE;
// 	hadc1.Init.ContinuousConvMode = DISABLE;
// 	hadc1.Init.DiscontinuousConvMode = DISABLE;
// 	hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
// 	hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
// 	hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
// 	hadc1.Init.NbrOfConversion = 1;
// 	hadc1.Init.DMAContinuousRequests = DISABLE;
// 	hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
// 	if (HAL_ADC_Init(&hadc1) != HAL_OK)
// 	{
// 		_Error_Handler(__FILE__, __LINE__);
// 	}

//     /**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. 
// 	 */
// 	sConfig.Channel = ADC_CHANNEL_15;
// 	sConfig.Rank = 1;
// 	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
// 	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
// 	{
// 		_Error_Handler(__FILE__, __LINE__);
// 	}

// }

// /* I2C1 init function */
// static void MX_I2C1_Init(void)
// {

// 	hi2c1.Instance = I2C1;
// 	hi2c1.Init.Timing = 0x00303D5B;
// 	hi2c1.Init.OwnAddress1 = 0;
// 	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
// 	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
// 	hi2c1.Init.OwnAddress2 = 0;
// 	hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
// 	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
// 	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
// 	if (HAL_I2C_Init(&hi2c1) != HAL_OK)
// 	{
// 		_Error_Handler(__FILE__, __LINE__);
// 	}

//     /**Configure Analogue filter 
// 	 */
// 	if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
// 	{
// 		_Error_Handler(__FILE__, __LINE__);
// 	}

//     /**Configure Digital filter 
// 	 */
// 	if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
// 	{
// 		_Error_Handler(__FILE__, __LINE__);
// 	}

// }

// /* QUADSPI init function */
// static void MX_QUADSPI_Init(void)
// {

// 	/* QUADSPI parameter configuration*/
// 	hqspi.Instance = QUADSPI;
// 	hqspi.Init.ClockPrescaler = 255;
// 	hqspi.Init.FifoThreshold = 1;
// 	hqspi.Init.SampleShifting = QSPI_SAMPLE_SHIFTING_NONE;
// 	hqspi.Init.FlashSize = 1;
// 	hqspi.Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_1_CYCLE;
// 	hqspi.Init.ClockMode = QSPI_CLOCK_MODE_0;
// 	hqspi.Init.FlashID = QSPI_FLASH_ID_1;
// 	hqspi.Init.DualFlash = QSPI_DUALFLASH_DISABLE;
// 	if (HAL_QSPI_Init(&hqspi) != HAL_OK)
// 	{
// 		_Error_Handler(__FILE__, __LINE__);
// 	}

// }

// /* SPI1 init function */
// static void MX_SPI1_Init(void)
// {

// 	/* SPI1 parameter configuration*/
// 	hspi1.Instance = SPI1;
// 	hspi1.Init.Mode = SPI_MODE_MASTER;
// 	hspi1.Init.Direction = SPI_DIRECTION_2LINES;
// 	hspi1.Init.DataSize = SPI_DATASIZE_4BIT;
// 	hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
// 	hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
// 	hspi1.Init.NSS = SPI_NSS_SOFT;
// 	hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
// 	hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
// 	hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
// 	hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
// 	hspi1.Init.CRCPolynomial = 7;
// 	hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
// 	hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
// 	if (HAL_SPI_Init(&hspi1) != HAL_OK)
// 	{
// 		_Error_Handler(__FILE__, __LINE__);
// 	}

// }

// /* SPI2 init function */
// static void MX_SPI2_Init(void)
// {

// 	/* SPI2 parameter configuration*/
// 	hspi2.Instance = SPI2;
// 	hspi2.Init.Mode = SPI_MODE_MASTER;
// 	hspi2.Init.Direction = SPI_DIRECTION_2LINES;
// 	hspi2.Init.DataSize = SPI_DATASIZE_4BIT;
// 	hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
// 	hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
// 	hspi2.Init.NSS = SPI_NSS_SOFT;
// 	hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
// 	hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
// 	hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
// 	hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
// 	hspi2.Init.CRCPolynomial = 7;
// 	hspi2.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
// 	hspi2.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
// 	if (HAL_SPI_Init(&hspi2) != HAL_OK)
// 	{
// 		_Error_Handler(__FILE__, __LINE__);
// 	}

// }

// /* SPI3 init function */
// static void MX_SPI3_Init(void)
// {

// 	/* SPI3 parameter configuration*/
// 	hspi3.Instance = SPI3;
// 	hspi3.Init.Mode = SPI_MODE_MASTER;
// 	hspi3.Init.Direction = SPI_DIRECTION_2LINES;
// 	hspi3.Init.DataSize = SPI_DATASIZE_4BIT;
// 	hspi3.Init.CLKPolarity = SPI_POLARITY_LOW;
// 	hspi3.Init.CLKPhase = SPI_PHASE_1EDGE;
// 	hspi3.Init.NSS = SPI_NSS_SOFT;
// 	hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
// 	hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
// 	hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
// 	hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
// 	hspi3.Init.CRCPolynomial = 7;
// 	hspi3.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
// 	hspi3.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
// 	if (HAL_SPI_Init(&hspi3) != HAL_OK)
// 	{
// 		_Error_Handler(__FILE__, __LINE__);
// 	}

// }

// /* SPI4 init function */
// static void MX_SPI4_Init(void)
// {
// 	__HAL_RCC_SPI4_CLK_ENABLE();
// 	__HAL_RCC_GPIOE_CLK_ENABLE();

// 	GPIO_InitTypeDef GPIO_InitStruct;
// 	GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14;
// 	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
// 	GPIO_InitStruct.Pull = GPIO_NOPULL;
// 	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
// 	GPIO_InitStruct.Alternate = GPIO_AF5_SPI4;
// 	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

// 	/* SPI4 parameter configuration*/
// 	hspi4.Instance = SPI4;
// 	hspi4.Init.Mode = SPI_MODE_MASTER;
// 	hspi4.Init.Direction = SPI_DIRECTION_2LINES;
// 	hspi4.Init.DataSize = SPI_DATASIZE_8BIT;
// 	hspi4.Init.CLKPolarity = SPI_POLARITY_HIGH;
// 	hspi4.Init.CLKPhase = SPI_PHASE_2EDGE;
// 	hspi4.Init.NSS = SPI_NSS_SOFT;
// 	hspi4.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
// 	hspi4.Init.FirstBit = SPI_FIRSTBIT_MSB;
// 	hspi4.Init.TIMode = SPI_TIMODE_DISABLE;
// 	hspi4.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
// 	hspi4.Init.CRCPolynomial = 10;
// 	/* hspi4.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE; */
// 	/* hspi4.Init.NSSPMode = SPI_NSS_PULSE_ENABLE; */
// 	if (HAL_SPI_Init(&hspi4) != HAL_OK)
// 	{
// 		_Error_Handler(__FILE__, __LINE__);
// 	}

// }

// /* SPI6 init function */
// static void MX_SPI6_Init(void)
// {

// 	/* SPI6 parameter configuration*/
// 	hspi6.Instance = SPI6;
// 	hspi6.Init.Mode = SPI_MODE_MASTER;
// 	hspi6.Init.Direction = SPI_DIRECTION_2LINES;
// 	hspi6.Init.DataSize = SPI_DATASIZE_4BIT;
// 	hspi6.Init.CLKPolarity = SPI_POLARITY_LOW;
// 	hspi6.Init.CLKPhase = SPI_PHASE_1EDGE;
// 	hspi6.Init.NSS = SPI_NSS_SOFT;
// 	hspi6.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
// 	hspi6.Init.FirstBit = SPI_FIRSTBIT_MSB;
// 	hspi6.Init.TIMode = SPI_TIMODE_DISABLE;
// 	hspi6.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
// 	hspi6.Init.CRCPolynomial = 7;
// 	hspi6.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
// 	hspi6.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
// 	if (HAL_SPI_Init(&hspi6) != HAL_OK)
// 	{
// 		_Error_Handler(__FILE__, __LINE__);
// 	}

// }

// /* TIM1 init function */
// static void MX_TIM1_Init(void)
// {

// 	TIM_Encoder_InitTypeDef sConfig;
// 	TIM_MasterConfigTypeDef sMasterConfig;

// 	htim1.Instance = TIM1;
// 	htim1.Init.Prescaler = 0;
// 	htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
// 	htim1.Init.Period = 0;
// 	htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
// 	htim1.Init.RepetitionCounter = 0;
// 	htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
// 	sConfig.EncoderMode = TIM_ENCODERMODE_TI1;
// 	sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
// 	sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
// 	sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
// 	sConfig.IC1Filter = 0;
// 	sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
// 	sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
// 	sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
// 	sConfig.IC2Filter = 0;
// 	if (HAL_TIM_Encoder_Init(&htim1, &sConfig) != HAL_OK)
// 	{
// 		_Error_Handler(__FILE__, __LINE__);
// 	}

// 	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
// 	sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
// 	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
// 	if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
// 	{
// 		_Error_Handler(__FILE__, __LINE__);
// 	}

// }

// /* TIM2 init function */
// static void MX_TIM2_Init(void)
// {

// 	TIM_MasterConfigTypeDef sMasterConfig;
// 	TIM_OC_InitTypeDef sConfigOC;

// 	htim2.Instance = TIM2;
// 	htim2.Init.Prescaler = 0;
// 	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
// 	htim2.Init.Period = 0;
// 	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
// 	htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
// 	if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
// 	{
// 		_Error_Handler(__FILE__, __LINE__);
// 	}

// 	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
// 	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
// 	if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
// 	{
// 		_Error_Handler(__FILE__, __LINE__);
// 	}

// 	sConfigOC.OCMode = TIM_OCMODE_PWM1;
// 	sConfigOC.Pulse = 0;
// 	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
// 	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
// 	if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
// 	{
// 		_Error_Handler(__FILE__, __LINE__);
// 	}

// 	if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
// 	{
// 		_Error_Handler(__FILE__, __LINE__);
// 	}

// 	HAL_TIM_MspPostInit(&htim2);

// }

// /* TIM3 init function */
// static void MX_TIM3_Init(void)
// {

// 	TIM_MasterConfigTypeDef sMasterConfig;
// 	TIM_OC_InitTypeDef sConfigOC;

// 	htim3.Instance = TIM3;
// 	htim3.Init.Prescaler = 0;
// 	htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
// 	htim3.Init.Period = 0;
// 	htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
// 	htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
// 	if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
// 	{
// 		_Error_Handler(__FILE__, __LINE__);
// 	}

// 	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
// 	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
// 	if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
// 	{
// 		_Error_Handler(__FILE__, __LINE__);
// 	}

// 	sConfigOC.OCMode = TIM_OCMODE_PWM1;
// 	sConfigOC.Pulse = 0;
// 	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
// 	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
// 	if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
// 	{
// 		_Error_Handler(__FILE__, __LINE__);
// 	}

// 	if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
// 	{
// 		_Error_Handler(__FILE__, __LINE__);
// 	}

// 	HAL_TIM_MspPostInit(&htim3);

// }

// /* TIM4 init function */
// static void MX_TIM4_Init(void)
// {

// 	TIM_Encoder_InitTypeDef sConfig;
// 	TIM_MasterConfigTypeDef sMasterConfig;

// 	htim4.Instance = TIM4;
// 	htim4.Init.Prescaler = 0;
// 	htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
// 	htim4.Init.Period = 0;
// 	htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
// 	htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
// 	sConfig.EncoderMode = TIM_ENCODERMODE_TI1;
// 	sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
// 	sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
// 	sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
// 	sConfig.IC1Filter = 0;
// 	sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
// 	sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
// 	sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
// 	sConfig.IC2Filter = 0;
// 	if (HAL_TIM_Encoder_Init(&htim4, &sConfig) != HAL_OK)
// 	{
// 		_Error_Handler(__FILE__, __LINE__);
// 	}

// 	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
// 	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
// 	if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
// 	{
// 		_Error_Handler(__FILE__, __LINE__);
// 	}

// }

// /* TIM5 init function */
// static void MX_TIM5_Init(void)
// {

// 	TIM_Encoder_InitTypeDef sConfig;
// 	TIM_MasterConfigTypeDef sMasterConfig;

// 	htim5.Instance = TIM5;
// 	htim5.Init.Prescaler = 0;
// 	htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
// 	htim5.Init.Period = 0;
// 	htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
// 	htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
// 	sConfig.EncoderMode = TIM_ENCODERMODE_TI1;
// 	sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
// 	sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
// 	sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
// 	sConfig.IC1Filter = 0;
// 	sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
// 	sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
// 	sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
// 	sConfig.IC2Filter = 0;
// 	if (HAL_TIM_Encoder_Init(&htim5, &sConfig) != HAL_OK)
// 	{
// 		_Error_Handler(__FILE__, __LINE__);
// 	}

// 	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
// 	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
// 	if (HAL_TIMEx_MasterConfigSynchronization(&htim5, &sMasterConfig) != HAL_OK)
// 	{
// 		_Error_Handler(__FILE__, __LINE__);
// 	}

// }

// /* TIM8 init function */
// static void MX_TIM8_Init(void)
// {

// 	TIM_Encoder_InitTypeDef sConfig;
// 	TIM_MasterConfigTypeDef sMasterConfig;

// 	htim8.Instance = TIM8;
// 	htim8.Init.Prescaler = 0;
// 	htim8.Init.CounterMode = TIM_COUNTERMODE_UP;
// 	htim8.Init.Period = 0;
// 	htim8.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
// 	htim8.Init.RepetitionCounter = 0;
// 	htim8.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
// 	sConfig.EncoderMode = TIM_ENCODERMODE_TI1;
// 	sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
// 	sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
// 	sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
// 	sConfig.IC1Filter = 0;
// 	sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
// 	sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
// 	sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
// 	sConfig.IC2Filter = 0;
// 	if (HAL_TIM_Encoder_Init(&htim8, &sConfig) != HAL_OK)
// 	{
// 		_Error_Handler(__FILE__, __LINE__);
// 	}

// 	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
// 	sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
// 	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
// 	if (HAL_TIMEx_MasterConfigSynchronization(&htim8, &sMasterConfig) != HAL_OK)
// 	{
// 		_Error_Handler(__FILE__, __LINE__);
// 	}

// }

// /* TIM9 init function */
// static void MX_TIM9_Init(void)
// {

// 	TIM_OC_InitTypeDef sConfigOC;

// 	htim9.Instance = TIM9;
// 	htim9.Init.Prescaler = 0;
// 	htim9.Init.CounterMode = TIM_COUNTERMODE_UP;
// 	htim9.Init.Period = 0;
// 	htim9.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
// 	htim9.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
// 	if (HAL_TIM_PWM_Init(&htim9) != HAL_OK)
// 	{
// 		_Error_Handler(__FILE__, __LINE__);
// 	}

// 	sConfigOC.OCMode = TIM_OCMODE_PWM1;
// 	sConfigOC.Pulse = 0;
// 	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
// 	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
// 	if (HAL_TIM_PWM_ConfigChannel(&htim9, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
// 	{
// 		_Error_Handler(__FILE__, __LINE__);
// 	}

// 	HAL_TIM_MspPostInit(&htim9);

// }

// /* USART1 init function */
// static void MX_USART1_UART_Init(void)
// {

// 	huart1.Instance = USART1;
// 	huart1.Init.BaudRate = 115200;
// 	huart1.Init.WordLength = UART_WORDLENGTH_7B;
// 	huart1.Init.StopBits = UART_STOPBITS_1;
// 	huart1.Init.Parity = UART_PARITY_NONE;
// 	huart1.Init.Mode = UART_MODE_TX_RX;
// 	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
// 	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
// 	huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
// 	huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
// 	if (HAL_UART_Init(&huart1) != HAL_OK)
// 	{
// 		_Error_Handler(__FILE__, __LINE__);
// 	}

// }

// /** Configure pins as 
//         * Analog 
//         * Input 
//         * Output
//         * EVENT_OUT
//         * EXTI
// */
// static void MX_GPIO_Init(void)
// {

// 	GPIO_InitTypeDef GPIO_InitStruct;

// 	/* GPIO Ports Clock Enable */
// 	__HAL_RCC_GPIOE_CLK_ENABLE();
// 	__HAL_RCC_GPIOC_CLK_ENABLE();
// 	__HAL_RCC_GPIOA_CLK_ENABLE();
// 	__HAL_RCC_GPIOB_CLK_ENABLE();
// 	__HAL_RCC_GPIOD_CLK_ENABLE();

// 	/*Configure GPIO pin Output Level */
// 	HAL_GPIO_WritePin(GPIOE, Sensor7_CS_Pin|Sensor7_CNVST_Pin|Motor1IN2_Pin|Motor4IN1_Pin 
// 					  |GyroCS_Pin|Sensor8_CS_Pin|Sensor8_CNVST_Pin, GPIO_PIN_RESET);

// 	/*Configure GPIO pin Output Level */
// 	HAL_GPIO_WritePin(GPIOC, Motor1IN1_Pin|Motor2IN2_Pin|Motor2IN1_Pin|Motor3IN2_Pin 
// 					  |Motor3IN1_Pin|Sensor5_CNVST_Pin|Sensor5_CS_Pin, GPIO_PIN_RESET);

// 	/*Configure GPIO pin Output Level */
// 	HAL_GPIO_WritePin(GPIOA, Motor4IN2_Pin|Sensor6_CS_Pin|Sensor6_CNVST_Pin|Sensor2_CS_Pin, GPIO_PIN_RESET);

// 	/*Configure GPIO pin Output Level */
// 	HAL_GPIO_WritePin(GPIOB, Sensor3_CS_Pin|Sensor3_CNVST_Pin, GPIO_PIN_RESET);

// 	/*Configure GPIO pin Output Level */
// 	HAL_GPIO_WritePin(GPIOD, Sensor4_CS_Pin|Sensor4_CNVST_Pin|Sensor2_CNVST_Pin|Sensor1_CNVST_Pin 
// 					  |Sensor1_CS_Pin, GPIO_PIN_RESET);

// 	/*Configure GPIO pins : Sensor7_CS_Pin Sensor7_CNVST_Pin Motor1IN2_Pin Motor4IN1_Pin 
// 	  GyroCS_Pin Sensor8_CS_Pin Sensor8_CNVST_Pin */
// 	GPIO_InitStruct.Pin = Sensor7_CS_Pin|Sensor7_CNVST_Pin|Motor1IN2_Pin|Motor4IN1_Pin 
// 		|GyroCS_Pin|Sensor8_CS_Pin|Sensor8_CNVST_Pin;
// 	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
// 	GPIO_InitStruct.Pull = GPIO_NOPULL;
// 	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
// 	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

// 	/*Configure GPIO pins : Motor1IN1_Pin Motor2IN2_Pin Motor2IN1_Pin Motor3IN2_Pin 
// 	  Motor3IN1_Pin Sensor5_CNVST_Pin Sensor5_CS_Pin */
// 	GPIO_InitStruct.Pin = Motor1IN1_Pin|Motor2IN2_Pin|Motor2IN1_Pin|Motor3IN2_Pin 
// 		|Motor3IN1_Pin|Sensor5_CNVST_Pin|Sensor5_CS_Pin;
// 	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
// 	GPIO_InitStruct.Pull = GPIO_NOPULL;
// 	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
// 	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

// 	/*Configure GPIO pins : SW1_Pin SW2_Pin */
// 	GPIO_InitStruct.Pin = SW1_Pin|SW2_Pin;
// 	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
// 	GPIO_InitStruct.Pull = GPIO_NOPULL;
// 	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

// 	/*Configure GPIO pins : Motor4IN2_Pin Sensor6_CS_Pin Sensor6_CNVST_Pin Sensor2_CS_Pin */
// 	GPIO_InitStruct.Pin = Motor4IN2_Pin|Sensor6_CS_Pin|Sensor6_CNVST_Pin|Sensor2_CS_Pin;
// 	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
// 	GPIO_InitStruct.Pull = GPIO_NOPULL;
// 	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
// 	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

// 	/*Configure GPIO pins : GyroINT1_Pin GyroINT2_Pin */
// 	GPIO_InitStruct.Pin = GyroINT1_Pin|GyroINT2_Pin;
// 	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
// 	GPIO_InitStruct.Pull = GPIO_NOPULL;
// 	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

// 	/*Configure GPIO pins : Sensor3_CS_Pin Sensor3_CNVST_Pin */
// 	GPIO_InitStruct.Pin = Sensor3_CS_Pin|Sensor3_CNVST_Pin;
// 	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
// 	GPIO_InitStruct.Pull = GPIO_NOPULL;
// 	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
// 	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

// 	/*Configure GPIO pins : Sensor4_CS_Pin Sensor4_CNVST_Pin Sensor2_CNVST_Pin Sensor1_CNVST_Pin 
// 	  Sensor1_CS_Pin */
// 	GPIO_InitStruct.Pin = Sensor4_CS_Pin|Sensor4_CNVST_Pin|Sensor2_CNVST_Pin|Sensor1_CNVST_Pin 
// 		|Sensor1_CS_Pin;
// 	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
// 	GPIO_InitStruct.Pull = GPIO_NOPULL;
// 	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
// 	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

// 	/*Configure GPIO pins : Sensor4_EOC_Pin Sensor3_EOC_Pin Sensor5_EOC_Pin Sensor2_EOC_Pin 
// 	  Sensor1_EOC_Pin Sensor8_EOC_Pin Sensor7_EOC_Pin */
// 	GPIO_InitStruct.Pin = Sensor4_EOC_Pin|Sensor3_EOC_Pin|Sensor5_EOC_Pin|Sensor2_EOC_Pin 
// 		|Sensor1_EOC_Pin|Sensor8_EOC_Pin|Sensor7_EOC_Pin;
// 	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
// 	GPIO_InitStruct.Pull = GPIO_NOPULL;
// 	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

// 	/*Configure GPIO pin : Sensor6_EOC_Pin */
// 	GPIO_InitStruct.Pin = Sensor6_EOC_Pin;
// 	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
// 	GPIO_InitStruct.Pull = GPIO_NOPULL;
// 	HAL_GPIO_Init(Sensor6_EOC_GPIO_Port, &GPIO_InitStruct);

// }

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line) {
	/* User can add his own implementation to report the HAL error return state */
	while(1) {
	}
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line) {
	/* User can add his own implementation to report the file name and line number,
	   ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
}

#endif
