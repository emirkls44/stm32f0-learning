#include "main.h"

void SystemClockConfig(void);
void GPIO_Init(void);
void TIM6_Init(void);
void Error_handler(void);

TIM_HandleTypeDef htimer6;

int  main(void)
{
	HAL_Init();
	GPIO_Init();
	SystemClockConfig();
	TIM6_Init();

	HAL_TIM_Base_Start_IT(&htimer6);

	while(1){

	}

}

void SystemClockConfig(void)
{

}
void GPIO_Init(void)
{
	__HAL_RCC_GPIOC_CLK_ENABLE();

	GPIO_InitTypeDef ledgpio;
	ledgpio.Pin=GPIO_PIN_8;
	ledgpio.Mode=GPIO_MODE_OUTPUT_PP;
	ledgpio.Pull=GPIO_NOPULL;
	HAL_GPIO_Init(GPIOC,&ledgpio);
}

void TIM6_Init(void)
{
	__HAL_RCC_TIM6_CLK_ENABLE();

	htimer6.Instance=TIM6;
	htimer6.Init.Prescaler=8000-1;
	htimer6.Init.Period=999;

	if(HAL_TIM_Base_Init(&htimer6)!=HAL_OK){
		Error_handler();
	}

	HAL_NVIC_SetPriority(TIM6_DAC_IRQn,0,0);
	HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_8);
}

void Error_handler(void)
{
	while(1);
}





