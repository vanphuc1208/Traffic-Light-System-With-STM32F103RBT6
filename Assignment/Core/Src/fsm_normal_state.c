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
	if(time1>99)
		time1 = 1;
}

void normalState(void) {
	switch(status) {
	case INIT:
		clearAllLed1();
		clearAllLed2();
		status=RedGreen;
		setTimer(0, timeGreen*100);
		setTimer(1, 100);
		time1=timeRed;
		time2=timeGreen;
		break;
	case RedGreen:
		displayRed1();
		displayGreen2();
		if(IsTimerUp(0)==1) {// transit state
			status=RedAm;
			setTimer(0, timeYellow*100);
			setTimer(1, 100);
			time1=timeYellow;
			time2=timeYellow;
		}

		if(IsTimerUp(1)==1) {// update time
			setTimer(1, 100);
			time1--;
			time2--;
		}

		if(is_button_pressed(1)) {
			status=ManRed;
			time1=timeRed;
			time2=2;
			clearAllLed1();
			clearAllLed2();
			setTimer(2, 25);
		}

		break;
	case RedAm:
		displayRed1();
		displayYellow2();
		if(IsTimerUp(0)==1) { //transit state
			status=GreenRed;
			setTimer(0, timeGreen*100);
			setTimer(1, 100);
			time1=timeGreen;
			time2=timeRed;
		}

		if(IsTimerUp(0)==1) { //update time
			time1--;
			time2--;
			setTimer(1, 100);
		}

		if(is_button_pressed(1)) {
			status=ManRed;
			time1=timeRed;
			time2=2;
			clearAllLed1();
			clearAllLed2();
			setTimer(2, 25);
		}

		break;
	case GreenRed:
		displayGreen1();
		displayRed2();
		if(IsTimerUp(0)==1) { //transit state
			status=AmRed;
			setTimer(0, timeYellow*100);
			setTimer(1, 100);
			time1=timeYellow;
			time2=timeYellow;
		}

		if(IsTimerUp(1)==1) {//update time
			setTimer(1, 100);
			time1--;
			time2--;
		}

		if(is_button_pressed(1)) {
			status=ManRed;
			time1=timeRed;
			time2=2;
			clearAllLed1();
			clearAllLed2();
			setTimer(2, 25);
		}
		break;
	case AmRed:
		displayYellow1();
		displayRed2();
		if(IsTimerUp(0)==1) { //transit state
			status=RedGreen;
			setTimer(0, timeGreen*100);
			setTimer(1, 100);
			time1=timeRed;
			time2=timeGreen;
		}

		if(IsTimerUp(1)==1) {//update time
			time1--;
			time2--;
			setTimer(1, 100);
		}

		if(is_button_pressed(1)) {
			status=ManRed;
			time1=timeRed;
			time2=2;
			clearAllLed1();
			clearAllLed2();
			setTimer(2, 25);
		}
		break;
	case ManRed:
		if(IsTimerUp(2)==1) {
			setTimer(2, 25);
			toggleRed();
		}
		if(is_button_pressed(2)) {
			increase();
		}
		if(is_button_pressed(3)) {
			timeRed=time1;
			timeGreen=timeRed-timeYellow;

		}
		if(is_button_pressed(1)) {
			status=ManAm;
			time1=timeYellow;
			time2=3;
			clearAllLed1();
			clearAllLed2();
			setTimer(2, 25);
		}
		break;
	case ManAm:
		if(IsTimerUp(2)==1) {
			setTimer(2, 25);
			toggleYellow();
		}
		if(is_button_pressed(2)) {
			increase();
		}
		if(is_button_pressed(3)) {
			timeYellow=time1;
			if(timeYellow >=timeRed) {
				timeRed=60;
			}
			timeGreen=timeRed-timeYellow;
		}
		if(is_button_pressed(1)) {
			status=ManGreen;
			time1=timeGreen;
			time2=4;
			clearAllLed1();
			clearAllLed2();
			setTimer(2, 25);
		}
		break;
	case ManGreen:
		if(IsTimerUp(2)==1) {
			setTimer(2, 25);
			toggleGreen();
		}
		if(is_button_pressed(2)) {
			increase();
		}
		if(is_button_pressed(3)) {
			timeGreen=time1;
			if(timeGreen >=timeRed) {
				timeRed=60;
			}
			timeYellow=timeRed-timeGreen;
		}
		if(is_button_pressed(1)) {
			status=RedGreen;
			setTimer(0, timeGreen*100);
			setTimer(1, 100);
			time1=timeRed;
			time2=timeGreen;
		}
		break;
	default:
		break;
	}
}

