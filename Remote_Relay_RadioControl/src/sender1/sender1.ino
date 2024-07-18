#include "radio.h"

#ifndef BLINK
#define BLINK

#include "blink.h"

#endif

#ifndef RADIO
#define RADIO

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#endif

#ifndef STDINT
#define STDINT

#include <stdint.h>

#endif

#define MISSING_RADIO_SIGNAL_DELAY_MS 20


Blinker blinker;

uint8_t buttonState = HIGH;

uint8_t previousButtonState = HIGH;

States execState = States::DISENGAGED;

RF24 radio(ce, csn); // CE, CSN

RadioPayload payload;


void setup() {
  // put your setup code here, to run once:
  pinMode(blinker.LED_PIN, OUTPUT);

  pinMode(blinker.BUTTON_PIN, INPUT_PULLUP);

  Serial.begin(115200); 
  radio.begin(); 
  //Append ACK packet from the receiving radio back to the transmitting radio 
  radio.setAutoAck(false); //(true|false) 
  //Set the transmission datarate 
  radio.setDataRate(RF24_1MBPS); //(RF24_250KBPS|RF24_1MBPS|RF24_2MBPS) 
  //Greater level = more consumption = longer distance 
  radio.setPALevel(RF24_PA_MAX); //(RF24_PA_MIN|RF24_PA_LOW|RF24_PA_HIGH|RF24_PA_MAX) 
  //Default value is the maximum 32 bytes 
  radio.setPayloadSize(sizeof(payload)); 

  radio.openWritingPipe(addresses[0]); // 00001
  radio.openReadingPipe(1, addresses[1]); // 00002
  radio.stopListening(); 

  PermanentToBlink();
}

void loop() {
  
  radio.startListening();
  blinker.LedSignal();
  
  // blocking synch
  uint8_t radioMissingCyclesCounter = 0;

  while (!radio.available()){
    blinker.LedSignal();
    
    if (radioMissingCyclesCounter < MISSING_RADIO_SIGNAL_DELAY_MS){
      radioMissingCyclesCounter++;
    }
    else {
      blinker.BlinkUnknownState();
    }
  } 

  // now radio is available - Update Execution State via Radio  
  radio.read(&payload, sizeof(payload));
  execState = payload.state;  
  Serial.println(execState); 

  if (execState == ENGAGED){
    blinker.BlinkToPermanent();    
  }else{
    blinker.PermanentToBlink();
  }


  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  
  // debounce filter
  delay(10);

  // check if the pushbutton is pressed and released:
  if (buttonState == HIGH && previousButtonState == LOW) {
    
    radio.stopListening();

    RadioPayload request;
    
    bool ok = radio.write(&request, sizeof(request));

    if (ok) Serial.println("Request Sent");

  }  
  previousButtonState = buttonState;
  buttonState = HIGH;

}

