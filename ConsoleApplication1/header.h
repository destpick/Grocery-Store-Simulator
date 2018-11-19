#ifndef GUARDCODE_H
#define GUARDCODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

typedef struct data {
	int customerNumber;
	int serviceTime;
	int totalTime;
}Data;

typedef struct node {
	Data *pData;
	struct node *next;
}Node;

typedef struct queue {
	Node *pHead;
	Node *pTail;
} Queue;


void enqueue(Queue *isle, int custNum);
void dequeue(Queue *isle);
Node * makeNode();
bool isEmpty(Queue *isle);
void displayQueue(Queue *isle);
void initialQueue(Queue *expressLane, Queue *normalLane);
int lengthOfSimulation();
int getRandom(int maxNum);
int getRandomNorm();
void runApp(Queue * expressLane, Queue *normalLane, int time);
void waitTime(Queue *isle);
void noLineWaitTime(Queue *isle);
void enqueuNormIsle(Queue *isle, int custNum);
#endif