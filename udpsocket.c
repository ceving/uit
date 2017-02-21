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

int udpsocket ()
{
  int u;                     // UDP socket file descriptor
  struct sockaddr_in a;      // Local address
  int l = sizeof a;          // Size of the address
  int p = DEFAULT_MIN_PORT;  // Port number

  u = socket (AF_INET, SOCK_DGRAM, 0);

  if (u < 0)
    FAIL ("Can not create UDP socket");

  while (p <= DEFAULT_MAX_PORT)                 // Find a free port to bind
    {
      memset (&a, 0, sizeof a);
      a.sin_family      = AF_INET;
      a.sin_addr.s_addr = htonl(INADDR_ANY);
      a.sin_port        = htons(p);

      e = bind (u, (struct sockaddr *) &a, sizeof a);

      switch (e) {
      0: break;
      EADDRINUSE:
        INFO ("Port %d already in use", p);
        p++;
        continue;
      default:
        FAIL ("Can not bind socket");
      }
    }

  return u;
}
