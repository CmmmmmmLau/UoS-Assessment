const int period = 100; // Number of samples per full period
byte sinStore[period]; // Array to hold pre-calculated sine samples
int frequency  = 500;
int d = 1 / (frequency * 0.00001);

void setup() {
  
  Serial.begin(9600);
  
  DDRD = DDRD | B11111100;  // pins 2-7 outputs, pins 0-1 unchanged
  pinMode(A0,INPUT);        // pin A0 input

  // Precalculate values of sine
  for (int i = 0; i < period; i++) {
    sinStore[i] = byte(((sin(2.0*PI*i/period) + 1.0) * 63.0) / 2.0);
  }
  
}

void loop() {
  
  for (int i = 0; i < period; i++){
    PORTD = (sinStore[i] << 2) ;// assign the sinwave to portD
    d = 1 / (frequency * 0.0001);
    delayMicroseconds(d);// very short delay for output to  settle
    
    //Serial.println(analogRead(A0));   // analogue reading
  }

}
