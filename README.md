☀️ Dual-Axis Solar Tracker with Power Measurement & Prediction
🔓 Open Source Project

An IoT-enabled dual-axis solar tracking system that measures real solar power output and predicts future power generation using machine learning and weather data.

📌 Project Overview

This project implements a dual-axis solar tracker using ESP32, combined with real-time power measurement and machine learning-based power prediction.
The system dynamically aligns the solar panel to maximize sunlight exposure, measures actual voltage, current, and power, integrates live weather data, and predicts solar power output using a trained regression model.

🎯 Objectives

Maximize solar energy harvesting using dual-axis tracking
Measure real-time solar panel voltage, current, and power
Predict solar power output using machine learning
Integrate live weather data for better prediction accuracy
Enable remote monitoring using IoT (Blynk)
Create a scalable and research-oriented solar monitoring system

🧠 System Architecture
LDR Sensors ──┐
              ├── ESP32 ── Servo Motors (Dual Axis Tracking)
BH1750 ───────┘
DHT11 ───────────┐
ACS712 ──────────┼── Power Calculation (V × I)
Voltage Divider ─┘
ESP32 ── WiFi ── Weather API ── ML Model ── Power Prediction
ESP32 ── Blynk ── Remote Monitoring Dashboard

🛠️ Hardware Requirements
Component	Purpose
ESP32	Main controller & Wi-Fi communication
Solar Panel	Energy generation
Dual-Axis Servo Motors	Solar panel alignment
LDR Sensors	Sunlight direction detection
BH1750	Light intensity measurement (lux)
DHT11	Temperature & humidity sensing
ACS712 (5A)	Current measurement
Voltage Divider (100kΩ + 10kΩ)	Solar panel voltage measurement
MPU6050	Orientation & motion sensing
Connecting Wires & Breadboard	Circuit connections

💻Software Requirements

Arduino IDE
ESP32 Board Package
Python 3.x
Blynk IoT Platform
OpenWeatherMap API
Machine Learning Libraries
NumPy
Pandas
Scikit-learn
Matplotlib
Seaborn
🔌 Power Measurement Method
🔹 Voltage Measurement
Solar panel voltage is stepped down using a voltage divider
ESP32 ADC reads safe voltage (≤ 3.3V)
Actual voltage calculated as:
Vsolar = Vadc × (R1 + R2) / R2
🔹 Current Measurement
ACS712 measures DC current (mA)
Converted to Amps in firmware
🔹 Power Calculation
Power (W) = Voltage (V) × Current (A)

🤖 Machine Learning Models
The project uses a trained regression model to predict solar power output based on:
Temperature
Humidity
Solar radiation
Light intensity
Weather parameters
Models Used:
Linear Regression
Decision Tree Regressor
Random Forest Regressor (Primary Model)
The trained model is exported and integrated into the ESP32 firmware.

🌦️ Weather Data Integration
Live weather data fetched using OpenWeatherMap API
Parameters used:
Temperature
Humidity
Pressure
Wind speed
Visibility
Improves accuracy of power prediction

📂 Project Structure
DUAL-AXIS-SOLO-TRACKER/
│
├── ESP32 code.ino              # Main firmware (tracking + power + IoT)
├── File converter.ipynb        # Data processing & model training
├── Power Prediction code.ipynb # ML power prediction analysis
├── Weather Prediction Code.ipynb
├── random_forest_model.pkl     # Trained ML model
└── README.md

🚀 Features
Dual-axis solar tracking
Real-time voltage, current & power measurement
Weather-aware power prediction
Machine learning integration
IoT-based remote monitoring (Blynk)
Data visualization & analysis
Research and industry-ready architecture

🔮 Future Enhancements
Cloud database storage (Firebase / AWS)
Mobile app for monitoring
MPPT integration
Battery charging analytics
Deep learning (LSTM) for time-series prediction
Edge ML optimization on ESP32
