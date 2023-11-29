/*
 * fsm_normal_state.c
 *
 *  Created on: Oct 22, 2023
 *      Author: OS
 */

#include "global.h"

void increase()
{
	time1++;
	if(time1 > 99)
		time1 = 1;
}

void balance(int RED, int AMBER, int GREEN)
{
	if(RED > timeRed)
	{
		timeYellow = timeYellow * (RED / timeRed);
		timeGreen = timeGreen * (RED / timeRed);
		timeRed = RED;
	}
	else if(AMBER > timeYellow)
	{
		timeRed = timeRed * (AMBER / timeYellow);
		timeGreen = timeGreen * (AMBER / timeYellow);
		timeYellow = AMBER;
	}
	else if(GREEN > timeGreen)
	{
		timeRed = timeRed * (GREEN / timeGreen);
		timeYellow = AMBER * (GREEN / timeGreen);
		timeGreen = GREEN;
	}
	else if(RED < timeRed)
	{
		timeYellow = (RED / 5) * 2;
		timeGreen = (RED / 5) * 3;
		timeRed = RED;
	}
	else if(AMBER < timeYellow)
	{
		timeRed = (AMBER / 2) * 5;
		timeGreen = (AMBER / 2) * 3;
		timeYellow = AMBER;
	}
	else if(GREEN < timeGreen)
	{
		timeRed = (GREEN / 3) * 5;
		timeYellow = (GREEN / 3) * 2;
		timeGreen = GREEN;
	}
}

void normalState(void)
{
	switch(status)
	{
	case INIT:
		clearAllLed1();
		clearAllLed2();
		status = RedGreen;
		setTimer(0, timeGreen * 100);
		setTimer(1, 100);
		time1 = timeRed;
		time2 = timeGreen;
		break;
	case RedGreen:
		displayRed1();
		displayGreen2();
		if(IsTimerUp(0) == 1)
		{	// Transit State
			status = RedAm;
			setTimer(0, timeYellow * 100);
			setTimer(1, 100);
			time1 = timeYellow;
			time2 = timeYellow;
		}

		if(IsTimerUp(1) == 1)
		{	// Update Time
			setTimer(1, 100);
			time1--;
			time2--;
		}

		if(is_button_pressed(1))
		{
			status = ManRed;
			time1 = timeRed;
			time2 = 2;
			clearAllLed1();
			clearAllLed2();
			setTimer(2, 25);
		}
		if(is_button_pressed(0))
		{
			pedestrian_flag = Pedestrian_RED;
			setTimer(3, (timeRed + timeGreen) * 100);
		}

		break;
	case RedAm:
		displayRed1();
		displayYellow2();
		if(IsTimerUp(0)==1)
		{	// Transit State
			status = GreenRed;
			setTimer(0, timeGreen * 100);
			setTimer(1, 100);
			time1 = timeGreen;
			time2 = timeRed;
			if(pedestrian_flag == Pedestrian_RED)
				pedestrian_flag = Pedestrian_GREEN;
		}

		if(IsTimerUp(0) == 1)
		{	// Update Time
			time1--;
			time2--;
			setTimer(1, 100);
		}

		if(is_button_pressed(1))
		{
			status = ManRed;
			time1 = timeRed;
			time2 = 2;
			clearAllLed1();
			clearAllLed2();
			setTimer(2, 25);
		}

		if(is_button_pressed(0))
		{
			pedestrian_flag = Pedestrian_RED;
			setTimer(3, (timeRed + timeGreen) * 100);
		}

		break;
	case GreenRed:
		displayGreen1();
		displayRed2();
		if(IsTimerUp(0) == 1)
		{	// Transit State
			status = AmRed;
			setTimer(0, timeYellow * 100);
			setTimer(1, 100);
			time1 = timeYellow;
			time2 = timeYellow;
		}

		if(IsTimerUp(1)==1)
		{	// Update Time
			setTimer(1, 100);
			time1--;
			time2--;
		}

		if(timeYellow < 5 && time1 <= 5 - timeYellow)
				buzzerValue= 512*(5- timeYellow - time1);

		if(is_button_pressed(1))
		{
			status = ManRed;
			time1 = timeRed;
			time2 = 2;
			clearAllLed1();
			clearAllLed2();
			setTimer(2, 25);
		}

		if(is_button_pressed(0))
		{
			pedestrian_flag = Pedestrian_GREEN;
			setTimer(3, (timeRed + timeGreen) * 100);
		}

		break;
	case AmRed:
		displayYellow1();
		displayRed2();
		if(IsTimerUp(0) == 1)
		{	// Transit State
			status = RedGreen;
			setTimer(0, timeGreen * 100);
			setTimer(1, 100);
			time1 = timeRed;
			time2 = timeGreen;
			if(pedestrian_flag == Pedestrian_GREEN)
				pedestrian_flag = Pedestrian_RED;
		}

		if (timeYellow >=5 && time1 <=5)
			buzzerValue= 512*(5 - time1);

		if(timeYellow < 5)
			buzzerValue+=256*(5 - time1);

		if(IsTimerUp(1) == 1)
		{	// Update Time
			time1--;
			time2--;
			setTimer(1, 100);
		}

		if(is_button_pressed(1))
		{
			status = ManRed;
			time1 = timeRed;
			time2 = 2;
			clearAllLed1();
			clearAllLed2();
			setTimer(2, 25);
		}

		if(is_button_pressed(0))
		{
			pedestrian_flag = Pedestrian_GREEN;
			setTimer(3, (timeRed + timeGreen) * 100);
		}

		break;
	case ManRed:
		if(IsTimerUp(2) == 1)
		{
			setTimer(2, 25);
			toggleRed();
		}
		if(is_button_pressed(2))
			increase();

		if(is_button_pressed(3))
			balance(time1, timeYellow, timeGreen);

		if(is_button_pressed(1))
		{
			status = ManAm;
			time1 = timeYellow;
			time2 = 3;
			clearAllLed1();
			clearAllLed2();
			setTimer(2, 25);
		}
		break;
	case ManAm:
		if(IsTimerUp(2) == 1)
		{
			setTimer(2, 25);
			toggleYellow();
		}
		if(is_button_pressed(2))
			increase();

		if(is_button_pressed(3))
			balance(timeRed, time1, timeGreen);

		if(is_button_pressed(1))
		{
			status = ManGreen;
			time1 = timeGreen;
			time2 = 4;
			clearAllLed1();
			clearAllLed2();
			setTimer(2, 25);
		}
		break;
	case ManGreen:
		if(IsTimerUp(2) == 1)
		{
			setTimer(2, 25);
			toggleGreen();
		}
		if(is_button_pressed(2))
			increase();

		if(is_button_pressed(3))
			balance(timeRed, timeYellow, time1);

		if(is_button_pressed(1))
		{
			status = RedGreen;
			setTimer(0, timeGreen * 100);
			setTimer(1, 100);
			time1 = timeRed;
			time2 = timeGreen;
		}
		break;
	default:
		break;
	}
}
