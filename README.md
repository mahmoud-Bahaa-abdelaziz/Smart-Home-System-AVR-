An embedded smart home automation system developed using an AVR microcontroller and Embedded C. The project integrates security, automation, and environmental monitoring through peripherals such as a keypad, EEPROM, servo motor, and temperature sensor.

📌 Features
🔐 Password-Based Authentication
Secure access using a 4x4 keypad.
Password verification before granting access.
💾 EEPROM Storage
Stores user password persistently.
Retains data even after power loss.
🚪 Servo Motor Control
Simulates an automated smart door lock.
Opens and closes the door based on authentication status.
🌡️ Temperature Monitoring
Reads ambient temperature using a temperature sensor.
Continuously monitors environmental conditions.
🤖 Home Automation
Integrates security and monitoring into a single embedded system.
Demonstrates real-time interaction between multiple hardware peripherals.
🛠️ Hardware Components
AVR Microcontroller (ATmega32 / ATmega16)
4x4 Keypad
Servo Motor
Temperature Sensor (LM35)
EEPROM (Internal)
LCD Display (16x2)
Power Supply
💻 Software & Tools
Embedded C
AVR-GCC
Atmel Studio / Microchip Studio
Proteus (for simulation, if applicable)
📂 Project Structure
Smart-Home-System/
│── main.c
│── keypad.c
│── keypad.h
│── lcd.c
│── lcd.h
│── servo.c
│── servo.h
│── temperature.c
│── temperature.h
│── eeprom.c
│── eeprom.h
│── utils/
└── README.md
🚀 How It Works
The system prompts the user to enter a password using the keypad.
The entered password is compared with the value stored in EEPROM.
If authentication succeeds:
The servo motor unlocks the door.
System access is granted.
If authentication fails:
Access is denied.
The temperature sensor continuously measures and displays the current temperature.
🎯 Learning Outcomes
AVR Microcontroller Programming
Embedded C Development
EEPROM Memory Management
Servo Motor Control using PWM
Keypad Interfacing
LCD Interfacing
Analog-to-Digital Conversion (ADC)
Sensor Integration
Real-Time Embedded System Design



Mahmoud Bahaa

Computer Engineering Student | Embedded Systems | Robotics | AI & Machine Learning
