/*** from dust i have come, dust i will be ***/

#include<stdio.h>
#include<unistd.h>

int main()
{
    pid_t a = 7, b = 7;

    a = fork(); printf("a done\n");
    b = fork(); printf("b done\n");

    printf("%d %d\n",a,b);

    return 0;
}  