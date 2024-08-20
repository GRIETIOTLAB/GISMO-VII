/* Soil Moisture sensor pin   : GPIO34
 * Relay pin                  : GPIO13
 *
  */
#include <WiFi.h>
#include <FirebaseESP32.h>
//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"
#include <Wire.h>
#include <SSD1306.h>

SSD1306  display(0x3c, 21, 22);

#define WIFI_SSID "xxxxxxxxxxxxx"
#define WIFI_PASSWORD "xxxxxxxxxxx"
#define API_KEY "xxxxxxxxxxxxxxxxxx"
#define DATABASE_URL "xxxxxxxxxxxxxxxxxxxxxxx" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long dataMillis = 0;
int count = 0;
bool signupOK = false;

#define smPin 34
#define relayPin 13
int smValue;
int smLimit = 1500;
int delayTime = 2000;
String motorStatus = "OFF";
void OLEDInit();
void OLEDUpdate();
void WiFiInit();
void FirebaseInit();
void FirebaseWrite();


String tag1 = "IOTLAB/Smart_Garden/Soil_Moisture";
String tag2 = "IOTLAB/Smart_Garden/Motor_Status";


void setup() {
  // put your setup code here, to run once:
  pinMode(relayPin,OUTPUT);
  Serial.begin(115200);
  OLEDInit();
  WiFiInit();
  FirebaseInit();
  }

void loop() {
  // put your main code here, to run repeatedly:

//FirebaseRead();  
smValue = 4095 - analogRead(smPin);
Serial.print("Soil Moisture = ");
Serial.println(smValue);

if (smValue < smLimit){
digitalWrite(relayPin,HIGH);
Serial.println("Motor turned ON");
motorStatus = "ON";
}
else{
digitalWrite(relayPin,LOW);
Serial.println("Motor turned OFF");
motorStatus = "OFF";
}

OLEDUpdate();
FirebaseWrite();
delay(delayTime);
}

void OLEDInit(){
  display.init();
  display.setFont(ArialMT_Plain_24);
}

void OLEDUpdate(){
  
 
  display.clear();
  display.drawString(30,0,String(smValue));
  display.drawString(30,30,String(motorStatus));
  display.display();
}

void WiFiInit(){
  pinMode(2,OUTPUT);
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
void FirebaseWrite(){
  Firebase.setInt(fbdo,tag1,smValue);
  Firebase.setString(fbdo,tag2,motorStatus);
  
}

  
