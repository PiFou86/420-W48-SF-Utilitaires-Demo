#pragma once

#include "Core/callback.h"
#ifdef ESP32
#include <functional>
#endif

class Timer {
 private:
  unsigned long m_nextTime;
  unsigned long m_interval;
  #ifdef ARDUINO_AVR_UNO
  Callback m_callback;
  #elif ESP32
  std::function<void()> m_callback;
  #endif

 public:
  #ifdef ARDUINO_AVR_UNO
  Timer(unsigned long interval, Callback callback);
  #elif ESP32
  Timer(unsigned long interval, std::function<void()> callback);
  #endif
  void tick();
};

inline constexpr unsigned long operator"" _msecondes(unsigned long long ms) {
  return ms;
}

inline constexpr unsigned long operator"" _secondes(unsigned long long s) {
  return s * 1000;
}

inline constexpr unsigned long operator"" _minutes(unsigned long long minutes) {
  return minutes * 60 * 1000;
}

inline constexpr unsigned long operator"" _hours(unsigned long long h) {
  return h * 60 * 60 * 1000;
}
