#include <Button.h>
#include <Initializable.h>
#include <Timers.h>
#include <Rtc.h>
#include <SevenSegmentClock.h>
#include <LED.h>

struct Debug {
  unsigned long force_sound_alarm_ms = 0;
};

struct SunriseAlarmConfig {
  unsigned long display_flash_on_duration_ms = 750;
  unsigned long display_flash_off_duration_ms = 750;
  Debug debug;
};

class SunriseAlarm : Initializable {
public:
  SunriseAlarm(SunriseAlarmConfig config);

  void init() override;

  void update();
private:
#ifdef DEBUG
  Debug _debug;
  LED _alarm_debug_led;
#endif

  void handle_alarm_set();
  void handle_time_set();
  bool should_sound_alarm();

  const uint8_t INCREMENT_BUTTON_PIN = 5;
  const uint8_t ALARM_SET_BUTTON_PIN = A3;
  const uint8_t TIME_SET_BUTTON_PIN = A2;
  const uint8_t LED_PIN = 6;

  bool _initialized = false;

  TimerSource _timer_source;
  Button _increment_button = Button(INCREMENT_BUTTON_PIN);
  DS3231 _rtc;
  SevenSegmentClock _display = SevenSegmentClock(
      _timer_source, 750, 150);

  Button _alarm_set_button = Button(ALARM_SET_BUTTON_PIN);
  Button _time_set_button = Button(TIME_SET_BUTTON_PIN);


  DateTime _alarm_time;
  OneShotTimer _alarm_timer;

};
