/*** from dust i have come dust i will be ***/

#include<iostream>
#include<pthread.h>
#include<queue>
#include<semaphore.h>
#include<stdio.h>
#include<string>
#include<unistd.h>

#define chocolateCake 1
#define vanillaCake 2

using namespace std;

//chefX and chefY makes cake and push them in cakeQ, chefZ pops it
//chefZ pushes cakes in vanillaQ and chocolate, waiter 1 & 2 pops from them
queue<int> vanillaQ, chocolateQ;
queue<int> cakeQ;

sem_t cakeFull, cakeEmpty;
sem_t vanillaFull, chocolateFull, vanillaEmpty, chocolateEmpty;

pthread_mutex_t lock, consoleLock;

void init_semaphore()
{
    sem_init(&cakeFull, 0, 0);
    sem_init(&cakeEmpty, 0, 5);

    sem_init(&vanillaFull, 0, 0);
    sem_init(&vanillaEmpty, 0, 5);

    sem_init(&chocolateFull, 0, 0);
    sem_init(&chocolateEmpty, 0, 5);

    pthread_mutex_init(&lock, 0);
    pthread_mutex_init(&consoleLock, 0);
}

void pfs(string str)
{
    pthread_mutex_lock(&consoleLock);
    cout << str;
    pthread_mutex_unlock(&consoleLock);
}

void *chef_x(void *arg)
{
    while(1)
    {
        usleep(600);
        
        //queue locked
        pfs("chef x is in a tea-break\n");
        pthread_mutex_lock(&lock);    

        //emptiness decreases by one
        pfs("chef x is in a tea-break\n");
        sem_wait(&cakeEmpty);   

        pfs("chef x in critical region\n");
        
        cakeQ.push(chocolateCake);
        
        pthread_mutex_lock(&consoleLock);
        printf("chef x produced a chocolate-cake and leaving critical region. queue size: %d\n", (int)cakeQ.size());
        pthread_mutex_unlock(&consoleLock);

        //amount of cake increases by one
        sem_post(&cakeFull);

        //unlock queue 
        pthread_mutex_unlock(&lock);
    }
}

void *chef_y(void *arg)
{
    while(1)
    {
        usleep(700);
        
        //queue locked
        pfs("chef y is in a tea-break\n");
        pthread_mutex_lock(&lock);    

        //emptiness decreases by one
        pfs("chef y is in a tea-break\n");
        sem_wait(&cakeEmpty);   

        pfs("chef y in critical region\n");
        
        cakeQ.push(chocolateCake);
        
        pthread_mutex_lock(&consoleLock);
        printf("chef y produced a vanilla-cake and leaving critical region. queue size: %d\n", (int)cakeQ.size());
        pthread_mutex_unlock(&consoleLock);

        //amount of cake increases by one
        sem_post(&cakeFull);

        //unlock queue 
        pthread_mutex_unlock(&lock);
    }
}

void *chef_z(void *arg)
{

}

void *waiter_1(void *arg)
{

}

void *waiter_2(void *arg)
{

}

int main()
{
    init_semaphore();

    pthread_t chefX, chefY, chefZ;
    pthread_t waiter1, waiter2;

    pthread_create(&chefX, NULL, chef_x, NULL);
    pthread_create(&chefX, NULL, chef_y, NULL);
    pthread_create(&chefX, NULL, chef_z, NULL);
    pthread_create(&chefX, NULL, waiter_1, NULL);
    pthread_create(&chefX, NULL, waiter_2, NULL);

    while(true);

    exit(EXIT_SUCCESS);
}