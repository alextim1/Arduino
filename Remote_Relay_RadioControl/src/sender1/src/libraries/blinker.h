#ifndef STDINT
#define STDINT

#include <stdint.h>

#endif

enum class States: uint8_t  
{
	DISENGAGED = 0U,
	ENGAGED = 1U,
};


class Blinker
{
	private:
		//---------------Service Constants Section-----------------------------

		static constexpr uint8_t DELAY_BLINKING_DISENGAGED{100};
		static constexpr uint8_t DELAY_BLINKING_UNDEFINED{50};

		//---------------Private Fields---------------------------------
		uint8_t _darkDelay = DELAY_BLINKING_DISENGAGED;

		uint8_t _lightDelay = DELAY_BLINKING_DISENGAGED;

	public:
		//---------------Pin--Mapping--Constants--Section---------------

		static constexpr uint8_t LED_PIN{3};
		static constexpr uint8_t BUTTON_PIN{2};  // the number of the pushbutton pin
		
		//---------------Declaration Section ------------------------------

		void BlinkToPermanent(void);
		void PermanentToBlink(void);
		void BlinkUnknownState(void);
		void LedSignal(void);
};
