/*** from dust i have come dust i will be ***/

#include<iostream>
#include<pthread.h>
#include<queue>
#include<semaphore.h>
#include<stdio.h>
#include<unistd.h>

using namespace std;

void *chef_x(void *arg)
{

}

void *chef_y(void *arg)
{

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