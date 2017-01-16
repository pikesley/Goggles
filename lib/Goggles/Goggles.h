#ifndef Goggles_h
#define Goggles_h

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

class Goggles {
public:
  Goggles(
    int pin,
    int sleep,
    int right_nose,
    int left_nose,
    int pixel_count
  );

  void blank();

  void roll(int colour[]);
  void juggle(int colour[]);

private:
  int correctColour(int component);
  void rollLeft(int colour[]);
  void rollRight(int colour[]);
  void lightOne(int index, int offset, int colour[]);

  int _sleep;
  int pin;
  int _right_nose;
  int _left_nose;
  int _pixel_count;
  int _offset;
  Adafruit_NeoPixel pixels;
};

#endif
