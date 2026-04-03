#include <stdint.h>
#include "uart.h"

static void delay(volatile uint32_t count) {
    while (count--);
}

int main(void) {
    uart_init();
    uart_send_string("STM32 UART driver running!\r\n");

    while (1) {
        uart_send_string("Hello from bare-metal!\r\n");
        delay(500000);
    }
}
