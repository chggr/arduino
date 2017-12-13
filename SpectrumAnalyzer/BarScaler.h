#ifndef BAR_SCALER_H
#define BAR_SCALER_H

#include <Arduino.h>
#include "Range.h"

// Scales the given array of values into a 16 bit integer in little endian
// format, so that it can be used to display a bar plot in an OLED display.
// The bars will be displayed in two 8-bit rows in the OLED screen.

template <class T>
class BarScaler {

    private:
        uint16_t *scaled;

    public:
        BarScaler(T values[], int size);
        ~BarScaler();
        uint8_t get(int row, int index);
};

template <class T>
BarScaler<T>::BarScaler(T values[], int size) {

    // Calculate the range of values.
    Range<T> range(values, size);
    T min = range.getMin();
    T max = range.getMax();
    T step = (max - min) / 16;

    // Calculate the 16 level thresholds.
    T levels[16];
    for (int i = 0; i < 16; i++) {
        levels[i] = min + (i + 1) * step;
    }

    // Scale the input values.
    scaled = new uint16_t[size];
    uint16_t temp;
    for (int i = 0; i < size; i++) {
        temp = 0;

        for (int j = 0; j < 16; j++) {
            if (values[i] < levels[i]) break;
            temp |= (1 << (16 - j));
        }
        scaled[i] = temp;
    }
}

template <class T>
BarScaler<T>::~BarScaler() {
    delete scaled;
}

template <class T>
uint8_t BarScaler<T>::get(int row, int index) {
    return row == 0 ? scaled[index] & 0xFF : scaled[index] >> 8;
}

#endif // BAR_SCALER_H

