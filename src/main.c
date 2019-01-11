#include "RTE_Components.h"             // Component selection
#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO


#define LED_GPIO_RCC          RCC_APB2Periph_GPIOC
#define LED_GPIO_PORT         GPIOC
#define LED_GPIO_PIN      		GPIO_Pin_13
#define LED_ONOFF(x)     			GPIO_WriteBit(LED_GPIO_PORT,LED_GPIO_PIN,x);

void LED_GPIO_Config(void);	

void LED_GPIO_Config(void)
{	
    //定义一个GPIO_InitTypeDef 类型的结构体
    GPIO_InitTypeDef  GPIO_InitStructure;	
    RCC_APB2PeriphClockCmd(LED_GPIO_RCC,ENABLE);//使能GPIO的外设时钟
    /*D1*/
    GPIO_InitStructure.GPIO_Pin =LED_GPIO_PIN;//选择要用的GPIO引脚
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //设置引脚模式为推免输出模式						 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//设置引脚速度为50MHZ         
    GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);//调用库函数，初始化GPIO
}

 /**
  * @file   LEDXToggle
  * @brief  LED亮灭翻转
  * @param  ledx:1--PC13;2--PB0;1--PB1
  * @retval 无
  */

void Delay_ms( uint16_t time_ms )
{
  uint16_t i,j;
  for( i=0;i<time_ms;i++ )
  {
		for( j=0;j<10309;j++ );//大约1ms
  }
}

int main(void)
{
  int i;
  /*初始化LED端口*/
  LED_GPIO_Config();
  while(1)
  {	
    LED_ONOFF(Bit_SET);
    Delay_ms(200);
    LED_ONOFF(Bit_RESET);
    Delay_ms(200);
  }		
}
