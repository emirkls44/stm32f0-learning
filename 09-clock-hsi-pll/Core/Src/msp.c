

#include "main.h"

 void HAL_MspInit(void)
{


}


void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	GPIO_InitTypeDef gpio_uart;

	__HAL_RCC_USART2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	gpio_uart.Pin=GPIO_PIN_2;
	gpio_uart.Mode=GPIO_MODE_AF_PP;
	gpio_uart.Pull=GPIO_PULLUP;
	gpio_uart.Speed=GPIO_SPEED_FREQ_LOW;
	gpio_uart.Alternate=GPIO_AF1_USART2;//USART2_TX
	HAL_GPIO_Init(GPIOA,&gpio_uart);

	gpio_uart.Pin=GPIO_PIN_3;//USART2_RX
	HAL_GPIO_Init(GPIOA,&gpio_uart);

	HAL_NVIC_EnableIRQ(USART2_IRQn);
	HAL_NVIC_SetPriority(USART2_IRQn, 3, 0);




}
