#include <Timers.h>
#include <Button.h>
#include <SevenSegmentClock.h>
#include <RTClib.h>
#include <Rtc.h>
#include "SunriseAlarm.h"
#include <CppShim.h>

SunriseAlarm sunrise_alarm({
    .display_flash_on_duration_ms = 750,
    .display_flash_off_duration_ms = 250,
});

void setup() {
  sunrise_alarm.init();
}

void loop() {
  sunrise_alarm.update();
}
