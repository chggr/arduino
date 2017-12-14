#ifndef FACES_H
#define FACES_H

// Defines all entity faces that will be available in the ecosystem.

const byte FACES[][8] = {
    FACE_SQUARE,
    FACE_CROSS,
    FACE_EX,
    FACE_CIRCLE,
    FACE_DASH,
    FACE_PIPE,
    FACE_HASH,
    FACE_HAITCH,
    FACE_BOXES,
    FACE_HOURGLASS
}

const byte FACES_LEN = sizeof(FACES)/8;

const byte FACE_EMPTY[] = {
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000
}

const byte FACE_DEAD[] = {
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111
}

const byte FACE_SQUARE[] = {
    0b00000000,
    0b01111110,
    0b01000010,
    0b01000010,
    0b01000010,
    0b01000010,
    0b01111110,
    0b00000000
}

const byte FACE_CROSS[] = {
    0b00000000,
    0b00011000,
    0b00011000,
    0b01111110,
    0b01111110,
    0b00011000,
    0b00011000,
    0b00000000
}

const byte FACE_EX[] {
    0b00000000,
    0b01000010,
    0b00100100,
    0b00011000,
    0b00011000,
    0b00100100,
    0b01000010,
    0b00000000
}

const byte FACE_CIRCLE[] = {
    0b00000000,
    0b00011000,
    0b00100100,
    0b01000010,
    0b01000010,
    0b00100100,
    0b00011000,
    0b00000000
}

const byte FACE_DASH[] = {
    0b00000000,
    0b00000000,
    0b00000000,
    0b01111110,
    0b01111110,
    0b00000000,
    0b00000000,
    0b00000000
}

const byte FACE_PIPE[] = {
    0b00000000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00000000
}

const byte FACE_HASH[] = {
    0b00000000,
    0b00100100,
    0b01111110,
    0b00100100,
    0b00100100,
    0b01111110,
    0b00100100,
    0b00000000
}

const byte FACE_HAITCH[] = {
    0b00000000,
    0b01000010,
    0b01000010,
    0b01111110,
    0b01111110,
    0b01000010,
    0b01000010,
    0b00000000
}

const byte FACE_BOXES[] = {
    0b00000000,
    0b01111110,
    0b01000010,
    0b01111110,
    0b01111110,
    0b01000010,
    0b01111110,
    0b00000000
}

const byte FACE_HOURGLASS[] = {
    0b00000000,
    0b01111110,
    0b00100100,
    0b00011000,
    0b00011000,
    0b00100100,
    0b01111110,
    0b00000000
}

#endif // FACES_H

