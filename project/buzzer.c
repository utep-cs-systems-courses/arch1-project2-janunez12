#include "libTimer.h"
#include "buzzer.h"
#include <msp430.h>

static int counterSuperMario = 0;    //Counter to keep track of the notes in SuperMario song
static int counterTitanic = 0;   //Counter to keep track of the notes in Titanic song

void buzzer_init(){
  /*
    Direct timer A output "TA0.1" to P2.6.
    According to table 21 from data sheet:
    P2SEL2.6, P2SEL2.7, and P2SEL.7 must be zero
    P2SEL.6 must be 1
    Also: P2.6 direction must be output
  */

  timerAUpmode(); //used to drive speaker
  P2SEL2 &= ~(BIT6 | BIT7);
  P2SEL &= ~BIT7;
  P2SEL |= BIT6;
  P2DIR = BIT6; //enable output to speaker (P2.6)
}

/*
  Super Mario is a method which calls the buzzer_set_period method
  from the buzzer.h file to produce the sound of the frequency specified on
  each case. When the method is called consistently, the song Super Mario
  is played on the MSP430's speaker.
*/

void superMario(){

  switch(counterSuperMario){
  case 0:
  case 1:
  case 2:
  case 4:
  case 9:
  case 15:
  case 20: buzzer_set_period(758); counterSuperMario++; break; //E5 note Fq 659.25
  case 3:
  case 7:
  case 21: buzzer_set_period(956); counterSuperMario++; break; //C5 note Fq 523.25
  case 5:
  case 6:
  case 8:
  case 14:
  case 16:
  case 19: buzzer_set_period(638); counterSuperMario++; break; //G5 note Fq 783.99
  case 10:
  case 13:
  case 17: buzzer_set_period(568); counterSuperMario++; break; //A5 note Fq 880.00
  case 11:
  case 23: buzzer_set_period(506); if(counterSuperMario==23){counterSuperMario = 0;} else{counterSuperMario++;}; break; //B5 note Fq 987.77
  case 12: buzzer_set_period(536); counterSuperMario++; break; //A#5 note Fq 932.33
  case 18: buzzer_set_period(716); counterSuperMario++; break; //F5 note Fq 698.46
  case 22: buzzer_set_period(851); counterSuperMario++; break; //D5 note Fq 587.33
  }
}

/*
  Titanic is a method which calls the buzzer_set_period method
  from the buzzer.h file to produce the sound of the frequency specified on
  each case. When the method is called consistently, the song Titanic
  is played on the MSP430's speaker.
*/

void titanic(){

  switch(counterTitanic){
  case 0:
  case 1:
  case 2:
  case 3:
  case 5:
  case 6:
  case 8:
  case 12:
  case 13:
  case 14:
  case 15:
  case 17:
  case 18:
  case 20:
  case 31:
  case 33:
  case 34:
  case 36:
  case 47:
  case 49:
  case 50:
  case 52:
  case 56: buzzer_set_period(638); if(counterTitanic==56){counterTitanic = 0;} else{counterTitanic++;}; break; //G5 Fq 783.99
  case 4:
  case 7:
  case 16:
  case 32:
  case 48:
  case 51: buzzer_set_period(676);counterTitanic++; break; //F# Fq 739.99
  case 9:
  case 11:
  case 21:
  case 26:
  case 30:
  case 37:
  case 42:
  case 46:
  case 53:
  case 55: buzzer_set_period(568);counterTitanic++;break;  //A5 Fq 880.00
  case 10:
  case 25:
  case 27:
  case 29:
  case 41:
  case 43:
  case 45:
  case 54: buzzer_set_period(506);counterTitanic++;break;  //B5 Fq 987.77
  case 19:
  case 22:
  case 35:
  case 38: buzzer_set_period(851);counterTitanic++;break;  //D5 Fq 587.33
  case 23:
  case 39: buzzer_set_period(426);counterTitanic++;break;  //^D Fq 1174.66
  case 24:
  case 28:
  case 40:
  case 44: buzzer_set_period(478);counterTitanic++;break;  //^C Fq 1046.50
  }
}

void buzzer_set_period(short cycles){
  CCR0 = cycles;
  CCR1 = cycles >> 1; //one half cycle
}
