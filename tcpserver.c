#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <syslog.h>
#include <sys/select.h>

#include "uit.h"

void tcpserver (int port)
{
  int t;                     // TCP file descriptor
  int c;                     // Client file descriptor
  struct sockaddr_in a;      // Client address
  pid_t p;                   // PID for new connection

  t = tcpsocket (port);

  for (;;)
    {
      socklen_t l = sizeof a;    // length of the client address

      c = accept (t, (struct sockaddr *) &a, &l);       // Accept new connection

      if (c < 0)
        FAIL ("Can not accept new new connection");

      p = fork();                                       // Fork for new connection

      if (p < 0)
        FAIL ("Can not fork for new connection");
      else
        if (p == 0)                                     // Connection handling
          {
            INFO ("Handling new connection");
            close (t);
            u = udpsocket ();
            relay (c, u);
            INFO ("Finishing connection");
          }
        else                                            // Server handling
          {
            close (c);
          }
    }
}
