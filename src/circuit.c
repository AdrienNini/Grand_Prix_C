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
int finish(void);

int main (int argc, char* argv[]){
	
	int i, j;
	int pidF;
	int numsVoit[20] = {44,77,3,33,5,7,31,11,31,19,18,14,2,10,55,8,20,27,30,9};
	
	// Mount the share memory
	// Tests: 
	// 	Vérification que les shmid sont identiques
	// 	Après plusieurs testes, les shmid sont toujours identiques entre le processus circuit et les voitures
	if(mountSHM() == -1){ // Le montage de la shared memory ne présente aucune erreur.
		perror("Error init share memory in race");
		return 1;
	} else {
		printf("Shared Memory mounted !\n");
		printf("<circuit> shmid = %d\n", shmid); // Affiche le shmid récupérer par le circuit
	}

	Cars = malloc(20*sizeof(struct car));
	
	// Init the sharmemory
	for(i = 0; i < 20; i++){
		Cars[i].id = numsVoit[i];
		Cars[i].crashed = 0;
	}
	writeSHM();

	// Create the cars
	for(j = 0; j < 20; j++){
		if((pidF = fork()) == -1){
			perror("Error fork");
			abort();
			return -1;
		}
		if(pidF == 0) {
		
		// Problème: Boucle infinie 
		// Le processsus circuit ne lit pas les bonnes informations dans la Shared Memory
		//
		//	while (finish()==0) {	
				readSHM();
				printf("Car %d \tTime for sector 1: %d\n", Cars[j].id, Cars[j].sectorsTime[0]);
		//	}
		
		 } else  {
		
			char* filePath = "../bin/voiture";
			char buffInt[4];
			sprintf(buffInt, "%d", j);
			char* args[] = {filePath, buffInt, NULL};
			
			if(execv(filePath, args) == -1){ // Démarre correctement toutes les voitures
				printf("%d", j);
				perror("Error exec car");
				return -1;
			}

		}
		
	}

	dismountSHM();
	return 0;
	
} 

// Termine la course lorsque toutes les voitures ont terminé leurs tours
int finish() {
	int cpt = 0;
	int i;
	for (i = 0; i < 20; i++){
		if (shmCar[i].finished == 1) {
			cpt++;
		}
	}
	if (cpt == 20) return 1;
	else return 0;
}

// Lis les données dans la shared memory
// Problèmes: Ne récupère pas les bonnes informations
// Tests: donne le même résultat avec un memcpy(); et un Cars = shmCar;
void readSHM() {
	memcpy(Cars, shmCar, sizeof(struct car)*20);	
}

// Ecris les données dans la shared memory
// Problèmes:
// 	Les informations sont bien enregistrée sur la shared memory 
// 	Mais les processus voiture n'arrivent pas à lire ces informations
// 	Comme si les shared memory étaient différentes
void writeSHM(){
	shmCar = Cars;
}
