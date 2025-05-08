# Temperature Control System with Feedback

This project implements a temperature control system using an **Arduino-based microcontroller** (e.g., Arduino Uno, ESP32) to manage a heating element, display temperature data, and provide feedback using an OLED display, RGB LED, and a buzzer.

The system uses a **Dallas DS18B20** temperature sensor to measure the temperature and controls the heating element with a **relay**. Based on the temperature, the system can change states, turning the heater on or off and providing visual and audio feedback.

## Features

- **Temperature Sensing**: Reads the temperature using the DS18B20 sensor.
- **State Management**: The system operates in different states:
  - **Idle**: System is idle, no heating.
  - **Heating**: Heating up, the heater is on.
  - **Stabilizing**: Temperature is near the target, stabilizing.
  - **Target Reached**: Target temperature is reached, heating is off.
  - **Overheat**: Temperature exceeds safe limits, the system triggers a buzzer.
- **Feedback**:
  - **OLED Display**: Displays the current temperature and system state.
  - **RGB LED**: Changes color to indicate the system's current state:
    - White for Idle
    - Red for Heating
    - Yellow for Stabilizing
    - Green for Target Reached
    - Blue for Overheat
  - **Buzzer**: Sounds when the system is in an overheat state.

## Components Needed

- **DS18B20 Temperature Sensor**
- **Relay Module** (for controlling the heating element)
- **RGB LED** (common cathode)
- **Buzzer**
- **Arduino (or compatible board)** (e.g., Arduino Uno, ESP32)
- **OLED Display (128x64, SSD1306)**
- **Resistor** (for the DS18B20 sensor, typically 4.7kΩ)
- **Jumper Wires**

## Circuit Diagram

- **DS18B20 Sensor**:
  - VCC to 5V (or 3.3V for ESP32)
  - GND to GND
  - DATA to pin 4 (OneWire bus) with a 4.7kΩ pull-up resistor between DATA and VCC.

- **Relay**:
  - Control pin connected to pin 5 (Relay Pin).

- **RGB LED**:
  - Connect the Red, Green, and Blue pins to 18, 19, and 23 respectively.
  - The common cathode pin should be connected to GND.

- **Buzzer**:
  - Connect to pin 12.

- **OLED Display**:
  - SDA to A4 (for Arduino) or SDA pin for ESP32.
  - SCL to A5 (for Arduino) or SCL pin for ESP32.
  - VCC to 3.3V or 5V (depending on your display's requirement).
  - GND to GND.
