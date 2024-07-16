typedef enum{
	DISENGAGED,
	ENGAGED,
} States;

//---------------Pin--Mapping--Constants--Section---------------

const uint8_t ledPin = 3;
const uint8_t buttonPin = 2;  // the number of the pushbutton pin
const uint8_t powerlogicPin = 3;

//---------------Service Constants Section-----------------------------
const uint8_t mask = 0x01;
const uint8_t delayBlinkingDisengaged = 100;
const uint8_t delayBlinkingUndefined = 50;

//---------------Declaration Section ------------------------------
void ChangeStateCyclically(States* pState);
void BlinkToPermanent();
void PermanentToBlink();
void BlinkUnknownState();
void LedSignal();
void PowerON();
void PowerOFF();
