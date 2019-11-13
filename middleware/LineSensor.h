/**
 * @file LineSensor.h
 */
#pragma once

#include "stm32f7xx_hal.h"

#include <vector>
#include "LineSensorModule.h"
#include "Spi.h"

class LineSensor {
private:
	explicit LineSensor();
	~LineSensor();

	LineSensorModule *modules;

public:
	void initialize();

	bool configAutomatic();

	void readSingleChannel(size_t num_module, LineSensorModuleNumber number);
	void updateSingleChannel(size_t num_module, LineSensorModuleNumber number);

	int16_t getSingleChannel(size_t num_module, LineSensorModuleNumber number);

	void interrupt(size_t num_module);

	static LineSensor* getInstance();
};

