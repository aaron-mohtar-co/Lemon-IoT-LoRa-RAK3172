# Segger RTT

Segger RTT (Real Time Transfer) can provide a console over the SWD programming connection. This is useful if you are running out of UART ports for the console or don't have a UART port provisioned on your board.

To enable the RTT console, enable CONFIG_USE_SEGGER_RTT & CONFIG_RTT_CONSOLE in your prj.conf file. You may also want to disable the console on the UART, if you are using it for other purposes.

```
CONFIG_USE_SEGGER_RTT=y
CONFIG_UART_CONSOLE=n
CONFIG_RTT_CONSOLE=y
```

On your PC, use J-Link RTT Viewer to connect to your RAK3172 (STM32WLE5CC) Target. If using Zephyr RTOS, it may not work with default settings (Auto Detection) as it cannot find the [RTT Control Block](https://wiki.segger.com/RTT#How_RTT_works) in the location the tools expect.   

If this is the case, change the search range to 0x20000000 0x3000. 

<p align="center"><img src="https://github.com/aaron-mohtar-co/Lemon-IoT-LoRa-RAK3172/blob/main/Examples/Segger_RTT/RTT_Viewer.png" width=40% height=40%></p>



