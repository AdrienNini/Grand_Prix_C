#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include "utils.h"




int main (int argc, char* argv[]){
	int i;
	int pidF;
	int numsVoit[20] = {44,77,3,33,5,7,31,11,31,19,18,14,2,10,55,8,20,27,30,9};
	// mount the share memory
	if(mountSHM() == -1){
		perror("Error init share memory in race");
		return -1;
	}
	//init the sharmemory
	for(i = 0; i < 20; i++){
		shmCar[i].id = numsVoit[i];
	}
	//creat the cars
	for(i = 0; i < 20; i++){
		if((pidF = fork()) == -1){
			perror("Error fork");
			return -1;
		}
		if(pidF != 0){
			if(execv("../bin/voiture",(char) i) == -1){
				perror("Error exec car");
				return -1;
			}
		}
		
	}
	
} 
