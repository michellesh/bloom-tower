class StaticSubPattern : public SubPattern {
 private:
  uint8_t _activeSubPattern = 0;
  uint8_t _percentBrightness = 0;  // percent brightness of the whole pattern
  uint8_t _backgroundType = COLOR_ON_BLACK;
  uint8_t _numSeconds =
      NUM_SECONDS_TRANSITION;  // number of seconds to run this pattern

  void _showBlack() {
    for (uint8_t d = 0; d < NUM_DISCS; d++) {
      for (uint16_t p = 0; p < discs[d].numLEDs; p++) {
        discs[d].setBlend(p, CRGB::Black, 0);
      }
    }
  }

  void _showChakra() {
    for (uint8_t d = 0; d < NUM_DISCS; d++) {
      for (uint16_t p = 0; p < discs[d].numLEDs; p++) {
        discs[d].setBlend(p, chakra[d], BRIGHTNESS);
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

  void _showLines() {
    for (uint8_t d = 0; d < NUM_DISCS; d++) {
      for (uint16_t p = 0; p < discs[d].numLEDs; p += SEGMENT_LENGTH) {
        if (_backgroundType == COLOR_ON_BLACK) {
          CRGB color = palette.getColor(d, p).nscale8(BRIGHTNESS *
                                                      _percentBrightness / 100);
          discs[d].setBlend(p, color, BRIGHTNESS);
        } else if (_backgroundType == WHITE_ON_COLOR) {
          CRGB white = CRGB::White;
          CRGB color = white.nscale8(BRIGHTNESS * getPercentBrightness() / 100);
          discs[d].setBlend(p, color, BRIGHTNESS);
        } else {
          CRGB color = palette.getColor(d).nscale8(
              BRIGHTNESS * getPercentBrightness() / 100);
          discs[d].setBlend(p, color, BRIGHTNESS);
        }
      }
    }
  }

 public:
  static const uint8_t BLACK = 0;
  static const uint8_t COLOR = 1;
  static const uint8_t LINES = 2;
  static const uint8_t TRIANGLE = 3;
  static const uint8_t CHAKRA = 4;

  StaticSubPattern(uint8_t activeSubPattern = 0,
                   uint8_t backgroundType = COLOR_ON_BLACK) {
    _activeSubPattern = activeSubPattern;
    _backgroundType = backgroundType;
  }

  virtual uint8_t getNumSeconds() { return _numSeconds; }

  virtual uint8_t getPercentBrightness() { return _percentBrightness; }

  virtual void setPercentBrightness(uint8_t percentBrightness) {
    _percentBrightness = percentBrightness;
  }

  virtual void show() {
    if (_backgroundType == WHITE_ON_COLOR ||
        _backgroundType == BRIGHT_ON_COLOR) {
      // Set background
      for (uint8_t d = 0; d < NUM_DISCS; d++) {
        for (uint16_t p = 0; p < discs[d].numLEDs; p++) {
          CRGB color = palette.getColor(d).nscale8(
              BACKGROUND_BRIGHTNESS * getPercentBrightness() / 100);
          discs[d].setBlend(p, color, BACKGROUND_BRIGHTNESS);
        }
      }
    }
    switch (_activeSubPattern) {
      case CHAKRA:
        _showChakra();
        break;
      case COLOR:
        _showColor();
        break;
      case LINES:
        _numSeconds = NUM_SECONDS_DEFAULT;
        _showLines();
      case TRIANGLE:
        _numSeconds = NUM_SECONDS_DEFAULT;
        //_showTriangle();
      default:
        _showBlack();
        break;
    }
  }
};
