// main.c
//
// A simple blinky program for ATtiny85
// Connect red LED at pin 2 (PB3)
//
// electronut.in

#define F_CPU				1000000UL
#define RESET_VIA_WATCHDOG	0x8
#define CCP_ENABLE_REGS		0xd8
#define	CCP_ENABLE_FLASH	0xe7

#include <avr/common.h>
#include <avr/sleep.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <util/delay.h>


int main (void)
	{
	// power reduction
	PRR = 0b111;

	// enable interrupts globally
	SREG |= 0b10000000;

	// set PB3 to be output
	DDRB |= 1<<PB1;
	while (1)
		{
		// flicker
		for(int i=0;i<3;i++)
			{
			//set high
			PORTB |= 1<<PB1;
			_delay_ms(5);
			// set PB3 low
			PORTB ^= 1<<PB1;
			_delay_ms(80);
			}

		// set up watchdog
		RSTFLR ^= 1<<WDRF;
		WDTCSR = 0b01000111;

		// then go to sleep
		set_sleep_mode(SLEEP_MODE_PWR_DOWN);
		sleep_enable();
		sleep_mode();
		//wdt wakes us up
		sleep_disable();
		
		//_delay_ms(2000);
		}
	
	return 1;
	}