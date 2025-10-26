#include "Dobot.h"
String item, s;
int f = 0;
void setup() {
  pinMode(10, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(5, OUTPUT);
  digitalWrite(5, 1);  //设置5号引脚高电平
  Dobot_Init();
  // Dobot_SetHOMECmd();
  Dobot_SetEndEffectorSuctionCup(false);
  Dobot_SetIOMultiplexing(18, IOFunctionDO);
  item = "";
  Serial.begin(9600);
  Serial3.begin(9600);
  Serial.println("item");

  Dobot_SetPTPCmd(MOVJ_XYZ, 200, -15, 70, 0);
}

void loop() {
  Dobot_SetPTPCmd(JUMP_XYZ, 90, -203.0, 18, 0);
  Dobot_SetPTPCmd(MOVJ_XYZ, 90, -203.0, -23, 0);
  while (Serial3.available()) {
    Serial.println(123);
    item = Serial3.readString();
    Serial.println(item);
    // item.trim();
    // for(int i=0;i<item.length();i++){
    //   Serial.print(int(item[i]));
    //   Serial.print(' ');
    // }
    f = 1;
  }
  // if (f == 1) {
  //   if (item == "{\"3-2-001\":\"on\"}") {
  //     Dobot_SetPTPCmd(JUMP_XYZ, 90, -203.0, 18, 0);
  //     Dobot_SetPTPCmd(MOVJ_XYZ, 90, -203.0, -23, 0);
  //     Dobot_SetEndEffectorSuctionCup(true);
  //     Dobot_SetPTPCmd(MOVJ_XYZ, 90, -203.0, 70, 0);
  //     Dobot_SetPTPCmd(JUMP_XYZ, 258, -15, 57, 0);
  //     Dobot_SetEndEffectorSuctionCup(false);
  //     delay(2000);
  //     digitalWrite(5, 0);  //设置5号引脚高电平
  //     Dobot_SetPTPCmd(MOVJ_XYZ, 200, -15, 70, 0);
  //     item = "";
  //   } else if (item == "{\"3-1-002\":\"on\"}") {
  //     Dobot_SetPTPCmd(JUMP_XYZ, 161, -252, 18, 0);
  //     Dobot_SetPTPCmd(MOVJ_XYZ, 161, -252, -23, 0);
  //     Dobot_SetEndEffectorSuctionCup(true);
  //     Dobot_SetPTPCmd(MOVJ_XYZ, 161, -252, 70, 0);
  //     Dobot_SetPTPCmd(JUMP_XYZ, 258, -15, 57, 0);
  //     Dobot_SetEndEffectorSuctionCup(false);
  //     delay(2000);
  //     digitalWrite(5, 0);  //设置5号引脚高电平
  //     Dobot_SetPTPCmd(MOVJ_XYZ, 200, -15, 70, 0);
  //     item = "";
  //   } else if (item == "{\"3-4-003\":\"on\"}") {
  //     Dobot_SetPTPCmd(JUMP_XYZ, -25, -296, 25, 0);
  //     Dobot_SetPTPCmd(MOVJ_XYZ, -25, -296, -23, 0);
  //     Dobot_SetEndEffectorSuctionCup(true);
  //     Dobot_SetPTPCmd(MOVJ_XYZ, -25, -296, 70, 0);
  //     Dobot_SetPTPCmd(JUMP_XYZ, 258, -15, 57, 0);
  //     Dobot_SetEndEffectorSuctionCup(false);
  //     delay(2000);
  //     digitalWrite(5, 0);  //设置5号引脚高电平
  //     Dobot_SetPTPCmd(MOVJ_XYZ, 200, -15, 70, 0);
  //     item = "";
  //   }
  //   f = 0;
  // }

  // if (digitalRead(A2)) {
  //   Dobot_SetPTPCmd(JUMP_XYZ, 90, -203.0, 18, 0);
  //   Dobot_SetPTPCmd(MOVJ_XYZ, 90, -203.0, -23, 0);
  //   Dobot_SetEndEffectorSuctionCup(true);
  //   Dobot_SetPTPCmd(MOVJ_XYZ, 90, -203.0, 70, 0);
  //   Dobot_SetPTPCmd(JUMP_XYZ, 258, -15, 57, 0);
  //   Dobot_SetEndEffectorSuctionCup(false);
  //   delay(2000);
  //   digitalWrite(5, 0);  //设置5号引脚高电平
  //   Dobot_SetPTPCmd(MOVJ_XYZ, 200, -15, 70, 0);
  //   item = "";
  // }
  // if (digitalRead(A1)) {
  //   Dobot_SetPTPCmd(JUMP_XYZ, 161, -252, 18, 0);
  //   Dobot_SetPTPCmd(MOVJ_XYZ, 161, -252, -23, 0);
  //   Dobot_SetEndEffectorSuctionCup(true);
  //   Dobot_SetPTPCmd(MOVJ_XYZ, 161, -252, 70, 0);
  //   Dobot_SetPTPCmd(JUMP_XYZ, 258, -15, 57, 0);
  //   Dobot_SetEndEffectorSuctionCup(false);
  //   delay(2000);
  //   digitalWrite(5, 0);  //设置5号引脚高电平
  //   Dobot_SetPTPCmd(MOVJ_XYZ, 200, -15, 70, 0);
  //   item = "";
  // }
  // if (digitalRead(A3)) {
  //   Dobot_SetPTPCmd(JUMP_XYZ, -25, -296, 25, 0);
  //   Dobot_SetPTPCmd(MOVJ_XYZ, -25, -296, -23, 0);
  //   Dobot_SetEndEffectorSuctionCup(true);
  //   Dobot_SetPTPCmd(MOVJ_XYZ, -25, -296, 70, 0);
  //   Dobot_SetPTPCmd(JUMP_XYZ, 258, -15, 57, 0);
  //   Dobot_SetEndEffectorSuctionCup(false);
  //   delay(2000);
  //   digitalWrite(5, 0);  //设置5号引脚高电平
  //   Dobot_SetPTPCmd(MOVJ_XYZ, 200, -15, 70, 0);
  //   item = "";
  // }
  // if (digitalRead(10) == 0) {
  //   digitalWrite(5, 1);  //设置5号引脚高电平
  // }
}