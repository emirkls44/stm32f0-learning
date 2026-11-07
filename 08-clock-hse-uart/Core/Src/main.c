


#include "main.h"


#define TRUE	1
#define FALSE	0
void SystemClockConfig(void);
void UART2_Init(void);
void Error_handler(void);


UART_HandleTypeDef huart2;
char *pdata="transmit islemi basarili";

uint8_t data_buffer[100];
uint8_t rcvd_data=0;
uint8_t reception_complate;
uint32_t count=0;

int  main(void){


	RCC_OscInitTypeDef osc_init;
	RCC_ClkInitTypeDef clk_init;
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
	clk_init.APB1CLKDivider=RCC_SYSCLK_DIV2;

	if (HAL_RCC_ClockConfig(&clk_init,FLASH_LATENCY_0)!=HAL_OK) {
		Error_handler();
	}
	__HAL_RCC_HSI_DISABLE();


	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

	UART2_Init();

	memset(msg,0,sizeof(msg));
	sprintf(msg,"SYSCLK : % ld\r\n",HAL_RCC_GetSysClockFreq());
	HAL_UART_Transmit(&huart2,msg,strlen(msg), HAL_MAX_DELAY);

	memset(msg,0,sizeof(msg));
	sprintf(msg,"HCLK : % ld\r\n",HAL_RCC_GetHCLKFreq());
	HAL_UART_Transmit(&huart2,msg,strlen(msg), HAL_MAX_DELAY);

	memset(msg,0,sizeof(msg));
	sprintf(msg,"PCLK : % ld\r\n",HAL_RCC_GetPCLK1Freq());
	HAL_UART_Transmit(&huart2,msg,strlen(msg), HAL_MAX_DELAY);

	while(1){

	}



}


void SystemClockConfig(void){

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

	if(rcvd_data =='*')
	{
		reception_complate=TRUE;
		data_buffer[count++]='*';
		HAL_UART_Transmit(huart,data_buffer,count, HAL_MAX_DELAY);
		count = 0;
	}
	else
	{
		data_buffer[count++]=rcvd_data;
	}
	HAL_UART_Receive_IT(&huart2, &rcvd_data, 1);

}

void Error_handler(void)
{
	while(1);
}









