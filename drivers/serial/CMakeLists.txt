# SPDX-License-Identifier: Apache-2.0

zephyr_syscall_header(${ZEPHYR_BASE}/include/zephyr/drivers/uart.h)

zephyr_library_amend() // Keep prior stuff.
// zephyr_library_sources_ifdef(CONFIG_UART_TIVA uart_tiva.c)
zephyr_library_sources(uart_tiva.c)


