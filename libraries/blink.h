typedef enum{
	DISENGAGED,
	ENGAGED,
} States;

const uint8_t ledPin = 5;
const uint8_t signalPin = 4;
const uint8_t buttonPin = 2;  // the number of the pushbutton pin
const uint8_t powerPin = 3;
const uint8_t mask = 0x01;

void ChangeStateCyclically(States* pState);
void BlinkSignalPowerOFF();
void StableSignalPowerON();
void StableSignalPowerOFF();
void PowerON();
void PowerOFF();
