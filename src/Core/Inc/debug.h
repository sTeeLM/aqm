#ifndef __AQM_DEBUG_H__
#define __AQM_DEBUG_H__

#include <stdio.h>
#include <stdint.h>

//#include <EventRecorder.h>

typedef enum {
  AQMLOG_ERROR,
  AQMLOG_INFO,
  AQMLOG_DBG
} aqm_log_type_t;

int8_t debug_init(void);
void debug_printf(uint8_t newline, aqm_log_type_t level, const char * fmt, ...);

#define AQM_DEBUG_LEVEL 4

#if (AQM_DEBUG_LEVEL >= 1)
#define AQMERR(...)     debug_printf(0, AQMLOG_ERROR, __VA_ARGS__)
#define AQMERR_R(...)   debug_printf(1, AQMLOG_ERROR, __VA_ARGS__)
#define AQMERR_RH       debug_printf(1, AQMLOG_ERROR, "%s","[ERR ]")
#define AQMERR_RT       debug_printf(1, AQMLOG_ERROR, "%s", "\r\n")
#else
#define AQMERR(...)     do{}while(0)
#define AQMERR_R(...)   do{}while(0)
#define AQMERR_RH
#define AQMERR_RT
#endif

#if (AQM_DEBUG_LEVEL >= 2)
#define AQMINFO(...)    debug_printf(0, AQMLOG_INFO, __VA_ARGS__) 
#define AQMINFO_R(...)  debug_printf(1, AQMLOG_INFO, __VA_ARGS__) 
#define AQMINFO_RH      debug_printf(1, AQMLOG_INFO, "%s", "[INFO]")
#define AQMINFO_RT      debug_printf(1, AQMLOG_INFO, "%s", "\r\n")
#else
#define AQMINFO(...)  do{}while(0)
#define AQMINFO_R(...)  do{}while(0)
#define AQMINFO_RH
#define AQMINFO_RT
#endif

#if (AQM_DEBUG_LEVEL >= 3)
#define AQMDBG(...)     debug_printf(0, AQMLOG_DBG, __VA_ARGS__)
#define AQMDBG_R(...)   debug_printf(1, AQMLOG_DBG, __VA_ARGS__) 
#define AQMDBG_RH       debug_printf(1, AQMLOG_DBG, "[DBG ]")
#define AQMDBG_RT       debug_printf(1, AQMLOG_DBG, "\r\n")
#else
#define AQMDBG(...)   do{}while(0)
#define AQMDBG_R(...) do{}while(0)
#define AQMDBG_RH
#define AQMDBG_RT
#endif

#endif

