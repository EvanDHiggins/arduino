#include <SevenSegmentClock.h>

uint8_t digit(uint8_t num, int radix, int base = 10) {
  while (radix > 0) {
    num = num / base;
    radix--;
  }
  return num % base;
}

void SevenSegmentClock::init() {
  _display.begin(0x70);
  _display.setBrightness(10);
}

void SevenSegmentClock::flash(bool b) {
  if (false) {
    _displayOn = true;
  }
  _flash = b;
}

void SevenSegmentClock::write_time(DateTime time) {
  bool showDisplay = flash_state();
  if (!showDisplay) {
    hide_display();
  } else {
    uint8_t hour = time.hour();
    uint8_t minute = time.minute();
    _display.writeDigitNum(0, hour >= 10 ? digit(hour, 1) : 0);

    _display.writeDigitNum(1, digit(hour, 0));

    _display.writeDigitNum(3, minute >= 10 ? digit(minute, 1) : 0);

    _display.writeDigitNum(4, digit(minute, 0));
    _display.drawColon(true);

    _display.writeDisplay();
  }
}

// Returns true if the display should show, otherwise false.
bool SevenSegmentClock::flash_state() {
  if (!_flash) return true;
  if (_displayOn && _flash_on_timer.triggered()) {
    _flash_off_timer.reset();
    _displayOn = !_displayOn;
  } else if(!_displayOn && _flash_off_timer.triggered()) {
    _flash_on_timer.reset();
    _displayOn = !_displayOn;
  }
  return _displayOn;
}

void SevenSegmentClock::hide_display() {
  _display.clear();
  _display.drawColon(true);
  _display.writeDisplay();
}
