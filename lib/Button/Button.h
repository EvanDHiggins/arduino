#include <eh_common.h>
#include <Arduino.h>

class Button : Initializable {
public:
  Button(uint8_t pin, int debounceDelayMillis = 20)
    : _pin(pin), _debounceDelayMillis(debounceDelayMillis) {}

  void init() override;

  int get();

  int changedState();

private:
  uint8_t _pin;
  int _lastButtonState = LOW;
  int _debounceDelayMillis;

  int getStateDebounced();
};
