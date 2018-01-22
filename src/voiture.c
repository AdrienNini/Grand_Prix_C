#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "utils.h"
#include "rtg.h"

int memPos;
struct car Car;


void writeSectorTime(int sector);
int checkBestSectorTime(int sector);
void calcLap(void);
void writeLapTime(void);
int getTime(int min, int max);
int isCrashed(void);
int isPit(void);


int main (int argc, char *argv[]) {
	
	//printf("Bonjour je suis la voiture %s \n", argv[1]);
	
	// Create and mount the shared memory
	if (mountSHM() == -1){
		printf("Creation or Mounting of SHM failed");
		return 1;		
	}
	
	// Find position in SHM
	
	memPos = atoi(argv[1]);
	

	// Init Car	
	Car = shmCar[memPos];
	

	// Race simulation
	int j = 0;
	for (j = 0; j < 30; j++)  { // Loop while !raceisOver
		

		int i;
		for (i = 0; i < sizeof(Car.sectorsTime)/sizeof(int) && !Car.crashed; i++) {		
			
			//printf("Loop \n");			

			if (!Car.crashed) { // isCrashed ?
				Car.sectorsTime[i] = getTime(25000, 35000); // Generate sector time
			//	printf("Time generated for car n°: %d\n", Car.id);
			//	writeSectorTime(i); 
			}
		}
		writeSectorTime(0);

		//if (isPit() && !Car.crashed) {
		//	Car.pitFlag = 1;
		//	Car.pitTime = getTime(5, 10);
		//}

		//if (!Car.crashed) {
		//	calcLap();
		//}


	}
}


void writeSectorTime(int sector) {
	// Write the best sector time in the Shared Memory
	if (checkBestSectorTime(sector)) {
		shmCar[memPos].sectorsTime[sector] = Car.sectorsTime[sector];
	}
}

int checkBestSectorTime(int sector) {
	// Check if the new sector time is better than the last best one (general)
	return shmCar[memPos].sectorsTime[sector] < Car.sectorsTime[sector];
}

void calcLap() {
	// Calc the total lap time
	int totalLap = 0, i;
	for (i = 0; i < sizeof(Car.sectorsTime)/sizeof(int); i++) {
		totalLap += Car.sectorsTime[i];
	}
	
}

void writeLapTime() {
	// Write the lap time in the Shared Memory
	if (shmCar[memPos].lapTime < Car.lapTime) {
		shmCar[memPos].lapTime = Car.lapTime;
	}
}

int getTime(int min, int max) {
	// Call the time generator function
	return randomRtg(min, max);
}


int isCrashed() {
	// decide randomly if car is crashed
	// 5% chance of crash
	//srand(time(NULL));
	
	return 0;	
}
	
int isPit() {
	// decide randomly is car go to pit
	// 20% change of pit stop
	return !Car.pitFlag;
}
