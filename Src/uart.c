#include "uart.h"

/*
 * USART2 is connected to the onboard ST-Link on the Nucleo-F411RE.
 * TX = PA2, RX = PA3, Alternate Function 7.
 * Data you send appears in CoolTerm on your Mac over USB.
 */

void uart_init(void) {
    /* 1. Enable clocks for GPIOA and USART2 */
    RCC_AHB1ENR |= RCC_GPIOA_EN;
    RCC_APB1ENR |= RCC_USART2_EN;

    /* 2. Configure PA2 (TX) as alternate function */
    GPIOA->MODER  &= ~(0x3U << (2 * 2));
    GPIOA->MODER  |=  (0x2U << (2 * 2));   /* AF mode */

    /* 3. Set alternate function 7 (USART2) on PA2 */
    GPIOA->AFR[0] &= ~(0xFU << (2 * 4));
    GPIOA->AFR[0] |=  (0x7U << (2 * 4));   /* AF7 = USART2 */

    /* 4. Set baud rate to 115200
     * BRR = fCK / baud = 16000000 / 115200 = 138.88 → 0x008B
     * fCK = 16MHz (default HSI clock on startup)
     */
    USART2->BRR = 0x008B;

    /* 5. Enable USART2, transmitter on */
    USART2->CR1 = (1U << 13) |   /* UE - USART enable */
                  (1U << 3);     /* TE - transmitter enable */
}

void uart_send_char(char c) {
    /* Wait until TX register is empty (TXE bit = bit 7 in SR) */
    while (!(USART2->SR & (1U << 7)));
    USART2->DR = (uint32_t)c;
}

void uart_send_string(const char *str) {
    while (*str) {
        uart_send_char(*str++);
    }
}
