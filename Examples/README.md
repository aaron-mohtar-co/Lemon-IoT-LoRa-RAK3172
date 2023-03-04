# Lemon IoT LoRa RAK3172 Examples

# LoRaWAN

The LoRaWAN folder contains example code to connect to a LoRaWAN Network and transmit temperature and humidity values from a Sensirion SHTC3.

LoRaWAN Device EUI, Join EUI and Application Key should be entered into the lorawan.h file prior to compiling. 

The prj.conf file includes statements to enable your region (Frequency):

```
#LORAMAC_REGION_AS923=y
LORAMAC_REGION_AU915=y
#LORAMAC_REGION_CN470=y
#LORAMAC_REGION_CN779=y
#LORAMAC_REGION_EU433=y
#LORAMAC_REGION_EU868=y
#LORAMAC_REGION_KR920=y
#LORAMAC_REGION_IN865=y
#LORAMAC_REGION_US915=y
#LORAMAC_REGION_RU864=y
```

The I2C SHTC3 sensor can be connected to the I2C2 port (SCL/PA12, SDA/PA11).

The example stores the DevNonce in NVS (Non-volatile Storage) as per LoRaWAN 1.0.4 Specifications.

## Example output

```
*** Booting Zephyr OS build zephyr-v3.2.0-3920-g5787c69b9ce5 ***
Zephyr LoRaWAN Node Example
Board: lemon_iot_lora_rak3172
NVS: ID 1, DevNonce: 8
Starting LoRaWAN stack.
Joining network using OTAA, dev nonce 8, attempt 1: Timed-out waiting for response.
Joining network using OTAA, dev nonce 9, attempt 2: Join successful.
Sending Temp 27.77 RH 50.1
Sending Temp 27.47 RH 51.2
```

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

# Building the examples

Follow the Zephyr [Getting Started Guide](https://docs.zephyrproject.org/3.2.0/develop/getting_started/index.html) to install the Zephyr environment and build tools on your workstation. 

To build and flash your target using west use:

```
cd Examples\LoRaWAN
west build -b lemon_iot_lora_rak3172
west flash 
```
