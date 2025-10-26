#include <Ultrasonic.h>

Ultrasonic ultrasonic(4, 3);
int f=0,g=0;
int distance;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial3.begin(115200);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  digitalWrite(11, 1);
  delay(1500);
  digitalWrite(11, 0);
}

void loop() {
  // put your main code here, to run repeatedly:

  distance = ultrasonic.read();
  // Serial.println(analogRead(A0));
  // Serial.println(distance);
  analogWrite(8, 255);
  while (Serial3.available()) {
    String s=Serial3.readString();
    s.trim();
    // Serial.println(s);
    if(s[8]=='u') f=1,digitalWrite(9, 1),delay(2500),digitalWrite(9, 0);
    else if(s[8]=='d')f=2,digitalWrite(10, 1),delay(2500),digitalWrite(10, 0);
    // else if(s[8]=='o')f=0,digitalWrite(9, 0),digitalWrite(10, 0);
    else if(s[8]=='1'){
      distance = ultrasonic.read();
      int v1=analogRead(A0);
      String s1="tn1.val="+String(v1);
      String s2="tn0.val="+String(distance);
      Serial3.println(s1);
      Serial3.println(s2);
    }
  }
  if(distance<65)tone(7, 2000);
  else noTone(7);
  if(analogRead(A0)>800)analogWrite(8, 10);
  else if(analogRead(A0)>400 and analogRead(A0)<=800)analogWrite(8, 100);
  else analogWrite(8, 255);
  // delay(3000);
  // analogWrite(8, 50);
  // delay(3000);
  // analogWrite(8, 5);
  // delay(3000);
  // analogWrite(8, 0);
  // delay(3000);
  // digitalWrite(9, 1);
  // delay(3000);
  // digitalWrite(9, 0);
  // delay(1000);
  // digitalWrite(10, 1);
  // delay(3000);
  // digitalWrite(10, 0);
  // delay(1000);
}
