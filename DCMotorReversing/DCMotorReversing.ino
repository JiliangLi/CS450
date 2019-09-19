/*
 * Eric Li
 * Sep 18, 2019
Adafruit Arduino - Lesson 15. Bi-directional Motor
*/
int enablePin = 11;
int in1Pin = 10;
int in2Pin = 9;
int switchPin = 7;
int potPin = 0;
const int buzzer = 12; //buzzer to arduino pin 12
int thisNote = 0;


int melody[] = {
  493.88, 0, 493.88, 493.88, 493.88, 440, 493.88, 493.88, 0, 493.88, 493.88, 493.88, 440, 493.88, 493.88, 0, 587.33, 493.88, 0, 440, 392, 0, 329.63, 329.63, 369.99, 392, 329.63};


// note durations: 4 = quarter note, 8 = eighth note, etc.:
long noteDurations[] = {
  40, 40, 20, 10, 10, 10, 30, 40, 40, 20, 10, 10, 10, 30, 40, 20, 40, 20, 20, 40, 20, 20, 20, 20, 20, 20, 20, 20};



void setup(){
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(switchPin, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 12 as an output
  Serial.begin(9600);
}

void setMotor(int motorspeed, boolean reverse){
  analogWrite(enablePin, motorspeed);
  digitalWrite(in1Pin, ! reverse);
  digitalWrite(in2Pin, reverse);
}

int curtime = 0;
int prevnote = 0;

void loop(){
  int total = 0;
  int thisNote;
  int change = 0;
  int control = 0;
  
  for(int i =0; i<27; i++){
    total += noteDurations[i];
    if(curtime%660<total){
      thisNote = i;
      if(thisNote!=prevnote){
        change = 1;
      }
      prevnote = i;
      break;
    }
  }
  
  control = int(analogRead(potPin)/200);
  
  int motorspeed = analogRead(potPin) / 4;
  Serial.println(analogRead(potPin));
  
  boolean reverse = digitalRead(switchPin);
//    Serial.println(analogRead(switchPin));
  
  setMotor(motorspeed, reverse);
  delay(5-control/2);

  
  int note = melody[thisNote];
  if(note!=0){
    note += control*50;
  }
  tone(buzzer, note, 20);
  delay(10-control);
  if(change ==1){
    delay(10-control);
  }

  noTone(buzzer);

  curtime += 1;
  
}
