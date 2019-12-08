/**
 * @file Qspi.cpp
 */

#include "Qspi.h"


Qspi::Qspi() {
    port.Instance = QUADSPI;
    port.Init.ClockPrescaler = 2;
    port.Init.FifoThreshold = 4;//1;
    port.Init.SampleShifting = QSPI_SAMPLE_SHIFTING_NONE;
    port.Init.FlashSize = 22;
    port.Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_1_CYCLE;
    port.Init.ClockMode = QSPI_CLOCK_MODE_0;
    port.Init.FlashID = QSPI_FLASH_ID_1;
    port.Init.DualFlash = QSPI_DUALFLASH_DISABLE;
    HAL_QSPI_Init(&port);

    __HAL_RCC_QSPI_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    /**QUADSPI GPIO Configuration
       PE2     ------> QUADSPI_BK1_IO2
       PB2     ------> QUADSPI_CLK
       PB10     ------> QUADSPI_BK1_NCS
       PD11     ------> QUADSPI_BK1_IO0
       PD12     ------> QUADSPI_BK1_IO1
       PD13     ------> QUADSPI_BK1_IO3 
    */
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    // hdma_quadspi.Instance = DMA2_Stream2;
    // hdma_quadspi.Init.Channel = DMA_CHANNEL_11;
    // hdma_quadspi.Init.Direction = DMA_MEMORY_TO_PERIPH;
    // hdma_quadspi.Init.PeriphInc = DMA_PINC_DISABLE;
    // hdma_quadspi.Init.MemInc = DMA_MINC_ENABLE;
    // hdma_quadspi.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    // hdma_quadspi.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    // hdma_quadspi.Init.Mode = DMA_NORMAL;
    // hdma_quadspi.Init.Priority = DMA_PRIORITY_MEDIUM;
    // hdma_quadspi.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    // if (HAL_DMA_Init(&hdma_quadspi) != HAL_OK)
    // {
    //   Error_Handler();
    // }

    // __HAL_LINKDMA(qspiHandle,hdma,hdma_quadspi);
}


void Qspi::comWriteEnable() {
    // Quad-SPI initialize
    QSPI_CommandTypeDef qspi_typedef;
    qspi_typedef.Instruction = 0x06;
    qspi_typedef.Address = 0x00;
    qspi_typedef.AlternateBytes = 0x00;
    qspi_typedef.AddressSize = QSPI_ADDRESS_8_BITS;
    qspi_typedef.AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS;
    qspi_typedef.DummyCycles = 0;
    qspi_typedef.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    qspi_typedef.AddressMode = QSPI_ADDRESS_NONE;
    qspi_typedef.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    qspi_typedef.DataMode = QSPI_DATA_NONE;
    qspi_typedef.NbData = 0;
    qspi_typedef.DdrMode = QSPI_DDR_MODE_DISABLE;
    qspi_typedef.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    qspi_typedef.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    HAL_QSPI_Command(&port, &qspi_typedef, 1000);
    uint8_t qdata[1];
    HAL_QSPI_Receive(&port, qdata, 1000);
}

bool Qspi::comManufactureDevice() {
    QSPI_CommandTypeDef qspi_typedef;
    qspi_typedef.Instruction = 0x90;
    qspi_typedef.Address = 0x00;
    qspi_typedef.AlternateBytes = 0x00;
    qspi_typedef.AddressSize = QSPI_ADDRESS_8_BITS;
    qspi_typedef.AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS;
    qspi_typedef.DummyCycles = 16;
    qspi_typedef.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    qspi_typedef.AddressMode = QSPI_ADDRESS_NONE;
    qspi_typedef.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    qspi_typedef.DataMode = QSPI_DATA_1_LINE;
    qspi_typedef.NbData = 3;
    qspi_typedef.DdrMode = QSPI_DDR_MODE_DISABLE;
    qspi_typedef.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    qspi_typedef.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    HAL_QSPI_Command(&port, &qspi_typedef, 1000);
    uint8_t qdata[3];
    HAL_QSPI_Receive(&port, qdata, 1000);

    if (qdata[0] == 0x00
        && qdata[1] == 0xEF
        && qdata[2] == 0x16) {
        return true;
    } else {
        return false;
    }
}
bool Qspi::comManufactureDeviceQuad(uint8_t* data) {
    QSPI_CommandTypeDef qspi_typedef;
    qspi_typedef.Instruction = 0x94;
    qspi_typedef.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    qspi_typedef.Address = 0x00000000;
    qspi_typedef.AddressSize = QSPI_ADDRESS_24_BITS;
    qspi_typedef.AddressMode = QSPI_ADDRESS_4_LINES;
    qspi_typedef.AlternateBytes = 0x00;
    qspi_typedef.AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS;
    qspi_typedef.AlternateByteMode = QSPI_ALTERNATE_BYTES_4_LINES;
    qspi_typedef.DummyCycles = 4;
    qspi_typedef.NbData = 2;
    qspi_typedef.DataMode = QSPI_DATA_4_LINES;
    qspi_typedef.DdrMode = QSPI_DDR_MODE_DISABLE;
    qspi_typedef.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    qspi_typedef.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    HAL_QSPI_Command(&port, &qspi_typedef, 1000);
    uint8_t qdata[2];
    HAL_QSPI_Receive(&port, data, 1000);

    if (data[0] == 0xEF
        && data[1] == 0x16) {
        return true;
    } else {
        return false;
    }
}

