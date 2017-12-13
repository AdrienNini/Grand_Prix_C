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
char *shmaddr;
int size = sizeof(struct car) * 20;

int mountSHM() {
        // Init Shared Memory
        if ((shmid = shmget(key, size, IPC_CREAT|0660)) == -1) {
                perror("shmget: shmget failed");
                return -1;
        } else {
                // Attach SHM
                if ((shmaddr = shmat(shmid, NULL, 0)) == (char *) -1) {
                        perror("shmat: shmat failed");
                        return -1;
                } else {
                        return 0;
                }
        }
}
