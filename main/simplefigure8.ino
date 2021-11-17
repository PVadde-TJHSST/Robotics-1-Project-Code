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
    // 45 degrees left

    // move forward
    moveTime(0, 100, 0, 5000);
    // 45 degrees right + 90 degrees

    // move forward (half of first move forward)
    moveTime(0, 100, 0, 2500);
    // 45 degrees right + 90 degrees

    // move forward
    moveTime(0, 100, 0, 5000);
    // 45 degrees left + 90 degrees

    // move foward (half of first move forward)
    moveTime(0, 100, 0, 2500)
    // left 90 degrees
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
