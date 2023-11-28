/*
 * buzzer.c
 *
 *  Created on: Nov 28, 2023
 *      Author: OS
 */

#include "buzzer.h"

void buzzer()
{
	 htim3.Instance->CCR1=buzzerValue;
}
