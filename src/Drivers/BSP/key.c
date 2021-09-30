#include "key.h"
#include "bsp.h"
#include "debug.h"

BSP_Error_Type BSP_Key_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  
  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pins : INT_KEY_MOD_Pin */
  GPIO_InitStruct.Pin = INT_KEY_MOD_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(INT_KEY_MOD_GPIO_Port, &GPIO_InitStruct);
  
  /*Configure GPIO pins : INT_KEY_SET_Pin */
  GPIO_InitStruct.Pin = INT_KEY_SET_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(INT_KEY_SET_GPIO_Port, &GPIO_InitStruct); 
  
  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(INT_KEY_MOD_EXTI_IRQn, BSP_KEY_IRQ_PRIORITY, BSP_KEY_IRQ_SUB_PRIORITY);
  HAL_NVIC_EnableIRQ(INT_KEY_MOD_EXTI_IRQn);

  HAL_NVIC_SetPriority(INT_KEY_SET_EXTI_IRQn, BSP_KEY_IRQ_PRIORITY, BSP_KEY_IRQ_SUB_PRIORITY);
  HAL_NVIC_EnableIRQ(INT_KEY_SET_EXTI_IRQn);  
  
  return BSP_ERROR_NONE;
}

bool BSP_Key_Is_Factory_Reset(void)
{
  return BSP_Key_Set_Pressed();
}

bool BSP_Key_Set_Pressed(void)
{
  return HAL_GPIO_ReadPin(INT_KEY_SET_GPIO_Port, INT_KEY_SET_Pin) == GPIO_PIN_RESET;
}

bool BSP_Key_Mod_Pressed(void)
{
  return HAL_GPIO_ReadPin(INT_KEY_MOD_GPIO_Port, INT_KEY_MOD_Pin) == GPIO_PIN_RESET;
}

/**
  * @brief This function handles EXTI line4 interrupt.
  */
void EXTI4_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI4_IRQn 0 */

  /* USER CODE END EXTI4_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
  /* USER CODE BEGIN EXTI4_IRQn 1 */

  /* USER CODE END EXTI4_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[9:5] interrupts.
  */
void EXTI9_5_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI9_5_IRQn 0 */

  /* USER CODE END EXTI9_5_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
  /* USER CODE BEGIN EXTI9_5_IRQn 1 */

  /* USER CODE END EXTI9_5_IRQn 1 */
}