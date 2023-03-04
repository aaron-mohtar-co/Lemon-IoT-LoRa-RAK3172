# Lemon IoT LoRa RAK3172 Examples

# LoRa

The LoRa folder contains example code to allow testing of LoRa radios (point to point communications). This is useful for validating your LoRa radio is working correctly before trying to connect to LoRaWAN networks.

When started, the app will listen for packets on the selected frequency/channel. When SW1 is pressed, will transmit a packet ('Hello') in ASCII. 

Please check the frequency/channel configuration prior to use and ensure you are transmitting on a permitted band for your country. 

```
*** Booting Zephyr OS build zephyr-v3.2.0-3920-g5787c69b9ce5 ***
LoRa Point to Point Communications Example
LoRa Device Configured
XMIT 6 bytes: 0x48 0x65 0x6c 0x6c 0x6f 0x00
XMIT 6 bytes: 0x48 0x65 0x6c 0x6c 0x6f 0x00
XMIT 6 bytes: 0x48 0x65 0x6c 0x6c 0x6f 0x00
XMIT 6 bytes: 0x48 0x65 0x6c 0x6c 0x6f 0x00
XMIT 6 bytes: 0x48 0x65 0x6c 0x6c 0x6f 0x00
RECV 6 bytes: 0x48 0x65 0x6c 0x6c 0x6f 0x00 RSSI = -75dBm, SNR = 8dBm
RECV 6 bytes: 0x48 0x65 0x6c 0x6c 0x6f 0x00 RSSI = -75dBm, SNR = 8dBm
RECV 6 bytes: 0x48 0x65 0x6c 0x6c 0x6f 0x00 RSSI = -75dBm, SNR = 9dBm
RECV 6 bytes: 0x48 0x65 0x6c 0x6c 0x6f 0x00 RSSI = -74dBm, SNR = 9dBm
RECV 6 bytes: 0x48 0x65 0x6c 0x6c 0x6f 0x00 RSSI = -74dBm, SNR = 9dBm
RECV 6 bytes: 0x48 0x65 0x6c 0x6c 0x6f 0x00 RSSI = -74dBm, SNR = 8dBm
```

## Building

Follow the Zephyr [Getting Started Guide](https://docs.zephyrproject.org/3.2.0/develop/getting_started/index.html) to install the Zephyr environment and build tools on your workstation. 

To build and flash your target using west use:

```
cd Examples\LoRa
west build -b lemon_iot_lora_rak3172
west flash 
```
