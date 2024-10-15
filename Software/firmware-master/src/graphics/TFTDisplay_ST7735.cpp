#include <Arduino.h>
#include <lvgl.h>
#include <SPI.h>
#include "TFTDisplay_ST7735.h"

#include "GPS.h"
#include "main.h"
#include "NodeDB.h"
#include "modules/AdminModule.h"

size_t cur_nodeIndex = 0;
<<<<<<< HEAD

=======
>>>>>>> 8458afa345dbcf67a06761ddd18c171214b21447
uint8_t
    Rcmd1[] = {                       // 7735R init, part 1 (red or green tab)
        15,                           // 15 commands in list:
        ST77XX_SWRESET, ST_CMD_DELAY, //  1: Software reset, 0 args, w/delay
        150,                          //     150 ms delay
        ST77XX_SLPOUT, ST_CMD_DELAY,  //  2: Out of sleep mode, 0 args, w/delay
        255,                          //     500 ms delay
        ST7735_FRMCTR1, 3,            //  3: Framerate ctrl - normal mode, 3 arg:
        0x01, 0x2C, 0x2D,             //     Rate = fosc/(1x2+40) * (LINE+2C+2D)
        ST7735_FRMCTR2, 3,            //  4: Framerate ctrl - idle mode, 3 args:
        0x01, 0x2C, 0x2D,             //     Rate = fosc/(1x2+40) * (LINE+2C+2D)
        ST7735_FRMCTR3, 6,            //  5: Framerate - partial mode, 6 args:
        0x01, 0x2C, 0x2D,             //     Dot inversion mode
        0x01, 0x2C, 0x2D,             //     Line inversion mode
        ST7735_INVCTR, 1,             //  6: Display inversion ctrl, 1 arg:
        0x07,                         //     No inversion
        ST7735_PWCTR1, 3,             //  7: Power control, 3 args, no delay:
        0xA2,
        0x02,             //     -4.6V
        0x84,             //     AUTO mode
        ST7735_PWCTR2, 1, //  8: Power control, 1 arg, no delay:
        0xC5,             //     VGH25=2.4C VGSEL=-10 VGH=3 * AVDD
        ST7735_PWCTR3, 2, //  9: Power control, 2 args, no delay:
        0x0A,             //     Opamp current small
        0x00,             //     Boost frequency
        ST7735_PWCTR4, 2, // 10: Power control, 2 args, no delay:
        0x8A,             //     BCLK/2,
        0x2A,             //     opamp current small & medium low
        ST7735_PWCTR5, 2, // 11: Power control, 2 args, no delay:
        0x8A, 0xEE,
        ST7735_VMCTR1, 1, // 12: Power control, 1 arg, no delay:
        0x0E,
        ST77XX_INVOFF, 0, // 13: Don't invert display, no args
        ST77XX_MADCTL, 1, // 14: Mem access ctl (directions), 1 arg:
        0xA8,             //     row/col addr, bottom-top refresh
        ST77XX_COLMOD, 1, // 15: set color mode, 1 arg, no delay:
        0x05},            //     16-bit color

    Rcmd2green160x80[] = {                                                          // 7735R init, part 2 (mini 160x80)
        2,                                                                          //  2 commands in list:
        ST77XX_CASET, 4,                                                            //  1: Column addr set, 4 args, no delay:
        0x00, 0x00,                                                                 //     XSTART = 0
        0x00, 0x4F,                                                                 //     XEND = 79
        ST77XX_RASET, 4,                                                            //  2: Row addr set, 4 args, no delay:
        0x00, 0x00,                                                                 //     XSTART = 0
        0x00, 0x9F},                                                                //     XEND = 159
    Rcmd3[] = {                                                                     // 7735R init, part 3 (red or green tab)
        4,                                                                          //  4 commands in list:
        ST7735_GMCTRP1, 16,                                                         //  1: Gamma Adjustments (pos. polarity), 16 args + delay:
        0x02, 0x1c, 0x07, 0x12,                                                     //     (Not entirely necessary, but provides
        0x37, 0x32, 0x29, 0x2d,                                                     //      accurate colors)
        0x29, 0x25, 0x2B, 0x39, 0x00, 0x01, 0x03, 0x10, ST7735_GMCTRN1, 16,         //  2: Gamma Adjustments (neg. polarity), 16 args + delay:
        0x03, 0x1d, 0x07, 0x06,                                                     //     (Not entirely necessary, but provides
        0x2E, 0x2C, 0x29, 0x2D,                                                     //      accurate colors)
        0x2E, 0x2E, 0x37, 0x3F, 0x00, 0x00, 0x02, 0x10, ST77XX_NORON, ST_CMD_DELAY, //  3: Normal display on, no args, w/delay
        10,                                                                         //     10 ms delay
        ST77XX_DISPON, ST_CMD_DELAY,                                                //  4: Main screen turn on, no args w/delay
        100};                                                                       //     100 ms delay

static const uint16_t screenWidth = 160;
static const uint16_t screenHeight = 80;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenWidth * screenHeight];

static char tempBuf[237];

static uint16_t bat_icon = 0;

ST7735 *scr = new ST7735(&SPI1, TFT_CS, TFT_DC, TFT_RST, BACK_LED);

