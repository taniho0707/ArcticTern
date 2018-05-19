/**
 * @file Spi.cpp
 */

#include "Spi.h"


Spi::Spi(){
	for (int i=0; i<8; i++) buffer[i] = 0x00;
}

void Spi::initialize(SPI_TypeDef *spi, GPIO_TypeDef *gpio, uint16_t gpiopin) {
	// ここどうにかしたい
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	
	if (spi == SPI1) {
		__HAL_RCC_SPI1_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();
		__HAL_RCC_GPIOD_CLK_ENABLE();
		GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4;
		GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
		GPIO_InitStruct.Pin = GPIO_PIN_7;
		HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	} else if (spi == SPI2) {
		__HAL_RCC_SPI2_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();
		GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
		GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	} else if (spi == SPI3) {
		__HAL_RCC_SPI3_CLK_ENABLE();
		__HAL_RCC_GPIOC_CLK_ENABLE();
		GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12;
		GPIO_InitStruct.Alternate = GPIO_AF5_SPI4;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	} else if (spi == SPI4) {
		__HAL_RCC_SPI4_CLK_ENABLE();
		__HAL_RCC_GPIOE_CLK_ENABLE();
		GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14;
		GPIO_InitStruct.Alternate = GPIO_AF5_SPI4;
		HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
	} else if (spi == SPI5) {
		__HAL_RCC_SPI5_CLK_ENABLE();
	} else if (spi == SPI6) {
		__HAL_RCC_SPI6_CLK_ENABLE();
		__HAL_RCC_GPIOA_CLK_ENABLE();
		GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
		GPIO_InitStruct.Alternate = GPIO_AF5_SPI4;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	}

	if (gpio == GPIOA) {
		__HAL_RCC_GPIOA_CLK_ENABLE();
	} else if (gpio == GPIOB) {
		__HAL_RCC_GPIOB_CLK_ENABLE();
	} else if (gpio == GPIOC) {
		__HAL_RCC_GPIOC_CLK_ENABLE();
	} else if (gpio == GPIOD) {
		__HAL_RCC_GPIOD_CLK_ENABLE();
	} else if (gpio == GPIOE) {
		__HAL_RCC_GPIOE_CLK_ENABLE();
	} else if (gpio == GPIOF) {
		__HAL_RCC_GPIOF_CLK_ENABLE();
	}

	cs_port = gpio;
	cs_pin = gpiopin;

	// GPIOの設定
	{
		GPIO_InitTypeDef GPIO_InitStruct;
		GPIO_InitStruct.Pin = cs_pin;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_Init(cs_port, &GPIO_InitStruct);
	}

	// SPIの設定
	{
		port.Instance = spi;
		port.Init.Mode = SPI_MODE_MASTER;
		port.Init.Direction = SPI_DIRECTION_2LINES;
		port.Init.DataSize = SPI_DATASIZE_8BIT;
		port.Init.CLKPolarity = SPI_POLARITY_HIGH;
		port.Init.CLKPhase = SPI_PHASE_2EDGE;
		port.Init.NSS = SPI_NSS_SOFT;
		port.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
		port.Init.FirstBit = SPI_FIRSTBIT_MSB;
		port.Init.TIMode = SPI_TIMODE_DISABLE;
		port.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
		port.Init.CRCPolynomial = 10;
		HAL_SPI_Init(&port);
	}

	// ピン出力を安定させるために空送信
	uint8_t bulkdata = 0x0;
	HAL_SPI_Transmit(&port, &bulkdata, 1, 1000);
	HAL_Delay(1);
}



void Spi::setChipSelect(){
	HAL_GPIO_WritePin(cs_port, cs_pin, GPIO_PIN_RESET);
}
void Spi::resetChipSelect(){
	HAL_GPIO_WritePin(cs_port, cs_pin, GPIO_PIN_SET);
}


int Spi::readSingleByte(uint8_t &data){
	uint8_t bulkdata = 0x00;
	HAL_SPI_TransmitReceive(&port, &bulkdata, &data, 1, 1000);
	return 0;
}

int Spi::writeSingleByte(uint8_t data){
	uint8_t bulk;
	HAL_SPI_TransmitReceive(&port, &data, &bulk, 1, 1000);
	return 0;
}

int Spi::readMultiByte(std::vector<uint8_t> &data, const uint8_t num){
	uint8_t recv = 0x00;
	if(data.capacity() < num) return -1;
	for (int i=0; i<num; i++) {
		readSingleByte(recv);
		data[i] = recv;
	}
	return 0;
}

int Spi::writeMultiByte(const std::vector<uint8_t> &data, const uint8_t num){
	if(data.capacity() < num) return -1;
	for (int i=0; i<num; i++) {
		writeSingleByte(data[i]);
	}
	return 0;
}

int Spi::rwMultiByte(
	std::vector<uint8_t> &data_read, const std::vector<uint8_t> &data_write,
	const uint8_t num_read, const uint8_t num_write)
{
	setChipSelect();
	int retval = 0;
	if(num_write > 0) retval += writeMultiByte(data_write, num_write);
	if(num_read > 0) retval += readMultiByte(data_read, num_read);
	resetChipSelect();
	return retval;
}

