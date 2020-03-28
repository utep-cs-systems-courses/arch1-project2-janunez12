#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"

int main(void)

{
  configureClocks();
  switch_init();
  buzzer_init();
  led_init();

  enableWDTInterrupts(); //Enable Watch Dog Timer
  or_sr(0x18);          // CPU off, GIE on

  return 0;
}

