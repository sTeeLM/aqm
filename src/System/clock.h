#ifndef __AQM_CLOCK_H__
#define __AQM_CLOCK_H__

#include <stdint.h>
#include "task.h"

void clock_init(void);

uint8_t clock_get_year(void);
void clock_set_year(uint8_t year);
void clock_inc_year(void);

uint8_t clock_get_mon(void);
void clock_set_mon(uint8_t month);
void clock_inc_mon(void);

uint8_t clock_get_date(void);
void clock_set_date(uint8_t date);
void clock_inc_date(void);

uint8_t clock_get_day(void);

uint8_t clock_get_hour(void);
void clock_set_hour(uint8_t hour);
void clock_inc_hour(void);

uint8_t clock_get_min(void);
void clock_set_min(uint8_t min);
void clock_inc_min(void);

uint8_t clock_get_sec(void);
void clock_clr_sec(void);

uint32_t clock_get_now_sec(void);
uint32_t clock_diff_now_sec(uint32_t now);

void clock_enter_console(void);
void clock_leave_console(void);

void clock_time_proc(enum task_events);

void clock_show(void);

#endif