char buttonstate = 0;
lv_obj_t *screen0;
lv_obj_t *menu_screen;
lv_obj_t *gps_screen;
lv_obj_t *lora_screen;
lv_obj_t *msg_screen;
lv_obj_t *node_screen;
lv_obj_t *node_user_screen;
lv_obj_t *msg = NULL;
lv_obj_t *time = NULL;
lv_obj_t *Lon_lable = NULL;
lv_obj_t *Lat_lable = NULL;
lv_obj_t *Alt_lable = NULL;
lv_obj_t *gps_icon = NULL;
lv_obj_t *battery = NULL;
lv_obj_t *Region = NULL;
lv_obj_t *short_name = NULL;
lv_obj_t *Modem = NULL;
lv_obj_t *txpower = NULL;
lv_obj_t *Channel_num = NULL;
lv_obj_t *Hop_limit = NULL;
lv_obj_t *BatteryChargePercent = NULL;
lv_obj_t *lora = NULL;
lv_obj_t *back_btn = NULL;
lv_obj_t *btn_lable = NULL;
lv_obj_t *container = NULL;
lv_obj_t *cb = NULL;

lv_obj_t *btn = NULL;

lv_obj_t *name = NULL;
lv_obj_t *volatge = NULL;
lv_obj_t *batlevel = NULL;
lv_obj_t *ChUtil = NULL;
lv_obj_t *AirUtil = NULL;
lv_obj_t *snr = NULL;
lv_obj_t *Lon = NULL;
lv_obj_t *Lat = NULL;

typedef struct
{
    lv_obj_t *screen;
    lv_event_cb_t callback;
    lv_obj_t *previous_menu;
    lv_event_cb_t previous_menu_callback;
} Sub_menu;

Sub_menu gps_menu{
    gps_screen,
    gps_refresh_callback,
    menu_screen,
    menu_refresh_callback};

Sub_menu lora_menu{
    lora_screen,
    lora_refresh_callback,
    menu_screen,
    menu_refresh_callback};

Sub_menu msg_menu{
    msg_screen,
    msg_refresh_callback,
    menu_screen,
    menu_refresh_callback};

Sub_menu node_menu{
    node_screen,
    node_refresh_callback,
    menu_screen,
    menu_refresh_callback};

Sub_menu node_user_menu{
    node_user_screen,
    node_user_refresh_callback,
    node_screen,
    node_refresh_callback};

Sub_menu *current_sub_menu = NULL;
// Main_menu *current_main_menu = NULL;

void menu_refresh_callback(lv_event_t *e)
{
    current_sub_menu = NULL;
    // current_main_menu = &main_menu;
    list_menu();
    switch_and_delete_screen(menu_screen);
}

void gps_refresh_callback(lv_event_t *e)
{
    current_sub_menu = &gps_menu;
    // current_main_menu = NULL;
    gps_refresh();
    switch_and_delete_screen(gps_screen);
}

void lora_refresh_callback(lv_event_t *e)
{
    current_sub_menu = &lora_menu;
    lora_refresh();
    switch_and_delete_screen(lora_screen);
}

void msg_refresh_callback(lv_event_t *e)
{
    current_sub_menu = &msg_menu;
    msg_refresh();
    switch_and_delete_screen(msg_screen);
}

void node_refresh_callback(lv_event_t *e)
{
    current_sub_menu = &node_menu;
    node_refresh();
    switch_and_delete_screen(node_screen);
}

void node_user_refresh_callback(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *btn = lv_event_get_target(e);
    if (code == LV_EVENT_VALUE_CHANGED)
    {
        icon_refresh();
    }
    if (code == LV_EVENT_CLICKED)
    {
        current_sub_menu = &node_user_menu;
        node_user_refresh(e);
        switch_and_delete_screen(node_user_screen);
    }
}

void gps_refresh()
{
    gps_screen = lv_obj_create(NULL);
    container_refresh(gps_screen, screen2_handler, 0);

    cb = lv_checkbox_create(gps_screen);
    lv_checkbox_set_text(cb, "Use gps");
    lv_obj_add_event_cb(cb, Use_gps, LV_EVENT_ALL, NULL);
    lv_obj_update_layout(cb);

<<<<<<< HEAD
    LOG_DEBUG("gps->readenabled() = %d", gps->readenabled());

    if (gps->readenabled() == true)
    {
        lv_obj_add_state(cb, LV_STATE_CHECKED);
    }
    else if (gps->readenabled() == false)
=======
    LOG_DEBUG("gps->powerState = %d", gps->powerState);

    if (gps->powerState == GPS_ACTIVE)
    {
        lv_obj_add_state(cb, LV_STATE_CHECKED);
    }
    else if (gps->powerState == GPS_OFF)
>>>>>>> 8458afa345dbcf67a06761ddd18c171214b21447
    {
        lv_obj_clear_state(cb, LV_STATE_CHECKED);
    }

    Lon_lable = lv_label_create(gps_screen);
    lv_label_set_text_fmt(Lon_lable, "Lon:%f", gpsStatus->getLongitude());

    Lat_lable = lv_label_create(gps_screen);
    lv_label_set_text_fmt(Lat_lable, "Lat:%f", gpsStatus->getLatitude());

    Alt_lable = lv_label_create(gps_screen);
    lv_label_set_text_fmt(Alt_lable, "Alt:%f", gpsStatus->getAltitude());
    lv_obj_add_event_cb(Alt_lable, gps_handler, LV_EVENT_ALL, NULL);
}

