#pragma once

#include <Arduino.h>
#include <lvgl.h>
#include <SPI.h>
#include <OLEDDisplay.h>

<<<<<<< HEAD
// #define TFT_CS 34
// #define TFT_RST 45 // Or set to -1 and connect to Arduino RESET pin
// #define TFT_DC 42
// #define BACK_LED 31

#define TFT_CS 45
#define TFT_RST 34 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC 35
#define BACK_LED 31
=======



#define TFT_CS         45
#define TFT_RST        34 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC         35
#define BACK_LED       31
>>>>>>> 8458afa345dbcf67a06761ddd18c171214b21447

#define ST77XX_CASET 0x2A
#define ST77XX_RASET 0x2B
#define ST7735_GMCTRP1 0xE0
#define ST7735_GMCTRN1 0xE1
#define ST77XX_NORON 0x13
#define ST_CMD_DELAY 0x80
#define ST77XX_DISPON 0x29
#define ST77XX_MADCTL 0x36

#define ST77XX_SWRESET 0x01
#define ST77XX_SLPOUT 0x11
#define ST7735_FRMCTR1 0xB1
#define ST7735_FRMCTR2 0xB2
#define ST7735_FRMCTR3 0xB3
#define ST7735_INVCTR 0xB4
#define ST7735_PWCTR1 0xC0
#define ST7735_PWCTR2 0xC1
#define ST7735_PWCTR3 0xC2
#define ST7735_PWCTR4 0xC3
#define ST7735_PWCTR5 0xC4
#define ST7735_VMCTR1 0xC5
#define ST77XX_INVOFF 0x20
#define ST77XX_COLMOD 0x3A

<<<<<<< HEAD
class ST7735 : public OLEDDisplay
{
private:
  SPISettings setting;
  SPIClass *spi;
  uint8_t _csPin;
  uint8_t _dcPin;
  uint8_t _rstPin;
  uint8_t _back_ledPin;

public:
  ST7735(SPIClass *SPI, uint8_t csPin, uint8_t dcPin, uint8_t rstPin, uint8_t back_ledpin)
      : spi(SPI), _csPin(csPin), _dcPin(dcPin), _rstPin(rstPin), _back_ledPin(back_ledpin) {};

  void ST7735init();

  void WriteComm(uint8_t command);

  void WriteData(uint8_t data);

  void Write16Data(uint16_t data);

  void sendCommand(uint8_t cmd, uint8_t *data, uint8_t datacount);

  void BlockWrite(unsigned int Xstart, unsigned int Xend, unsigned int Ystart, unsigned int Yend);

  void lcd_colorbox(unsigned short xstart, unsigned short ystart, unsigned short xlong, unsigned short ylong, unsigned short *color);

  void displayInit(uint8_t *addr);

  void set_screen(char state);

  virtual void display() override { return; };

protected:
  virtual int getBufferOffset(void) override { return 0; }
=======
class ST7735 : public OLEDDisplay {
  private:
    SPISettings setting;
    SPIClass *spi; 
    uint8_t _csPin;
    uint8_t _dcPin;
    uint8_t _rstPin;
    uint8_t _back_ledPin;

    public:
    ST7735( SPIClass *SPI,uint8_t csPin, uint8_t dcPin, uint8_t rstPin,  uint8_t back_ledpin)
    : spi(SPI), _csPin(csPin), _dcPin(dcPin), _rstPin(rstPin),_back_ledPin(back_ledpin){};

    void ST7735init();

    void WriteComm(uint8_t command);

    void WriteData(uint8_t data);

    void Write16Data(uint16_t data);

    void sendCommand(uint8_t cmd ,uint8_t *data,uint8_t datacount) ;

    void BlockWrite(unsigned int Xstart,unsigned int Xend,unsigned int Ystart,unsigned int Yend);

    void lcd_colorbox(unsigned short xstart,unsigned short ystart,unsigned short xlong,unsigned short ylong,unsigned short* color);

    void displayInit(uint8_t *addr);

    void set_screen(char state);

    virtual void display() override { return ; };

    protected:

    virtual int getBufferOffset(void) override { return 0; }

>>>>>>> 8458afa345dbcf67a06761ddd18c171214b21447
};

extern ST7735 *scr;
extern char buttonstate;

<<<<<<< HEAD
void my_disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p);
void switch_event_handler(lv_event_t *e);
void switch_and_delete_screen(lv_obj_t *new_screen);
void gps_refresh();
void back_btn_handler(lv_event_t *e);
=======

void my_disp_flush( lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p );
void switch_event_handler(lv_event_t * e);
void switch_and_delete_screen(lv_obj_t * new_screen);
void gps_refresh();
void back_btn_handler(lv_event_t * e);
>>>>>>> 8458afa345dbcf67a06761ddd18c171214b21447
void lora_refresh();
void msg_refresh();
void node_refresh();

<<<<<<< HEAD
void list_menu();
uint32_t keypad_get_key();
void keypad_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data);
void checkbox_event_handler(lv_event_t *e);
void scr_refresh();
void anim_x_cb(void *var, int32_t v);
void anim_size_cb(void *var, int32_t v);
void animation_end_cb(struct _lv_anim_t *);

void gps_refresh_callback(lv_event_t *e);
void menu_refresh_callback(lv_event_t *e);
void lora_refresh_callback(lv_event_t *e);
void msg_refresh_callback(lv_event_t *e);
void node_refresh_callback(lv_event_t *e);
void node_user_refresh_callback(lv_event_t *e);

void screen1_handler(lv_event_t *e);
void screen2_handler(lv_event_t *e);
void screen3_handler(lv_event_t *e);
void screen4_handler(lv_event_t *e);
void screen5_handler(lv_event_t *e);
void screen6_handler(lv_event_t *e);

void Use_gps(lv_event_t *e);
void gps_handler(lv_event_t *e);
void battery_handler(lv_event_t *e);

void lora_handler(lv_event_t *e);
void msg_handler(lv_event_t *e);

void node_user_handle(lv_event_t *e);
void container_refresh(lv_obj_t *screen, lv_event_cb_t cb, int has_backbtn);
void icon_refresh();
void node_user_refresh(lv_event_t *e);
=======

void list_menu();
uint32_t keypad_get_key();
void keypad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
void checkbox_event_handler(lv_event_t * e);
void scr_refresh();
void anim_x_cb(void * var, int32_t v);
void anim_size_cb(void * var, int32_t v);
void animation_end_cb(struct _lv_anim_t *);


void gps_refresh_callback(lv_event_t * e);
void menu_refresh_callback(lv_event_t * e);
void lora_refresh_callback(lv_event_t * e);
void msg_refresh_callback(lv_event_t * e);
void node_refresh_callback(lv_event_t * e);
void node_user_refresh_callback(lv_event_t * e);

void screen1_handler(lv_event_t * e);
void screen2_handler(lv_event_t * e);
void screen3_handler(lv_event_t * e);
void screen4_handler(lv_event_t * e);
void screen5_handler(lv_event_t * e);
void screen6_handler(lv_event_t * e);

void Use_gps(lv_event_t * e);
void gps_handler(lv_event_t * e);
void battery_handler(lv_event_t * e);

void lora_handler(lv_event_t * e);
void msg_handler(lv_event_t * e);

void node_user_handle(lv_event_t * e);
void container_refresh(lv_obj_t *screen,lv_event_cb_t cb,int has_backbtn);
void icon_refresh();
void node_user_refresh(lv_event_t * e);
>>>>>>> 8458afa345dbcf67a06761ddd18c171214b21447
