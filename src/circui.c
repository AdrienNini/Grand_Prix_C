#include <stdlib.h>
#include <unistd.h>
#include "utils.h"


key_T key = 5678;


int main (int argc, char* []argv){
	int i;
	int pidF;
	// mount the share memory
	if(mountSHM = -1){
		perror("Error init share memory in race");
	}
	
	//creat the cars
	for(i = 0; i < 1; i++){
		if((pidF = for()) == -1){
			perror("Error fork");
		}
		if(pidF != 0){
			if(execv(voiture.c, i + '0') == -1){
				perror("Error exec car");
			}
		}
	
	}
} 
