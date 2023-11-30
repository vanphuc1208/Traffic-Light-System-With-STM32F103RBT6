/*
 * fsm_pedestrian.c
 *
 *  Created on: Nov 28, 2023
 *      Author: thien
 */

#include "global.h"

void fsm_pedestrian(void)
{
	switch(pedestrian_flag)
	{
		case Pedestrian_INIT:
			clearPedestrian();

			buzzer(0);
			break;

		case Pedestrian_RED:
			freq = 30;
			if(isTimerUp(3) == 1)
				pedestrian_flag = Pedestrian_INIT;

			displayPedestrianRed();

			buzzer(0);
			break;

		case Pedestrian_GREEN:
			if(isTimerUp(3) == 1)
				pedestrian_flag = Pedestrian_INIT;

			displayPedestrianGreen();

			if(isTimerUp(4) == 1)
			{
				setTimer(5, freq);
				setTimer(4, 100);
				freq += 10;
			}
			if(isTimerUp(5) == 0)
				buzzer(buzzerValue);
			if(isTimerUp(5) == 1)
				buzzer(0);

			break;
	}
}
