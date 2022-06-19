#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#include <Arduino.h>
#include <FastLED.h>

#include "globals.h"
#include "colors.h"
#include "utils.h"
#include "fade.h"
#include "Disc.h"

Disc discs[NUM_DISCS];
CRGB *leds;
uint8_t *ledBrightness;

#include "Palette.h"
Palette palette;

#include "Range.h"
#include "Timer.h"
#include "Pattern.h"
#include "Bloom.h"
#include "Spiral.h"
#include "Twinkle.h"

#include "SubPattern.h"
#include "BloomSubPattern.h"
#include "SpiralSubPattern.h"
#include "TwinkleSubPattern.h"
#include "StaticSubPattern.h"

StaticSubPattern staticBlack(StaticSubPattern::BLACK);
StaticSubPattern staticColor(StaticSubPattern::COLOR);

TwinkleSubPattern twinkle(TwinkleSubPattern::ORIGINAL);
TwinkleSubPattern twinkleExpandedPixel(TwinkleSubPattern::EXPANDED_PIXEL);
TwinkleSubPattern twinkleCorners(TwinkleSubPattern::CORNERS);

BloomSubPattern bloomContinuous(BloomSubPattern::CONTINUOUS);
BloomSubPattern bloomStartSame(BloomSubPattern::START_SAME);
BloomSubPattern bloomEndSame(BloomSubPattern::END_SAME);
BloomSubPattern bloomUpward(BloomSubPattern::UPWARD);
BloomSubPattern bloomDownward(BloomSubPattern::DOWNWARD);
BloomSubPattern bloomExplodeIn(BloomSubPattern::EXPLODE_IN);
BloomSubPattern bloomExplodeOut(BloomSubPattern::EXPLODE_OUT);

SpiralSubPattern rubberBandWorm(SpiralSubPattern::RUBBER_BAND_WORM);
SpiralSubPattern rubberBandNoAnchor(SpiralSubPattern::RUBBER_BAND_NO_ANCHOR);
SpiralSubPattern rubberBandAnchored(SpiralSubPattern::RUBBER_BAND_ANCHORED);
SpiralSubPattern growingSpirals(SpiralSubPattern::GROWING_SPIRALS);
SpiralSubPattern basicSpiralRotation(SpiralSubPattern::BASIC_SPIRAL_ROTATION);
SpiralSubPattern continuousSpiral(SpiralSubPattern::CONTINUOUS_SPIRAL);
SpiralSubPattern cornerChase(SpiralSubPattern::CORNER_CHASE, WHITE_ON_COLOR);
SpiralSubPattern cornerChaseReverse(SpiralSubPattern::CORNER_CHASE_REVERSE,
                                    WHITE_ON_COLOR);

Timer patternTimer = {seconds(NUM_SECONDS_DEFAULT), 0};

// clang-format off
SubPattern *activePatterns[] = {
  // Added for Bloom Tower
  //&twinkleExpandedPixel, // same as twinkle but expand a 'pixel' to be 1 ft segments
  //&twinkleCorners, // twinkle in corner 5%, everywhere else is a background color
  //&cornerChase, // light up corner (5%) and shoot upwards
  //&cornerChaseReverse, // light up corner (5%) and shoot upwards

  // Same from OG Bloom
  &twinkle, // set with lower density than OG Bloom
  //&bloomContinuous,
  //&bloomStartSame,
  //&bloomEndSame,
  //&bloomUpward,
  //&bloomDownward,
  //&rubberBandWorm,
  //&rubberBandNoAnchor,
  //&rubberBandAnchored,
  //&growingSpirals,
  //&basicSpiralRotation,
  //&continuousSpiral
};
// clang-format on

SubPattern *sourcePattern;
SubPattern *targetPattern;
uint8_t numPatterns = sizeof(activePatterns) / sizeof(activePatterns[0]);

void logMemory() {
  Serial.print("Used PSRAM: ");
  Serial.println(ESP.getPsramSize() - ESP.getFreePsram());
}

