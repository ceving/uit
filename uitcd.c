#include "uit.h"

char program_name[] = "uitcd";

int main (int argc, char *argv[])
{
  daemonize ();
  tcpclient ();
  terminate ();
  return 0;
}
