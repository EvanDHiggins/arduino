#include <Arduino.h>
#include <Initializable.h>
#include <Timers.h>
#include <RTClib.h>
#include <Adafruit_LEDBackpack.h>

const unsigned long DEFAULT_FLASH_DURATION_MS = 750;

class SevenSegmentClock : Initializable {
public:
  SevenSegmentClock(const TimerSource& timer_source) : _flash_timer(timer_source.one_shot(DEFAULT_FLASH_DURATION_MS)) {}

  void init();
  void flash(bool b);
  void write_time(DateTime time);

private:
  Adafruit_7segment _display;
  bool _flash = false;
  unsigned long _last_flash_toggle;
  bool _displayOn = true;
  OneShotTimer _flash_timer;



  // Returns true if the display should show, otherwise false.
  bool flash_state();

  void hide_display();
};
