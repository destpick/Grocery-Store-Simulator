#include"header.h"

void initialQueue(Queue *expressIsle, Queue *normalIsle) {
	expressIsle->pHead = NULL;
	expressIsle->pTail = NULL;
	normalIsle->pHead = NULL;
	normalIsle->pTail = NULL;
}

Node * makeNode() {
	Node *temp = NULL;
	temp=(Node*)malloc(sizeof(Node));
	if (temp != NULL) {
		temp->pData = (Data*)malloc(sizeof(Data));
		if (temp->pData != NULL) {
			temp->next = NULL;
			return temp;
		}
	}
	return NULL;
}

bool isEmpty(Queue* isle) {
	if (isle->pHead == NULL && isle->pTail == NULL) {
		return true;
	}
	else {
		return false;
	}
}

void enqueue(Queue *isle, int custNum) {
	Node *temp = NULL, *tail = isle->pTail;
	temp = makeNode();

	if (isle->pHead == NULL && isle->pTail==NULL) {
		isle->pHead = temp;
		isle->pTail = temp;
	}

	else {
		isle->pTail->next = temp;
		isle->pTail = temp;
	}
	temp->pData->serviceTime = getRandom(5);
	if (temp == isle->pHead) {
		temp->pData->totalTime = temp->pData->serviceTime;
	}
	else {
		temp->pData->totalTime = temp->pData + tail->pData->totalTime - 1;
	}
	temp->pData->customerNumber = custNum;
}

void enqueuNormIsle(Queue *isle, int custNum) {
	Node *temp = NULL, *tail = isle->pTail;

	temp = makeNode();

	if (isle->pHead == NULL && isle->pTail == NULL) {
		isle->pTail = temp;
		isle->pHead = temp;
	}
	else {
		isle->pTail->next = temp;
		isle->pTail = temp;
	}
	temp->pData->serviceTime = getRandomNorm();

	if (temp == isle->pHead) {
		temp->pData->totalTime = temp->pData->serviceTime;
	}
	else {
		temp->pData->totalTime = temp->pData->serviceTime + tail->pData->totalTime - 1;
	}
	temp->pData->customerNumber = custNum;
}

void displayQueue(Queue *isle) {
	Node *temp = NULL;
	temp = isle->pHead;

	if (temp == NULL) {
		printf("Isle is Empty.\n");
	}
	else {
		while (temp != NULL) {
			printf("Customer Number: %d\n\t Service Time: %d\n\tTotalTime: %d\n", temp->pData->customerNumber, temp->pData->serviceTime, temp->pData->totalTime);
			temp = temp->next;
		}
	}
}

void dequeue(Queue *isle) {
	Node *temp = isle->pHead;
	if (isle->pHead != NULL && isle->pTail != NULL) {
		if (isle->pHead == isle->pTail) {
			free(temp);
			isle->pHead = NULL;
			isle->pTail = NULL;
		}
		else {
			isle->pHead = isle->pHead->next;
			free(temp);
		}
	}
}
int lengthOfSimulation() {
	int choice = 0;
	do {
		printf("How long would you like the simulation to run? Enter Number in min.");
		scanf_s("%d", &choice);
	} while (choice < 1);
	return choice;
}

int getRandom(int maxNum) {
	int randomNumber;
	randomNumber = (rand() % maxNum) + 1;
	return randomNumber;
}

int getRandomNorm() {
	int randomNumber;
	randomNumber = 3 + rand() / (RAND_MAX / (6) + 1);
	return randomNumber;
}

void runApp(Queue * expressIsle, Queue *normalIsle, int time) {
	int eCus = 0, nCus = 0;
	int xNCCount = 0, xECCount = 0;
	bool nECus = false, nNCus = false;

	xECCount = getRandom(5);
	xNCCount = getRandomNorm();

	for (int i = 0; i < time; i++) {
		
		if (xECCount == 0) {
			eCus += 1;
			enqueue(expressIsle, eCus);
			xECCount = getRandom(5);
			nECus = true;
		}
		if (xNCCount == 0) {
			nCus += 1;
			enqueuNormIsle(normalIsle, nCus);
			xNCCount = getRandomNorm();
			nNCus = true;
		}
		if (expressIsle->pHead != NULL && nECus == false) {
			waitTime(expressIsle);
		}
		else {
			noLineWaitTime(expressIsle);
		}
		if (expressIsle->pHead != NULL && expressIsle->pHead->pData->serviceTime == 0) {
			dequeue(expressIsle);
		}
		if (nECus == false) {
			xECCount -= 1;
		}
		else {
			nECus == false;
		}
		if (normalIsle->pHead != NULL && nNCus == false) {
			waitTime(normalIsle);
		}
		if (normalIsle->pHead != NULL && normalIsle->pHead->pData->serviceTime == 0) {
			dequeue(normalIsle);
		}
		if(nNCus==false){
			xNCCount -= 1;
		}
		else {
			nNCus = false;
		}
		if ((i % 10 == 0)) {
			printf("Express Isle at %d minutes: \n", i);
			displayQueue(expressIsle);
			printf("\t\t ================");
			printf("Normal Isle at %d minutes: \n", i);
			displayQueue(normalIsle);

		}
	}
	system("pause");
}


void waitTime(Queue *isle) {
	Node * temp = isle->pHead;

	int wait = 0;

	while (temp != NULL) {
		if (temp == isle->pHead) {
			temp->pData->serviceTime -= 1;
		}
		wait = wait + temp->pData->serviceTime;

		temp->pData->totalTime = wait;
		temp = temp->next;
	}
}

void noLineWaitTime(Queue *isle) {

	if (isle->pHead != isle->pTail) {
		Node *temp = isle->pHead;
		int wait = 0;
		while (temp->next != NULL) {
			if (temp == isle->pHead) {
				temp->pData->serviceTime -= 1;
			}
			wait = wait + temp->pData->serviceTime;
			temp = temp->next;
		}
	}
}