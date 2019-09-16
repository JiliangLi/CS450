/*
Adafruit Arduino - Lesson 9. Light sensing
*/
int lightPin = 0;
int latchPin = 5;
int clockPin = 6;
int dataPin = 4;
int leds = 0;
int potPin = 1;

void setup()
{
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  Serial.begin(9600);
}
void loop(){
  int reading = analogRead(lightPin);
  int numLEDSLit = reading / 57; //1023 / 9 / 2
  if (numLEDSLit > 8) numLEDSLit = 8;
  leds = 0; // no LEDs lit to start
  for (int i = 0; i < numLEDSLit; i++){
    leds = leds + (1 << i); // sets the i'th bit
  }
  updateShiftRegister();
  int readingresistor = analogRead(potPin);
  Serial.println(readingresistor);
  delay(500);
}

void updateShiftRegister(){
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, leds);
  digitalWrite(latchPin, HIGH);
}
