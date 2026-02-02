#include "main.h"

int main(void) {
    HAL_Init();

    RCC->AHBENR |= (1 << 17) | (1 << 19);
    RCC->APB2ENR |= (1 << 14);

    GPIOC->MODER |= (1 << 18);   //01

    GPIOA->MODER |= (2 << 18);   //
    GPIOA->AFR[1] &= ~(0xF << 4);
    GPIOA->AFR[1] |= (1 << 4); // AF1: USART1_TX

    USART1->BRR = 833;
    USART1->CR1 = (1 << 0) | (1 << 3); // UE ve TE aktif

    uint32_t lastTick = 0;
    const uint32_t ms = 500;

    while (1) {
        if (HAL_GetTick() - lastTick >= ms) {
            lastTick = HAL_GetTick();

            GPIOC->ODR ^= (1 << 9);

            if (GPIOC->ODR & (1 << 9)) {
                char msg[] = "LED ACIK\r\n";

                for(int i = 0; msg[i] != '\0'; i++) {
                    while (!(USART1->ISR & (1 << 7))); // TXE bekle
                    USART1->TDR = msg[i];
                }

            } else {
                char msg[] = "LED KAPALI\r\n";

                for(int i = 0; msg[i] != '\0'; i++) {
                    while (!(USART1->ISR & (1 << 7)));
                    USART1->TDR = msg[i];
                }

            }
        }
    }
}
