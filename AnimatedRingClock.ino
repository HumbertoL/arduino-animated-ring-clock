#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// Data pin on ring
#define PIN 5
#define NUM_PIXELS 60

// Demo at different speeds
// 1.0 = normal speed
// 0.5 = double speedS
#define ANIMATION_SCALE 0.5


// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);


// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  // pinMode(13, OUTPUT);
  // digitalWrite(13, HIGH);
  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  clock();
  resetPixels();
}

void clock() {
  // Set to blue
  uint32_t  color = strip.Color(0, 0, 32);
  uint32_t  off = strip.Color(0, 0, 0);
  int numPixels =  strip.numPixels();
  // int numTicks = 60; // 60 Seconds in a minute

  // Used to correct for rings that aren't 60 pixels. 60/numPixels
  float scale = 60 / NUM_PIXELS; //60 / 24 = 2.5;
  for (uint16_t i = 0; i < numPixels; i++) {
    // The delay needs to increase as the loop progresses
    int msDelay = (1000 / (numPixels - i)) * scale * ANIMATION_SCALE;
    for (uint16_t j = 0; j < numPixels; j++) {
      if ( j < numPixels - i) {
        if (j > 0) {
          // Turn off previous pixel
          strip.setPixelColor( numPixels - j, off);
        }
        strip.setPixelColor( numPixels - j - 1, color);

        strip.show();
        delay(msDelay);
      }
      else {
        break;
      }
    }
  }
}

void resetPixels() {
  uint32_t  off = strip.Color(0, 0, 0);
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, off);
  }
  strip.show();
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}
