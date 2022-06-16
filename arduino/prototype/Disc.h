struct Disc {
  uint8_t discIndex;
  uint16_t numLEDs;     // number of LEDs in this disc
  uint16_t maxRadius;   // TODO
  CRGB *leds;           // the LEDs for this disc
  uint8_t *brightness;  // the brightness of the LEDs for this disc

  int16_t radius(uint16_t pixelIndex) {
    return RADII[discIndex][pixelIndex % (numLEDs / NUM_SIDES)];
  }

  int16_t angle(uint16_t pixelIndex) { return ANGLES[discIndex][pixelIndex]; }

  void setBrighter(uint16_t pixelIndex, CRGB color, uint8_t colorBrightness) {
    if (colorBrightness > brightness[pixelIndex]) {
      leds[pixelIndex] = color;
      brightness[pixelIndex] = colorBrightness;
    }
  }

  void setBlend(uint16_t pixelIndex, CRGB color, uint8_t colorBrightness) {
    if (brightness[pixelIndex] == 0) {
      leds[pixelIndex] = color;
      brightness[pixelIndex] = colorBrightness;
    } else {
      leds[pixelIndex] = getColorBetween(color, leds[pixelIndex]);
      brightness[pixelIndex] = (brightness[pixelIndex] + colorBrightness) / 2;
    }
  }
};
