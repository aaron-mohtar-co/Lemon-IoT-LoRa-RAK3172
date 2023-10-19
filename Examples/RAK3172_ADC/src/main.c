/*
 * RAK3172 (STM32WLE5CC) ADC Example 
 * 
 * The STM32WL ADC consists of 12 external and 4 internal channels. 
 * 
 * The RAK3172 has the following ADC inputs broken out:
 * Channel 2  - P0.19 ADC0 'adc_in2_pb3'
 * Channel 3  - P0.20 ADC1 'adc_in3_pb4'
 * Channel 4  - P0.18 ADC2 'adc_in4_pb2'
 * Channel 6  - P0.10 ADC3 'adc_in6_pa10'
 * Channel 11 - P0.15 ADC4 'adc_in11_pa15'
 *  
 * Internal Inputs are:
 * Channel 12 - Temperature
 * Channel 13 - Volt Ref
 * Channel 14 - VBAT/3
 * Channel 15 - DAC Output
 * 
 * To connect the ADC to the I/O pin, they must be defined in the pinctrl property of the ADC node:
 * pinctrl-0 = <&adc_in2_pb3>, <&adc_in3_pb4>, <&adc_in4_pb2>, <&adc_in6_pa10>, <&adc_in11_pa15>;
 * 
 * Copyright (c) 2023 Aaron Mohtar & Co Pty Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <string.h>
#include <zephyr/device.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/adc.h>

#define ADC_CHANNEL		2

void main(void)
{
	const struct device *dev_adc;
	int err;
	int16_t buf;

	static const struct adc_channel_cfg channel_cfg = {
		.gain = ADC_GAIN_1,
		.reference = ADC_REF_INTERNAL,
		.acquisition_time = ADC_ACQ_TIME_DEFAULT,
		.channel_id = ADC_CHANNEL
	};

	const struct adc_sequence adc_sequence = {
		.channels = BIT(ADC_CHANNEL),
		.calibrate = 1,
		.buffer = &buf,
		.buffer_size = sizeof(buf),
		.resolution = 12,
		.oversampling = 5
	};

	printk("Lemon IoT RAK3172 ADC Example\nBoard: %s\n", CONFIG_BOARD);

	dev_adc = DEVICE_DT_GET(DT_ALIAS(adcperiph));
	if (!device_is_ready(dev_adc)) {
		 printk("ADC: Device binding failed.\n");
	}	

	err = adc_channel_setup(dev_adc, &channel_cfg);
	if (err < 0) {
		printk("Could not setup ADC channel (%d)\n", err);
		return;
	}

	while(1) {
		err = adc_read(dev_adc, &adc_sequence);
		if (err < 0) {
			printk("Could not read ADC (%d)\n", err);
			continue;
		} else {
			printk("Raw: %d\n", buf);
		}
	}
}
