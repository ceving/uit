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

void relay (int   c,        // Client TCP file descriptor
            int   s,        // Server UCP file descriptor
            char *r,        // Address string of remote host
            int   p)        // Port of remote host
{
  struct sockaddr_in a;     // Remote address

  memset(&a, 0, sizeof a);
  a.sin_family      = AF_INET;
  a.sin_addr.s_addr = inet_addr(r);
  a.sin_port        = htons(p);

  for (;;)
    {
      int n = recv (
    }
}
