/**
 * @file Led.cpp
 */

#include "Led.h"

Led::Led(){
	gpio_port = GPIOB;
	gpio_channel = GPIO_PIN_5;

	__HAL_RCC_GPIOB_CLK_ENABLE();

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.Pin = GPIO_PIN_5;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

    hi2c1.Instance = I2C1;
    hi2c1.Init.Timing = 0x20404768;
    hi2c1.Init.OwnAddress1 = 0;
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c1.Init.OwnAddress2 = 0;
    hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
    hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

    HAL_I2C_Init(&hi2c1);
    /** Configure Analogue filter */
    HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE);
    /** Configure Digital filter */
    HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0);

    // __HAL_RCC_GPIOB_CLK_ENABLE();
    /**I2C1 GPIO Configuration    
       PB8     ------> I2C1_SCL
       PB9     ------> I2C1_SDA 
    */
    GPIO_InitStructure.Pin = GPIO_PIN_8|GPIO_PIN_9;
    GPIO_InitStructure.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    // GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStructure.Alternate = GPIO_AF4_I2C1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

    __HAL_RCC_I2C1_CLK_ENABLE();
  
    // /* I2C1 DMA Init */
    // /* I2C1_TX Init */
    // hdma_i2c1_tx.Instance = DMA1_Stream6;
    // hdma_i2c1_tx.Init.Channel = DMA_CHANNEL_1;
    // hdma_i2c1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    // hdma_i2c1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    // hdma_i2c1_tx.Init.MemInc = DMA_MINC_ENABLE;
    // hdma_i2c1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    // hdma_i2c1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    // hdma_i2c1_tx.Init.Mode = DMA_NORMAL;
    // hdma_i2c1_tx.Init.Priority = DMA_PRIORITY_LOW;
    // hdma_i2c1_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    // HAL_DMA_Init(&hdma_i2c1_tx);

    // __HAL_LINKDMA(i2cHandle, hdmatx, hdma_i2c1_tx);
}

void Led::on(LedNumbers num){
    switch (num) {
    case LedNumbers::TOP :
        HAL_GPIO_WritePin(gpio_port, gpio_channel, GPIO_PIN_SET);
        break;
    case LedNumbers::LED0 :
        uint8_t data[2] = {0x00, 0x01};
        HAL_I2C_Master_Transmit(&hi2c1, 0x1 << 1, data, 2, 1000);

        HAL_Delay(1);
        data[0] = 0x0C;
        data[1] = 0x55;
        HAL_I2C_Master_Transmit(&hi2c1, 0x1 << 1, data, 2, 1000);

        HAL_Delay(1);
        data[0] = 0x0D;
        data[1] = 0x55;
        HAL_I2C_Master_Transmit(&hi2c1, 0x1 << 1, data, 2, 1000);
        // uint8_t data[14];
        // data[0] = 0x80; //0b 100 00000
        // data[1] = 0x91; //0b 100 00001
        // data[2] = 0x05; //0b 00 000 101
        // data[3] = 0x00; //0x 00
        // data[4] = 0x00; //0x 00
        // data[5] = 0x00; //0x 00
        // data[6] = 0x00; //0x 00
        // data[7] = 0x00; //0x 00
        // data[8] = 0x00; //0x 00
        // data[9] = 0x00; //0x 00
        // data[10] = 0x00; //0x 00
        // data[11] = 0xFF; //0x FF
        // data[12] = 0x00; //0x 00
        // data[13] = 0x01; //0b 00 00 00 01
        // status = HAL_I2C_Master_Transmit(&hi2c1, 0x1 << 1, data, 14, 1000);
        // // HAL_I2C_Mem_Write(&hi2c1, 0x1, data[0], 1, &data[1], 13, 1000);
        break;
    }
}

void Led::off(LedNumbers num){
    switch (num) {
    case LedNumbers::TOP :
        HAL_GPIO_WritePin(gpio_port, gpio_channel, GPIO_PIN_RESET);
        break;
    case LedNumbers::LED0 :
        
        break;
    }}

bool Led::isFlicking(LedNumbers num){
	if(flick_params.at(static_cast<uint8_t>(num)).start_time == 0) return false;
	else return true;
}

void Led::flickSync(LedNumbers num, float freq, uint16_t time){
	flickAsync(num, freq, time);
	while(isFlicking(num));
}

void Led::flickAsync(LedNumbers num, float freq, uint16_t time){
	// flick_params.at(static_cast<uint8_t>(num)).start_time = Timer::getTime();
	// flick_params.at(static_cast<uint8_t>(num)).freq = freq;
	// flick_params.at(static_cast<uint8_t>(num)).time = time;
}

void Led::flickStop(LedNumbers num){
	// flick_params.at(static_cast<uint8_t>(num)).start_time = 0;
	// off(num);
}


void Led::interrupt(){
	// uint32_t t;
	// uint32_t t2;
	// int8_t i = -1;
	// for(auto& n : flick_params){
	// 	++i;
	// 	if(n.start_time == 0) continue;
	// 	t2 = static_cast<uint32_t>(1000/n.freq);
	// 	t = (Timer::getTime() - n.start_time) % t2;
	// 	if((n.time != 0) && ((Timer::getTime() - n.start_time) > n.time)){
	// 		n.start_time = 0;
	// 		off(static_cast<LedNumbers>(i));
	// 		continue;
	// 	}
	// 	if(t > (t2/2)) on(static_cast<LedNumbers>(i));
	// 	else off(static_cast<LedNumbers>(i));
	// }
}


Led *Led::getInstance(){
	static Led instance;
	return &instance;
}
