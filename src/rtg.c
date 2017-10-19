//RANDOM TIME GENERATOR
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// RANDOM VARs
int randTime;
int randPool[20];

// SHARED MEMORY VARs
key_t key = 77;
int msgqid;
int type = 1;
int d;

struct msg {
	long type;
	int data;
};


int main (int argc, char *argv[]) {

	// CREATE A SHARED MEMORY (MSGQUEUE)
	if ((msgqid = msgget(key, 0666|IPC_CREAT)) == -1) {
		perror("msgget: msgget failed");
		exit(1);
	} else {
		printf("MsqgQueue: Creation succeded !\n");
	} 

	// CHECK IF SOMETHING STORED IN MEMORY
	if ((msgrcv(msgqid, &d, sizeof(d), type, IPC_NOWAIT)) == -1) {
		printf("no data in memory\n");
	} else {
		printf("Data : %d\n", d);
	}

	
	srand((unsigned)time(NULL));
	int a, b;
	for (a = 0; a < 20; a++) {
		randTime = rand() % 30;
		randPool[a] = randTime;
		printf("%d\n", randTime);
	}

	struct msg m;
	m.type = type;
	m.data = 123456;

	printf("%d\n", m.data);
	msgsnd(msgqid, &m, sizeof(m.data), 0);

	//printf("%d\n", randPool[rand() % 20];


	return 0;
}
