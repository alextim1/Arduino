#include "blinker.h"

//--------------------------------- Defenition Section -----------------------
void Blinker::BlinkToPermanent(void)
{
  this._darkDelay = 0;
  this._lightDelay = 200;
}
void Blinker::PermanentToBlink(void)
{
  this._darkDelay = delayBlinkingDisengaged;
  this._lightDelay = delayBlinkingDisengaged;
}
void Blinker::BlinkUnknownState(void)
{
  this._darkDelay = delayBlinkingUndefined;
  this._lightDelay = delayBlinkingUndefined;
}
void Blinker::LedSignal(void)
{
  digitalWrite(this.LED_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(this._lightDelay);                       // wait for a second
  digitalWrite(this.LED_PIN, LOW);    // turn the LED off by making the voltage LOW
  delay(this._darkDelay);
  digitalWrite(this.LED_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(this._lightDelay);                       // wait for a second
  digitalWrite(this.LED_PIN, LOW);    // turn the LED off by making the voltage LOW
  delay(this._darkDelay);
}