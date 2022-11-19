// C++ code
//
int sensorValue = 0;
float sensorVoltage = 0;
float temp = 0.0;

int switchState = 0;



void setup()
{
  Serial.begin(9600);
  pinMode(A0,INPUT);
  pinMode(2,INPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
}

void loop()
{
  sensorValue = analogRead(A0);
  sensorVoltage = (float(sensorValue)/1023) * 5;
  temp = (sensorVoltage - 0.5)/0.01;
  
  switchState = digitalRead(2);
  if (switchState == 1) {
    if(temp < 20){
      digitalWrite(3,HIGH);
      digitalWrite(4,LOW);
    } else {
      digitalWrite(3,HIGH);
      digitalWrite(4,HIGH);
    }
  } else {
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
  }
    
  Serial.print("temperature:");
  Serial.println(temp);
  Serial.print(" LED1 State: ");
  Serial.print(digitalRead(3));
  Serial.print(" LED2 State: ");
  Serial.println(digitalRead(4));
  delay(100); // Delay a little bit to improve simulation performance
}
