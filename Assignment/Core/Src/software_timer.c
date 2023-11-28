/*
 * software_timer.c
 *
 *  Created on: Nov 28, 2023
 *      Author: thien
 */

#include "software_timer.h"

int timer_counter[TIMER];
int timer_flag[TIMER];

int IsTimerUp(int timer)
{
	return (timer_flag[timer] == 1);
}

void setTimer(int timer, int duration)
{
	timer_counter[timer] = duration;
	timer_flag[timer] = 0;
}
void timerRun(void)
{
	for (int timer = 0; timer < TIMER; timer++)
	{
		if(timer_counter[timer] > 0)
		{
			timer_counter[timer]--;
			if(timer_counter[timer] == 0)
				timer_flag[timer] = 1;
		}
	}
}
