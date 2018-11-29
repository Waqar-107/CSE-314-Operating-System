/*** from dust i have come dust i will be ***/

#include<iostream>
#include<pthread.h>
#include<queue>
#include<semaphore.h>
#include<stdio.h>
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

pthread_mutex_t lock;

void init_semaphore()
{
    sem_init(&cakeFull, 0, 0);
    sem_init(&cakeEmpty, 0, 5);

    sem_init(&vanillaFull, 0, 0);
    sem_init(&vanillaEmpty, 0, 5);

    sem_init(&chocolateFull, 0, 0);
    sem_init(&chocolateEmpty, 0, 5);

    pthread_mutex_init(&lock, 0);
}

void *chef_x(void *arg)
{
    while(1)
    {
        sleep(1);
        
        //queue locked
        printf("chef x is in a cofee-break\n");
        pthread_mutex_lock(&lock);    

        //emptiness decreases by one
        printf("chef x is in a cofee-break\n");
        sem_wait(&cakeEmpty);   

        printf("chef x in critical region\n");
        
        cakeQ.push(chocolateCake);
        printf("chef x produced a vanilla-cake and leaving critical region\nqueue size: %d", cake.size());

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
        sleep(2);
        
        //queue locked
        printf("chef y is in a cofee-break\n");
        pthread_mutex_lock(&lock);    

        //emptiness decreases by one
        printf("chef y is in a cofee-break\n");
        sem_wait(&cakeEmpty);   

        printf("chef y in critical region\n");
        
        cakeQ.push(chocolateCake);
        printf("chef y produced a vanilla-cake and leaving critical region\nqueue size: %d", cake.size());

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