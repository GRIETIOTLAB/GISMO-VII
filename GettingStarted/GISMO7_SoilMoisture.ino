int threshold = 1500;
void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);
    pinMode(2,OUTPUT);
  }

void loop() {
  // put your main code here, to run repeatedly:
  int smValue = 4095 - analogRead(34);
  Serial.println(smValue);
  if(smValue < threshold)
  digitalWrite(2,HIGH);
  else
  digitalWrite(2,LOW);
  delay(1000);
}
