import processing.serial.*;
import net.java.games.input.*;
import org.gamecontrolplus.*;
import org.gamecontrolplus.gui.*;
import org.firmata.*;
import cc.arduino.*;

Arduino arduino;
ControlDevice cont;
ControlIO control;
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
  
  //println(Serial.list());
  //println(Serial.list()[1]);
  println();
  println(Arduino.list());
  println(Arduino.list()[0]);
  port = new Serial(this, Serial.list()[1], 57600);
  
  size(360, 200);
  
  //contSetup();
   
}

void draw() {
  //getUserInput();
  //write();
}

public void getUserInput() {
  x = xSlider.getValue();
  y = ySlider.getValue();
  //r = rSlider.getValue();
  r = hat.getX() * 255.0;
}

public void write() {
  TL = int(x + y - r);
  TR = int(x - y + r);
  BL = int(x - y - r);
  BR = int(x + y + r);
  
  port.write(TL + '/' + TR + '/' + BL + '/' + BR + '\n');
}

void contSetup() {
  control = ControlIO.getInstance(this);
  //cont = control.getMatchedDevice("PVDesktopContConfig");
  cont = control.filter(GCP.GAMEPAD).getDevice("Stadia Controller");
  if (cont == null) {
    println("Controller is Null.");
    System.exit(-1);
  }
  
  xSlider = cont.getSlider("z");
  ySlider = cont.getSlider("rz");
  //rSlider = cont.getSlider("X Axis");
  hat = cont.getHat("cooliehat: pov");
  
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
