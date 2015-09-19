#include "io430.h"

// Procedure to configure clock
void configureClock();

int main() {
  // Stop watchdog timer
  WDTCTL = WDTPW + WDTHOLD;
  
  configureClock();
  
  // Configre GPIO
  P1DIR |= BIT0;
  P1OUT &= ~BIT0;
  
  while (1) {
    P1OUT ^= BIT0;
    
    __delay_cycles(125000);
  }
}

void configureClock() {
  // DCO clock is at 1 MHz
  BCSCTL1 = CALBC1_1MHZ;
  DCOCTL = CALDCO_1MHZ;
  
  // Divide MCLK by a factor of 8
  BCSCTL2 |= DIVM1 | DIVM0;
}
