#include <Button.h>
#include <Arduino.h>

void Button::init() {
  pinMode(_pin, INPUT);
}

int Button::get() {
  return getStateDebounced();
}

int Button::changedState() {
  int newState = getStateDebounced();
  if (newState != _lastButtonState) {
    _lastButtonState = newState;
    Serial.println("Returning new button state: " + newState);
    return newState;
  }

  return -1;
}

int Button::getStateDebounced() {
  int lastState = digitalRead(_pin);
  int lastTime = millis();
  while (true) {
    int state = digitalRead(_pin);
    if (state == lastState && (millis() - lastTime) > _debounceDelayMillis) {
      break;
    }
    lastState = state;
  }
  return digitalRead(_pin);
}
