// #include <Printers.h>
// #include <XBee.h>

// XBee xbee = XBee();
// XBeeAddress64 addr64 = XBeeAddress64(0x0013A200, 0x41B79B35);
// uint8_t payload[5];
// ZBTxRequest zbTx;

const byte leftPin = 8;
const byte rightPin = 9;
const byte upPin = 10;
const byte downPin = 11;

void setup() {
  pinMode(leftPin, INPUT);
  pinMode(rightPin, INPUT);
  pinMode(upPin, INPUT);
  pinMode(downPin, INPUT);
  
  Serial1.begin(57600);
  // xbee.setSerial(Serial1);
}

String s;
void loop() {
//  if (digitalRead(leftPin))
//    Serial1.print('1');
//  else
//    Serial1.print('0');
//
//  if (digitalRead(rightPin))
//    Serial1.print('1');
//  else
//    Serial1.print('0');
//
//  if (digitalRead(upPin))
//    Serial1.print('1');
//  else
//    Serial1.print('0');
//
//  if (digitalRead(downPin))
//    Serial1.println('1');
//  else
//    Serial1.println('0');

  if (digitalRead(leftPin))
    s = '1';
  else
    s = '0';
    
  if (digitalRead(rightPin))
    s += '1';
  else
    s += '0';

  if (digitalRead(upPin))
    s += '1';
  else
    s += '0';

  if (digitalRead(downPin))
    s += '1';
  else
    s += '0';
  Serial1.println(s);
  //delay(150);
  
  // zbTx = ZBTxRequest(addr64, payload, sizeof(payload));
  // xbee.send(zbTx);
  
}
