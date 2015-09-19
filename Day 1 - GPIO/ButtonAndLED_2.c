/* ButtonAndLED_1.c - Control a LED via a button
    Press for the first time - Turn on LED
    Press for the second time - Turn off LED
*/
#include "io430.h"

#define LED        BIT0
#define BUTTON     BIT3

int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  
  P1DIR |= LED;               // Set LED pin as output
  P1OUT &= ~LED;
  P1REN |= BUTTON;            // Enable BUTTON pin pullup resistor
  P1OUT |= BUTTON;            // Use pullup resistor

  while(1) {
    if((P1IN & BUTTON)) {     // Button is not pressed
        while((P1IN & BUTTON)) {  // Do nothing when button is not pressed
        }

        P1OUT ^= LED;         // When button is pressed, toggle LED
        __delay_cycles(50);   // Delay to debounce
    }
  }
}