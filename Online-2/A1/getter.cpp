/*** from dust i have come, dust i will be ***/

#include<bits/stdc++.h>
#include<sys/shm.h>
#include<unistd.h>

#include "sharedMem.h"

using namespace std;

int main()
{
    int running = 1, shmID;
    void *shared_memory = (void*)0;

    struct data *shared_stuff;
    shmID = shmget((key_t)1234, sizeof(struct data*), 0666 | IPC_CREAT);

    if(shmID == -1){
        printf("shmget failed\n");
        exit(EXIT_FAILURE);
    }

    shared_memory = shmat(shmID, (void*)0, 0);
    if(shared_memory == (void*)-1){
        printf("shmat failed\n");
        exit(EXIT_FAILURE);
    }

    printf("memory attached at %p\n", shared_memory);
    shared_stuff = (struct data*)shared_memory;

    while(running)
    {
        //getter
        if(shared_stuff->flag == 0)
            running = 0;
        
        //not sorting running
        else if(shared_stuff->flag != 2)
        {
            if(shared_stuff->idx > 0)
                printf("%d\n", shared_stuff->arr[0]);
        }
    }

    if(shmdt(shared_memory) == -1){
        printf("shmdt failed\n");
        exit(EXIT_FAILURE);
    }

    if(shmctl(shmID, IPC_RMID, 0) == -1){
        printf("shmctl(IPC_RMID) failed\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}