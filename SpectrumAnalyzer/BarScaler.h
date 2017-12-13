#ifndef BAR_SCALER_H
#define BAR_SCALER_H

#include <Arduino.h>
#include "Range.h"

// Scales each value in the given array into a 32-bit integer in little endian
// format, so that it can be used to create a bar plot in an OLED display.
// The bars will be displayed in four 8-bit rows in the OLED screen.

template <class T>
class BarScaler {

    private:
        uint32_t *scaled;

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
    T step = (max - min) / 32;

    // Calculate the 32 level thresholds.
    T levels[32];
    for (int i = 0; i < 32; i++) {
        levels[i] = min + (i + 1) * step;
    }

    // Scale the input values.
    scaled = new uint32_t[size];
    uint32_t result;
    uint32_t bit = 1;
    for (int i = 0; i < size; i++) {
        result = 0;

        for (int j = 0; j < 32; j++) {
            if (values[i] < levels[j]) break;
            result |= (bit << (32 - j));
        }
        scaled[i] = result;
    }
}

template <class T>
BarScaler<T>::~BarScaler() {
    delete scaled;
}

template <class T>
uint8_t BarScaler<T>::get(int row, int index) {
    uint32_t value = scaled[index];
    int shift = row * 8;
    return (value >> shift) & 0xFF;
}

#endif // BAR_SCALER_H

