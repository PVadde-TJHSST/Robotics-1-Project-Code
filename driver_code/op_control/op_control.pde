import processing.serial.*;
import net.java.games.input.*;
import org.gamecontrolplus.*;
import org.gamecontrolplus.gui.*;
import cc.arduino.*;
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

int TL;
int TR;
int BL;
int BR;

Serial port;

void setup() {
  
  println(Serial.list());
  port = new Serial(this, Serial.list()[1], 57600);
  
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
  TL = int(x + y + r);
  TR = int(x - y - r);
  BL = int(x - y + r);
  BR = int(x + y - r);
  
  port.write(str(TL));
  port.write('/');
  
  port.write(str(TR));
  port.write('/');
  
  port.write(str(BL));
  port.write('/');
  
  port.write(str(BR));
  port.write("\n");
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
  println("x multiplier: " + xSlider.getMultiplier());
  println("y multiplier: " + ySlider.getMultiplier());
  //println("r multiplier: " + rSlider.getMultiplier());
  
  xSlider.setTolerance(deadzone);
  ySlider.setTolerance(deadzone);
  //rSlider.setTolerance(deadzone);
  println("x tolerance: " + xSlider.getTolerance());
  println("y tolerance: " + ySlider.getTolerance());
  //println("r tolerance: " + rSlider.getTolerance());
}
