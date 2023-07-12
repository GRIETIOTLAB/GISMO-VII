void setup() {
  // put your setup code here, to run once:
pinMode(14,INPUT_PULLUP);
pinMode(25,OUTPUT);
Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
int value;
value = digitalRead(14);
if(value == HIGH)
{
Serial.println("Switch open");
digitalWrite(25,LOW);
}
else
{
Serial.println("Switch closed");
digitalWrite(25,HIGH);
}
delay(1000);

}
