// TLC5971.h
#include <stdint.h>
#include <time.h>

#define T_SCALE 10000
#define CURR_MAX_MA 60

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

class TLC5971
{
  public:
    TLC5971(int num, int pinSCKI, int pinSDTI);
    void printConfig();
    void write();
    void set_blank(bool val);
    void set_current_ma(int current_ma);
    void set_8bit_color(int channel, uint8_t r, uint8_t g, uint8_t b);

  private:
    struct timespec tsetup = {.tv_sec=0, .tv_nsec=5L*T_SCALE};
    struct timespec thold = {.tv_sec=0, .tv_nsec=3L*T_SCALE};
    struct timespec twidth = {.tv_sec=0, .tv_nsec=10L*T_SCALE};

    int num;
    int pinSCKI;
    int pinSDTI;

    bool config_outtmg = OUTTMG_FALL;
    bool config_extgck = EXTGCK_INT;
    bool config_tmgrst = TMGRST_DIS;
    bool config_dsprpt = DSPRPT_DIS;
    bool config_blank = BLANK_OFF;

    uint8_t config_bc_r = 0;
    uint8_t config_bc_g = 0;
    uint8_t config_bc_b = 0;

    uint16_t config_gs_r[4] = {0};
    uint16_t config_gs_g[4] = {0};
    uint16_t config_gs_b[4] = {0};

    void sleep_setup();
    void sleep_width();
    void sleep_hold();
    int send_bit(int val);
    void send_bits(int len, uint16_t val);
    void send_6bits(uint8_t val);
    void send_7bits(uint8_t val);
    void send_16bits(uint16_t val);
};
