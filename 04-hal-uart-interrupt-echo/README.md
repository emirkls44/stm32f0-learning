# STM32 UART Interrupt-Based Data Management (Echo)

This project implements non-blocking UART transmission and reception using the STM32 HAL library. The system manages data through a software buffer controlled by interrupt service routines (ISRs) and callback functions.

## Architectural Features
- **Interrupt Management:** Both data reception (RX) and transmission (TX) are handled entirely via interrupt service routines.
- **Buffering Logic:** Incoming data is stored in a `tx_buffer`. An asynchronous transmission queue is managed using `head` and `tail` pointers.
- **Low CPU Overhead:** The main execution loop (while(1)) remains unblocked during communication, allowing the MCU to perform other tasks simultaneously.

## Technical Parameters
- **Hardware:** STM32F051R8TX (Easily portable to other STM32 series)
- **Baudrate:** 115200
- **Configuration:** 8-bit Data, 1 Stop Bit, No Parity
- **Oversampling:** 16x
