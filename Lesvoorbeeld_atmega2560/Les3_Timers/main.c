/*
 * Lesvoorbeeld_atmega2560.c
 *
 * Created: 10/02/2020 18:26:21
 * Author : Etienne
 */ 

#define F_CPU 16e6

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


// Build in led Arduino on PB7 (pin 13)
void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

void setupTimer(void) {

	 cli(); // Disable interrupts

	 // SETUP CLOCK AT FREQUENCY OF 1 HZ
	 TCCR1A = 0;// set entire TCCR1A register to 0
	 TCCR1B = 0;// same for TCCR1B
	 TCNT1  = 0;//initialize counter value to 0
	 // set compare match register for 1hz increments
	 OCR1A = 15624;// = (16*10^6) / (1*1024) - 1 (must be <65536)
	 // turn on CTC mode
	 TCCR1B |= (1 << WGM12);
	 // Set CS12 and CS10 bits for 1024 prescaler  (pg 130)
	 TCCR1B |= (1 << CS12) | (1 << CS10);
	 // enable timer compare interrupt
	 TIMSK1 |= (1 << OCIE4A);

	 sei();//allow interrupts
}



ISR(TIMER1_COMPA_vect){//timer1 interrupt 1Hz toggles pin 13 (LED)
	//generates pulse wave of frequency 1Hz/2 = 0.5kHz (takes two cycles for full wave- toggle high then toggle low)
	PORTB ^= (1<<7);
}


int main(void) {
	DDRB = 0xFF;
	setupTimer();
    while (1)  {
		wait(50);
    }
	return 0;
}

