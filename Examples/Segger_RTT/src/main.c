/*
 * Zephyr Hello World Boiler Plate Example
 * Demonstrates a basic Zephyr project with console support
 * 
 * Copyright (c) 2023 Aaron Mohtar & Co Pty Ltd
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <string.h>
#include <zephyr/device.h>
#include <zephyr/kernel.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(rtt);

int main(void)
{
	printk("Zephyr Hello World! Example \nBoard: %s\n", CONFIG_BOARD);

	while (1) {
		printk("Hello World\n");
		LOG_INF("Hello World");
		k_msleep(1000);
	}
}
