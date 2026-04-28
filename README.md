# 🏠 ESP32 Smart Home Automation System

A complete IoT-based Smart Home System built using **ESP32**, integrated with multiple sensors and controlled via the **Blynk mobile app**.

This project enhances home safety and automation by detecting **fire, rain, and motion**, and responding with alerts, alarms, and automated actions.

---

## 🚀 Features

* 🔥 **Fire Detection System**

  * Detects flame using a flame sensor
  * Activates buzzer and LED alert
  * Sends real-time notification to Blynk app

* 🌧️ **Rain Detection System**

  * Detects rain using analog rain sensor
  * Triggers buzzer (low tone) and LED
  * Displays rain status on Blynk dashboard

* 🚶 **Motion Detection + Smart Door**

  * PIR sensor detects motion
  * Automatically opens door using servo motor
  * LED indication for motion detection

* 📱 **Blynk App Integration**

  * Remote monitoring
  * Manual control of:

    * Door (Servo Motor)
    * LED
  * Real-time sensor updates

---

## 🛠️ Components Used

* ESP32 Microcontroller
* Flame Sensor
* Rain Sensor (Analog)
* PIR Motion Sensor
* Servo Motor
* Buzzers (2x)
* LEDs
* Jumper Wires

---

## ⚙️ Pin Configuration

| Component    | ESP32 Pin   |
| ------------ | ----------- |
| Flame Sensor | 27          |
| Fire Buzzer  | 12          |
| Fire LED     | 13          |
| Rain Sensor  | 34 (Analog) |
| Rain Buzzer  | 26          |
| Rain LED     | 25          |
| PIR Sensor   | 4           |
| Servo Motor  | 14          |
| PIR LED      | 21          |

---

## 📲 Blynk Virtual Pins

| Function         | Virtual Pin |
| ---------------- | ----------- |
| Fire Alert       | V0          |
| LED Control      | V1          |
| Door Control     | V2          |
| Rain Status      | V3          |
| Motion Detection | V5          |

---

## 🔧 Setup Instructions

1. Clone the repository:

   ```bash
   git clone https://github.com/your-username/ESP32-Smart-Home-Automation.git
   ```

2. Open the project in **Arduino IDE**

3. Install required libraries:

   * Blynk
   * ESP32Servo

4. Update your credentials:

   ```cpp
   char ssid[] = "YOUR_WIFI_NAME";
   char pass[] = "YOUR_WIFI_PASSWORD";
   ```

5. Add your Blynk Auth Token

6. Upload code to ESP32

---

## 📊 How It Works

* Sensors continuously send data to ESP32
* ESP32 processes conditions:

  * Fire → High alert (buzzer + LED)
  * Rain → Low alert (buzzer + LED)
  * Motion → Door opens automatically
* Data is synced with Blynk in real-time

---

## 📸 Future Improvements

* 📱 Mobile app UI enhancement
* 🌍 Cloud data logging
* 📷 Camera integration
* 🔒 Face recognition door system
* 🧠 AI-based smart automation

---

## 👨‍💻 Author

**Roshan Khatri**

---

## ⭐ Give a Star!

If you like this project, don't forget to star ⭐ the repository!
