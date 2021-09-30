#ifndef __AQM_USART_H__
#define __AQM_USART_H__

#include <stdint.h>
#include "bsp.h"

BSP_Error_Type BSP_USART1_Init(void);
BSP_Error_Type BSP_USART2_Init(void);
BSP_Error_Type BSP_USART1_Transmit(uint8_t *pData, uint16_t Size);
BSP_Error_Type BSP_USART1_Receive(uint8_t *pData, uint16_t Size);
int16_t BSP_USART1_Get_Char(void);
int16_t BSP_USART1_Try_Get_Char(void);
#endif