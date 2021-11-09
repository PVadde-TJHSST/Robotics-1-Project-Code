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

const int TLpin = 9; //White
const int TRpin = 10; //Blue
const int BLpin = 11; //Yellow
const int BRpin = 13; //Pink

const int minP = 1000;
const int neuP = 1500;
const int maxP = 2000;

const int ThreshTL = 5;
const int ThreshTR = 5;
const int ThreshBL = 5;
const int ThreshBR = 5;

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
  xbee.setSerial(Serial);
}

void loop() {
  readXBee();
  topLeft.write(TLP);
  topRight.write(TRP);
  botLeft.write(BLP);
  botRight.write(BRP);
}

void move(int x, int y, int r) {
  topLeft.write(x + y + r);
  topRight.write(x - y - r);
  botLeft.write(x - y + r);
  botRight.write(x + y - r);
}

void setMotors() {
  topLeft.attach(TLpin);
  topRight.attach(TRpin);
  botLeft.attach(BLpin);
  botRight.attach(BRpin);
  
  topLeft.setDeadBand(ThreshTL);
  topRight.setDeadBand(ThreshTR);
  botLeft.setDeadBand(ThreshBL);
  botRight.setDeadBand(ThreshBR);

  topLeft.setMinPulse(minP);
  topLeft.setNeutralPulse(neuP);
  topLeft.setMaxPulse(maxP);

  topRight.setMinPulse(minP);
  topRight.setNeutralPulse(neuP);
  topRight.setMaxPulse(maxP);

  botLeft.setMinPulse(minP);
  botLeft.setNeutralPulse(neuP);
  botLeft.setMaxPulse(maxP);

  botRight.setMinPulse(minP);
  botRight.setNeutralPulse(neuP);
  botRight.setMaxPulse(maxP);
}

int i;
int c;
String p = "";
void readXBee() {
  xbee.readPacket();
  if (xbee.getResponse().isAvailable() && xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {
    xbee.getResponse().getZBRxResponse(rx);
    for (i = 0, c = 1; i < rx.getDataLength(); i++) {
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
