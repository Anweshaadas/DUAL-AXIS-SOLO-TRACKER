☀️ Dual-Axis Solar Tracker with Power Prediction

An IoT-enabled dual-axis solar tracking system integrated with machine learning models to maximize solar energy harvesting and accurately predict power generation.

🧩 Project Summary

This project combines embedded systems, IoT, and machine learning to build a smart dual-axis solar tracker capable of predicting solar power output using real-time sensor data and weather information.
The system continuously aligns solar panels for maximum sunlight exposure and applies regression models to forecast power generation.

🧠 Core Technologies
Domain	Tools / Technologies
Programming	Python, Arduino
IoT	ESP32, Sensors
Machine Learning	Random Forest, Decision Tree, Linear Regression
Data Analysis	Pandas, Matplotlib, Seaborn
APIs	OpenWeatherMap
Hardware Control	Arduino, ESP32
🏗️ System Components
🔌 Hardware & Sensors

DHT11 – Temperature & Humidity sensing

BH1750 – Light intensity measurement

MPU6050 – Orientation and motion tracking

ACS712 – Current sensing for power monitoring

Dual-Axis Mechanism – Maximizes solar exposure

Arduino + ESP32 – Control, communication & data transfer

🤖 Machine Learning Models Used

The following regression models are trained to predict solar power output:

Linear Regression

Decision Tree Regressor

Random Forest Regressor (Primary Model)

📌 Predictions are based on:

Sensor readings

Weather conditions

Historical power data

🌦️ Weather Data Integration

Real-time weather data fetched using OpenWeatherMap API

Historical weather dataset (Antwerp) used for training and testing

Improves prediction accuracy by incorporating:

Temperature

Humidity

Light intensity

Weather conditions

📊 Data Processing & Analysis
Python Scripts & Notebooks
File	Purpose
converter.ipynb	Data preprocessing, Random Forest training, feature extraction, and model export
final.ipynb	Dataset merging, regression modeling, evaluation, and visualization
Libraries Used

Pandas – Data manipulation

Matplotlib – Graph plotting

Seaborn – Statistical visualizations

📈 Key Features

✅ Dual-axis solar tracking for maximum efficiency
✅ Real-time sensor data acquisition
✅ Machine learning-based power prediction
✅ Weather-enhanced prediction accuracy
✅ Power trend visualization & analysis
✅ IoT-enabled monitoring

📂 Project Structure
Dual-Axis-Solar-Tracker/
│
├── converter.ipynb     # Feature extraction & Random Forest training
├── final.ipynb         # Regression models & visualization
├── datasets/           # Weather & power datasets
├── arduino_code/       # Embedded system code
└── README.md

⚙️ Installation & Usage
1️⃣ Clone the Repository
git clone https://github.com/kavindu26589/Dual-Axis-Solar-Tracker-Project.git

2️⃣ Install Python Dependencies
pip install pandas matplotlib seaborn scikit-learn

3️⃣ Run Notebooks

Open converter.ipynb → Train model & extract features

Open final.ipynb → Analyze data & visualize results

4️⃣ Upload Embedded Code

Flash Arduino & ESP32 with provided firmware

Connect sensors and power supply

🔮 Future Enhancements

Deep Learning (LSTM) for time-series prediction

Cloud dashboard for live monitoring

Mobile app integration

Solar efficiency analytics

Edge ML deployment on ESP32
