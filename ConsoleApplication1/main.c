#include "header.h"

int main() {

	Queue expressIsle, normalIsle;
	int sTime = 0;

	initialQueue(&expressIsle, &normalIsle);
	srand(time(NULL));

	do {
		sTime = lengthOfSimulation();
		runApp(&expressIsle, &normalIsle, sTime);

	} while (1);

	return 0;
}