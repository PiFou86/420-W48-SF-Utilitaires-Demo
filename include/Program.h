#pragma once

#include <Arduino.h>

class Timer;
class BasicCommandInterpretor;
class Program {
 private:
    BasicCommandInterpretor *m_basicCommandInterpretor;

    Timer *m_loggerDemoTimer;
    Timer *m_demoTimer;

    static void demoLogger();
 public:
  Program();
  void setup();
  void loop();
};