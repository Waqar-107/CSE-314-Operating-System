/*** from dust i have come, dust i will be ***/

#include<stdio.h>
#include<unistd.h>

#define pfs(str) printf("%s",str)
#define pf(n) printf("%d\n",n)

void foo()
{
    int n = 1;

    //the parent will be non-zero value by the fork
    //the child will get zero by the fork
    if(fork() == 0)
        pfs("child has n = "), pf(++n);

    else
        pfs("parent has n = "), pf(--n);
}

int main()
{
    foo();
    return 0;
}  