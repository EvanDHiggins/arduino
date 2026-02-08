#include <Button.h>
#include <Initializable.h>
#include <Timers.h>
#include <Rtc.h>
#include <SevenSegmentClock.h>

class SunriseAlarm : Initializable {
public:
  void init() override;

  void update();
private:

  void handle_alarm_set();
  void handle_time_set();

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
  OneShotTimer _alarm_timer = _timer_source.one_shot(0, true);
};
