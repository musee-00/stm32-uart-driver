#ifndef UART_H
#define UART_H

#include <stdint.h>

#define USART2_BASE   0x40004400UL
#define RCC_BASE      0x40023800UL
#define GPIOA_BASE    0x40020000UL

#define RCC_AHB1ENR  (*(volatile uint32_t *)(RCC_BASE + 0x30))
#define RCC_APB1ENR  (*(volatile uint32_t *)(RCC_BASE + 0x40))

#define RCC_GPIOA_EN  (1U << 0)
#define RCC_USART2_EN (1U << 17)

typedef struct {
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t BRR;
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t CR3;
    volatile uint32_t GTPR;
} USART_TypeDef;

typedef struct {
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFR[2];
} GPIO_TypeDef;

#define USART2  ((USART_TypeDef *) USART2_BASE)
#define GPIOA   ((GPIO_TypeDef *)  GPIOA_BASE)

void uart_init(void);
void uart_send_char(char c);
void uart_send_string(const char *str);

#endif
