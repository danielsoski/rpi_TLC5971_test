#include "TLC5971.h"

#define PIN_SCKI 4
#define PIN_SDTI 5

int main (void)
{
  TLC5971 leds(1, PIN_SCKI, PIN_SDTI);
  leds.printConfig();

  return 0;
}
