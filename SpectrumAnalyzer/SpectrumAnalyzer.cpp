#include <Arduino.h>
#include "OledDisplay.h"

#define PI 3.14159265359

#define LEFT_INPUT_PIN A0
#define RIGHT_INPUT_PIN A1

#define BUFFER_SIZE 800
#define SAMPLE_FREQ 76923
#define FREQ_STEP 1000

int buffer[BUFFER_SIZE] = { 0 };
double left_dft[COL_COUNT] = { 0.0 };
double right_dft[COL_COUNT] = { 0.0 };
OledDisplay display;

// Sets the input pin and initializes the ATmega328 analog to digital converter
// (ADC). The micro controller's clock speed is 16 MHz and the ADC conversion
// takes 13 clock cycles. The ADC prescaler is set to 16, so that the overall
// conversion frequency is (16 MHz) / (13 * 16) = 76923 Hz.
//
// Audible sound frequency ranges from 20 Hz to 20000 Hz, so we need a sampling
// frequency greater than 40000 Hz to be able to capture the highest frequency
// components in the audible spectrum. Higher sampling frequency also allows
// the buffer to fill up faster, thus achieving almost real-time performance.
// Having said that, the ADC prescaller should not be set to less than 16, as
// lower values (8, 4 and 2) are known to cause significant conversion
// inaccuracies.
void setup() {
    pinMode(LEFT_INPUT_PIN, INPUT);
    pinMode(RIGHT_INPUT_PIN, INPUT);

    display.init();

    ADCSRA = bit(ADEN) | bit(ADPS2);
}

// Stores samples of the signal attached to the input pin into the buffer.
void sample(uint8_t pin) {
    for (uint16_t i = 0; i < BUFFER_SIZE; i++) {
        buffer[i] = analogRead(pin);
    }
}

// Calculates the k-th element of the Discrete Fourier transformation of the
// signal stored in the buffer. This is a complex number, so this method
// returns its magnitude.
double DFT(unsigned int k) {
    double re = 0, im = 0, phase;

    for (uint16_t n = 1; n < BUFFER_SIZE; n++) {
        phase = 2 * PI * k * n / SAMPLE_FREQ;
        re += buffer[n] * cos(phase);
        im -= buffer[n] * sin(phase);
    }
    return sqrt(re * re + im * im);
}

void loop() {
    sample(LEFT_INPUT_PIN);
    for (uint8_t i = 1; i <= COL_COUNT; i++) {
        left_dft[i] = DFT(i * FREQ_STEP);
    }

    sample(RIGHT_INPUT_PIN);
    for (uint8_t i = 1; i <= COL_COUNT; i++) {
        right_dft[i] = DFT(i * FREQ_STEP);
    }

    display.spectrum(right_dft, left_dft, COL_COUNT);
}

