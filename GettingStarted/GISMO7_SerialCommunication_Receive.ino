void setup() {
  // put your setup code here, to run once:
pinMode(2,OUTPUT);
pinMode(14,OUTPUT);
Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available())
  {
    char c = Serial.read();
    switch(c){
      case '1':
      digitalWrite(2,HIGH);
      digitalWrite(14,HIGH);
      break;
      case '2':
      digitalWrite(14,LOW);
      digitalWrite(2,LOW);
      break;
      case '3':
      digitalWrite(2,HIGH);
      digitalWrite(14,LOW);
      break;
      case '4':
      digitalWrite(2,LOW);
      digitalWrite(14,HIGH);
      break;
    }
  }
}
