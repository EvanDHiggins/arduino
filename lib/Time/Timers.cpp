#include <Timers.h>

// ========== TimerSource ========== 

void TimerSource::update() {
  _millis = millis();
}

OneShotTimer TimerSource::one_shot(
    unsigned long time_ms,
    bool start_disabled
) const {
  return OneShotTimer(*this, time_ms, start_disabled);
}

OneShotTimer TimerSource::disabled_one_shot() const {
  return one_shot(0, true);
}


// ========== OneShotTimer ========== 
//
OneShotTimer::OneShotTimer(
    const TimerSource& source,
    unsigned long duration_ms,
    bool start_disabled
) : _source(source),
    _start_time(source.current_millis()),
    _duration_ms(duration_ms),
    _done(start_disabled) {}

bool OneShotTimer::triggered() {
  if (_done) return false;

  unsigned long elapsed = _source.current_millis() - this->_start_time;
  if (elapsed >= _duration_ms) {
    _done = true;
    return true;
  }
  return false;
}

unsigned long OneShotTimer::remaining_ms() {
  if (!active()) return 0;
  return ((_start_time + _duration_ms) - _source.current_millis());
}

bool OneShotTimer::active() const {
  return !_done;
}

void OneShotTimer::reset() {
  _done = false;
  _start_time = _source.current_millis();
}
