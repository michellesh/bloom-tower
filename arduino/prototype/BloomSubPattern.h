#define MAX_BLOOMS 2

class BloomSubPattern : public SubPattern {
 private:
  Bloom _blooms[MAX_BLOOMS];
  uint8_t _numBlooms = MAX_BLOOMS;
  uint8_t _activeSubPattern = 0;
  uint8_t _percentBrightness = 0;  // percent brightness of the whole pattern
  uint8_t _backgroundType = COLOR_ON_BLACK;
  uint8_t _numSeconds =
      NUM_SECONDS_DEFAULT;  // number of seconds to run this pattern

 public:
  static const uint8_t CONTINUOUS = 0;
  static const uint8_t START_SAME = 1;
  static const uint8_t END_SAME = 2;
  static const uint8_t UPWARD = 3;
  static const uint8_t DOWNWARD = 4;
  static const uint8_t EXPLODE_IN = 5;
  static const uint8_t EXPLODE_OUT = 6;

  BloomSubPattern(uint8_t activeSubPattern = 0,
                  uint8_t backgroundType = COLOR_ON_BLACK) {
    _activeSubPattern = activeSubPattern;
    _backgroundType = backgroundType;
    int16_t discOffset = 0;
    bool continuous = false;
    int16_t speed = Bloom::SPEED.DFLT;

    switch (_activeSubPattern) {
      case CONTINUOUS:
        _numBlooms = 1;
        continuous = true;
        break;
      case END_SAME:
        discOffset = -20;
        break;
      case UPWARD:
        discOffset = 20;
        break;
      case DOWNWARD:
        discOffset = -40;
        break;
      case EXPLODE_IN:
        _numBlooms = 1;
        discOffset = -20;
        break;
      case EXPLODE_OUT:
        _numBlooms = 1;
        discOffset = -20;
        speed = -speed;
        break;
      default:
        break;
    }

    if (_numBlooms > 0) {
      _blooms[0] = Bloom();
      _blooms[0].setRipples(discOffset, continuous);
      _blooms[0].setSpeed(speed);
    }
    if (_numBlooms > 1) {
      _blooms[1] = Bloom(1, Bloom::OFFSET.MAX / 2 + Bloom::WIDTH.DFLT / 2);
      _blooms[1].setRipples(discOffset, continuous);
      _blooms[0].setSpeed(speed);
    }
  }

  virtual uint8_t getNumSeconds() { return _numSeconds; }

  virtual uint8_t getPercentBrightness() { return _percentBrightness; }

  virtual void setPercentBrightness(uint8_t percentBrightness) {
    _percentBrightness = percentBrightness;
    for (uint8_t i = 0; i < _numBlooms; i++) {
      _blooms[i].setPercentBrightness(percentBrightness);
    }
  }

  virtual void show() {
    for (uint8_t i = 0; i < _numBlooms; i++) {
      _blooms[i].show(_backgroundType);
    }
  }
};
