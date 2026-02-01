#include <Arduino.h>
#include <Common/Initializable.h>

class Button : Initializable {
public:
  Button(uint8_t pin, int debounceDelayMillis = 20)
    : _pin(pin), _debounceDelayMillis(debounceDelayMillis) {}

  void init() override;

  int get();

  bool high() {
    return this->get() == HIGH;
  }

  bool low() {
    return this->get() == LOW;
  }

  int changedState();

private:
  uint8_t _pin;
  int _lastButtonState = LOW;
  int _debounceDelayMillis;

  int getStateDebounced();
};
