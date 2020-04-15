#include <msp430.h>
#include "stateMachine.h"
#include "switches.h"
#include "led.h"
#include "buzzer.h"
#include "libTimer.h"

char switch_state_down, switch_state_changed, tempo;
char switch0, switch1, switch2, switch3, switch4;

extern void toggle();

static char switch_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */

  P1IES |= (p2val & SWITCHES);  /* if switch up, sense down */
  P1IES &= (p2val | ~SWITCHES); /* if switch down, sense up */

  return p2val;
}

static char switch_option() {

  char p2val = switch_update_interrupt_sense();
  char switchState;

  if(p2val & SW1 && p2val & SW2 && p2val & SW3 && p2val & SW4){
    switchState = 0;

    return 0;
  }
  
  else if (!(p2val & SW1)){
    switchState = 1;

    return 1;
  }
  
  else if (!(p2val & SW2)){
    switchState = 2;

    return 2;
  }
  
  else if (!(p2val & SW3)){
    switchState = 3;
    return 3;

  }

  else if (!(p2val & SW4)){
    switchState = 4;

    return 4;
  }

  else return 0;
}

void switch_interrupt_handler() {

  char switchState = switch_option();

  switch (switchState) {
    // Initial State
  case 0:
    buzzer_set_period(0);
    switch_state_down = 0;
    break;

  case 1:
    superMario();
    tempo = 120;
    reset_state();
    switch_state_down = 1;
    break;

  case 2:
    titanic();
    tempo = 250;
    reset_state();
    switch_state_down = 1;
    break;
    
  case 3:
    aladdin();
    tempo = 250;
    reset_state();
    switch_state_down = 1;
    break;

  case 4:
    buzzer_set_period(0);
    reset_state();
    switch_state_down = 0;
    break;

  }
  if(switch_state_down){
    switch_state_changed = 1;
    led_update();

  }
  else {

    switch_state_changed = 1;
    led_update();
    dim_led();
  }
}

void dim_led(){
  unsigned int j;

  for(j = 1; j < 1200; j++)    // Increasing Intensity
    {
      P1OUT |= LED_RED;         // LED ON
      delay(j);                 // Delay for ON Time
      P1OUT &= ~LED_RED;        // LED OFF
      delay(1200-j);           // OFF Time = Period - ON Time
    }

  for(j = 1200; j > 1; j--)    // Decreasing Intensity
    {
      P1OUT |= LED_RED;         // LED ON
      delay(j);               // Delay for ON Time
      P1OUT &= ~LED_RED;        // LED OFF
      delay(1200-j);           // OFF Time = Period - ON Time
    }
  
  switch_state_changed = 0;
}

void delay(unsigned int t)          // Custom delay function
{
  unsigned int i;
  for(i = t; i > 0; i--)
    __delay_cycles(1);          // __delay_cycles accepts only constants !
}

void reset_state(){
  // red_on = 0;
  // green_on = 0;
  led_update();
}
