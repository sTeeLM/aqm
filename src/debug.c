#include <stdio.h>
#include <stdarg.h>
#include "debug.h"

void debug_printf(const char * fmt, ...)
{
  va_list arg_ptr;
  
  va_start (arg_ptr, fmt); /* format string */
  vprintf (fmt, arg_ptr);
  va_end (arg_ptr);
}
