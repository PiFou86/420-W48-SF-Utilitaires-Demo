#include "Core/Timer.h"

#include <Arduino.h>
 
Timer::Timer(unsigned long interval, Callback callback)
    : m_nextTime(0), m_interval(interval), m_callback(callback) {
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
