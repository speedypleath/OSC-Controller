# OSC Controller

## Flash config file

Create a file named `config.json` in the data folder with the following content:

```json
{
    "wifi": {
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