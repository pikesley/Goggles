#include <Adafruit_NeoPixel.h>

#define PIN 16
#define BUTTON 9
#define DELAY 35

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(32, PIN);

uint8_t  mode   = 0, // Current animation effect
         offset = 0; // Position of spinny eyes
uint32_t prevTime;

void setup() {
  pixels.begin();
  pixels.setBrightness(85); // 1/3 brightness
  prevTime = millis();
}

void loop() {
  uint8_t  i;
  uint32_t t;

  switch(mode) {

  case 0:
    wheel(0xFF0000);
    break;
  case 1:
    wheel(0x00FF00);
    break;
  case 2:
    wheel(0x0000FF);
    break;
  }

  t = millis();
  if((t - prevTime) > DELAY * 16) {
    mode++;
    if(mode > 2) {
      mode = 0;
    }
    for(i=0; i<32; i++) pixels.setPixelColor(i, 0);
    prevTime = t;
  }
}

void wheel(uint32_t colour) {
  for(int i=0; i<32; i++) {
    uint32_t c = 0;
    if(((offset + i) & 7) < 2) c = colour;
    pixels.setPixelColor(   i, c);
  }
  pixels.show();
  offset++;
  delay(DELAY);
}
