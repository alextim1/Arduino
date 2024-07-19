#include "Powerhandler.h"

//---------------Definition Section ------------------------------

Powerhandler::Powerhandler(/* args */)
{
}

Powerhandler::~Powerhandler()
{
}

void Powerhandler::ChangeStateCyclically(States* pState)
{
    *pState = (*pState + 0x01)&this._mask;
}

void Powerhandler::PowerON(void)
{
    digitalWrite(powerhandler::POWER_LOGIC_PIN, LOW);
}

void Powerhandler::PowerOFF(void)
{
    digitalWrite(powerhandler::POWER_LOGIC_PIN, HIGH);
}




