/**
 * @file ComPc.h
 */
#pragma once

#include <string>
#include <cstdarg>
#include <cstdio>
#include "stm32f7xx_hal.h"

#include "Usart.h"


class ComPc : protected Usart{
private:

	explicit ComPc(USART_TypeDef *port);

	uint8_t bit2hex(const uint8_t val);

	DMA_InitTypeDef DMA_InitStructure;
	UART_HandleTypeDef huart1;

public:

	static ComPc *getInstance();

	uint16_t printf(const char *fmt, ...);

};
