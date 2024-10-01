# SPDX-License-Identifier: Apache-2.0

zephyr_syscall_header(${ZEPHYR_BASE}/include/zephyr/drivers/uart.h)

zephyr_library()
zephyr_library_sources_ifdef(CONFIG_UART_TIVA uart_tiva.c)


