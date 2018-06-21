#include <wiringPi.h>
#include <time.h>
#include <stdint.h>

#define PIN_SCKI 4
#define PIN_SDTI 5
#define T_SCALE 10000

#define CMD_WRITE 0x25
#define OUTTMG_FALL 0
#define OUTTMG_RISE 1
#define EXTGCK_INT 1
#define TMGRST_DIS 0
#define TMGRST_EN 1
#define DSPRPT_DIS 0
#define DSPRPT_EN 1
#define BLANK_ON 0
#define BLANK_OFF 1

#define BC_1MA  2
#define BC_10MA 21
#define BC_20MA 42
#define BC_30MA 63
#define BC_40MA 65
#define BC_50MA 106
#define BC_60MA 127

#define GS_10  6553
#define GS_20  13107
#define GS_30  19660
#define GS_40  26214
#define GS_50  32767
#define GS_60  39321
#define GS_70  45874
#define GS_80  52428
#define GS_90  58981
#define GS_100 65535

struct timespec tsetup = {.tv_sec=0, .tv_nsec=5L*T_SCALE};
struct timespec thold = {.tv_sec=0, .tv_nsec=3L*T_SCALE};
struct timespec twidth = {.tv_sec=0, .tv_nsec=10L*T_SCALE};

void sleep_setup() {
  nanosleep(&tsetup, NULL);
}

void sleep_width() {
  nanosleep(&twidth, NULL);
}

void sleep_hold() {
  nanosleep(&thold, NULL);
}

int send_bit(int val)
{
  if (val != 1 && val != 0) {
    return 0;
  }

  digitalWrite(PIN_SDTI, val);
  sleep_setup();
  digitalWrite(PIN_SCKI, HIGH);
  sleep_width();
  digitalWrite(PIN_SCKI, LOW);
  sleep_hold();
  digitalWrite(PIN_SDTI, LOW);

  return 1;
}

int send_6bits(uint8_t val) {
  int i;
  for (i=5; i>=0; i--) {
    send_bit((val >> i) & 0x1);
  }
  return 1;
}

int send_7bits(uint8_t val) {
  int i;
  for (i=6; i>=0; i--) {
    send_bit((val >> i) & 0x1);
  }
  return 1;
}

int send_16bits(uint16_t val) {
  int i;
  for (i=15; i>=0; i--) {
    send_bit((val >> i) & 0x1);
  }
  return 1;
}

int main (void)
{
  wiringPiSetup();
  pinMode(PIN_SCKI, OUTPUT);
  pinMode(PIN_SDTI, OUTPUT);

  send_6bits(CMD_WRITE);

  send_bit(OUTTMG_FALL);
  send_bit(EXTGCK_INT);
  send_bit(TMGRST_DIS);
  send_bit(DSPRPT_DIS);
  send_bit(BLANK_ON);

  send_7bits(BC_1MA); // BC BLUE 0-3
  send_7bits(BC_1MA); // BC GREEN 0-3
  send_7bits(BC_1MA); // BC RED 0-3

  send_16bits(0); // GS BLUE 3
  send_16bits(0); // GS GREEN 3
  send_16bits(0); // GS RED 3

  send_16bits(0); // GS BLUE 2
  send_16bits(0); // GS GREEN 2
  send_16bits(0); // GS RED 2

  send_16bits(GS_100); // GS BLUE 1
  send_16bits(GS_100); // GS GREEN 1
  send_16bits(GS_100); // GS RED 1

  send_16bits(GS_100); // GS BLUE 0
  send_16bits(GS_100); // GS GREEN 0
  send_16bits(GS_100); // GS RED 0

  return 0;
}
