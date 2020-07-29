#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <math.h>

#define wheelConstant 4333  //
#define HEtimeout 5000000   //
#define HEpin 2            //HE sensor pin (or a switch to ground)



float v = 0;            
float v_max;
float distance = 0;
float duration = 0;

Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);

void setup() {
  pinMode(HEpin, INPUT_PULLUP); //normally high
  Serial.begin(9600);       //IDE serial monitor/plotter

  /// LCD
  display.begin();
  display.setContrast(60);  
  display.clearDisplay(); 
  display.setTextColor(BLACK);
  display.setRotation(2);
}

void loop() {
  detSpeed();           //determine speed
  printSpeed();            // print speed with a delay
}

void printSpeed(){
   Serial.println(v);  //put it to monitor/plotter
   Serial.println(duration);  //put it to monitor/plotter
   Serial.println(v_max);  //put it to monitor/plotter
   
if(v == 0){
  // start
  display.clearDisplay(); 
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  
  display.println("Jesse Weikamp");
  //display.setCursor(24,8);
  display.println("v=");
  display.setCursor(16,8);
  display.print(v);
  display.setCursor(48,8);
  display.print("km/h");
  display.setCursor(0,16);
  display.println("max");
  display.setCursor(24,16);
  display.print(v_max);
  display.setCursor(56,16);
  display.print("km/h");
  display.setCursor(0,24);
  display.print("odo ");
  display.print(distance);
  display.print("km");
  //
  //display.setCursor(0,40);
  //display.println("test....");

  // dit moet als laatste
  display.display();
}
if(v != 0){
    display.clearDisplay(); 
    display.setTextSize(1);
    display.setTextColor(BLACK);
    display.setCursor(0,0);
    display.println("Jesse Weikamp");
    display.setTextSize(2);
    display.print(v);
    display.setCursor(60,8);
    display.setTextSize(1);
    display.print("km/h");
    
    display.setCursor(0,24);
    display.println("max");
    display.setCursor(24,24);
    display.print(v_max);
    display.setCursor(56,24);
    display.print("km/h");
    display.setCursor(0,32);
    display.print("odo ");
    display.print(distance);
     display.print(" km");
// dit moet als laatste
     display.display();
  

  } 
   delay(1000);
  
}

void detSpeed(){
  duration = pulseIn(HEpin, HIGH, HEtimeout)/1000; //pulse length in millis
  if (duration == 0) v = 0;       //timout so call it zero kph
  else {v = (wheelConstant/duration); //
  }
  distance = distance + ((v*duration)/1000000);

  if(v >= v_max){

  v_max = v;

  }
}
