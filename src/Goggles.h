#ifndef Goggles_h
#define Goggles_h

#include "Arduino.h"
#include "Adafruit_NeoPixel.h"

class Goggles {
public:
  Goggles(
    int pin,
    int sleep,
    int right_nose,
    int left_nose,
    int pixel_count
  );

  void lightOne(int index, int offset, int colour[]);
  void blankAll();
  int correctColour(int component);

  int pin;
  int _sleep;
  int right_nose;
  int left_nose;
  int _pixel_count;
  int _offset;
  Adafruit_NeoPixel pixels;

  void roll(int colour[]);
};

#endif
