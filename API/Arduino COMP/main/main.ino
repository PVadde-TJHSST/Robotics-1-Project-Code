#include <SoftwareSerial.h>
#include <Printers.h>
#include <XBee.h>

XBee xbee = XBee();
XBeeAddress64 addr64 = XBeeAddress64(0x0013A200, 0x41BE7880);

SoftwareSerial sSerial(2, 3); // RX, TX

uint8_t payload[] = {};
ZBTxRequest zbTx;

void setup {
  Serial.begin(57600);
  sSerial.begin(57600);
  xbee.setSerial(sSerial);
}

void loop {
  if (readIn()) {
    zbTx = ZBTxRequest(addr64, payload, sizeof(payload));
    xbee.send(zbTx);
  }
}

bool readIn() {
  if (Serial.available > 0) {
    payload = Serial.readStringUntil('\n').toCharArray(); //CHECK PROCESSING
    return true;
  }
  return false;
}
