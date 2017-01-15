#include <Adafruit_NeoPixel.h>
#include <gamma.h>

#define PIN 16
#define BUTTON 7
#define DELAY 35
#define PIXELS 16
#define RIGHT_NOSE 14
#define LEFT_NOSE 4

extern const int gamma8[];
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(PIXELS * 2, PIN);
volatile byte changeMode = false;
int offset = 0;

int white[]   = {255, 255, 255};
int red[]     = {255,   0,   0};
int orange[]  = {255, 127,   0};
int green[]   = {  0, 255,   0};
int cyan[]    = {  0, 255, 255};
int blue[]    = {  0,   0, 255};
int magenta[] = {255,   0, 255};

void pin_ISR() {
  changeMode = true;
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


void setup() {
  pinMode(BUTTON, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON), pin_ISR, FALLING);
  pixels.begin();
  pixels.setBrightness(85); // 1/3 brightness
}
