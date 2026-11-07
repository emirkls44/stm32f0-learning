# 09 – HSI + PLL: selectable 16 / 32 / 48 MHz system clock

`SystemClockConfig(clock_freq)` configures the PLL from the HSI for one of three system clocks
and prints the result on USART2 (PA2 TX, 115200 8N1).

On the STM32F051 the PLL input is HSI / 2 = 4 MHz:

| Setting | PLL | SYSCLK = HCLK | APB1 | PCLK | Flash latency |
|---|---|---|---|---|---|
| `SYS_CLOCK_FREQ_16_MHZ` | ×4 | 16 MHz | /2 | 8 MHz | 1 |
| `SYS_CLOCK_FREQ_32_MHZ` | ×8 | 32 MHz | /4 | 8 MHz | 1 |
| `SYS_CLOCK_FREQ_48_MHZ` | ×12 | 48 MHz | /8 | 6 MHz | 1 |

UART is initialised after the clock change, so its baud rate register is computed from the new
PCLK.

Fixes compared with the first version: the APB prescaler used `RCC_SYSCLK_DIVx` (the AHB encoding),
which divided HCLK instead of PCLK — in the 48 MHz case the CPU actually ran at 6 MHz. The
`RCC_OscInitTypeDef`/`RCC_ClkInitTypeDef` structures are now zero-initialised, since HAL reads
fields that the code does not set.
