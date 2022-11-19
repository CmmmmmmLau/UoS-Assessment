// Input/Output pins
#define pwm1 5
#define pwm2 6
#define photo 12

// Global variables
boolean motor_dir = 0;
int motor_speed = 0;

// Command interface
String inputString = "00000000";
char subsystem = 0;
 
void setup() {
  pinMode(pwm1,OUTPUT);
  pinMode(pwm2,OUTPUT);
  Serial.begin(9600);
}
 
void loop() {

  // Serial interface
  if(Serial.available()){
    inputString = Serial.readStringUntil('\n');
  }
        
  // Command processing
  subsystem = inputString[0];
  switch (subsystem) {
    case 'm':
      motor_speed = numberFromCommand(inputString);
      Serial.println((String)"Setting motor speed to "+motor_speed);
      break;
  }
  inputString = "";

  // Motor direction
  if(motor_dir){
    analogWrite(pwm1,motor_speed);
    digitalWrite(pwm2,0);
  }
  else{
    analogWrite(pwm2,motor_speed);
    digitalWrite(pwm1,0);
  }
  
} // End loop

// Functions below this line

// Return the int number from string character 2:end
int numberFromCommand(String command){
  String numberString = command.substring(1,command.length());
  int number = numberString.toInt();
  return number;
}
