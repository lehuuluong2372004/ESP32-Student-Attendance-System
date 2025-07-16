# ESP32 Student Attendance System

Digital attendance system using ESP32 with keypad input and cloud integration.

## Features

- Input student ID via 4x4 keypad (max 8 characters)
- Display on 128x64 OLED screen
- Send data to Google Sheets via WiFi
- Confirm with `#` key, clear with `*` key

## Hardware Required

- ESP32 DevKit C V4
- SSD1306 OLED Display (128x64, I2C)
- 4x4 Membrane Keypad
- Jumper wires

## Wiring

### OLED SSD1306
- **VCC** → ESP32 **5V**
- **GND** → ESP32 **GND**
- **SDA** → ESP32 **GPIO 4**
- **SCL** → ESP32 **GPIO 5**

### 4x4 Keypad
- **R1-R4** → ESP32 **GPIO 13, 12, 14, 27**
- **C1-C4** → ESP32 **GPIO 26, 25, 33, 32**

## Setup

1. Install required libraries:
   - `Keypad` by Mark Stanley
   - `Adafruit GFX Library`
   - `Adafruit SSD1306`

2. Configure WiFi credentials in `main.cpp`

3. Set up Google Sheets with Apps Script and update `URLsheet`

4. Upload code to ESP32

## Usage

- **0-9, A-D**: Input student ID
- **#**: Confirm and send
- **\***: Clear input

## Libraries

```cpp
#include <Keypad.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <HTTPClient.h>
```

## Simulation

Test on Wokwi using the provided `diagram.json` file.

## Author

**Le Huu Luong**

## License

MIT License
