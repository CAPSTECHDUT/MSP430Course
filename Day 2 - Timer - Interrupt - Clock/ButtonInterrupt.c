#include "io430.h"

int cnt;
int main() {
  // Stop watchdog timer
  WDTCTL = WDTPW + WDTHOLD;
  
  // Configure pin 1.0 as output
  P1DIR |= BIT0;
  P1OUT &= ~BIT0;
  
  // Configure pin 1.3 as input
  // and enable interrupt for it
  P1DIR &= ~BIT3;
  P1REN |= BIT3;
  P1OUT |= BIT3;
  P1IE  |= BIT3;
  P1IES |= BIT3;
  P1IFG &= ~BIT3;
  
  // Enable GIE bit
  __bis_SR_register(GIE);
 }

// procedure that handles button interrupt event
#pragma vector = PORT1_VECTOR
__interrupt void PORT1_ISR() {
  cnt++;                // increment counter
  P1OUT ^= BIT0;        // Toggle led status
  P1IFG &= ~BIT3;       // Clear IFG to wait for the next interrupt
}