# Arduino-Uno-R3-Digital-combination-lock-using-servo-horn-as-Latch

# 🔐 Digital Combination Lock — Arduino

A simple **Arduino-based digital combination lock system** using a **4×4 keypad, I2C LCD, servo motor, buzzer, and status LEDs**. The system allows the user to enter a predefined password through the keypad. If the password is correct, the servo unlocks the mechanism and the green LED turns on. Otherwise, access is denied and the red LED indicates failure.

This project is designed and simulated using **Tinkercad**.

---

## 📸 Project Overview

The project consists of:

- Arduino UNO
- 4×4 Matrix Keypad
- 16×2 I2C LCD
- Servo Motor
- Piezo Buzzer
- Green LED
- Red LED

The Arduino acts as the main controller, processing keypad input and controlling the LCD, servo, LEDs, and buzzer.

---

## ⚙️ Features

- 🔢 4-digit password authentication
- 🔐 Servo-based locking mechanism
- 📟 16×2 LCD for user interaction
- 🟢 Green LED for successful authentication
- 🔴 Red LED for failed authentication / locked state
- 🔊 Buzzer for audio feedback
- `*` key to reset the entered password
- `#` key to submit the password
- Automatic relocking after successful access
- Serial Monitor support for debugging

---

## 🧰 Components Required

| Component | Quantity |
|---|---:|
| Arduino UNO | 1 |
| 4×4 Matrix Keypad | 1 |
| 16×2 I2C LCD | 1 |
| Servo Motor | 1 |
| Piezo Buzzer | 1 |
| Green LED | 1 |
| Red LED | 1 |
| Resistors | 2 |
| Breadboard | 1 |
| Jumper Wires | As required |

---

## 🔌 Pin Configuration

### 4×4 Keypad

| Keypad Pin | Arduino Pin |
|---|---|
| Row 1 | D2 |
| Row 2 | D3 |
| Row 3 | D4 |
| Row 4 | D5 |
| Column 1 | D6 |
| Column 2 | D7 |
| Column 3 | D8 |
| Column 4 | D9 |

### Other Components

| Component | Arduino Pin |
|---|---|
| Servo Signal | D10 |
| Buzzer | D11 |
| Green LED | D12 |
| Red LED | D13 |
| LCD SDA | A4 |
| LCD SCL | A5 |
| LCD VCC | 5V |
| LCD GND | GND |

> **Note:** The LCD uses the I2C interface. For an Arduino UNO, SDA is connected to **A4** and SCL to **A5**.

---

## 🔑 Password

The default password is:

```text
1975
```

### How to enter the password

1. Turn on the Arduino.
2. The LCD displays:

```text
Enter Code:
```

3. Enter:

```text
1975
```

4. Press:

```text
#
```

5. If the password is correct:
   - LCD displays **ACCESS GRANTED**
   - Green LED turns ON
   - Buzzer produces a high-pitched tone
   - Servo rotates to **90°**
   - Lock remains open for **3 seconds**
   - System automatically locks again

### Incorrect password

If the entered password is incorrect:

```text
ACCESS DENIED
```

The red LED flashes and the buzzer produces a low-frequency error tone.

---

## 🎛️ Keypad Controls

| Key | Function |
|---|---|
| `0–9` | Enter password digits |
| `A–D` | Can be used as additional input characters |
| `*` | Reset current input |
| `#` | Submit password |

Only the first **4 characters** are accepted as the password.

---

## 🔄 System Working

```text
             ┌─────────────────┐
             │   Arduino UNO   │
             └────────┬────────┘
                      │
        ┌─────────────┼─────────────┐
        │             │             │
        ▼             ▼             ▼
   ┌─────────┐   ┌──────────┐   ┌────────┐
   │ Keypad  │   │   LCD    │   │ Buzzer │
   └─────────┘   └──────────┘   └────────┘
                      │
                      ▼
               Password Check
                      │
             ┌────────┴────────┐
             │                 │
          Correct           Incorrect
             │                 │
             ▼                 ▼
        ┌─────────┐       ┌─────────┐
        │  Servo  │       │ Red LED │
        │ Unlock  │       │  Error  │
        └─────────┘       └─────────┘
             │
             ▼
       Green LED ON
```

---

## 🧠 Program Logic

The program follows this sequence:

