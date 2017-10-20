//RANDOM TIME GENERATOR
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

// RANDOM VARs
int randTime;
int randPool[20];

// SHARED MEMORY VARs
key_t key = 5678;
int shmid;
char *shmaddr;
int size = sizeof(int);


// VARIABLES
unsigned int randSeed = 1;


int main (int argc, char *argv[]) {

	// CREATE A SHARED MEMORY
	initSH();	
	attachSH(shmid);
	

	// CHECK IF SOMETHING IS IN MEMORY
	if (*shmaddr != 0) {
		randSeed = *shmaddr;
	} else {
		//printf("Nothing in Memory\n");
	}

	// GENERATE RANDOM NUMBER
	srand((unsigned)time(NULL) * randSeed );
	
	randTime = rand() % 35;
	
	// WRITE NEW RANDSEED ON MEMORY
	*shmaddr = hash(randTime);
	
	printf("%d\n", randTime);


	return 0;
}

int initSH() {
	if ((shmid = shmget(key, size, IPC_CREAT|0660)) == -1) {
		perror("shmget: shmget failed"); 
		exit(1);
	} else {
		//printf("shmget: shmget succeded !\n");
		return 0;
	}
}

int attachSH(int id) {
	if ((shmaddr = shmat(id, NULL, 0)) == (char *)  -1) {
		perror("shmat: shmat failed");
		exit(1);
	} else {
		//printf("shmat: shmat succeded !\n");
		return 0;
	}
}

int hash (int d){
	int pid = getpid(), result;
	result = d^pid;
	result = result * 891997;
	return abs(result);
}
