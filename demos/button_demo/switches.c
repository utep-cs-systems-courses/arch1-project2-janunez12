#include <msp430.h>
#include "switches.h"
#include "led.h"
 
void 
switch_init()			/* setup switch */
{  
  P1REN |= SWITCHES;		/* enables resistors for switches */
  P1IE = SWITCHES;		/* enable interrupts from switches */
  P1OUT |= SWITCHES;		/* pull-ups for switches */
  P1DIR &= ~SWITCHES;		/* set switches' bits for input */
}

void
switch_interrupt_handler()
{
  P1OUT |= LED_GREEN;
  P1OUT &= ~LED_RED;

  while(1){
    if(!(P1IN & SW1)){
      P1OUT ^= LEDS;
      __delay_cycles(100000);
    }
  }
}


