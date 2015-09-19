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
    
    __delay_cycles(150000);
  }
}

void configureClock() {
  // DCO(1, 3) = 0.15 MHz
  // Set range
  BCSCTL1 &= ~(RSEL3 | RSEL2 | RSEL1);
  BCSCTL1 |= RSEL0;
  
  // Set step
  DCOCTL &= ~DCO2;
  DCOCTL |= DCO1 | DCO0; 
}