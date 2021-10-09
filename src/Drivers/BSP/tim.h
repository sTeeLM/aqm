#ifndef __AQM_TIM_H__
#define __AQM_TIM_H__

#include <stdint.h>
#include "bsp.h"

BSP_Error_Type BSP_TIM1_Init(void);
BSP_Error_Type BSP_TIM1_Start(void);
BSP_Error_Type BSP_TIM1_Stop(void);
void BSP_TIM1_Start_Beeper(uint8_t Dur, uint8_t Loop);
void BSP_TIM1_Start_PMW(void);
void BSP_TIM1_Stop_PMW(void);
BSP_Error_Type BSP_TIM2_Init(void);

#endif