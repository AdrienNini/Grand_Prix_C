struct car {
         int id;
         bool pitFlag;
         bool  crashed;
         int[3] sectorsTime;
         int lapTime;
         int pitTime;
         int raceTime;
};

bool mountSHM() {
        // Init Shared Memory
        if ((shmid = shmget(key, size, IPC_CREAT|0660)) == -1) {
                perror("shmget: shmget failed");
                return false;
        } else {
                // Attach SHM
                if ((shmaddr = shmat(shmid, NULL, 0)) == (char *) -1) {
                        perror("shmat: shmat failed");
                        return false;
                } else {
                        return true;
                }
        }
}
