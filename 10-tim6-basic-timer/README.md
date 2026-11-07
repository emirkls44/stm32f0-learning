# STM32F0 Time Base Interrupt (TIM6)

This repository demonstrates how to configure a Basic Timer (TIM6) to generate periodic interrupts on the STM32F0 series using the HAL library. 

## Hardware
* **MCU:** STM32F051R8
* **Board:** STM32F0DISCOVERY

## Features
* System clock configured to 48 MHz via HSI and PLL.
* TIM6 configured with a prescaler of 48000 and a period of 999.
* Generates a precise 1-second (1 Hz) hardware interrupt.
* GPIO pin toggles state inside the `HAL_TIM_PeriodElapsedCallback` routine to verify timing.

## Toolchain
* STM32CubeIDE
* STM32F0xx HAL Drivers
