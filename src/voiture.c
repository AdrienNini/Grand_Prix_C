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
	
	
	// Create and mount the shared memory
	// N'affiche pas d'erreurs à la création et au montage de la shared memory
	if (mountSHM() == -1){
		printf("Creation or Mounting of SHM failed");
		return 1;		
	} else {
		printf("<voiture>\tshmid = %d\n", shmid); // Affiche le shmid récupéré par le processus voiture
	}
	
	// Find position in SHM
	
	memPos = atoi(argv[1]);
	

	// Init Car
	// Problèmes:
	// 	Ne récupère pas le numéro de la voiture, précédemment écrit par le circuit
	Car = shmCar[memPos];
	

	// Race simulation
	int j;
	for (j = 0; j < 30; j++)  {
		

		int i;
		for (i = 0; i < sizeof(Car.sectorsTime)/sizeof(int) && !Car.crashed; i++) {		
			

			if (!Car.crashed) { // isCrashed ?
				Car.sectorsTime[i] = getTime(25000, 35000); // Generate sector time
				writeSectorTime(i); 
			} else {
				printf("<voiture %d>\tCar crashed !\n", memPos);
			}
		}

		sleep(1);

		if (isPit() && !Car.crashed) {
			printf("<voiture %d>\tCar stopped at pit\n", memPos);
			Car.pitFlag = 1;
			Car.pitTime = getTime(5, 10);
		}

		if (!Car.crashed) {
			calcLap();
			writeLapTime();
		}


	}

	Car.finished = 1;
	shmCar[memPos].finished = Car.finished;	

}


void writeSectorTime(int sector) {
	// Write the best sector time in the Shared Memory
	
	// Test : Vérifie que la lecture et l'écrite dans la Shared Memory fonctionne
	printf("<voiture %d>\tLocal data : %d\n", memPos, Car.sectorsTime[sector]); // Affiche les données de la structure car en locale

	if (checkBestSectorTime(sector)) {
		shmCar[memPos].sectorsTime[sector] = Car.sectorsTime[sector];
		printf("<voiture %d>\tShared memory data : %d\n", memPos, shmCar[memPos].sectorsTime[sector]); // Affiche les données de la structure car en shared memory
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
	return randomRtg(0, 1000) < 200 ? 1: 0;
}
	
int isPit() {
	return randomRtg(0, 1000) < 200 ? 1: 0;
}
