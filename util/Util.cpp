/**
 * @file Util.cpp
 */

#include "Util.h"

void util::enableGpioClock(GPIO_TypeDef *gpio) {
	if (gpio == GPIOA) {
		__HAL_RCC_GPIOA_CLK_ENABLE();
	} else if (gpio == GPIOB) {
		__HAL_RCC_GPIOB_CLK_ENABLE();
	} else if (gpio == GPIOC) {
		__HAL_RCC_GPIOC_CLK_ENABLE();
	} else if (gpio == GPIOD) {
		__HAL_RCC_GPIOD_CLK_ENABLE();
	} else if (gpio == GPIOE) {
		__HAL_RCC_GPIOE_CLK_ENABLE();
	} else if (gpio == GPIOF) {
		__HAL_RCC_GPIOF_CLK_ENABLE();
	}
}
