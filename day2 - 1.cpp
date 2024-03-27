#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHMSZ 27

int main() {
    int shmid;
    key_t key;
    char *shm, *s;

    key = 5678;

    // Locate the shared memory segment
    if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    // Attach to the shared memory
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    // Read from the shared memory
    for (s = shm; *s != '\0'; s++)
        putchar(*s);
    putchar('\n');

    // Notify the other process
    *shm = '*';

    // Detach from the shared memory
    shmdt(shm);

    return 0;
}
