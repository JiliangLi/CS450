/*
 * Sep 11, 2019
 * Eric Li
Adafruit Arduino - Lesson 4. 8 LEDs and a Shift Register
https://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/
*/
int latchPin = 5;
int clockPin = 6;
int dataPin = 4;
int redLed = 11;
byte leds = 0;
const int trigPin = 9;
const int echoPin = 10;

long duration1;
long duration2;
int distance;

void setup(){
pinMode(latchPin, OUTPUT);
pinMode(dataPin, OUTPUT);
pinMode(clockPin, OUTPUT);
pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT); 
pinMode(redLed, OUTPUT); 
Serial.begin(9600); 
}

void loop(){
  digitalWrite(redLed, LOW);

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration1 = pulseIn(echoPin, HIGH);

  delay(100);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration2 = pulseIn(echoPin, HIGH);


  if(duration2<200){
    red();
  }
  
  if(duration1>duration2){
    closer();
  }

  else if(duration1==duration2){
    for (int i = 0; i < 8; i++){
      bitSet(leds, i);
      updateShiftRegister();
    }
    delay(1000);
  }
  
  else{
    farther();
  }

Serial.print("distance1: ");
Serial.println(duration1);
Serial.print("distance2: ");
Serial.println(duration2);
}


void red(){
  digitalWrite(redLed, HIGH);
  delay(1000);
}
void closer(){
  leds = 0;
  updateShiftRegister();
  delay(70);
  for (int i = 0; i < 8; i++){
    bitSet(leds, i);
    updateShiftRegister();
    delay(70);
  }
}

void farther(){
  leds = 0;
  updateShiftRegister();
  delay(70);
  for (int i = 7; i >= 0; i--){
    bitSet(leds, i);
    updateShiftRegister();
    delay(70);
  }
}
 
void updateShiftRegister(){
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, leds);
  digitalWrite(latchPin, HIGH);
}
