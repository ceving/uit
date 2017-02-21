#ifndef UIT_H
#define UIT_H

#define MESSAGE_SIZE     (1024)
#define BUFFER_SIZE      (1472)

#define DEFAULT_MIN_PORT (12300)
#define DEFAULT_MAX_PORT (49151)

extern char program_name[];
extern char in_daemon_mode;

void  daemonize ();
void  terminate ();
void  tcpclient ();
void  tcpserver (int port);
int   tcpsocket (int port);
int   udpsocket ();
int   relay  ();
char *message   (char* format, ...);

#define MSG(LEVEL, TAG, FORMAT, ARGS...) do {                   \
    if (in_daemon_mode)                                         \
      syslog (LEVEL, FORMAT, ##ARGS);                           \
    else                                                        \
      fprintf (stderr, TAG ": " FORMAT "\n", ##ARGS);           \
  } while (0)

#define INFO(FORMAT, ARGS...) MSG(LOG_INFO,    "INFO", FORMAT, ##ARGS)
#define WARN(FORMAT, ARGS...) MSG(LOG_WARNING, "WARN", FORMAT, ##ARGS)

#define FAIL(FORMAT, ARGS...) do {                              \
    int e = errno;                                              \
    char *m = message (FORMAT ": %s", ##ARGS, strerror(e));     \
    MSG(LOG_ERR, "ERROR", "%s", m);                             \
    terminate ();                                               \
    exit (1);                                                   \
  } while (0)

#endif
