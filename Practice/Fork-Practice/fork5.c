/*** from dust i have come, dust i will be ***/

#include<stdio.h>
#include<unistd.h>

#define pfs(str) printf("%s",str)
#define pf(n) printf("%d\n",n)

int main()
{
    pid_t p1 = fork();
    pfs("pid1 : "), pf(p1);

    pid_t p2 = fork();
    pfs("pid2 : "), pf(p2);

    pid_t p3 = fork();
    pfs("pid3 : "), pf(p3);

    pfs("threading is a mess.\n");

    return 0;
}  