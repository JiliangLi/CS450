/*
 * Sep 9, 2019
 * Eric Li
Adafruit Arduino - Lesson 3. RGB LED
*/

int redPin = 11;
int greenPin = 10;
int bluePin = 9;

  
void setup()
{
pinMode(redPin, OUTPUT);
pinMode(greenPin, OUTPUT);
pinMode(bluePin, OUTPUT);
}

void loop()
{
  int redcolor = 100;
  int greencolor = 100;
  int bluecolor = 100;
  int redcount = 0;
  int greencount = 0;
  int bluecount = 0;
  
  while(true){
    long randnumred = random(0,10);
    if(redcount%2==0){
      if(redcolor+randnumred<255){
        redcolor+=randnumred;
        }
      else{
        redcount+=1;
      }
    }

    else{
      if(redcolor-randnumred>0){
        redcolor-=randnumred;
      }
      else{
        redcount+=1;
      }
    }

    
    long randnumgreen = random(0,30);
    if(greencount%2==0){
      if(greencolor+randnumgreen<255){
        greencolor+=randnumgreen;
        }
      else{
        greencount+=1;
      }
    }

    else{
      if(greencolor-randnumgreen>0){
        greencolor-=randnumgreen;
      }
      else{
        greencount+=1;
      }
    }    


    long randnumblue = random(0,20);
    if(bluecount%2==0){
      if(bluecolor+randnumblue<255){
        bluecolor+=randnumblue;
        }
      else{
        bluecount+=1;
      }
    }

    else{
      if(bluecolor-randnumblue>0){
        bluecolor-=randnumblue;
      }
      else{
        bluecount+=1;
      }
    }
    setColor(redcolor, greencolor, bluecolor);
    delay(15);
  }
}

void setColor(int red, int green, int blue)
{
analogWrite(redPin, red);
analogWrite(greenPin, green);
analogWrite(bluePin, blue);
}
