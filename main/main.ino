#include <I2CEncoder.h>
#include <Wire.h>
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

  vTranslate(255);
  delay(1000);
  hTranslate(255);
  delay(1000);
  vTranslate(-255);
  delay(1000);
  hTranslate(-255);
  delay(1000);

}

void vTranslate(int power) {
  topLeft.write(power);
  topRight.write(power);
  botLeft.write(power);
  botRight.write(power);
}

void hTranslate(int power) {
  topLeft.write(power);
  topRight.write(-power);
  botLeft.write(-power);
  botRight.write(power);
}

void halt() {
  topLeft.write(0);
  topRight.write(0);
  botLeft.write(0);
  botRight.write(0);
}

void rotate(int power) {
  topLeft.write(power);
  topRight.write(-power);
  botLeft.write(power);
  botRight.write(-power);
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
