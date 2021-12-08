#include <Printers.h>
#include <XBee.h>
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

XBee xbee = XBee();
ZBRxResponse rx = ZBRxResponse();
#define MAX_FRAME_DATA_SIZE 50
Rx16Response rx16 = Rx16Response();

int TLP;
int TRP;
int BLP;;
int BRP;

void setup() {
  setMotors();
  Serial.begin(57600);
  Serial1.begin(57600);
  xbee.setSerial(Serial1);
}

void loop() {
  readXBee();
  topLeft.write(TLP);
  topRight.write(TRP);
  botLeft.write(BLP);
  botRight.write(BRP);
}

void move(int x, int y, int r) {
  topLeft.write(x + y - r);
  topRight.write(x - y + r);
  botLeft.write(x - y - r);
  botRight.write(x + y + r);
}

void setMotors() {
  topLeft.attach(TLpin);
  topRight.attach(TRpin);
  botLeft.attach(BLpin);
  botRight.attach(BRpin);
  
  topLeft.setDeadBand(Thresh);
  topRight.setDeadBand(Thresh);
  botLeft.setDeadBand(Thresh);
  botRight.setDeadBand(Thresh);

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

int i;
int c;
String p = "";
void readXBee() {
  xbee.readPacket();
  if (xbee.getResponse().isAvailable() && xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {
    xbee.getResponse().getZBRxResponse(rx);
    for (i = 0, c = 1; i < rx.getDataLength() - 1; i++) {
      if ((char)rx.getData()[i] == '/') {
        if (c == 1)
          TLP = p.toInt();
        else if (c == 2)
          TRP = p.toInt();
        else if (c == 3)
          BLP = p.toInt();
        else if (c == 4)
          BRP = p.toInt();
        p = "";
        c++;
      } else {
        p += (char)rx.getData()[i];
      }
    }
  }
}
