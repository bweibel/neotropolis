#include <Adafruit_NeoPixel.h>

#define PIN        6   // NeoPixel data pin
#define NUMPIXELS  15  // Number of NeoPixels in your strip

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int mode = 0; // Start in mode 0

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(9600); // Initialize serial communication at 9600 bits per second
}

void loop() {
  while (Serial.available() > 0) { // If data is available to read
    char c = Serial.read(); // Read it
    if (c == 'n') { // If 'n' was received
      mode++; // Switch to the next mode
      if (mode > 3) mode = 0; // If we've gone past the last mode, wrap around to the first one
    }
  }

  switch (mode) {
    case 0:
      setAllLEDs(255, 0, 0); // Red
      break;
    case 1:
      setAllLEDs(0, 255, 0); // Green
      break;
    case 2:
      setAllLEDs(0, 0, 255); // Blue
      break;
    case 3:
      rainbowCycle(20); // Rainbow cycle
      break;
  }
}

void setAllLEDs(uint8_t red, uint8_t green, uint8_t blue) {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(red, green, blue));
  }
  strip.show();
}

void rainbowCycle(uint8_t wait) {
  uint16_t i, j;
  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
