#include "power.h"

BSP_Error_Type BSP_Power_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  
  __HAL_RCC_GPIOA_CLK_ENABLE();
  
  HAL_GPIO_WritePin(POWER_GPIO_Port, POWER_Pin, GPIO_PIN_RESET);
  
  /*Configure GPIO pins : POWER_Pin */
  GPIO_InitStruct.Pin = POWER_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(POWER_GPIO_Port, &GPIO_InitStruct);
  
  /*Configure GPIO pin : INT_CHARGE_Pin */
  GPIO_InitStruct.Pin = INT_CHARGE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(INT_CHARGE_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(INT_CHARGE_EXTI_IRQn, BSP_CHARGE_IRQ_PRIORITY, BSP_CHARGE_IRQ_SUB_PRIORITY);
  HAL_NVIC_EnableIRQ(INT_CHARGE_EXTI_IRQn);
  
  return BSP_ERROR_NONE;
}

/**
  * @brief This function handles EXTI line[15:10] interrupts.
  */
void EXTI15_10_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI15_10_IRQn 0 */

  /* USER CODE END EXTI15_10_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(INT_CHARGE_Pin);
  /* USER CODE BEGIN EXTI15_10_IRQn 1 */

  /* USER CODE END EXTI15_10_IRQn 1 */
}