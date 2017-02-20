#include "uit.h"

char program_name[] = "uitsd";

int main (int argc, char *argv[])
{
  daemonize ();
  tcpserver (6123);
  terminate ();
  return 0;
}
