# EMG-Controlled-Prosthetic-Hand

This project features a wireless prosthetic hand system powered by EMG signal control. A wearable glove captures muscle activity and translates it into movement commands for a robotic hand. At the same time, force sensors on the robotic fingers detect contact pressure and send feedback signals wirelessly, activating a vibration motor on the glove. The entire bidirectional communication is handled efficiently using the ESP-NOW protocol.

---
Prosthetic Hand
<img width="577" height="682" alt="image" src="https://github.com/user-attachments/assets/3f7c741d-932a-406e-aa4f-482295ec2772" />

EMG Sensor Device
<img width="544" height="589" alt="image" src="https://github.com/user-attachments/assets/8de45357-c73d-4ae2-bb90-283512019173" />
<img width="472" height="501" alt="image" src="https://github.com/user-attachments/assets/22d92ef4-f10d-440e-9ab8-04a788641ba1" />

## 📽️ Demonstration

> Grasping Objects using Pinch and Power Grip:  
> <img width="856" height="545" alt="image" src="https://github.com/user-attachments/assets/c35c996a-1444-4b48-808f-dfc08860345b" />


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

