/*** from dust i have come, dust i will be ***/

#include<stdio.h>
#include<unistd.h>

#define pfs(str) printf("%s",str)
#define pf(n) printf("%d\n",n)

int main()
{
    int n;
    pid_t pid;

    pid = fork();
    pfs("pid : "); pf(pid);

    if(pid) {
        pfs("parent start\n");
        n = 1;
        pfs("parent done\n");
    }

    else {
        pfs("child started\n");
        n = 2;
        pfs("child done\n");
    }

    pf(n);

    return 0;
}