void Qspi::comFastReadData(uint32_t addr, uint8_t* data, size_t num) {
    QSPI_CommandTypeDef qspi_typedef;
    qspi_typedef.Instruction = 0x0B;
    qspi_typedef.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    qspi_typedef.Address = addr;
    qspi_typedef.AddressSize = QSPI_ADDRESS_24_BITS;
    qspi_typedef.AddressMode = QSPI_ADDRESS_1_LINE;
    qspi_typedef.AlternateBytes = 0x00;
    qspi_typedef.AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS;
    qspi_typedef.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    qspi_typedef.DummyCycles = 8;
    qspi_typedef.NbData = num;
    qspi_typedef.DataMode = QSPI_DATA_1_LINE;
    qspi_typedef.DdrMode = QSPI_DDR_MODE_DISABLE;
    qspi_typedef.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    qspi_typedef.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    HAL_QSPI_Command(&port, &qspi_typedef, 1000);
    HAL_QSPI_Receive(&port, data, 1000);
}
void Qspi::comFastReadQuad(uint32_t addr, uint8_t* data, size_t num) {
    QSPI_CommandTypeDef qspi_typedef;
    qspi_typedef.Instruction = 0x6B;
    qspi_typedef.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    qspi_typedef.Address = addr;
    qspi_typedef.AddressSize = QSPI_ADDRESS_24_BITS;
    qspi_typedef.AddressMode = QSPI_ADDRESS_1_LINE;
    qspi_typedef.AlternateBytes = 0x00;
    qspi_typedef.AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS;
    qspi_typedef.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    qspi_typedef.DummyCycles = 8;
    qspi_typedef.NbData = num;
    qspi_typedef.DataMode = QSPI_DATA_4_LINES;
    qspi_typedef.DdrMode = QSPI_DDR_MODE_DISABLE;
    qspi_typedef.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    qspi_typedef.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    HAL_QSPI_Command(&port, &qspi_typedef, 1000);
    HAL_QSPI_Receive(&port, data, 1000);
}

void Qspi::comPageProgram(uint32_t addr, uint8_t* data) {
    QSPI_CommandTypeDef qspi_typedef;
    qspi_typedef.Instruction = 0x02;
    qspi_typedef.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    qspi_typedef.Address = addr;
    qspi_typedef.AddressSize = QSPI_ADDRESS_24_BITS;
    qspi_typedef.AddressMode = QSPI_ADDRESS_1_LINE;
    qspi_typedef.AlternateBytes = 0x00;
    qspi_typedef.AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS;
    qspi_typedef.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    qspi_typedef.DummyCycles = 0;
    qspi_typedef.NbData = 256;
    qspi_typedef.DataMode = QSPI_DATA_1_LINE;
    qspi_typedef.DdrMode = QSPI_DDR_MODE_DISABLE;
    qspi_typedef.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    qspi_typedef.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    HAL_QSPI_Command(&port, &qspi_typedef, 1000);
    HAL_QSPI_Transmit(&port, data, 1000);
}
void Qspi::comQuadPageProgram(uint32_t addr, uint8_t* data) {
    QSPI_CommandTypeDef qspi_typedef;
    qspi_typedef.Instruction = 0x32;
    qspi_typedef.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    qspi_typedef.Address = addr;
    qspi_typedef.AddressSize = QSPI_ADDRESS_24_BITS;
    qspi_typedef.AddressMode = QSPI_ADDRESS_1_LINE;
    qspi_typedef.AlternateBytes = 0x00;
    qspi_typedef.AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS;
    qspi_typedef.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    qspi_typedef.DummyCycles = 0;
    qspi_typedef.NbData = 256;
    qspi_typedef.DataMode = QSPI_DATA_4_LINES;
    qspi_typedef.DdrMode = QSPI_DDR_MODE_DISABLE;
    qspi_typedef.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    qspi_typedef.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    HAL_QSPI_Command(&port, &qspi_typedef, 1000);
    HAL_QSPI_Transmit(&port, data, 1000);
}

