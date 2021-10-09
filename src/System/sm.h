#ifndef __AQM_SM_H__
#define __AQM_SM_H__

#include <stdint.h>
#include <stddef.h>
#include "task.h"

enum sm_functions
{
  SM_AQM_DISPLAY  = 0,    // 显示测量数值
  SM_SET_TIME,            // 设置时间
  SM_SET_DATE,            // 设置日期
  SM_SET_PARAM,           // 设置参数
  SM_FUNCTION_CNT
};

typedef void (*SM_PROC)(uint8_t from_func, uint8_t from_state, uint8_t to_func, uint8_t to_state, enum task_events ev);

struct sm_trans
{
  enum task_events event;
  uint8_t to_function;
  uint8_t to_state;
  SM_PROC sm_proc;
};

void sm_init(void);

void sm_run(enum task_events ev);

#endif
