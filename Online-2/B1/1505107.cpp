/*** from dust i have come, dust i will be ***/

#include<bits/stdc++.h>
#include<unistd.h>
#include<sys/sem.h>
#include<unistd.h>
#include "sem.h"
#include "data.h"

#define pfs(s) printf("%s", s);
#define pf(n) printf("%d", n);
#define nl printf("\n");
#define dbg printf("in\n")

#define N 5

using namespace std;

int main()
{
    int running = 1;
    sem_id = semget((key_t)1234, 1, 0666 | IPC_CREAT);

    //semaphore set by the parent process 
    if(argc > 1)
    {
        if(!set_semvalue())
        {
            pfs("failed to initialize semaphore\n");
            exit(EXIT_FAILURE);
        }

        sleep(2);
    }

    //initiate the catalog
    struct catalog shared_stuff;
    shared_stuffa = writer("A", N, 0);
    shared_stuff->b = writer("B", N, 0);
    shared_stuff->c = writer("C", N, 0);

    shared_stuff->id = 0;
    shared_stuff->text = "";



}