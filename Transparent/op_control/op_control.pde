import processing.serial.*;
import net.java.games.input.*;
import org.gamecontrolplus.*;
import org.gamecontrolplus.gui.*;
//import cc.arduino.*;
import org.firmata.*;

ControlDevice cont;
ControlIO control;
//Arduino arduino;
float x;
float y;
float r;

float deadzone = 0.1;

ControlSlider xSlider;
ControlSlider ySlider;
//ControlSlider rSlider;
ControlHat hat;

String TL;
String TR;
String BL;
String BR;
//byte[] hexArr;

Serial port;

//API mode
//byte[] packet = {byte(0x7E)};
//byte[] dataHex;

void setup() {
  
  println(Serial.list());
  port = new Serial(this, Serial.list()[2], 57600);
  
  size(360, 200);
  
  contSetup();
  
  //arduino = new Arduino(this, Arduino.list()[0], 57600);
  //arduino.pinMode(10, Arduino.SERVO);
   
}

void draw() {
  getUserInput();
  //background(x, 100, 255);
  //background(y, 100, 255);
  //background(r, 100, 255);
  write();
  delay(10);
}

public void getUserInput() {
  x = xSlider.getValue();
  y = ySlider.getValue();
  //r = rSlider.getValue();
  r = hat.getX() * 255.0;
}

public void write() {
  TL = str(int(x + y - r));
  TR = str(int(x - y + r));
  BL = str(int(x - y - r));
  BR = str(int(x + y + r));
  
  //hexArr = numHex(TL + "/" + TR + "/" + BL + "/" + BR);
  //createPacket();
  port.write(TL + "/" + TR + "/" + BL + "/" + BR + "\n");
}

void contSetup() {
  control = ControlIO.getInstance(this);
  //cont = control.getMatchedDevice("PVDesktopContConfig");
  cont = control.filter(GCP.GAMEPAD).getDevice("Stadia Controller");
  if (cont == null) {
    println("Controller is Null.");
    System.exit(-1);
  }
  
  xSlider = cont.getSlider("Z Axis");
  ySlider = cont.getSlider("Z Rotation");
  //rSlider = cont.getSlider("X Axis");
  hat = cont.getHat("cooliehat: Hat Switch");
  
  xSlider.setMultiplier(255.0);
  ySlider.setMultiplier(-255.0);
  //rSlider.setMultiplier(255.0);
  //hat.setMultiplier(255.0);
  println("x multiplier: " + xSlider.getMultiplier());
  println("y multiplier: " + ySlider.getMultiplier());
  //println("r multiplier: " + rSlider.getMultiplier());
  //println("r multiplier: " + hat.getMultiplier());
  
  xSlider.setTolerance(deadzone);
  ySlider.setTolerance(deadzone);
  //rSlider.setTolerance(deadzone);
  println("x tolerance: " + xSlider.getTolerance());
  println("y tolerance: " + ySlider.getTolerance());
  //println("r tolerance: " + rSlider.getTolerance());
}

//void createPacket() {
//  byte[] dataHex = numHex(TL + "/" + TR + "/" + BL + "/" + BR);
  
//}

//byte[] numHex(String num) {
//  String s = "";
//  for (char c : num.toCharArray())
//    s += hex(byte(c), 2);
  
//  int len = s.length();
//    byte[] ret = new byte[len / 2];
//    for (int i = 0; i < len; i = i + 2) {
//        ret[i / 2] = (byte) ((Character.digit(s.charAt(i), 16) << 4) + Character.digit(s.charAt(i+1), 16));
//    }
//    return ret;
//}
