/*
 * buzzer.c
 *
 *  Created on: Nov 28, 2023
 *      Author: OS
 */

#include "buzzer.h"

void buzzer(int duty_cycle)
{
	 htim3.Instance->CCR1 = duty_cycle;
//     __HAL_TIM_SET_AUTORELOAD(&htim3, buzzerValue*2); // Increasing frequency : Auto-Reload Register - ARR
//     __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, buzzerValue); // Increasing duty cycle: Capture/Compare Register - CCR
}
