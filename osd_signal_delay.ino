#include <avr/sleep.h>

#define BUTTON_PIN 2 // interrupt pin
#define OUTPUT_PIN 3

#define DELAY_MS 500

unsigned long pressedMillis = 0;

void setup() {
  pinMode(BUTTON_PIN, INPUT);
  pinMode(OUTPUT_PIN, INPUT);
}

void loop() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  cli();
  attachInterrupt(0, buttonTriggered, LOW);
  sei();
  sleep_cpu();

  // wakes here with interrupt
  
  sleep_disable();

  pressedMillis = millis();
  while (!digitalRead(BUTTON_PIN)) {
    if ((millis() - pressedMillis) > DELAY_MS) {
      digitalWrite(OUTPUT_PIN, LOW);
      pinMode(OUTPUT_PIN, OUTPUT);
    }
    delay(5);
  }

  pinMode(OUTPUT_PIN, INPUT);
}

void buttonTriggered() {
  detachInterrupt(0);
}
