int motor=10;
int buzzer=5;
int capt=A5;
void setup()
{
  pinMode(motor, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(capt, INPUT);
  Serial.begin(9600);
}

void loop()
{int valeur =analogRead(capt);
 if (valeur>300){
  
   digitalWrite(buzzer,HIGH);
    for (int i=0;i<=255;i++){
  
  analogWrite(motor,i);
  Serial.println(i);
  delay(50);
  };
  delay(500);
  
  for (int i=255;i>=0;i--){
  analogWrite(motor,i);
    Serial.println(i);
    delay(50);
  };
   delay(500);}
 else{ digitalWrite(buzzer,LOW);}
}
