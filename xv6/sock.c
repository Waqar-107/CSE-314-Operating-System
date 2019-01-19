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
    stable.sock[i].currentState = CLOSE, stable.sock[i].dataAvailable = 0, stable.sock[i].localPort = -1;

  //unused
  for(i = 0; i < NPORT; i++) stable.port[i] = 0;
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

  //if we have made it to this line that means our desired port is unused
  for(i = 0; i < NSOCK; i++)
  {
    if(stable.sock[i].currentState == CLOSE){
      stable.sock[i].currentState = LISTEN;
      stable.sock[i].localPort = lport;
      stable.port[lport] = 1;
      cprintf("%d th index selected for listen, port: %d\n",i, lport);
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
  
  acquire(&stable.lock);

  int i, server_idx = -1, local_port = -1;
  for(i = 0;i < NSOCK; i++)
  {
    if(stable.sock[i].currentState == LISTEN && stable.sock[i].localPort == rport)
    {
      server_idx = i;
      break;
    }
  }

  if(server_idx){release(&stable.lock); return E_NOTFOUND;}

  local_port = getLocalPort();
  if(local_port == -1){release(&stable.lock); return E_NOTFOUND;}

  for(i = 0; i < NSOCK; i++)
  {
    if(stable.sock[i].currentState == CLOSE)
    {
      //client_idx = i;

      stable.sock[i].currentState = CONNECT;
      stable.sock[i].localPort = local_port;
      stable.sock[i].ownerPID = myproc()->pid;
      stable.sock[i].remotePort =  stable.sock[server_idx].localPort;

      stable.sock[server_idx].remotePort = local_port;
      stable.sock[server_idx].currentState = CONNECT;
    }
  }

  release(&stable.lock);

  return local_port;
}

int
send(int lport, const char* data, int n) {
  
  int i, client_idx = -1, server_idx = -1;

  //acquire lock
  acquire(&stable.lock);
  
  //find corresponding local port
  for(i = 0; i < NSOCK; i++)
  {
    if(stable.sock[i].localPort == lport && stable.sock[i].currentState == CONNECT){
      client_idx = i;
      break;
    }
  }

  if(client_idx == -1){cprintf("client not found in s\n");release(&stable.lock); return E_NOTFOUND;}

  //find who is to send
  for(i = 0; i < NSOCK; i++)
  {
    if(stable.sock[i].localPort == stable.sock[client_idx].remotePort && stable.sock[i].currentState == CONNECT){
      server_idx = i;
      break;
    }
  }

  //port not found
  if(server_idx == -1){cprintf("server not found in s\n");release(&stable.lock); return E_NOTFOUND;}

  if(myproc()->pid != stable.sock[client_idx].ownerPID){
    return E_ACCESS_DENIED;
  }

  if(stable.sock[server_idx].dataAvailable == 1){
    sleep(&stable.sock[client_idx], &stable.lock);
    strncpy(stable.sock[server_idx].buffer, data, n);
    stable.sock[server_idx].dataAvailable = 1;
  }

  else{
    //cprintf("%s sent to server\n",data);
    strncpy(stable.sock[server_idx].buffer, data, n);
    stable.sock[server_idx].dataAvailable = 1;
    wakeup(&stable.sock[server_idx]);
  }

  release(&stable.lock);

  return 0;
}


int
recv(int lport, char* data, int n) {
  
  //lock the stable
  acquire(&stable.lock);

  int i, client_idx = -1;

  //find corresponding local port
  for(i = 0; i < NSOCK; i++)
  {
    //cprintf("%d %d %d\n",i,stable.sock[i].localPort,stable.sock[i].currentState);
    if(stable.sock[i].localPort == lport && stable.sock[i].currentState == CONNECT){
      client_idx = i;
      break;
    }
  }

  if(client_idx == -1){release(&stable.lock); return E_NOTFOUND;}

  if(myproc()->pid != stable.sock[client_idx].ownerPID){
    return E_ACCESS_DENIED;
  }

  struct socket *temp = &stable.sock[client_idx];

  //wait for data
  if(stable.sock[client_idx].dataAvailable == 1){
    strncpy(data, stable.sock[client_idx].buffer, n);
    stable.sock[client_idx].dataAvailable = 0;
    wakeup(temp);
  }

  else{
    sleep(temp, &stable.lock);
    strncpy(data, stable.sock[client_idx].buffer, n);
    stable.sock[client_idx].dataAvailable = 0;
  }

  //unlock the stable
  release(&stable.lock);

  return 0;
}

int
disconnect(int lport) {
  
  int i = 0, ret = E_NOTFOUND, idx = -1;
  
  //lock the stable
  acquire(&stable.lock);

  for(i = 0; i < NSOCK; i++)
  {
    if(stable.sock[i].localPort == lport){
      stable.sock[i].dataAvailable = 0;
      stable.port[lport] = 0;
      stable.sock[i].currentState = CLOSE;
      ret = 0; idx = i;
    }
  }

  if(myproc()->pid != stable.sock[idx].ownerPID){
    return E_ACCESS_DENIED;
  }

  //unlock the stable
  release(&stable.lock);

  return ret;
}