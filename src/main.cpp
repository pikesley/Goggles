#include <Goggles.h>

int white[]   = {255, 255, 255};
int red[]     = {255,   0,   0};
int orange[]  = {255, 127,   0};
int green[]   = {  0, 255,   0};
int cyan[]    = {  0, 255, 255};
int blue[]    = {  0,   0, 255};
int magenta[] = {255,   0, 255};

int button = 7;
int mode = 0;
volatile byte changeMode = false;

Goggles goggles(16, // pin
                35, // delay (ms)
                14, // right-eye nose pin
                4,  // left-eye nose pin
                16  // pixels-per-eye
              );

void pin_ISR() {
  changeMode = true;
}

void setup() {
  pinMode(button, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(button), pin_ISR, FALLING);
  goggles.blank();
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
    goggles.blank();
    goggles.juggle(white);
    break;
  case 1:
    goggles.roll(red);
    break;
  case 2:
    goggles.roll(orange);
    break;
  case 3:
    goggles.roll(green);
    break;
  case 4:
    goggles.roll(cyan);
    break;
  case 5:
    goggles.roll(blue);
    break;
  case 6:
    goggles.roll(magenta);
    break;
  }
}
