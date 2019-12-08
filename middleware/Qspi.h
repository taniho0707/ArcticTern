/**
 * @file Qspi.h
 * @brief USART通信を行う際の基底クラス。単体での使用不可
 */
#pragma once

#include "stm32f7xx_hal.h"

#include <vector>

class Qspi{
private:
    Qspi();

    QSPI_HandleTypeDef port;

public:
    // Private Functions
    // Write Enable
    void comWriteEnable();

    // (Volatile SR Write Enable)

    // Manufacturer/Device ID
    bool comManufactureDevice();
    bool comManufactureDeviceQuad(uint8_t* data);

    // Fast Read Data
    void comFastReadData(uint32_t addr, uint8_t* data, size_t num);

    // Fast Read
    void comFastReadQuad(uint32_t addr, uint8_t* data, size_t num);

    // Page Program // 256Byte
    void comPageProgram(uint32_t addr, uint8_t* data);

    // Quad Input Page Program // 256Byte
    void comQuadPageProgram(uint32_t addr, uint8_t* data);

    // (Sector Erase (4KB))
    void comSectorErase(uint32_t addr);

    // Block Erase (64KB))
    void comBlockErase(uint32_t addr);

    // (Chip Erase)
    void comChipErase();

    // Write Status Register-1
    void comWriteStatusRegister1(uint8_t data);
    void comWriteStatusRegister2(uint8_t data);
    void comWriteStatusRegister3(uint8_t data);

    // Read Status Register-1
    uint8_t comReadStatusRegister1();
    uint8_t comReadStatusRegister2();
    uint8_t comReadStatusRegister3();

    // Global Block Unlock
    void comGlobalBlockUnlock();

    // Public Functions

	// void send1byte(char data);
	// void send1byte(uint8_t data);

	// void sendnbyte(char *c, const int n);
	// void sendnbyte(std::vector<uint8_t>& c, const int n);

	// void sendbydma(const char *c, const int n);
	// void sendbydma(const std::vector<uint8_t>& c, const int n);

	// bool recv1byte(uint8_t& data);
	// bool recvnbyte(std::vector<uint8_t>& c, const int n);

    static Qspi* getInstance();
};

