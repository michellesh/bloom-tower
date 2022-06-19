class StaticSubPattern : public SubPattern {
 private:
  uint8_t _activeSubPattern = 0;
  uint8_t _percentBrightness = 0;  // percent brightness of the whole pattern
  uint8_t _numSeconds =
      NUM_SECONDS_TRANSITION;  // number of seconds to run this pattern

  void _showBlack() {
    for (uint8_t d = 0; d < NUM_DISCS; d++) {
      for (uint16_t p = 0; p < discs[d].numLEDs; p++) {
        discs[d].setBlend(p, CRGB::Black, 0);
      }
    }
  }

  void _showColor() {
    for (uint8_t d = 0; d < NUM_DISCS; d++) {
      for (uint16_t p = 0; p < discs[d].numLEDs; p++) {
        CRGB color = palette.getColor(d, p).nscale8(BRIGHTNESS *
                                                    _percentBrightness / 100);
        discs[d].setBlend(p, color, BRIGHTNESS);
      }
    }
  }

 public:
  static const uint8_t BLACK = 0;
  static const uint8_t COLOR = 1;

  StaticSubPattern(uint8_t activeSubPattern = 0) {
    _activeSubPattern = activeSubPattern;
  }

  virtual uint8_t getNumSeconds() { return _numSeconds; }

  virtual uint8_t getPercentBrightness() { return _percentBrightness; }

  virtual void setPercentBrightness(uint8_t percentBrightness) {
    _percentBrightness = percentBrightness;
  }

  virtual void show() {
    switch (_activeSubPattern) {
      case COLOR:
        _showColor();
        break;
      default:
        _showBlack();
        break;
    }
  }
};
