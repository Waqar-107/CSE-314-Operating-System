/*** from dust i have come, dust i will be ***/

#include<bits/stdc++.h>
#include<sys/shm.h>
#include<unistd.h>

#include "sharedMem.h"

#define dbg printf("in\n")

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
    
    shared_stuff->idx = 0;
    shared_stuff->flag = 1;
    strcpy(shared_stuff->msg,"");
    
    while(running)
    {
        //inserter
        if(shared_stuff->flag == 1)
        {
            cout << "msg received: " << shared_stuff->msg << endl;
            if(strncmp(shared_stuff->msg, "terminate", 9) == 0)
            {
                for(i = 0;i<shared_stuff->idx; i++)
                        printf("%d ", shared_stuff->arr[i]);
                    
                printf("\n");
                running = 0;
                shared_stuff->flag = 0;
            }

            else
            {
                printf("enter n: ");
                scanf("%d", &n);

                printf("enter numbers:\n");
                while(n--)
                {
                    scanf("%d", &m);
                    shared_stuff->arr[shared_stuff->idx++] = m;
                }

                for(i = 0;i<shared_stuff->idx; i++)
                        printf("%d ", shared_stuff->arr[i]);
                    
                printf("\n");
                strcpy(shared_stuff->msg, "sort");
                shared_stuff->flag = 2;
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