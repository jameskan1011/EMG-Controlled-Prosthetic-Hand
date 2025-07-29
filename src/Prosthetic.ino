#include <esp_now.h>
#include <WiFi.h>

#define SAMPLE_RATE 1000

#define INPUT_PIN_1 34
#define INPUT_PIN_2 35

#define DETECT_PIN_1 17
#define DETECT_PIN_2 16

#define MOTOR_PIN 27

#define BUFFER_SIZE 128
#define NUM_SERVOS 5

uint8_t servoAngles[NUM_SERVOS] = {180, 180, 180, 180, 180};
const int thresholds[2] = {20, 20};  // Sensor 1 and Sensor 2

int circular_buffer[2][BUFFER_SIZE];
int data_index[2] = {0};
int sum[2] = {0};

bool motorFlag = false;

uint8_t receiverMAC[] = {0xDC, 0x06, 0x75, 0x67, 0x62, 0xB8};  // Replace with your receiver MAC
esp_now_peer_info_t peerInfo;

struct FilterState {
  float z1[4] = {0}, z2[4] = {0};
};
FilterState filterStates[2];  // Only two sensors

void OnDataRecv(const esp_now_recv_info *info, const uint8_t *data, int len) {
  if (len == sizeof(bool)) {
    motorFlag = *data;
    digitalWrite(MOTOR_PIN, motorFlag ? HIGH : LOW);
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  pinMode(MOTOR_PIN, OUTPUT);
  digitalWrite(MOTOR_PIN, LOW);

  pinMode(DETECT_PIN_1, INPUT);
  pinMode(DETECT_PIN_2, INPUT);

  analogReadResolution(10);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init failed");
    return;
  }

  memcpy(peerInfo.peer_addr, receiverMAC, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  static unsigned long lastMicros = 0;
  unsigned long currentMicros = micros();

  if (currentMicros - lastMicros >= 1000000 / SAMPLE_RATE) {
    lastMicros = currentMicros;

    int value1 = readSensor(INPUT_PIN_1, DETECT_PIN_1, thresholds[0], 0);
    int value2 = readSensor(INPUT_PIN_2, DETECT_PIN_2, thresholds[1], 1);
    //Serial.print(value1);
    //Serial.println(value2);

    if (value1 >= thresholds[0]) {
      // Sensor 1 active → move all 5 servos
      for (int i = 0; i < NUM_SERVOS; i++) {
        servoAngles[i] = 0;
      }
    } else if (value2 >= thresholds[1]) {
      // Sensor 2 active → move servo 0 and 1
      servoAngles[0] = 0;
      servoAngles[1] = 0;
      for (int i = 2; i < NUM_SERVOS; i++) {
        servoAngles[i] = 180;
      }
    } else {
      // No trigger → default positions
      for (int i = 0; i < NUM_SERVOS; i++) {
        servoAngles[i] = 180;
      }
    }

    esp_now_send(receiverMAC, (uint8_t *)servoAngles, sizeof(servoAngles));

    Serial.print("[");
    for (int i = 0; i < NUM_SERVOS; i++) {
      Serial.print(servoAngles[i]);
      if (i < NUM_SERVOS - 1) Serial.print(" ");
    }
    Serial.println("]");
  }
}

int readSensor(int inputPin, int detectPin, int threshold, int index) {
  if (digitalRead(detectPin) == HIGH) {
    int raw = analogRead(inputPin);
    int filtered = Filter(raw, filterStates[index]);
    int envelope = getEnvelop(index, abs(filtered));
    return envelope;
  }
  return 0;
}

int getEnvelop(int index, int value) {
  sum[index] -= circular_buffer[index][data_index[index]];
  sum[index] += value;
  circular_buffer[index][data_index[index]] = value;
  data_index[index] = (data_index[index] + 1) % BUFFER_SIZE;
  return (sum[index] / BUFFER_SIZE) * 2;
}

float Filter(float input, FilterState &state) {
  float output = input;
  {
    float x = output - (-0.55195385 * state.z1[0]) - (0.60461714 * state.z2[0]);
    output = 0.00223489 * x + (0.00446978 * state.z1[0]) + (0.00223489 * state.z2[0]);
    state.z2[0] = state.z1[0];
    state.z1[0] = x;
  }
  {
    float x = output - (-0.86036562 * state.z1[1]) - (0.63511954 * state.z2[1]);
    output = 1.0 * x + (2.0 * state.z1[1]) + (1.0 * state.z2[1]);
    state.z2[1] = state.z1[1];
    state.z1[1] = x;
  }
  {
    float x = output - (-0.37367240 * state.z1[2]) - (0.81248708 * state.z2[2]);
    output = 1.0 * x + (-2.0 * state.z1[2]) + (1.0 * state.z2[2]);
    state.z2[2] = state.z1[2];
    state.z1[2] = x;
  }
  {
    float x = output - (-1.15601175 * state.z1[3]) - (0.84761589 * state.z2[3]);
    output = 1.0 * x + (-2.0 * state.z1[3]) + (1.0 * state.z2[3]);
    state.z2[3] = state.z1[3];
    state.z1[3] = x;
  }
  return output;
}
