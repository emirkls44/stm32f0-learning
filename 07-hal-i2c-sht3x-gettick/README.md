# 07 – SHT3x over I2C, scheduled with `HAL_GetTick()`

Same sensor and wiring as example 06, but the `HAL_Delay()` calls are replaced by a two-step
schedule based on `HAL_GetTick()`, so the main loop keeps running between the steps:

1. 100 ms after the last read: send the measurement command `0x2C06`
2. 100 ms later: read the 6-byte result and convert it

Results are in `temperature` and `humidity`. The I2C transfers themselves are still blocking HAL
calls (about 0.3 ms for the command, 0.7 ms for the read at 100 kHz).
