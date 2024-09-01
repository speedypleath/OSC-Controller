# OSC Controller

## Schematic
![image](https://github.com/user-attachments/assets/203783e9-bc32-4cf2-8e85-2f88f5e9a770)

## Flash config file

Create a file named `config.json` in the data folder with the following content:

```json
{
    "network": {
        "ssid": "your_ssid",
        "password": "your_password"
    },
    "osc": {
        "host": ""
    }
}
```
From PlatformIO, you can use the `Build Filesystem Image` and `Upload Filesystem Image` tasks to upload the file to the ESP8266.

## Chose network using serial monitor
You can use the serial monitor to chose the network to connect to. The serial monitor will display the available networks and their index. To connect to a network, type the index of the network and press enter. If the network is secured, you will be asked to enter the password. The network will be saved in the flash memory of the ESP8266 and will be used on the next boot.


## Debugging

### Reset flash memory

```bash
python -m esptool --chip esp8266 --port /dev/cu.usbserial-220 erase_flash
```

> [!WARNING]
> You can't flash the ESP8266 while pin D8 is in use. You need to disconnect the pin before flashing the ESP8266.

### BluetoothSerial.h: No such file or directory

To fix this error, delete `SLIPEncodedBluetoothSerial` from the OSC library and rebuild the project.
