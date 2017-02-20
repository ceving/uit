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

int tcpsocket (int port)
{
  int s;                 // socket file descriptor
  int e;                 // error number
  struct sockaddr_in a;  // socket address

  if ((s = socket (AF_INET, SOCK_STREAM, 0))             // Create socket
      < 0)
    FAIL ("Can not create socket");

  int opt_val = 1;
  setsockopt (s,                                         // Socket options
              SOL_SOCKET,
              SO_REUSEADDR,
              &opt_val, sizeof opt_val);

  a.sin_family      = AF_INET;                           // Socket type
  a.sin_port        = htons (port);
  a.sin_addr.s_addr = htonl (INADDR_ANY);

  if ((e = bind (s, (struct sockaddr *) &a, sizeof(a)))  // Bind
      < 0)
    FAIL ("Can not bind socket");

  if ((e = listen (s, 128))                              // Start listening
      < 0)
    FAIL ("Can not listen on socket");

  INFO ("Server is listening on %d\n", port);

  return s;
}
