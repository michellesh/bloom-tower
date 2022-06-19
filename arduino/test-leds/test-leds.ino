#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#include <Arduino.h>
#include <FastLED.h>

#define BRIGHTNESS 255
#define LED_TYPE WS2813
#define COLOR_ORDER GRB

#define NUM_LEVELS 7

#define PIN_1 2
#define PIN_2 4
#define PIN_3 5
#define PIN_4 12
#define PIN_5 13
#define PIN_6 14
#define PIN_7 18

int NUM_LEDS[] = {176, 388, 544, 700, 1052, 1404, 1728};
int NUM_LEDS_TOTAL = NUM_LEDS[0] + NUM_LEDS[1] + NUM_LEDS[2] + NUM_LEDS[3] +
                     NUM_LEDS[4] + NUM_LEDS[5] + NUM_LEDS[6];

CRGB colors[] = {CRGB::Purple, CRGB::Blue,   CRGB::Cyan, CRGB::Green,
                 CRGB::Yellow, CRGB::Orange, CRGB::Red};

struct Level {
  int levelIndex;
  int numLEDs;
  CRGB *leds;
};

CRGB *leds;
Level levels[NUM_LEVELS];

void setup() {
  Serial.begin(115200);
  delay(500);

  leds = new CRGB[NUM_LEDS_TOTAL];

  int startIndex = 0;
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

  int offset = 0;
  for (int i = 0; i < NUM_LEVELS; i++) {
    Level level = {i, NUM_LEDS[i], &leds[offset]};
    levels[i] = level;
    offset += level.numLEDs;
  }

  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  for (int i = 0; i < NUM_LEVELS; i++) {
    for (int j = 0; j < levels[i].numLEDs; j++) {
      levels[i].leds[j] = colors[i];
    }
  }
  FastLED.show();
}
