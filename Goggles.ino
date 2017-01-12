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

const uint8_t PROGMEM gamma8[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
    2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
    5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
   10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
   17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
   25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
   37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
   51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
   69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
   90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
  115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
  144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
  177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
  215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255 };
