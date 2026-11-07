#include "main.h"
#include "stdio.h"

char rx_buffer[100];
uint8_t rx_index = 0;
uint8_t kayit_basladi = 0;

char tx_buffer_main[150];
char *tx_ptr;
volatile uint8_t tx_busy = 0;


void USART1_Send_Message_IT(char* str);

int main(void)
{
  HAL_Init();

  RCC->AHBENR  |= RCC_AHBENR_GPIOAEN;
  RCC->APB2ENR |= RCC_APB2ENR_USART1EN;


  GPIOA->MODER |=  (2<<20) | (2<<18);
  GPIOA->AFR[1] |=  ((1 << 4) | (1 << 8));

  USART1->BRR = 833;
  USART1->CR1 |= USART_CR1_UE | USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE;

  NVIC_EnableIRQ(USART1_IRQn);

  while (1)
  {

  }
}

void USART1_Send_Message_IT(char* str) {
    if (tx_busy) {
    	return;
    }
    tx_busy = 1;
    tx_ptr = str;

    USART1->CR1 |= USART_CR1_TXEIE;
}


void USART1_IRQHandler(void) {

    if (USART1->ISR & USART_ISR_RXNE) {

        char c = USART1->RDR;

        if (c == '@') {
            rx_index = 0;
            kayit_basladi = 1;

        }
        else if (kayit_basladi) {

            if (c == '*') {
                rx_buffer[rx_index] = '\0';
                kayit_basladi = 0;

                sprintf(tx_buffer_main, "\r\n>> GELEN: %s\r\n", rx_buffer);
                USART1_Send_Message_IT(tx_buffer_main);
            }
            else if (rx_index < 99) {
                rx_buffer[rx_index++] = c;
            }
        }
    }

    if (USART1->ISR & USART_ISR_TXE) {
        if (tx_busy) {
            if (*tx_ptr != '\0') {
                USART1->TDR = *tx_ptr++;
            }
            else {
                USART1->CR1 &= ~USART_CR1_TXEIE;
                tx_busy = 0;
            }
        }
    }
    if (USART1->ISR & (USART_ISR_ORE | USART_ISR_FE)) {
        USART1->ICR |=(USART_ICR_ORECF | USART_ICR_FECF);
    }
}
