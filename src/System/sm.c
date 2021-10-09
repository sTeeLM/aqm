#include "sm.h"

#include "clock.h"
#include "delay.h"
#include "power.h"

#include "debug.h"

static const char * sm_functions_names[] = {
  "SM_AQM_DISPLAY",      // 显示测量数值
  "SM_SET_TIME",         // 时间设置
  "SM_SET_DATE",         // 日期设置
  "SM_SET_PARAM",        // 参数设置
};

static const char ** sm_states_names[] = {
};

static struct sm_trans ** sm_trans_table[] = {
};

static uint8_t sm_cur_fuction;
static uint8_t sm_cur_state;

void sm_init(void)
{
//  sm_cur_fuction = SM_CLOCK_DISPLAY;
//  sm_cur_state   = SM_CLOCK_DISPLAY_INIT;
  task_set(EV_BUTTON_MOD_UP);
}

void sm_run(enum task_events ev)
{
  uint8_t i;
  uint8_t new_fun, new_state;
  
  struct sm_trans *p = NULL;
  
  if(ev == EV_POWEROFF) {
    
  } else {
    p = sm_trans_table[sm_cur_fuction][sm_cur_state];
    while(p != NULL && p->sm_proc) {
      if(p->event == ev) {
        AQMDBG("[%s] [%s][%s] -> [%s][%s]",
          task_names[ev],
          sm_functions_names[sm_cur_fuction],
          sm_states_names[sm_cur_fuction][sm_cur_state],
          sm_functions_names[p->to_function],
          sm_states_names[p->to_function][p->to_state]     
        );
        p->sm_proc(sm_cur_fuction, sm_cur_state, p->to_function, p->to_state, ev);
        sm_cur_fuction = p->to_function;
        sm_cur_state   = p->to_state;
        break;
      }
      p ++;
    }
  }
}

