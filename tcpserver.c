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
  int server_fd, client_fd, err;
  struct sockaddr_in server, client;
  char buf[MESSAGE_SIZE];

  server_fd = socket (AF_INET, SOCK_STREAM, 0);
  if (server_fd < 0) FAIL ("Can not create socket");

  server.sin_family = AF_INET;
  server.sin_port = htons (port);
  server.sin_addr.s_addr = htonl(INADDR_ANY);

  int opt_val = 1;
  setsockopt (server_fd, SOL_SOCKET, SO_REUSEADDR, &opt_val, sizeof opt_val);

  err = bind (server_fd, (struct sockaddr *) &server, sizeof(server));
  if (err < 0) FAIL ("Could not bind socket");

  err = listen(server_fd, 128);
  if (err < 0) FAIL ("Could not listen on socket");

  printf("Server is listening on %d\n", port);

  while (1) {
    socklen_t client_len = sizeof(client);
    client_fd = accept(server_fd, (struct sockaddr *) &client, &client_len);

    if (client_fd < 0) FAIL ("Could not establish new connection");

    while (1) {
      int read = recv(client_fd, buf, MESSAGE_SIZE, 0);

      if (!read) break; // done reading
      if (read < 0) FAIL ("Client read failed");

      err = send(client_fd, buf, read, 0);
      if (err < 0) FAIL ("Client write failed");
    }
  }

}
