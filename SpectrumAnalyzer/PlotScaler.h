#ifndef PLOT_SCALER_H
#define PLOT_SCALER_H

#include <Arduino.h>
#include "Range.h"

// Scales the given array of values into 32-bit integers in little endian
// format. The output can be used to create a plot in an OLED display. If
// the input array size is greater than the scaled size, the values in the
// input array will be compressed by taking the average of neighbouring
// samples.

template <class T>
class PlotScaler {

    private:
        uint32_t *scaled;

    public:
        PlotScaler(T values[], int size, int scaledSize);
        ~PlotScaler();
        uint8_t get(int row, int index);
};

template <class T>
PlotScaler<T>::PlotScaler(T values[], int size, int scaledSize) {

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

    // Scale the input values, compress them if too many.
    scaled = new uint32_t[scaledSize];
    int compression = size / scaledSize;
    uint32_t bit = 1;
    uint32_t sum;
    for (int i = 0; i < scaledSize; i++) {
        sum = 0;
        for (int j = 0; j < compression; j++) {
            sum += values[i * compression + j];
        }
        sum /= compression;

        scaled[i] = bit;
        for (int j = 0; j < 32; j++) {
            if (sum <= levels[j]) {
                scaled[i] = bit << (32 - j - 1);
                break;
            }
        }
    }
}

template <class T>
PlotScaler<T>::~PlotScaler() {
    delete scaled;
}

template <class T>
uint8_t PlotScaler<T>::get(int row, int index) {
    uint32_t value = scaled[index];
    int shift = row * 8;
    return (value >> shift) & 0xFF;
}

#endif // PLOT_SCALER_H