void lora_refresh()
{
    lora_screen = lv_obj_create(NULL);
    container_refresh(lora_screen, screen3_handler, 0);
    const char *my_region = "Unknown Region";
    switch (config.lora.region)
    {
    case meshtastic_Config_LoRaConfig_RegionCode_UNSET:
        my_region = "UNSET";
        break;
    case meshtastic_Config_LoRaConfig_RegionCode_US:
        my_region = "US";
        break;
    case meshtastic_Config_LoRaConfig_RegionCode_EU_433:
        my_region = "EU_433";
        break;
    case meshtastic_Config_LoRaConfig_RegionCode_EU_868:
        my_region = "_EU_868";
        break;
    case meshtastic_Config_LoRaConfig_RegionCode_CN:
        my_region = "CN";
        break;
    case meshtastic_Config_LoRaConfig_RegionCode_JP:
        my_region = "JP";
        break;
    case meshtastic_Config_LoRaConfig_RegionCode_ANZ:
        my_region = "ANZ";
        break;
    case meshtastic_Config_LoRaConfig_RegionCode_KR:
        my_region = "KR";
    case meshtastic_Config_LoRaConfig_RegionCode_TW:
        my_region = "TW";
        break;
    case meshtastic_Config_LoRaConfig_RegionCode_RU:
        my_region = "RU";
        break;
    case meshtastic_Config_LoRaConfig_RegionCode_IN:
        my_region = "IN";
        break;
    case meshtastic_Config_LoRaConfig_RegionCode_NZ_865:
        my_region = "NZ_865";
        break;
    case meshtastic_Config_LoRaConfig_RegionCode_TH:
        my_region = "TH";
        break;
    case meshtastic_Config_LoRaConfig_RegionCode_LORA_24:
        my_region = "LORA_24";
        break;
    case meshtastic_Config_LoRaConfig_RegionCode_UA_433:
        my_region = "UA_433";
        break;
    case meshtastic_Config_LoRaConfig_RegionCode_UA_868:
        my_region = "UA_868";
        break;
    case meshtastic_Config_LoRaConfig_RegionCode_MY_433:
        my_region = "MY_433";
        break;
    case meshtastic_Config_LoRaConfig_RegionCode_MY_919:
        my_region = "MY_919";
        break;
    case meshtastic_Config_LoRaConfig_RegionCode_SG_923:
        my_region = "SG_923";
        break;
    }
    Region = lv_label_create(lora_screen);
    lv_label_set_text_fmt(Region, "Region:%s", my_region);
    char shortname[5] = {0};
    snprintf(shortname, sizeof(shortname), "%s", owner.short_name);
    short_name = lv_label_create(lora_screen);
    lv_label_set_text_fmt(short_name, "name:%s", shortname);
    const char *modem_preset = "Unknown modem";
    switch (config.lora.modem_preset)
    {
    case meshtastic_Config_LoRaConfig_ModemPreset_LONG_FAST:
        modem_preset = "LONG_FAST";
        break;
    case meshtastic_Config_LoRaConfig_ModemPreset_LONG_SLOW:
        modem_preset = "LONG_SLOW";
        break;
    case meshtastic_Config_LoRaConfig_ModemPreset_VERY_LONG_SLOW:
        modem_preset = "VERY_LONG_SLOW";
        break;
    case meshtastic_Config_LoRaConfig_ModemPreset_MEDIUM_SLOW:
        modem_preset = "MEDIUM_SLOW";
        break;
    case meshtastic_Config_LoRaConfig_ModemPreset_MEDIUM_FAST:
        modem_preset = "MEDIUM_FAST";
        break;
    case meshtastic_Config_LoRaConfig_ModemPreset_SHORT_SLOW:
        modem_preset = "SHORT_SLOW";
        break;
    case meshtastic_Config_LoRaConfig_ModemPreset_SHORT_FAST:
        modem_preset = "SHORT_FAST";
        break;
    case meshtastic_Config_LoRaConfig_ModemPreset_LONG_MODERATE:
        modem_preset = "LONG_MODERATE";
        break;
    }
    Modem = lv_label_create(lora_screen);
    lv_label_set_text_fmt(Modem, "Modem present:\n%s", modem_preset);

    txpower = lv_label_create(lora_screen);
    lv_label_set_text_fmt(txpower, "Tx power:%ddB", config.lora.tx_power);

    Channel_num = lv_label_create(lora_screen);
    lv_label_set_text_fmt(Channel_num, "Channel_num:%d", config.lora.channel_num);

    Hop_limit = lv_label_create(lora_screen);
    lv_label_set_text_fmt(Hop_limit, "Hop_limit:%d", config.lora.hop_limit);
    lv_obj_add_event_cb(Hop_limit, lora_handler, LV_EVENT_ALL, NULL);
}

void msg_refresh()
{
    msg_screen = lv_obj_create(NULL);
    container_refresh(msg_screen, screen4_handler, 0);

    const meshtastic_MeshPacket &mp = devicestate.rx_text_message;
    meshtastic_NodeInfoLite *node = nodeDB->getMeshNode(getFrom(&mp));

    uint32_t seconds = sinceReceived(&mp);
    uint32_t minutes = seconds / 60;
    uint32_t hours = minutes / 60;
    uint32_t days = hours / 24;
    uint8_t timestampHours, timestampMinutes;
    int32_t daysAgo;
    bool useTimestamp = graphics::deltaToTimestamp(seconds, &timestampHours, &timestampMinutes, &daysAgo);
    time = lv_label_create(msg_screen);
    lv_label_set_text_fmt(time, "%s ago from %s", screen->drawTimeDelta(days, hours, minutes, seconds).c_str(), (node && node->has_user) ? node->user.short_name : "???");

    snprintf(tempBuf, sizeof(tempBuf), "%s", mp.decoded.payload.bytes);
    msg = lv_label_create(msg_screen);
    lv_obj_add_event_cb(msg, msg_handler, LV_EVENT_ALL, NULL);
    lv_obj_set_width(msg, 159);
    lv_label_set_long_mode(msg, LV_LABEL_LONG_WRAP); // 设置标签为自动换行模式
    lv_label_set_text_fmt(msg, "msg:%s", tempBuf);
}

