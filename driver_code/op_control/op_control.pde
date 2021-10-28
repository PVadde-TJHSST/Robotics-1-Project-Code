import processing.serial.*;
import net.java.games.input.*;
import org.gamecontrolplus.*;
import org.gamecontrolplus.gui.*;
import cc.arduino.*;
import org.firmata.*;

ControlDevice cont;
ControlIO control;
Arduino arduino;
float x;
float y;
float r;

int TL = 0;
int TR = 0;
int BL = 0;
int BR = 0;

Serial port;

void setup() {
  
  //println(Serial.list());
  port = new Serial(this, Serial.list()[0], 57600);
  
  size(360, 200);
  control = ControlIO.getInstance(this);
  cont = control.getMatchedDevice("xbox_cont_config");
  if (cont == null) {
    println("Controller is Null.");
    System.exit(-1);
  }
  
  arduino = new Arduino(this, Arduino.list()[0], 57600);
  arduino.pinMode(10, Arduino.SERVO);
   
}

void draw() {
  getUserInput();
  background(x, 100, 255);
  background(y, 100, 255);
  background(r, 100, 255);
  
  //arduino.topLeft.write(x + y + r);
  //arduino.topRight.write(x - y - r);
  //arduino.botLeft.write(x - y + r);
  //arduino.botRight.write(x + y - r);
  //arduino.servoWrite(TL, (int)(x + y + r));
  //arduino.servoWrite(TR, (int)(x - y - r));
  //arduino.servoWrite(BL, (int)(x - y + r));
  //arduino.servoWrite(BR, (int)(x + y - r));
  //arduino.move((int)x, (int)y, (int)r);
  
  write();
  
}

public void getUserInput() {
  x = map(cont.getSlider("thumbX").getValue(), -1, 1, -255, 255);
  y = map(cont.getSlider("thumbY").getValue(), -1, 1, -255, 255);
  r = map(cont.getSlider("leftThumbR").getValue(), -1, 1, -255, 255);
}

public void write() {
  port.write(Float.toString(x));
  port.write('.');
  
  port.write(Float.toString(y));
  port.write('-');
  
  port.write(Float.toString(r));
  port.write('-');
}
