# 08 – HSE clock configuration and UART

Clock tree set up by hand with `HAL_RCC_OscConfig()` / `HAL_RCC_ClockConfig()` (no CubeMX code
generation: own `msp.c` and `it.c`), then the resulting frequencies are printed over UART.

| Clock | Value |
|---|---|
| SYSCLK | 8 MHz HSE in bypass mode (external 8 MHz clock, e.g. from the ST-LINK MCO) |
| HCLK | SYSCLK / 2 = 4 MHz, flash latency 0 |
| PCLK | HCLK / 1 = 4 MHz |

After start-up the board prints `SYSCLK`, `HCLK` and `PCLK` on USART2 (PA2 TX, PA3 RX, 115200 8N1)
and then echoes every message that ends with `*`.

Fixes compared with the first version:

- `APB1CLKDivider` was set to `RCC_SYSCLK_DIV2`, which is the *AHB* prescaler encoding. HAL wrote
  it into the AHB field, so the APB divider never took effect. It now uses `RCC_HCLK_DIV1`
  (dividing further would put the 115200 baud rate 2.1 % off).
- `HAL_UART_Receive_IT()` was never called, so the echo never worked.
- The receive callback no longer writes past the 100-byte buffer or blocks inside the interrupt
  with `HAL_UART_Transmit(..., HAL_MAX_DELAY)`; the main loop sends the echo.
