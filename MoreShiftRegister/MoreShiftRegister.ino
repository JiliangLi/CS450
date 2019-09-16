/*
* Eric Li
* Sep 15
 */
 
//
// Use one 74HC595 to control a 12-pin common-anode 4-digit seven-segment display with fast scanning
// the display: http://www.icshop.com.tw/product_info.php/products_id/19357
//https://docs.labs.mediatek.com/resource/linkit7697-arduino/en/tutorial/driving-7-segment-displays-with-74hc595
//

#define DELAY_FACTOR  (100)
#define NUM_OF_DIGITS (4)

// 4 display on/off pin (for the common anode/cathode)
const int control_pins[NUM_OF_DIGITS] = {2, 7, 12, 13};
// pin 11 of 74HC595 (SHCP)
const int bit_clock_pin = 6;
// pin 12 of 74HC595 (STCP)
const int digit_clock_pin = 5;
// pin 14 of 74HC595 (DS)
const int data_pin = 4;
const int trigPin = 9;
const int echoPin = 10;

long duration1;
long duration2;
int distance;

int potPin = 1;

// digit pattern for a 7-segment display
const byte digit_pattern[16] =
{
  ~B00111111,  // 0
  ~B00000110,  // 1
  ~B01011011,  // 2
  ~B01001111,  // 3
  ~B01100110,  // 4
  ~B01101101,  // 5
  ~B01111101,  // 6
  ~B00000111,  // 7
  ~B01111111,  // 8
  ~B01101111,  // 9
  ~B01110111,  // A
  ~B01111100,  // b
  ~B00111001,  // C
  ~B01011110,  // d
  ~B01111001,  // E
  ~B01110001   // F
};

int digit_data[NUM_OF_DIGITS] = {0};
int scan_position = 0;

unsigned int counter = 0;

void setup(){
  int i;

  // set related pins as output pins
  for (i = 0; i < NUM_OF_DIGITS; i++){
    pinMode(control_pins[i], OUTPUT);
  }

  pinMode(data_pin, OUTPUT);
  pinMode(bit_clock_pin, OUTPUT);
  pinMode(digit_clock_pin, OUTPUT);  
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  Serial.begin(9600); 
}



void update_one_digit(){
  int i;
  byte pattern;
  
  // turn off all digit
  for (i = 0; i < NUM_OF_DIGITS; i++){
    digitalWrite(control_pins[i], HIGH);
  }

  // get the digit pattern of the position to be updated
  pattern = digit_pattern[digit_data[scan_position]];

  // turn off the output of 74HC595
  digitalWrite(digit_clock_pin, LOW);
  
  // update data pattern to be outputed from 74HC595
  // because it's a common anode LED, the pattern needs to be inverted
  shiftOut(data_pin, bit_clock_pin, MSBFIRST, ~pattern);
  
  // turn on the output of 74HC595
  digitalWrite(digit_clock_pin, HIGH);

  // turn on the digit to be updated in this round
  digitalWrite(control_pins[scan_position], LOW);

  // go to next update position
  scan_position++;
  
  if (scan_position >= NUM_OF_DIGITS){
    scan_position = 0; 
  }
}

unsigned int number;
long lastUpdate = 0;
long lastRead = 0;

void loop(){ 
  lastUpdate = micros();
  int i;
  unsigned int digit_base;

  if (millis() - lastRead > 200){
    lastRead = millis();
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
  
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    int reading = analogRead(potPin);
    if(reading<=500){
      number = int (pulseIn(echoPin, HIGH) * 0.034/2);
    }
    else{
      number = int (pulseIn(echoPin, HIGH) * 0.034/5.08);
    }
  }

  digit_base = 10;

  // get every values in each position of those 4 digits based on "digit_base"
  //
  // digit_base should be <= 16
  //
  // for example, if digit_base := 2, binary values will be shown. If digit_base := 16, hexidecimal values will be shown
  //
  unsigned int temp = number;
  
  for (i = 0; i < NUM_OF_DIGITS; i++)
  {
    digit_data[i] = temp % digit_base;
    temp /= digit_base;
  }

  // update one digit
  update_one_digit();
  
  
  delayMicroseconds(400 - (micros() - lastUpdate));
}
