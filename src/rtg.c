//RANDOM TIME GENERATOR
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


int randTime;
int randPool[20][5];

int main (int argc, char *argv[]) {

	srand((unsigned)time(NULL));
	int a, b;
	for (a = 0; a < 20; a++){
		for (b = 0; b < 5; b++){
			randTime = rand() % 30;
			randPool[a][b] = randTime;
		}
	}

	printf("%d\n", randPool[rand() % 20][rand() % 5]);


	return 1;
 

}
