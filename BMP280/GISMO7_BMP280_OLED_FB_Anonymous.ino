

#include <WiFi.h>
#include <FirebaseESP32.h>
//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"
#include <Wire.h>
#include <SSD1306.h>
#include <Adafruit_BMP280.h>


Adafruit_BMP280 bmp; // I2C
SSD1306  display(0x3c, 21, 22);
#define SEALEVELPRESSURE_HPA (1013.25)

float tempC,tempF,atPressure,altitude,humidity;

#define WIFI_SSID "IDEALab03"
#define WIFI_PASSWORD "griet@idealab"
#define API_KEY "AIzaSyC-zI60FmauZOLGzAw64IRiXKv4swzSLDM"
#define DATABASE_URL "https://myproject-e6014-default-rtdb.firebaseio.com/" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long dataMillis = 0;
int count = 0;
bool signupOK = false;
//String myString;

void setup()
{

    pinMode(2,OUTPUT);
    Serial.begin(115200);

    Serial.println(F("BMP280 test"));

  if (!bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID)) {
      Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                      "try a different address!"));
    while (1) delay(10);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

     OLEDInit();


    WiFiInit();
    FirebaseInit();
}

void loop()
{
    if (millis() - dataMillis > 5000 && signupOK && Firebase.ready())
    {
        dataMillis = millis();
        printValues();
        displayValues();

        //String path = auth.token.uid.c_str(); //<- user uid
       // path = "/test/int";
        //Serial.printf("Set int... %s\n", Firebase.setInt(fbdo, path.c_str(), count++) ? "ok" : fbdo.errorReason().c_str());
        //Serial.printf("Set int... %s\n", Firebase.setInt(fbdo, "IOTLAB/SensorValue", count++) ? "ok" : fbdo.errorReason().c_str());
       
}
}

void WiFiInit(){
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        digitalWrite(2,!digitalRead(2));
        delay(300);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();

}
void FirebaseInit(){
    Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

   config.api_key = API_KEY;
   config.database_url = DATABASE_URL;
   Firebase.reconnectWiFi(true);
   Serial.print("Sign up new user... ");

    /* Sign up */
    if (Firebase.signUp(&config, &auth, "", ""))
    {
        Serial.println("ok");
        signupOK = true;

        /** if the database rules were set as in the example "EmailPassword.ino"
         * This new user can be access the following location.
         * 
         * "/UserData/<user uid>"
         * 
         * The new user UID or <user uid> can be taken from auth.token.uid
        */
    }
    else
        Serial.printf("%s\n", config.signer.signupError.message.c_str());

    /* Assign the callback function for the long running token generation task */
    config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

    /** The id token (C++ string) will be available from config.signer.tokens.id_token
     * if the sig-up was successful. 
     * 
     * Now you can initialize the library using the internal created credentials.
     * 
     * If the sign-up was failed, the following function will initialize because 
     * the internal authentication credentials are not created.
    */
    Firebase.begin(&config, &auth);
}
void OLEDInit(){
  display.init();
  display.setFont(ArialMT_Plain_16);
}
void printValues(){
 // float tempC,tempF,atPressure,altitude,humidity;
  Serial.print("Temperature = ");
  tempC = bmp.readTemperature();
//Serial.print(bme.readTemperature());
Serial.print(tempC);
Serial.println(" deg C");
Firebase.setFloat(fbdo,"IOTLAB/Environment_Monitor/Temperature",tempC);

Serial.print("Temperature = ");
//Serial.print(1.8*bme.readTemperature()+32);
Serial.print(1.8*tempC+32);
Serial.println(" deg F");

Serial.print("Pressure = ");
atPressure=bmp.readPressure()/100.0F;
//Serial.print(bme.readPressure()/100.0F);
Serial.print(atPressure);
Serial.println(" hPa");
Firebase.setFloat(fbdo,"IOTLAB/Environment_Monitor/Pressure",atPressure);

Serial.print("Altitude = ");
altitude=bmp.readAltitude(SEALEVELPRESSURE_HPA);
//Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
Serial.print(altitude);
Serial.println(" m");
Firebase.setFloat(fbdo,"IOTLAB/Environment_Monitor/Altitude",altitude);
Serial.println();
Firebase.setFloat(fbdo,"IOTLAB/Environment_Monitor/Humidity",0.0);

}

void displayValues(){
  display.clear();
  
  String myString = "";
  
  char buffer[6];
  dtostrf(tempC,5,1,buffer);
  myString.concat(buffer);
  myString.concat(" C");
  display.drawString(0,0,myString);

  humidity = 0.0;
  myString = "";
  dtostrf(humidity,5,1,buffer);
  myString.concat(buffer);
  myString.concat(" %");
  display.drawString(64,0,myString);

 myString = "";
  dtostrf(atPressure,5,1,buffer);
  myString.concat(buffer);
   display.drawString(0,30,myString);

    myString = "";
  dtostrf(altitude,5,1,buffer);
  myString.concat(buffer);
  myString.concat("m");
   display.drawString(64,30,myString);


  display.display();

}
