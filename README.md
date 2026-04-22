# Bare-metal UART Driver — STM32F411RE

Register-level UART driver with zero HAL dependencies. Sends serial data from STM32 Nucleo to a Mac over USB using USART2.

---

## What It Does

- Initialises USART2 at 115200 baud using direct register writes
- Configures PA2 (TX) as Alternate Function 7
- Transmits strings from STM32 to a serial monitor (CoolTerm / screen)

---

## Hardware

- STM32 Nucleo F411RE
- USB cable (ST-Link onboard — no extra hardware needed)

| Signal | Pin |
|--------|-----|
| UART TX | PA2 |
| UART RX | PA3 |

---

## How It Works

**Clock setup**
```c
RCC_AHB1ENR |= RCC_GPIOA_EN;   // enable GPIOA clock
RCC_APB1ENR |= RCC_USART2_EN;  // enable USART2 clock
```

**GPIO — PA2 as AF7**
```c
GPIOA->MODER |= (0x2U << (2 * 2));   // alternate function mode
GPIOA->AFR[0] |= (0x7U << (2 * 4)); // AF7 = USART2
```

**Baud rate — 115200**
```c
USART2->BRR = 0x008B; // 16MHz HSI / 115200
```

**Enable USART**
```c
USART2->CR1 = (1U << 13) | (1U << 3); // UE + TE
```

---

## File Structure

| File | Purpose |
|------|---------|
| `Src/main.c` | Entry point — calls uart_init and sends strings in a loop |
| `Src/uart.c` | UART driver implementation |
| `Inc/uart.h` | Register definitions and function declarations |

---

## Build & Flash

Open in **STM32CubeIDE**, build with `Ctrl+B`, flash with `Run`.

To view output on Mac:
```bash
screen /dev/tty.usbmodem* 115200
```

---

## Stack

**C · STM32F411RE · ARM Cortex-M4 · Bare-metal · No HAL**
