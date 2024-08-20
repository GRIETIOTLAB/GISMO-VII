

#include <WiFi.h>
#include <FirebaseESP32.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"


#define WIFI_SSID "xxxxxxxxxxxxx"
#define WIFI_PASSWORD "xxxxxxxxxxxxxxxxxxx"

#define API_KEY "xxxxxxxxxxxxxxxxxxxxxxxxxxx"
#define DATABASE_URL "xxxxxxxxxxxxxxxxxxxxxxxxxxxx" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long dataMillis = 0;
int count = 0;
bool signupOK = false;
String myString;

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

void loop()
{
    if (millis() - dataMillis > 5000 && signupOK && Firebase.ready())
    {
        dataMillis = millis();
        //String path = auth.token.uid.c_str(); //<- user uid
       // path = "/test/int";
        //Serial.printf("Set int... %s\n", Firebase.setInt(fbdo, path.c_str(), count++) ? "ok" : fbdo.errorReason().c_str());
        Serial.printf("Set int... %s\n", Firebase.setInt(fbdo, "IOTLAB/SensorValue", count++) ? "ok" : fbdo.errorReason().c_str());

       
    }
}
