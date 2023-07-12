void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
int SoilMoisture;
SoilMoisture = 4095- analogRead(34);
Serial.println(SoilMoisture);
delay(1000);
}
