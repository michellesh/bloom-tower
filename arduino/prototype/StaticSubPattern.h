class StaticSubPattern : public SubPattern {
 private:
  uint8_t _activeSubPattern = 0;
  uint8_t _percentBrightness = 0;  // percent brightness of the whole pattern
  uint8_t _backgroundType = COLOR_ON_BLACK;
  uint8_t _numSeconds =
      NUM_SECONDS_DEFAULT;  // number of seconds to run this pattern
  uint8_t _offsets[NUM_DISCS] = {0, 0, 0, 0, 0, 0, 0};

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
        // discs[d].leds[p] = chakra[d];
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

  void _showLines(bool moving = false) {
    for (uint8_t d = 0; d < NUM_DISCS; d++) {
      for (uint16_t p = 0; p < discs[d].numLEDs; p++) {
        if ((p + _offsets[d]) % SEGMENT_LENGTH == 0) {
          if (_backgroundType == COLOR_ON_BLACK) {
            CRGB color = palette.getColor(d, p).nscale8(
                BRIGHTNESS * _percentBrightness / 100);
            discs[d].setBlend(p, color, BRIGHTNESS);
          } else if (_backgroundType == WHITE_ON_COLOR) {
            CRGB white = CRGB::White;
            CRGB color =
                white.nscale8(BRIGHTNESS * getPercentBrightness() / 100);
            discs[d].setBlend(p, color, BRIGHTNESS);
          } else {
            CRGB color = palette.getColor(d).nscale8(
                BRIGHTNESS * getPercentBrightness() / 100);
            discs[d].setBlend(p, color, BRIGHTNESS);
          }
        } else {
          discs[d].setBlend(p, CRGB::Black, 0);
        }
      }
      if (moving) {
        _offsets[d]++;
        if (_offsets[d] > discs[d].numLEDs) {
          _offsets[d] = 0;
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
  static const uint8_t LINES_MOVING = 5;

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
    /*
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
    */
    switch (_activeSubPattern) {
      case CHAKRA:
        _showChakra();
        break;
      case COLOR:
        _showColor();
        break;
      case LINES:
        _showLines(false);
      case LINES_MOVING:
        _showLines(true);
      case TRIANGLE:
        //_showTriangle();
      default:
        _numSeconds = SEC_10;
        _showBlack();
        break;
    }
  }
};
