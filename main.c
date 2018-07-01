#include "TLC5971.h"
#include <unistd.h>

#define PIN_SCKI 5
#define PIN_SDTI 4

int main (void)
{
  TLC5971 leds(0, PIN_SCKI, PIN_SDTI);
  
  leds.set_current_ma(15);
  //leds.set_8bit_color(0, 255, 197, 143); // 2600K - 40W Tungsten
  //leds.set_8bit_color(1, 255, 197, 143); // 2600K - 40W Tungsten
  leds.set_8bit_color(1, 0, 0, 255);
  leds.set_8bit_color(0, 0, 0, 255);
  leds.write();
  
  leds.set_blank(true);
  leds.printConfig();
  leds.write();

  //usleep(5000000); //sleep 5s
  //leds.set_blank(false);
  //leds.write();

  return 0;
}
