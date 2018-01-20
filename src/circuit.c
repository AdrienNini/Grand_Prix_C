#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <string.h>
#include "utils.h"


struct car *Cars;
void readSHM(void);
void writeSHM(void);

int main (int argc, char* argv[]){
	int i;
	int pidF;
	int numsVoit[20] = {44,77,3,33,5,7,31,11,31,19,18,14,2,10,55,8,20,27,30,9};
	// mount the share memory
	if(mountSHM() == -1){
		perror("Error init share memory in race");
		return 1;
	} else {
		printf("Shared Memory mounted !\n");
	}
	//init the sharmemory
	for(i = 0; i < 20; i++){
		Cars[i].id = numsVoit[i];
		Cars[i].crashed = 0;
	}
	writeSHM();

	//create the cars
	i = 0;
	for(i = 0; i < 1; i++){
		if((pidF = fork()) == -1){
			perror("Error fork");
			abort();
			return -1;
		}
		if(pidF == 0) {
			
			sleep(2);
			readSHM();
			printf("Car %d \n\tTime for sector 1: %d", Cars[i].id, Cars[i].sectorsTime[0]);
	
		
		 } else  {
		
			char* filePath = "../bin/voiture";
			char buffInt[4];
			sprintf(buffInt, "%d", i);
			char* args[] = {filePath, buffInt, NULL};
			
			if(execv(filePath, args) == -1){
				printf("%d", i);
				perror("Error exec car");
				return -1;
			}

		}
		
	}

	dismountSHM();
	return 0;
	
} 

void readSHM() {
	memcpy(Cars, shmCar, sizeof(struct car)*20);	
}

void writeSHM(){
	shmCar = Cars;
}
