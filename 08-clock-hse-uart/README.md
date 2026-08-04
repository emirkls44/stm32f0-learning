# STM32F0 Clock and UART Configuration

This repository contains a basic clock tree and UART configuration for the STM32F0DISCOVERY board using HAL.

## Hardware
* **MCU:** STM32F051R8
* **Board:** STM32F0DISCOVERY
* **Clock Source:** 8 MHz HSE (Bypass mode via ST-LINK MCO)

## Features
* System clock configured via HSE.
* AHB and APB1 prescalers configured to DIV2.
* Flash latency set to 0 wait states.
* UART2 initialized at 115200 baud rate (TX/RX).
* Interrupt-based UART reception sequence (terminates and echoes upon receiving `*`).

## Toolchain
* STM32CubeIDE
* STM32F0xx HAL Drivers
