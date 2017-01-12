// Low power NeoPixel goggles example.  Makes a nice blinky display
// with just a few LEDs on at any time.

#include <Adafruit_NeoPixel.h>

#define PIN 16
#define BUTTON 9

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(32, PIN);

uint8_t  mode   = 0, // Current animation effect
         offset = 0; // Position of spinny eyes
uint32_t color  = 0xFF0000; // Start red
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
    for(i=0; i<32; i++) {
      uint32_t c = 0;
      if(((offset + i) & 7) < 2) c = color; // 4 pixels on...
      pixels.setPixelColor(   i, c); // First eye
     // pixels.setPixelColor(31-i, c); // Second eye (flipped)
    }
    pixels.show();
    offset++;
    delay(50);
    break;
  }

  t = millis();
  if((t - prevTime) > 2000) {      // Every 8 seconds...
    mode++;                        // Next mode
    if(mode > 0) {                 // End of modes?
      mode = 0;                    // Start modes over
      color >>= 8;                 // Next color R->G->B
      if(!color) color = 0xFF0000; // Reset to red
    }
    for(i=0; i<32; i++) pixels.setPixelColor(i, 0);
    prevTime = t;
  }
}
