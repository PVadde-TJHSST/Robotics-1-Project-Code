//#include <I2CEncoder.h>
//#include <Wire.h>
#include <Servo.h>
#include <vexMotor.h>

vexMotor topLeft;
vexMotor topRight;
vexMotor botLeft;
vexMotor botRight;

const int TLpin = 7;
const int TRpin = 11;
const int BLpin = 8;
const int BRpin = 10;

const int Thresh = 5;

int c = 1;
int val;

void setup() {
  topLeft.attach(TLpin);
  topRight.attach(TRpin);
  botLeft.attach(BLpin);
  botRight.attach(BRpin);

  setMotorPulse();
  setMotorThreshold();

  pinMode(2, INPUT);
  pinMode(12, OUTPUT);
  pinMode(A0, OUTPUT);

  Serial.begin(9600);

  delay(5000);
}

void loop() {
  //Digital
//  val = digitalRead(2);
//  if (val == 0) {
//    move(0, 255, 0);
//  } else if (val == 1) {
//    if (c == 3) {
//      digitalWrite(LED_BUILTIN, LOW);
//      digitalWrite(12, HIGH);
//      c = 1;
//      halt();
//      moveTime(0, -255, 0, 1000);
//      delay(3000);
//      moveTime(0, 0, -255, 500);
//      digitalWrite(12, LOW);
//    } else {
//      digitalWrite(LED_BUILTIN, HIGH);
//      c++;
//      moveTime(0, 0, -255, 500);
//      moveTime(0, -255, 0, 750);
//      delay(250);
//    }
//  }

//  move(0, 127, 0);
//  while (!digitalRead(2)) {}
//  moveTime(0, -127, 0, 500);
//  moveTime(0, 0, -127, 250);

  //Analog
  move(0, 0, 63);
  while (analogRead(A0) <= 5) {}
  halt();
  delay(500);
  moveTime(0, 255, 0, 1000);
  //Serial.println(analogRead(A0));
}

void moveTime(int x, int y, int r, int milli) {
  move(x, y, r);
  delay(milli);
  halt();
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
  topLeft.setDeadBand(Thresh);
  topRight.setDeadBand(Thresh);
  botLeft.setDeadBand(Thresh);
  botRight.setDeadBand(Thresh);
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
