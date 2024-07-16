typedef enum{
	DISENGAGED,
	ENGAGED,
} States;

const uint8_t ledPin = 3;
const uint8_t buttonPin = 2;  // the number of the pushbutton pin
const uint8_t powerlogicPin = 3;
const uint8_t mask = 0x01;

void ChangeStateCyclically(States* pState);
void BlinkToPermanent();
void PermanentToBlink();
void PowerON();
void PowerOFF();
