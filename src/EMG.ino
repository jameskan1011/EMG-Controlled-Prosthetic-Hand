#include <esp_now.h>
#include <WiFi.h>
#include <ESP32Servo.h>

// MAC of sender device
uint8_t senderMAC[] = {0x58, 0xBF, 0x25, 0xA1, 0x44, 0x90};

// Pins
int servoPins[5] = {5, 6, 7, 8, 9};
#define FSR_PIN_1 0
#define FSR_PIN_2 1
#define FSR_PIN_3 2
#define FSR_PIN_4 3
#define FSR_PIN_5 4

Servo servos[5];

// Servo position control
uint8_t currentPositions[5] = {180, 180, 180, 180, 180};  // Initial
uint8_t targetPositions[5] = {90, 90, 90, 90, 90};   // Updated on receive
unsigned long lastUpdateTime = 0;
const unsigned long updateInterval = 5; // ms between servo steps

bool motorFlag = false;
esp_now_peer_info_t peerInfo;

// Callback: when data received
void OnDataRecv(const esp_now_recv_info *info, const uint8_t *data, int len) {
  if (len == sizeof(targetPositions)) {  // Fix: match real array
    memcpy(targetPositions, data, sizeof(targetPositions));  // Update targets

    Serial.print("[");
    for (int i = 0; i < 5; i++) {
      Serial.print(targetPositions[i]);
      if (i < 4) Serial.print(" ");
    }
    Serial.println("]");
  } else {
    Serial.println("Received data size mismatch!");
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  analogReadResolution(10);

  // Attach servos
  for (int i = 0; i < 5; i++) {
    servos[i].setPeriodHertz(50);
    servos[i].attach(servoPins[i], 500, 2400);
    servos[i].write(currentPositions[i]); // Set to initial position
  }

  // Initialize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init failed");
    return;
  }

  memcpy(peerInfo.peer_addr, senderMAC, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  unsigned long currentTime = millis();

  // Smooth servo movement
  if (currentTime - lastUpdateTime >= updateInterval) {
    lastUpdateTime = currentTime;

    for (int i = 0; i < 5; i++) {
      if (currentPositions[i] != targetPositions[i]) {
        currentPositions[i] += (currentPositions[i] < targetPositions[i]) ? 1 : -1;
        servos[i].write(currentPositions[i]);
      }
    }
  }

  // Read FSRs
  int fsr1 = analogRead(FSR_PIN_1);
  int fsr2 = analogRead(FSR_PIN_2);
  int fsr3 = analogRead(FSR_PIN_3);
  int fsr4 = analogRead(FSR_PIN_4);
  int fsr5 = analogRead(FSR_PIN_5);


  // Motor flag logic
  motorFlag = (fsr1 > 100 || fsr2 > 100 || fsr3 < 100 || fsr4 > 100 || fsr5 > 100);
  esp_now_send(senderMAC, (uint8_t *)&motorFlag, sizeof(motorFlag));

}
