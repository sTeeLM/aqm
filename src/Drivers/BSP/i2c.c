#include "i2c.h"
#include "delay.h"
#include "debug.h"

static I2C_HandleTypeDef hi2c1;

static void BSP_I2C_DisableIRQ(void)
{
//  HAL_NVIC_DisableIRQ(INT_KEY_SET_EXTI_IRQn);
//  HAL_NVIC_DisableIRQ(INT_KEY_MOD_EXTI_IRQn); 
//  HAL_NVIC_DisableIRQ(INT_BT_EXTI_IRQn);
//  HAL_NVIC_DisableIRQ(INT_ALARM_EXTI_IRQn); 
//  HAL_NVIC_DisableIRQ(INT_ACC_EXTI_IRQn);  
//  HAL_NVIC_DisableIRQ(INT_MP3_EXTI_IRQn);   
}

static void BSP_I2C_EnableIRQ(void)
{
//  HAL_NVIC_EnableIRQ(INT_KEY_SET_EXTI_IRQn);
//  HAL_NVIC_EnableIRQ(INT_KEY_MOD_EXTI_IRQn); 
//  HAL_NVIC_EnableIRQ(INT_BT_EXTI_IRQn);
//  HAL_NVIC_EnableIRQ(INT_ALARM_EXTI_IRQn); 
//  HAL_NVIC_EnableIRQ(INT_ACC_EXTI_IRQn);  
//  HAL_NVIC_EnableIRQ(INT_MP3_EXTI_IRQn);  
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
BSP_Error_Type BSP_I2C_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    return BSP_ERROR_INTERNAL;
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */
  return BSP_ERROR_NONE;
}

/**
  * @brief I2C1 Denitialization Function
  * @param None
  * @retval None
  */
void BSP_I2C_DeInit(void)
{
  HAL_I2C_DeInit(&hi2c1);
}

static void BSP_I2C_Quit_Busy(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  
  /**I2C1 GPIO Configuration
  PB6     ------> I2C1_SCL
  PB7     ------> I2C1_SDA
  */
  AQMDBG("enter BSP_I2C_Quit_Busy");
  
  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;  //此行原有
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;   //GPIO配置为输出
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;      //强上拉
  HAL_GPIO_Init(GPIOB,&GPIO_InitStruct);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET); 
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
  
  AQMDBG("wait I2C1_SDA up...");
  while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7) != GPIO_PIN_SET) {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
    delay_us(10);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
    delay_us(10);
  }
  AQMDBG("done!");
  
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
  
  delay_ms(10);
  // SDA 输出一个低脉冲
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
  delay_us(10);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
  
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET); 
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);  
  
  delay_ms(10);
  I2C1->CR1 = I2C_CR1_SWRST;
  delay_ms(10);
  I2C1->CR1 = 0;
  
  __HAL_RCC_I2C1_FORCE_RESET();
  
  // 恢复控制器
  AQMDBG("reinit!");
  BSP_I2C_DeInit();
  delay_ms(10);
  BSP_I2C_Init();
//  I2C1->CR1 = I2C_INIT_SAVE_CR1;
//  I2C1->CR2 = I2C_INIT_SAVE_CR2; 
//  I2C1->OAR1 = I2C_INIT_SAVE_OAR1;
//  I2C1->OAR2 = I2C_INIT_SAVE_OAR2;
//  I2C1->CCR = I2C_INIT_SAVE_CCR; 
//  I2C1->TRISE = I2C_INIT_SAVE_TRISE; 
//  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
//  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
//  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  AQMDBG("done!");
}

#define BSP_I2C_MAX_WAIT_CNT 5000

BSP_Error_Type BSP_I2C_Write(uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size)
{
  HAL_StatusTypeDef ret;
  uint32_t wait_cnt;
  wait_cnt = 0;
  BSP_I2C_DisableIRQ();
  while((ret = HAL_I2C_Mem_Write(&hi2c1, DevAddress, MemAddress, MemAddSize, pData, Size, BSP_I2C_SEND_TIMEOUT)) == HAL_BUSY) {
    delay_us(100);
    wait_cnt ++;
    if(wait_cnt > BSP_I2C_MAX_WAIT_CNT && ret == HAL_BUSY) {
      AQMERR("BSP_I2C_Write busy too long");
      BSP_I2C_Quit_Busy();
      delay_ms(10);
    }
  };
  BSP_I2C_EnableIRQ();
  if(ret != HAL_OK) AQMERR("BSP_I2C_Write ret %d", ret);
  return ret ==  HAL_OK ? BSP_ERROR_NONE : BSP_ERROR_INTERNAL;
}

BSP_Error_Type BSP_I2C_Read(uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size)
{
  HAL_StatusTypeDef ret;
  uint32_t wait_cnt;
  wait_cnt = 0;
  BSP_I2C_DisableIRQ();
  while((ret = HAL_I2C_Mem_Read(&hi2c1, DevAddress, MemAddress, MemAddSize, pData, Size, BSP_I2C_RECV_TIMEOUT)) == HAL_BUSY) {
    delay_us(100);
    wait_cnt ++;
    if(wait_cnt > BSP_I2C_MAX_WAIT_CNT && ret == HAL_BUSY) {
      AQMERR("BSP_I2C_Read busy too long");
      BSP_I2C_Quit_Busy();
      delay_ms(10);
    } 
  };
  BSP_I2C_EnableIRQ();
  if(ret != HAL_OK) AQMERR("BSP_I2C_Read ret %d", ret);
  return ret ==  HAL_OK ? BSP_ERROR_NONE : BSP_ERROR_INTERNAL;
}

/**
* @brief I2C MSP Initialization
* This function configures the hardware resources used in this example
* @param hi2c: I2C handle pointer
* @retval None
*/
void HAL_I2C_MspInit(I2C_HandleTypeDef* hi2c)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(hi2c->Instance==I2C1)
  {
  /* USER CODE BEGIN I2C1_MspInit 0 */

  /* USER CODE END I2C1_MspInit 0 */

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**I2C1 GPIO Configuration
    PB6     ------> I2C1_SCL
    PB7     ------> I2C1_SDA
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* Peripheral clock enable */
    __HAL_RCC_I2C1_CLK_ENABLE();
  /* USER CODE BEGIN I2C1_MspInit 1 */

  /* USER CODE END I2C1_MspInit 1 */
  }

}

/**
* @brief I2C MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hi2c: I2C handle pointer
* @retval None
*/
void HAL_I2C_MspDeInit(I2C_HandleTypeDef* hi2c)
{
  if(hi2c->Instance==I2C1)
  {
  /* USER CODE BEGIN I2C1_MspDeInit 0 */

  /* USER CODE END I2C1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_I2C1_CLK_DISABLE();

    /**I2C1 GPIO Configuration
    PB6     ------> I2C1_SCL
    PB7     ------> I2C1_SDA
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6);

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_7);

  /* USER CODE BEGIN I2C1_MspDeInit 1 */

  /* USER CODE END I2C1_MspDeInit 1 */
  }

}

