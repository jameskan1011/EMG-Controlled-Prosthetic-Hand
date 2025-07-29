# EMG-Controlled-Prosthetic-Hand

This project features a wireless prosthetic hand system powered by EMG signal control. A wearable glove captures muscle activity and translates it into movement commands for a robotic hand. At the same time, force sensors on the robotic fingers detect contact pressure and send feedback signals wirelessly, activating a vibration motor on the glove. The entire bidirectional communication is handled efficiently using the ESP-NOW protocol.

---

## 📽️ Demonstration

> Example:  
> <video src="media/demo-glove.webm" autoplay loop muted playsinline width="600"></video>

---

## 🎯 Project Objectives

- Design and implement a wearable glove for teleoperation.
- Read EMG muscle signals to control servos on a robotic hand.
- Detect force from FSR sensors and provide real-time vibration feedback.
- Use ESP-NOW protocol for low-latency wireless communication.

---

## 🧰 System Overview

### 🔁 Bidirectional Communication:

| Sender (Glove)                      | Receiver (Robotic Hand)                |
|------------------------------------|----------------------------------------|
| EMG signal processing              | Servo control (5 channels)            |
| Detect pins convert gestures       | FSR sensors monitor contact force     |
| Sends servo angles via ESP-NOW     | Sends force flags via ESP-NOW         |
| Vibration motor triggered by FSR   | Real-time feedback loop               |

### 👇 Hardware Components:

- **ESP32 SuperMini (x2)**
- **EMG Muscle Sensor (4 channels)**
- **FSR Force Sensors (5 units)**
- **Vibration Motor**
- **Servos (5x SG90 or MG90s)**
- **Glove platform**

---

## 🧠 Features

- **Gesture Recognition:** EMG + digital detect pins convert muscle activity into finger movements.
- **Wireless Feedback:** Robotic hand returns force data, triggering vibration motor on glove.
- **Real-Time Response:** ESP-NOW ensures low-latency two-way control.
- **Scalable Design:** Easily adaptable to full robotic arms or VR-based systems.

---

## 🧪 Testing & Results

- **Latency:** Less than 100ms round-trip delay.
- **Accuracy:** Consistent mapping of EMG gestures to servo positions.
- **Robustness:** Maintained stable communication within 5 meters indoors.

---

## 🗺️ Folder Structure

