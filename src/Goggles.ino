#include <Arduino.h>
#include <gamma.h>

#include <Adafruit_NeoPixel.h>

#define PIN 16
#define BUTTON 7
#define DELAY 35
#define PIXELS 16
#define RIGHT_NOSE 14
#define LEFT_NOSE 4

extern const uint8_t gamma8[];
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(PIXELS * 2, PIN);

uint8_t  mode   = 0, // Current animation effect
         offset = 0; // Position of spinny eyes
volatile byte changeMode = false;

int white[]   = {255, 255, 255};
int red[]     = {255,   0,   0};
int orange[]  = {255, 127,   0};
int green[]   = {  0, 255,   0};
int cyan[]    = {  0, 255, 255};
int blue[]    = {  0,   0, 255};
int magenta[] = {255,   0, 255};

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
  }
}

void pin_ISR() {
  changeMode = true;
}

void juggle(int colour[]) {
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

void rollRight(int colour[]) {
  for(int i = RIGHT_NOSE; i < PIXELS + RIGHT_NOSE; i++) {
    lightOne(i % PIXELS, 0, colour);
    delay(DELAY);
  }

  blankAll();
}

void rollLeft(int colour[]) {
  for(int i = LEFT_NOSE + PIXELS; i > LEFT_NOSE; i--) {
    lightOne(i % PIXELS, PIXELS, colour);
    delay(DELAY);
  }

  blankAll();
}

void lightOne(int index, int offset, int colour[]) {
  for(int i = offset; i < PIXELS + offset; i++) {
    pixels.setPixelColor(i, 0);
    if(i == index + offset) {
      pixels.setPixelColor(i,
                           pgm_read_byte(&gamma8[colour[0]]),
                           pgm_read_byte(&gamma8[colour[1]]),
                           pgm_read_byte(&gamma8[colour[2]]));
    }
  }
  pixels.show();
}

void blankAll() {
  for(int i = 0; i < PIXELS * 2; i++) {
    pixels.setPixelColor(i, 0);
  }
  pixels.show();
}

void rollers(int colour[]) {
  for(int i = 0; i < PIXELS * 2; i++) {
    pixels.setPixelColor(i, 0);
    if(((offset + i) & 7) < 2) {
      pixels.setPixelColor(i,
                           pgm_read_byte(&gamma8[colour[0]]),
                           pgm_read_byte(&gamma8[colour[1]]),
                           pgm_read_byte(&gamma8[colour[2]]));
    }
  }
  pixels.show();
  offset++;
  delay(DELAY);
}
