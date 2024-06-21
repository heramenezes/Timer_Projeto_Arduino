#include <SoftwareSerial.h>
#include <Servo.h>

Servo serv;
#define pot A0
#define led 4
#define but 3
#define mot 2
#define buzzer 7
#define max 0
#define min 180

void setup(){
  pinMode(led, OUTPUT);
  pinMode(but, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  serv.attach(mot);
  serv.write(90);
  Serial.begin(9600);
}

void alarm(){
  tone(buzzer, 1500);
  digitalWrite(led, HIGH);
  delay(2000);
  noTone(buzzer);
  digitalWrite(led, LOW);
}

void loop(){
  serv.write(min);
  while(digitalRead(but)==HIGH);
  double time = analogRead(pot) / 17.05;  
  double startTime = time;
  while(time>0.1){
    delay(1000);
    serv.write(180 * (time/startTime));
    time--;
    Serial.println(time);
  }
  serv.write(max);
  alarm();
}