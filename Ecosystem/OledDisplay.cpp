#include "OledDisplay.h"

// Sends a command to the LCD display.
void OledDisplay::command(uint8_t c) {
    Wire.beginTransmission(I2C_ADDR);
    Wire.write(0x00);
    Wire.write(c);
    Wire.endTransmission();
}

// Initializes the display as per data sheet.
void OledDisplay::init() {
    Wire.begin();
    delay(10);

    command(CMD_DISPLAY_OFF);

    command(CMD_CLK_DIVIDE_RATIO);
    command(0x80);

    command(CMD_MULTIPLEX);
    command(LCD_HEIGHT - 1);

    command(CMD_DISPLAY_OFFSET);
    command(0x00);

    command(CMD_START_LINE | 0x00);

    command(CMD_CHARGE_PUMP);
    command(0x14);

    command(CMD_MEMORY_MODE);
    command(0x00);

    command(CMD_SEGMENT_REMAP | 0x01);
    command(CMD_COM_OUT_SCAN_DIR);

    command(CMD_SET_COM_PINS);
    command(0x12);

    command(CMD_SET_CONTRAST);
    command(0xCF);

    command(CMD_SET_PRECHARGE);
    command(0xF1);

    command(CMD_VCOMH_DESEL_LEV);
    command(0x40);

    command(CMD_DISPLAY_ALL_ON);
    command(CMD_NORMAL_INVERSE);
    command(CMD_DEACTIVATE_SCROLL);
    command(CMD_DISPLAY_ON);
}

// Resets cursor at the top left corner.
void OledDisplay::resetCursor() {

    command(CMD_COLUMN_ADDR);
    command(0x00);
    command(LCD_WIDTH - 1);

    command(CMD_PAGE_ADDR);
    command(0x00);
    command(7);
}

// Displays the given world on the OLED screen.
void OledDisplay::display(World &world) {
    resetCursor();

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 16; j++) {
            Wire.beginTransmission(I2C_ADDR);
            Wire.write(CMD_START_LINE);

            for (int k = 0; k < 8; k++) {
                Wire.write(world.getByte(i, j * 8 + k));
            }
            Wire.endTransmission();
        }
    }
}

