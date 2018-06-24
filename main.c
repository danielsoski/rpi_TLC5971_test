#include "TLC5971.h"

#define PIN_SCKI 4
#define PIN_SDTI 5

int main (void)
{
  TLC5971 leds(0, PIN_SCKI, PIN_SDTI);
  leds.set_current_ma(10);
  leds.set_8bit_color(0, 255, 197, 143); // 2600K - 40W Tungsten
  leds.set_8bit_color(1, 255, 197, 143); // 2600K - 40W Tungsten
  //leds.set_blank(BLANK_ON);
  leds.printConfig();
  //leds.write();

  return 0;
}
