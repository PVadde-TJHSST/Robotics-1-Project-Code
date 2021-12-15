//#include <SoftwareSerial.h>
#include <Printers.h>
#include <XBee.h>

XBee xbee = XBee();
XBeeAddress64 addr64 = XBeeAddress64(0x0013A200, 0x41B79B35);

//SoftwareSerial sSerial(2, 3); // RX, TX

//const byte numChars = 19;
uint8_t payload[] = {(byte)'h'};
ZBTxRequest zbTx = ZBTxRequest(addr64, payload, sizeof(payload));
//boolean newData = false;
//static byte ndx = 0;
//char endMarker = '\n';
//char rc;

const byte leftPin = 12; //Digital
const byte rightPin = 11; //Digital
const byte upPin = 9; //digital
const byte downPin = 8;

void setup() {
  pinMode(leftPin, INPUT);
  pinMode(rightPin, INPUT);
  pinMode(upPin, INPUT);
  pinMode(downPin, INPUT);
  
  Serial1.begin(57600);
  //sSerial.begin(57600);
  xbee.setSerial(Serial1);
}

void loop() {
//  xbee.send(zbTx);
//  delay(1000);
  Serial1.print('1');
  Serial1.print('1');
  Serial1.print('1');
  Serial1.println('1');
  delay(1000);
}

//String motors;
//char[] motorArr;
//int x = 0;
//int y = 0;
//int r = 0;
//void readIn() {
//  while (Serial.available() > 0 && !newData) {
//    rc = Serial.read();
//    if (rc != endMarker) {
//      payload[ndx] = rc;
//      ndx++;
//      if (ndx >= numChars)
//        ndx = numChars - 1;
//    } else {
//      ndx = 0;
//      newData = true;
//    }
//  }

  // x = map(analogRead(xAxisPin, -1023, 1023, -255, 255);
  // y = map(analogRead(yAxisPin, -1023, 1023, -255, 255);
  
  // if (digitalRead(rLeftPin) && !digitalRead(rRightPin)) {
  //   first = rLeftPin;
  //   r = map(analogRead(rSpeedPin), 0, 1023, 0, 255);
  // } else if (!digitalRead(rLeftPin) && digitalRead(rRightPin)) {
  //   first = rRightPin;
  //   r = -map(analogRead(rSpeedPin), 0, 1023, 0, 255);
  // } else if (digitalRead(rLeftPin) && digitalRead(rRightPin)) {
  //   if (first = rRightPin)
  //     r = -map(analogRead(rSpeedPin), 0, 1023, 0, 255);
  //   else
  //     r = map(analogRead(rSpeedPin), 0, 1023, 0, 255);
  // }

//  if (digitalRead(leftPin))
//    x -= 255;
//  if (digitalRead(rightPin))
//    x += 255;
//  if (digitalRead(upPin))
//    y += 255;
//  if (digitalRead(downPin))
//    y -= 255;

//  motors = (x + y - r) + (char)'/' + (x - y + r) + (char)'/' + (x - y - r) + (char)'/' + (x + y + r);
  // motors.toCharArray(motorArr, motors.length());
  // for (int i = 0; i < motors.length(); i++)
  //   payload[i] = (uint8_t)motorArr[i];
//  payload[0] = "\0";
  //motors.getBytes(payload, motors.length() + 1);
//  x = 0;
//  y = 0;
//}
