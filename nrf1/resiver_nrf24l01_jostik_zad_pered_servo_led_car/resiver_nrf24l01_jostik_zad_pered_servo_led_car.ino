#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
const uint64_t pipe = 0xE8E8F0F0E1LL;
#define CE_PIN 9
#define CSN_PIN 10

RF24 radio(CE_PIN, CSN_PIN);
int datos[3];
int ENB = 5;
int IN4 = 6;
int IN3 = 7;
int led = 4;
long time = 0;
long debounce = 300;
boolean ledOn = false;
boolean lastBut = HIGH;
Servo servo; //объявляем переменную servo типа Servo

void setup()
{
  radio.begin();
  Serial.begin(9600);
  radio.openReadingPipe(1, pipe);
  radio.startListening();
  pinMode(ENB, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(led, OUTPUT);
  int val_led = 0;
  servo.attach(3);
}

void loop() {
  uint8_t numero_canal;
  if ( radio.available() )
  {
    radio.read(datos, sizeof(datos));
 //   Serial.print("Analog = " );
 //   Serial.println(datos[0]);
    int val = datos[0];
    int val1;

    val1 = map(val, 0, 1023, 254, -254);

    if (val1 >= 0)
    {
      analogWrite(ENB, val1);
      digitalWrite(IN4, LOW);
      digitalWrite(IN3, HIGH);
    }
    else
    {
      val1 = abs(val1); //Инвертируем значение -1,-2,-3 и т.д

      analogWrite(ENB, val1);
      digitalWrite(IN4, HIGH);
      digitalWrite(IN3, LOW);
    }

   Serial.print("data: ");
    Serial.println(val1);
  }

  if (datos[1] == 0 && lastBut == HIGH && millis() - time > debounce) // Управление светодиодом
  {
    ledOn = !ledOn;
    lastBut = HIGH;
    time = millis();
  }
  else // Иначе,
  {
    lastBut = digitalRead(lastBut);

  }
  digitalWrite(led, ledOn);

  //int ledval = datos[1];
  //int leds=abs(ledval);
  //Serial.println(ledOn);
  //digitalWrite(led,leds);
  int val_x = datos[2];
  val_x = map(val_x, 0, 1023, 80, -100);
  //Serial.println(datos[2]);
  servo.attach(3);
  servo.write(val_x);
  Serial.println(val_x);
}

