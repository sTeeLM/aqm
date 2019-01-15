#ifndef __AQM_DEBUG_H__
#define __AQM_DEBUG_H__

#ifdef __AQM_DEBUG__
void debug_printf(const char * fmt, ...);
#define ADBG(exp) debug_printf exp
#else
#define ADBG(exp)
#endif

#endif