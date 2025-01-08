//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

void setup() {
  pinMode(2,OUTPUT);
  pinMode(13,OUTPUT);
  Serial.begin(115200);
  SerialBT.begin("xxxxx"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
 char c;
 if(SerialBT.available())
 c = SerialBT.read();

 if(c == '1')
 {
 Serial.println("Received 1 on BT");
 digitalWrite(2,HIGH);
 digitalWrite(13,LOW);
 }
 else if (c == '0')
 {
 Serial.println("Received 0 on BT"); 
 digitalWrite(2,LOW);
 digitalWrite(13,HIGH);
 }
 }
