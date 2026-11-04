# Sensor Testing Guide (Arduino Uno)

Notes and pinouts for testing the workshop sensors:
1. **VL53L0X** — Laser Time-of-Flight (ToF) distance sensor
2. **MFRC522** — 13.56 MHz RFID reader
3. **MPU6050** — 6-axis accelerometer & gyroscope
4. **HC-SR04** — Ultrasonic sonar distance sensor
5. **Photoresistor Module (JZK LM393)** — Light intensity / brightness detector
6. **KY-023 Joystick** — 2-axis analog thumbstick with button

---

## Setup Notes

- **Installing libraries:** In the Arduino IDE, go to `Sketch` -> `Include Library` -> `Manage Libraries...`, search for the library name, and click Install (click "Install All" if it asks for dependencies like `Adafruit BusIO` or `Adafruit Unified Sensor`).
- **Serial Monitor:** All sketches use **`115200` baud**. Open `Tools` -> `Serial Monitor` (`Ctrl+Shift+M`) and set the baud rate dropdown in the bottom-right corner to `115200` (if left on `9600`, the text will look scrambled).

---

## 1. VL53L0X (Laser Distance Sensor)

Measures distance from ~30 mm to 2000 mm (3 cm to 2 m) over I2C.
*(Note: If there is a small yellow/clear protective film over the sensor lens, peel it off first).*

**Library needed:** `Adafruit_VL53L0X` by Adafruit

**Wiring (I2C):**

| VL53L0X Pin | Arduino Uno      | Notes |
| :--- | :--- | :--- |
| VIN / VCC | 5V (or 3.3V) | Power |
| GND | GND | Ground |
| SDA | A4 | I2C Data |
| SCL | A5 | I2C Clock |
| XSHUT / GPIO1 | Not connected | Optional pins |

**Sketch:** `VL53L0X_test/VL53L0X_test.ino`
Upload and open Serial Monitor at `115200` baud to see distance in `mm` and `cm`.

---

## 2. MFRC522 (RFID Reader)

Reads the UID of 13.56 MHz RFID cards and key fobs over SPI.

**IMPORTANT:** Power this board with **3.3V only**. Do not connect VCC to 5V as the chip is not 5V-power tolerant.

**Library needed:** `MFRC522` by GithubCommunity

**Wiring (SPI):**

| MFRC522 Pin | Arduino Uno      | Notes |
| :--- | :--- | :--- |
| 3.3V (VCC) | **3.3V** | **3.3V only (do NOT use 5V)** |
| RST | Pin 9 | Reset |
| GND | GND | Ground |
| IRQ | Not connected | Unused |
| MISO | Pin 12 | SPI MISO |
| MOSI | Pin 11 | SPI MOSI |
| SCK | Pin 13 | SPI Clock |
| SDA (SS) | Pin 10 | SPI Chip Select |

**Sketch:** `MFRC522_test/MFRC522_test.ino`
On startup it prints the MFRC522 firmware version (usually `0x91` or `0x92`). Tap a card or fob against the reader to print its hex UID and PICC card type.

---

## 3. MPU6050 (Accelerometer & Gyroscope)

6-axis IMU over I2C. Outputs 3-axis acceleration in m/s² (when sitting flat on a desk, Z reads ~9.8 m/s² from gravity), 3-axis gyro rotation rate in rad/s, and chip temperature in °C.

**Library needed:** `Adafruit MPU6050` by Adafruit (along with `Adafruit Unified Sensor` and `Adafruit BusIO`)

**Wiring (I2C):**

| MPU6050 Pin | Arduino Uno      | Notes |
| :--- | :--- | :--- |
| VCC | 5V (or 3.3V) | Power |
| GND | GND | Ground |
| SCL | A5 | I2C Clock |
| SDA | A4 | I2C Data |
| XDA / XCL / AD0 / INT | Not connected | Auxiliary / address / interrupt pins |

**Sketch:** `MPU6050_test/MPU6050_test.ino`
Upload and tilt/rotate the board to check the X, Y, Z accel and gyro readings in the Serial Monitor.

---

## 4. HC-SR04 Ultrasonic Sonar

Measures distance (~2 cm to 400 cm) by sending a 10 us pulse on `TRIG` and timing the echo return on `ECHO` with `pulseIn()`.

**Library needed:** None (uses built-in Arduino functions)

**Wiring:**

| HC-SR04 Pin | Arduino Uno      | Notes |
| :--- | :--- | :--- |
| VCC | 5V | Needs 5V |
| GND | GND | Ground |
| TRIG | Pin 9 | Trigger input |
| ECHO | Pin 10 | Echo output |

**Sketch:** `Sonar_test/Sonar_test.ino`
Prints distance in `cm` and `mm`.

---

## 5. Photoresistor / Light Intensity Sensor Module (JZK LM393)

*(Sold under names like "JZK Photoresistor Sensor Module", "Digital Light Intensity Sensor Module", "Light Brightness Detector Module").*

Uses an LDR (photoresistor) and an LM393 comparator:
- **3-pin modules (`VCC`, `GND`, `DO`):** Digital output `DO` switches `LOW` when bright and `HIGH` when dark. Adjust the trigger point using the onboard blue potentiometer screw.
- **4-pin modules (`VCC`, `GND`, `DO`, `AO`):** Also includes analog pin `AO`, which outputs a continuous value from `0` (brightest) to `1023` (darkest).

**Library needed:** None

**Wiring:**

| Light Sensor Pin | Arduino Uno      | Notes |
| :--- | :--- | :--- |
| VCC | 5V | Power |
| GND | GND | Ground |
| DO | Pin 2 | Digital threshold output (`0` = Bright, `1` = Dark) |
| AO *(if 4-pin)* | A0 | Analog output (`0–1023`), leave unconnected if 3-pin |

**Sketch:** `Photoresistor_Light_test/Photoresistor_Light_test.ino`
Cover the LDR with your hand or shine a phone torch on it while turning the blue potentiometer until the trigger LED switches on and off.

---

## 6. 2-Axis Analog Joystick (KY-023)

Uses two 10k potentiometers for the X and Y axes (`0–1023`, center resting value is roughly `512`) and a push button (`SW`) that connects to GND when pressed down.

**Library needed:** None

**Wiring:**

| Joystick Pin | Arduino Uno      | Notes |
| :--- | :--- | :--- |
| GND | GND | Ground |
| +5V | 5V | Power |
| VRx | A0 | X-axis analog out |
| VRy | A1 | Y-axis analog out |
| SW | Pin 2 | Push button (uses `INPUT_PULLUP` in code, active `LOW`) |

**Sketch:** `Joystick_test/Joystick_test.ino`
Prints `X`, `Y`, and whether the button is pressed.

---

## Common Issues

- **Garbled text in Serial Monitor:** Change the Serial Monitor baud rate dropdown to **`115200`**.
- **`Failed to boot VL53L0X` / `Failed to find MPU6050`:** Check that `SDA` is on `A4` and `SCL` is on `A5` (not swapped), and make sure pin headers are connected properly (they should be)
- **MFRC522 `0x00` or `0xFF` communication error:** Check SPI pins (`9, 10, 11, 12, 13`) and make sure `3.3V` and `GND` are connected.
