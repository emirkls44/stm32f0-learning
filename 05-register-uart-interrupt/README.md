# 05 – Register-level UART with interrupts

USART1 receive and transmit handled in `USART1_IRQHandler()` without the HAL UART driver.

- 9600 8N1 on PA9 (TX) / PA10 (RX), `BRR = 833` for the 8 MHz HSI
- A message is the text between `@` and `*`. `@hello*` is answered with `>> GELEN: hello`
- RX: every byte is read in the interrupt (`RXNE`); bytes after `@` are stored until `*`
- TX: `TXEIE` is enabled and the interrupt sends one byte per `TXE` until the string ends
- Overrun and framing errors are cleared through `ICR`

Changes after the first version: the reply is formatted in the main loop instead of calling
`sprintf()` inside the interrupt, a new reply is not written into the buffer while the previous one is
still being sent, and `ICR` is written directly (it is write-1-to-clear, so `|=` is wrong).
