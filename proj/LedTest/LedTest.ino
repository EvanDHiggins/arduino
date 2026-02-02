#include "Arduino.h"
#include "HardwareSerial.h"
#include <Button.h>

uint8_t LED_PIN = 6;
uint8_t BUTTON_PIN = 5;
Button b = Button(BUTTON_PIN);

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  if (b.high()) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
}
