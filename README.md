# ESP32 USB HCI Bluetooth dongle

This project turns your generic ESP32 board into a natively supported USB Bluetooth dongle!

It works by running the ESP32 as an HCI controller and exposing its UART interface to the computer.

## Linux usage

Assuming you are running bluez (check `systemctl status bluetooth`, there should be something running),
connect your ESP32 board, flash this project via `idf.py`.

Then, check what tty the board is connected to, for instance `/dev/ttyUSB0`.

Lastly, you need to connect to the board, running `hciattach -s 921600 /dev/ttyUSB0 any 921600 noflow`.

You can check if the device was connected to by running `hciconfig`, there should be one device like this:

```
hciX:   Type: Primary  Bus: UART
        BD Address: C4:4F:33:11:3B:B3  ACL MTU: 1021:9  SCO MTU: 255:4
        UP RUNNING PSCAN ISCAN 
        RX bytes:138145 acl:90 sco:0 events:15057 errors:0
        TX bytes:12237259 acl:14383 sco:0 commands:223 errors:0
```
Look for `Bus: UART`.

From that point on, bluetooth should work in your OS.

When you want to stop using the thing, run `killall hciattach`.

If you reset your esp, it might get tangled up in the OS. In that case, run `sudo hciconfig hciX reset`.


## Windows usage

well, no idea, really...


Ideally you need an HCI driver that talks to a HCI controller through a COM port...