void setup() {
  Serial.begin(115200);
  delay(500);

  leds = (CRGB *)ps_malloc(sizeof(CRGB) * NUM_LEDS_TOTAL);
  ledBrightness = (uint8_t *)ps_malloc(sizeof(uint8_t) * NUM_LEDS_TOTAL);
  logMemory();

  uint16_t startIndex = 0;
  // TODO This assumes PIN_1 is the top/smallest level (disc)
  // If PIN_1 is the bottom/largest level (disc), reverse the pin order here:
  FastLED.addLeds<LED_TYPE, PIN_1, COLOR_ORDER>(leds, startIndex, NUM_LEDS[0])
      .setCorrection(TypicalLEDStrip)
      .setDither(BRIGHTNESS < 255);
  startIndex += NUM_LEDS[0];
  FastLED.addLeds<LED_TYPE, PIN_2, COLOR_ORDER>(leds, startIndex, NUM_LEDS[1])
      .setCorrection(TypicalLEDStrip)
      .setDither(BRIGHTNESS < 255);
  startIndex += NUM_LEDS[1];
  FastLED.addLeds<LED_TYPE, PIN_3, COLOR_ORDER>(leds, startIndex, NUM_LEDS[2])
      .setCorrection(TypicalLEDStrip)
      .setDither(BRIGHTNESS < 255);
  startIndex += NUM_LEDS[2];
  FastLED.addLeds<LED_TYPE, PIN_4, COLOR_ORDER>(leds, startIndex, NUM_LEDS[3])
      .setCorrection(TypicalLEDStrip)
      .setDither(BRIGHTNESS < 255);
  startIndex += NUM_LEDS[3];
  FastLED.addLeds<LED_TYPE, PIN_5, COLOR_ORDER>(leds, startIndex, NUM_LEDS[4])
      .setCorrection(TypicalLEDStrip)
      .setDither(BRIGHTNESS < 255);
  startIndex += NUM_LEDS[4];
  FastLED.addLeds<LED_TYPE, PIN_6, COLOR_ORDER>(leds, startIndex, NUM_LEDS[5])
      .setCorrection(TypicalLEDStrip)
      .setDither(BRIGHTNESS < 255);
  startIndex += NUM_LEDS[5];
  FastLED.addLeds<LED_TYPE, PIN_7, COLOR_ORDER>(leds, startIndex, NUM_LEDS[6])
      .setCorrection(TypicalLEDStrip)
      .setDither(BRIGHTNESS < 255);

  uint16_t offset = 0;
  for (uint8_t d = 0; d < NUM_DISCS; d++) {
    Disc disc = {d, NUM_LEDS[d], MAX_RADIUS_DISC[d], &leds[offset],
                 &ledBrightness[offset]};

    discs[d] = disc;
    offset += disc.numLEDs;
  }

  // Initialize all LEDs to black
  for (int16_t i = 0; i < NUM_LEDS_TOTAL; i++) {
    leds[i] = CRGB::Red;
  }

  FastLED.setBrightness(100);

  // Set first pattern in activePatterns to be played first
  sourcePattern = (SubPattern *)activePatterns[numPatterns - 1];
  sourcePattern->setPercentBrightness(0);
  targetPattern = (SubPattern *)activePatterns[0];
  targetPattern->setPercentBrightness(100);
  patternTimer.totalCycleTime = seconds(targetPattern->getNumSeconds());
}

void loop() {
  clearLEDs();
  palette.cycle();

  if (patternTimer.complete()) {
    // Increment active pattern
    sourcePattern = (SubPattern *)targetPattern;
    static uint8_t nextPattern = 0;
    nextPattern = (nextPattern + 1) % numPatterns;
    targetPattern = (SubPattern *)(activePatterns[nextPattern]);

    // Reset the timer to how long new targetPattern runs for
    patternTimer.totalCycleTime = seconds(targetPattern->getNumSeconds());
    patternTimer.reset();
  }

  EVERY_N_MILLISECONDS(100) {
    shiftPercentBrightnessTo(targetPattern, 100);
    shiftPercentBrightnessTo(sourcePattern, 0);
  }

  for (uint8_t i = 0; i < numPatterns; i++) {
    if (activePatterns[i]->getPercentBrightness() > 0) {
      activePatterns[i]->show();
    }
  }

  // demoColorModes();

  FastLED.show();
  ticks++;
}

void shiftPercentBrightnessTo(SubPattern *pattern,
                              uint8_t toPercentBrightness) {
  if (pattern->getPercentBrightness() == toPercentBrightness) {
    return;
  } else if (pattern->getPercentBrightness() < toPercentBrightness) {
    pattern->setPercentBrightness(
        min(pattern->getPercentBrightness() + 3, 100));
  } else if (pattern->getPercentBrightness() > toPercentBrightness) {
    pattern->setPercentBrightness(max(pattern->getPercentBrightness() - 3, 0));
  }
}

void clearLEDs() {
  for (uint16_t i = 0; i < NUM_LEDS_TOTAL; i++) {
    ledBrightness[i] = 0;
    leds[i].nscale8(0);
  }
}

void plotVars(int numValues, ...) {
  va_list values;
  va_start(values, numValues);
  for (int i = 0; i < numValues; i++) {
    Serial.print(va_arg(values, int));
    Serial.print(" ");
  }
  va_end(values);
  Serial.println();
}

void demoColorModes() {
  // Cycle through color modes for demonstration
  EVERY_N_SECONDS(10) {
    palette.setColorMode((palette.getActiveColorMode() + 1) % 6);
    Serial.println(palette.getActiveColorMode());
  }
  FastLED.setBrightness(50);
  for (uint8_t d = 0; d < NUM_DISCS; d++) {
    for (uint16_t p = 0; p < discs[d].numLEDs; p++) {
      discs[d].leds[p] = palette.getColor(d, p, true);
    }
  }
}
