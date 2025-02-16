// Define Blynk Device
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6y3sAbdir"
#define BLYNK_TEMPLATE_NAME "EnvironmentSensor"
#define BLYNK_AUTH_TOKEN "Q7Qi6MMES3vZhd6a_YsglmxjRbbAr6dN"

// Define AP Wifi
char ssid[] = "Hoi Dong 5";
char pass[] = "kvt1ptit";

// Libraries
#include <BlynkSimpleEsp8266.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Define DHT11 Sensor
#define DHTTYPE DHT11
#define DHTPIN D1
DHT dht(DHTPIN, DHTTYPE);

// GPIO
int Yellow = D5;
int Red = D6;

uint32_t startTick, t ,h, l; 

void setup() {
  Serial.begin(9600);
  pinMode(Yellow, OUTPUT);
  pinMode(Red, OUTPUT);
  dht.begin();
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  startTick = millis();
}

BLYNK_WRITE(V3){
  int value = param.asInt();
  digitalWrite(Yellow, value);
  Blynk.virtualWrite(V3, digitalRead(Yellow));
}

BLYNK_WRITE(V4){
  int value = param.asInt();
  digitalWrite(Red, value);
  Blynk.virtualWrite(V4, digitalRead(Red));
}

void loop() {
  Blynk.run();
  if(millis() - startTick >= 1000){
    startTick = millis();
    h = dht.readHumidity();
    t = dht.readTemperature();
    l = analogRead(A0);
    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
    else{
      Serial.println("Temp: " + String(t) + "°C");
      Serial.println("Hum: " + String(h) + "%");
      Blynk.virtualWrite(V0, t);
      Blynk.virtualWrite(V1, h);
    }
    Serial.println("Light: " + String(l) + "LUX");
    Blynk.virtualWrite(V2, l);
  }
}
