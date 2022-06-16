class TwinkleSubPattern : public SubPattern {
 private:
  Twinkle _twinkle;
  uint8_t _activeSubPattern = 0;
  uint8_t _percentBrightness = 0;  // percent brightness of the whole pattern

 public:
  static const uint8_t ORIGINAL = 0;
  static const uint8_t EXPANDED_PIXEL = 1;

  TwinkleSubPattern(uint8_t activeSubPattern = 0) {
    _activeSubPattern = activeSubPattern;
  }

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
      default:
        _twinkle.show();
        break;
    }
  }
};
