/*
	based on examples, tone keyboard and debounce 
	but I re design the logic and actually the whole thing
	
	pin assign rearranged for shrimp ic layout convenience
	
	circuit:
	* pushbutton attached from pin 2 to +5V
	* 10K resistor attached from pin 2 to ground
	
	* Note: On most Arduino boards, there is already an LED on the board
	connected to pin 13

	* 8-ohm speaker or piezo on digital pin 9  
 	*mini 1
*/

#include "pitches.h"

const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // LED pin
const int output1 =10;    //for controlling external stuff
const int soundPin = 9;

int sndfree=1;
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 1300;    // the debounce time; increase if the output flickers

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
}
  
void loop() {
 
  int reading = digitalRead(buttonPin);
  
  if (reading==HIGH && sndfree==1){
     tone(soundPin, NOTE_G5, 200 );
     digitalWrite(ledPin, HIGH);
     sndfree=0; //ban any further snd play
     resettimer();
  }
   
  if (reading==HIGH && sndfree==0){
    //before sndfree is reset, any more trigger reset the timer
    resettimer();
  }
  
  //only if let go and stay LOW for the period of time, AND sound had triggered
  if ( millis() > ( lastDebounceTime + debounceDelay) && sndfree==0 ) {
    sndfree=1;
    digitalWrite(ledPin, LOW);
  }
   
}

void dosomething(){
}

void resettimer(){
  lastDebounceTime = millis();
}
