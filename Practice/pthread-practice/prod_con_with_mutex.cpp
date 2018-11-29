/*** from dust i have come dust i will be ***/

#include<iostream>
#include<pthread.h>
#include<queue>
#include<semaphore.h>
#include<stdio.h>
#include<unistd.h>

using namespace std;

sem_t empty, full;
queue<int> q;
pthread_mutex_t lock;

void init_semaphore()
{
    sem_init(&empty, 0, 5);
    sem_init(&full, 0, 0);

    pthread_mutex_init(&lock, 0);
}

void *producer(void *arg)
{
    printf("%s\n", (char*)arg);
    for(int i = 0; i <= 10; i++)
    {
        sem_wait(&empty);

        pthread_mutex_lock(&lock);
        sleep(1);

        q.push(i);
        printf("producer produced item %d\n", i);

        pthread_mutex_unlock(&lock);

        sem_post(&full);
    }
}

void *consumer(void *arg)
{
    printf("%s\n", (char*)arg);
    for(int i = 0; i <= 10; i++)
    {
        sem_wait(&full);

        pthread_mutex_lock(&lock);
        sleep(1);

        int item = q.front();
        q.pop();

        printf("consumer consumed item: %d\n", item);

        pthread_mutex_unlock(&lock);

        sem_post(&empty);
    }
}

int main()
{
    pthread_t t1, t2;

    init_semaphore();

    char *msg1 = "i am producer";
    char *msg2 = "i am consumer";

    pthread_create(&t1, NULL, producer, (void*)msg1);
    pthread_create(&t2, NULL, consumer, (void*)msg2);

    while(1);

    return 0;
}