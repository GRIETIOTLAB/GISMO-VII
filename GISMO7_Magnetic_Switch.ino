void setup() {
  // put your setup code here, to run once:
pinMode(14,INPUT_PULLUP);
Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
int value;
value = digitalRead(14);
if(value == HIGH)
{
Serial.println("Switch open");
}
else
{
Serial.println("Switch closed");
}
delay(1000);

}
