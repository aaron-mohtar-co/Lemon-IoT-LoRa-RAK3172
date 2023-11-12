
/*
 * RAK3172 Power Management example
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

const char *pm_state_names[] = {"Active", "Runtime Idle", "Suspend to Idle", "Standby", "Suspend to RAM", "Suspend to Disk", "Soft-off", "Count" };

int main(void)
{
	uint8_t num_cpu_states;
	const struct pm_state_info *cpu_states;

	LOG_INF("Power Management Example");
	LOG_INF("Board: %s", CONFIG_BOARD);

	num_cpu_states = pm_state_cpu_get_all(0u, &cpu_states);
	LOG_INF("Number of Power Management States: %d", num_cpu_states);

	for (uint8_t i = 0U; i < num_cpu_states; i++) {
		LOG_INF("State %d: %s, substrate-id: %d", i, pm_state_names[cpu_states[i].state], cpu_states[i].substate_id);
		LOG_INF("          min-residency: %dus, exit-latency: %dus", cpu_states[i].min_residency_us, cpu_states[i].exit_latency_us);
	}

	while (1) {

		LOG_INF("Wakeup");
		k_sleep(K_SECONDS(10));

		//pm_state_force(0u, &(struct pm_state_info) {PM_STATE_RUNTIME_IDLE, 0, 0, 0});
		//pm_state_force(0u, &(struct pm_state_info) {PM_STATE_SUSPEND_TO_IDLE, 2, 0, 0});
		//pm_state_force(0u, &(struct pm_state_info) {PM_STATE_SUSPEND_TO_IDLE, 3, 0, 0});
		//pm_state_force(0u, &(struct pm_state_info) {PM_STATE_SOFT_OFF, 0, 0, 0});
		//pm_state_force(0u, &(struct pm_state_info) {PM_STATE_STANDBY, 0, 0, 0});
		//sys_poweroff();
	}
}
