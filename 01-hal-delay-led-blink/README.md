# 01 – LED blink with `HAL_Delay()`

First STM32CubeMX/HAL project: toggles the green LED (LD3, PC9) every second with a blocking
`HAL_Delay(1000)`.

- Board: STM32F0DISCOVERY (STM32F051R8), 8 MHz HSI
- Shows the CubeMX project layout (`USER CODE` sections, `MX_GPIO_Init()`)
- Limitation: `HAL_Delay()` blocks the CPU; example 02 removes that.
