#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#include <Arduino.h>
#include <FastLED.h>

#include "globals.h"
#include "colors.h"
#include "utils.h"
#include "Disc.h"

Disc discs[NUM_DISCS];
CRGB *leds;

#include "Palette.h"
Palette palette;

#include "Range.h"
#include "Bloom.h"
#include "Spin.h"
#include "Twinkle.h"

Bloom bloom;
Spin spin;
Twinkle twinkle;

void setup() {
  Serial.begin(115200);
  delay(500);

  leds = new CRGB[NUM_LEDS_TOTAL];

  uint16_t startIndex = 0;
  FastLED.addLeds<NEOPIXEL, PIN_1>(leds, startIndex, NUM_LEDS_PIN_1);
  startIndex += NUM_LEDS_PIN_1;
  FastLED.addLeds<NEOPIXEL, PIN_2>(leds, startIndex, NUM_LEDS_PIN_2);
  startIndex += NUM_LEDS_PIN_2;
  FastLED.addLeds<NEOPIXEL, PIN_3>(leds, startIndex, NUM_LEDS_PIN_3);
  startIndex += NUM_LEDS_PIN_3;
  FastLED.addLeds<NEOPIXEL, PIN_4>(leds, startIndex, NUM_LEDS_PIN_4);
  startIndex += NUM_LEDS_PIN_4;
  FastLED.addLeds<NEOPIXEL, PIN_5>(leds, startIndex, NUM_LEDS_PIN_5);
  startIndex += NUM_LEDS_PIN_5;
  FastLED.addLeds<NEOPIXEL, PIN_6>(leds, startIndex, NUM_LEDS_PIN_6);
  startIndex += NUM_LEDS_PIN_6;
  FastLED.addLeds<NEOPIXEL, PIN_7>(leds, startIndex, NUM_LEDS_PIN_7);

  uint16_t offset = 0;
  for (uint8_t d = 0; d < NUM_DISCS; d++) {
    Disc disc = {d,
                 NUM_LEDS_DISC[d],
                 NUM_LEDS_PETAL[d][0],
                 NUM_LEDS_PETAL[d][1],
                 NUM_LEDS_PETAL[d][2],
                 offset,
                 &leds[offset],
                 MAX_RADIUS_DISC[d]};

    discs[d] = disc;
    offset += disc.numLEDs;
  }

  // Initialize all LEDs to black
  for (int16_t i = 0; i < NUM_LEDS_TOTAL; i++) {
    leds[i] = CRGB::Black;
  }

  bloom = bloom.initContinuous();
}

int bloomType = 0;

void loop() {
  palette = palette.cycle();

  // cyclePalettes();
  // showPalette();
  // cycleBloomTypes();

  bloom = bloom.show();

  EVERY_N_MILLISECONDS(1500) { bloom = bloom.reverse(); }

  // twinkle = twinkle.show();

  // spin = spin.width(spin.WIDTH.DFLT)
  //            .speed(5)
  //            .offset(spin.OFFSET.DFLT)
  //            .show();

  ticks++;
}

void cycleBloomTypes() {
  EVERY_N_SECONDS(10) {
    bloomType++;
    if (bloomType >= 5) {
      bloomType = 0;
    }
    if (bloomType == 0) {
      bloom = bloom.initStartSame();
    } else if (bloomType == 1) {
      bloom = bloom.initUpward();
    } else if (bloomType == 2) {
      bloom = bloom.initDownward();
    } else if (bloomType == 3) {
      bloom = bloom.initEndSame();
    } else {
      bloom = bloom.initContinuous();
    }
  }

  bloom = bloom.show();
}

void cyclePalettes() {
  // Cycle through color modes for demonstration
  EVERY_N_SECONDS(15) {
    palette.colorMode = palette.colorMode < 4 ? palette.colorMode + 1 : 0;
  }

  showPalette();
}

void showPalette() {
  FastLED.setBrightness(50);
  for (uint8_t d = 0; d < NUM_DISCS; d++) {
    for (uint8_t p = 0; p < discs[d].numLEDs; p++) {
      discs[d].leds[p] = palette.getColor(d, p, true);
      // discs[d].leds[p] = campfire[d];
    }
  }
  FastLED.show();
}
