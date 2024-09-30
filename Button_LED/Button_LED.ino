#define BLYNK_PRINT Serial

/* Fill in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL6YDHJ6tqf"
#define BLYNK_TEMPLATE_NAME "LED"
#define BLYNK_AUTH_TOKEN "Eyo_GRlf3vxDDc8ptJ6bYPMR_M8O0305"


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "P403";
char pass[] = "987654321";
//GPIO
int R=D1;
int Y=D2;
int bt1=D5;
int bt2=D6;
int R_state=HIGH;
int Y_state=HIGH;

void setup() {
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  pinMode(R,OUTPUT);
  pinMode(Y,OUTPUT);
  pinMode(bt1,INPUT_PULLUP);
  pinMode(bt2,INPUT_PULLUP);
}
BLYNK_WRITE(V1){
  int value = param.asInt();
  digitalWrite(R,value);
  Blynk.virtualWrite(V0,digitalRead(R));
}
BLYNK_WRITE(V3){
  int value = param.asInt();
  digitalWrite(Y,value);
  Blynk.virtualWrite(V2,digitalRead(Y));
}
void loop() {
  Blynk.run();
  if(digitalRead(bt1)==0){
    delay(200);
    if(R_state){
      digitalWrite(R,!digitalRead(R));
      Blynk.virtualWrite(V0,digitalRead(R));
      Blynk.virtualWrite(V1,digitalRead(R));
      R_state=LOW;
    }
  }
  else R_state=HIGH;
  if(digitalRead(bt2)==0){
    delay(200);
    if(Y_state){
      digitalWrite(Y,!digitalRead(Y));
      Blynk.virtualWrite(V2,digitalRead(Y));
      Blynk.virtualWrite(V3,digitalRead(Y));
      Y_state=LOW;
    }
  }
  else Y_state=HIGH;
}
