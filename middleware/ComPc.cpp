/**
 * @file ComPc.cpp
 */

#include "ComPc.h"

ComPc::ComPc(USART_TypeDef *port) :
	Usart(huart1)
{
	__HAL_RCC_USART1_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	huart1.Instance = USART1;
	huart1.Init.BaudRate = 115200;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	HAL_UART_Init(&huart1);

	setTypeDef(huart1);

	// // OLD Settinga
	// GPIO_InitTypeDef GPIO_InitStructure;
	// USART_InitTypeDef USART_InitStructure;
	// RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	// RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	// RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);

	// GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	// // GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
	// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9/* | GPIO_Pin_10*/;
	// GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	// GPIO_Init(GPIOA, &GPIO_InitStructure);

	// USART_InitStructure.USART_BaudRate = 115200;
	// USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// USART_InitStructure.USART_Parity = USART_Parity_No;
	// USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	// USART_InitStructure.USART_Mode = /*USART_Mode_Rx | */USART_Mode_Tx;
	// USART_Init(USART1, &USART_InitStructure);
	// // USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	// USART_Cmd(USART1, ENABLE);

	// DMA_DeInit(DMA2_Stream7);
	// DMA_InitStructure.DMA_Channel = DMA_Channel_4;
	// DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&(USART1->DR));
	// DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)send_buf;
	// DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	// DMA_InitStructure.DMA_BufferSize = BUFSIZE;
	// DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	// DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	// DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	// DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	// DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	// DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	// DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;
	// DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
	// DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	// DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	// DMA_Init(DMA2_Stream7, &DMA_InitStructure);

	// // NVIC_InitTypeDef NVIC_InitStructure;
	// // NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	// // NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream7_IRQn;
	// // NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	// // NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	// // NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
	// // NVIC_Init(&NVIC_InitStructure);
}


ComPc *ComPc::getInstance(){
	static ComPc instance(USART1);
	return &instance;
}

uint16_t ComPc::printf(const char *fmt, ...){
	char buffer[300];
	int len;

	va_list ap;
	va_start(ap, fmt);

	len = vsprintf(buffer, fmt, ap);
	// sendbydma(buffer, len);
	sendnbyte(buffer, len);
	va_end(ap);
	return static_cast<uint16_t>(len);
}

