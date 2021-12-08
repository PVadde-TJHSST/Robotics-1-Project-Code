//#include <SoftwareSerial.h>
#include <Printers.h>
#include <XBee.h>

XBee xbee = XBee();
XBeeAddress64 addr64 = XBeeAddress64(0x0013A200, 0x41BE7880);

//SoftwareSerial sSerial(2, 3); // RX, TX

//const byte numChars = 19;
uint8_t payload[];
ZBTxRequest zbTx;
//boolean newData = false;
//static byte ndx = 0;
//char endMarker = '\n';
//char rc;

const byte rLeftPin = 1; //Digital
const byte rRightPin = 2; //Digital
const byte rSpeedPin = 3; //Analog
const byte xAxisPin = 4; //Analog
const byte yAxisPin = 5; //Analog

void setup() {
  pinMode(rLeftPin, INPUT);
  pinMode(rRightPin, INPUT);
  pinMode(rSpeedPin, INPUT);
  pinMode(xAxisPin, INPUT);
  pinMode(yAxisPin, INPUT);
  
  Serial.begin(57600);
  //sSerial.begin(57600);
  xbee.setSerial(Serial);
}

void loop() {
  readIn();
  zbTx = ZBTxRequest(addr64, payload, sizeof(payload));
  xbee.send(zbTx);
  //delay(5);
}

String motors;
int x;
int y;
int r;
byte first;
void readIn() {
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

  x = map(analogRead(xAxisPin, -1023, 1023, -255, 255);
  y = map(analogRead(yAxisPin, -1023, 1023, -255, 255);
  
  if (digitalRead(rLeftPin) && !digitalRead(rRightPin)) {
    first = rLeftPin;
    r = map(analogRead(rSpeedPin), 0, 1023, 0, 255);
  } else if (!digitalRead(rLeftPin) && digitalRead(rRightPin)) {
    first = rRightPin;
    r = -map(analogRead(rSpeedPin), 0, 1023, 0, 255);
  } else if (digitalRead(rLeftPin) && digitalRead(rRightPin)) {
    if (first = rRightPin)
      r = -map(analogRead(rSpeedPin), 0, 1023, 0, 255);
    else
      r = map(analogRead(rSpeedPin), 0, 1023, 0, 255);
  }

  motors = String(x + y - r) + '/' + String(x - y + r) + '/' + String(x - y - r) + '/' + String(x + y + r);
  payload = getBytes(motors, motors.length() + 1);
}
