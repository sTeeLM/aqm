#include "pms.h"

BSP_Error_Type BSP_PMS_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_GPIOA_CLK_ENABLE();  
  __HAL_RCC_GPIOB_CLK_ENABLE();
  
  HAL_GPIO_WritePin(PMS_RESET_GPIO_Port, PMS_RESET_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(PMS_SET_GPIO_Port, PMS_SET_Pin, GPIO_PIN_RESET);
  
  /*Configure GPIO pins : PMS_SET_Pin */
  GPIO_InitStruct.Pin = PMS_SET_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(PMS_SET_GPIO_Port, &GPIO_InitStruct);
  
  /*Configure GPIO pins : PMS_RESET_GPIO_Port */
  GPIO_InitStruct.Pin = PMS_RESET_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(PMS_RESET_GPIO_Port, &GPIO_InitStruct);
  
  return BSP_ERROR_NONE;
}
