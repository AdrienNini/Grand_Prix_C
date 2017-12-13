#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "utils.h"


int memPos;

int main (int argc, char *argv[]) {
	
	// Create and mount the shared memory
	if (!mountSHM()){
		printf("Creation or Mounting of SHM failed");
		return 1;		
	}
	
	// Find position in SHM
	
	memPos = parseInt(argv[1]);
	

	// Init Car	
	struct car Car;
	Car.crashed = -1;
	

	// Init SHM in the Parent Process
	/* int i;
	for (i = 0; i < size; i++) {
		if (*shmaddr[i].id == Car.id) {
			memPos = i;
		}
	}
	*/

	// Race simulation
	while (!raceIsOver && !crashed) { // Loop while !raceisOver
		int i;
		for (i = 0; i < sizeof(sectorsTime)/sizeof(int) && !crashed; i++) {		

			if (!(crashed = isCrashed())) { // isCrashed ?
				Car.sectorsTime[i] = getTime(); // Generate sector time
				writeSectorTime(i); 
			}
			
		}

		if (isPit() && !crashed) {
			Car.pitFlag = 1;
			pitTime = getTime();
		}

		if (!crashed) {
			calcLap();
		}
	} 	
}


void writeSectorTime(int sector) {
	// Write the best sector time in the Shared Memory
	if (checkBestSectorTime(sector)) {
		*shmaddr[memPos].sectorsTime[sector] = Car.sectorsTime[sector];
	}
}

int checkBestSectorTime(int sector) {
	// Check if the new sector time is better than the last best one (general)
	return *shmaddr[memPos].sectorsTime[sector] < Car.sectorsTime[sector];
}

void calcLap() {
	// Calc the total lap time
	int totalLap = 0, i;
	for (i = 0; i < sizeof(Car.sectorsTime)/sizeof(int); i++) {
		totalLcap += Car.sectorTime[i];
	}
	
}

void writeLapTime() {
	// Write the lap time in the Shared Memory
	if (*shmaddr[memPos].lapTime < Car.lapTime) {
		*shmadd[memPos].lapTime = Car.lapTime;
	}
}

int getTime() {
	// Call the time generator function
}


int isCrashed() {
	// decide randomly if car is crashed
	// 5% chance of crash
	//srand(time(NULL));
	
	return -1;	
}
	
int isPit() {
	// decide randomly is car go to pit
	// 20% change of pit stop
	return !Car.pitFlag;
}