void node_refresh()
{
    node_screen = lv_obj_create(NULL);
    container_refresh(node_screen, screen5_handler, 0);
    if (lora != NULL)
    {
        lv_obj_add_event_cb(lora, battery_handler, LV_EVENT_ALL, NULL);
    }

    /*Create a list*/
    cb = lv_list_create(node_screen);
    lv_obj_set_size(cb, 160, 60);
    lv_obj_center(cb);

    lv_list_add_text(cb, "node_list");
    lv_obj_add_event_cb(cb, msg_handler, LV_EVENT_ALL, NULL);
    size_t *array = new size_t[nodeDB->getNumMeshNodes()]; // 动态分配数组

    meshtastic_NodeInfoLite *n = NULL;
    size_t nodeIndex;
    for (nodeIndex = 0; nodeIndex < nodeDB->getNumMeshNodes(); nodeIndex++)
    {
        nodeIndex = nodeIndex % nodeDB->getNumMeshNodes(); // 保证0~

        n = nodeDB->getMeshNodeByIndex(nodeIndex);
        if (n->num == nodeDB->getNodeNum())
        {
            // Don't show our node, just skip to next
            LOG_DEBUG("PASS OWN NODE\n");
            continue;
        }

        meshtastic_NodeInfoLite *node = nodeDB->getMeshNodeByIndex(nodeIndex);
        const char *username = node->has_user ? node->user.short_name : "Unknown Name";
        LOG_DEBUG("username=%s\n", username);
        LOG_DEBUG("nodeIndex=%d\n", nodeIndex);
        btn = lv_list_add_btn(cb, LV_SYMBOL_DUMMY, username);
        array[nodeIndex] = nodeIndex;
        lv_obj_add_event_cb(btn, node_user_refresh_callback, LV_EVENT_CLICKED, &array[nodeIndex]);
    }
    lv_group_t *group = lv_group_get_default();
    lv_group_add_obj(group, btn); // 添加进group 如果用触摸屏就不用
}

void node_user_refresh(lv_event_t *e)
{
    node_user_screen = lv_obj_create(NULL);
    container_refresh(node_user_screen, screen6_handler, 0);
    if (lora != NULL)
    {
        lv_obj_add_event_cb(lora, node_user_handle, LV_EVENT_ALL, NULL);
    }
    cur_nodeIndex = *(size_t *)e->user_data;
    meshtastic_NodeInfoLite *node = nodeDB->getMeshNodeByIndex(cur_nodeIndex);
    const char *username = node->has_user ? node->user.short_name : "Unknown Name";

    name = lv_label_create(node_user_screen);
    lv_label_set_text_fmt(name, "name:%s", username);
    volatge = lv_label_create(node_user_screen);
    lv_label_set_text_fmt(volatge, "volatge:%f", node->device_metrics.voltage);
    batlevel = lv_label_create(node_user_screen);
    lv_label_set_text_fmt(batlevel, "batlevel:%d", node->device_metrics.battery_level);
    ChUtil = lv_label_create(node_user_screen);
    lv_label_set_text_fmt(ChUtil, "ChUtil:%f", node->device_metrics.channel_utilization);
    AirUtil = lv_label_create(node_user_screen);
    lv_label_set_text_fmt(AirUtil, "AirUtil:%f", node->device_metrics.air_util_tx);
    snr = lv_label_create(node_user_screen);
    lv_label_set_text_fmt(snr, "snr:%f", node->snr);
    Lon = lv_label_create(node_user_screen);
    lv_label_set_text_fmt(Lon, "Lon:%d", node->position.longitude_i);
    Lat = lv_label_create(node_user_screen);
    lv_label_set_text_fmt(Lat, "Lat:%d", node->position.latitude_i);
}

void list_menu()
{
    menu_screen = lv_obj_create(NULL);
    container_refresh(menu_screen, screen1_handler, 0);
    /*Create a list*/
    lv_obj_t *list1 = lv_list_create(menu_screen);
    lv_obj_set_size(list1, 160, 60);
    lv_obj_center(list1);
    if (lora != NULL)
    {
        lv_obj_add_event_cb(lora, battery_handler, LV_EVENT_ALL, NULL);
    }
    /*Add buttons to the list*/
    lv_obj_t *btn_gps;
    lv_obj_t *btn_lora;
    lv_obj_t *btn_msg;
    lv_obj_t *btn_node;
    // lv_list_add_text(list1, "");
    btn_gps = lv_list_add_btn(list1, LV_SYMBOL_GPS, "GPS");
    lv_obj_add_event_cb(btn_gps, gps_refresh_callback, LV_EVENT_CLICKED, NULL);
    btn_lora = lv_list_add_btn(list1, LV_SYMBOL_WIFI, "LORA");
    lv_obj_add_event_cb(btn_lora, lora_refresh_callback, LV_EVENT_CLICKED, NULL);
    btn_msg = lv_list_add_btn(list1, LV_SYMBOL_ENVELOPE, "MSG");
    lv_obj_add_event_cb(btn_msg, msg_refresh_callback, LV_EVENT_CLICKED, NULL);
    btn_node = lv_list_add_btn(list1, LV_SYMBOL_ENVELOPE, "NODE");
    lv_obj_add_event_cb(btn_node, node_refresh_callback, LV_EVENT_CLICKED, NULL);

    lv_group_t *group = lv_group_get_default();
    lv_group_focus_obj(btn_gps);
}

