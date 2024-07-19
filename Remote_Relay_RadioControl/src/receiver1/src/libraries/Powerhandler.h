#include "states.h"

#ifndef STDINT
#define STDINT

#include <stdint.h>

#endif

class Powerhandler
{
private:
    /* data */
    //---------------Service Constants Section-----------------------------
    const uint8_t _mask = 0x01;
public:
    //---------------Pin--Mapping--Constants--Section---------------

    static constexpr uint8_t POWER_LOGIC_PIN{3};

    //---------------Declarations-----------------------------------
    Powerhandler(/* args */);
    ~Powerhandler();

    void ChangeStateCyclically(States* pState);

    void PowerON(void);
    void PowerOFF(void);
};



