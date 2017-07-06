#include <Arduino.h>

#define DATA_PIN_A 10
#define LATCH_PIN_A 11
#define CLOCK_PIN_A 12

#define DATA_PIN_B 2
#define LATCH_PIN_B 3
#define CLOCK_PIN_B 4

#define INPUT_PIN 5

#define DELAY 100

// An array of characters holding information about which dots / leds should
// light up to represent each number. For example dots[1] represents number 1
// and thus only the middle led is active. Similarly, dots[4] represents number
// 4 and therefore all corner dots should light up.
unsigned char dots[7] = { 0b00000000,
                          0b00001000,
                          0b01000001,
                          0b01001001,
                          0b01010101,
                          0b01011101,
                          0b01110111 };

// Displays the given number on either dice A or dice B according to the
// boolean parameter. The provided number should be between 0 and 6.
void displayNumber(unsigned char num, bool diceA) {
    int dataPin = diceA ? DATA_PIN_A : DATA_PIN_B;
    int latchPin = diceA ? LATCH_PIN_A : LATCH_PIN_B;
    int clockPin = diceA ? CLOCK_PIN_A : CLOCK_PIN_B;

    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, dots[num]);
    digitalWrite(latchPin, HIGH);
}          

// Sets the input and output pins. The internall pull-up resistor is used on
// the input pin to ensure no noise is picked up during operation. Additionally
// seeds the random number generator with noise picked up by analog pin 0, so
// that rolling the dice is as random as possible.
void setup() {
    pinMode(INPUT_PIN, INPUT_PULLUP);

    pinMode(DATA_PIN_A, OUTPUT);
    pinMode(LATCH_PIN_A, OUTPUT);
    pinMode(CLOCK_PIN_A, OUTPUT);

    pinMode(DATA_PIN_B, OUTPUT);
    pinMode(LATCH_PIN_B, OUTPUT);
    pinMode(CLOCK_PIN_B, OUTPUT);

    randomSeed(analogRead(0));

    displayNumber(0, true);
    displayNumber(0, false);
}

// Waits until the user has pressed the button to roll the dice. Picks up a
// random number between 30 and 50 inclusive so that the dice roll for three
// to five seconds before settling on the final number.
void loop() {
    if (digitalRead(INPUT_PIN) == LOW) {
        int rollCount = random(30, 51);
        for (int i = 0; i < rollCount; i++) {
            displayNumber(random(1, 7), true);
            displayNumber(random(1, 7), false);
            delay(DELAY);
        }
    }
    delay(DELAY);
}

