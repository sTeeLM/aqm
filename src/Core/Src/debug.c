#include <stdio.h>
#include <stdarg.h>
#include "debug.h"
#include "usart.h"

int8_t debug_init(void)
{
  return 0;
}

static char buffer[1024];

void debug_printf(uint8_t raw, aqm_log_type_t level, const char * fmt, ...)
{
  va_list arg_ptr;
  uint32_t len = 0;
  if(!raw) {
    len = snprintf(buffer, sizeof(buffer) - 1, "%s ",
      level == AQMLOG_ERROR ? "[ERR ]" : 
      (level == AQMLOG_INFO? "[INFO]" : "[DBG ]"));
  }
  
  va_start (arg_ptr, fmt); /* format string */
  len += vsnprintf (buffer + len, sizeof(buffer) - len - 5, fmt, arg_ptr);
  va_end (arg_ptr);
  
  if(!raw)
    len += snprintf(buffer + len, sizeof(buffer) - len - 1, "%s", "\r\n");
  
  buffer[sizeof(buffer) - 1] = 0;

  BSP_USART1_Transmit((uint8_t *)buffer, len);
}

