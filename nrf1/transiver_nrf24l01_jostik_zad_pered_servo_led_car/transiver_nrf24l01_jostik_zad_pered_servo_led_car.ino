#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
#define CE_PIN 9
#define CSN_PIN 10
const uint64_t pipe = 0xE8E8F0F0E1LL;
RF24 radio(CE_PIN, CSN_PIN);
int datos[3];
//int but=7;
Servo myservo;
int pot_x = 1;
int val_x;
void setup()
{
  pinMode(7, INPUT);
  pinMode(pot_x, INPUT);
  radio.begin();
  Serial.begin(9600);
  radio.openWritingPipe(pipe);
}

void loop()
{
  datos[0] = analogRead(0);
  datos[1] = digitalRead(7);
  val_x = analogRead(pot_x);
 // val_x = map(val_x, 0, 1023, 254, -254);
  datos[2] = val_x;
  bool ok = radio.write(datos, sizeof(datos));
  if (ok)
  {
   Serial.println(datos[0]);
    
  }
  //Serial.println(datos[1]);
  Serial.println(pot_x);

}
