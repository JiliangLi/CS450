//
// Eric Li
// Sep 16, 2019
//

// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;
// defines variables
long duration;
int distance;

int countnum = 50;
int allData[50];
int count = 0;
int allDistance[180];


#include <Servo.h> 
int servoPin = 8;
Servo servo;  
 
int angle = 0;   // servo position in degrees 
 
void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  servo.attach(servoPin); 
  
  Serial.begin(9600); // Starts the serial communication
  }

void loop(){
  for(angle = 0; angle < 180; angle++)  
  {                                  
    servo.write(angle);
    int thedistance = countdistance();
//    delay(100);
    allDistance[angle] = thedistance;
    Serial.println(thedistance);               
  } 

  int smallest = 0;
  for(int i=0; i<180; i++){
    if(allDistance[i]<allDistance[smallest]){
      smallest = i;
    }
  }
      Serial.print("smallest ");               

      Serial.println(smallest);               

  // now scan back from 180 to 0 degrees
  for(angle = 180; angle >=0; angle--)    
  {
    if(angle==smallest){
      servo.write(angle);
      delay(3000);                                
    }
    else{
      servo.write(angle);           
      delay(5);      
    }
      
  } 
        

}

  
int countdistance() {
  for(int i=0; i<countnum; i++){
    if(count<countnum){
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
    
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
    
      duration = pulseIn(echoPin, HIGH);
  
      allData[count] = duration;
      count+=1; 
  
    }
  
    else{
      int avg = 0;
      int deviation = 0;
      int peak = 0;
      int finalavg = 0;
      int remain = 0;
  
      for(int i=0; i<countnum; i++){
        avg += allData[i];
      }
      avg = avg/countnum;
      for(int i=0; i<countnum; i++){
        deviation += (sq(allData[i]-avg))/(countnum-1);
      }
      deviation = sqrt(deviation);
      
      for(int i=0; i<countnum-1; i++){
        for(int j=i+1; j<countnum; j++){
          if(i>j){
            int temp = allData[i];
            allData[i] = allData[j];
            allData[j] = allData[i];
          }
        }
      }
  
      peak = allData[int(countnum/2)];
  
      for(int i=0; i<countnum; i++){
        if(allData[i]>peak+deviation*2||allData[i]<peak-deviation*2){
          allData[i] = 0;
        }
        else{
          remain += 1;
        }
      }
      
      for(int i=0; i<countnum; i++){
        finalavg += allData[i];
      }
  
      finalavg = finalavg /remain;
      distance = finalavg;
      count = 0;
      
      distance= duration*0.034/2;
    
      Serial.print("Distance: ");
      Serial.println(distance);
      return distance;
    }
  }
}
