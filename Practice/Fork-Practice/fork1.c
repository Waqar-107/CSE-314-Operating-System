/*** from dust i have come, dust i will be ***/

#include<stdio.h>
#include<unistd.h>

int main()
{
    int pid;
    printf("hello os!!!\n");

    pid = fork();

    if(pid == -1)
        printf("error in process creation\n");
    
    else if(pid == 0)
        printf("child\n");

    else if(pid == 0)
        printf("parent\n");

    return 0;
}
