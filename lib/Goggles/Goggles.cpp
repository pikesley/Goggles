#include <Goggles.h>

Goggles::Goggles(
  int pin,
  int sleep,
  int right_nose,
  int left_nose,
  int pixel_count
) {
  pin = pin;
  _sleep = sleep;
  _right_nose = right_nose;
  _left_nose = left_nose;
  _pixel_count = pixel_count;

  _offset = 0;

  pixels = Adafruit_NeoPixel(pixel_count * 2, pin);
  pixels.begin();
  pixels.setBrightness(85);
}

void Goggles::blank() {
  for(int i = 0; i < _pixel_count * 2; i++) {
    pixels.setPixelColor(i, 0);
  }
  pixels.show();
}

void Goggles::roll(int colour[]) {
  for(int i = 0; i < _pixel_count * 2; i++) {
    pixels.setPixelColor(i, 0);
    if(((_offset + i) & 7) < 2) {
      pixels.setPixelColor(i,
                           correctColour(colour[0]),
                           correctColour(colour[1]),
                           correctColour(colour[2]));
    }
  }
  pixels.show();
  _offset++;
  delay(_sleep);
}

void Goggles::juggle(int colour[]) {
  for(int i = 0; i < 1; i++) {
    rollLeft(colour);
    rollRight(colour);
  }
  for(int i = 0; i < 2; i++) {
    rollLeft(colour);
  }
  for(int i = 0; i < 1; i++) {
    rollRight(colour);
    rollLeft(colour);
  }
  for(int i = 0; i < 2; i++) {
    rollRight(colour);
  }
}

void Goggles::lightOne(int index, int offset, int colour[]) {
  for(int i = offset; i < _pixel_count * 2; i++) {
    pixels.setPixelColor(i, 0);
    if(i == index + offset) {
      pixels.setPixelColor(i,
                           correctColour(colour[0]),
                           correctColour(colour[1]),
                           correctColour(colour[2]));
    }
  }
  pixels.show();
}

int Goggles::correctColour(int component) {
  // from https://learn.adafruit.com/led-tricks-gamma-correction/the-quick-fix
  int gamma8[] = {
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   1,   1,   1,
        1,   1,   1,   1,   1,   1,   1,   1,   1,   2,   2,   2,   2,   2,   2,   2,
        2,   3,   3,   3,   3,   3,   3,   3,   4,   4,   4,   4,   4,   5,   5,   5,
        5,   6,   6,   6,   6,   7,   7,   7,   7,   8,   8,   8,   9,   9,   9,  10,
       10,  10,  11,  11,  11,  12,  12,  13,  13,  13,  14,  14,  15,  15,  16,  16,
       17,  17,  18,  18,  19,  19,  20,  20,  21,  21,  22,  22,  23,  24,  24,  25,
       25,  26,  27,  27,  28,  29,  29,  30,  31,  32,  32,  33,  34,  35,  35,  36,
       37,  38,  39,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  50,
       51,  52,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,  64,  66,  67,  68,
       69,  70,  72,  73,  74,  75,  77,  78,  79,  81,  82,  83,  85,  86,  87,  89,
       90,  92,  93,  95,  96,  98,  99, 101, 102, 104, 105, 107, 109, 110, 112, 114,
      115, 117, 119, 120, 122, 124, 126, 127, 129, 131, 133, 135, 137, 138, 140, 142,
      144, 146, 148, 150, 152, 154, 156, 158, 160, 162, 164, 167, 169, 171, 173, 175,
      177, 180, 182, 184, 186, 189, 191, 193, 196, 198, 200, 203, 205, 208, 210, 213,
      215, 218, 220, 223, 225, 228, 231, 233, 236, 239, 241, 244, 247, 249, 252, 255
    };

  return gamma8[component];
}

void Goggles::rollRight(int colour[]) {
  for(int i = _right_nose; i < _pixel_count + _right_nose; i++) {
    lightOne(i % _pixel_count, 0, colour);
    delay(_sleep);
  }

  blank();
}

void Goggles::rollLeft(int colour[]) {
  for(int i = _left_nose + _pixel_count; i > _left_nose; i--) {
    lightOne(i % _pixel_count, _pixel_count, colour);
    delay(_sleep);
  }

  blank();
}
