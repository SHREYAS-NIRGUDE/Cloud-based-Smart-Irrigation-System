#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#include <ESP32Servo.h>
#include <LiquidCrystal.h>

// Replace with your network credentials
char auth[] = "ZH208colxIDl4CRx7dzbhm8jR6gVoujy";
const char* ssid = "wifi";
const char* password = "";

// Replace with your pin connections using GPIO pin numbers
#define soilMoisturePin 34 // Soil moisture sensor pin (GPIO 34)
#define rainfallPin 35     // Rainfall sensor pin (GPIO 35)
#define temperatureHumidityPin 27 // DHT11 sensor pin (GPIO 27)
#define ldrPin 36          // LDR pin (GPIO 36)
#define servoPin 12        // Servo motor pin (GPIO 12)
#define buzzerPin 25       // Buzzer pin (GPIO 25)
#define redLedPin 13       // Red LED pin (GPIO 13)
#define greenLedPin 33     // Green LED pin (GPIO 33)

// Replace with your threshold values
const int soilMoistureThreshold = 2500;   // Soil moisture threshold
const float temperatureThreshold = 30.0; // Temperature threshold

// Create instances for DHT sensor, Servo motor, and Buzzer
DHT dht(temperatureHumidityPin, DHT11);
Servo servoMotor;
int buzzerState = LOW;

// Virtual Pin for Blynk app control
#define servoControlPin V5

// Servo position variable
int servoPosition = 90;

BLYNK_WRITE(servoControlPin) {
  // Get the new servo position from the Blynk app
  servoPosition = param.asInt();
  // Set the servo to the new position
  servoMotor.write(servoPosition);
}

// Define LCD connections
const int rs = 19;
const int en = 23;
const int d4 = 18;
const int d5 = 17;
const int d6 = 16;
const int d7 = 15;
// Create instance for LCD display
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void setup() {
  // Start serial communication
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Initialize Blynk
  Blynk.begin(auth, ssid, password);

  // Initialize sensors
  dht.begin();
  
  // Initialize Servo motor
  servoMotor.setPeriodHertz(50); // Set the PWM frequency of the servo motor (default: 50Hz)
  servoMotor.attach(servoPin, 500, 2400); // Adjust the pulse range (500-2400) as per your servo motor
  
  // Set initial position of the Servo motor
  servoMotor.write(servoPosition); // Set the initial angle as per your setup

  // Initialize Buzzer
  pinMode(buzzerPin, OUTPUT);

  // Initialize LEDs
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);

  lcd.begin(16, 2);

  // Set initial display
  //lcd.setCursor(0, 0);
  //lcd.print("Soil: -- Rain: --");
  //lcd.setCursor(0, 1);
  //lcd.print("Temp: --C Hum: --%");
  //delay(2000);  // Wait for the display to show the initial message
}

void loop() {
  Blynk.run();
  
  // Read sensor values
  int soilMoisture = analogRead(soilMoisturePin);
  int rainfall = analogRead(rainfallPin);
  float temperature = dht.readTemperature();
  int lightLevel = analogRead(ldrPin);
  int humidity = dht.readHumidity();

  // Control the Servo motor based on irrigation needs
  if (soilMoisture > soilMoistureThreshold || temperature > temperatureThreshold) {
    servoMotor.write(0); // Rotate the Servo to a specific angle (0 degrees) as per your setup
  } else {
    servoMotor.write(servoPosition); // Rotate the Servo to the current position
  }

  // Update Blynk app with sensor readings
  Blynk.virtualWrite(V1, soilMoisture);
  Blynk.virtualWrite(V2, rainfall);
  Blynk.virtualWrite(V3, temperature);
  Blynk.virtualWrite(V4, lightLevel);
  Blynk.virtualWrite(V6, humidity);
  
  // Print sensor values in the Serial Monitor
  Serial.print("Soil Moisture: ");
  Serial.print(soilMoisture);
  Serial.println(" wfv");
  Serial.print("Rainfall: ");
  Serial.print(rainfall);
  Serial.println(" cm");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  Serial.print("Light Level: ");
  Serial.println(lightLevel);
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  // Check if rainfall value is 1000 and beep the buzzer three times
  if (rainfall < 4000) {
    for (int i = 0; i < 3; i++) {
      digitalWrite(buzzerPin, HIGH);
      delay(200);
      digitalWrite(buzzerPin, LOW);
      delay(200);
    }
  }

  // Check if servo motor is at 0 position and turn on the green LED
  if (servoMotor.read() == 0) {
    digitalWrite(greenLedPin, HIGH);
  } else {
    digitalWrite(greenLedPin, LOW);
  }

  // Check if rainfall value is less than 4000 and turn on the red LED
  if (rainfall < 4000) {
    digitalWrite(redLedPin, HIGH);
  } else {
    digitalWrite(redLedPin, LOW);
  }

  lcd.noCursor();
  // Update LCD display with sensor values
  lcd.setCursor(0, 0);
  lcd.print("Soil: ");
  lcd.print(soilMoisture);
  lcd.blink();

  delay(1000);

  lcd.setCursor(0, 1);
  lcd.print("Rain: ");
  lcd.print(rainfall);
  lcd.blink();

  delay(1000);

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print("C");
  lcd.blink();

  delay(1000);

  lcd.setCursor(0, 1);
  lcd.print("Humid: ");
  lcd.print(humidity);
  lcd.print("%");
  lcd.blink();

  delay(1000);

  lcd.setCursor(0, 0);
  lcd.print("Light: ");
  lcd.print(lightLevel);
  lcd.blink();
  delay(1000); // Adjust the delay as needed
}