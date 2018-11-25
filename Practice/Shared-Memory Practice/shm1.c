/*** from dust i have come, dust i will be ***/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/shm.h>
#include<unistd.h>

#include "sharedMem.h"

int main()
{
    int running = 1, shmID;
    void *shared_mem = (void *)0;

    struct data *shared_stuff;
    shmID = shmget((key_t)1234, sizeof(struct data*), 0666 | IPC_CREAT);

    if(shmID == -1){
        printf("shmget failed\n");
        exit(EXIT_FAILURE);
    }

    shared_mem = shmat(shmID, (void*)0, 0);
    if(shared_mem == (void*)-1){
        printf("shmat failed\n");
        exit(EXIT_FAILURE);
    }

    printf("memory attached at %p\n", shared_mem);

    shared_stuff = (struct data*)shared_mem;
    shared_stuff->n = 0;

    while(running)
    {
        //printf("in shmt1 while\n");
        if(shared_stuff->n){
            printf("you wrote: %s\n",shared_stuff->str);
            sleep(2);
            shared_stuff->n = 0;

            if(strncmp(shared_stuff->str,"end",3) == 0)
                running = 0;
        }
    }

    if(shmdt(shared_mem) == -1){
        printf("shmdt failed\n");
        exit(EXIT_FAILURE);
    }

    if(shmctl(shmID, IPC_RMID, 0) == -1){
        printf("shmctl(IPC_RMID) failed\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
