/*** from dust i have come, dust i will be ***/

#include<bits/stdc++.h>
#include<sys/shm.h>
#include<unistd.h>

#include "sharedMem.h"

using namespace std;

int main()
{
    int i, j, k;
    int n, m;

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
        //sorting
        if(shared_stuff->flag == 2)
        {
            cout << "msg received: " << shared_stuff->msg << endl;
            
            k = 1;
            for(i = 0; i < shared_stuff->idx - 1; i++){
                if(shared_stuff->arr[i]>shared_stuff->arr[i+1]){
                    k = 0;
                    break;
                }
            }

            //sorted
            if(k){
                strcpy(shared_stuff->msg, "terminate");
                shared_stuff->flag = 1;
            }

            else{
                sort(shared_stuff->arr, shared_stuff->arr+shared_stuff->idx);
                strcpy(shared_stuff->msg, "sorted");
                shared_stuff->flag = 1;
            }
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