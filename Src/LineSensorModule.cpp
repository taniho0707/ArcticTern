/**
 * @file LineSensorModule.cpp
 */
#include "LineSensorModule.h"

#include "Util.h"

LineSensorModule::LineSensorModule() :
	Spi()
{
	for (int i=0; i<8; ++i) {
		converted_raw[i] = 0;
	}
}

void LineSensorModule::initialize(
	SPI_TypeDef *spi, GPIO_TypeDef *gpio_cs, uint16_t gpiopin_cs,
	GPIO_TypeDef *gpio_eoc, uint16_t gpiopin_eoc, IRQn_Type irq,
	GPIO_TypeDef *gpio_cnvst, uint16_t gpiopin_cnvst
	) {
	// SPIの初期設定
	Spi::initialize(spi, gpio_cs, gpiopin_cs);
	resetChipSelect();

	// GPIOの初期設定
	this->gpio_eoc = gpio_eoc;
	this->gpio_cnvst = gpio_cnvst;

	util::enableGpioClock(gpio_eoc);
	util::enableGpioClock(gpio_cnvst);

	{
		// CNVSTピンの設定
		GPIO_InitTypeDef GPIO_InitStruct;
		GPIO_InitStruct.Pin = gpiopin_cnvst;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(gpio_cnvst, &GPIO_InitStruct);
		HAL_GPIO_WritePin(gpio_cnvst, gpiopin_cnvst, GPIO_PIN_SET);

		// EOCピンの設定
		GPIO_InitStruct.Pin = gpiopin_eoc;
		GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
		HAL_GPIO_Init(gpio_eoc, &GPIO_InitStruct);

		/// @todo 優先順位
		HAL_NVIC_SetPriority(irq, 8, 8);
		// HAL_NVIC_EnableIRQ(irq);
	}
}

bool LineSensorModule::configAutomatic(){
	return true;
}

bool LineSensorModule::whoami(){
	/// @todo 配列を使えるように変更
	// std::vector<uint8_t> writedata(2);
	// std::vector<uint8_t> readdata(2);
	// writedata[0] = static_cast<uint8_t>(GyroCommands::WHO_AM_I) | 0x80;
	// readdata[0] = 0x00;
	// auto retval = rwMultiByte(readdata, writedata, 1, 1);
	// if(readdata[0] != 0x69) return false;
	// retval = configAutomatic();
	return true;
}

void LineSensorModule::readSingleChannel(LineSensorModuleNumber number) {
	// シングルスキャンしてconverted_rawに代入する
	std::vector<uint8_t> writedata(2);
	std::vector<uint8_t> readdata(2);
	writedata[0] = static_cast<uint8_t>(GyroCommands::WHO_AM_I) | 0x80;
	readdata[0] = 0x00;
	auto retval = rwMultiByte(readdata, writedata, 1, 1);
}

int16_t LineSensorModule::getSingleChannel(LineSensorModuleNumber number) {
	return converted_raw[static_cast<size_t>(number)];
}
