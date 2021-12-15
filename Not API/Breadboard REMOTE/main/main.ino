// #include <Printers.h>
// #include <XBee.h>
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
int x = 0;
int y = 0;

// XBee xbee = XBee();
// ZBRxResponse rx = ZBRxResponse();
// #define MAX_FRAME_DATA_SIZE 50
// Rx16Response rx16 = Rx16Response();

void setup() {
  setMotors();
//  Serial.begin(57600);
  Serial1.begin(57600);
//   xbee.setSerial(Serial1);
}

void loop() {
  readXBee();
  move(x, y, 0);
}

void move(int x, int y, int r) {
  topLeft.write(x + y - r);
  topRight.write(x - y + r);
  botLeft.write(x - y - r);
  botRight.write(x + y + r);
}

void halt() {
  topLeft.write(0);
  topRight.write(0);
  botLeft.write(0);
  botRight.write(0);
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

// int i;
// int c;
String p;
void readXBee() {
//   xbee.readPacket();
//   if (xbee.getResponse().isAvailable() && xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {
//     xbee.getResponse().getZBRxResponse(rx);
//     for (i = 0, c = 1; i < rx.getDataLength() - 1; i++) {
//       if ((char)rx.getData()[i] == '/') {
//         if (c == 1)
//           TLP = p.toInt();
//         else if (c == 2)
//           TRP = p.toInt();
//         else if (c == 3)
//           BLP = p.toInt();
//         else if (c == 4)
//           BRP = p.toInt();
//         p = "";
//         c++;
//       } else {
//         p += (char)rx.getData()[i];
//       }
//     }
//   }

    x = 0;
    y = 0;
    for(int i = 0; i < 1; i++) {
      if (Serial1.available() > 0) {
          p = Serial1.readStringUntil('\n');
          if (p.length() >= 5) {
  
              if(p.charAt(p.length() - 5) == '1' && p.charAt(p.length() - 4) == '1') {
                move(0, 0, 255);
                delay(100);
                halt();
                break;
              }

              if(p.charAt(p.length() - 3) == '1' && p.charAt(p.length() - 2) == '1') {
                move(0, 0, -255);
                delay(100);
                halt();
                break;
              }
              
              if (p.charAt(p.length() - 5) == '1')
                  x -= 255;
              if (p.charAt(p.length() - 4) == '1')
                  x += 255;
              if (p.charAt(p.length() - 3) == '1')
                  y += 255;
              if (p.charAt(p.length() - 2) == '1')
                  y -= 255;
  
          }
      }
   }
}
