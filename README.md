# EMG-Controlled Prosthetic Hand

This project features a **wireless prosthetic hand system** powered by EMG signal control.  
A wearable EMG device captures muscle activity and translates it into movement commands for a robotic hand.  
Force sensors on the robotic fingers detect contact pressure and send feedback wirelessly to activate a **vibration motor** on the glove.  
All communication is handled efficiently via the **ESP-NOW protocol** for real-time response.

---

## 🖐️ Prosthetic Hand

<p align="center">
  <img width="400" alt="Prosthetic Hand" src="https://github.com/user-attachments/assets/3f7c741d-932a-406e-aa4f-482295ec2772" />
</p>

---

## 🧤 EMG Sensor Device

<p align="center">
  <img width="300" alt="EMG Sensor Glove Front" src="https://github.com/user-attachments/assets/8de45357-c73d-4ae2-bb90-283512019173" />
  &nbsp;&nbsp;&nbsp;
  <img width="300" alt="EMG Sensor Glove Back" src="https://github.com/user-attachments/assets/22d92ef4-f10d-440e-9ab8-04a788641ba1" />
</p>

---

## 📽️ Demonstration


<p align="center">
  <video src="https://github.com/user-attachments/assets/7f13d15d-7b53-4090-8c28-4c555c97ecc5" autoplay loop muted playsinline width="100"></video>
</p>


**Grasping Objects using Pinch and Power Grip**


<p align="center">
  <img width="700" alt="Grasp Demo" src="https://github.com/user-attachments/assets/c35c996a-1444-4b48-808f-dfc08860345b" />
</p>


---

## 🧠 Features
<h3 align="center">Sensor Feedback</h3>

<p align="center">
  <img src="https://github.com/user-attachments/assets/780776b2-6f83-41ed-af58-4b2ff6226d09" width="350" />
  &nbsp;&nbsp;&nbsp;
  <img src="https://github.com/user-attachments/assets/b8394736-d9b1-4a1b-b97f-0292cb9dd101" width="350" />
</p>
![photo_2025-04-25_01-53-26](https://github.com/user-attachments/assets/56d0cb88-ba74-4a7c-ac9e-b05377ec0a86)

- **Pinch and Power Grip Control:** Specific EMG signals trigger predefined hand movements — either pinch or power grip — based on which sensor is activated.
- **Wireless Haptic Feedback:** FSR sensors on the prosthetic fingers detect contact force and activate a vibration motor on the wearable in real-time.
- **Low-Latency Communication:** ESP-NOW enables fast, two-way communication between the wearable and robotic hand without needing a Wi-Fi network.
- **Compact and Lightweight:** Designed for wearable use, the system minimizes bulk and weight for user comfort and mobility.

