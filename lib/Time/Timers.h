#pragma once

#include <Arduino.h>

class OneShotTimer;

class TimerSource {
public:
  void update();

  OneShotTimer one_shot(unsigned long time_ms, bool start_disabled = false) const;

  unsigned long current_millis() const {
    return _millis;
  }

private:
  unsigned long _millis = millis();
};

/**
 * Timer class that counts down from a start time and emits a signal exactly once.
 * 
 * The timer isn't completed until OneShotTimer::triggered has been called once
 * after the duration has elapsed.
 */
class OneShotTimer {
public:
  OneShotTimer(
      const TimerSource& source, 
      unsigned long duration_ms,
      bool start_disabled = false
  );

  bool triggered();

  bool active() const;

  void reset();

private:
  const TimerSource& _source;
  const unsigned long _duration_ms;

  unsigned long _start_time;

  // Wether the timer has triggered yet.
  bool _done = false;
};