void Qspi::comSectorErase(uint32_t addr) {
    QSPI_CommandTypeDef qspi_typedef;
    qspi_typedef.Instruction = 0x20;
    qspi_typedef.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    qspi_typedef.Address = addr;
    qspi_typedef.AddressSize = QSPI_ADDRESS_24_BITS;
    qspi_typedef.AddressMode = QSPI_ADDRESS_1_LINE;
    qspi_typedef.AlternateBytes = 0x00;
    qspi_typedef.AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS;
    qspi_typedef.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    qspi_typedef.DummyCycles = 0;
    qspi_typedef.NbData = 0;
    qspi_typedef.DataMode = QSPI_DATA_NONE;
    qspi_typedef.DdrMode = QSPI_DDR_MODE_DISABLE;
    qspi_typedef.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    qspi_typedef.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    HAL_QSPI_Command(&port, &qspi_typedef, 1000);
    uint8_t data;
    HAL_QSPI_Transmit(&port, &data, 1000);
}

void Qspi::comBlockErase(uint32_t addr) {
    QSPI_CommandTypeDef qspi_typedef;
    qspi_typedef.Instruction = 0xD8;
    qspi_typedef.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    qspi_typedef.Address = addr;
    qspi_typedef.AddressSize = QSPI_ADDRESS_24_BITS;
    qspi_typedef.AddressMode = QSPI_ADDRESS_1_LINE;
    qspi_typedef.AlternateBytes = 0x00;
    qspi_typedef.AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS;
    qspi_typedef.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    qspi_typedef.DummyCycles = 0;
    qspi_typedef.NbData = 0;
    qspi_typedef.DataMode = QSPI_DATA_NONE;
    qspi_typedef.DdrMode = QSPI_DDR_MODE_DISABLE;
    qspi_typedef.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    qspi_typedef.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    HAL_QSPI_Command(&port, &qspi_typedef, 1000);
    uint8_t data;
    HAL_QSPI_Transmit(&port, &data, 1000);
}

void Qspi::comChipErase() {
    QSPI_CommandTypeDef qspi_typedef;
    qspi_typedef.Instruction = 0xC7;
    qspi_typedef.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    qspi_typedef.Address = 0x0;
    qspi_typedef.AddressSize = QSPI_ADDRESS_24_BITS;
    qspi_typedef.AddressMode = QSPI_ADDRESS_NONE;
    qspi_typedef.AlternateBytes = 0x00;
    qspi_typedef.AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS;
    qspi_typedef.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    qspi_typedef.DummyCycles = 0;
    qspi_typedef.NbData = 0;
    qspi_typedef.DataMode = QSPI_DATA_NONE;
    qspi_typedef.DdrMode = QSPI_DDR_MODE_DISABLE;
    qspi_typedef.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    qspi_typedef.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    HAL_QSPI_Command(&port, &qspi_typedef, 1000);
    uint8_t data;
    HAL_QSPI_Transmit(&port, &data, 1000);
}

