#include <blink.h>
#include <radio.h>
#include <stdint.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

uint8_t switchRequest = LOW;

uint8_t buttonState = HIGH;

uint8_t previousButtonState = HIGH;

States execState = DISENGAGED;

RF24 radio(ce, csn); // CE, CSN


void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);

  pinMode(buttonPin, INPUT_PULLUP);


  radio.begin();
  radio.openWritingPipe(addresses[0]); // 00001
  radio.openReadingPipe(1, addresses[1]); // 00002
  radio.setPALevel(RF24_PA_MIN);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  radio.startListening();
  
  // blocking synch
  while (!radio.available()) 
      
  radio.read(&execState, sizeof(execState));
      
    
  Serial.println(execState);
  

  
  
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  
  // debounce filter
  delay(10);

  // check if the pushbutton is pressed and released:
  if (buttonState == HIGH && previousButtonState == LOW) {
    
    radio.stopListening();

    switchRequest = HIGH;
    
    bool ok = radio.write(&switchRequest, sizeof(switchRequest));

    if (ok) Serial.println(switchRequest);

  } 

  
  
  previousButtonState = buttonState;
  buttonState = HIGH;
  switchRequest = LOW;
}
