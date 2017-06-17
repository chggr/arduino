#include <Arduino.h>

#define DATA_PIN 6
#define LATCH_PIN 5
#define CLOCK_PIN 4
#define INPUT_PIN 3

#define NOOP 0
#define RANDOM 1
#define PRIME 2
#define CASCADE 3
#define COUNTER 4
#define CLOCK 5
#define FIBONACCI 6
#define ABUNDANT 7
#define FACTORIAL 8
#define HAPPY 9
#define JUGGLER 10
#define COMPLEMENT 11
#define PERFECT 12

#define DELAY 1000
#define BIT_COUNT 32

// Sets the input and output pins and seeds the random number generator
// by reading random noise from an analog input pin. The internal pull
// up resistor is used on the input pin to ensure no noise is picked up
// during operation.
void setup() {
    pinMode(LATCH_PIN, OUTPUT);
    pinMode(CLOCK_PIN, OUTPUT);    
    pinMode(DATA_PIN, OUTPUT);
    pinMode(INPUT_PIN, INPUT_PULLUP);
    
    randomSeed(analogRead(0));
}

// Retrieves the current operational mode and calls the correct function
// accordingly. Repeates this step after a given delay to allow enough
// time for the result to be displayed.
void loop() {
    switch (getMode()) {
        case NOOP: break;
        case RANDOM: displayRandom(); break;
        case PRIME: displayPrime(); break;
        case CASCADE: displayCascade(); break;
        case COUNTER: displayCounter(); break;
        case CLOCK: displayClock(); break;
        case FIBONACCI: displayFibonacci(); break;
        case ABUNDANT: displayAbundant(); break;
        case FACTORIAL: displayFactorial(); break;
        case HAPPY: displayHappy(); break;
        case JUGGLER: displayJuggler(); break;
        case COMPLEMENT: displayComplement(); break;
        case PERFECT: displayPerfect(); break;
    }
    delay(DELAY);
}

// Returns the current operational mode. Detects if the user is causing the
// input pin to go LOW and changes the mode accordingly.
unsigned char getMode() {
    static unsigned char mode;
    if (digitalRead(INPUT_PIN) == LOW) {
        mode = (mode > PERFECT) ? 0 : mode + 1;
    }
    return mode;
}

// Writes the provided number in binary form to the output pins.
void displayNumber(unsigned long num) {
    digitalWrite(LATCH_PIN, LOW);
    shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, num);    
    shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, (num >> 8));    
    shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, (num >> 16));
    shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, (num >> 24));    
    digitalWrite(LATCH_PIN, HIGH);
}

// Displays a cascading bit that moves from the lowest pin number to
// the highest. If LEDs are attached to the output pins, this will
// produce an effect where each LED lights up in sequence.
void displayCascade() {
    static unsigned long num;
    num <<= 1;
    if (num == 0) {
        num = 1;
    }
    displayNumber(num);
}

// Displays a random number between 0 and the maximum number that can
// be represented using the given bit count.
void displayRandom() {
    unsigned long partA = random(1UL << BIT_COUNT - 1);
    unsigned long partB = random(1UL << BIT_COUNT - 1);
    displayNumber(partA + partB);
}

// Displays the next prime number between 1 and the maximum number that
// can be represented using the given output pin count.
void displayPrime() {
    static unsigned long num;
    
    while(!isPrime(++num)) { }
    displayNumber(num);
}

// Returns true if the provided number is a prime number, false otherwise.
boolean isPrime(unsigned long num) {
    for (int i=2; i<=num/2; i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

// Counts from 0 to the maximum number that can be represented using the
// given output pin count.
void displayCounter() {
    static unsigned long num;
    displayNumber(++num);
}

// Displays a clock that counts the seconds, minutes, hours and days.
void displayClock() {
    static unsigned long seconds;
    static unsigned long minutes;
    static unsigned long hours;
    static unsigned long days;
    
    seconds++;
    if (seconds == 60) {
        seconds = 0;
        minutes++;
    }
    if (minutes == 60) {
        minutes = 0;
        hours++;
    }
    if (hours == 24) {
        hours = 0;
        days++;
    }
    if (days > (1UL << 8) - 1) {
        seconds = 0;
        minutes = 0;
        hours = 0;
        days = 0;
    }
    
    displayNumber((days << 24) + (hours << 16) + (minutes << 8) + seconds);
}

// Displays numbers in the Fibonacci sequence.
void displayFibonacci() {
    static unsigned long previous = 0;
    static unsigned long current = 1;
    
    unsigned long sum = current + previous;
    // Detect overflows and reset the sequence.
    if (sum < current) {
        previous = 0;
        current = 1;
    } else {
        previous = current;
        current = sum;
    }
    displayNumber(current);
}

// Displays abundant numbers, i.e. numbers whose sum of proper divisors is
// greater than the number itself.
void displayAbundant() {
    static unsigned long num;
    unsigned long sum;

    while(true) {
        num++;
        sum = 0;
        for (int i=1; i<=num/2; i++) {
            if (num%i == 0) {
                sum += i;
            }
        }
        if (sum > num) {
            break;
        }
    }
    displayNumber(num);
}

// Displays the factorial of a number (n!), which is the sum of all positive
// integers less than or equal to that number.
void displayFactorial() {
    static unsigned char num;
    unsigned long factorial = 1;

    num++;
    for (int i=1; i<=num; i++) {
        factorial *= i;
    }

    // Reset num to avoid overflows.
    if (num >= 12) {
        num = 0;
    }
    displayNumber(factorial);
}

// Displays happy numbers, i.e. numbers whose sum of squares of digits
// converges to 1 after a given number of itterations (in this case 1000).
void displayHappy() {
    static unsigned long num;

    while (!isHappy(++num)) { }
    displayNumber(num);
}

boolean isHappy(unsigned long num) {
    for (int i=0; i<1000; i++) {
        num = sumSquaresDigits(num);
        if (num == 1) {
            break;
        }
    }
    return num == 1;
}

unsigned long sumSquaresDigits(unsigned long num) {
    unsigned long sum = 0;
    unsigned char digit;

    while (num > 0) {
        digit = num % 10;
        num /= 10;
        sum += digit * digit; 
    }
    return sum;
}

// Picks up a random number and displays its Juggler sequence, i.e. a sequence
// converging to one that is defined as n^(1/2) if n is even and n^(3/2) if n
// is odd.
void displayJuggler() {
    static unsigned long num;

    if (num == 1 || num == 0) {
        num = random(1UL << 10);
    }
    num = pow(num, num % 2 == 0 ? 0.5 : 1.5);
    displayNumber(num);  
}

// Counts from 0 to 2^17 - 1 and displays both the number and its complement.
void displayComplement() {
    static unsigned long num;
    if (++num > (1UL << BIT_COUNT / 2) - 1) {
        num = 0;
    }
    displayNumber(num + ((~num) << BIT_COUNT / 2));
}

// Displays perfect numbers, i.e. numbers that are equal to the sum of all
// proper positive divisors excluding the number itself.
void displayPerfect() {
    static unsigned long num;

    while (!isPerfect(++num)) { }
    displayNumber(num);
}

boolean isPerfect(unsigned long num) {
    unsigned long sum = 0;
    for (int i=0; i<=num/2; i++) {
        if (num % i == 0) {
            sum += i;
        }
    }
    return sum == num;
}


