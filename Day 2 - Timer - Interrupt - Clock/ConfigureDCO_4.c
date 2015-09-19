#include "io430.h"
 
// Procedure to configure clock
void configureClock();

int main( void ) {
  // Stop watchdog timer
  WDTCTL = WDTPW + WDTHOLD;
  
  configureClock();
  
  // Configre GPIO
  P1DIR |= BIT0;
  P1OUT &= ~BIT0;
  
  while (1) {
    P1OUT ^= BIT0;
    
    __delay_cycles(312000);
  }
}

void configureClock() {
  // Set range RSEL = 3
  BCSCTL1 &= ~(RSEL3 | RSEL2);
  BCSCTL1 |= RSEL1 | RSEL0;
  
  // Set step DCO = 3
  DCOCTL &= ~DCO2;
  DCOCTL |= (DCO1 | DCO0);
  DCOCTL &= ~(MOD3 | MOD2 | MOD1 | MOD0);
  DCOCTL |= MOD4;
  // DCO(3, 3) = 0.3 MHz
  // DCO(3, 4) = SDCO * DCO(3, 3) = 0.324
  // MOD = 16 
  // -> f = [DCO(3, 3) + DCO(3, 4)] / 2 = 0.312 MHz
}