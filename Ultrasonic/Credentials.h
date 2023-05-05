#define FIREBASE_HOST "xxxxxxxxxxxxxxxxxxxx" //Do not include https:// in FIREBASE_HOST
#define FIREBASE_AUTH "xxxxxxxxxxxxxxxxxxxx"
#define WIFI_SSID "xxxxxxxxxx"
#define WIFI_PASSWORD "xxxxxxxxxxxxxxxx"
#include <Wire.h>
#include "SSD1306.h" 
#include "FirebaseESP32.h"
FirebaseData firebaseData;
SSD1306  display(0x3c, 21, 22);
