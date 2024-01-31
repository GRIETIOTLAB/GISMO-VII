#define FIREBASE_HOST "gismo7-default-rtdb.firebaseio.com/" //Do not include https:// in FIREBASE_HOST
#define FIREBASE_AUTH "tRZxezT4QJA3zoi7bzTUjlGkto9YhzMe0fsOKUgC"
#define WIFI_SSID "IDEALab03"
#define WIFI_PASSWORD "griet@idealab"
#include <Wire.h>
#include "SSD1306.h" 
#include "FirebaseESP32.h"
FirebaseData firebaseData;
SSD1306  display(0x3c, 21, 22);
