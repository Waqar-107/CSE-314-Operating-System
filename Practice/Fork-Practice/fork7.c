/*** from dust i have come, dust i will be ***/

#include<stdio.h>
#include<unistd.h>

#define pfs(str) printf("%s",str)
#define pf(n) printf("%d\n",n)

int main()
{
    char *argv[3] = {"Command-line", "", NULL};

    int pid = fork();
    if(!pid)
        execvp("find", argv);

    /* Put the parent to sleep for 3 seconds--let the child finished executing */
	sleep(2);

	printf( "Finished executing the parent process\n-the child won't get here--you will only see this once\n" );

    return 0;
}  