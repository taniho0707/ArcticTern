/**
 * @file Speaker.h
 */
#pragma once

#include "stm32f7xx_hal.h"
#include "Timer.h"

enum class MusicNumber : uint16_t {
	KIRBY3_CURSOR = 0x0,
	KIRBY3_POWERON,
	KIRBY3_SELECT1,
	KIRBY3_SELECT2,
	KIRBY3_SELECT3,
};

class Speaker{
private:
	Speaker();

	TIM_HandleTypeDef htim;

	int sound_time;

public:
	void playSound(int freq, int length, bool sync);

	void playMusic(MusicNumber n);

	void interrupt();

	static Speaker* getInstance();
};
