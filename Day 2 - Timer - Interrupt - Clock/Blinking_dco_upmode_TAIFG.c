#include <msp430.h> 

volatile unsigned char count = 0;

void clockSetup();

int main(void) {
  WDTCTL = WDTPW | WDTHOLD;             // Stop watchdog timer

  clockSetup();
  
  TACCR0 = 62500;
  TACTL = TASSEL_2 + ID_3 + MC_1 + TAIE;           // SMCLK/8, up mode

  
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

#pragma vector = TIMER0_A1_VECTOR
__interrupt void ISR(void) {
 switch( TA0IV )
  {
    case  2:  break;                        // CCR1 not used
    case  4:  break;                        // CCR2 not used
    case 10:  count++;                      // overflow
              if(count == 2) {
                P1OUT ^= BIT0 | BIT6;         
                count = 0;
              }
              break;                                        
  }
}