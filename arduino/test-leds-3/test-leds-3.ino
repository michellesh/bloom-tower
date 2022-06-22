#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#include <Arduino.h>
#include <FastLED.h>

#define BRIGHTNESS 255
#define LED_TYPE WS2813
#define COLOR_ORDER GRB

#define PIN_1 2
#define PIN_2 4
#define PIN_3 5
#define PIN_4 12
#define PIN_5 13
#define PIN_6 14
#define PIN_7 18

#define NUM_LEDS_1 176
#define NUM_LEDS_2 388
#define NUM_LEDS_3 544
#define NUM_LEDS_4 700
#define NUM_LEDS_5 1052
#define NUM_LEDS_6 1404
#define NUM_LEDS_7 1728

CRGB leds[NUM_LEDS_1];
CRGB leds2[NUM_LEDS_2];
CRGB leds3[NUM_LEDS_3];
CRGB leds4[NUM_LEDS_4];
CRGB leds5[NUM_LEDS_5];
CRGB leds6[NUM_LEDS_6];
CRGB leds7[NUM_LEDS_7];

void setup() {
  Serial.begin(115200);
  delay(500);

  FastLED.addLeds<LED_TYPE, PIN_1, COLOR_ORDER>(leds, NUM_LEDS_1)
      .setCorrection(TypicalLEDStrip)
      .setDither(BRIGHTNESS < 255);
  FastLED.addLeds<LED_TYPE, PIN_2, COLOR_ORDER>(leds2, NUM_LEDS_2)
      .setCorrection(TypicalLEDStrip)
      .setDither(BRIGHTNESS < 255);
  FastLED.addLeds<LED_TYPE, PIN_3, COLOR_ORDER>(leds3, NUM_LEDS_3)
      .setCorrection(TypicalLEDStrip)
      .setDither(BRIGHTNESS < 255);
  FastLED.addLeds<LED_TYPE, PIN_4, COLOR_ORDER>(leds4, NUM_LEDS_4)
      .setCorrection(TypicalLEDStrip)
      .setDither(BRIGHTNESS < 255);
  FastLED.addLeds<LED_TYPE, PIN_5, COLOR_ORDER>(leds5, NUM_LEDS_5)
      .setCorrection(TypicalLEDStrip)
      .setDither(BRIGHTNESS < 255);
  FastLED.addLeds<LED_TYPE, PIN_6, COLOR_ORDER>(leds6, NUM_LEDS_6)
      .setCorrection(TypicalLEDStrip)
      .setDither(BRIGHTNESS < 255);
  FastLED.addLeds<LED_TYPE, PIN_7, COLOR_ORDER>(leds7, NUM_LEDS_7)
      .setCorrection(TypicalLEDStrip)
      .setDither(BRIGHTNESS < 255);

  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  for (int i = 0; i < NUM_LEDS_1; i++) {
    leds[i] = CRGB::Blue;
  }
  for (int i = 0; i < NUM_LEDS_2; i++) {
    leds2[i] = CRGB::Green;
  }
  for (int i = 0; i < NUM_LEDS_3; i++) {
    leds3[i] = CRGB::Blue;
  }
  for (int i = 0; i < NUM_LEDS_4; i++) {
    leds4[i] = CRGB::Green;
  }
  for (int i = 0; i < NUM_LEDS_5; i++) {
    leds5[i] = CRGB::Blue;
  }
  for (int i = 0; i < NUM_LEDS_6; i++) {
    leds6[i] = CRGB::Green;
  }
  for (int i = 0; i < NUM_LEDS_7; i++) {
    leds7[i] = CRGB::Blue;
  }
  FastLED.show();
}
