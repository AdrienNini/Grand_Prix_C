//RANDOM TIME GENERATOR
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


int randTime;
int[] randPool;

int main (int argc, char *argv[]) {

	srand((unsigned)time(NULL));
	int a, b;
	for (a = 0; a < 20; a++){
		for (b = 0; b < 5; b++){
			randTime = rand() % 30;
			printf("%d\n", randTime);
		}
	}


	return 1;

}
