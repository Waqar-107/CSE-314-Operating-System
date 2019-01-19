#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "x86.h"
#include "proc.h"

int
sys_listen(void)
{
  int port = 0;

  if(argint(0,&port) < 0) return -1;

  return listen(port);
}

int
sys_connect(void)
{
  int port = 0;
  char *host = 0;

  if(argint(0, &port) < 0) return -1;
  if(argstr(1, &host) < 0) return -1;

  if(strncmp(host,"127.0.0.1",strlen(host))!=0 && strncmp(host,"localhost",strlen(host)) != 0)
  {
    return E_INVALID_ARG; // error in port or host
  }
  return connect(port, host);
}

int
sys_send(void)
{
  int port = 0;
  char* buf = 0;
  int n = 0;
  
  if(argint(0, &port)<0 || argint(2, &n) < 0 || argstr(1, &buf) < 0)
    return -1;

  return send(port, buf, n);
}

int
sys_recv(void)
{
  int port = 0;
  char* buf = 0;
  int n = 0;

  if(argint(0, &port) < 0 || argint(2, &n) < 0 || argstr(1, &buf) < 0)
    return -1;

  return recv(port, buf, n);
}

int
sys_disconnect(void)
{
  int port = 0;

  if(argint(0, &port) < 0) return -1;

  return disconnect(port);
}