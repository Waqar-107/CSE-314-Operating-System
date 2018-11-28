/*** from dust i have come, dust i will be ***/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/sem.h>
#include "sem.h"

#define pfs(s) printf("%s", s);

int main(int argc, char *argv)
{
    int i;

    //semget() will create a new semaphore if not already exists, and if exists then acquire that
    sem_id = semget((key_t)1234, 1, 0666 | IPC_CREAT);

    if(argc > 1)
    {
        if(!set_semValue()){
            pfs("failed to initiate semaphore\n");
            exit(EXIT_FAILURE);
        }

        sleep(2);
    }

    for(i = 0; i < 5; i++)
    {
        if(!semaphore_p())exit(EXIT_FAILURE);

        pfs("hello\n");
        fflush(stdout);
        sleep(4);

        pfs("world\n");
        fflush(stdout);

        if(!semaphore_v())exit(EXIT_FAILURE);
    }

    printf("%d - finished\n", getpid());
    if(argc > 1){
        sleep(6);
        del_semValue();
    }

    exit(EXIT_SUCCESS);
}