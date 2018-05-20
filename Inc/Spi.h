/**
 * @file Spi.h
 */

#pragma once

#include "stm32f7xx_hal.h"

#include <vector>

#include "ComPc.h"


class Spi{
private:

protected:
	GPIO_TypeDef *cs_port;
	uint16_t cs_pin;
	SPI_HandleTypeDef port;

	uint8_t buffer[8];

	void initialize(SPI_TypeDef *spi, GPIO_TypeDef *gpio, uint16_t gpiopin);

	void setChipSelect();
	void resetChipSelect();

	int readSingleByte(uint8_t &data);
	int writeSingleByte(uint8_t data);

	int readMultiByte(std::vector<uint8_t> &data, const uint8_t num);
	int writeMultiByte(const std::vector<uint8_t> &data, const uint8_t num);

	// 複数バイトを書き込み，読み出しを行う関数です
	int rwMultiByte(
		std::vector<uint8_t> &data_read, const std::vector<uint8_t> &data_write,
		const uint8_t num_read, const uint8_t num_write);

	// 複数バイトの同時書き込み読み出しを行う関数です
	int rwAllMultiByte(
		std::vector<uint8_t> &data_read, const std::vector<uint8_t> &data_write,
		const uint8_t num_readwrite);

public:
	Spi();
};
