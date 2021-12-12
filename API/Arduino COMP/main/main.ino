//#include <SoftwareSerial.h>
#include <Printers.h>
#include <XBee.h>

XBee xbee = XBee();
XBeeAddress64 addr64 = XBeeAddress64(0x0013A200, 0x41B79B35);

//SoftwareSerial sSerial(2, 3); // RX, TX

const byte numChars = 19;
uint8_t payload[numChars];
ZBTxRequest zbTx;
boolean newData = false;
static byte ndx = 0;
char endMarker = '\n';
char rc;

void setup() {
  Serial.begin(57600);
  Serial1.begin(57600);
  //sSerial.begin(57600);
  xbee.setSerial(Serial1);
}

void loop() {
  readIn();
  if (newData == true){
    zbTx = ZBTxRequest(addr64, payload, sizeof(payload));
    xbee.send(zbTx);
    newData = false;
  }
}


void readIn() {
  while (Serial.available() > 0 && !newData) {
    rc = Serial.read();
    if (rc != endMarker) {
      payload[ndx] = rc;
      ndx++;
      if (ndx >= numChars)
        ndx = numChars - 1;
    } else {
      ndx = 0;
      newData = true;
    }
  }
}
