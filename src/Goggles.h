#ifndef Goggles_h
#define Goggles_h

#include "Arduino.h"
#include "Adafruit_NeoPixel.h"

class Goggles {
public:
  Goggles(
    int pin,
    int button,
    int sleep,
    int right_nose,
    int left_nose,
    int pixel_count
  );

  void lightOne(int index, int offset, int colour[]);

  int pin;
  int button;
  int sleep;
  int right_nose;
  int left_nose;
  int pixel_count;
  Adafruit_NeoPixel pixels;

  const int PROGMEM gamma8[];
};

#endif
