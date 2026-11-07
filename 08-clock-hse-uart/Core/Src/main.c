


#include "main.h"
#include <stdio.h>


#define TRUE	1
#define FALSE	0
void UART2_Init(void);
void Error_handler(void);


UART_HandleTypeDef huart2;

uint8_t data_buffer[100];
uint8_t rcvd_data=0;
volatile uint8_t reception_complete = FALSE;
volatile uint32_t count=0;

int  main(void){


	RCC_OscInitTypeDef osc_init;
	RCC_ClkInitTypeDef clk_init = {0};
	char msg[100];

	HAL_Init();

	memset(&osc_init,0,sizeof(osc_init));
	osc_init.OscillatorType=RCC_OSCILLATORTYPE_HSE;
	osc_init.HSEState=RCC_HSE_BYPASS;
	if(HAL_RCC_OscConfig(&osc_init)!=HAL_OK)
		{
			Error_handler();
		}


	clk_init.ClockType=RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | \
			RCC_CLOCKTYPE_PCLK1;
	clk_init.SYSCLKSource=RCC_SYSCLKSOURCE_HSE;
	clk_init.AHBCLKDivider=RCC_SYSCLK_DIV2;
	/* APB prescaler values are RCC_HCLK_DIVx; RCC_SYSCLK_DIVx (used here
	 * before) is the AHB encoding and was written into the AHB field.
	 * APB1 is left undivided: at PCLK = 2 MHz the 115200 baud rate would be
	 * 2.1 % off, at 4 MHz it is 0.8 %. */
	clk_init.APB1CLKDivider=RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&clk_init,FLASH_LATENCY_0)!=HAL_OK) {
		Error_handler();
	}
	__HAL_RCC_HSI_DISABLE();


	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

	UART2_Init();

	memset(msg,0,sizeof(msg));
	sprintf(msg,"SYSCLK : %lu\r\n",HAL_RCC_GetSysClockFreq());
	HAL_UART_Transmit(&huart2,(uint8_t*)msg,strlen(msg), HAL_MAX_DELAY);

	memset(msg,0,sizeof(msg));
	sprintf(msg,"HCLK : %lu\r\n",HAL_RCC_GetHCLKFreq());
	HAL_UART_Transmit(&huart2,(uint8_t*)msg,strlen(msg), HAL_MAX_DELAY);

	memset(msg,0,sizeof(msg));
	sprintf(msg,"PCLK : %lu\r\n",HAL_RCC_GetPCLK1Freq());
	HAL_UART_Transmit(&huart2,(uint8_t*)msg,strlen(msg), HAL_MAX_DELAY);

	/* Reception was never started before, so the callback below never ran. */
	HAL_UART_Receive_IT(&huart2, &rcvd_data, 1);

	while(1){
		/* Echo a complete message from the main loop: a blocking transmit
		 * with HAL_MAX_DELAY must not run inside the interrupt callback. */
		if (reception_complete == TRUE)
		{
			HAL_UART_Transmit(&huart2, data_buffer, count, HAL_MAX_DELAY);
			count = 0;
			reception_complete = FALSE;
			HAL_UART_Receive_IT(&huart2, &rcvd_data, 1);
		}
	}



}




void UART2_Init(void){
	huart2.Instance= USART2;
	huart2.Init.BaudRate=115200;
	huart2.Init.WordLength=UART_WORDLENGTH_8B;
	huart2.Init.StopBits=UART_STOPBITS_1;
	huart2.Init.Parity=UART_PARITY_NONE;
	huart2.Init.HwFlowCtl=UART_HWCONTROL_NONE;
	huart2.Init.Mode=UART_MODE_TX_RX;
	if (HAL_UART_Init(&huart2)!=HAL_OK){
		Error_handler();
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	data_buffer[count++] = rcvd_data;

	/* A message ends with '*'. Also stop when the buffer is full instead of
	 * writing past its end. */
	if ((rcvd_data == '*') || (count >= sizeof(data_buffer)))
	{
		reception_complete = TRUE; /* main loop echoes it and restarts reception */
		return;
	}

	HAL_UART_Receive_IT(huart, &rcvd_data, 1);
}

void Error_handler(void)
{
	while(1);
}









