#include <stdio.h>

struct car {
	int id;
	bool pitFlag;
	bool  crashed;
	int[3] sectorsTime;
	int lapTime;
	int pitTime;
	int raceTime;
};

// Shared Memory Variables

key_t key = 5678;
int shmid;
char *shmaddr;
int size = sizeof(struct car * 20);

int memPos;

int main (int argc, char *argv[]) {
	
	// Create and mount the shared memory
	if (!mountSHM()){
		printf("Creation or Mounting of SHM failed");
		return 1;		
	}
	

	// Init Car	
	struct car Car;
	Car.id = (int) argv[1]; // id from params
	Car.outFlag = false;
	
	// Find position in SHM
	int i;
	for (i = 0; i < size; i++) {
		if (*shmaddr[i].id == Car.id) {
			memPos = i;
		}
	}

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

bool checkBestSectorTime(int sector) {
	// Check if the new sector time is better than the last best one (general)
	return *shmaddr[memPos].sectorsTime[sector] < Car.sectorsTime[sector];
}

void calcLap() {
	// Calc the total lap time
	// Check the Best Lap time 
	// Write the Best Lap time to SHM
}

void writeLapTime() {
	// Write the lap time in the Shared Memory
}

int getTime() {
	// Call the time generator function
}

bool mountSHM() {
	// Init Shared Memory
	if ((shmid = shmget(key, size, IPC_CREAT|0660)) == -1) {
		perror("shmget: shmget failed");
		return false;
	} else {
		// Attach SHM
		if ((shmaddr = shmat(id, NULL, 0)) == (char *) -1) {
			perror("shmat: shmat failed");
			return false;
		} else {
			return true;
		}
	}	
}

bool isCrashed() {
	// decide randomly if car is crashed
}
	
bool isPit() {
	// decide randomly is car go to pit
}
