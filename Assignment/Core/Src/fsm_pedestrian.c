/*
 * fsm_pedestrian.c
 *
 *  Created on: Nov 28, 2023
 *      Author: thien
 */

#include "global.h"

void fsm_pedestrian(void){
	switch(pedestrian_flag)
	{
		case Pedestrian_INIT:
			clearPedestrian();
			break;
		case Pedestrian_RED:
			if(IsTimerUp(3) == 1)
			{
				pedestrian_flag = Pedestrian_INIT;
			}
			displayPedestrianRed();
			break;
		case Pedestrian_GREEN:
			if(IsTimerUp(3) == 1)
			{
				pedestrian_flag = Pedestrian_INIT;
			}
			displayPedestrianGreen();
			break;
	}
}
