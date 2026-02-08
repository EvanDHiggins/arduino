#pragma once

#include <Arduino.h>
#include <Initializable.h>
#include <Timers.h>
#include <RTClib.h>
#include <Adafruit_LEDBackpack.h>

const unsigned long DEFAULT_FLASH_DURATION_MS = 750;

class SevenSegmentClock : Initializable {
public:
  SevenSegmentClock(
      const TimerSource& timer_source,
      unsigned long flash_on_duration = DEFAULT_FLASH_DURATION_MS,
      unsigned long flash_off_duration = DEFAULT_FLASH_DURATION_MS) :
    _flash_on_timer(timer_source.one_shot(flash_on_duration)),
    _flash_off_timer(timer_source.one_shot(flash_off_duration)) {}

  void init();
  void flash(bool b);
  void write_time(DateTime time);

private:
  Adafruit_7segment _display;
  bool _flash = false;
  unsigned long _last_flash_toggle;
  bool _displayOn = true;
  OneShotTimer _flash_off_timer;
  OneShotTimer _flash_on_timer;

  // Returns true if the display should show, otherwise false.
  bool flash_state();

  void hide_display();
};
