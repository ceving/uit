#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <syslog.h>

#include "uit.h"

void udpserver (int port)
{
  int u;
  //struct sockaddr_in ucs;  // UDP client socket

  if ((u = socket (AF_INET, SOCK_DGRAM, 0))
      < 0)
    FAIL ("Can not create UDP socket");


}
