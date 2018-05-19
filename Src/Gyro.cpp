/**
 * @file Gyro.cpp
 */
#include "Gyro.h"

Gyro::Gyro() :
	Spi(),
	lsb2dps(0.03354),
	lsb2mps(0.000049762),
	zero_gyroz(0.0),
	zero_accelx(0.0)
{
	initialize(SPI4, GPIOE, GPIO_PIN_15);

	total_angle = 0.0f;
	
	resetChipSelect();
}

bool Gyro::configAutomatic(){
	uint8_t ret = 0;
	std::vector<uint8_t> writedata(2);
	std::vector<uint8_t> readdata(1);
	writedata[0] = static_cast<uint8_t>(GyroCommands::CTRL1_XL);
	writedata[1] = 0x70;
	ret = rwMultiByte(readdata, writedata, 0, 2);
	writedata[0] = static_cast<uint8_t>(GyroCommands::CTRL2_G);
	writedata[1] = 0x88;
	ret = rwMultiByte(readdata, writedata, 0, 2);
	return ret;
}


bool Gyro::whoami(){
	// uint8_t writedata[2] = {(static_cast<uint8_t>(GyroCommands::WHO_AM_I) | 0x80), 0x00};
	// uint8_t readdata[2] = {0x00, 0x00};
	std::vector<uint8_t> writedata(2);
	std::vector<uint8_t> readdata(2);
	writedata[0] = static_cast<uint8_t>(GyroCommands::WHO_AM_I) | 0x80;
	readdata[0] = 0x00;

	auto retval = rwMultiByte(readdata, writedata, 1, 1);

	// bool retval = true;
	// HAL_SPI_TransmitReceive(&port, writedata, readdata, 2, 1000);
	// resetChipSelect();

	// if(retval) return false;
	if(readdata[0] != 0x69) return false;
	retval = configAutomatic();

	return true;
}

int16_t Gyro::readGyroX(){
	int16_t ret = 0x0000;
	std::vector<uint8_t> writedata(1);
	std::vector<uint8_t> readdata(1);
	writedata[0] = static_cast<uint8_t>(GyroCommands::OUTX_H_G) | 0x80;
	rwMultiByte(readdata, writedata, 1, 1);
	ret += (static_cast<uint16_t>(readdata[0]) << 8);
	writedata[0] = static_cast<uint8_t>(GyroCommands::OUTX_L_G) | 0x80;
	rwMultiByte(readdata, writedata, 1, 1);
	ret += readdata[0];
	return ret;
}

int16_t Gyro::readGyroY(){
	int16_t ret = 0x0000;
	std::vector<uint8_t> writedata(1);
	std::vector<uint8_t> readdata(1);
	writedata[0] = static_cast<uint8_t>(GyroCommands::OUTY_H_G) | 0x80;
	rwMultiByte(readdata, writedata, 1, 1);
	ret += (static_cast<uint16_t>(readdata[0]) << 8);
	writedata[0] = static_cast<uint8_t>(GyroCommands::OUTY_L_G) | 0x80;
	rwMultiByte(readdata, writedata, 1, 1);
	ret += readdata[0];
	return ret;
}

int16_t Gyro::readGyroZ(){
	uint16_t ret = 0x0000;
	std::vector<uint8_t> writedata(1);
	std::vector<uint8_t> readdata(1);
	writedata[0] = static_cast<uint8_t>(GyroCommands::OUTZ_H_G) | 0x80;
	rwMultiByte(readdata, writedata, 1, 1);
	ret += (static_cast<uint16_t>(readdata[0]) << 8);
	writedata[0] = static_cast<uint8_t>(GyroCommands::OUTZ_L_G) | 0x80;
	rwMultiByte(readdata, writedata, 1, 1);
	ret += readdata[0];
	return ret;
}

int16_t Gyro::readAccelX(){
	uint16_t ret = 0x0000;
	std::vector<uint8_t> writedata(1);
	std::vector<uint8_t> readdata(1);
	writedata[0] = static_cast<uint8_t>(GyroCommands::OUTX_H_XL) | 0x80;
	rwMultiByte(readdata, writedata, 1, 1);
	ret += (static_cast<uint16_t>(readdata[0]) << 8);
	writedata[0] = static_cast<uint8_t>(GyroCommands::OUTX_L_XL) | 0x80;
	rwMultiByte(readdata, writedata, 1, 1);
	ret += readdata[0];
	return ret;
}

int16_t Gyro::readAccelY(){
	uint16_t ret = 0x0000;
	std::vector<uint8_t> writedata(1);
	std::vector<uint8_t> readdata(1);
	writedata[0] = static_cast<uint8_t>(GyroCommands::OUTY_H_XL) | 0x80;
	rwMultiByte(readdata, writedata, 1, 1);
	ret += (static_cast<uint16_t>(readdata[0]) << 8);
	writedata[0] = static_cast<uint8_t>(GyroCommands::OUTY_L_XL) | 0x80;
	rwMultiByte(readdata, writedata, 1, 1);
	ret += readdata[0];
	return ret;
}

int16_t Gyro::readAccelZ(){
	uint16_t ret = 0x0000;
	std::vector<uint8_t> writedata(1);
	std::vector<uint8_t> readdata(1);
	writedata[0] = static_cast<uint8_t>(GyroCommands::OUTZ_H_XL) | 0x80;
	rwMultiByte(readdata, writedata, 1, 1);
	ret += (static_cast<uint16_t>(readdata[0]) << 8);
	writedata[0] = static_cast<uint8_t>(GyroCommands::OUTZ_L_XL) | 0x80;
	rwMultiByte(readdata, writedata, 1, 1);
	ret += readdata[0];
	return ret;
}

void Gyro::readAccelFront(){
	cur_accel_front = (static_cast<float>(readAccelX()) * lsb2mps - zero_accelx);
	return;
}

void Gyro::readGyroYaw(){
	cur_gyro_yaw = (static_cast<float>(readGyroZ()) * lsb2dps - zero_gyroz);
	return;
}


void Gyro::resetCalibration(){
	float tmp = 0.0;
	for (auto i=0; i<1000; i++) {
		readGyroYaw();
		tmp += (getGyroYaw() / 1000);
		HAL_Delay(1);
	}
	zero_gyroz = tmp;
}

float Gyro::getAccelFront(){
	return cur_accel_front;
}

float Gyro::getGyroYaw(){
	return cur_gyro_yaw;
}


float Gyro::getTotalAngle() {
	return total_angle;
}

void Gyro::resetTotalAngle() {
	total_angle = 0.0f;
}


void Gyro::interrupt() {
	readGyroYaw();
	total_angle += getGyroYaw() / 1000.0f;
}


Gyro* Gyro::getInstance(){
	static Gyro instance;
	return &instance;
}
