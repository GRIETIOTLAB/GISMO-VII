#include <WiFi.h>
#include <FirebaseESP32.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"


#define WIFI_SSID "xxxxxxxxxxx"
#define WIFI_PASSWORD "xxxxxxxxxxxx"
#define API_KEY "xxxxxxxxxxxxxxxxxxxxxxxxxxx"
#define DATABASE_URL "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long dataMillis = 0;
int count = 0;
bool signupOK = false;

void setup()
{
 
    Serial.begin(115200);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();

    Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

    config.api_key = API_KEY;
    config.database_url = DATABASE_URL;

    Firebase.reconnectWiFi(true);
    Serial.print("Sign up new user... ");

    if (Firebase.signUp(&config, &auth, "", ""))
    {
        Serial.println("ok");
        signupOK = true;
    }
    else
        Serial.printf("%s\n", config.signer.signupError.message.c_str());

    config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
    Firebase.begin(&config, &auth);
}
void loop()
{
    if (millis() - dataMillis > 5000 && signupOK && Firebase.ready())
    {
        dataMillis = millis();
        //String path = auth.token.uid.c_str(); //<- user uid
        String path = "/IOTLAB/My_App/Sensor_Value";
        
        Serial.printf("Set sensor value... %s\n", Firebase.setInt(fbdo, path.c_str(), count++) ? "ok" : fbdo.errorReason().c_str());
        Serial.println(count);
    }
}
