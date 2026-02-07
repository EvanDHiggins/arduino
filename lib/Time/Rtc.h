#include <RTClib.h>
#include <Initializable.h>

class DS3231 : Initializable {
public:

  void init() {
    if (!_rtc.begin()) {
      Serial.println("Failing to initialize RTC. ");
      while (true) delay(10000);
    }

    if (_rtc.lostPower() || true) {
      Serial.println("RTC lost power, setting the time!");
      // Sets the RTC to the date & time this sketch was compiled
      _rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
  }

  DateTime now() {
    return _rtc.now();
  }

  void set(const DateTime& dt) {
    _rtc.adjust(dt);
  }

private:
  RTC_DS3231 _rtc;
};
