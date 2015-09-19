/* ButtonAndLED_1.c - Control a LED via a button
    Pressed - Turn on LED
    Release - Turn off LED
*/
#include "io430.h"

#define LED         BIT0
#define BUTTON      BIT3

int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  
  P1DIR |= LED;               // Set LED pin as output
  P1REN |= BUTTON;            // Enable BUTTON pin pullup resistor
  P1OUT |= BUTTON;            // Use pullup resistor

  while(1) {
    if((P1IN & BUTTON)) {     // Button is not pressed
        P1OUT &= ~LED;
    }
    else {
        P1OUT |= LED;
    }
  }
}