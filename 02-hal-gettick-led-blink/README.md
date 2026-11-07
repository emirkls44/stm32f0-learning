# 02 – Non-blocking LED blink with `HAL_GetTick()`

Same LED (LD3, PC9) as example 01, but the main loop never waits: it compares `HAL_GetTick()`
with the time of the last toggle and toggles every 500 ms.

```c
if (HAL_GetTick() - son_zaman >= led_ms) { toggle; son_zaman = HAL_GetTick(); }
```

The unsigned subtraction stays correct when the 32-bit tick counter wraps around (after ~49 days).
