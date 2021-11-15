//#include <I2CEncoder.h>
//#include <Wire.h>
#include <Servo.h>
#include <vexMotor.h>

vexMotor topLeft;
vexMotor topRight;
vexMotor botLeft;
vexMotor botRight;

const int TLpin = 9;
const int TRpin = 10;
const int BLpin = 11;
const int BRpin = 13;

const int ThreshTL = 5;
const int ThreshTR = 5;
const int ThreshBL = 5;
const int ThreshBR = 5;

void setup() {
  topLeft.attach(TLpin);
  topRight.attach(TRpin);
  botLeft.attach(BLpin);
  botRight.attach(BRpin);

  setMotorPulse();
  setMotorThreshold();

  delay(5000);
}

void loop() {
  figure8(10);
  delay(500);
}

int x;
int y;
void figure8(int t) {
  // int x;
  // for (x = 0; x <= 255; x++)
  //   moveTime(x, findY(x, -1), 0, t);
  // for (x = 255; x >= 0; x--)
  //   moveTime(x, findY(x, 1), 0, t);
  // for (x = 0; x >= -255; x--)
  //   moveTime(x, findY(x, -1), 0, t);
  // for (x = -255; x <= 0; x++)
  //   moveTime(x, findY(x, 1), 0, t);
  // delay(750);

  //Bottom Right
  for (x = 255, y = findY(1); x >= 0; x--, y = findY(1))
    moveTime(x, y, 0, t);
  halt();
  for (x = 0, y = findY(1); x >= -255; x--, y = findY(1))
    moveTime(x, y, 0, t);
  halt();

  //Top Left
  for (x = -255, y = findY(1); x <= 0; x++, y = findY(1))
    moveTime(x, y, 0, t);
  halt();
  for (x = 0, y = findY(1); x <= 255; x++, y = findY(1))
    moveTime(x, y, 0, t);
  halt();

  //Top Right
  for (x = 255, y = findY(-1); x >= 0; x--, y = findY(-1))
    moveTime(x, y, 0, t);
  halt();
  for (x = 0, y = findY(-1); x >= -255; x--, y = findY(-1))
    moveTime(x, y, 0, t);
  halt();

  //Bottom Left
  for (x = -255, y = findY(-1); x <= 0; x++, y = findY(-1))
    moveTime(x, y, 0, t);
  halt();
  for (x = 0, y = findY(-1); x <= 255; x++, y = findY(-1))
    moveTime(x, y, 0, t);
  halt();
}

int findY(int a) {
  return (int)(a * sqrt(65025 - sq(x)));
}

void moveTime(int x, int y, int r, int milli) {
  move(x, y, r);
  delay(milli);
}

void move(int x, int y, int r) {
  topLeft.write(x + y + r);
  topRight.write(x - y - r);
  botLeft.write(x - y + r);
  botRight.write(x + y - r);
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
  topLeft.setMinPulse(1000);
  topLeft.setNeutralPulse(1500);
  topLeft.setMaxPulse(2000);

  topRight.setMinPulse(1000);
  topRight.setNeutralPulse(1500);
  topRight.setMaxPulse(2000);

  botLeft.setMinPulse(1000);
  botLeft.setNeutralPulse(1500);
  botLeft.setMaxPulse(2000);

  botRight.setMinPulse(1000);
  botRight.setNeutralPulse(1500);
  botRight.setMaxPulse(2000);
}
