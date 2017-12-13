#ifndef OLED_DISPLAY_H
#define OLED_DISPLAY_H

#include <Arduino.h>
#include <Wire.h>

// LCD spec and address.
#define LCD_WIDTH 128
#define LCD_HEIGHT 64
#define I2C_ADDR 0x3C

// LCD commands.
#define CMD_DISPLAY_OFF        0xAE
#define CMD_CLK_DIVIDE_RATIO   0xD5
#define CMD_MULTIPLEX          0xA8
#define CMD_DISPLAY_OFFSET     0xD3
#define CMD_START_LINE         0x40
#define CMD_CHARGE_PUMP        0x8D
#define CMD_MEMORY_MODE        0x20
#define CMD_SEGMENT_REMAP      0xA1
#define CMD_COM_OUT_SCAN_DIR   0xC8
#define CMD_SET_COM_PINS       0xDA
#define CMD_SET_CONTRAST       0x81
#define CMD_SET_PRECHARGE      0xD9
#define CMD_VCOMH_DESEL_LEV    0xDB
#define CMD_DISPLAY_ALL_ON     0xA4
#define CMD_NORMAL_INVERSE     0xA6
#define CMD_DEACTIVATE_SCROLL  0x2E
#define CMD_DISPLAY_ON         0xAF
#define CMD_COLUMN_ADDR        0x21
#define CMD_PAGE_ADDR          0x22

// UI preferences.
// Values in pixels should satisfy the following equation:
// 2 * BORDER_WIDTH + COL_COUNT * (COL_WIDTH + COL_SPACING) = LCD_WIDTH

// Ten thick columns.
// #define BORDER_WIDTH 4
// #define COL_COUNT 10
// #define COL_WIDTH 10
// #define COL_SPACING 2

// Twenty thin columns.
#define BORDER_WIDTH 4
#define COL_COUNT 20
#define COL_WIDTH 5
#define COL_SPACING 1

// Sixty columns, no spacing.
// #define BORDER_WIDTH 4
// #define COL_COUNT 60
// #define COL_WIDTH 2
// #define COL_SPACING 0

class OledDisplay {

    public:
        void init();
        void write(double left[], double right[]);

    private:
        void command(uint8_t c);
        void write(double data[]);
        void writeBorder();
};

#endif // OLED_DISPLAY_H

