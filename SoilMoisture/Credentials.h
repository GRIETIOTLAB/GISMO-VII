#define FIREBASE_HOST "xxxxxxxxxxxxxxxxxxxxxx" //Do not include https:// in FIREBASE_HOST
#define FIREBASE_AUTH "xxxxxxxxxxxxxxxxxxxxxx"
#define WIFI_SSID "xxxxxxxxxxxxx"
#define WIFI_PASSWORD "xxxxxxxxxxxxxxxxxxxx"
#include <Wire.h>
#include "SSD1306.h" 
#include "FirebaseESP32.h"
FirebaseData firebaseData;
SSD1306  display(0x3c, 21, 22);