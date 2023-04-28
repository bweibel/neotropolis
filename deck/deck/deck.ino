#include <Adafruit_NeoPixel.h>

#define PIN        6   // NeoPixel data pin
#define NUMPIXELS  16  // Number of NeoPixels in your strip

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int mode = 0; // Start in mode 0
uint16_t j = 0; // For rainbow cycle
uint32_t lastUpdate = 0; // For non-blocking delay
uint8_t brightness = 0; // For breathing effect
bool increasing = true; // For breathing effect
int wipeIndex = 0; // For colorWipe

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
      if (mode > 5) mode = 0; // If we've gone past the last mode, wrap around to the first one
    }
  }

  switch (mode) {
    case 0:
      if (millis() - lastUpdate > 10) { // Non-blocking delay
        lastUpdate = millis();
        brightnessUpdate(); // Update brightness for breathing effect
        setAllLEDs( brightness + 100, 0, 0); // Red
      }
      break;
    case 1:
      if (millis() - lastUpdate > 10) { // Non-blocking delay
        lastUpdate = millis();
        brightnessUpdate(); // Update brightness for breathing effect
        setAllLEDs(0, brightness + 100, 0); // Green
      }
      break;
    case 2:
      if (millis() - lastUpdate > 10) { // Non-blocking delay
        lastUpdate = millis();
        brightnessUpdate(); // Update brightness for breathing effect
        setAllLEDs(0, 0, brightness + 100); // Blue
      }
      break;
    case 3:
      if (millis() - lastUpdate > 20) { // Non-blocking delay
        lastUpdate = millis();
        rainbowCycleUpdate(); // Update rainbow cycle
      }
      break;
    case 4:
      if (millis() - lastUpdate > 50) { // Non-blocking delay
        lastUpdate = millis();
        theaterChase(strip.Color(0, 50, 120), 150); 
      }
      break;
    case 5:
      if (millis() - lastUpdate > 50) { // Non-blocking delay
        lastUpdate = millis();
        colorWipe(strip.Color(255, 0, 0), 100); // Red
      }
      break;
  }
}

void setAllLEDs(uint8_t red, uint8_t green, uint8_t blue) {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(red, green, blue));
  }
  strip.show();
}

void rainbowCycleUpdate() {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
  }
  strip.show();
  j++;
  if (j >= 256 * 5) { // 5 cycles of all colors on wheel
    j = 0;
  }
}

void brightnessUpdate() {
  if (increasing) {
    brightness++;
    if (brightness >= 50) increasing = false;
  } else {
    brightness--;
    if (brightness <= 0) increasing = true;
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

void theaterChase(uint32_t color, int wait) {
  for (int j = 0; j < 10; j++) {  // Do 10 cycles of chasing
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, color);  // Turn every third pixel on
      }
      strip.show();
     
      delay(wait);
     
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      // Turn every third pixel off
      }
    }
  }
}

void colorWipe(uint32_t color, int wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color); // Set pixel's color
    strip.show(); // Update strip
    delay(wait); // Pause for a moment
  }
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0)); // Set pixel's color
    strip.show(); // Update strip
    delay(wait); // Pause for a moment
  }
}