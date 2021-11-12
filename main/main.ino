//#include <I2CEncoder.h>
//#include <Wire.h>
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

void setup() {

  topLeft.attach(TLpin);
  topRight.attach(TRpin);
  botLeft.attach(BLpin);
  botRight.attach(BRpin);

  setMotorPulse();
  setMotorThreshold();

}

void loop() {

  figure8(10);
  
}

void figure8(int t) {
  int x;
  for (x = 0; x <= 255; x++)
    moveTime(x, findY(x, -1), 0, t);
  for (x = 255; x >= 0; x--)
    moveTime(x, findY(x, 1), 0, t);
  for (x = 0; x >= -255; x--)
    moveTime(x, findY(x, -1), 0, t);
  for (x = -255; x <= 0; x++)
    moveTime(x, findY(x, 1), 0, t);
  delay(750);
}

int findY(int x, int a) {
  return (int)(a * sqrt(-1 * ((pow(x, 4) - (65025 * sq(x))) / 65025)));
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