void ST7735::ST7735init()
{
    spi->begin();

    pinMode(_csPin, OUTPUT);
    pinMode(_dcPin, OUTPUT);
    pinMode(_rstPin, OUTPUT);
<<<<<<< HEAD
    pinMode(_back_ledPin, OUTPUT_H0H1);

    // uint32_t a = NRF_UICR->REGOUT0;
    // LOG_DEBUG("NRF_UICR->REGOUT0=%d", a);
    // NRF_UICR->REGOUT0 = 0X5;
    // a = NRF_UICR->REGOUT0;
    // LOG_DEBUG("NRF_UICR->REGOUT0=%d", a);
=======
    pinMode(_back_ledPin, OUTPUT_S0D1);
>>>>>>> 8458afa345dbcf67a06761ddd18c171214b21447

    digitalWrite(_rstPin, HIGH);
    delay(5);
    digitalWrite(_rstPin, LOW);
    delay(20);
    digitalWrite(_rstPin, HIGH);
    delay(150);

    set_screen(true);

    scr->displayInit(Rcmd1);
    scr->displayInit(Rcmd2green160x80);
    scr->displayInit(Rcmd3);

    lv_init();

    lv_disp_draw_buf_init(&draw_buf, buf, NULL, screenWidth * screenHeight);

    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    /*Change the following line to your display resolution*/
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    /*Initialize the (dummy) input device driver*/
    static lv_indev_t *indev_keypad;
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_KEYPAD;
    indev_drv.read_cb = keypad_read;
    indev_keypad = lv_indev_drv_register(&indev_drv);

    lv_group_t *group = lv_group_create();
    lv_group_set_default(group);
    lv_indev_set_group(indev_keypad, group);
    lv_group_set_editing(group, false);

    lv_color_t custom_color_primary = lv_color_hex(0x67EA94);   // 红色作为主颜色
    lv_color_t custom_color_secondary = lv_color_hex(0x000000); // 绿色作为次颜色
    lv_theme_t *th = lv_theme_default_init(NULL, custom_color_primary, custom_color_secondary, 1, &lv_font_montserrat_14);
    lv_disp_set_theme(NULL, th);

    screen0 = lv_obj_create(NULL);
    lv_scr_load(screen0);

    lv_obj_set_flex_flow(screen0, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_pad_row(screen0, 5, 0); // 将行间距设置为10像素
    lv_obj_set_flex_align(screen0, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x67EA94), LV_PART_MAIN);

    /*Create a white label, set its text and align it to the center*/
    lv_obj_t *meshtastic = lv_label_create(lv_scr_act());
    lv_label_set_text(meshtastic, "Meshtastic");
    lv_obj_set_style_text_color(lv_scr_act(), lv_color_hex(0x000000), LV_PART_MAIN);

    lv_obj_t *lable = lv_label_create(lv_scr_act());
    lv_label_set_text(lable, "The Smallest Device");
    lv_obj_set_style_text_color(lv_scr_act(), lv_color_hex(0x000000), LV_PART_MAIN);

    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, lable);
    lv_anim_set_values(&a, -50, +50);
    lv_anim_set_time(&a, 2000);
    lv_anim_set_path_cb(&a, lv_anim_path_linear);
    lv_anim_set_exec_cb(&a, anim_x_cb);
    lv_anim_set_ready_cb(&a, animation_end_cb);
    lv_anim_start(&a);
}

void ST7735::WriteComm(uint8_t command)
{
    spi->beginTransaction(setting);
    digitalWrite(_dcPin, LOW);
    digitalWrite(_csPin, LOW);
    spi->transfer(command);
    digitalWrite(_csPin, HIGH);
    spi->endTransaction();
}

void ST7735::WriteData(uint8_t data)
{
    spi->beginTransaction(setting);
    digitalWrite(_dcPin, HIGH);
    digitalWrite(_csPin, LOW);
    spi->transfer(data);
    digitalWrite(_csPin, HIGH);
    spi->endTransaction();
}

void ST7735::Write16Data(uint16_t data)
{
    spi->beginTransaction(setting);
    digitalWrite(_dcPin, HIGH);
    digitalWrite(_csPin, LOW);
    spi->transfer(data >> 8);
    spi->transfer(data & 0xFF);
    digitalWrite(_csPin, HIGH);
    spi->endTransaction();
}

void ST7735::sendCommand(uint8_t cmd, uint8_t *data, uint8_t datacount)
{
    WriteComm(cmd);
    uint8_t i;
    for (i = 0; i < datacount; i++)
    {
        WriteData(*data);
        data++;
    }
}

void ST7735::BlockWrite(unsigned int Xstart, unsigned int Xend, unsigned int Ystart, unsigned int Yend)
{
    WriteComm(0x2a);
    WriteData(Xstart >> 8);
    WriteData(Xstart & 0xff);
    WriteData(Xend >> 8);
    WriteData(Xend & 0xff);

    WriteComm(0x2b);
    WriteData(Ystart >> 8);
    WriteData(Ystart & 0xff);
    WriteData(Yend >> 8);
    WriteData(Yend & 0xff);

    WriteComm(0x2c);
}
void ST7735::lcd_colorbox(unsigned short xstart, unsigned short ystart, unsigned short xlong, unsigned short ylong, unsigned short *color)
{
    BlockWrite(xstart, xstart + xlong - 1, ystart, ystart + ylong - 1);
    // sendblockdata(white,xstart+xlong-1*(ystart+ylong-1)*2);
    spi->beginTransaction(setting);
    digitalWrite(_dcPin, HIGH);
    digitalWrite(_csPin, LOW);
    spi->transfer(color, xlong * ylong * 2);
    digitalWrite(_csPin, HIGH);
    spi->endTransaction();
}

