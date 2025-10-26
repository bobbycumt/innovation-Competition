#include <MPU6050_tockn.h>
#include <Wire.h>

MPU6050 mpu6050(Wire);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  digitalWrite(11, 1);
  delay(1500);
  digitalWrite(11, 0);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

}

void loop() {
  // put your main code here, to run repeatedly:
  mpu6050.update();
  Serial.print(mpu6050.getAccX());
  Serial.print('\t');
  Serial.print(mpu6050.getAccY());
  Serial.print('\t');
  Serial.println(mpu6050.getAccZ());
  delay(1000);
}
