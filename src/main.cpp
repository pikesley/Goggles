#include <Arduino.h>
#include <Goggles.h>

int white[]   = {255, 255, 255};
int red[]     = {255,   0,   0};
int orange[]  = {255, 127,   0};
int green[]   = {  0, 255,   0};
int cyan[]    = {  0, 255, 255};
int blue[]    = {  0,   0, 255};
int magenta[] = {255,   0, 255};

void setup() {
  Adafruit_NeoPixel p = Adafruit_NeoPixel(32, 16);
  p.setPixelColor(0, 255, 255, 255);
  p.show();

  /*Goggles g(16, 7, 35, 14, 4, 16);
  g.blankAll();
  g.lightOne(14, 0, red);*/
}

void loop() {
  /*if (changeMode) {
    mode++;
    changeMode = false;
    if (mode > 6) {
      mode = 0;
    }
  }

  switch(mode) {
  case 0:
    blankAll();
    juggle(white);
    break;
  case 1:
    rollers(red);
    break;
  case 2:
    rollers(orange);
    break;
  case 3:
    rollers(green);
    break;
  case 4:
    rollers(cyan);
    break;
  case 5:
    rollers(blue);
    break;
  case 6:
    rollers(magenta);
    break;
  }*/
}
