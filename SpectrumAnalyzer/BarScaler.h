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

    Range<T> range(values, size);
    T min = range.getMin();
    T max = range.getMax();
    T step = (max - min) / 16;

    scaled = new uint16_t[size];
    for (int i = 0; i < size; i++) {
        scaled[i] = 0;

        for (int j = 0; j < 16; j++) {
            if (values[i] >= min + (j + 1) * step) {
                scaled[i] |= (1 << (16 - i));
            } else {
                break;
            }
        }
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

