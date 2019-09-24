/*
Adafruit Arduino - Lesson 14. Sweep
*/
 
#include <Servo.h> 
#include <Stepper.h>


int xPin = A1;
int yPin = A0;
int buttonPin = 2;

int xPosition = 0;
int yPosition = 0;
int buttonState = 0;

int in1Pin = 12;
int in2Pin = 11;
int in3Pin = 10;
int in4Pin = 9;

Stepper motor(512, in1Pin, in2Pin, in3Pin, in4Pin);  

int servoPin = 3;
 
Servo servo;  
 
int angle = 0;   // servo position in degrees 
 
void setup() 
{ 
  servo.attach(servoPin); 

  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);
  
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  Serial.begin(9600); 
  motor.setSpeed(20);

  //activate pull-up resistor on the push-button pin
  pinMode(buttonPin, INPUT_PULLUP); 
 
} 

 
void loop() 
{ 
  xPosition = analogRead(xPin);
  Serial.print("X: ");
  Serial.println(xPosition);
  if(xPosition>800){
    for(int i =0; i<20; i++){
      if(angle>0){
        angle-=3;
        servo.write(angle);
      }
      motor.step(10); 
    }
    
      
  }
//
  else if(xPosition<200){

    for(int i =0; i<20; i++){
      if(angle<180){
        angle+=3;
        servo.write(angle);  
                 
      }
      motor.step(-10); 
    }
    
  }

  delay(10); // add some delay between reads
}
