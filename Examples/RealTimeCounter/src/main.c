/*
 * RAK3172 (STM32WLE5CC) Real Time Counter (RTC) Example
 *
 * Zephyr has support for Real-time clock and Real-time counter. The clock provides a broken-down 
 * time format, while the counter provides a low power counter that can be used to track time
 * https://docs.zephyrproject.org/latest/hardware/peripherals/rtc.html
 *
 * For STM32 RTC bindings, see:
 * https://docs.zephyrproject.org/latest/reference/devicetree/bindings/rtc/st%2Cstm32-rtc.html#dtbinding-st-stm32-rtc
 * 
 * https://github.com/zephyrproject-rtos/zephyr/issues/56599
 * 
 * Copyright (c) 2023 Aaron Mohtar & Co Pty Ltd
 * Copyright (c) 2019 Linaro Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <string.h>
#include <zephyr/device.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/counter.h>

struct counter_alarm_cfg alarm_cfg;

#define ALARM_CHANNEL_ID 0

static void test_counter_interrupt_fn(const struct device *counter_dev,
				uint8_t chan_id, uint32_t ticks,
				void *user_data)
{
	printk("Alarm\n");
}

int main(void)
{
	const struct device *const counter_dev = DEVICE_DT_GET(DT_INST(0, st_stm32_rtc));
	int err;

	printk("Lemon IoT RAK3172 Real Time Clock Example\nBoard: %s\n", CONFIG_BOARD);

	if (!device_is_ready(counter_dev)) {
		printk("device not ready.\n");
		return(-1);
	}

	counter_start(counter_dev);

	alarm_cfg.flags = 0;
	alarm_cfg.ticks = counter_us_to_ticks(counter_dev, 20*1000000);
	alarm_cfg.callback = test_counter_interrupt_fn;
	alarm_cfg.user_data = &alarm_cfg;

	err = counter_set_channel_alarm(counter_dev, ALARM_CHANNEL_ID, &alarm_cfg);
	printk("Set alarm in %u sec (%u ticks)\n",
		(uint32_t)(counter_ticks_to_us(counter_dev,
		alarm_cfg.ticks) / USEC_PER_SEC),
		alarm_cfg.ticks);

	if (-EINVAL == err) {
		printk("Alarm settings invalid\n");
	} else if (-ENOTSUP == err) {
		printk("Alarm setting request not supported\n");
	} else if (err != 0) {
		printk("Error\n");
	}

	pm_system_suspend();

	while (1) {
		k_sleep(K_FOREVER);
	}
}
