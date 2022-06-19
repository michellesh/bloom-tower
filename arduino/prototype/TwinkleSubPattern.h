class TwinkleSubPattern : public SubPattern {
 private:
  Twinkle _twinkle;
  uint8_t _activeSubPattern = 0;
  uint8_t _percentBrightness = 0;  // percent brightness of the whole pattern
  uint8_t _numSeconds =
      NUM_SECONDS_DEFAULT;  // number of seconds to run this pattern

  void _showCorners() {
    _twinkle.show();

    // Override a background everywhere except the corners 5%
    for (uint8_t d = 0; d < NUM_DISCS; d++) {
      for (uint16_t p = 0; p < discs[d].numLEDs; p++) {
        if (discs[d].percentCorner(p) > 5) {
          // Background color from color scheme:
          CRGB color = palette.getColor(d).nscale8(
              BACKGROUND_BRIGHTNESS * getPercentBrightness() / 100);
          discs[d].setBlend(p, color, BACKGROUND_BRIGHTNESS);

          // If no background:
          // discs[d].setBlend(p, CRGB::Black, 0);
        }
      }
    }
  }

 public:
  static const uint8_t ORIGINAL = 0;
  static const uint8_t EXPANDED_PIXEL = 1;
  static const uint8_t CORNERS = 2;

  TwinkleSubPattern(uint8_t activeSubPattern = 0) {
    _activeSubPattern = activeSubPattern;
  }

  virtual uint8_t getNumSeconds() { return _numSeconds; }

  virtual uint8_t getPercentBrightness() { return _percentBrightness; }

  virtual void setPercentBrightness(uint8_t percentBrightness) {
    _percentBrightness = percentBrightness;
    _twinkle.setPercentBrightness(percentBrightness);
  }

  virtual void show() {
    switch (_activeSubPattern) {
      case EXPANDED_PIXEL:
        _twinkle.showExpandedPixel();
        break;
      case CORNERS:
        _showCorners();
        break;
      default:
        _twinkle.show();
        break;
    }
  }
};
