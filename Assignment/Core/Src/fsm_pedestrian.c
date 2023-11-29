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

			buzzerValue = 0;
			buzzer();
			break;

		case Pedestrian_RED:
			if(isTimerUp(3) == 1)
				pedestrian_flag = Pedestrian_INIT;

			displayPedestrianRed();

			buzzerValue = 0;
			buzzer();
			break;

		case Pedestrian_GREEN:
			if(isTimerUp(3) == 1)
				pedestrian_flag = Pedestrian_INIT;

			displayPedestrianGreen();

			buzzer();
			break;
	}
}
