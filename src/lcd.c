#include <stdint.h>
#include "lcd.h"
#include "RTE_Components.h"             // Component selection
#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO

#define LCD_RW GPIO_Pin_5
#define LCD_RS GPIO_Pin_6
#define LCD_E GPIO_Pin_7

#define LCD_D0 GPIO_Pin_8
#define LCD_D1 GPIO_Pin_9
#define LCD_D2 GPIO_Pin_10
#define LCD_D3 GPIO_Pin_11
#define LCD_D4 GPIO_Pin_12
#define LCD_D5 GPIO_Pin_13
#define LCD_D6 GPIO_Pin_14
#define LCD_D7 GPIO_Pin_15

void delay_us（uint32_t cnt)
{
  char i;
  while(cnt--) {
　　i = 10;
　　while(i--);
  }
}



static void lcd_wait_fbuf(void)
{
  GPIO_ResetBits(GPIOB, LCD_RS);
  GPIO_SetBits(GPIOB, LCD_RW);
  GPIO_SetBits(GPIOB, LCD_E);
  
  GPIOB->ODR =  GPIOB->ODR | 0xF0; // data 全部写1
  
  while((GPIOB->ODR & 0xF0 == 0xF0));
  
  GPIO_SetBits(GPIOB, LCD_RW);
  GPIO_ResetBits(GPIOB, LCD_E);
  
}

static void lcd_write_instruction(uint8_t val)
{
  uint16_t tmp;
  lcd_wait_fbuf();
  GPIO_ResetBits(GPIOB, LCD_RS);
  GPIO_ResetBits(GPIOB, LCD_RW);
  GPIO_ResetBits(GPIOB, LCD_E);
  
  tmp = val;
  tmp <<= 8;
  tmp |= (GPIOB->ODR & 0x0F);
  GPIOB->ODR = tmp;
  
  delay_us(340);
  GPIO_SetBits(GPIOB, LCD_E);
  delay_us(340);
  GPIO_ResetBits(GPIOB, LCD_E);
}

static void lcd_write_data(uint8_t val)
{
  uint16_t tmp;
  lcd_wait_fbuf();
  GPIO_SetBits(GPIOB, LCD_RS);
  GPIO_ResetBits(GPIOB, LCD_RW);
  GPIO_ResetBits(GPIOB, LCD_E);
  
  tmp = val;
  tmp <<= 8;
  tmp |= (GPIOB->ODR & 0x0F);
  GPIOB->ODR = tmp;
  
  delay_us(340);
  GPIO_SetBits(GPIOB, LCD_E);
  delay_us(340);
  GPIO_ResetBits(GPIOB, LCD_E);
}

void lcd_initialize(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能GPIO的外设时钟
  
  GPIO_InitStruct.GPIO_Pin = LCD_RW |LCD_RS | LCD_E
    | LCD_D0 |LCD_D1 | LCD_D2 | LCD_D3 
    | LCD_D4 |LCD_D5 | LCD_D6 | LCD_D7;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void lcd_set_pm_1_0(uint16_t val) // ug/m3
{
  
}

void lcd_set_pm_2_5(uint16_t val) // ug/m3
{
  
}

void lcd_set_pm_10(uint16_t val) // ug/m3
{
  
}

void lcd_set_temperature(uint16_t val) // val/10 
{
  
}

void lcd_set_humidity(uint16_t val) // val/10
{
  
}

void lcd_set_formaldehyde(uint16_t val) // g/m3
{
  
}

void lcd_refresh(void)
{
  
}

void lcd_rotate(void)
{
  
}