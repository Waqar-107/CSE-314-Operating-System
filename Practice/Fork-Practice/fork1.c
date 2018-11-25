/*** from dust i have come, dust i will be ***/

#include<stdio.h>
#include<unistd.h>

int main()
{
    pid_t pid;
    printf("hello os!!!\n");

    pid = fork();

    printf("pid : %d\n", pid);

    if(pid == -1)
        printf("error in process creation\n");
    
    else if(pid == 0)
        printf("child\n");

    else
        printf("parent\n");

    return 0;
}
