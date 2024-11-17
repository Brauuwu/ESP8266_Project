#include <SoftwareSerial.h>
#define RX_PIN 4
#define TX_PIN 5
SoftwareSerial mySerial(RX_PIN, TX_PIN);
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.println("ESP8266 UNO UART Communication Test");
}

void loop() {
  if(Serial.available()){
    char c = Serial.read();
    mySerial.write(c);
    if(c=='R'){
      Serial.println("Sent Data (RED) complete!");
      Serial.println("Red LED is on");
    }
    if(c=='Y'){
      Serial.println("Sent Data (YELLOW) complete!");
      Serial.println("Yellow LED is on");
    }
    if(c=='A'){
      Serial.println("Sent Data (ALL) complete!");
      Serial.println("All LEDs are on");
    }
    if(c=='O'){
      Serial.println("Sent Data (OFF) complete!");
      Serial.println("All LED are off");
    }
  }
}
