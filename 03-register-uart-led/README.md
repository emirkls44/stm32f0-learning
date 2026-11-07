# 03 – Register-level GPIO and UART

LED and UART output written directly against the RCC, GPIO and USART1 registers (HAL is only used
for `HAL_Init()` and `HAL_GetTick()`).

Every 500 ms the green LED (LD3, PC9) toggles and `LED ACIK` / `LED KAPALI` is sent over UART.

| Item | Setting |
|---|---|
| UART | USART1 TX on PA9 (AF1), 9600 8N1 |
| Baud rate | `BRR = 8 MHz / 9600 = 833` (HSI, no PLL) |
| Transmit | polling: wait for `TXE` (ISR bit 7), then write `TDR` |

Wiring: PA9 → RX of a USB-UART adapter, GND → GND.
