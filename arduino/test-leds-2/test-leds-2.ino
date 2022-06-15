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

#define NUM_LEDS 144

CRGB leds[NUM_LEDS];
CRGB leds2[NUM_LEDS];

void setup() {
  Serial.begin(115200);
  delay(500);

  FastLED.addLeds<LED_TYPE, PIN_1, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.addLeds<LED_TYPE, PIN_2, COLOR_ORDER>(leds2, NUM_LEDS);

  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Blue;
  }
  for (int i = 0; i < NUM_LEDS; i++) {
    leds2[i] = CRGB::Red;
  }
  FastLED.show();
}
