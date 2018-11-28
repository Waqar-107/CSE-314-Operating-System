/*** from dust i have come, dust i will be ***/

#include<unistd.h>
#include<bits/stdc++.h>
#include<unistd.h>
#include<sys/shm.h>
#include "sharedMem.h"

#define pfs(s) printf("%s", s);
#define pf(n) printf("%d", n);
#define nl printf("\n");
#define dbg printf("in\n")

using namespace std;

int main()
{
    srand(time(NULL));

    int i,j,k;
    vector<int> odd, even;

    int running = 1, shmID;
    void *shared_mem = (void*)0;

    struct data *sharedStuff;
    shmID = shmget((key_t)1234, sizeof(struct data*), 0666 | IPC_CREAT);

    //-----------------------------------------------------------------------------------
    //shared mem allocation
    if(shmID == -1){
        pfs("shmget failed\n");
        exit(EXIT_FAILURE);
    }

    shared_mem = shmat(shmID, (void*)0, 0);
    if(shared_mem == (void*)-1){
        pfs("shmat failed");
        exit(EXIT_FAILURE);
    }

    printf("memory attached at %p\n", shared_mem);

    sharedStuff = (struct data*)shared_mem;
    sharedStuff->flag = 0;
    //-----------------------------------------------------------------------------------

    sharedStuff->n = 0;
    int myID = -1;

    if(sharedStuff->n == 0)
    {
        if(fork() == 0)
        {
            sharedStuff->n++;
            myID = sharedStuff->n;
            if(fork() == 0)
            {
                sharedStuff->n++;
                myID = sharedStuff->n;
                if(fork() == 0)
                {
                    sharedStuff->n++;
                    myID = sharedStuff->n;
                }
            }
        }
    }

    //pf(myID);nl;
    if(myID == 1)
    {
        int itr = 0;
        while(itr<10)
        {
            //generate 5 number
            if(sharedStuff->flag == 0)
            {
                sharedStuff->idx = 0;
                for(i=0;i<5;i++)
                {
                    int x = rand() % 100;
                    sharedStuff->arr[i] = x;
                    sharedStuff->idx++;
                }
                
                itr++;
                sharedStuff->flag = 1;
                sharedStuff->f2 = 0;
                sharedStuff->f3 = 0;

            }
        }

        sleep(2);
    }

    else if(myID == 2)
    {
        int itr = 0;
        while(itr<10)
        {
            //fill the odd
            if(sharedStuff->flag != 0)
            {
                if(sharedStuff->idx<5){pfs("ERROR in buffer\n"); exit(EXIT_FAILURE);}

                for(i=0;i<5;i++)
                {
                    if(sharedStuff->arr[i]%2 == 1)
                        odd.push_back(sharedStuff->arr[i]);
                }

                itr++;

                if(itr==10)
                {
                    for(i=0;i<odd.size();i++)
                        printf("%d ", odd[i]);
                    nl;
                }

                sleep(1);
                sharedStuff->f2=1;

                if(sharedStuff->f3)
                    sharedStuff->flag=0;
            }
        }
    }

    else if(myID == 3)
    {
        int itr = 0;
        while(itr<10)
        {
            //fill the even
            if(sharedStuff->flag != 0)
            {
                if(sharedStuff->idx<5){pfs("ERROR in buffer\n"); exit(EXIT_FAILURE);}

                for(i=0;i<5;i++)
                {
                    if(sharedStuff->arr[i]%2 == 0)
                        odd.push_back(sharedStuff->arr[i]);
                }

                itr++;
                if(itr==10)
                {
                    for(i=0;i<odd.size();i++)
                        printf("%d ", even[i]);
                    nl;
                }

                sleep(1);
                sharedStuff->f3=1;

                if(sharedStuff->f2)
                    sharedStuff->flag=0;
            }
        }
    }
    

    //-----------------------------------------------------------------------------------
    //memory detached
    if(myID == -1)
    {
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
    
    exit(EXIT_SUCCESS);
}