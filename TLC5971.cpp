// TLC5971.cpp

#include "TLC5971.h"
#include <wiringPi.h>
#include <iostream>

using namespace std;

TLC5971::TLC5971(int num, int pinSCKI, int pinSDTI)
{
    this->num = num;
    this->pinSCKI = pinSCKI;
    this->pinSDTI = pinSDTI;
    wiringPiSetup();
    pinMode(pinSCKI, OUTPUT);
    pinMode(pinSDTI, OUTPUT);
}

void TLC5971::sleep_setup() {
  nanosleep(&tsetup, NULL);
}

void TLC5971::sleep_width() {
  nanosleep(&twidth, NULL);
}

void TLC5971::sleep_hold() {
  nanosleep(&thold, NULL);
}

int TLC5971::send_bit(int val)
{
  if (val != 1 && val != 0) {
    return 0;
  }

  digitalWrite(this->pinSDTI, val);
  this->sleep_setup();
  digitalWrite(this->pinSCKI, HIGH);
  this->sleep_width();
  digitalWrite(this->pinSCKI, LOW);
  this->sleep_hold();
  digitalWrite(this->pinSDTI, LOW);

  return 1;
}

void TLC5971::send_bits(int len, uint16_t val) {
  int i;
  for (i=len-1; i>=0; i--) {
    this->send_bit((val >> i) & 0x1);
  }
}

void TLC5971::send_6bits(uint8_t val) {
  this->send_bits(6, val);
}

void TLC5971::send_7bits(uint8_t val) {
  this->send_bits(7, val);
}

void TLC5971::send_16bits(uint16_t val) {
  this->send_bits(16, val);
}

void TLC5971::printConfig()
{
  cout << "num: " << this->num << endl;
  cout << "pinSCKI: " << this->pinSCKI << endl;
  cout << "pinSDTI: " << this->pinSDTI << endl;

  cout << "config_outtmg: " << this->config_outtmg << endl;
  cout << "config_extgck: " << this->config_extgck << endl;
  cout << "config_tmgrst: " << this->config_tmgrst << endl;
  cout << "config_dsprpt: " << this->config_dsprpt << endl;
  cout << "config_blank: " << this->config_blank << endl;

  cout << "config_bc_r: " << (unsigned int)this->config_bc_r << endl;
  cout << "config_bc_g: " << (unsigned int)this->config_bc_g << endl;
  cout << "config_bc_b: " << (unsigned int)this->config_bc_b << endl;

  int i;
  for (i=0; i<4; i++) {
    cout << "config_gs_r[" << i << "]: " << this->config_gs_r[i] << endl;
    cout << "config_gs_g[" << i << "]: " << this->config_gs_g[i] << endl;
    cout << "config_gs_b[" << i << "]: " << this->config_gs_b[i] << endl;
  }
}

void TLC5971::write()
{
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
}

void TLC5971::set_blank(bool val)
{
  if (val == true) {
    this->config_blank = BLANK_ON;
  }
  else {
    this->config_blank = BLANK_OFF;
  }
}

void TLC5971::set_current_ma(int current_ma)
{
  if (current_ma < 0 || current_ma > 60) {
    return;
  }

  uint8_t bc_val = current_ma * 127 / CURR_MAX_MA;
  this->config_bc_r = bc_val;
  this->config_bc_g = bc_val;
  this->config_bc_b = bc_val;
}

void TLC5971::set_8bit_color(int channel, uint8_t r, uint8_t g, uint8_t b)
{
    if (channel < 0 || channel > 3) {
      return;
    }

    uint16_t r_scaled = (int)r * GS_100 / 255;
    uint16_t g_scaled = (int)g * GS_100 / 255;
    uint16_t b_scaled = (int)b * GS_100 / 255;

    this->config_gs_r[channel] = r_scaled;
    this->config_gs_g[channel] = g_scaled;
    this->config_gs_b[channel] = b_scaled;
}
