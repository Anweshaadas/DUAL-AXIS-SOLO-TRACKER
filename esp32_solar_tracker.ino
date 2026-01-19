#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <DHT.h>
#include <DHT_U.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "ACS712.h"
#include <BH1750.h>
#include "time.h"
#include <HTTPClient.h>
#include <Servo.h>
#include <Arduino_JSON.h>

// ML model
#include "D:\\arduino-1.8.19\\libraries\\Random_Forest.h"

// ================== BLYNK ==================
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6RKIpiE7q"
#define BLYNK_DEVICE_NAME "fyp"

char auth[] = "n3KDCJEb8CdgBeA0UgWSHcUGa9viduA4";
char ssid[] = "KAVINDU";
char pass[] = "password";

// ================== WEATHER ==================
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 0;
const int daylightOffset_sec = 3600;
const char* openWeatherMapApiKey = "fb73d4644cc4e9bf9de38de50222c6fc";
String city = "Colombo";
String countryCode = "LK";

// ================== DHT ==================
#define DHTPIN 4
#define DHTTYPE DHT11
DHT_Unified dht(DHTPIN, DHTTYPE);

// ================== OBJECTS ==================
WiFiServer server(80);
Adafruit_MPU6050 mpu;
BH1750 lightMeter(0x23);
BlynkTimer timer;

// ================== POWER MEASUREMENT ==================
ACS712 ACS(25, 3.3, 4095, 185);   // ACS712-5A
const int voltPin = 34;

// Voltage divider values
const float R1 = 100000.0;   // 100k ohm
const float R2 = 10000.0;    // 10k ohm

// ================== VARIABLES ==================
float voltage_value = 0;
float current_mA = 0;
float current_A = 0;
float power_W = 0;

double temperature, humidity, wind, pressure, visibility;
double tempC;
float lux, irr, radiation;

unsigned long lastTime = 0;
unsigned long timerDelay = 600000;

// ================== SETUP ==================
void setup() {
  Serial.begin(115200);
  Wire.begin();

  Blynk.begin(auth, ssid, pass);

  ACS.autoMidPoint();

  if (!lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
    Serial.println("BH1750 error");
  }

  dht.begin();
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

// ================== HTTP REQUEST ==================
String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
  http.begin(client, serverName);
  int httpResponseCode = http.GET();
  String payload = "{}";
  if (httpResponseCode > 0) payload = http.getString();
  http.end();
  return payload;
}

// ================== LOOP ==================
void loop() {

  // ===== TEMPERATURE & HUMIDITY =====
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  temperature = event.temperature;
  tempC = temperature;

  dht.humidity().getEvent(&event);
  humidity = event.relative_humidity;

  // ===== CURRENT =====
  current_mA = ACS.mA_DC();
  current_A = current_mA / 1000.0;

  // ===== VOLTAGE (FIXED WITH DIVIDER) =====
  float adc = analogRead(voltPin);
  float adc_voltage = (adc * 3.3) / 4095.0;
  voltage_value = adc_voltage * ((R1 + R2) / R2);

  // ===== POWER =====
  power_W = voltage_value * current_A;

  Serial.println("------ POWER DATA ------");
  Serial.print("Voltage (V): "); Serial.println(voltage_value);
  Serial.print("Current (A): "); Serial.println(current_A);
  Serial.print("Power (W): "); Serial.println(power_W);

  // ===== LIGHT & IRRADIANCE =====
  lux = lightMeter.readLightLevel();
  irr = lux * 0.0079;
  radiation = irr / 375000.0;

  // ===== WEATHER API =====
  if ((millis() - lastTime) > timerDelay && WiFi.status() == WL_CONNECTED) {
    String serverPath =
      "http://api.openweathermap.org/data/2.5/weather?q=" +
      city + "," + countryCode + "&appid=" + openWeatherMapApiKey;

    String jsonBuffer = httpGETRequest(serverPath.c_str());
    JSONVar data = JSON.parse(jsonBuffer);

    if (JSON.typeof(data) != "undefined") {
      pressure = data["main"]["pressure"];
      wind = data["wind"]["speed"];
      visibility = data["visibility"];
    }
    lastTime = millis();
  }

  // ===== ML PREDICTION =====
  float feature_values[] = {
    tempC, humidity, radiation,
    tempC, humidity, radiation,
    tempC, humidity, radiation
  };

  float prediction = intercept;
  for (int i = 0; i < sizeof(coefficients) / sizeof(coefficients[0]); i++) {
    prediction += coefficients[i] * feature_values[i];
  }

  float predicted_power = (prediction * 6) / 5000;

  Serial.print("Predicted Power: ");
  Serial.println(predicted_power);

  // ===== BLYNK SEND =====
  Blynk.virtualWrite(V0, tempC);
  Blynk.virtualWrite(V1, humidity);
  Blynk.virtualWrite(V2, wind);
  Blynk.virtualWrite(V3, visibility / 1000);
  Blynk.virtualWrite(V5, voltage_value);
  Blynk.virtualWrite(V6, current_A);
  Blynk.virtualWrite(V7, power_W);
  Blynk.virtualWrite(V8, irr);
  Blynk.virtualWrite(V9, pressure);
  Blynk.virtualWrite(V11, predicted_power);

  Blynk.run();
  timer.run();

  delay(2000);
}

