#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>

#include "uit.h"

char in_daemon_mode = '\0';

void daemonize ()
{
  pid_t pid;

  pid = fork();                         // First fork
  if (pid < 0) {
    perror ("First fork");
    exit (EXIT_FAILURE);
  }

  if (pid > 0)                          // Exit parent
    exit (EXIT_SUCCESS);

  if (setsid() < 0) {                   // Become session leader
    perror (NULL);
    exit (EXIT_FAILURE);
  }

  signal(SIGCHLD, SIG_IGN);             // Ignore signals
  signal(SIGHUP, SIG_IGN);

  pid = fork();                         // Second fork
  if (pid < 0) {
    perror ("Second fork");
    exit (EXIT_FAILURE);
  }

  if (pid > 0)                          // Exit parent
    exit (EXIT_SUCCESS);

  umask (0);                            // Clear umask

  if (chdir ("/") < 0) {                // Change to root dir
    perror ("Change root dir");
    exit (EXIT_FAILURE);
  }

  if (close (STDIN_FILENO) < 0) {       // Close stdin
    perror ("Closing stdin");
    exit (EXIT_FAILURE);
  }

  if (close (STDOUT_FILENO) < 0) {      // Close stdout
    perror ("Closing stdout");
    exit (EXIT_FAILURE);
  }

  if (close (STDERR_FILENO) < 0) {      // Close stderr
    perror ("Closing stdout");
    exit (EXIT_FAILURE);
  }

  openlog ("udp-in-tcp",                // Initialize logging
           LOG_PID,
           LOG_DAEMON);

  syslog (LOG_INFO,                     // Notify startup
          "%s started", program_name);

  in_daemon_mode++;
}
