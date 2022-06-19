class Spiral : public Pattern {
 private:
  uint8_t _id = 0;
  int16_t _angle = 0;  // the current angle
  int16_t _width = WIDTH.DFLT;
  int16_t _speed = SPEED.DFLT;
  int16_t _discOffset[NUM_DISCS] = {0, 0, 0, 0, 0, 0, 0};
  uint8_t _minRadius[NUM_DISCS] = {0, 0, 0, 0, 0, 0, 0};
  uint8_t _maxRadius[NUM_DISCS] = {100, 100, 100, 100, 100, 100, 100};
  uint8_t _heightBrightness[NUM_DISCS] = {255, 255, 255, 255, 255, 255, 255};

  // Gets the brightness of the LED if the LED's angle is close to the current
  // angle
  uint8_t _getBrightness(uint8_t d, uint16_t p) {
    if (!isBetween(discs[d].radius(p), _minRadius[d], _maxRadius[d])) {
      return 0;
    }

    int16_t targetAngle = (_angle + _discOffset[d] + 360) % 360;
    int16_t pixelAngle = discs[d].angle(p);

    // Calculate distance from the current angle. If angle is near end
    // (360-width < a < 360), also check LEDs near beginning. If angle is near
    // beginning (0 < a < width), also check LEDs near end
    int16_t dist = isBetween(targetAngle - pixelAngle, 0, _width)
                       ? targetAngle - pixelAngle
                   : targetAngle > 360 - _width &&
                           isBetween(targetAngle - 360 - pixelAngle, 0, _width)
                       ? targetAngle - 360 - pixelAngle
                   : targetAngle < _width &&
                           isBetween(targetAngle + 360 - pixelAngle, 0, _width)
                       ? targetAngle + 360 - pixelAngle
                       : 0;

    uint8_t brightness = addFadeShape(map(dist, 0, _width, 0, 255));
    return min(brightness, _heightBrightness[d]);
  };

 public:
  Spiral(uint8_t id = 0) { _id = id; }

  static constexpr Range WIDTH = {
      10, 90, 90};  // How many degrees along the circumference at
                    // the current angle to light up
  static constexpr Range SPEED = {1, 10, 3};  // How many degrees to add to the
                                              // current angle each time
  static constexpr Range DISC_OFFSET = {
      20, 90, 30};  // How many degrees to increase angle per
                    // disc higher = tighter spiral

  void setWidth(int16_t width) { _width = abs(width); }

  void setSpeed(int16_t speed) { _speed = speed; }

  void setAngle(int16_t angle) { _angle = angle; }

  void setDiscOffset(uint8_t i, int16_t angle) { _discOffset[i] = angle; }

  void reverse() { _speed = _speed * -1; }

  void setRadiusRangePercent(uint8_t min, uint8_t max) {
    for (uint8_t d = 0; d < NUM_DISCS; d++) {
      _minRadius[d] = map(min, 0, 100, 0, MAX_RADIUS_DISC[d]);
      _maxRadius[d] = map(max, 0, 100, 0, MAX_RADIUS_DISC[d]);
    }
  }

  void setHeightRangePercent(uint8_t min, uint8_t max) {
    uint8_t fade = 50;  // how much percent of full height to add fade
    for (uint8_t d = 0; d < NUM_DISCS; d++) {
      if (min == 0 && max == 100) {
        _heightBrightness[d] = 255;
      }

      uint8_t height = PERCENT_HEIGHT_DISC[d];
      _heightBrightness[d] =
          isBetweenI(height, min, min + fade)
              ? map(height, min, min + fade, 0, 255)
          : isBetweenI(height, max - fade, max)
              ? map(height, max - fade, max, 255, 0)
          : min < max ? (isBetweenI(height, min + fade, max - fade) ? 255 : 0)
                      : (isBetweenI(height, max, min) ? 0 : 255);
    }
  }

  void show(uint8_t backgroundType = COLOR_ON_BLACK) {
    if (backgroundType == COLOR_ON_BLACK) {
      showColor();
    } else if (backgroundType == WHITE_ON_COLOR) {
      showWhite();
    } else {
      showBright();
    }
  }

  void showColor() {
    for (uint8_t d = 0; d < NUM_DISCS; d++) {
      for (uint16_t p = 0; p < discs[d].numLEDs; p++) {
        uint8_t brightness = _getBrightness(d, p);
        if (brightness > 0) {
          CRGB color = palette.getColor(_id * 2).nscale8(
              brightness * getPercentBrightness() / 100);
          discs[d].setBlend(p, color, brightness);
        }
      }
    }

    // Increment the angle. After 360 degrees, start over at 0 degrees
    _angle = (_angle + _speed + 360) % 360;
  }

  void showWhite() {
    CRGB white = CRGB::White;
    for (uint8_t d = 0; d < NUM_DISCS; d++) {
      for (uint16_t p = 0; p < discs[d].numLEDs; p++) {
        uint8_t brightness = _getBrightness(d, p);
        if (brightness > 0) {
          brightness = map(brightness, 0, 255, BACKGROUND_BRIGHTNESS, 255);
          CRGB color = white.nscale8(brightness * getPercentBrightness() / 100);
          discs[d].setBlend(p, color, brightness);
        }
      }
    }

    // Increment the angle. After 360 degrees, start over at 0 degrees
    _angle = (_angle + _speed + 360) % 360;
  }

  void showBright() {
    for (uint8_t d = 0; d < NUM_DISCS; d++) {
      for (uint16_t p = 0; p < discs[d].numLEDs; p++) {
        uint8_t brightness = _getBrightness(d, p);
        if (brightness > BACKGROUND_BRIGHTNESS) {
          CRGB color = palette.getColor(d).nscale8(
              brightness * getPercentBrightness() / 100);
          discs[d].setBlend(p, color, brightness);
        }
      }
    }

    // Increment the angle. After 360 degrees, start over at 0 degrees
    _angle = (_angle + _speed + 360) % 360;
  }
};
