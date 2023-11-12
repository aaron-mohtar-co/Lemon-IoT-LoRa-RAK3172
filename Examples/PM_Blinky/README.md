# STM32 PM Blinky

This is a copy of the [STM32 Power Management Blinky](https://github.com/zephyrproject-rtos/zephyr/tree/main/samples/boards/stm32/power_mgmt/blinky) source code found in the Zephyr Repo. 

The project is an exact copy, with the addition of a lemon_iot_lora_rak3172.overlay file used to disable the default usart1 (and enable lpuart1).

This example blinks an LED (led0 alias) every 2000mS. During the LED off period, power consumption should be close to STOP2. During the on period, most of the power consumption will be LED. 
