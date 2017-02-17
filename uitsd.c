#include "uit.h"

char program_name[] = "uitsd";

int main (int argc, char *argv[])
{
  daemonize();
  tcpserver();
  terminate();
  return 0;
}
