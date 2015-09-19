/* 
BlinkingLED.c - Turn on and off a LED repeatly
*/
#include "io430.h"

int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  
  P1DIR |= BIT0;               // Set P1.0 as output

  while(1) {
    P1OUT ^= BIT0;             // Toggle P1.0
    __delay_cycles(100000);    // Delay for a while
  }
}