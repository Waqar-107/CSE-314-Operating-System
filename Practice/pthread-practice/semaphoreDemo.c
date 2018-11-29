/*** from dust i have come, dust i will be ***/

#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

sem_t binary_semaphore;
char msg[100];

void *foo(void *arg)
{
    int x;
    char msg2[10];

    while(1)
    {
        printf("thread2 : waiting...\n");
        sem_wait(&binary_semaphore);

        printf("i am new thread waiting inside critical region\nEnter something");
        scanf("%s", msg);

        printf("you entered: %s for th2\n", msg);
        printf("th2 leaving its critical zone\n");
        
        sem_post(&binary_semaphore);
    }
}

int main()
{
    pthread_t th;
    pthread_attr_t ta;

    int x;
    char msg2[10];

    //semaphore, 0 means semaphore is local to the calling process\
    the last param is initial value of the sem 
    sem_init(&binary_semaphore, 0, 1);

    pthread_attr_init(&ta);
    pthread_attr_setschedpolicy(&ta, SCHED_RR);

    pthread_create(&th, &ta, foo, NULL);

    while(1)
    {
        printf("main waiting...\n");
        sem_wait(&binary_semaphore);

        printf("main thread waiting inside critical zone\nEnter something:");
        scanf("%s", msg);

        printf("you entered: %s for main\n", msg);
        printf("main leaving its critical zone\n");

        sem_post(&binary_semaphore);
        sleep(2);
    }

    sleep(5);
}