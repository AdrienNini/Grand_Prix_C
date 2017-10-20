//RANDOM TIME GENERATOR
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

// RANDOM VARs
int randTime;
int randPool[20];

// SHARED MEMORY VARs
key_t key = 77;
int shmid;
char *shmaddr;
int size = 1;



int main (int argc, char *argv[]) {

	// CREATE A SHARED MEMORY
	initSH();	
	
	// CHECK IF SOMETHING STORED IN MEMORY
	attachSh();	


	srand((unsigned)time(NULL));
	int a, b;
	for (a = 0; a < 20; a++) {
		randTime = rand() % 30;
		randPool[a] = randTime;
		printf("%d\n", randTime);
	}


	//printf("%d\n", randPool[rand() % 20];


	return 0;
}

int initSH() {
	if ((shmid = shmget(key, size, IPC_CREAT)) == -1) {
		perror("shmget: shmget failed"); 
		exit(1);
	} else {
		printf("shmget: shmget succeded !\n");
		return 0;
	}
}

int attachSh() {
	shmaddr = shmat(shmid, NULL, 0); 
	return 0;
}

