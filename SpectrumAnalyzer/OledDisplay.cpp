#include "OledDisplay.h"
#include "Range.h"

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

// Returns a byte that represents the given value's magnitude, taking into
// account the min and max values provided. The byte returned is in big-endian
// format, as required by the display.
uint8_t OledDisplay::scale(double value, double min, double max) {
    if (value <= min) {
        return 0x00;
    }
    if (value >= max) {
        return 0xFF;
    }

    uint8_t result = 0;
    double step = (max - min) / 8;
    for (uint8_t i = 0; i < 8; i++) {
        if (value >= min + (i + 1) * step) {
            result |= (1 << (7 - i));
        } else {
            break;
        }
    }
    return result;
}

// Writes a border to the display.
void OledDisplay::writeBorder() {
    Wire.beginTransmission(I2C_ADDR);
    Wire.write(CMD_START_LINE);
    for (uint8_t i = 0; i < BORDER_WIDTH; i++) {
        Wire.write(0x00);
    }
    Wire.endTransmission();
}

// Writes data to one half of the display. Ensures that data is scaled properly
// before writing to the display.
void OledDisplay::write(double values[]) {
    uint8_t row_count = LCD_HEIGHT / 8 / 2;
    Range<double> range(values, COL_COUNT);
    double step = range.getMax() / row_count;

    for (uint8_t row = 0; row < row_count; row++) {

        // Write the left border.
        writeBorder();

        // Write all segments (column and spacing).
        for (uint8_t seg = 0; seg < COL_COUNT; seg++) {
            uint8_t value = scale(values[seg],
                    (row_count - row - 1) * step,
                    (row_count - row) * step);

            Wire.beginTransmission(I2C_ADDR);
            Wire.write(CMD_START_LINE);
            for (uint8_t i = 0; i < COL_WIDTH + COL_SPACING; i++) {
                Wire.write(i < COL_SPACING ? 0x00 : value);
            }
            Wire.endTransmission();
        }

        // Write the right border.
        writeBorder();
    }
}

// Writes spectrum data for the left and right channel to the display. The size
// of both arrays is assumed to be equal to COL_COUNT.
void OledDisplay::write(double left[], double right[]) {

    // Set cursor at the top left corner.
    command(CMD_COLUMN_ADDR);
    command(0x00);
    command(LCD_WIDTH - 1);

    command(CMD_PAGE_ADDR);
    command(0x00);
    command(7);

    // Write left channel on top, right channel below.
    write(left);
    write(right);
}

