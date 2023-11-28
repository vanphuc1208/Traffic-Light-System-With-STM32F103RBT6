/*
 * global.h
 *
 *  Created on: Oct 22, 2023
 *      Author: OS
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"
#include"button.h"
#include"software_timer.h"
#include"displayLed.h"
#include "fsm_normal_state.h"
#include "scheduler.h"

#define INIT 0

#define TIMER	  3

#define RedGreen  1
#define RedAm  	  2
#define GreenRed  4
#define AmRed     5
#define ManRed   10
#define ManAm    11
#define ManGreen 12


extern int timeRed;
extern int timeYellow;
extern int timeGreen;
extern int status;
extern int time1,time2;

#endif /* INC_GLOBAL_H_ */
