#include "Powerhandler.h"

#ifndef RADIO
#define RADIO

#include "radio.h"

#endif

States execState = States::DISENGAGED;

RadioPayload switchRequest;

RF24 radio(ce, csn); // CE, CSN

Powerhandler powerhandler;

RadioPayload payload = {state{States::DISENGAGED}};

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin as an output.
  
  pinMode(Powerhandler::POWER_LOGIC_PIN, OUTPUT);

  digitalWrite(Powerhandler::POWER_LOGIC_PIN, HIGH);

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

  radio.openWritingPipe(addresses[1]); // 00002
  radio.openReadingPipe(1, addresses[0]); // 00001
  radio.stopListening(); 

  powerhandler.PowerOFF();
}




// the loop function runs over and over again forever
void loop() 
{
  delay(5);

  radio.stopListening();
  
  // Propagation Broadcast execState
  bool ok = radio.write(&payload, sizeof(payload));

  if (ok)
  {
    Serial.println(payload.state);
  }

  delay(5);
  radio.startListening();

  if (radio.available())
  {
    // Reset request before reading to be shure reading is performed
    switchRequest.request = LOW;

    while (radio.available())
    {  
      radio.read(&switchRequest, sizeof(switchRequest));
    }

    if (switchRequest.request == HIGH) 
    {    
      powerhandler.ChangeStateCyclically(&execState);
    } 

  }

  if (execState == States::ENGAGED)
  {    
    powerhandler.PowerON();    
  } 
  else
  {
    powerhandler.PowerOFF();
  }
  
}
