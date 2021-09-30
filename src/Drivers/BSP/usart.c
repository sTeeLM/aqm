#include "usart.h"
#include "delay.h"

static UART_HandleTypeDef huart1;
static UART_HandleTypeDef huart2;

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
BSP_Error_Type BSP_USART1_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    return BSP_ERROR_INTERNAL;
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */
  return BSP_ERROR_NONE;
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
BSP_Error_Type BSP_USART2_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    return BSP_ERROR_INTERNAL;
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */
  return BSP_ERROR_NONE;
}

/**
* @brief UART MSP Initialization
* This function configures the hardware resources used in this example
* @param huart: UART handle pointer
* @retval None
*/
void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(huart->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
  else if(huart->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspInit 0 */

  /* USER CODE END USART2_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART2 interrupt Init */
    HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspInit 1 */

  /* USER CODE END USART2_MspInit 1 */
  }

}

/**
* @brief UART MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param huart: UART handle pointer
* @retval None
*/
void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{
  if(huart->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

    /* USART1 interrupt DeInit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
  else if(huart->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspDeInit 0 */

  /* USER CODE END USART2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();

    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3);

    /* USART2 interrupt DeInit */
    HAL_NVIC_DisableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspDeInit 1 */

  /* USER CODE END USART2_MspDeInit 1 */
  }

}

/**
  * @brief This function handles USART1 global interrupt.
  */
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */

  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */

  /* USER CODE END USART1_IRQn 1 */
}

/**
  * @brief This function handles USART2 global interrupt.
  */
void USART2_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */

  /* USER CODE END USART2_IRQn 0 */
  HAL_UART_IRQHandler(&huart2);
  /* USER CODE BEGIN USART2_IRQn 1 */

  /* USER CODE END USART2_IRQn 1 */
}

static BSP_Error_Type BSP_USART_Transmit(UART_HandleTypeDef * huart, uint8_t *pData, uint16_t Size)
{
  HAL_StatusTypeDef res = HAL_UART_Transmit(huart, pData, Size, BSP_USART1_TRANSMIT_TIMEOUT);
  BSP_Error_Type ret = BSP_ERROR_INTERNAL;
  switch(res) {
    case HAL_ERROR:
      ret = BSP_ERROR_INTERNAL;
      break;
    case HAL_TIMEOUT:
      ret = BSP_ERROR_TIMEOUT;
      break;
    case HAL_BUSY:
      ret = BSP_ERROR_BUSY;
      break;
    case HAL_OK:
      ret = BSP_ERROR_NONE;
      break;
  }
  return ret;  
}

static BSP_Error_Type BSP_USART_Receive(UART_HandleTypeDef * huart, uint8_t *pData, uint16_t Size)
{
  HAL_StatusTypeDef res = HAL_UART_Receive(huart, pData, Size, BSP_USART1_RECEIVE_TIMEOUT);
  BSP_Error_Type ret = BSP_ERROR_INTERNAL;
  switch(res) {
    case HAL_ERROR:
      ret = BSP_ERROR_INTERNAL;
      break;
    case HAL_TIMEOUT:
      ret = BSP_ERROR_TIMEOUT;
      break;
    case HAL_BUSY:
      ret = BSP_ERROR_BUSY;
      break;
    case HAL_OK:
      ret = BSP_ERROR_NONE;
      break;
  }
  return ret;  
}

static BSP_Error_Type BSP_USART_Transmit_IT(UART_HandleTypeDef * huart, uint8_t *pData, uint16_t Size)
{
  BSP_Error_Type ret = BSP_ERROR_INTERNAL;
  HAL_StatusTypeDef res;
   
  res = HAL_UART_Transmit_IT(huart, pData, Size);
  switch(res) {
    case HAL_ERROR:
      ret = BSP_ERROR_INTERNAL;
      break;
    case HAL_BUSY:
      ret = BSP_ERROR_BUSY;
      break;
    case HAL_OK:
      ret = BSP_ERROR_NONE;
      break;
    default:;
  }
  return ret;
}

static BSP_Error_Type BSP_USART_Receive_IT(UART_HandleTypeDef * huart, uint8_t *pData, uint16_t Size)
{
  BSP_Error_Type ret = BSP_ERROR_INTERNAL;
  HAL_StatusTypeDef res;
  
  res = HAL_UART_Receive_IT(huart, pData, Size);
  switch(res) {
    case HAL_ERROR:
      ret = BSP_ERROR_INTERNAL;
      break;
    case HAL_BUSY:
      ret = BSP_ERROR_BUSY;
      break;
    case HAL_OK:
      ret = BSP_ERROR_NONE;
      break;
    default:;
  }
  return ret;
}

//--------------------------------------------------------------------------------
BSP_Error_Type BSP_USART1_Transmit(uint8_t *pData, uint16_t Size)
{
  return BSP_USART_Transmit(&huart1, pData, Size);
}

BSP_Error_Type BSP_USART1_Receive(uint8_t *pData, uint16_t Size)
{
  return BSP_USART_Receive(&huart1, pData, Size);
}

int16_t BSP_USART1_Try_Get_Char(void)
{
  uint8_t ch = 0;
  HAL_StatusTypeDef res = HAL_UART_Receive(&huart1, &ch, 1, 0);
  if(res != HAL_OK) {
    return 0;
  } else {
    return ch;
  }
}

int16_t BSP_USART1_Get_Char(void)
{
  uint8_t ch = 0;
  HAL_StatusTypeDef res;
  while((res = HAL_UART_Receive(&huart1, &ch, 1, BSP_USART1_RECEIVE_TIMEOUT)) == HAL_TIMEOUT) {
    delay_us(10);
  }
  if(res == HAL_OK) {
    return ch;
  } else {
    return -1 ;
  }
}
