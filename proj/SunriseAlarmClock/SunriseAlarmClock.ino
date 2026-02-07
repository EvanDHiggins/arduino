#include <Timers.h>
#include <Button.h>
#include <SevenSegmentClock.h>
#include <RTClib.h>
#include <Rtc.h>

const uint8_t INCREMENT_BUTTON_PIN = 5;
const uint8_t ALARM_SET_BUTTON_PIN = A3;
const uint8_t TIME_SET_BUTTON_PIN = A2;
const uint8_t LED_PIN = 6;

TimerSource timer_source;
Button increment_button = Button(INCREMENT_BUTTON_PIN);
DS3231 rtc;
SevenSegmentClock display(timer_source);

Button alarm_set_button = Button(ALARM_SET_BUTTON_PIN);
Button time_set_button = Button(TIME_SET_BUTTON_PIN);

DateTime alarm_time;
OneShotTimer alarm_timer = timer_source.one_shot(0, true);


void setup() {
  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);
  increment_button.init();
  alarm_set_button.init();
  rtc.init();
  display.init();
  alarm_time = DateTime(rtc.now().unixtime() - 120);
}

bool should_sound_alarm() {
  if (alarm_timer.active()) {
    
  }
  DateTime now = rtc.now();
  bool triggered = now.hour() == alarm_time.hour() && now.minute() == alarm_time.minute();
}

void loop() {
  timer_source.update();
  if (alarm_set_button.get() == HIGH) {
    display.flash(true);
    display.write_time(alarm_time);
    if (increment_button.changedState() == HIGH) {
      alarm_time = DateTime(alarm_time.unixtime() + 60);
    }
  } else if (time_set_button.get() == HIGH) {
    display.flash(true);
    if (increment_button.changedState() == HIGH) {
      DateTime now = rtc.now();
      rtc.set(DateTime(now.unixtime() + 60));
    }
    display.write_time(rtc.now());
  } else {
    digitalWrite(LED_PIN, LOW);
    display.flash(false);
    display.write_time(rtc.now());
  }

  if (should_sound_alarm()) {
    digitalWrite(LED_PIN, HIGH);
  }
}
