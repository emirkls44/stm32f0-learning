#include "main.h"

#define TRUE	1
#define FALSE	0
void SystemClockConfig(uint8_t clock_freq);
void UART2_Init(void);
void Error_handler(void);

UART_HandleTypeDef huart2;

char msg[100];



int  main(void){




	HAL_Init();
	UART2_Init();

	SystemClockConfig(SYS_CLOCK_FREQ_48_MHZ);
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

	UART2_Init();

		memset(msg, 0, sizeof(msg));
	    sprintf(msg, "SYSCLK : %lu\r\n", HAL_RCC_GetSysClockFreq());
	    HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);

	    memset(msg, 0, sizeof(msg));
	    sprintf(msg, "HCLK : %lu\r\n", HAL_RCC_GetHCLKFreq());
	    HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);

	    memset(msg, 0, sizeof(msg));
	    sprintf(msg, "PCLK : %lu\r\n", HAL_RCC_GetPCLK1Freq());
	    HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);


	while(1){

	}



}


void SystemClockConfig(uint8_t clock_freq)
{
	RCC_OscInitTypeDef osc_init;
	RCC_ClkInitTypeDef clk_init;

	uint32_t FLatency =0;

	osc_init.OscillatorType=RCC_OSCILLATORTYPE_HSI;
	osc_init.HSIState=RCC_HSI_ON;
	osc_init.HSICalibrationValue=16;
	osc_init.PLL.PLLState=RCC_PLL_ON;
	osc_init.PLL.PLLSource=RCC_PLLSOURCE_HSI;

	switch (clock_freq) {
	case SYS_CLOCK_FREQ_16_MHZ:
	{

		osc_init.PLL.PLLMUL = RCC_PLL_MUL4;

		clk_init.ClockType=RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | \
				RCC_CLOCKTYPE_PCLK1;
		clk_init.SYSCLKSource=RCC_SYSCLKSOURCE_PLLCLK;
		clk_init.AHBCLKDivider=RCC_SYSCLK_DIV1;
		clk_init.APB1CLKDivider=RCC_SYSCLK_DIV2;

		FLatency= FLASH_LATENCY_1;

	    break;
	}

	case SYS_CLOCK_FREQ_32_MHZ:
	{
		osc_init.PLL.PLLMUL = RCC_PLL_MUL8;
		clk_init.ClockType=RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | \
					RCC_CLOCKTYPE_PCLK1;
			clk_init.SYSCLKSource=RCC_SYSCLKSOURCE_PLLCLK;
			clk_init.AHBCLKDivider=RCC_SYSCLK_DIV1;
			clk_init.APB1CLKDivider=RCC_SYSCLK_DIV4;

			FLatency= FLASH_LATENCY_1;

	    break;
	}
	case SYS_CLOCK_FREQ_48_MHZ:
	{
		osc_init.PLL.PLLMUL = RCC_PLL_MUL12;

		clk_init.ClockType=RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | \
						RCC_CLOCKTYPE_PCLK1;
				clk_init.SYSCLKSource=RCC_SYSCLKSOURCE_PLLCLK;
				clk_init.AHBCLKDivider=RCC_SYSCLK_DIV1;
				clk_init.APB1CLKDivider=RCC_SYSCLK_DIV8;

				FLatency= FLASH_LATENCY_1;

	    break;
	}

	default:
		break;
	}
		if(HAL_RCC_OscConfig(&osc_init)!=HAL_OK)
		{
			Error_handler();
		}

		if(HAL_RCC_ClockConfig(&clk_init,FLatency)!=HAL_OK)
		{
			Error_handler();
		}

		//Systick configuration

		HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
		HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
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



}

void Error_handler(void)
{
	while(1);
}