void ST7735::displayInit(uint8_t *addr)
{

    uint8_t numCommands, cmd, numArgs;
    uint16_t ms;

    numCommands = pgm_read_byte(addr++); // Number of commands to follow
    while (numCommands--)
    {                                    // For each command...
        cmd = pgm_read_byte(addr++);     // Read command
        numArgs = pgm_read_byte(addr++); // Number of args to follow
        ms = numArgs & ST_CMD_DELAY;     // If hibit set, delay follows args
        numArgs &= ~ST_CMD_DELAY;        // Mask out delay bit
        sendCommand(cmd, addr, numArgs);
        addr += numArgs;

        if (ms)
        {
            ms = pgm_read_byte(addr++); // Read post-command delay time (ms)
            if (ms == 255)
                ms = 500; // If 255, delay for 500 ms
            delay(ms);
        }
    }
}

void ST7735::set_screen(char state)
{
<<<<<<< HEAD
    if (state)
    {
        analogWrite(_back_ledPin, 255);
    }
    else
    {
        analogWrite(_back_ledPin, 0);
    }
=======
    digitalWrite(_back_ledPin, state);
>>>>>>> 8458afa345dbcf67a06761ddd18c171214b21447
}

void my_disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
    // unsigned long timestamp = millis();
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);
    scr->lcd_colorbox(area->x1, 24 + area->y1, w, h, (uint16_t *)color_p);
    lv_disp_flush_ready(disp_drv);
}

void battery_refresh(lv_obj_t *container)
{

<<<<<<< HEAD
    if (gps->readenabled() == true)
=======
    if (gps->powerState == GPS_ACTIVE)
>>>>>>> 8458afa345dbcf67a06761ddd18c171214b21447
    {
        gps_icon = lv_label_create(container);
        lv_label_set_text(gps_icon, LV_SYMBOL_GPS); // GPS
    }
<<<<<<< HEAD
    else if (gps->readenabled() == false)
=======
    else if (gps->powerState == GPS_OFF)
>>>>>>> 8458afa345dbcf67a06761ddd18c171214b21447
    {
        gps_icon = lv_label_create(container);
        lv_label_set_text(gps_icon, LV_SYMBOL_DUMMY); // GPS
    }

    lora = lv_label_create(container);
    lv_label_set_text(lora, LV_SYMBOL_WIFI); // lora
    battery = lv_label_create(container);
    BatteryChargePercent = lv_label_create(container);
    if (powerStatus->getIsCharging())
    {
        lv_label_set_text(battery, LV_SYMBOL_BATTERY_FULL); // 设置为中等电量
<<<<<<< HEAD
        lv_label_set_text_fmt(BatteryChargePercent, "%d%%", powerStatus->getBatteryChargePercent());
=======
>>>>>>> 8458afa345dbcf67a06761ddd18c171214b21447
    }
    else
    {

        if (powerStatus->getBatteryChargePercent() == 100)
        {
            lv_label_set_text(battery, LV_SYMBOL_BATTERY_FULL); // 设置为中等电量
        }
        else if (powerStatus->getBatteryChargePercent() < 100 && powerStatus->getBatteryChargePercent() >= 66)
        {
            lv_label_set_text(battery, LV_SYMBOL_BATTERY_3); // 设置为中等电量
        }
        else if (powerStatus->getBatteryChargePercent() < 66 && powerStatus->getBatteryChargePercent() >= 33)
        {
            lv_label_set_text(battery, LV_SYMBOL_BATTERY_2); // 设置为中等电量
        }
        else if (powerStatus->getBatteryChargePercent() < 33 && powerStatus->getBatteryChargePercent() > 0)
        {
            lv_label_set_text(battery, LV_SYMBOL_BATTERY_1); // 设置为中等电量
        }
        else if (powerStatus->getBatteryChargePercent() == 0)
        {
            lv_label_set_text(battery, LV_SYMBOL_BATTERY_EMPTY); // 设置为中等电量
        }
        lv_label_set_text_fmt(BatteryChargePercent, "%d%%", powerStatus->getBatteryChargePercent());
    }
}

void container_refresh(lv_obj_t *screen, lv_event_cb_t cb, int has_backbtn)
{

    lv_obj_add_event_cb(screen, cb, LV_EVENT_REFRESH, NULL);
    lv_obj_set_flex_flow(screen, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_pad_row(screen, 6, 0); // 将行间距设置为10像素
    lv_obj_set_flex_align(screen, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);

    container = lv_obj_create(screen);
    lv_obj_set_size(container, 160, 17);
    lv_obj_set_pos(container, 0, 0);
    lv_obj_set_style_border_width(container, 0, 0);
    lv_obj_set_style_pad_all(container, 3, 0);

    lv_obj_set_flex_flow(container, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_style_pad_column(container, 3, 0); // 将行间距设置为10像素
    lv_obj_set_flex_align(container, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_CENTER);

    battery_refresh(container);

    if (has_backbtn)
    {
        back_btn = lv_btn_create(screen);
        lv_obj_set_size(back_btn, 28, 14);
        lv_obj_set_style_bg_color(back_btn, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_add_event_cb(back_btn, back_btn_handler, LV_EVENT_CLICKED, NULL);
        btn_lable = lv_label_create(back_btn);
        lv_label_set_text(btn_lable, "<");
        lv_obj_set_style_text_color(btn_lable, lv_color_hex(0x000000), LV_PART_MAIN);
        lv_obj_align(btn_lable, LV_ALIGN_CENTER, 0, 0);
    }
}

void screen6_handler(lv_event_t *e)
{

    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_REFRESH)
    {
        lv_event_send(lora, LV_EVENT_VALUE_CHANGED, NULL);
    }
}

void screen5_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_REFRESH)
    {
        lv_event_send(lora, LV_EVENT_VALUE_CHANGED, NULL);
    }
}

