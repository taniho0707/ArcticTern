/**
 * @file ComPc.cpp
 */

#include "ComPc.h"

ComPc::ComPc(USART_TypeDef *port) :
	Usart(huart)
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

	huart.Instance = USART1;
	huart.Init.BaudRate = 115200;
	huart.Init.WordLength = UART_WORDLENGTH_8B;
	huart.Init.StopBits = UART_STOPBITS_1;
	huart.Init.Parity = UART_PARITY_NONE;
	huart.Init.Mode = UART_MODE_TX_RX;
	huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart.Init.OverSampling = UART_OVERSAMPLING_16;
	HAL_UART_Init(&huart);

	setTypeDef(huart);
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
	sendnbyte(buffer, len);
	va_end(ap);
	return static_cast<uint16_t>(len);
}

