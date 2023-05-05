#include "SSD1306.h"

SSD1306 display(0x3c,21,22);

// defines pins numbers
const int trigPin = 12;
const int echoPin = 13;

// defines variables
long duration;
int distance;

void OLEDInit();
void OLEDUpdate();


void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
pinMode(14,OUTPUT);
Serial.begin(115200); // Starts the serial communication
OLEDInit();
}

void loop() {
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance
distance= duration*0.034/2;

// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);

OLEDUpdate();
digitalWrite(14,!digitalRead(14));

delay(1000);
}
void OLEDInit(){
  display.init();
  display.setFont(ArialMT_Plain_24);
}

void OLEDUpdate(){
  
  String d = String(distance) + " cm";
  display.clear();
  display.drawString(30,0,d);
  display.display();
}
  
