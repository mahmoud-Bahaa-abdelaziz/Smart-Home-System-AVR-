# 🏠 Smart Home Automation System
An embedded smart home automation system developed using an **AVR microcontroller** and **Embedded C**.

## 📌 Features
### 🔐 Password-Based Authentication
- Secure access using a 4×4 keypad
- Password verification before granting access

### 💾 EEPROM Storage
- Stores user passwords persistently
- Retains data even after power loss

### 🚪 Servo Motor Control
- Simulates an automated smart door lock
- Unlocks and locks the door based on authentication status

### 🌡️ Temperature Monitoring
- Reads ambient temperature using an LM35 sensor
- Displays real-time temperature readings

## 🛠️ Hardware Components
- AVR Microcontroller (ATmega32 / ATmega16)
- 4×4 Keypad
- Servo Motor
- LM35 Temperature Sensor
- Internal EEPROM
- 16×2 LCD Display

## 💻 Software & Tools
- Embedded C
- AVR-GCC
- Microchip Studio
- Proteus

## 🚀 How It Works
1. Enter the password using the keypad.
2. The password is verified against the value stored in EEPROM.
3. If correct, the servo motor unlocks the door.
4. Otherwise, access is denied.
5. The system continuously monitors and displays the temperature.

## 👨‍💻 Author
**Mahmoud Bahaa**
Computer Engineering Student | Embedded Systems | AI & Machine Learning

GitHub: https://github.com/mahmoud-Bahaa-abdel



Mahmoud Bahaa

Computer Engineering Student | Embedded Systems | Robotics | AI & Machine Learning
