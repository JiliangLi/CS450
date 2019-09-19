const int buzzer = 12; //buzzer to arduino pin 12


void setup(){
 
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 12 as an output
  Serial.begin(9600);

}

int melody[] = {
  493.88, 0, 493.88, 493.88, 493.88, 440, 493.88, 493.88, 0, 493.88, 493.88, 493.88, 440, 493.88, 493.88, 0, 587.33, 493.88, 0, 440, 392, 0, 329.63, 329.63, 369.99, 392, 329.63};


// note durations: 4 = quarter note, 8 = eighth note, etc.:
long noteDurations[] = {
  4, 4, 8, 16, 16, 16, 5.3, 4, 4, 8, 16, 16, 16, 5.3, 4, 8, 4, 8, 8, 4, 8, 8, 8, 8, 8, 8, 8, 8};

void loop(){


  for (int thisNote = 0; thisNote < 27; thisNote++) {
      int noteDuration = 1000/noteDurations[thisNote];
      int note = melody[thisNote];
      if(note!=0){
        note += 0;
      }
      tone(buzzer, note, noteDuration);

      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      noTone(buzzer);
      }
}
