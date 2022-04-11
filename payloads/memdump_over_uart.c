/*
 * memdump_over_uart.c - S905D3 memory dump tool
 * $ aarch64-linux-gnu-gcc -O3 -nostdlib -Wl,--build-id=none -o memdump_over_uart.elf memdump_over_uart.c
 * $ aarch64-linux-gnu-objcopy -O binary -j .text memdump_over_uart.elf memdump_over_uart.bin
 *
 * derived from https://github.com/khadas/u-boot/blob/khadas-vims-pie/arch/arm/cpu/armv8/g12a/firmware/scp_task/uart.c
 *
 * Copyright (C) 2015 Amlogic, Inc. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#define P_WATCHDOG_RESET (volatile unsigned int *)0xFFD0F0DC
#define UART_PORT_CONS 0xFF803000
#define UART_STAT_MASK_TFIFO_FULL (1 << 21)
#define UART_STAT_MASK_TFIFO_EMPTY (1 << 22)
#define UART_WFIFO (0 << 2)
#define UART_CONTROL (2 << 2)
#define UART_STATUS (3 << 2)
#define P_UART(uart_base, reg) (uart_base + reg)
#define P_UART_WFIFO(uart_base) P_UART(uart_base, UART_WFIFO)
#define P_UART_MODE(uart_base) P_UART(uart_base, UART_MODE)
#define P_UART_CTRL(uart_base) P_UART(uart_base, UART_CTRL)
#define P_UART_STATUS(uart_base) P_UART(uart_base, UART_STATUS)

#define writel(v, addr) (*((volatile unsigned *)(addr)) = v)
#define readl(addr) (*((volatile unsigned *)(addr)))

static inline int uart_tx_isfull(void)
{
	return readl(P_UART_STATUS(UART_PORT_CONS)) &
		   UART_STAT_MASK_TFIFO_FULL;
}

static inline void uart_tx_flush(void)
{
	while (!(readl(P_UART_STATUS(UART_PORT_CONS)) &
			 UART_STAT_MASK_TFIFO_EMPTY))
		;
}

static inline int uart_putc(int c)
{
	if (c == '\n')
		uart_putc('\r');

	/* Wait until TX is not full */
	while (uart_tx_isfull())
		;

	writel((char)c, P_UART_WFIFO(UART_PORT_CONS));
	/*wait_uart_empty();*/
	uart_tx_flush();
	return c;
}

static inline void uart_put_hex(unsigned int data, unsigned bitlen)
{
	int i;
	unsigned char s;
	for (i = bitlen - 4; i >= 0; i -= 4)
	{
		if ((data >> i) == 0)
		{
			uart_putc(0x30);
			continue;
		}
		s = (data >> i) & 0xf;
		if (s < 10)
			uart_putc(0x30 + s);
		else
			uart_putc(0x61 + s - 10);
	}
}

static inline void watchdog_reset(void)
{
	*P_WATCHDOG_RESET = 0;
}
// linux command hex to bin : cat log.cap  | xxd -r -p > dump.bin
void _start()
{
	void (*_reset)() = (void *)0xFFFF0000;
	unsigned long mem_addr = 0x7bee1dc8;
	unsigned int size = 0x100;
	while (size--)
	{
		uart_put_hex(*(unsigned char *)(mem_addr++), 8);
		watchdog_reset();
	}
	_reset();
}
