#include "Program.h"

#include "Constantes.h"
#include "Core/SpecificCommandInterpretor.h"
#include "Core/Timer.h"
#include "Log/Logger.h"

Program::Program()
    : m_basicCommandInterpretor(nullptr),
      m_loggerDemoTimer(nullptr),
      m_demoTimer(nullptr) {
  Serial.begin(SERIAL_SPEED);
  Logger.begin(&Serial);

  this->demoLogger();

  this->m_loggerDemoTimer = new Timer(15_secondes, &Program::demoLogger);
  this->m_demoTimer =
      new Timer(10_secondes, []() { Logger.println(F("Hello, world!")); });
  this->m_basicCommandInterpretor = new SpecificCommandInterpretor(Serial);
}

void Program::loop() {
  this->m_basicCommandInterpretor->tick();

  // this->m_loggerDemoTimer->tick();
  this->m_demoTimer->tick();
}

void Program::demoLogger() {
  LOGGER_BEGIN_METHOD;

  // pour la démo seulement :
  static int i = 0;
  LOGGER_VAR(i);
  i++;

  Logger.println(F("Setting logger level to ERROR and printing tests..."));
  Logger.setLoggerLevel(LoggerLevel::ERROR);
  Logger.errorln(F("Hello World!"));
  Logger.warningln(F("Hello World!"));
  Logger.infoln(F("Hello World!"));
  Logger.verboseln(F("Hello World!"));

  Logger.println(F("Setting logger level to WARNING and printing tests..."));
  Logger.setLoggerLevel(LoggerLevel::WARNING);
  Logger.errorln(F("Hello World!"));
  Logger.warningln(F("Hello World!"));
  Logger.infoln(F("Hello World!"));
  Logger.verboseln(F("Hello World!"));

  Logger.println(F("Setting logger level to INFO and printing tests..."));
  Logger.setLoggerLevel(LoggerLevel::INFO);
  Logger.errorln(F("Hello World!"));
  Logger.warningln(F("Hello World!"));
  Logger.infoln(F("Hello World!"));
  Logger.verboseln(F("Hello World!"));

  Logger.println(F("Setting logger level to VERBOSE and printing tests..."));
  Logger.setLoggerLevel(LoggerLevel::VERBOSE);
  Logger.errorln(F("Hello World!"));
  Logger.warningln(F("Hello World!"));
  Logger.infoln(F("Hello World!"));
  Logger.verboseln(F("Hello World!"));

  LOGGER_END_METHOD
}