void screen4_handler(lv_event_t *e)
{

    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_REFRESH)
    {
        lv_event_send(msg, LV_EVENT_VALUE_CHANGED, NULL);
    }
}

void screen3_handler(lv_event_t *e)
{

    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_REFRESH)
    {
        lv_event_send(Hop_limit, LV_EVENT_VALUE_CHANGED, NULL);
    }
}

void screen2_handler(lv_event_t *e)
{
<<<<<<< HEAD
=======

>>>>>>> 8458afa345dbcf67a06761ddd18c171214b21447
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_REFRESH)
    {
        lv_event_send(Alt_lable, LV_EVENT_VALUE_CHANGED, NULL);
    }
}

void screen1_handler(lv_event_t *e)
{

    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_REFRESH)
    {
        lv_event_send(lora, LV_EVENT_VALUE_CHANGED, NULL);
    }
}

void switch_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    if (code == LV_EVENT_VALUE_CHANGED)
    {
        LV_UNUSED(obj);
        LV_LOG_USER("State: %s\n", lv_obj_has_state(obj, LV_STATE_CHECKED) ? "On" : "Off");
    }
}

void switch_and_delete_screen(lv_obj_t *new_screen)
{
    lv_obj_t *current_screen = lv_scr_act(); // 获取当前屏幕
    lv_scr_load(new_screen);                 // 切换到新的屏幕
    lv_obj_del(current_screen);              // 删除当前屏幕
}

void Use_gps(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    if (code == LV_EVENT_VALUE_CHANGED)
    {
<<<<<<< HEAD
        gps->toggleGpsMode();
=======
        if (lv_obj_get_state(obj) & LV_STATE_CHECKED)
        {
            if (config.position.gps_mode == meshtastic_Config_PositionConfig_GpsMode_DISABLED)
            {
                config.position.gps_mode = meshtastic_Config_PositionConfig_GpsMode_ENABLED;
                LOG_INFO("User toggled GpsMode. Now ENABLED\n");
                gps->enable();
            }
        }
        else
        {
            if (config.position.gps_mode == meshtastic_Config_PositionConfig_GpsMode_ENABLED)
            {
                config.position.gps_mode = meshtastic_Config_PositionConfig_GpsMode_DISABLED;
                LOG_INFO("User toggled GpsMode. Now DISABLED.\n");
                gps->disable();
            }
        }
>>>>>>> 8458afa345dbcf67a06761ddd18c171214b21447
    }
}

void icon_refresh()
{
<<<<<<< HEAD
    if (gps->readenabled() == true)
    {
        lv_label_set_text(gps_icon, LV_SYMBOL_GPS);
    }
    else if (gps->readenabled() == false)
=======
    if (gps->powerState == GPS_ACTIVE)
    {
        lv_label_set_text(gps_icon, LV_SYMBOL_GPS);
    }
    else if (gps->powerState == GPS_OFF)
>>>>>>> 8458afa345dbcf67a06761ddd18c171214b21447
    {
        lv_label_set_text(gps_icon, LV_SYMBOL_DUMMY);
    }
    if (powerStatus->getIsCharging())
    {
        bat_icon = ((bat_icon + 1) % 500);
        if (bat_icon >= 0 && bat_icon < 10)
        {
            lv_label_set_text(battery, LV_SYMBOL_BATTERY_EMPTY);
        }
        else if (bat_icon >= 100 && bat_icon < 200)
        {
            lv_label_set_text(battery, LV_SYMBOL_BATTERY_1);
        }
        else if (bat_icon >= 200 && bat_icon < 300)
        {
            lv_label_set_text(battery, LV_SYMBOL_BATTERY_2);
        }
        else if (bat_icon >= 300 && bat_icon < 400)
        {
            lv_label_set_text(battery, LV_SYMBOL_BATTERY_3);
        }
        else if (bat_icon >= 400 && bat_icon <= 500)
        {
            lv_label_set_text(battery, LV_SYMBOL_BATTERY_FULL); // 设置为中等电量
        }
    }
    if (lora != NULL)
    {
        lv_label_set_text(lora, LV_SYMBOL_WIFI); // lora
    }
<<<<<<< HEAD
    if (BatteryChargePercent != NULL)
=======
    if (lora != NULL)
>>>>>>> 8458afa345dbcf67a06761ddd18c171214b21447
    {
        lv_label_set_text_fmt(BatteryChargePercent, "%d%%", powerStatus->getBatteryChargePercent());
    }
}

