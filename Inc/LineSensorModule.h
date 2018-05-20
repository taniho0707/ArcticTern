/**
 * @file LineSensorModule.h
 */
#pragma once

#include "stm32f7xx_hal.h"

#include <vector>
#include "Spi.h"

// モジュールごとのセンサ番号を示す
// 半時計回り
enum class LineSensorModuleNumber : uint8_t {
	S0,
	S1,
	S2,
	S3,
	S4,
	S5,
	S6,
	S7,
};

// MAX11125のレジスタアドレス一覧
// これに送るデータを加算して使用する
enum class MAX11125Commands : uint16_t {
	ADC_MODE_CONTROL = 0x0000,
	ADC_CONFIGURATION = 0x8000,
	UNIPOLAR = 0x8800,
	BIPOLAR = 0x9000,
	RANGE = 0x9800,
	CUSTOM_SCAN0 = 0xA000,
	CUSTOM_SCAN1 = 0xA800,
	SAMPLE_SET = 0xB000,
};

class LineSensorModule : protected Spi {
private:

	const float lsb2volt;

	// int16_t AD変換後のデータを保持する配列
	// 以降，DSPのベクトル演算に回す配列はすべてq15_tで定義する
	/// @todo 型を直してCMSIS-DSPを使えるようにする
	/*q15_t*/ int16_t converted_raw[8];

	// GPIO
	GPIO_TypeDef *gpio_eoc, *gpio_cnvst;
	uint16_t gpiopin_eoc, gpiopin_cnvst;

public:
	explicit LineSensorModule();
	~LineSensorModule();

	void initialize(
		SPI_TypeDef *spi, GPIO_TypeDef *gpio_cs, uint16_t gpiopin_cs,
		GPIO_TypeDef *gpio_eoc, uint16_t gpiopin_eoc, IRQn_Type irq,
		GPIO_TypeDef *gpio_cnvst, uint16_t gpiopin_cnvst
		);

	bool whoami();
	bool configAutomatic();

	void readSingleChannel(LineSensorModuleNumber number);
	void updateSingleChannel(LineSensorModuleNumber number);

	int16_t getSingleChannel(LineSensorModuleNumber number);
};
