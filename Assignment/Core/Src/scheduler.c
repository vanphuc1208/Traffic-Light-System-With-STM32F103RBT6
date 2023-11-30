/*
 * scheduler.c
 *
 *  Created on: Nov 25, 2023
 *      Author: OS
 */


#include "scheduler.h"
#include <stdio.h>
#include <stdlib.h>
typedef struct
{
	void ( * pTask)(void);
	uint32_t Delay;
	uint32_t Period;
	uint8_t RunMe;
	// uint32_t TaskID;
} sTask;

struct Node
{
	sTask data;
	struct Node* next;
};


struct Node* head = NULL;

void SCH_Init(void)
{
	head = NULL;
}

void AddNode(sTask NewTask)
{
	struct Node* NewNode = (struct Node*)malloc(sizeof(struct Node));
	NewNode -> data.pTask = NewTask.pTask;
	NewNode -> data.Delay = NewTask.Delay;
	NewNode -> data.Period = NewTask.Period;
	NewNode -> data.RunMe = NewTask.RunMe;
	NewNode -> next = NULL;

	// List is empty, just addNode
	if(head == NULL)
	{
		head = NewNode;
		return;
	}
	struct Node* temp = head;

	// If the list has A5 B3 C2 Adding D3  ->  D3 A2 B3 C2
	if(NewNode -> data.Delay < temp -> data.Delay )
	{
		temp -> data.Delay -= NewNode -> data.Delay;
		NewNode -> next = temp;
		head = NewNode;
		return;
	}

	// If the list has A5 B3 C2 Adding D9  ->  A5 B3 D1 C1
	while(temp -> next != NULL)
	{
		NewNode -> data.Delay -= temp -> data.Delay;
		if(NewNode -> data.Delay <= temp -> next -> data.Delay)
			break;

		temp = temp -> next;
	}

	// temp current in B3 and D become D1
	if(temp -> next == NULL)
	{
		NewNode -> data.Delay -= temp -> data.Delay;
		temp -> next = NewNode;
	}
	else
	{
		temp -> next -> data.Delay -= NewNode -> data.Delay; // convert C2 to C1
		NewNode -> next = temp -> next;
		temp -> next = NewNode;
	}
}

void DeleteBegin()
{
	struct Node* temp = head;
	if(temp == NULL) return;
	head = head -> next;
	free(temp);
}

void SCH_Add_Task(void (*p_function)(), uint32_t DELAY, uint32_t PERIOD)
{
	sTask NewTask;
	NewTask.pTask = p_function;
	NewTask.Delay = DELAY;
	NewTask.Period = PERIOD;

	if(NewTask.Delay == 0)
		NewTask.RunMe = 1;
	else
		NewTask.RunMe = 0;

	AddNode(NewTask);
}

void SCH_Update(void)
{
	if(head == NULL) return;

	if(head -> data.Delay <= 0)
		head -> data.RunMe = 1;
	else
		head -> data.Delay--;
}

void SCH_Dispatch_Tasks(void)
{
	if(head == NULL) return;

	if(head -> data.RunMe > 0)
	{
		(*head -> data.pTask)();
		sTask NewTask = head -> data;
		DeleteBegin();

		if(NewTask.Period != 0)
			SCH_Add_Task(NewTask.pTask, NewTask.Period, NewTask.Period);
	}

	 HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
}
