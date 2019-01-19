#include "types.h"
#include "defs.h"
#include "param.h"
#include "spinlock.h"
#include "sock.h"
#include "memlayout.h"
#include "mmu.h"
#include "x86.h"
#include "proc.h"

struct {
  struct spinlock lock;
  struct socket sock[NSOCK];
  int port[NPORT];
} stable;

void
sinit(void)
{
  // initialize the lock
  initlock(&stable.lock, "stable");

  int i;
  for(i = 0; i < NSOCK; i++)
    stable.sock[i].currentState = CLOSE, stable.sock[i].dataAvailable = 0;

  //unused
  for(i = 0; i < NPORT)port[i] = 0;

  //intialize LPORT that will be assigned as local-ports
  LPORT = 0;
}

//returns the local port
int getLocalPort(){

  int i;
  for(i = 0; i < NPORT; i++)
  {
    if(stable.port[i] == 0)
      return i;
  }
  
  return -1;
}

int
listen(int lport) {

  int i, ret = -1;

  //lock the stable
  acquire(&stable.lock);

  //check if the desired port is already listening
  for(i = 0; i < NSOCK; i++)
  {
    if(stable.sock[i].localPort == lport && stable.sock[i].currentState == LISTEN)
      goto LISTENING_STATE;
  }

  if(lport >= NPORT)goto LISTENING_STATE;

  //if we have made it to this line that means our desired port is unused
  for(i = 0; i < NSOCK; i++)
  {
    if(stable.sock[i].currentState == CLOSE){
      stable.sock[i].currentState = LISTEN;
      stable.sock[i].localPort = lport;
      port[lport] = 1;
      
      ret = 0; 
      stable.sock[i].ownerPID = myproc()->pid;
      
      break;
    }
  }

  LISTENING_STATE:

  //unlock the stable
  release(&stable.lock);

  return ret;
}


int
connect(int rport, const char* host) {

  int i, ret = -1, lcp;

  //lock the stable
  acquire(&stable.lock);

  //check if the port is listening
  for(i = 0;i < NSOCK; i++) {
    if(stable.sock[i].currentState == LISTEN && stable.sock[i].localPort == rport) {
        ret = i;
        break;
    }
  }

  if(ret == -1) goto RET;

  //allot a socket for the connection which is operating in any closed port
  for(i = 0; i < NSOCK; i++) {
    if(stable.sock[i].currentState == CLOSE)
    {
      //get a free port for client
      lcp = getLocalPort(); cprintf("local port assigned for client: %d\n", lcp);
      if(lcp == -1)goto RET;

      //imagine that sock[i] is in client machine
      stable.sock[i].ownerPID = myproc()->pid;
      stable.sock[i].currentState = CONNECT;
      stable.sock[i].remotePort = rport;
      stable.sock[i].localPort = lcp;

      //this is in server machine
      stable.sock[ret].remotePort = lcp;

      ret = lcp;
      break;
    }
  }

  RET:

  //unlock the stable
  release(&stable.lock);

  return ret;
}

int
send(int lport, const char* data, int n) {
  
  int i;
  
  //lock the stable
  acquire(&stable.lock);

  for(i = 0; i < )

  //unlock the stable
  release(&stable.lock);

  return 0;
}


int
recv(int lport, char* data, int n) {
  //lock the stable
  acquire(&stable.lock);

  //unlock the stable
  release(&stable.lock);

  return 0;
}

int
disconnect(int lport) {
  //lock the stable
  acquire(&stable.lock);

  //unlock the stable
  release(&stable.lock);

  return 0;
}

/*
a socket with port is listening
if a client comes and wants to connect with it -> they will be connected and the connection state will be CONNECT
, none other will be able to connect with it 
*/