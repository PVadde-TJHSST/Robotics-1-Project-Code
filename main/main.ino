#include <I2CEncoder.h>
#include <Servo.h>
#include <Wire.h>

void setup() {

I2CEncoder encoder;
Wire.begin();
encoder.init(MOTOR_393_SPEED_ROTATIONS, MOTOR_393_TIME_DELTA);
  
}

void loop() {


  
}