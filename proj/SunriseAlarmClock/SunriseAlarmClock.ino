#include <Timers.h>
#include <Button.h>
#include <SevenSegmentClock.h>
#include <RTClib.h>
#include <Rtc.h>
#include "SunriseAlarm.h"

SunriseAlarm sunrise_alarm;
void setup() {
  sunrise_alarm.init();
}

void loop() {
  sunrise_alarm.update();
}
