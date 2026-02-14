#pragma once

#include "Arduino.h"
#include <Initializable.h>

class LED : Initializable {
public:
  LED(int pin) : _pin(pin) {}

  void init() override {
    pinMode(_pin, OUTPUT);
  }

  void update() {
    digitalWrite(_pin, int(_on));
  }

  void toggle() {
    set(!_on);
  }

  void on() {
    set(true);
  }

  void off() {
    set(false);
  }

  void set(bool on) {
    _on = on;
  }

private:
  int _pin;

  bool _on = false;

};
