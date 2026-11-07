# 06 – SHT3x over I2C with blocking HAL calls

Reads temperature and humidity from a Sensirion SHT3x once per second using the HAL I2C driver in
blocking mode.

| Item | Setting |
|---|---|
| I2C | I2C1, PB6 = SCL, PB7 = SDA (AF1, open-drain), 100 kHz (`Timing = 0x2000090E` for 8 MHz) |
| Sensor address | 0x44 (ADDR pin low) |
| Command | `0x2C06`: single shot, high repeatability, clock stretching enabled |

Sequence in the main loop:

1. `HAL_I2C_Master_Transmit()` sends the command
2. `HAL_Delay(15)` waits for the conversion (max. 15.5 ms at high repeatability)
3. `HAL_I2C_Master_Receive()` reads 6 bytes: T (2) + CRC, RH (2) + CRC
4. T = −45 + 175 · raw / 65535 °C, RH = 100 · raw / 65535 %
5. `HAL_Delay(1000)`

Results are in the globals `sicaklik` and `nem` (watch them in *Live Expressions*). The internal
pull-ups are enabled, but they are weak; external 4.7 kΩ pull-ups are recommended.

Limitations: the CPU is blocked during every delay, and the CRC bytes are read but not checked.
Example 07 removes the delays; the [SHT3x driver repository](https://github.com/emirkls44/STM32_I2C_TEMP_SHT3X_Modular)
is a register-level, interrupt-driven version with CRC checking and error recovery.
