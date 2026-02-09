#include "SunriseAlarm.h"

SunriseAlarm::SunriseAlarm(SunriseAlarmConfig config)
  : _display(
      _timer_source,
      config.display_flash_on_duration_ms,
      config.display_flash_off_duration_ms
    )
{}

void SunriseAlarm::init() {
  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);
  _increment_button.init();
  _alarm_set_button.init();
  _rtc.init();
  _display.init();
  _alarm_time = DateTime(_rtc.now().unixtime() - 120);
}

void SunriseAlarm::update() {
  _timer_source.update();

  if (_alarm_set_button.high()) {
    handle_alarm_set();
  } else if (_time_set_button.high()) {
    handle_time_set();
  } else {
    digitalWrite(LED_PIN, LOW);
    _display.flash(false);
    _display.write_time(_rtc.now());
  }

  //if (_should_sound_alarm()) {
   // digitalWrite(LED_PIN, HIGH);
  //}
}

void SunriseAlarm::handle_alarm_set() {
    _display.flash(true);
    _display.write_time(_alarm_time);
    if (_increment_button.changedState() == HIGH) {
      _alarm_time = DateTime(_alarm_time.unixtime() + 60);
    }
}

void SunriseAlarm::handle_time_set() {
    _display.flash(true);
    if (_increment_button.changedState() == HIGH) {
      DateTime now = _rtc.now();
      _rtc.set(DateTime(now.unixtime() + 60));
    }
    _display.write_time(_rtc.now());
}
