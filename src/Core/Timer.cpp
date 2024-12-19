#include "Core/Timer.h"

#include <Arduino.h>
 
#ifdef ARDUINO_AVR_UNO
  Timer::Timer(unsigned long interval, Callback callback) {
#elif ESP32
  Timer::Timer(unsigned long interval, std::function<void()> callback) {
  #endif
  ;
}

void Timer::tick() {
  unsigned long now = millis();
  if (now >= this->m_nextTime) {
    while (now >= this->m_nextTime ) {
      this->m_nextTime += this->m_interval;
    }
    this->m_callback();
  }
}
