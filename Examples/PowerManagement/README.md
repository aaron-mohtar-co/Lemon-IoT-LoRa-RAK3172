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