```text
START
  │
  ▼
Initialize LCD, Keypad, Servo,
LEDs and Buzzer
  │
  ▼
Lock Servo
  │
  ▼
Wait for Keypad Input
  │
  ├── '*' ──► Clear Input
  │
  ├── '#' ──► Check Password
  │
  └── Digit ──► Add to Password
                    │
                    ▼
              Compare Password
                 /       \
              Match     No Match
                │           │
                ▼           ▼
         ACCESS GRANTED  ACCESS DENIED
                │           │
                ▼           ▼
          Unlock Servo    Red LED
                │         + Buzzer
                ▼
           Wait 3 sec
                │
                ▼
             Relock
```

---

## 📚 Libraries Used

The following Arduino libraries are required:

```cpp
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <string.h>
```

### Libraries

- **Keypad** — interfaces with the 4×4 matrix keypad
- **LiquidCrystal_I2C** — controls the 16×2 I2C LCD
- **Servo** — controls the servo motor
- **string.h** — provides `strcmp()` and `memset()`

---

## 🛠️ Installation

### 1. Install Arduino IDE

Download and install the Arduino IDE.

### 2. Install Required Libraries

From:

```text
Arduino IDE
    ↓
Sketch
    ↓
Include Library
    ↓
Manage Libraries
```

Install:

```text
Keypad
LiquidCrystal I2C
Servo
```

`string.h` is generally included with the Arduino environment.

---

## 💻 Uploading the Code

1. Open the Arduino IDE.
2. Connect the Arduino UNO.
3. Select:

```text
Tools → Board → Arduino UNO
```

4. Select the appropriate COM port.
5. Paste the provided code.
6. Click **Upload**.

---

## 🔧 Changing the Password

The password can be changed in the code:

```cpp
const char masterCode[] = "1975";
```

For example, to change it to `1234`:

```cpp
const char masterCode[] = "1234";
```

The system currently supports a **4-character password**.

---

## 🔧 Changing Servo Positions

The locked and unlocked positions are defined here:

```cpp
const int LOCKED_POSITION = 0;
const int UNLOCKED_POSITION = 90;
```

If your physical locking mechanism requires different angles, they can be modified:

```cpp
const int LOCKED_POSITION = 10;
const int UNLOCKED_POSITION = 100;
```

The exact angles depend on the mechanical design of the lock.

---

## 📟 LCD Address

The LCD is configured with:

```cpp
LiquidCrystal_I2C lcd(0x27, 16, 2);
```

The most common I2C address is:

```text
0x27
```

If the LCD does not work, try:

```cpp
LiquidCrystal_I2C lcd(0x3F, 16, 2);
```

---

## 🔊 Feedback System

### Correct Password

| Output | Action |
|---|---|
| LCD | `ACCESS GRANTED` |
| Green LED | ON |
| Red LED | OFF |
| Buzzer | High tone |
| Servo | Moves to 90° |

### Wrong Password

| Output | Action |
|---|---|
| LCD | `ACCESS DENIED` |
| Green LED | OFF |
| Red LED | Flashes |
| Buzzer | Low error tone |
| Servo | Remains locked |

---

## 🗂️ Suggested Repository Structure

```text
Digital-Combination-Lock/
│
├── Digital_Combination_Lock.ino
├── README.md
│
├── images/
│   └── circuit-diagram.png
│
└── simulation/
    └── tinkercad-link.txt
```

---

## 🚀 Possible Improvements

This project can be extended with several additional security features:

- 🔢 6-digit or longer passwords
- 🔒 Temporary lockout after multiple failed attempts
- ⏱️ Automatic lockout timer
- 🔊 Different buzzer patterns
- 💾 EEPROM password storage
- 🔄 Password change functionality
- 👆 Fingerprint authentication
- 📱 Bluetooth-based unlocking
- 📶 Wi-Fi/IoT-based remote unlocking using ESP32
- 📝 Access attempt logging
- 🔋 Battery-powered operation
- 🔐 RFID card authentication
- 🛡️ Tamper detection using an additional sensor

---

## ⚠️ Security Note

This project is primarily an **educational prototype**. The password is hard-coded into the Arduino program:

```cpp
const char masterCode[] = "1975";
```

Therefore, it should **not be considered a secure commercial locking system**. Anyone with access to the source code can determine the password.

For a real security system, password storage should be protected and additional authentication mechanisms should be implemented.

---

## 🎯 Learning Outcomes

Through this project, you can learn:

- Arduino programming
- Matrix keypad interfacing
- I2C communication
- LCD interfacing
- Servo motor control
- Digital input/output
- Password/string handling in C/C++
- Conditional logic
- Hardware-software integration
- Embedded system design

---

## 👨‍💻 Author

**Sohan Ghosh**

Electronics & Communication Engineering  
Arduino / Embedded Systems Project

---

## 📜 License

This project is intended for **educational and personal use**. Feel free to modify and improve the project for learning and academic purposes.
