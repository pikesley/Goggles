#include <Adafruit_NeoPixel.h>

#define PIN 16
#define BUTTON 7
#define DELAY 35
#define PIXELS 16
#define RIGHT_NOSE 14
#define LEFT_NOSE 4

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(PIXELS * 2, PIN);

uint8_t  mode   = 3, // Current animation effect
         offset = 0; // Position of spinny eyes
volatile byte changeMode = false;

uint32_t red     = 0xFF0000;
uint32_t magenta = 0xFF00FF;
uint32_t green   = 0x00FF00;
uint32_t cyan    = 0x0000FF;
uint32_t blue    = 0x0000FF;

void setup() {
  pinMode(BUTTON, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON), pin_ISR, FALLING);
  pixels.begin();
  pixels.setBrightness(85); // 1/3 brightness
}

void loop() {
  if (changeMode) {
    mode++;
    changeMode = false;
    if (mode > 5) {
      mode = 0;
    }
  }

  switch(mode) {
  case 0:
    rollers(red);
    break;
  case 1:
    blankAll();
    juggle(0xFFFF00);
    break;
  case 2:
    rollers(green);
    break;
  case 3:
    blankAll();
    juggle(cyan);
    break;
  case 4:
    rollers(blue);
    break;
  case 5:
    blankAll();
    juggle(magenta);
    break;


  }
}

void pin_ISR() {
  changeMode = true;
}

void juggle(uint32_t colour) {
  for(int i = 0; i < 1; i++) {
    rollLeft(colour);
    rollRight(colour);
  }
/*  for(int i = 0; i < 2; i++) {
    rollLeft(colour);
  }
  for(int i = 0; i < 1; i++) {
    rollRight(colour);
    rollLeft(colour);
  }
  for(int i = 0; i < 2; i++) {
    rollRight(colour);
  }*/
}

void rollRight(uint32_t colour) {
  for(int i = RIGHT_NOSE; i < PIXELS + RIGHT_NOSE; i++) {
    lightOne(i % PIXELS, 0, colour);
    delay(DELAY);
  }

  blankAll();
}

void rollLeft(uint32_t colour) {
  for(int i = LEFT_NOSE + PIXELS; i > LEFT_NOSE; i--) {
    lightOne(i % PIXELS, PIXELS, colour);
    delay(DELAY);
  }

  blankAll();
}

void lightOne(int index, int offset, uint32_t colour) {
  for(int i = offset; i < PIXELS + offset; i++) {
    uint32_t c = 0;
    if(i == index + offset) c = colour;
    pixels.setPixelColor(i, c);
  }
  pixels.show();
}

void blankAll() {
  for(int i = 0; i < PIXELS * 2; i++) {
    pixels.setPixelColor(i, 0);
  }
  pixels.show();
}

void rollers(uint32_t colour) {
  for(int i = 0; i < PIXELS * 2; i++) {
    uint32_t c = 0;
    if(((offset + i) & 7) < 2) c = colour;
    pixels.setPixelColor(i, c);
  }
  pixels.show();
  offset++;
  delay(DELAY);
}
