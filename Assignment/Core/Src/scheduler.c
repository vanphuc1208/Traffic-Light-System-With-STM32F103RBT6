/*
 * scheduler.c
 *
 *  Created on: Nov 25, 2023
 *      Author: OS
 */


#include "scheduler.h"
#include <stdio.h>
#include <stdlib.h>
typedef struct {
	void ( * pTask)(void);
	uint32_t Delay;
	uint32_t Period;
	uint8_t RunMe;
	//uint32_t TaskID;
} sTask;

struct Node{
	sTask data;
	struct Node* next;
};


struct Node* head=NULL;

void SCH_Init(void) {
	head=NULL;
}

void addNode(sTask newTask) {
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->data.pTask = newTask.pTask;
	newNode->data.Delay = newTask.Delay;
	newNode->data.Period = newTask.Period;
	newNode->data.RunMe = newTask.RunMe;
	newNode->next = NULL;
	//list is empty just addNode
	if(head == NULL) {
		head=newNode;
		return;
	}
	struct Node* tmp=head;
	//if the list has A5 B3 C2  we add D3 -> D3 A2 B3 C2
	if(newNode->data.Delay < tmp->data.Delay ) {
		tmp->data.Delay-= newNode->data.Delay;
		newNode->next=tmp;
		head=newNode;
		return;
	}

	// if the list has A5 B3 C2 we add D9 -> A5 B3 D1 C1
	while(tmp->next !=NULL) {
		newNode->data.Delay -= tmp->data.Delay;
		if(newNode->data.Delay <= tmp->next->data.Delay) {
			break;
		}
		tmp=tmp->next;
	}
	// tmp dang o B3 va D tro thanh D1
	if(tmp->next ==NULL) {
		newNode->data.Delay-=tmp->data.Delay;
		tmp->next=newNode;
	}
	else {
		tmp->next->data.Delay-= newNode->data.Delay; // chuyen C2 thanh C1
		newNode->next=tmp->next;
		tmp->next=newNode;
	}
}

void deleteBegin() {
	struct Node* tmp=head;
	if(tmp==NULL) return;
	head=head->next;
	free(tmp);
}

void SCH_Add_Task(void (*p_function)(), uint32_t DELAY, uint32_t PERIOD){
	sTask newTask;
	newTask.pTask=p_function;
	newTask.Delay=DELAY;
	newTask.Period=PERIOD;
	if(newTask.Delay==0) {
		newTask.RunMe=1;
	}
	else {
		newTask.RunMe=0;
	}
	addNode(newTask);
}

void SCH_Update(void) {
	if(head==NULL) return;
	if(head->data.Delay <=0) {
		head->data.RunMe=1;
	}
	else {
		head->data.Delay--;
	}
}

void SCH_Dispatch_Tasks(void) {
	if(head==NULL) return;
	if(head->data.RunMe > 0) {
		(*head->data.pTask)();
		sTask newTask=head->data;
		deleteBegin();
		if(newTask.Period !=0) {
			SCH_Add_Task(newTask.pTask, newTask.Period, newTask.Period);
		}
	}
}
