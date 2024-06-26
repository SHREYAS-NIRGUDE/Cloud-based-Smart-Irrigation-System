# Cloud-based-Smart-Irrigation-System

This project implements a Smart Irrigation System using an ESP32 microcontroller. The system monitors soil moisture, temperature, humidity, and detects rainfall. Based on these readings, it controls a motor connected to a water pump. Additionally, the water pump can be manually controlled via an IoT cloud server where all sensor readings are displayed.

## Features

- **Soil Moisture Measurement**: Monitors the moisture level of the soil.
- **Temperature and Humidity Monitoring**: Measures the ambient temperature and humidity using a DHT11 sensor.
- **Rainfall Detection**: Detects rainfall to adjust irrigation needs.
- **Light Level Detection**: Measures the ambient light level.
- **Automatic Irrigation Control**: Controls a servo motor connected to a water pump based on soil moisture and temperature readings.
- **Manual Control via IoT Cloud**: Allows manual control of the water pump through the Blynk IoT platform.
- **Visual Indicators**: Includes an LCD display to show real-time sensor readings, LEDs for status indication, and a buzzer for alerts.

## Components

- **ESP32**: The main microcontroller used for this project.
- **DHT11 Sensor**: Used for measuring temperature and humidity.
- **Soil Moisture Sensor**: Measures the moisture content in the soil.
- **Rainfall Sensor**: Detects rainfall.
- **LDR (Light Dependent Resistor)**: Measures ambient light levels.
- **Servo Motor**: Controls the water pump.
- **Buzzer**: Provides audible alerts.
- **LEDs**: Red and green LEDs for status indication.
- **LiquidCrystal Display (LCD)**: Displays sensor readings.

## Circuit Diagram

![Circuit Diagram]([Circuit Diagram.jpg](https://github.com/SHREYAS-NIRGUDE/Cloud-based-Smart-Irrigation-System/blob/main/Circuit%20Diagram.jpg?raw=true))

Usage
The system will automatically start measuring the soil moisture, temperature, humidity, rainfall, and light levels.
Based on the soil moisture and temperature readings, the servo motor will control the water pump.
Sensor readings are displayed on the LCD and can be monitored through the Blynk app.
The water pump can be manually controlled via the Blynk app.
