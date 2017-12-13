#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include "utils.h"




int main (int argc, char* argv[]){
	int i;
	int pidF;
	// mount the share memory
	if(mountSHM() == -1){
		perror("Error init share memory in race");
	}
	
	//creat the cars
	for(i = 0; i < 20; i++){
		if((pidF = fork()) == -1){
			perror("Error fork");
		}
		if(pidF != 0){
			if(execv("../bin/voiture", i + '0') == -1){
				perror("Error exec car");
			}
		}
		
	}
	
} 
