/*
 * Copyright (c) 2015 Intel Corporation.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file Board config file
 */

#include <zephyr/device.h>
#include <zephyr/init.h>

#include <zephyr/kernel.h>

#include "soc.h"

#ifdef CONFIG_UART_STELLARIS
#include <zephyr/drivers/uart.h>

// Addresses from TM4C129XNCZAD data sheet.
#define RCGCGPIO (*((volatile uint32_t *)0x400FE608))
#define RCGCUART (*((volatile uint32_t *)0x400FE618))


#define SCGCGPIO (*((volatile uint32_t *)0x400FE708))
#define SCGCUART (*((volatile uint32_t *)0x400FE718))

// Clock Enables.
#define RCGCGPIO_GPIOA_EN 0x00000001
#define SCGCGPIO_GPIOA_EN 0x00000001


#define RCGCUART_UART0_EN 0x00000001
#define RCGCUART_UART1_EN 0x00000002
#define RCGCUART_UART2_EN 0x00000004
#define RCGCUART_UART3_EN 0x00000008
#define RCGCUART_UART4_EN 0x00000010
#define RCGCUART_UART5_EN 0x00000020
#define RCGCUART_UART6_EN 0x00000040
#define RCGCUART_UART7_EN 0x00000080

// Sleep mode clock gating.   UARTs should run 
// in sleep mode by default.
#define SCGCUART_UART0_EN 0x00000001
#define SCGCUART_UART1_EN 0x00000002
#define SCGCUART_UART2_EN 0x00000004
#define SCGCUART_UART3_EN 0x00000008
#define SCGCUART_UART4_EN 0x00000010
#define SCGCUART_UART5_EN 0x00000020
#define SCGCUART_UART6_EN 0x00000040
#define SCGCUART_UART7_EN 0x00000080

static int uart_tiva_init(void)
{
#ifdef CONFIG_UART_STELLARIS_PORT_0

// CHEATING FOR BRING-UP.  Assume that we're on PA0/PA1 
// BRD = BRDI + BRDF = UARTSysClk / (ClkDiv * Baud Rate) 
//  BRD = BRDI + BRDF = 16_000_000 / (16 * 115200) 
//  BRD = BRDI + BRDF = 1_000_000 / ( 115200) = 8.6 
// BRDF = 44;

	RCGCGPIO |= RCGCGPIO_GPIOA_EN;
	SCGCGPIO |= SCGCGPIO_GPIOA_EN;

	RCGCUART |= RCGCUART_UART0_EN;
	SCGCUART |= SCGCUART_UART0_EN;

    // This is ugly and strange.  Do it anyway.  For now.

    *((uint32_t *) 0x40058420) |= 3; // AFSEL UART IOs.
    *((uint32_t *) 0x4005851c) |= 3; // Digital Enable
    *((uint32_t *) 0x4005852c)  = (1<<4 | 1<<0); // Port Selections.
    *((uint32_t *) 0x40058400) |= 2; // PA1 is an output. 

    *((uint32_t *) 0x4000cfc8) = 5; // UART Alternate Clock Control

#endif

#ifdef CONFIG_UART_STELLARIS_PORT_1
	RCGCUART |= RCGCUART_UART1_EN;
	SCGCUART |= SCGCUART_UART1_EN;
#endif

#ifdef CONFIG_UART_STELLARIS_PORT_2
	RCGCUART |= RCGCUART_UART2_EN;
	SCGCUART |= SCGCUART_UART2_EN;
#endif

#ifdef CONFIG_UART_STELLARIS_PORT_3
	RCGCUART |= RCGCUART_UART3_EN;
	SCGCUART |= SCGCUART_UART4_EN;
#endif

#ifdef CONFIG_UART_STELLARIS_PORT_4
	RCGCUART |= RCGCUART_UART4_EN;
	SCGCUART |= SCGCUART_UART4_EN;
#endif

#ifdef CONFIG_UART_STELLARIS_PORT_5
	RCGCUART |= RCGCUART_UART5_EN;
	SCGCUART |= SCGCUART_UART5_EN;
#endif

#ifdef CONFIG_UART_STELLARIS_PORT_6
	RCGCUART |= RCGCUART_UART6_EN;
	SCGCUART |= SCGCUART_UART6_EN;
#endif

#ifdef CONFIG_UART_STELLARIS_PORT_7
	RCGCUART |= RCGCUART_UART7_EN;
	SCGCUART |= SCGCUART_UART7_EN;
#endif

	return 0;
}

SYS_INIT(uart_tiva_init, EARLY, CONFIG_KERNEL_INIT_PRIORITY_DEVICE);

#endif /* CONFIG_UART_STELLARIS */

// FIXME.  This is definately wrong.  The Tiva has a different 
// Ethernet IP.
#ifdef CONFIG_ETH_STELLARIS

#define RCGC2 (*((volatile uint32_t *)0x400FE108))

#define RCGC2_PHY_EN   0x40000000
#define RCGC2_EMAC_EN  0x10000000

static int eth_stellaris_init(void)
{
	// RCGC2 |= (RCGC2_PHY_EN | RCGC2_EMAC_EN);
	return 0;
}

SYS_INIT(eth_stellaris_init, PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEVICE);

#endif /* CONFIG_ETH_STELLARIS */