void Qspi::comWriteStatusRegister1(uint8_t data) {
    QSPI_CommandTypeDef qspi_typedef;
    qspi_typedef.Instruction = 0x01;
    qspi_typedef.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    qspi_typedef.Address = 0x0;
    qspi_typedef.AddressSize = QSPI_ADDRESS_24_BITS;
    qspi_typedef.AddressMode = QSPI_ADDRESS_NONE;
    qspi_typedef.AlternateBytes = 0x00;
    qspi_typedef.AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS;
    qspi_typedef.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    qspi_typedef.DummyCycles = 0;
    qspi_typedef.NbData = 1;
    qspi_typedef.DataMode = QSPI_DATA_1_LINE;
    qspi_typedef.DdrMode = QSPI_DDR_MODE_DISABLE;
    qspi_typedef.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    qspi_typedef.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    HAL_QSPI_Command(&port, &qspi_typedef, 1000);
    HAL_QSPI_Transmit(&port, &data, 1000);
}
void Qspi::comWriteStatusRegister2(uint8_t data) {
    QSPI_CommandTypeDef qspi_typedef;
    qspi_typedef.Instruction = 0x31;
    qspi_typedef.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    qspi_typedef.Address = 0x0;
    qspi_typedef.AddressSize = QSPI_ADDRESS_24_BITS;
    qspi_typedef.AddressMode = QSPI_ADDRESS_NONE;
    qspi_typedef.AlternateBytes = 0x00;
    qspi_typedef.AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS;
    qspi_typedef.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    qspi_typedef.DummyCycles = 0;
    qspi_typedef.NbData = 1;
    qspi_typedef.DataMode = QSPI_DATA_1_LINE;
    qspi_typedef.DdrMode = QSPI_DDR_MODE_DISABLE;
    qspi_typedef.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    qspi_typedef.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    HAL_QSPI_Command(&port, &qspi_typedef, 1000);
    HAL_QSPI_Transmit(&port, &data, 1000);
}
void Qspi::comWriteStatusRegister3(uint8_t data) {
    QSPI_CommandTypeDef qspi_typedef;
    qspi_typedef.Instruction = 0x11;
    qspi_typedef.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    qspi_typedef.Address = 0x0;
    qspi_typedef.AddressSize = QSPI_ADDRESS_24_BITS;
    qspi_typedef.AddressMode = QSPI_ADDRESS_NONE;
    qspi_typedef.AlternateBytes = 0x00;
    qspi_typedef.AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS;
    qspi_typedef.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    qspi_typedef.DummyCycles = 0;
    qspi_typedef.NbData = 1;
    qspi_typedef.DataMode = QSPI_DATA_1_LINE;
    qspi_typedef.DdrMode = QSPI_DDR_MODE_DISABLE;
    qspi_typedef.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    qspi_typedef.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    HAL_QSPI_Command(&port, &qspi_typedef, 1000);
    HAL_QSPI_Transmit(&port, &data, 1000);
}

uint8_t Qspi::comReadStatusRegister1() {
    QSPI_CommandTypeDef qspi_typedef;
    qspi_typedef.Instruction = 0x05;
    qspi_typedef.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    qspi_typedef.Address = 0x0;
    qspi_typedef.AddressSize = QSPI_ADDRESS_24_BITS;
    qspi_typedef.AddressMode = QSPI_ADDRESS_NONE;
    qspi_typedef.AlternateBytes = 0x00;
    qspi_typedef.AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS;
    qspi_typedef.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    qspi_typedef.DummyCycles = 0;
    qspi_typedef.NbData = 1;
    qspi_typedef.DataMode = QSPI_DATA_1_LINE;
    qspi_typedef.DdrMode = QSPI_DDR_MODE_DISABLE;
    qspi_typedef.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    qspi_typedef.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    HAL_QSPI_Command(&port, &qspi_typedef, 1000);
    uint8_t ret;
    HAL_QSPI_Receive(&port, &ret, 1000);
    return ret;
}
uint8_t Qspi::comReadStatusRegister2() {
    QSPI_CommandTypeDef qspi_typedef;
    qspi_typedef.Instruction = 0x35;
    qspi_typedef.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    qspi_typedef.Address = 0x0;
    qspi_typedef.AddressSize = QSPI_ADDRESS_24_BITS;
    qspi_typedef.AddressMode = QSPI_ADDRESS_NONE;
    qspi_typedef.AlternateBytes = 0x00;
    qspi_typedef.AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS;
    qspi_typedef.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    qspi_typedef.DummyCycles = 0;
    qspi_typedef.NbData = 1;
    qspi_typedef.DataMode = QSPI_DATA_1_LINE;
    qspi_typedef.DdrMode = QSPI_DDR_MODE_DISABLE;
    qspi_typedef.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    qspi_typedef.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    HAL_QSPI_Command(&port, &qspi_typedef, 1000);
    uint8_t ret;
    HAL_QSPI_Receive(&port, &ret, 1000);
    return ret;
}
uint8_t Qspi::comReadStatusRegister3() {
    QSPI_CommandTypeDef qspi_typedef;
    qspi_typedef.Instruction = 0x15;
    qspi_typedef.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    qspi_typedef.Address = 0x0;
    qspi_typedef.AddressSize = QSPI_ADDRESS_24_BITS;
    qspi_typedef.AddressMode = QSPI_ADDRESS_NONE;
    qspi_typedef.AlternateBytes = 0x00;
    qspi_typedef.AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS;
    qspi_typedef.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    qspi_typedef.DummyCycles = 0;
    qspi_typedef.NbData = 1;
    qspi_typedef.DataMode = QSPI_DATA_1_LINE;
    qspi_typedef.DdrMode = QSPI_DDR_MODE_DISABLE;
    qspi_typedef.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    qspi_typedef.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    HAL_QSPI_Command(&port, &qspi_typedef, 1000);
    uint8_t ret;
    HAL_QSPI_Receive(&port, &ret, 1000);
    return ret;
}

