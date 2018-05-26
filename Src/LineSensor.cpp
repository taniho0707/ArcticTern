/**
 * @file LineSensor.cpp
 */
#include "LineSensor.h"

LineSensor::LineSensor() {
	modules = new LineSensorModule[8];
}

LineSensor::~LineSensor() {
	delete[] modules;
}


void LineSensor::initialize() {
	modules[2].initialize(
		SPI2, GPIOB, GPIO_PIN_11,
		GPIOD, GPIO_PIN_14, EXTI15_10_IRQn,
		GPIOB, GPIO_PIN_12);
	modules[2].configAutomatic();
}

bool LineSensor::configAutomatic() {
	
}

void LineSensor::readSingleChannel(size_t num_module, LineSensorModuleNumber number) {
	modules[num_module].readSingleChannel(number);
}

void LineSensor::updateSingleChannel(size_t num_module, LineSensorModuleNumber number) {
	modules[num_module].updateSingleChannel(number);
}

int16_t LineSensor::getSingleChannel(size_t num_module, LineSensorModuleNumber number) {
	return modules[num_module].getSingleChannel(number);
}


void LineSensor::interrupt(size_t num_module) {
	modules[num_module].updateSingleChannel(LineSensorModuleNumber::S0);
}

LineSensor* LineSensor::getInstance() {
	static LineSensor linesensor;
	return &linesensor;
}
