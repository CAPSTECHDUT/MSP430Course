#include <msp430.h> 

void clockSetup();

int main(void) {
  WDTCTL = WDTPW | WDTHOLD;             // Stop watchdog timer

  clockSetup();
  
  TACCTL0 = CCIE;                           // Enable CCR0 interrupt
  TACCR0 = 62500;                           // Setting CCRO value
  TACTL = TASSEL_2 + ID_3 + MC_3;           // SMCLK/8, up/down mode

  
  P1DIR |= BIT0;

  __bis_SR_register(LPM0_bits + GIE);
  return 0;
}

// Setting MCLK SMCLK = DCO = 1MHz, ACLK = VLO ~ 12kHz
void clockSetup() {
  BCSCTL1 = CALBC1_1MHZ;                    // Set DCO to 1MHz
  DCOCTL =  CALDCO_1MHZ; 
  BCSCTL3 |= LFXT1S_2;                      // Set ACLK = VLO
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void ISR(void) {
  P1OUT ^= BIT0 | BIT6;
}
