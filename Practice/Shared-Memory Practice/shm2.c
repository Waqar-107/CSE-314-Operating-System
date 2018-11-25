/*** from dust i have come, dust i will be ***/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/shm.h>
#include<unistd.h>

#include "sharedMem.h"

int main()
{
    char buffer[BUFSIZ];
    int running = 1, shmID;
    void *shared_mem = (void *)0;

    struct data *shared_stuff;

    //key_t for requesting shared memory
    //0666 asks for access for permission, IPC_CREAT crreates a shared memory segment
    shmID = shmget((key_t)1234, sizeof(struct data*), 0666 | IPC_CREAT);

    if(shmID == -1){
        printf("shmget failed\n");
        exit(EXIT_FAILURE);
    }

    //shmat() attaches the shared memory
    shared_mem = shmat(shmID, (void*)0, 0);
    if(shared_mem == (void*)-1){
        printf("shmat failed\n");
        exit(EXIT_FAILURE);
    }

    printf("memory attached at %p\n", shared_mem);

    //shared memory segment casted
    shared_stuff = (struct data*)shared_mem;
    
    while(running)
    {
        //the program will get into the while in the second iteration
        while(shared_stuff->n == 1){
            sleep(1);
            printf("waiting for client...\n");
        }

        printf("enter some text: ");
        fgets(buffer, BUFSIZ, stdin);

        strncpy(shared_stuff->str, buffer, SZ);
        shared_stuff->n = 1;

        if(strncmp(buffer, "end", 3) == 0)
            running = 0;
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
