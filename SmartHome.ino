// SmartHome system made using ESP32, RainSensor, FlameSensor, Buzzers, PIR MotionSensor, ServoMotor, and LEDs

#define BLYNK_TEMPLATE_ID   "TMPL6A3titjls"
#define BLYNK_TEMPLATE_NAME "Smart home"
#define BLYNK_AUTH_TOKEN    "Jdqp2VPDBVehtd0TZJAe8zbmxjMWCn8I"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>


// Wifi Configurations
char ssid[] = "ROSHAN5975";
char pass[] = "12345678";

// ESP Pins that are used

// Fire
#define FLAME_DO_PIN 27
#define FIRE_BUZZER_PIN 12
#define FIRE_LED_PIN 13

// Rain
#define RAIN_ANALOG_PIN 34
#define RAIN_BUZZER_PIN 26
#define RAIN_LED_PIN 25
#define RAIN_THRESHOLD 3800

// PIR + Servo + LED
#define PIR_PIN 4
#define SERVO_PIN 14
#define PIR_LED_PIN 21

// Variables
int lastFlameState = 0;
int lastRainState  = 0;
int lastPirState   = 0;

Servo myServo;
BlynkTimer timer;

// Blynk Write

// Manual door control (V2)
BLYNK_WRITE(V2) {
  int value = param.asInt();
  if (value == 1) myServo.write(90);
  else myServo.write(0);
}

// Manual LED control (V1)
BLYNK_WRITE(V1) {
  int value = param.asInt();
  digitalWrite(PIR_LED_PIN, value ? HIGH : LOW);
}

// Blynk Connected
BLYNK_CONNECTED() {
  Serial.println("Connected to Blynk!");
  Blynk.syncVirtual(V0, V1, V2, V3, V5);
}

// Fire Sensor
void checkFireSensor() {
  int flameState = digitalRead(FLAME_DO_PIN);
  if (flameState == HIGH) {
    Serial.println("FIRE DETECTED!");
    digitalWrite(FIRE_LED_PIN, HIGH);
    tone(FIRE_BUZZER_PIN, 2000);  // High-pitch tone for fire
    if (flameState != lastFlameState) Blynk.virtualWrite(V0, 1);
  } else {
    Serial.println("No fire");
    digitalWrite(FIRE_LED_PIN, LOW);
    noTone(FIRE_BUZZER_PIN);       // Stop fire buzzer
    if (flameState != lastFlameState) Blynk.virtualWrite(V0, 0);
  }
  lastFlameState = flameState;
}

// Rain Sensor
void checkRainSensor() {
  int rainValue = analogRead(RAIN_ANALOG_PIN);
  int rainDetected = (rainValue < RAIN_THRESHOLD) ? 1 : 0;

  Serial.print("Rain: "); Serial.println(rainDetected ? "RAIN" : "NO RAIN");
  digitalWrite(RAIN_LED_PIN, rainDetected ? HIGH : LOW);

  if (rainDetected) tone(RAIN_BUZZER_PIN, 500); // Low-pitch tone for rain
  else noTone(RAIN_BUZZER_PIN);     //Stop Rain Buzzer

  if (rainDetected != lastRainState) Blynk.virtualWrite(V3, rainDetected);
  lastRainState = rainDetected;
}

// PIR Sensor + Servo Motor + LEDs
void checkPIR() {
  int pirState = digitalRead(PIR_PIN);
  digitalWrite(PIR_LED_PIN, pirState ? HIGH : LOW);

  if (pirState == HIGH) {
    myServo.write(90); // Move servo
    Serial.println("Motion detected!");
  } else {
    myServo.write(0);
    Serial.println("No motion");
  }

  if (pirState != lastPirState) Blynk.virtualWrite(V5, pirState);
  lastPirState = pirState;
}

// Setups
void setup() {
  Serial.begin(115200);

  // Fire setup
  pinMode(FLAME_DO_PIN, INPUT);
  pinMode(FIRE_BUZZER_PIN, OUTPUT);
  pinMode(FIRE_LED_PIN, OUTPUT);
  digitalWrite(FIRE_BUZZER_PIN, LOW);
  digitalWrite(FIRE_LED_PIN, LOW);

  // Rain setup
  pinMode(RAIN_BUZZER_PIN, OUTPUT);
  pinMode(RAIN_LED_PIN, OUTPUT);
  digitalWrite(RAIN_BUZZER_PIN, LOW);
  digitalWrite(RAIN_LED_PIN, LOW);

  // PIR setup
  pinMode(PIR_PIN, INPUT);
  pinMode(PIR_LED_PIN, OUTPUT);
  digitalWrite(PIR_LED_PIN, LOW);

  myServo.attach(SERVO_PIN);
  myServo.write(0);

  Serial.println("Connecting to WiFi & Blynk...");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Timers
  timer.setInterval(500L, checkFireSensor);
  timer.setInterval(500L, checkRainSensor);
  timer.setInterval(300L, checkPIR);

  Serial.println("System Ready!");
}

// Loop
void loop() {
  Blynk.run();
  timer.run();
}
 