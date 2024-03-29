
/*
 * Class A LoRaWAN sample application
 *
 * Copyright (c) 2023 Aaron Mohtar & Co Pty Ltd
 * Copyright (c) 2023 Craig Peacock
 * Copyright (c) 2020 Manivannan Sadhasivam <mani@kernel.org>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <string.h>
#include <zephyr/device.h>
#include <zephyr/kernel.h>
#include <zephyr/lorawan/lorawan.h>
#include <zephyr/drivers/i2c.h>

#include <zephyr/drivers/flash.h>
#include <zephyr/storage/flash_map.h>
#include <zephyr/fs/nvs.h>

#include "shtc3.h"
#include "lorawan.h"

#define DELAY K_MINUTES(10)
#define NVS_PARTITION			storage_partition
#define NVS_PARTITION_DEVICE	FIXED_PARTITION_DEVICE(NVS_PARTITION)
#define NVS_PARTITION_OFFSET	FIXED_PARTITION_OFFSET(NVS_PARTITION)

#define NVS_DEVNONCE_ID 1

// Set NVS_CLEAR to wipe NVS partition on boot.
//#define NVS_CLEAR

#define LOG_LEVEL CONFIG_LOG_DBG_LEVEL
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(lorawan_class_a);

static void dl_callback(uint8_t port, bool data_pending, int16_t rssi, int8_t snr, uint8_t len, const uint8_t *data)
{
	LOG_INF("Port %d, Pending %d, RSSI %ddB, SNR %ddBm", port, data_pending, rssi, snr);
	if (data) {
		LOG_HEXDUMP_INF(data, len, "Payload: ");
	}
}

static void lorwan_datarate_changed(enum lorawan_datarate dr)
{
	uint8_t unused, max_size;

	lorawan_get_payload_sizes(&unused, &max_size);
	LOG_INF("New Datarate: DR_%d, Max Payload %d", dr, max_size);
}

int main(void)
{
	const struct device *lora_dev;
	const struct device *i2c_dev;
	struct lorawan_join_config join_cfg;

	uint8_t dev_eui[] = LORAWAN_DEV_EUI;
	uint8_t join_eui[] = LORAWAN_JOIN_EUI;
	uint8_t app_key[] = LORAWAN_APP_KEY;

	uint16_t payload[2];

	int ret;
	static struct nvs_fs fs;
	struct flash_pages_info info;
	ssize_t bytes_written;

	uint16_t dev_nonce = 0;

	printk("Zephyr LoRaWAN Node Example\nBoard: %s\n", CONFIG_BOARD);

	fs.flash_device = NVS_PARTITION_DEVICE;
	if (!device_is_ready(fs.flash_device)) {
		printk("Flash device %s is not ready\n", fs.flash_device->name);
		return(-1);
	}
	fs.offset = NVS_PARTITION_OFFSET;
	ret = flash_get_page_info_by_offs(fs.flash_device, fs.offset, &info);
	if (ret) {
		printk("Unable to get page info\n");
		return(-1);
	}
	fs.sector_size = info.size;
	fs.sector_count = 3U;

	ret = nvs_mount(&fs);
	if (ret) {
		printk("Flash Init failed\n");
		return(-1);
	}

#if NVS_CLEAR
	ret = nvs_clear(&fs);
	if (ret) {
		printk("Flash Clear failed\n");
		return(-1);
	} else {
		printk("Cleared NVS from flash\n");
	}
#endif

	ret = nvs_read(&fs, NVS_DEVNONCE_ID, &dev_nonce, sizeof(dev_nonce));
	if (ret > 0) { /* item was found, show it */
		printk("NVS: ID %d, DevNonce: %d\n", NVS_DEVNONCE_ID, dev_nonce);
	} else   {/* item was not found, add it */
		printk("NVS: No DevNonce found, resetting to %d\n", dev_nonce);
		bytes_written = nvs_write(&fs, NVS_DEVNONCE_ID, &dev_nonce, sizeof(dev_nonce));
		if (bytes_written < 0) {
			printf("NVS: Failed to write id %d (%d)\n", NVS_DEVNONCE_ID, bytes_written);
		} else {
			printf("NVS: Wrote %d bytes to id %d\n",bytes_written, NVS_DEVNONCE_ID);
		}
	}

	i2c_dev = DEVICE_DT_GET(DT_ALIAS(sensorbus));
	if (!i2c_dev) {
		printk("I2C: Device driver not found.\n");
		return(-1);
	} else {
		//i2c_configure(i2c_dev, I2C_SPEED_SET(I2C_SPEED_STANDARD));
	}

	lora_dev = DEVICE_DT_GET(DT_ALIAS(lora0));
	if (!device_is_ready(lora_dev)) {
		printk("%s: device not ready.", lora_dev->name);
		return(-1);
	}

	printk("Starting LoRaWAN stack.\n");
	ret = lorawan_start();
	if (ret < 0) {
		printk("lorawan_start failed: %d\n\n", ret);
		return(-1);
	}

	// Enable callbacks
	struct lorawan_downlink_cb downlink_cb = {
		.port = LW_RECV_PORT_ANY,
		.cb = dl_callback
	};

	lorawan_register_downlink_callback(&downlink_cb);
	lorawan_register_dr_changed_callback(lorwan_datarate_changed);

	join_cfg.mode = LORAWAN_ACT_OTAA;
	join_cfg.dev_eui = dev_eui;
	join_cfg.otaa.join_eui = join_eui;
	join_cfg.otaa.app_key = app_key;
	join_cfg.otaa.nwk_key = app_key;
	join_cfg.otaa.dev_nonce = dev_nonce;

	int i = 1;

	do {
		printk("Joining network using OTAA, dev nonce %d, attempt %d: ", dev_nonce, i++);
		ret = lorawan_join(&join_cfg);
		if (ret < 0) {
			if ((ret =-ETIMEDOUT)) {
				printf("Timed-out waiting for response.\n");
			} else {
				printk("Join failed (%d)\n", ret);
			}
		} else {
			printk("Join successful.\n");
		}

		// Increment DevNonce as per LoRaWAN 1.0.4 Spec.
		dev_nonce++;
		join_cfg.otaa.dev_nonce = dev_nonce;
		// Save value away in Non-Volatile Storage.
		bytes_written = nvs_write(&fs, NVS_DEVNONCE_ID, &dev_nonce, sizeof(dev_nonce));
		if (bytes_written < 0) {
			printf("NVS: Failed to write id %d (%d)\n", NVS_DEVNONCE_ID, bytes_written);
		} else {
			//printf("NVS: Wrote %d bytes to id %d\n",bytes_written, NVS_DEVNONCE_ID);
		}

		if (ret < 0) {
			// If failed, wait before re-trying.
			k_sleep(K_MSEC(5000));
		}

	} while (ret != 0);

	while (1) {

		shtc3_wakeup(i2c_dev);
		k_msleep(1);
		shtc3_GetTempAndHumidity(i2c_dev, &payload[0], &payload[1]);
		shtc3_sleep(i2c_dev);
		printk("Sending Temp %.02f RH %.01f\r\n", shtc3_convert_temp(payload[0]), shtc3_convert_humd(payload[1])); 
	
		ret = lorawan_send(2, (uint8_t *)&payload, sizeof(payload), LORAWAN_MSG_UNCONFIRMED);
		if (ret == -EAGAIN) {
			LOG_ERR("lorawan_send failed: %d. Continuing...", ret);
			k_sleep(DELAY);
			continue;
		} else if (ret < 0) {
			LOG_ERR("lorawan_send failed: %d", ret);
			return(-1);
		}

		LOG_INF("Data sent!");
		k_sleep(DELAY);
	}
}
