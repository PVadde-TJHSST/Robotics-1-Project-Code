#include <I2CEncoder.h>
#include <Wire.h>
#include <Servo.h>
#include <vexMotor.h>

vexMotor topLeft;
vexMotor topRight;
vexMotor botLeft;
vexMotor botRight;

const int TLpin = 9; //White
const int TRpin = 10; //Blue
const int BLpin = 11; //Yellow
const int BRpin = 13; //Pink

const int minP = 1000;
const int neuP = 1500;
const int maxP = 2000;

const int ThreshTL = 5;
const int ThreshTR = 5;
const int ThreshBL = 5;
const int ThreshBR = 5;

String XBeeIn;

int contX = 255;
int contY = 255;
int contR = 255;

void setup() {

  topLeft.attach(TLpin);
  topRight.attach(TRpin);
  botLeft.attach(BLpin);
  botRight.attach(BRpin);

  setMotorPulse();
  setMotorThreshold();

  Serial.begin(57600);

}

void loop() {
  readXBee();
  move(contX, contY, contR);
}

//void figure8Test(int t) {
//  moveTime(0, 255, 0, t);
//  moveTime(255, 0, 0, t);
//  moveTime(0, -255, 0, t);
//  moveTime(-255, 0, 0, t);
//  moveTime(0, -255, 0, t);
//  moveTime(255, 0, 0, t);
//  moveTime(0, 255, 0, t);
//  moveTime(-255, 0, 0, t);
//}

void moveTime(int x, int y, int r, int milli) {
  move(x, y, r);
  delay(milli);
  halt();
}

void move(int x, int y, int r) {
  topLeft.write(x + y - r);
  topRight.write(x - y + r);
  botLeft.write(x - y - r);
  botRight.write(x + y + r);
}

void halt() {
  topLeft.write(0);
  topRight.write(0);
  botLeft.write(0);
  botRight.write(0);
}

void setMotorThreshold() {
  topLeft.setDeadBand(ThreshTL);
  topRight.setDeadBand(ThreshTR);
  botLeft.setDeadBand(ThreshBL);
  botRight.setDeadBand(ThreshBR);
}

void setMotorPulse() {
  topLeft.setMinPulse(minP);
  topLeft.setNeutralPulse(neuP);
  topLeft.setMaxPulse(maxP);

  topRight.setMinPulse(minP);
  topRight.setNeutralPulse(neuP);
  topRight.setMaxPulse(maxP);

  botLeft.setMinPulse(minP);
  botLeft.setNeutralPulse(neuP);
  botLeft.setMaxPulse(maxP);

  botRight.setMinPulse(minP);
  botRight.setNeutralPulse(neuP);
  botRight.setMaxPulse(maxP);
}

void readXBee() {
  if (Serial.available() > 0) {
    XBeeIn = Serial.readStringUntil('@');
    int c = 1;
    for (int i = XBeeIn.indexOf("/"); i != -1; i = XBeeIn.indexOf("/")) {
      s: switch (c) {
        case 1:
          contX = XBee.substring(0, i).toInt();
          break s;
        case 2:
          contY = XBee.substring(0, i).toInt();
          break s;
        case 3:
          contR = XBee.substring(0, i).toInt();
          break s;
        default:
          break s;
      }
      c++;
      XBeeIn = XBeeIn.substring(i);
    }
  }
  
}
