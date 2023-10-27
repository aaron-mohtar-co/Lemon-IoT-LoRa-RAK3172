
/*
 * RAK3172 Brown Out Reset Example
 *
 * https://www.st.com/resource/en/user_manual/um2642-description-of-stm32wl-hal-and-lowlayer-drivers-stmicroelectronics.pdf
 * D:\Zephyr\zephyrproject\modules\hal\stm32\stm32cube\stm32wlxx\drivers\include
 */

#include <stdio.h>
#include <string.h>
#include <zephyr/device.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/hwinfo.h>
#include <soc.h>

LOG_MODULE_REGISTER(main);

void print_reset_cause(void)
{
	int ret;
	uint32_t cause;

	ret = hwinfo_get_reset_cause(&cause);
	if (ret == 0) {
		LOG_INF("Reset: 0x%04X", cause);
		if (cause & RESET_BROWNOUT) 	LOG_INF("Reset: Brownout");
		if (cause & RESET_PIN)			LOG_INF("Reset: Reset Pin");
		if (cause & RESET_POR)			LOG_INF("Reset: Power-on Reset");
		if (cause & RESET_SOFTWARE)		LOG_INF("Reset: Software Reset");
		if (cause & RESET_USER)			LOG_INF("Reset: User Reset");
		if (cause & RESET_WATCHDOG)		LOG_INF("Reset: Watch Dog");

		ret = hwinfo_clear_reset_cause();
	}
}

int check_brown_out_reset()
{
	FLASH_OBProgramInitTypeDef OptionBytes;
	HAL_FLASHEx_OBGetConfig(&OptionBytes);

	LOG_INF("Option Bytes = 0x%04X", OptionBytes.UserConfig);
	LOG_INF("BOR_LEV = 0x%X", (unsigned int)(OptionBytes.UserConfig & OB_USER_BOR_LEV));

	if ((OptionBytes.UserConfig & OB_USER_BOR_LEV) != OB_BOR_LEVEL_3)
	{
		LOG_INF("Brown out reset not set to Level 3 (approximately 2.5V)");

		HAL_FLASH_Unlock();
		HAL_FLASH_OB_Unlock();

		OptionBytes.OptionType = OPTIONBYTE_USER;
		OptionBytes.UserType = OB_USER_BOR_LEV;
		OptionBytes.UserConfig = OB_BOR_LEVEL_3;

		if (HAL_FLASHEx_OBProgram(&OptionBytes) != HAL_OK)
		{
			HAL_FLASH_OB_Lock();
			HAL_FLASH_Lock();
			return HAL_ERROR;
		}

		HAL_FLASH_OB_Launch();

		/* We should not make it past the Launch, so lock
		 * flash memory and return an error from function
		 */
		HAL_FLASH_OB_Lock();
		HAL_FLASH_Lock();
	}

	return HAL_OK;
}

int main(void)
{
	LOG_INF("Power Management Example");
	LOG_INF("Board: %s", CONFIG_BOARD);

	print_reset_cause();

	check_brown_out_reset();

	while (1) {
		LOG_INF("Hello World");
		k_sleep(K_SECONDS(1));
	}
}
