#include "BarScaler.h"
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

// Resets cursor at the top left corner.
void OledDisplay::resetCursor() {

    command(CMD_COLUMN_ADDR);
    command(0x00);
    command(LCD_WIDTH - 1);

    command(CMD_PAGE_ADDR);
    command(0x00);
    command(7);
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

// Creates a bar plot from the given array of values and displays it in one
// half of the OLED screen.
void OledDisplay::writeBarPlot(double data[]) {
    BarScaler<double> scaler(data, COL_COUNT);

    for (int row = 0; row < 4 ; row++) {

        // Write the left border.
        writeBorder();

        // Write all segments (column and spacing).
        for (int seg = 0; seg < COL_COUNT; seg++) {
            uint8_t value = scaler.get(row, seg);

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

// Displays spectrum information for the left and right channels on the OLED
// screen as bar plots. The bar plot for the left channel will appear on top
// and the bar plot for the right channel at the bottom. The number of bars in
// each plot is controlled via COL_COUNT. The size of both input arrays is
// assumed to be equal to COL_COUNT.
void OledDisplay::spectrum(double left[], double right[]) {
    resetCursor();
    writeBarPlot(left);
    writeBarPlot(right);
}

// Creates a plot from the given array of values and displays it in one half of
// the OLED screen.
void OledDisplay::writePlot(int data[]) {
    // TODO
}

// Displays music samples for the left and right channels on the OLED screen as
// plots. The plot for the left channel will appear on top and the plot for the
// right channel at the bottom.
void OledDisplay::samples(int left[], int right[]) {
    resetCursor();
    writePlot(left);
    writePlot(right);
}