void Qspi::comGlobalBlockUnlock() {
    QSPI_CommandTypeDef qspi_typedef;
    qspi_typedef.Instruction = 0x98;
    qspi_typedef.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    qspi_typedef.Address = 0x0;
    qspi_typedef.AddressSize = QSPI_ADDRESS_24_BITS;
    qspi_typedef.AddressMode = QSPI_ADDRESS_NONE;
    qspi_typedef.AlternateBytes = 0x00;
    qspi_typedef.AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS;
    qspi_typedef.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    qspi_typedef.DummyCycles = 0;
    qspi_typedef.NbData = 0;
    qspi_typedef.DataMode = QSPI_DATA_NONE;
    qspi_typedef.DdrMode = QSPI_DDR_MODE_DISABLE;
    qspi_typedef.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    qspi_typedef.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    HAL_QSPI_Command(&port, &qspi_typedef, 1000);
    uint8_t ret;
    HAL_QSPI_Receive(&port, &ret, 1000);
}


Qspi* Qspi::getInstance() {
    static Qspi instance;
    return &instance;
}

// Usart::Usart(UART_HandleTypeDef uart){
// 	port = uart;
// }

// void Usart::setTypeDef(UART_HandleTypeDef uart){
// 	port = uart;
// }

// uint8_t Usart::getChecksum(const uint8_t *data, const uint8_t num){
// 	uint8_t cs = 0x00;
// 	for (uint8_t i=0; i<num; i++) {
// 		cs += data[i];
// 	}
// 	cs = ~cs;
// 	++cs;
// 	return cs;
// }
// uint8_t Usart::getChecksum(const std::vector<uint8_t>&data, const uint8_t num){
// 	uint8_t cs = 0x00;
// 	for (auto v : data) {
// 		cs += v;
// 	}
// 	cs = ~cs;
// 	++cs;
// 	return cs;
// }

// void Usart::send1byte(char data){
// 	uint8_t newdata = data;
// 	HAL_UART_Transmit(&port, &newdata, 1, 1000);
// 	// USART_SendData(usart_port, (uint16_t)data);
// 	// while( USART_GetFlagStatus(usart_port, USART_FLAG_TXE) == RESET );
// }
// void Usart::send1byte(uint8_t data){
// 	HAL_UART_Transmit(&port, &data, 1, 1000);
// 	// USART_SendData(usart_port, (uint16_t)data);
// 	// while( USART_GetFlagStatus(usart_port, USART_FLAG_TXE) == RESET );
// }

// void Usart::sendnbyte(char *data, const int len){
// 	// int i;
// 	// for(i=0; i<len; ++i) send1byte(data[i]);
// 	HAL_UART_Transmit(&port, (uint8_t *)(data), len, 1000);
// }
// void Usart::sendnbyte(std::vector<uint8_t>& c, const int n){
// 	for(auto v : c) send1byte(v);
// }


// void Usart::sendbydma(const char *data, const int len){
// 	// strcpy(send_buf, data);
// 	// DMA_ClearFlag(DMA2_Stream7, DMA_FLAG_TCIF7);
// 	// DMA_Cmd(DMA2_Stream7, ENABLE);
// 	// USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
// }
// void Usart::sendbydma(const std::vector<uint8_t>& c, const int n){
// 	// USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
// }

// bool Usart::recv1byte(uint8_t& data){
// 	// while(USART_GetFlagStatus(usart_port, USART_FLAG_RXNE) == RESET);
// 	// data = USART_ReceiveData(usart_port);
// 	return true;
// }

// bool Usart::recvnbyte(std::vector<uint8_t>& c, const int n){
// 	// c.clear();
// 	// for (int i=0; i<n; i++) {
// 	// 	c.push_back(static_cast<uint8_t>(USART_ReceiveData(usart_port)));
// 	// }
// 	return true;
// }

