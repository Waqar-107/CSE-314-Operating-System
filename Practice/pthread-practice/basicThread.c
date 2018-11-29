/*** from dust i have come, dust i will be***/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void *alice(void *arg)
{
    int i;
    for(i = 0; i < 5; i++)
        printf("%s\n", (char*)arg);
}

void *bob(void *arg)
{
    int i;
    for(i = 0; i < 5; i++)
        printf("%s\n", (char*)arg);
}

void *argNai(void *arg)
{
    printf("i can be arg less you know ;)\n");
}

int main()
{
    pthread_t th1;
    pthread_t th2;
    pthread_t th3;

    char *msg1 = "thread uno";
    char *msg2 = "thread dos";

    //the thread identifier
    //null by default
    //service routine - the piece of code required to perform
    //a single arg can be passed to the service routine
    pthread_create(&th1, NULL, alice, (void*)msg1);
    pthread_create(&th2, NULL, bob, (void*)msg2);

    //the service routine should be passed null if there is no need\
    of passing anything
    pthread_create(&th3, NULL, argNai, NULL);
    while(1);

    return 0;
}