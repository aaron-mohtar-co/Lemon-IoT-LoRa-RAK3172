# Lemon-IoT-LoRa-RAK3172 Power Management

The Lemon IoT LoRa RAK3172 Device Tree includes a global stm32wle5Xc.dtsi file containing power management states for the STM32WLE5xC series of SoC.

```
/dts-v1/;
#include <st/wl/stm32wle5Xc.dtsi>
#include <st/wl/stm32wle5jcix-pinctrl.dtsi>
#include "lemon_iot_lora_rak3172-pinctrl.dtsi"
```

These global files can be found in the [zephyr\dts\arm\st\wl](https://github.com/zephyrproject-rtos/zephyr/tree/main/dts/arm/st/wl) folder and include

```
	cpus {
		#address-cells = <1>;
		#size-cells = <0>;

		cpu0: cpu@0 {
			device_type = "cpu";
			compatible = "arm,cortex-m4f";
			reg = <0>;
			cpu-power-states = <&stop0 &stop1 &stop2>;
		};

		power-states {
			stop0: state0 {
				compatible = "zephyr,power-state";
				power-state-name = "suspend-to-idle";
				substate-id = <1>;
				min-residency-us = <100>;
			};
			stop1: state1 {
				compatible = "zephyr,power-state";
				power-state-name = "suspend-to-idle";
				substate-id = <2>;
				min-residency-us = <500>;
			};
			stop2: state2 {
				compatible = "zephyr,power-state";
				power-state-name = "suspend-to-idle";
				substate-id = <3>;
				min-residency-us = <900>;
			};
		};

```
This example starts by printing out the power management states to validate they are enabled:

```
*** Booting Zephyr OS build zephyr-v3.5.0-1329-g26f30db8adab ***
[00:00:00.000,000] <inf> main: Power Management Example
[00:00:00.000,000] <inf> main: Board: lemon_iot_lora_rak3172
[00:00:00.000,000] <inf> main: Number of Power Management States: 3
[00:00:00.000,000] <inf> main: State 0: Suspend to Idle, substrate-id: 1
[00:00:00.000,000] <inf> main:           min-residency: 100us, exit-latency: 0us
[00:00:00.000,000] <inf> main: State 1: Suspend to Idle, substrate-id: 2
[00:00:00.000,000] <inf> main:           min-residency: 500us, exit-latency: 0us
[00:00:00.000,000] <inf> main: State 2: Suspend to Idle, substrate-id: 3
[00:00:00.000,000] <inf> main:           min-residency: 900us, exit-latency: 0us
```
Then the code enters a loop, printing "Wakeup" on the console, followed by sleeping for 10 seconds. Monitoring the device's power consumption should show it entering a low power state.

## Notes

The Lemon IoT LoRa RAK3172 module uses the standard usart1, however this may cause issues with the CPU entering or exiting power saving states. We use a board overlay file to reassign the console to the low power uart1 using PA2 (TX) and PA3 (RX).
