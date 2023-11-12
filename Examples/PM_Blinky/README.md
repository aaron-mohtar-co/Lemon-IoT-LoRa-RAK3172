# STM32 PM Blinky

This is a copy of the [STM32 Power Management Blinky](https://github.com/zephyrproject-rtos/zephyr/tree/main/samples/boards/stm32/power_mgmt/blinky) source code found in the Zephyr Repo. 

The project is an exact copy, with the addition of a lemon_iot_lora_rak3172.overlay file used to disable the default usart1 (and enable lpuart1).

This example blinks an LED (led0 alias) every 2000mS. During the LED off period, power consumption should be close to STOP2. During the on period, most of the power consumption will be LED. On the Lemon IoT LoRa board, the led0 alias points to the red LED.

## Stop 2

The ballpark STOP 2 target curent consumption is 1uA for the STM32WLE5CC. The following tables are extracted from the STM32WLE5xx STM32WLE4xx Datasheet, DS13105 Rev 12.

![Table 25: Main Performances at VDD = 3V](https://github.com/aaron-mohtar-co/Lemon-IoT-LoRa-RAK3172/blob/main/Examples/PM_Blinky/img/main_performances.png)

As you can see, this value will vary due to supply voltage, temperature and crystal. (On the Lemon-IoT-LoRa-RAK3172, we use the external 32.768kHz Crystal - LSE) 

![Table 43. Current consumption in Stop 2 mode](https://github.com/aaron-mohtar-co/Lemon-IoT-LoRa-RAK3172/blob/main/Examples/PM_Blinky/img/Stop2_detailed.png)

## Actual Measurements




