//#include <SoftwareSerial.h>
#include <Printers.h>
#include <XBee.h>

XBee xbee = XBee();
XBeeAddress64 addr64 = XBeeAddress64(0x0013A200, 0x41B79B35);

//SoftwareSerial sSerial(2, 3); // RX, TX

//const byte numChars = 19;
uint8_t payload[5];
ZBTxRequest zbTx;
//boolean newData = false;
//static byte ndx = 0;
//char endMarker = '\n';
//char rc;

const byte leftPin = 8; //Digital
const byte rightPin = 9; //Digital
const byte upPin = 11; //digital
const byte downPin = 12;

void setup() {
  pinMode(leftPin, INPUT);
  pinMode(rightPin, INPUT);
  pinMode(upPin, INPUT);
  pinMode(downPin, INPUT);
  
  Serial.begin(57600);
  //sSerial.begin(57600);
  xbee.setSerial(Serial);
}

void loop() {
  // readIn();
  // for (int i = 0; i < 16; i++)
  //   Serial.print(payload[i], DEC);
  // Serial.print("\n");
  // zbTx = ZBTxRequest(addr64, payload, sizeof(payload));
  // xbee.send(zbTx);
  //delay(5);

  //Serial.println(digitalRead(leftPin) + digitalRead(rightPin) + digitalRead(upPin) + digitalRead(downPin));
  if (digitalRead(leftPin))
    payload[0] = 'L';
  else
    payload[0] = 'l';
  if (digitalRead(rightPin))
    payload[1] = 'R';
  else
    payload[1] = 'r';
  if (digitalRead(upPin))
    payload[2] = 'U';
  else
    payload[2] = 'u';
  if (digitalRead(downPin))
    payload[3] = 'D';
  else
    payload[3] = 'd';
  // for (int i = 0; i < sizeof(payload); i++) {
  //   Serial.print(payload[i], DEC);
  //   Serial.print(' ');
  // }
  // Serial.print("\n");
  zbTx = ZBTxRequest(addr64, payload, sizeof(payload));
  xbee.send(zbTx);
  
}

String motors;
// char[] motorArr;
int x = 0;
int y = 0;
int r = 0;
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

  if (digitalRead(leftPin))
    x -= 255;
  if (digitalRead(rightPin))
    x += 255;
  if (digitalRead(upPin))
    y += 255;
  if (digitalRead(downPin))
    y -= 255;

  motors = (x + y - r) + (char)'/' + (x - y + r) + (char)'/' + (x - y - r) + (char)'/' + (x + y + r);
  // motors.toCharArray(motorArr, motors.length());
  // for (int i = 0; i < motors.length(); i++)
  //   payload[i] = (uint8_t)motorArr[i];
  payload[0] = "\0";
  //motors.getBytes(payload, motors.length() + 1);
  x = 0;
  y = 0;
}
