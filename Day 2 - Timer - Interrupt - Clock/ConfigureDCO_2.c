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
    
    __delay_cycles(265000);
  }
}

void configureClock() {
  // DCO(2, 6) = 0.265 MHz
  // Set range
  BCSCTL1 &= ~(RSEL3 | RSEL2 | RSEL0);
  BCSCTL1 |= RSEL1;
  
  // Set step
  DCOCTL &= ~DCO0;
  DCOCTL |= DCO2 | DCO1; 
}