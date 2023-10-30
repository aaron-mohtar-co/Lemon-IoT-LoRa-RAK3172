
/*
 * RAK3172 Power Management example
 *
 * When CONFIG_PM=Y, lptim must be enabled. (Ref to board overlay)
 *
 */

#include <stdio.h>
#include <string.h>
#include <zephyr/device.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/pm/pm.h>
#include <zephyr/pm/policy.h>
#include <zephyr/logging/log.h>

#include <zephyr/sys/poweroff.h>

LOG_MODULE_REGISTER(main);

int main(void)
{
	LOG_INF("Power Management Example");
	LOG_INF("Board: %s", CONFIG_BOARD);

	while (1) {
		k_sleep(K_SECONDS(10));
		sys_poweroff();
		//pm_state_force(0u, &(struct pm_state_info){PM_STATE_SOFT_OFF, 1, 0});
	}
}
