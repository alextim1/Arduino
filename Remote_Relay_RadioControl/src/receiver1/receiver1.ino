#include "radio.h"

#ifndef BLINK
#define BLINK

#include "blink.h"

#endif

#ifndef RADIO
#define RADIO

#include <stdint.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#endif



States execState = DISENGAGED;

uint8_t switchRequest = LOW;

RF24 radio(ce, csn); // CE, CSN



// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(ledPin, OUTPUT);

  pinMode(signalPin, OUTPUT);

  pinMode(powerPin, OUTPUT);

  // pinMode(buttonPin, INPUT_PULLUP);

  digitalWrite(signalPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(powerPin, HIGH);

  radio.begin();
  radio.openWritingPipe(addresses[1]); // 000002
  radio.openReadingPipe(1, addresses[0]); // 000001
  radio.setPALevel(RF24_PA_MIN);

  Serial.begin(9600);
}




// the loop function runs over and over again forever
void loop() {

  

  delay(5);

  radio.stopListening();
  
  // Propagation Broadcast execState
  bool ok = radio.write(&execState, sizeof(execState));

  if (ok){
    Serial.println(execState);
  }

  delay(5);
  radio.startListening();

  if (radio.available()){
    while (radio.available()){
  
      radio.read(&switchRequest, sizeof(switchRequest));
    }

    if (switchRequest == HIGH) {
    
      ChangeStateCyclically(&execState);
    } 

  }

  if (execState == ENGAGED){
    
    StableSignalPowerON();
    
    PowerON();
    
  }else{
    StableSignalPowerOFF();
    BlinkSignalPowerOFF(); 
    PowerOFF();
  }
  
}

//*********************** Definition Section***********************************************
void ChangeStateCyclically(States* pState){
  *pState = (*pState + 0x01)&mask;

}

void BlinkSignalPowerOFF(){
  digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);                       // wait for a second
  digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
  delay(100);
}
void StableSignalPowerON(){
  digitalWrite(signalPin, HIGH);   // turn the LED on (HIGH is the voltage level)
}
void StableSignalPowerOFF(){
  digitalWrite(signalPin, LOW);   // turn off the LED on 
}
void PowerON(){
  digitalWrite(powerPin, LOW);
}
void PowerOFF(){
  digitalWrite(powerPin, HIGH);
}
