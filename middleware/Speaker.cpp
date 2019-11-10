/**
 * @file Speaker.cpp
 */

#include "Speaker.h"

Speaker::Speaker(){
	sound_time = 0;

	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_TIM9_CLK_ENABLE();
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OC_InitTypeDef TIM_OC_InitStructure;

	GPIO_InitStructure.Pin = GPIO_PIN_5;
	GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStructure.Alternate = GPIO_AF3_TIM9;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStructure);

	htim.Instance = TIM9;
	htim.Init.Prescaler = 31;
	htim.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim.Init.Period = 14300;
	htim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	HAL_TIM_PWM_Init(&htim);

	TIM_OC_InitStructure.OCMode = TIM_OCMODE_PWM1;
	TIM_OC_InitStructure.Pulse = 0;
	TIM_OC_InitStructure.OCPolarity = TIM_OCPOLARITY_LOW;
	TIM_OC_InitStructure.OCFastMode = TIM_OCFAST_DISABLE;
	HAL_TIM_PWM_ConfigChannel(&htim, &TIM_OC_InitStructure, TIM_CHANNEL_1);
}

void Speaker::playSound(int freq, int length, bool sync){
	TIM_OC_InitTypeDef TIM_OC_InitStructure;

	htim.Instance = TIM9;
	htim.Init.Prescaler = 31;
	htim.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim.Init.Period = static_cast<uint16_t>(3375000/freq)-1;
	htim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	HAL_TIM_PWM_Init(&htim);

	TIM_OC_InitStructure.OCMode = TIM_OCMODE_PWM1;
	TIM_OC_InitStructure.Pulse = (htim.Init.Period/2)-1;
	TIM_OC_InitStructure.OCPolarity = TIM_OCPOLARITY_LOW;
	TIM_OC_InitStructure.OCFastMode = TIM_OCFAST_DISABLE;
	HAL_TIM_PWM_ConfigChannel(&htim, &TIM_OC_InitStructure, TIM_CHANNEL_1);

	if(sync){
		HAL_TIM_PWM_Start(&htim, TIM_CHANNEL_1);
		HAL_Delay(length);
		HAL_TIM_PWM_Stop(&htim, TIM_CHANNEL_1);
	} else {
		HAL_TIM_PWM_Start(&htim, TIM_CHANNEL_1);
		sound_time = length;
	}
}

void Speaker::interrupt(){
	if(sound_time == 1){
		sound_time = 0;
		HAL_TIM_PWM_Stop(&htim, TIM_CHANNEL_1);
	} else if(sound_time > 1){
		-- sound_time;
	}
}

void Speaker::playMusic(MusicNumber n){
	switch(n){
	case MusicNumber::KIRBY3_CURSOR:
		playSound(1568, 50, true);
		break;
	case MusicNumber::KIRBY3_POWERON:
		playSound(880, 100, true);
		playSound(1175, 200, true);
		break;
	case MusicNumber::KIRBY3_SELECT1:
		playSound(1174, 30, true);
		playSound(1661, 30, true);
		playSound(2093, 30, true);
		break;
	case MusicNumber::KIRBY3_SELECT2:
		playSound(1174, 30, true);
		HAL_Delay(100);
		playSound(1174, 30, true);
		playSound(1661, 30, true);
		playSound(2093, 30, true);
		break;
	case MusicNumber::KIRBY3_SELECT3:
		playSound(1174, 90, true);
		playSound(1661, 90, true);
		playSound(2093, 90, true);
		break;
	}
}

Speaker* Speaker::getInstance(){
	static Speaker instance;
	return &instance;
}
