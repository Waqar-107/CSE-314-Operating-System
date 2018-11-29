/**** from dust i have come, dust i will be ***/

#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<queue>
#include<unistd.h>

using namespace std;

sem_t empty, full;
queue<int> q;

void init_semaphore()
{
    sem_init(&empty, 0, 5);
    sem_init(&full, 0, 0);
}

void *producer(void *arg)
{
    printf("in producer : %s\n", (char*)arg);
    for(int i = 0; i <= 10; i++)
    {
        sem_wait(&empty);

        sleep(1);

        q.push(i);
        printf("producer produced item %d\n", i);

        sem_post(&full);
    }
}

void *consumer(void *arg)
{
    printf("in consumer : %s\n", (char*)arg);

    for(int i = 0; i <= 10 ; i++)
    {
        sem_wait(&full);
        sleep(1);

        int item = q.front();
        q.pop();

        printf("consumer consumed item %d\n", item);
        sem_post(&empty);
    }
}

int main()
{
    pthread_t t1, t2;
    init_semaphore();

    char *msg1 = "i am prod";
    char *msg2 = "i am consumer";

    pthread_create(&t1, NULL, producer, (void*)msg1);
    pthread_create(&t2, NULL, consumer, (void*)msg2);

    while(1);

    return 0;
}
