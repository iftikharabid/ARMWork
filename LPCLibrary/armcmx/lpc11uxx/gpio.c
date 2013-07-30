
#include "LPC11Uxx.h"			/* LPC11xx Peripheral Registers */
#include "gpio.h"

void GPIOInit( void )
{
  /* Enable AHB clock to the GPIO domain. */
  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6);

  /* Enable AHB clock to the FlexInt, GroupedInt domain. */
  LPC_SYSCON->SYSAHBCLKCTRL |= ((1<<19) | (1<<23) | (1<<24));

  return;
}

void pinMode( GPIOPin pin, uint8_t dir ) {
  if( dir ) {
    LPC_GPIO->DIR[PIONumber[pin>>5]] |= (1<<(pin&0x1f));
  } else {
    LPC_GPIO->DIR[PIONumber[pin>>5]] &= ~(1<<(pin&0x1f));
  }
  return;
}

void digitalWrite(GPIOPin pin, uint8_t bitVal ) {
  if ( bitVal ) {
    LPC_GPIO->SET[PIONumber[pin>>5]] = 1<<(pin&0x1f);
  } else {
    LPC_GPIO->CLR[PIONumber[pin>>5]] = 1<<(pin&0x1f);
  }
  return;
}

uint8_t digitalRead(GPIOPin pin) {
  return (LPC_GPIO->PIN[PIONumber[pin>>5]] & (1<<(pin&0x1f))) != 0;
}

uint8_t digitalToggle(GPIOPin pin) {
  if ( LPC_GPIO->PIN[PIONumber[pin>>5]] & (1<<(pin&0x1f)) ) {
    LPC_GPIO->CLR[PIONumber[pin>>5]] = 1<<(pin&0x1f);
    return 1;
  } else {
    LPC_GPIO->SET[PIONumber[pin>>5]] = 1<<(pin&0x1f);
    return 0;
  }
}
