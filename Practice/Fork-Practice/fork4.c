/*** from dust i have come, dust i will be ***/

#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<stdlib.h>

#define pfs(str) printf("%s",str)
#define pf(n) printf("%d\n",n)

int main()
{
    pid_t pid;
    char *msg;

    int n, exit_code;
    pfs("fork program starting\n");

    pid = fork();
    pfs("pid : ");pf(pid);

    switch(pid)
    {
        case -1:
            perror("fork failed\n");
            break;
        case 0:
            msg = "this is the child\n";
            n = 5;
            exit_code = 37;
            break;
        default:
            msg = "this is the parent\n";
            n = 3;
            exit_code = 0;
            break;
    }

    for( ; n > 0; n--){
        pfs(msg);
        sleep(1);
    }

    if(pid != 0){
        int stat_val;
        pid_t child_pid;

        //wait() waits for all the child processes to terminate, returns the childs pid, in the\
        pointer it returns a flag indicating completition status of child
        child_pid = wait(&stat_val);

        pfs("child has finished. pid: ");pf(child_pid);

        if(WIFEXITED(stat_val))
            pfs("child exits with code: "), pf(WEXITSTATUS(stat_val));
        else
            pfs("child terminated abnormally\n");
    }

    exit(exit_code);
}