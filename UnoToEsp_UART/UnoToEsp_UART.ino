#include <SoftwareSerial.h>
#define RX_PIN 10
#define TX_PIN 11
SoftwareSerial mySerial(RX_PIN, TX_PIN);

int Red_LED = 2;
int Yellow_LED = 3;
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.println("ESP8266 UNO UART Communication Test");
  pinMode(Red_LED, OUTPUT);
  pinMode(Yellow_LED, OUTPUT);
}
void Red(){
  digitalWrite(Red_LED, HIGH);
  digitalWrite(Yellow_LED, LOW);
}
void Yellow(){
  digitalWrite(Red_LED, LOW);
  digitalWrite(Yellow_LED, HIGH);
}
void All(){
  digitalWrite(Red_LED, HIGH);
  digitalWrite(Yellow_LED, HIGH);
}
void Off(){
  digitalWrite(Red_LED, LOW);
  digitalWrite(Yellow_LED, LOW);
}
void loop() {
  if(mySerial.available()){
    char c = mySerial.read();
    if(c=='R'){
      Serial.println("Received Data (RED) complete!");
      Serial.println("Red LED is on");
      Red();
    }
    if(c=='Y'){
      Serial.println("Received Data (YELLOW) complete!");
      Serial.println("Yellow LED is on");
      Yellow();
    }
    if(c=='A'){
      Serial.println("Received Data (ALL) complete!");
      Serial.println("All LEDs are on");
      All();
    }
    if(c=='O'){
      Serial.println("Received Data (OFF) complete!");
      Serial.println("All LED are off");
      Off();
    }
  }
}