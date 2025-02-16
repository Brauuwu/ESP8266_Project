#include <ESP8266WiFi.h>
#include <DHT.h>
#include <ThingsBoard.h>
#include <Arduino_MQTT_Client.h>

#define DHTPIN D2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define SSID "Hoi Dong 5"
#define PASS "kvt1ptit"

#define TB_SERVER "thingsboard.cloud"
#define TOKEN "IAsTxZ9uOlmUz1MkWwIk"

constexpr uint16_t MAX_MESSAGE_SIZE = 128U;

WiFiClient espClient;
Arduino_MQTT_Client mqttClient(espClient);
ThingsBoard tb(mqttClient, MAX_MESSAGE_SIZE);

void connectToWiFi() {
  Serial.println("Connecting to WiFi...");
  WiFi.begin(SSID, PASS);
  int attempts = 0;
  
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\nFailed to connect to WiFi.");
  } else {
    Serial.println("\nConnected to WiFi");
  }
}

void connectToThingsBoard() {
  if (!tb.connected()) {
    Serial.println("Connecting to ThingsBoard server");
    
    if (!tb.connect(TB_SERVER, TOKEN)) {
      Serial.println("Failed to connect to ThingsBoard");
    } else {
      Serial.println("Connected to ThingsBoard");
    }
  }
}

void sendDataToThingsBoard(float t, int h) {
  tb.sendTelemetryData("temperature", t);
  tb.sendTelemetryData("humidity", h);
  if(tb.connected()) Serial.println("Data sent");
}

void setup() {
  Serial.begin(9600);
  dht.begin();
  connectToWiFi();
  connectToThingsBoard();
}

void loop() {
  tb.loop();
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if(isnan(h) || isnan(t)){
    Serial.println("DHT11 sensor timed out!");
  }
  else{
    Serial.println(String(t) + " " + String(h));
  }
  sendDataToThingsBoard(t, h);
  delay(1000);
}
