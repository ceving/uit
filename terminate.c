#include <syslog.h>

#include "uit.h"

void terminate ()
{
  closelog ();                          // Finish logging

  syslog (LOG_INFO,                     // Notify termination
          "%s terminated",
          program_name);
}
