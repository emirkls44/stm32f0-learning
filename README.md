# STM32F0 Learning Examples

Small exercises I wrote while learning the STM32F0 (January – August 2026), from blinking an LED to
interrupts, I2C and clock configuration. They are kept as a record of the progression; each folder
is a standalone STM32CubeIDE project for the **STM32F0DISCOVERY** (STM32F051R8).

| # | Example | Topics |
|---|---|---|
| 01 | [LED blink with `HAL_Delay()`](01-hal-delay-led-blink) | CubeMX project structure, GPIO |
| 02 | [LED blink with `HAL_GetTick()`](02-hal-gettick-led-blink) | non-blocking timing |
| 03 | [Register-level GPIO + UART](03-register-uart-led) | RCC/GPIO/USART registers, polling TX |
| 04 | [HAL UART interrupt echo](04-hal-uart-interrupt-echo) | `HAL_UART_Receive_IT`, TX/RX callbacks |
| 05 | [Register-level UART interrupts](05-register-uart-interrupt) | `USART1_IRQHandler`, RXNE/TXE, framing |
| 06 | [SHT3x over I2C, blocking](06-hal-i2c-sht3x-blocking) | HAL I2C, sensor datasheet |
| 07 | [SHT3x over I2C, tick-scheduled](07-hal-i2c-sht3x-gettick) | removing blocking delays |
| 08 | [HSE clock + UART](08-clock-hse-uart) | clock tree, prescalers, UART receive IT |
| 09 | [HSI + PLL 16/32/48 MHz](09-clock-hsi-pll) | PLL, flash latency, APB prescaler |
| 10 | [TIM6 basic timer interrupt](10-tim6-basic-timer) | timer prescaler/period, NVIC |

Later, larger projects built on these:

- [Motor control firmware (STM32F051)](https://github.com/emirkls44/industrial_motor_control_stm32)
- [ESP32 MQTT gateway](https://github.com/emirkls44/industrial-motor-control-esp32-gateway)
- [SHT3x driver with register-level, interrupt-driven I2C](https://github.com/emirkls44/STM32_I2C_TEMP_SHT3X_Modular)

## Building

Each folder can be imported into STM32CubeIDE (*File → Import → Existing Projects into Workspace*).
To build all examples from the command line:

```sh
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=cmake/arm-none-eabi.cmake
cmake --build build
```

CI builds every example on each push.

## History

The examples used to be separate repositories. They were merged here with their full commit
history (`git log -- 05-register-uart-interrupt` shows that example's history). Build output that
had been committed by mistake was removed from the history, and bugs found in a later review were
fixed in separate commits (see each folder's README).
