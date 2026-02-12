#include "main.h"
#include <string.h>

UART_HandleTypeDef huart1;

char *mesaj = "Sistem Aktif\r\n";

#define BUFFER_SIZE 64
uint8_t tx_buffer[BUFFER_SIZE];
volatile uint8_t head = 0;
volatile uint8_t tail = 0;

uint8_t rx_byte;
volatile uint8_t tx_mesgul = 0;

static void MX_USART1_Init(void);

int main(void){
    HAL_Init();
    MX_USART1_Init();

    HAL_UART_Receive_IT(&huart1, &rx_byte, 1);
    HAL_UART_Transmit(&huart1, (uint8_t*)mesaj, strlen(mesaj), 100);

    while (1){

    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
    if (huart->Instance == USART1){

        if(head < BUFFER_SIZE){
            tx_buffer[head] = rx_byte;
            head++;

            if(tx_mesgul == 0){
                tx_mesgul = 1;
                HAL_UART_Transmit_IT(&huart1, &tx_buffer[tail], 1);
            }
        }
        HAL_UART_Receive_IT(&huart1, &rx_byte, 1);
    }
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
    if (huart->Instance == USART1){

        tail++;
        if(tail < head){
            HAL_UART_Transmit_IT(&huart1, &tx_buffer[tail], 1);
        }
        else {
            head = 0;
            tail = 0;
            tx_mesgul = 0;
        }
    }
}
static void MX_USART1_Init(void)
{
    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

    if (HAL_UART_Init(&huart1) != HAL_OK)
    {
        Error_Handler();
    }

    HAL_NVIC_EnableIRQ(USART1_IRQn);
}

void Error_Handler(void)
{
    __disable_irq();
    while (1)
    {
    }
}
