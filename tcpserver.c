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

void tcpserver (int port)
{
  int s;                     // Server file descriptor
  int c;                     // Client file descriptor
  struct sockaddr_in a;      // Client address
  pid_t p;                   // PID for new connection

  s = tcpsocket (port);

  for (;;)
    {
      socklen_t l = sizeof a;    // length of the client address

      if ((c = accept (s, (struct sockaddr *) &a, &l))  // Accept new connection
          < 0)
        FAIL ("Can not accept new new connection");

      if ((p = fork())                                  // Fork for new connection
          < 0)
        FAIL ("Can not fork for new connection");

      if (p == 0)                                       // Connection handling
        {
          INFO ("Handling new connection");
          close (s);
          relay ();
          INFO ("Finishing connection");
        }
      else                                              // Server handling
        {
          close (c);
        }
    }
}
