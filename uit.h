#ifndef UIT_H
#define UIT_H

#define MESSAGE_SIZE 1024

extern char program_name[];
extern char in_daemon_mode;

void daemonize ();
void terminate ();
void tcpserver ();
char *message (char* format, ...);

#define FAIL(FORMAT, ARGS...) do {                              \
    int e = errno;                                              \
    char *m = message (FORMAT ": %s", ##ARGS, strerror(e));     \
    if (in_daemon_mode)                                         \
      syslog (LOG_ERR, "%s", m);                                \
    else                                                        \
      fprintf (stderr, "%s\n", m);                              \
    terminate ();                                               \
    exit (1);                                                   \
  } while (0)

#endif
