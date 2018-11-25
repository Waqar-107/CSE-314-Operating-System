/*** from dust i have come, dust i will be ***/

#include<stdio.h>
#include<unistd.h>

#define pfs(str) printf("%s",str)
#define pf(n) printf("%d\n",n)

int main()
{
    pid_t pid;

    char *msg;
    int n;

    pid = fork();

    if(pid == -1){
        n = 1;
        msg = "error\n";
    }

    else if(pid == 0){
        n = 5;
        msg = "child\n";
    }

    else{
        n = 7;
        msg = "parent\n";
    }

    while(n--){
        pfs(msg);
        sleep(1);
    }

    return 0;
}