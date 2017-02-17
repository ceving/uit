#include <stdarg.h>
#include <stdio.h>

#include "uit.h"

static char buffer[MESSAGE_SIZE];

char* message (char *format, ...)
{
  va_list ap;
  va_start (ap, format);
  vsnprintf (buffer, MESSAGE_SIZE, format, ap);
  va_end (ap);
  return buffer;
}
