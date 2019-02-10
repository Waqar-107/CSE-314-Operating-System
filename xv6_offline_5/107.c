#include "types.h"
#include "user.h"

void child() {
 sleep(100);
 printf(1,"this is a child process\n");
}

void parent() {
  printf(1,"this is a parent process\n");
}


int main(int argc, char *argv[])
{
  /*if (0 == fork()) {
    child();
    exit();
  } else {
    parent();
    // This is the parent process. So, it needs to wait before client terminates
    wait();
    exit();
  }*/

  int i;
  for(i=0;i<20;i++){
    sbrk(2);
  }

	//printf(1,"hello world\n");
	//exit();
}
