#include <msp430.h>
#include "switches.h"
#include "buzzer.h"

/* Switch on P2 (S1) */
void __interrupt_vec(PORT2_VECTOR) Port_2(){

  if (P2IFG & SWITCHES) {      /* did a button cause this interrupt? */
    P2IFG &= ~SWITCHES;      /* clear pending sw interrupts */
    switch_interrupt_handler();  /* single handler for all switches */
  }
}

/*
  Interrupt to play each song loaded in the MSP430
  for a certain amount of time.
  The method switch_interrupt_hadler is used to
  check is a button on the MSP430 was pressed.
*/

void
__interrupt_vec(WDT_VECTOR) WDT(){

  static char decisecond_count = 0;

  if(++decisecond_count == tempo){
    int repeat = 1;
    while(repeat <= 5){
      int cnt = 0;
      buzzer_set_period(0);
      while(cnt < 30000){
	cnt++;
      }
      repeat++;
    }
    switch_interrupt_handler();
    decisecond_count = 0;
  }
}



