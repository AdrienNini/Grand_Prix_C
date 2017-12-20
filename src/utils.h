struct car {
         int id;
         int pitFlag;
         int  crashed;
         int sectorsTime[3];
         int lapTime;
         int pitTime;
         int raceTime;
};

// SHARED MEMORY

key_t key = 6789;
int shmid;
struct car *shmCar;
int size = sizeof(struct car) * 20;

int mountSHM() {

	printf("1");

        // Init Shared Memory
        if ((shmid = shmget(key, size, IPC_CREAT|0660)) == -1) {
                printf("shmget: shmget failed");
                return -1;
        } else {
		printf("2");
                // Attach SHM
                if ((shmCar = (struct car*) shmat(shmid, NULL, 0)) == (struct car*)  -1) {
                        printf"shmat: shmat failed");
                        return -1;
                } else {
                        return 0;
                }
        }
}