void gps_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_VALUE_CHANGED)
    {
        icon_refresh();
        lv_label_set_text_fmt(Lon_lable, "Lon:%f", gpsStatus->getLongitude());
        lv_label_set_text_fmt(Lat_lable, "Lat:%f", gpsStatus->getLatitude());
        lv_label_set_text_fmt(Alt_lable, "Alt:%f", gpsStatus->getAltitude());
    }
}
void lora_handler(lv_event_t *e)
{

    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_VALUE_CHANGED)
    {
        icon_refresh();
    }
}

void msg_handler(lv_event_t *e)
{

    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_VALUE_CHANGED)
    {
        icon_refresh();

        const meshtastic_MeshPacket &mp = devicestate.rx_text_message;
        meshtastic_NodeInfoLite *node = nodeDB->getMeshNode(getFrom(&mp));

        uint32_t seconds = sinceReceived(&mp);
        uint32_t minutes = seconds / 60;
        uint32_t hours = minutes / 60;
        uint32_t days = hours / 24;
        uint8_t timestampHours, timestampMinutes;
        int32_t daysAgo;
        bool useTimestamp = graphics::deltaToTimestamp(seconds, &timestampHours, &timestampMinutes, &daysAgo);
        lv_label_set_text_fmt(time, "%s ago from %s", screen->drawTimeDelta(days, hours, minutes, seconds).c_str(), (node && node->has_user) ? node->user.short_name : "???");

        snprintf(tempBuf, sizeof(tempBuf), "%s", mp.decoded.payload.bytes);
        lv_label_set_text_fmt(msg, "mesg:%s", tempBuf);
    }
}

void node_user_handle(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_VALUE_CHANGED)
    {
        icon_refresh();
        meshtastic_NodeInfoLite *node = nodeDB->getMeshNodeByIndex(cur_nodeIndex);
        const char *username = node->has_user ? node->user.long_name : "Unknown Name";
        lv_label_set_text_fmt(name, "name:%s", username);
        lv_label_set_text_fmt(volatge, "volatge:%f", node->device_metrics.voltage);
        lv_label_set_text_fmt(batlevel, "batlevel:%d", node->device_metrics.battery_level);
        lv_label_set_text_fmt(ChUtil, "ChUtil:%f", node->device_metrics.channel_utilization);
        lv_label_set_text_fmt(AirUtil, "AirUtil:%f", node->device_metrics.air_util_tx);
        lv_label_set_text_fmt(snr, "snr:%f", node->snr);
        lv_label_set_text_fmt(Lon, "Lon:%d", node->position.longitude_i);
        lv_label_set_text_fmt(Lat, "Lat:%d", node->position.latitude_i);
    }
}

void battery_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_VALUE_CHANGED)
    {
        icon_refresh();
    }
}

void back_btn_handler(lv_event_t *e)
{
    list_menu();
    switch_and_delete_screen(menu_screen);
}

uint32_t keypad_get_key()
{
    /*Your code comes here*/
    /* LVGL有较多操作符，如果你的按键不够用，可以采用组合键的方案 */
    /* 当然，使用外部按键的话你应该考虑“按键抖动”的问题，使用软消抖或硬消抖 */
    /* 假设我有3个按键：“UP”、“SURE”、“DOWN” */

    switch (buttonstate)
    {
    case 1:
        buttonstate = 0;
        return 1;
    case 2:
        buttonstate = 0;
        return 2;
    case 3:
        buttonstate = 0;
        return 3;
    case 4:
        buttonstate = 0;
        return 4;
    case 5:
        buttonstate = 0;
        return 5;
    case 6:
        buttonstate = 0;
        return 6;
    }
    return 0;
}

void keypad_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{
    static uint32_t last_key = 0;
    uint32_t act_key = keypad_get_key();
    if (act_key != 0)
    {
        data->state = LV_INDEV_STATE_PR;
        switch (act_key)
        {
        case 1:
            act_key = LV_KEY_NEXT;
            break;
        case 2:
            act_key = LV_KEY_PREV;
            break;
        case 3:
            act_key = LV_KEY_ENTER;
            break;
        case 4:
            act_key = LV_KEY_ESC;
            if (current_sub_menu != NULL)
                current_sub_menu->previous_menu_callback(NULL);
            break;
        case 5:
            lv_obj_scroll_by_bounded(lv_scr_act(), 0, +80, LV_ANIM_ON); // 向上滑动50像素
            act_key = LV_KEY_ESC;
            break;
        case 6:
            lv_obj_scroll_by_bounded(lv_scr_act(), 0, -80, LV_ANIM_ON); // 向上滑动50像素
            act_key = LV_KEY_ESC;
            break;
        default:
            break;
        }
        last_key = act_key;
    }
    else
    {
        data->state = LV_INDEV_STATE_REL;
    }
    data->key = last_key;
}

<<<<<<< HEAD
=======
void checkbox_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    if (code == LV_EVENT_VALUE_CHANGED)
    {
        const char *txt = lv_checkbox_get_text(obj);
        const char *state = lv_obj_get_state(obj) & LV_STATE_CHECKED ? "Checked" : "Unchecked";
    }
}

>>>>>>> 8458afa345dbcf67a06761ddd18c171214b21447
void scr_refresh()
{
    lv_event_send(lv_scr_act(), LV_EVENT_REFRESH, NULL);
}

void anim_x_cb(void *var, int32_t v)
{
    lv_obj_set_x((lv_obj_t *)var, v);
}

void anim_size_cb(void *var, int32_t v)
{
    lv_obj_set_size((lv_obj_t *)var, v, v);
}

void animation_end_cb(struct _lv_anim_t *)
{
    list_menu();
    lv_scr_load(menu_screen);
}
