#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
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

#define BNO055_SAMPLERATE_DELAY_MS (100)
Adafruit_BNO055 bno = Adafruit_BNO055(55);

void setup() {
  topLeft.attach(TLpin);
  topRight.attach(TRpin);
  botLeft.attach(BLpin);
  botRight.attach(BRpin);

  setMotorPulse();
  setMotorThreshold();

  Serial.begin(9600);

  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  delay(5000);
}

void loop() {
  move(0, 255, 0);
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
